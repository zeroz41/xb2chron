#include "math.h"
#include "nvn/nvn.h"
#include "nvn/nvn_FuncPtrInline.h"
#include "grlib/CGLibUtilSH.h"
#include "grlib/CGLibUtilPixel.h"
#include "grlib/CGLibGpuTimeStamp.h"
#include "grlib/CGLibVtxFetch.h"
#include "grlib/CGLibVtxIndex.h"
#include "grlib/CGLibVtlMemPool.h"
#include "classes/grlib/context/CGLibSystemContext.h"
#include "classes/grlib/CGLibManager.h"
#include "mtl/MemManager.h"
#include "nn/os.h"
#include <string.h>

namespace grlib {

using context::CGLibSystemContext;


mm::Vec3 sgFace2DMapping[6][3] = {
    // +x face
    {mm::Vec3(0.0f, 0.0f, -1.0f), mm::Vec3(0.0f, -1.0f, 0.0f), mm::Vec3(1.0f, 0.0f, 0.0f)},
    // -x face
    {mm::Vec3(0.0f, 0.0f, 1.0f), mm::Vec3(0.0f, -1.0f, 0.0f), mm::Vec3(-1.0f, 0.0f, 0.0f)},
    // +y face
    {mm::Vec3(1.0f, 0.0f, 0.0f), mm::Vec3(0.0f, 0.0f, 1.0f), mm::Vec3(0.0f, 1.0f, 0.0f)},
    // -y face
    {mm::Vec3(1.0f, 0.0f, 0.0f), mm::Vec3(0.0f, 0.0f, -1.0f), mm::Vec3(0.0f, -1.0f, 0.0f)},
    // +z face
    {mm::Vec3(1.0f, 0.0f, 0.0f), mm::Vec3(0.0f, -1.0f, 0.0f), mm::Vec3(0.0f, 0.0f, 1.0f)},
    // -z face
    {mm::Vec3(-1.0f, 0.0f, 0.0f), mm::Vec3(0.0f, -1.0f, 0.0f), mm::Vec3(0.0f, 0.0f, -1.0f)},
};

void CGLibUtilSH::TexelCoordToVect(mm::Vec3& vect, int face, float u, float v, int size) {
    // from [0, size - 1] to [-(1 - 1 / size), 1 - 1 / size], + 0.5 for the texel centre
    float nvcU = 2.0f * (u + 0.5f) / (float)size - 1.0f;
    float nvcV = 2.0f * (v + 0.5f) / (float)size - 1.0f;

    // u contribution
    vect.x = nvcU * sgFace2DMapping[face][0].x;
    vect.y = nvcU * sgFace2DMapping[face][0].y;
    vect.z = nvcU * sgFace2DMapping[face][0].z;
    // v contribution
    mm::Vec3 temp = nvcV * sgFace2DMapping[face][1];
    vect.x = temp.x + vect.x;
    vect.y = temp.y + vect.y;
    vect.z = temp.z + vect.z;
    // the face axis
    vect.x = sgFace2DMapping[face][2].x + vect.x;
    vect.y = sgFace2DMapping[face][2].y + vect.y;
    vect.z = sgFace2DMapping[face][2].z + vect.z;

    float length = vect.length();
    if (length <= 1e-6f) {
        vect = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        vect.x = scale * vect.x;
        vect.y = scale * vect.y;
        vect.z = scale * vect.z;
    }
}

float CGLibUtilPixel::convF16toF32(unsigned short value) {
    unsigned int exponent = (value >> 10) & 0x1F;
    unsigned int bits;
    if (exponent == 0x1F) {
        bits = 0x7F800000;
    } else if (exponent == 0) {
        bits = 0;
    } else {
        bits = (exponent + 112) << 23;
    }
    bits = ((value & 0x8000) << 16) | ((value & 0x3FF) << 13) | bits;
    return *reinterpret_cast<float*>(&bits);
}

unsigned short CGLibUtilPixel::convF32toF16(float value) {
    unsigned int bits = *reinterpret_cast<unsigned int*>(&value);
    unsigned int exponent = (bits >> 23) & 0xFF;
    unsigned int mantissa;
    unsigned int half;
    if (exponent == 0xFF) {
        mantissa = (bits >> 13) & 0x3FF;
        half = 0x7C00;
    } else if (exponent < 0x66) {
        mantissa = 0;
        half = 0;
    } else if (exponent > 0x8E) {
        mantissa = 0;
        half = 0x7C00;
    } else if (exponent <= 0x70) {
        mantissa = ((bits & 0x7FFFFF) | 0x800000) >> (113 - exponent) >> 13;
        half = 0;
    } else {
        mantissa = 0;
        half = (exponent - 112) << 10;
    }
    return mantissa | ((bits >> 16) & 0x8000) | half;
}

CGLibGpuTimeStamp::CGLibGpuTimeStamp() {
    m_time = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            m_reports[i][j].clear();
        }
    }
}

CGLibGpuTimeStamp::~CGLibGpuTimeStamp() {
    release();
}

void CGLibGpuTimeStamp::release() {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (m_reports[j][i].m_pBuff != nullptr) {
                ctx->m_occlusion.freeID(m_reports[j][i].m_id);
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            m_reports[i][j].clear();
        }
    }
}

void CGLibGpuTimeStamp::reset() {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    for (int i = 1; i < 16; i++) {
        nvnCommandBufferResetCounter(ctx->m_pipeline.m_pCmdBuf, (NVNcounterType)i);
    }
}

void CGLibGpuTimeStamp::begin() {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    Report& report = m_reports[0][CGLibManager::s_nDblNowIdx];
    if (report.m_pBuff == nullptr) {
        report.m_id = ctx->m_occlusion.allocID();
        report.m_pBuff = ctx->m_occlusion.getBuffer(report.m_id);
        report.m_offset = report.m_pBuff - ctx->m_pReportPoolMem;
    }
    nvnCommandBufferReportCounter(ctx->m_pipeline.m_pCmdBuf, (NVNcounterType)0,
                                  nvnMemoryPoolGetBufferAddress(ctx->m_pReportPool) + report.m_offset);
}

void CGLibGpuTimeStamp::end() {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    Report& report = m_reports[1][CGLibManager::s_nDblNowIdx];
    if (report.m_pBuff == nullptr) {
        report.m_id = ctx->m_occlusion.allocID();
        report.m_pBuff = ctx->m_occlusion.getBuffer(report.m_id);
        report.m_offset = report.m_pBuff - ctx->m_pReportPoolMem;
    }
    nvnCommandBufferReportCounter(ctx->m_pipeline.m_pCmdBuf, (NVNcounterType)0,
                                  nvnMemoryPoolGetBufferAddress(ctx->m_pReportPool) + report.m_offset);
    int now = CGLibManager::s_nDblNowIdx;
    if (report.m_isReported && m_reports[0][now].m_pBuff != nullptr && m_reports[1][now].m_pBuff != nullptr) {
        unsigned long beginTime = nvnDeviceGetTimestampInNanoseconds(
            &CGLibManager::get()->m_device, reinterpret_cast<const NVNcounterData*>(m_reports[0][now].m_pBuff));
        unsigned long endTime = nvnDeviceGetTimestampInNanoseconds(
            &CGLibManager::get()->m_device, reinterpret_cast<const NVNcounterData*>(m_reports[1][now].m_pBuff));
        m_time = endTime - beginTime;
    } else {
        m_time = 0;
    }
    report.m_isReported = true;
}

void CGLibVtxFetch::release() {
    if (m_isAlloc != 0) {
        if (m_pAttribs != nullptr) {
            mtl::MemManager::deallocate(m_pAttribs, 0, false);
            m_pAttribs = nullptr;
        }
    } else {
        m_pAttribs = nullptr;
    }
    m_isAlloc = 0;
}

CGLibVtxFetch::CGLibVtxFetch() {
    m_pAttribs = nullptr;
    m_isAlloc = 0;
}

CGLibVtxFetch::~CGLibVtxFetch() {
    release();
}

void CGLibVtxFetch::createFetchObj(CGLibVtxAttr* attributes, int count) {
    int size = count * sizeof(NVNvertexAttribState);
    release();
    m_pAttribs = static_cast<NVNvertexAttribState*>(
        mtl::MemManager::allocate(CGLibMemHandle::s_hFchHandle, size, 4, false, "no name", 0));
    m_isAlloc = 1;
    m_attribNum = count;
    for (int i = 0; i < count; i++) {
        int location = attributes[i].location;
        nvnVertexAttribStateSetDefaults(&m_pAttribs[location]);
        nvnVertexAttribStateSetFormat(&m_pAttribs[location], (NVNformat)attributes[i].format, attributes[i].offset);
        nvnVertexAttribStateSetStreamIndex(&m_pAttribs[location], attributes[i].stream);
    }
}

int CGLibVtxFetch::createMemFetchObj(void* memory, CGLibVtxAttr* attributes, int count) {
    release();
    m_pAttribs = static_cast<NVNvertexAttribState*>(memory);
    m_isAlloc = 0;
    m_attribNum = count;
    for (int i = 0; i < count; i++) {
        int location = attributes[i].location;
        nvnVertexAttribStateSetDefaults(&m_pAttribs[location]);
        nvnVertexAttribStateSetFormat(&m_pAttribs[location], (NVNformat)attributes[i].format, attributes[i].offset);
        nvnVertexAttribStateSetStreamIndex(&m_pAttribs[location], attributes[i].stream);
    }
    return count * sizeof(NVNvertexAttribState);
}

CGLibVtxIndex::CGLibVtxIndex() {
    m_count = 0;
}

CGLibVtxIndex::~CGLibVtxIndex() {
    CGLibMemHandle::free(m_mem);
}

void CGLibVtxIndex::release() {
    CGLibMemHandle::free(m_mem);
}

void CGLibVtxIndex::createIndexBuff(unsigned int count, GrlPrimitiveType type, GrlIndexFormat format) {
    release();
    m_type = type;
    m_format = format;
    m_count = count;
    int size = getIndexSize();
    CGLibMemHandle::allocVertex(m_mem, size + (4 - size % 4) % 4);
    CGLibSystemContext::get()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxIndex::createMemIndexBuff(CGLibVtlMemPool* pool, unsigned int offset, unsigned int count,
                                       GrlPrimitiveType type, GrlIndexFormat format) {
    release();
    m_type = type;
    m_format = format;
    m_count = count;
    resetIndexBuff(pool, offset);
}

void CGLibVtxIndex::createCopyIndexBuff(const void* indices, unsigned int count, GrlPrimitiveType type,
                                        GrlIndexFormat format) {
    release();
    m_type = type;
    m_format = format;
    m_count = count;
    int size = getIndexSize();
    CGLibMemHandle::allocVertex(m_mem, size + (4 - size % 4) % 4);
    memcpy(m_mem.m_pMem, indices, size);
    nn::os::FlushDataCache(m_mem.m_pMem, size);
    CGLibSystemContext::get()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxIndex::resetIndexBuff(CGLibVtlMemPool* pool, unsigned int offset) {
    CGLibMemHandle::setMemBuff(m_mem, pool->m_pMem + offset);
    m_gpuAddress = pool->m_gpuAddress + offset;
}

void CGLibVtxIndex::drawIndex() {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_pipeline.updateVertex();
    nvnCommandBufferDrawElements(ctx->m_pipeline.m_pCmdBuf, (NVNdrawPrimitive)m_type, (NVNindexType)m_format, m_count,
                                 m_gpuAddress);
}

void CGLibVtxIndex::drawIndex(unsigned int count, unsigned int offset) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_pipeline.updateVertex();
    nvnCommandBufferDrawElements(ctx->m_pipeline.m_pCmdBuf, (NVNdrawPrimitive)m_type, (NVNindexType)m_format, count,
                                 m_gpuAddress + offset);
}

void CGLibVtxIndex::drawInsIndex(int instances) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_pipeline.updateVertex();
    nvnCommandBufferDrawElementsInstanced(ctx->m_pipeline.m_pCmdBuf, (NVNdrawPrimitive)m_type, (NVNindexType)m_format,
                                          m_count, m_gpuAddress, 0, 0, instances);
}

void CGLibVtxIndex::drawInsIndex(int instances, unsigned int count, unsigned int offset) {
    CGLibSystemContext* ctx = CGLibSystemContext::get();
    ctx->m_pipeline.updateVertex();
    nvnCommandBufferDrawElementsInstanced(ctx->m_pipeline.m_pCmdBuf, (NVNdrawPrimitive)m_type, (NVNindexType)m_format,
                                          count, m_gpuAddress + offset, 0, 0, instances);
}

void CGLibVtxIndex::lock(void** buffer, unsigned int* size) {
    *buffer = m_mem.m_pMem;
    *size = getIndexSize();
}

void CGLibVtxIndex::unlock() {
    int size = getIndexSize();
    nn::os::FlushDataCache(m_mem.m_pMem, size);
}

}  // namespace grlib
