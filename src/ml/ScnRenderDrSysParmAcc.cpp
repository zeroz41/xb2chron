#include "nvn/nvn.h"
#include "nn/diag.h"
#include "grlib/CGLibTexDescriptor.h"
#include "grlib/CGLibSamplerDescriptor.h"
#include "grlib/CGLibTextureBuffer.h"
#include "nn/vi.h"
#include "nv/nv_MemoryManagement.h"
#include <stdlib.h>
#include "grlib/CGLibVtlMemPool.h"
#include "grlib/CGLibMemHandle.h"
#include "grlib/CGLibBuffReleaseTbl.h"
#include "nvn/nvn_FuncPtrInline.h"
#include "mtl/MemManager.h"
#include "ml/MlMem.h"
#include "grlib/CGLibDeviceObj.h"
#include "grlib/CGLibBuffFixAlloc.h"
#include "grlib/CGLibMemPoolAdder.h"
#include "grlib/CGLibMemPool.h"
#include "grlib/CGLibCmdBuffer.h"
#include "classes/grlib/context/CGLibSystemContext.h"
#include "classes/ml/DrMdoMat.h"
#include "classes/ml/ScnRender.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/DrMan.h"
#include "classes/ml/Scn.h"
#include "classes/ml/WorkCpu.h"
#include "classes/cloud/CloudMan.h"
#include "ml/DrIniSys.h"
#include "ml/DrPixlPostParm.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "ml/ScnRenderDrViewCtrl.h"
#include "classes/ml/ScnObjModelDrSys.h"
#include "ml/MdoWrkMatRes.h"
#include "classes/ml/DrMdlObj.h"
#include "classes/ml/DrMdoCtlNom.h"
#include "ml/DrResEtcParams.h"
#include "ml/DrResEtcPamObj.h"
#include "ml/DrResMdoMeshObj.h"
#include "ml/DrResMdoVtxMeshObj.h"
#include "ml/DrCreator.h"
#include "ml/DrEnvColiMan.h"
#include "ml/DrEnvironmentMan.h"
#include "ml/ScnObjAccResMdlInfo.h"
#include "ml/ScnObjAccResNode.h"
#include "ml/ScnObjAccEtcParams.h"
#include "ml/ScnObjAccResSubMesh.h"
#include "ml/ScnObjAccVolumeFade.h"
#include "ml/ScnObjAccMdlParticle.h"
#include "ml/ScnObjAccGpuCheck.h"
#include "ml/ScnObjAccStmReadObj.h"
#include "ml/ScnRenderDrEnvColi.h"
#include "ml/ScnObjAccRimBloom.h"
#include "ml/DrStmReadObj.h"
#include "classes/ml/ScnObjModelDrSysStandard.h"
#include "classes/ml/ScnObjLightDrSys.h"
#include "classes/ml/ScnObjClipDySys.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnObjEnvColiDr.h"
#include "ml/ScnObjAccSeamPos.h"
#include "ml/ScnObjAccSeamEtcPos.h"
#include "classes/ml/DrMdoCtlPos.h"
#include "nn/os.h"
#include "classes/grlib/CGLibManager.h"
#include "grlib/CGLibVtxInstans.h"
#include "grlib/CGLibVtxOneInstans.h"
#include "grlib/CGLibVtxVertex.h"
#include "grlib/CGLibVtxStmOut.h"
#include <string.h>

namespace grlib {

CGLibVtxInstans::CGLibVtxInstans() { m_base = 0; }

CGLibVtxInstans::~CGLibVtxInstans() { CGLibMemHandle::free(m_mem); }

void CGLibVtxInstans::release() { CGLibMemHandle::free(m_mem); }

void CGLibVtxInstans::createInstansBuffer(int size) {
    CGLibMemHandle::free(m_mem);
    m_size = size;
    m_frameSize = m_size / 2;
    CGLibMemHandle::allocVertex(m_mem, size);
    context::CGLibSystemContext::sys()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxInstans::beginInstansBuff() {
    m_base = CGLibManager::s_nDblNowIdx * m_frameSize;
    m_offset = 0;
    m_flushed = 0;
}

void CGLibVtxInstans::updateInstansBuff() {
    unsigned int size = m_offset - m_flushed;
    if (size != 0) {
        nn::os::FlushDataCache(static_cast<unsigned char*>(m_mem.m_pMem) + (m_base + m_flushed), size);
        m_flushed = m_offset;
    }
}

void* CGLibVtxInstans::getNextInstansBuff() { return static_cast<unsigned char*>(m_mem.m_pMem) + (m_offset + m_base); }

unsigned long CGLibVtxInstans_plf::getGPUAdress() { return m_gpuAddress + CGLibManager::s_nDblNowIdx * m_frameSize; }

CGLibVtxOneInstans::CGLibVtxOneInstans() {}

CGLibVtxOneInstans::~CGLibVtxOneInstans() { CGLibMemHandle::free(m_mem); }

void CGLibVtxOneInstans::createInstansBuffer(int size) {
    CGLibMemHandle::free(m_mem);
    m_size = size;
    CGLibMemHandle::allocVertex(m_mem, size);
    context::CGLibSystemContext::sys()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxOneInstans::beginInstansBuff() {
    m_offset = 0;
    m_flushed = 0;
}

void CGLibVtxOneInstans::updateInstansBuff() {
    if (m_offset != m_flushed) {
        nn::os::FlushDataCache(static_cast<unsigned char*>(m_mem.m_pMem) + m_flushed, m_offset - m_flushed);
        m_flushed = m_offset;
    }
}

void* CGLibVtxOneInstans::getBuff() { return m_mem.m_pMem; }

CGLibVtxStmOut::CGLibVtxStmOut() {}

CGLibVtxStmOut::~CGLibVtxStmOut() { CGLibMemHandle::free(m_mem); }

void CGLibVtxStmOut::release() { CGLibMemHandle::free(m_mem); }

void CGLibVtxStmOut::createWorkBuff(int size) {
    CGLibMemHandle::free(m_mem);
    size += (4 - size % 4) % 4;
    CGLibMemHandle::allocVertex(m_mem, size);
    m_stride = 0;
    m_used = 0;
    m_size = size;
    context::CGLibSystemContext::sys()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxStmOut::begin(int stride) {
    m_stride = stride;
    context::CGLibSystemContext* pSys = context::CGLibSystemContext::sys();
    nvnCommandBufferSetRasterizerDiscard(pSys->m_pipeline.m_pCmdBuf, true);
    nvnCommandBufferBindTransformFeedbackBuffer(pSys->m_pipeline.m_pCmdBuf, 0, m_gpuAddress, m_size);
    nvnCommandBufferBeginTransformFeedback(pSys->m_pipeline.m_pCmdBuf, m_gpuAddress + m_size);
}

void CGLibVtxStmOut::end(unsigned int count) {
    m_used = m_stride * count;
    context::CGLibSystemContext* pSys = context::CGLibSystemContext::sys();
    nvnCommandBufferEndTransformFeedback(pSys->m_pipeline.m_pCmdBuf, m_gpuAddress + m_used);
    nvnCommandBufferSetRasterizerDiscard(pSys->m_pipeline.m_pCmdBuf, false);
    nvnCommandBufferBarrier(pSys->m_pipeline.m_pCmdBuf, 0x21);
}

void CGLibVtxStmOut::setStorageBuffer(unsigned int location) {
    if (location != 0xFFFFFFFF) {
        context::CGLibSystemContext* pSys = context::CGLibSystemContext::sys();
        pSys->m_pipeline.m_pShader->setStorageBuffer(location, pSys->m_pipeline.m_pCmdBuf, m_gpuAddress, m_size);
    }
}

void CGLibVtxStmOut::setStorageBuffer(unsigned int location, unsigned int offset, unsigned int size) {
    if (location != 0xFFFFFFFF) {
        context::CGLibSystemContext* pSys = context::CGLibSystemContext::sys();
        pSys->m_pipeline.m_pShader->setStorageBuffer(location, pSys->m_pipeline.m_pCmdBuf, m_gpuAddress + offset, size);
    }
}

unsigned int CGLibVtxStmOut::getSize() { return m_size; }

CGLibVtxVertex::CGLibVtxVertex() : m_size(0), m_stride(0), m_num(0) {}

CGLibVtxVertex::~CGLibVtxVertex() { CGLibMemHandle::free(m_mem); }

void CGLibVtxVertex::release() { CGLibMemHandle::free(m_mem); }

void CGLibVtxVertex::delayRelease() { context::CGLibSystemContext::sys()->releaseDelayVertex(m_mem); }

void CGLibVtxVertex::createVertexBuff(unsigned int size, unsigned int stride) {
    CGLibMemHandle::free(m_mem);
    m_size = size;
    m_stride = stride;
    m_num = size / stride;
    CGLibMemHandle::allocVertex(m_mem, size + (-size & 3));
    context::CGLibSystemContext::sys()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxVertex::createMemVertexBuff(CGLibVtlMemPool* pool, unsigned int offset, unsigned int size,
                                         unsigned int stride) {
    CGLibMemHandle::free(m_mem);
    m_size = size;
    m_stride = stride;
    m_num = size / stride;
    CGLibMemHandle::setMemBuff(m_mem, pool->m_pMem + offset);
    m_gpuAddress = pool->m_gpuAddress + offset;
}

void CGLibVtxVertex::createCopyVertexBuff(const void* vertices, unsigned int size, unsigned int stride) {
    CGLibMemHandle::free(m_mem);
    m_num = size / m_stride;
    m_size = size;
    m_stride = stride;
    CGLibMemHandle::allocVertex(m_mem, size + (-size & 3));
    memcpy(m_mem.m_pMem, vertices, size);
    nn::os::FlushDataCache(m_mem.m_pMem, size);
    context::CGLibSystemContext::sys()->getVertexGpuAddress(m_gpuAddress, m_mem);
}

void CGLibVtxVertex::resetVertexBuff(CGLibVtlMemPool* pool, unsigned int offset) {
    CGLibMemHandle::setMemBuff(m_mem, pool->m_pMem + offset);
    m_gpuAddress = pool->m_gpuAddress + offset;
}

void CGLibVtxVertex::lock(void** ppBuffer, unsigned int* pSize) {
    *ppBuffer = m_mem.m_pMem;
    *pSize = m_size;
}

void CGLibVtxVertex::unlock() { nn::os::FlushDataCache(m_mem.m_pMem, m_size); }

void CGLibVtxVertex::unlock(unsigned int offset, unsigned int size) {
    nn::os::FlushDataCache(static_cast<unsigned char*>(m_mem.m_pMem) + offset, size);
}

CGLibMemPoolList::CGLibMemPoolList() : m_offset(0) {}

CGLibMemPoolList::~CGLibMemPoolList() { release(); }

void CGLibMemPoolList::release() {
    CGLibMemPool::release();
    m_offset = 0;
}

void CGLibMemPoolList::setupHandle(mtl::ALLOC_HANDLE handle, unsigned int size, unsigned int flags) {
    CGLibMemPool::setupHandle(handle, size, flags);
}

void CGLibMemPool::setupHandle(mtl::ALLOC_HANDLE handle, unsigned int size, unsigned int flags) {
    release();
    m_pAlloc = mtl::MemManager::allocate(handle, size, 0x1000, false, "no name", 0);
    setupBuffer(m_pAlloc, size + (-size & 0xFFF), flags);
}

void CGLibMemPool::release() {
    if (m_size != 0) {
        nvnMemoryPoolFinalize(m_pPool);
        context::CGLibSystemContext::sys()->m_memPoolTbl.freeBuffer(m_pPool);
        m_size = 0;
        if (m_pAlloc != nullptr) {
            mtl::MemManager::deallocate(m_pAlloc, 0, false);
            m_pAlloc = nullptr;
        }
        m_pPool = nullptr;
    }
}

unsigned int CGLibMemPoolList::cntOffset(unsigned int size, unsigned int alignment) {
    unsigned int offset = m_offset + (alignment - m_offset % alignment) % alignment;
    m_offset = (alignment - size % alignment) % alignment + offset + size;
    return offset;
}

CGLibMemPool::CGLibMemPool() : m_size(0), m_pAlloc(nullptr), m_pBuffer(nullptr) {}

CGLibPartsMemPool::CGLibPartsMemPool() : m_pPrev(nullptr), m_pNext(nullptr) {}

CGLibPartsMemPool::~CGLibPartsMemPool() { m_pool.release(); }

CGLibMemPool::~CGLibMemPool() { release(); }

void CGLibPartsMemPool::addAdder(void* buffer, unsigned int size) { m_pool.setupBuffer(buffer, size, 100); }

void CGLibMemPool::setupBuffer(void* buffer, unsigned int size, unsigned int flags) {
    release();
    m_size = size;
    m_pBuffer = buffer;
    NVNdevice* pDevice = &CGLibManager::sys()->m_device;
    NVNmemoryPoolBuilder builder;
    nvnMemoryPoolBuilderSetDefaults(&builder);
    nvnMemoryPoolBuilderSetDevice(&builder, pDevice);
    nvnMemoryPoolBuilderSetFlags(&builder, flags);
    nvnMemoryPoolBuilderSetStorage(&builder, buffer, size);
    CGLibBuffMemPoolTbl& tbl = context::CGLibSystemContext::sys()->m_memPoolTbl;
    m_pPool = reinterpret_cast<NVNmemoryPool*>(tbl.getBuffer(tbl.allocID()));
    nvnMemoryPoolInitialize(m_pPool, &builder);
}

// 1.0.0 still had it out of line (3.0.1 inlines it everywhere)
const ml::CriticalSection& CGLibMemPoolAdder::getCriticalSection() {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71015E92E0, its guard lbl_71015E9308)
    static ml::CriticalSection s_cs;
    return s_cs;
}

CGLibMemPoolAdder::CGLibMemPoolAdder() : m_pHead(nullptr), m_pTail(nullptr) {}

CGLibMemPoolAdder::~CGLibMemPoolAdder() { release(); }

void CGLibMemPoolAdder::release() {
    CGLibPartsMemPool* pPool = m_pHead;
    while (pPool != nullptr) {
        CGLibPartsMemPool* pNext = pPool->m_pNext;
        delete pPool;
        pPool = pNext;
    }
    m_pHead = nullptr;
    m_pTail = nullptr;
}

void CGLibMemPoolAdder::setup() { release(); }

CGLibMemPool* CGLibMemPoolAdder::getMemPool(const void* p) {
    ml::CS lock(getCriticalSection());
    for (CGLibPartsMemPool* pPool = m_pHead; pPool != nullptr; pPool = pPool->m_pNext) {
        unsigned long top = reinterpret_cast<unsigned long>(pPool->m_pool.m_pBuffer);
        if (top <= reinterpret_cast<unsigned long>(p) && reinterpret_cast<unsigned long>(p) - top < pPool->m_pool.m_size) {
            return &pPool->m_pool;
        }
    }
    return nullptr;
}

void CGLibMemPoolAdder::releaseAdder(void* buffer) {
    ml::CS lock(getCriticalSection());
    for (CGLibPartsMemPool* pPool = m_pHead; pPool != nullptr; pPool = pPool->m_pNext) {
        if (pPool->m_pool.m_pBuffer == buffer) {
            CGLibPartsMemPool* pPrev = pPool->m_pPrev;
            CGLibPartsMemPool* pNext = pPool->m_pNext;
            if (pPrev == nullptr) {
                if (pNext == nullptr) {
                    m_pHead = nullptr;
                    m_pTail = nullptr;
                } else {
                    m_pHead = pNext;
                    pNext->m_pPrev = nullptr;
                }
            } else if (pNext == nullptr) {
                m_pTail = pPrev;
                pPrev->m_pNext = nullptr;
            } else {
                pPool->m_pPrev->m_pNext = pPool->m_pNext;
                pPool->m_pNext->m_pPrev = pPool->m_pPrev;
            }
            pPool->m_pPrev = nullptr;
            pPool->m_pNext = nullptr;
            delete pPool;
            break;
        }
    }
}

void CGLibMemPoolAdder::addAdder(mtl::ALLOC_HANDLE handle) {
    addAdder(mtl::MemManager::getTopAdr(handle), mtl::MemManager::getTotalSize(handle));
}

void CGLibMemPoolAdder::releaseAdder(mtl::ALLOC_HANDLE handle) { releaseAdder(mtl::MemManager::getTopAdr(handle)); }

mtl::ALLOC_HANDLE CGLibMemHandle::s_hTop;
mtl::ALLOC_HANDLE CGLibMemHandle::s_hDefHandle;
mtl::ALLOC_HANDLE CGLibMemHandle::s_hPxlHandle;
mtl::ALLOC_HANDLE CGLibMemHandle::s_hVtxHandle;
mtl::ALLOC_HANDLE CGLibMemHandle::s_hUniHandle;
mtl::ALLOC_HANDLE CGLibMemHandle::s_hMemHandle;
mtl::ALLOC_HANDLE CGLibMemHandle::s_hFchHandle;
mtl::ALLOC_HANDLE CGLibMemHandle::s_hShdHandle;
mtl::ALLOC_HANDLE CGLibMemHandle::s_hCntHandle;

// 1.0.0 still had it out of line (3.0.1 inlines it everywhere)
const ml::CriticalSection& CGLibMemHandle::getCriticalSection() {
    // Proposed name, not the original's: the symbols leave it unnamed (lbl_71015E9338, its guard lbl_71015E9360)
    static ml::CriticalSection s_cs;
    return s_cs;
}

void CGLibMemHandle::setup(const ArgMemInfo& info) {
    release();
    unsigned int defSize = info.m_topSize + info.m_etc128Size + info.m_etc256Size + info.m_etc512Size +
                           info.m_etc768Size + info.m_etc1024Size;
    unsigned int topSize = defSize + info.m_pxlSize + info.m_vtxSize + info.m_uniSize + info.m_memSize +
                           info.m_fetSize + info.m_shdSize + 0x20000;
    s_hTop = mtl::MemManager::create(ml::MlMem::getGraphicMem(), topSize, "GLIBTOP", false, mtl::AllocatorType(1),
                                     0x10000, "no name", 0);
    s_hCntHandle = mtl::MemManager::create(ml::MlMem::getGraphicMem(), info.m_cntSize, "GLIBCNT", true,
                                           mtl::AllocatorType(1), 0x1000, "no name", 0);
    s_hDefHandle = mtl::MemManager::create(s_hTop, defSize, "GLIBDEF", true, mtl::AllocatorType(1), 0x1000, "no name", 0);
    s_hPxlHandle =
        mtl::MemManager::create(s_hTop, info.m_pxlSize, "GLIBPXL", true, mtl::AllocatorType(1), 0x10000, "no name", 0);
    s_hVtxHandle =
        mtl::MemManager::create(s_hTop, info.m_vtxSize, "GLIBVTX", false, mtl::AllocatorType(1), 0x1000, "no name", 0);
    s_hUniHandle =
        mtl::MemManager::create(s_hTop, info.m_uniSize, "GLIBUNI", false, mtl::AllocatorType(1), 0x1000, "no name", 0);
    s_hMemHandle =
        mtl::MemManager::create(s_hTop, info.m_memSize, "GLIBMEM", true, mtl::AllocatorType(1), 0x1000, "no name", 0);
    s_hFchHandle =
        mtl::MemManager::create(s_hTop, info.m_fetSize, "GLIBFET", true, mtl::AllocatorType(1), 0x1000, "no name", 0);
    s_hShdHandle =
        mtl::MemManager::create(s_hTop, info.m_shdSize, "GLIBSHD", true, mtl::AllocatorType(1), 0x1000, "no name", 0);
}

void CGLibMemHandle::release() {
    if (s_hDefHandle.m_handle != 0) {
        mtl::MemManager::erase(s_hDefHandle);
        s_hDefHandle = mtl::ALLOC_HANDLE();
    }
    if (s_hPxlHandle.m_handle != 0) {
        mtl::MemManager::erase(s_hPxlHandle);
        s_hPxlHandle = mtl::ALLOC_HANDLE();
    }
    if (s_hVtxHandle.m_handle != 0) {
        mtl::MemManager::erase(s_hVtxHandle);
        s_hVtxHandle = mtl::ALLOC_HANDLE();
    }
    if (s_hUniHandle.m_handle != 0) {
        mtl::MemManager::erase(s_hUniHandle);
        s_hUniHandle = mtl::ALLOC_HANDLE();
    }
    if (s_hMemHandle.m_handle != 0) {
        mtl::MemManager::erase(s_hMemHandle);
        s_hMemHandle = mtl::ALLOC_HANDLE();
    }
    if (s_hFchHandle.m_handle != 0) {
        mtl::MemManager::erase(s_hFchHandle);
        s_hFchHandle = mtl::ALLOC_HANDLE();
    }
    if (s_hShdHandle.m_handle != 0) {
        mtl::MemManager::erase(s_hShdHandle);
        s_hShdHandle = mtl::ALLOC_HANDLE();
    }
    if (s_hCntHandle.m_handle != 0) {
        mtl::MemManager::erase(s_hCntHandle);
        s_hCntHandle = mtl::ALLOC_HANDLE();
    }
    if (s_hTop.m_handle != 0) {
        mtl::MemManager::erase(s_hTop);
        s_hTop = mtl::ALLOC_HANDLE();
    }
    s_hTop = mtl::ALLOC_HANDLE();
    s_hDefHandle = mtl::ALLOC_HANDLE();
    s_hPxlHandle = mtl::ALLOC_HANDLE();
    s_hVtxHandle = mtl::ALLOC_HANDLE();
    s_hUniHandle = mtl::ALLOC_HANDLE();
    s_hMemHandle = mtl::ALLOC_HANDLE();
    s_hFchHandle = mtl::ALLOC_HANDLE();
    s_hShdHandle = mtl::ALLOC_HANDLE();
}

void CGLibMemHandle::setMemBuff(CGLibMemType& mem, void* buffer) {
    ml::CS lock(getCriticalSection());
    mem.m_pMem = buffer;
    mem.m_type = 5;
}

void CGLibMemHandle::allocVertex(CGLibMemType& mem, unsigned int size) {
    ml::CS lock(getCriticalSection());
    if (size <= 128) {
        mem.m_type = 0;
        CGLibBuffMinUniform& buff = context::CGLibSystemContext::sys()->m_etcBuffer[0];
        mem.m_pMem = buff.getBuffer(buff.allocID());
    } else if (size <= 256) {
        mem.m_type = 1;
        CGLibBuffMinUniform& buff = context::CGLibSystemContext::sys()->m_etcBuffer[1];
        mem.m_pMem = buff.getBuffer(buff.allocID());
    } else if (size <= 512) {
        mem.m_type = 2;
        CGLibBuffMinUniform& buff = context::CGLibSystemContext::sys()->m_etcBuffer[2];
        mem.m_pMem = buff.getBuffer(buff.allocID());
    } else if (size <= 768) {
        mem.m_type = 3;
        CGLibBuffMinUniform& buff = context::CGLibSystemContext::sys()->m_etcBuffer[3];
        mem.m_pMem = buff.getBuffer(buff.allocID());
    } else if (size <= 1024) {
        mem.m_type = 4;
        CGLibBuffMinUniform& buff = context::CGLibSystemContext::sys()->m_etcBuffer[4];
        mem.m_pMem = buff.getBuffer(buff.allocID());
    } else {
        mem.m_pMem = mtl::MemManager::allocate(s_hVtxHandle, size, 4, false, "no name", 0);
        mem.m_type = 6;
    }
}

void CGLibMemHandle::allocUniform(CGLibMemType& mem, unsigned int size) {
    ml::CS lock(getCriticalSection());
    if (size <= 256) {
        mem.m_type = 1;
        CGLibBuffMinUniform& buff = context::CGLibSystemContext::sys()->m_etcBuffer[1];
        mem.m_pMem = buff.getBuffer(buff.allocID());
    } else if (size <= 512) {
        mem.m_type = 2;
        CGLibBuffMinUniform& buff = context::CGLibSystemContext::sys()->m_etcBuffer[2];
        mem.m_pMem = buff.getBuffer(buff.allocID());
    } else if (size <= 768) {
        mem.m_type = 3;
        CGLibBuffMinUniform& buff = context::CGLibSystemContext::sys()->m_etcBuffer[3];
        mem.m_pMem = buff.getBuffer(buff.allocID());
    } else if (size <= 1024) {
        mem.m_type = 4;
        CGLibBuffMinUniform& buff = context::CGLibSystemContext::sys()->m_etcBuffer[4];
        mem.m_pMem = buff.getBuffer(buff.allocID());
    } else {
        mem.m_pMem = mtl::MemManager::allocate(s_hUniHandle, size, 0x100, false, "no name", 0);
        mem.m_type = 6;
    }
}

void CGLibBuffFixAlloc::freeBuffer(void* p) {
    freeID((reinterpret_cast<unsigned long>(p) - reinterpret_cast<unsigned long>(m_pBuff)) / m_elemSize);
}

CGLibBuffFixAlloc::CGLibBuffFixAlloc() : m_pBuff(nullptr), m_pBits(nullptr), m_nextID(0), m_num(0) {}

CGLibBuffFixAlloc::~CGLibBuffFixAlloc() { releaseTbl(); }

void CGLibBuffFixAlloc::releaseTbl() {
    if (m_pBuff != nullptr) {
        mtl::MemManager::deallocate(m_pBuff, 0, false);
        m_pBuff = nullptr;
    }
    if (m_pBits != nullptr) {
        mtl::MemManager::deallocate(m_pBits, 0, false);
        m_pBits = nullptr;
    }
}

void CGLibBuffFixAlloc::setupTbl(mtl::ALLOC_HANDLE hTbl, mtl::ALLOC_HANDLE hBuff, unsigned int num, unsigned int size,
                                 unsigned int alignment) {
    setupTbl(hTbl, num, size);
    unsigned int buffSize = m_elemSize * m_num;
    m_pBuff = static_cast<unsigned char*>(mtl::MemManager::allocate(hBuff, buffSize, alignment, false, "no name", 0));
}

// Not identical yet: 6 words off from the original (0x7100706764; register scheduling). Kept because the 5-argument
// setupTbl and setupFixTbl inline it, and those match only with this body.
void CGLibBuffFixAlloc::setupTbl(mtl::ALLOC_HANDLE hTbl, unsigned int num, unsigned int size) {
    releaseTbl();
    unsigned int bitsNum = num / 64;
    if (num % 64 != 0) {
        bitsNum++;
    }
    m_elemSize = size;
    m_num = num;
    m_bitsNum = bitsNum;
    unsigned int bitsSize = bitsNum * sizeof(unsigned long);
    m_pBits = static_cast<unsigned long*>(mtl::MemManager::allocate(hTbl, bitsSize, 0x10, false, "no name", 0));
    m_bitsIdx = 0;
    m_useNum = 0;
    m_nextID = 0;
    memset(m_pBits, 0, bitsSize);
}

void CGLibBuffFixAlloc::setupFixTbl(mtl::ALLOC_HANDLE hTbl, mtl::ALLOC_HANDLE hBuff, unsigned int num,
                                    unsigned int size, unsigned int buffSize, unsigned int alignment) {
    setupTbl(hTbl, num, size);
    m_pBuff = static_cast<unsigned char*>(mtl::MemManager::allocate(hBuff, buffSize, alignment, false, "no name", 0));
}

int CGLibBuffFixAlloc::createBuff() {
    m_pBits[m_nextID >> 6] |= 1UL << (m_nextID & 0x3F);
    int id = m_nextID;
    m_nextID = id + 1 < m_num ? id + 1 : 0;
    m_useNum++;
    m_bitsIdx = m_nextID >> 6;
    return id;
}

void CGLibBuffFixAlloc::freeID(unsigned int id) {
    m_pBits[id >> 6] &= ~(1UL << (static_cast<unsigned long>(id) & 0x3F));
    m_useNum--;
}

CGLibBuffSamplerTbl::CGLibBuffSamplerTbl() : m_pBuff(nullptr), m_useNum(0), m_num(0) {}

CGLibBuffSamplerTbl::~CGLibBuffSamplerTbl() { release(); }

CGLibBuffTexture::CGLibBuffTexture() {}

CGLibBuffTexture::~CGLibBuffTexture() { release(); }

void CGLibBuffTexture::release() {
    releasePlf();
    releaseTbl();
}

void CGLibBuffTexture::createTexture(unsigned int num) {
    release();
    setupTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hDefHandle, num, 0xC0, 0x10);
    createPlf(num, m_pBuff);
}

CGLibBuffOcclusion::CGLibBuffOcclusion() {}

CGLibBuffOcclusion::~CGLibBuffOcclusion() { release(); }

void CGLibBuffOcclusion::release() {
    releasePlf();
    releaseTbl();
}

unsigned int CGLibBuffOcclusion_plf::getBufferSize() { return context::CGLibSystemContext::s_nvReportCounterSize * 2; }

void CGLibBuffOcclusion::createOcclusion(unsigned int num) {
    release();
    setupTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hCntHandle, num, getBufferSize(), 0x1000);
    createPlf(num, m_pBuff);
}

CGLibBuffMemPoolTbl::CGLibBuffMemPoolTbl() {}

CGLibBuffMemPoolTbl::~CGLibBuffMemPoolTbl() { release(); }

void CGLibBuffMemPoolTbl::release() { releaseTbl(); }

void CGLibBuffMemPoolTbl::createMemPoolTbl(unsigned int num) {
    release();
    setupTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hDefHandle, num, 0x100, 0x100);
}

// 1.0.0 still had these three out of line (3.0.1 inlines them everywhere)
CGLibReleaseObj::CGLibReleaseObj() : m_work(), m_pNext(nullptr) {}

CGLibReleaseObj::~CGLibReleaseObj() { release(); }

void CGLibReleaseObj::release() {
    if (m_work.m_use) {
        s_callRelease[m_work.m_type](m_work);
        m_work = wrkRelease();
    }
}

CGLibBuffReleaseTbl::CGLibBuffReleaseTbl() : m_num(0), m_pTbl(nullptr), m_free(), m_stock() {}

void CGLibBuffReleaseTbl::release() {
    for (int i = 0; i < m_num; i++) {
        m_pTbl[i].release();
    }
    if (m_pTbl != nullptr) {
        mtl::MemManager::deallocate(m_pTbl, 0, false);
        m_pTbl = nullptr;
    }
    m_num = 0;
    m_stock[1] = List();
    m_stock[0] = List();
    m_free = List();
}

CGLibReleaseObj* CGLibBuffReleaseTbl::createObj() {
    CGLibReleaseObj* pObj = m_free.pop();
    m_stock[CGLibManager::s_nStkNowIdx].push(pObj);
    return pObj;
}

void CGLibBuffReleaseTbl::update() {
    List& list = m_stock[CGLibManager::s_nDblNowIdx];
    CGLibReleaseObj* pObj = list.m_pHead;
    if (pObj != nullptr) {
        do {
            CGLibReleaseObj* pNext = pObj->m_pNext;
            pObj->release();
            m_free.push(pObj);
            pObj = pNext;
        } while (pObj != nullptr);
        m_stock[CGLibManager::s_nDblNowIdx] = List();
    }
}

CGLibBuffMinUniform::CGLibBuffMinUniform() { release(); }

void CGLibBuffMinUniform::release() {
    m_pool.release();
    releaseTbl();
}

CGLibBuffMinUniform::~CGLibBuffMinUniform() {}

void CGLibBuffMinUniform::createUniform(unsigned int size, unsigned int elemSize) {
    release();
    setupFixTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hDefHandle, size / elemSize, elemSize, size, 0x1000);
    m_pool.setupBuffer(m_pBuff, size, 0x24);
}

CGLibVtlMemPool::CGLibVtlMemPool() {
    m_size = 0;
    m_pMem = nullptr;
    m_isOwner = false;
    m_offset = 0;
}

CGLibVtlMemPool::~CGLibVtlMemPool() { release(); }

void CGLibVtlMemPool::release() {
    if (m_isOwner) {
        nvnMemoryPoolFinalize(m_pPool);
        context::CGLibSystemContext::sys()->m_memPoolTbl.freeBuffer(m_pPool);
    }
    m_size = 0;
    m_pMem = nullptr;
    m_isOwner = false;
    m_offset = 0;
}

void CGLibVtlMemPool::setupBuffer(void* buffer, unsigned int size) {
    release();
    m_size = size;
    m_pMem = static_cast<unsigned char*>(buffer);
    m_offset = 0;
    CGLibMemPool* pPool = context::CGLibSystemContext::sys()->m_memPoolAdder.getMemPool(buffer);
    if (pPool == nullptr) {
        NVNdevice* pDevice = &CGLibManager::sys()->m_device;
        NVNmemoryPoolBuilder builder;
        nvnMemoryPoolBuilderSetDefaults(&builder);
        nvnMemoryPoolBuilderSetDevice(&builder, pDevice);
        nvnMemoryPoolBuilderSetFlags(&builder, 100);
        nvnMemoryPoolBuilderSetStorage(&builder, buffer, size);
        CGLibBuffMemPoolTbl& tbl = context::CGLibSystemContext::sys()->m_memPoolTbl;
        m_pPool = reinterpret_cast<NVNmemoryPool*>(tbl.getBuffer(tbl.allocID()));
        nvnMemoryPoolInitialize(m_pPool, &builder);
        m_gpuAddress = nvnMemoryPoolGetBufferAddress(m_pPool);
        m_isOwner = true;
    } else {
        nn::os::FlushDataCache(m_pMem, size);
        m_offset = reinterpret_cast<unsigned long>(buffer) - reinterpret_cast<unsigned long>(pPool->m_pBuffer);
        m_pPool = pPool->m_pPool;
        NVNbufferAddress address = nvnMemoryPoolGetBufferAddress(pPool->m_pPool);
        m_gpuAddress = m_offset + address;
        m_isOwner = false;
    }
}

void CGLibVtlMemPool::delayRelease() {
    if (m_isOwner) {
        context::CGLibSystemContext::sys()->releaseDelayMempool(m_pPool, nullptr);
    }
    m_size = 0;
    m_pMem = nullptr;
    m_isOwner = false;
    m_offset = 0;
}

void CGLibReleaseObj_plf::release_mempool(wrkRelease& work) {
    if (work.m_mempool) {
        nvnMemoryPoolFinalize(static_cast<NVNmemoryPool*>(work.m_res.m_obj.m_pObj));
        context::CGLibSystemContext::sys()->m_memPoolTbl.freeBuffer(work.m_res.m_obj.m_pObj);
    }
    if (work.m_res.m_obj.m_pBuff != nullptr) {
        mtl::MemManager::deallocate(work.m_res.m_obj.m_pBuff, 0, false);
        work.m_res.m_obj.m_pBuff = nullptr;
    }
}

void CGLibReleaseObj_plf::release_textrue(wrkRelease& work) {
    if (work.m_texture) {
        nvnTextureFinalize(static_cast<NVNtexture*>(work.m_res.m_obj.m_pObj));
        context::CGLibSystemContext::sys()->m_textureAlloc.freeBuffer(work.m_res.m_obj.m_pObj);
    }
    if (work.m_res.m_obj.m_pBuff != nullptr) {
        mtl::MemManager::deallocate(work.m_res.m_obj.m_pBuff, 0, false);
        work.m_res.m_obj.m_pBuff = nullptr;
    }
    if (work.m_textureID != -1) {
        context::CGLibSystemContext::sys()->m_texDescriptor.freeID(work.m_textureID);
    }
    if (work.m_samplerID != -1) {
        context::CGLibSystemContext::sys()->m_texDescriptor.freeID(work.m_samplerID);
    }
}

void CGLibReleaseObj_plf::release_vertex(wrkRelease& work) { CGLibMemHandle::free(work.m_res.m_mem); }

void (*CGLibReleaseObj_plf::s_callRelease[4])(wrkRelease& work) = {release_mempool, release_textrue, release_sampler,
                                                                   release_vertex};

CGLibCmdBuffer::CGLibCmdBuffer() : m_cmdUsed(0), m_ctrlUsed(0), m_init(false) {}

CGLibCmdBuffer::~CGLibCmdBuffer() { release(); }

void CGLibCmdBuffer::release() {
    if (m_init) {
        nvnCommandBufferFinalize(&m_cmdBuf);
        m_memPool.release();
    }
}

}  // namespace grlib

// Placeholder name: 1.0.0 leaves it unnamed too (fn_71007B29FC). A file static: CGLibCmdBuffer::setup installs it
// as the buffer's memory callback (callback data: the CGLibCmdBuffer). What it does: nothing for the two
// out-of-memory events (0, 1), NN_UNEXPECTED_DEFAULT for any other.
static void fn_71007084DC(NVNcommandBuffer*, NVNcommandBufferMemoryEvent event, size_t, void*) {
    switch (event) {
    case 0:
    case 1:
        break;
    default:
        nn::detail::UnexpectedDefaultImpl("", "", 0);
    }
}

namespace grlib {

void CGLibCmdBuffer::setup(unsigned int offset, unsigned int size, CGLibMemPool& pool, unsigned int ctrlSize) {
    release();
    nvnCommandBufferInitialize(&m_cmdBuf, &CGLibManager::sys()->m_device);
    m_pPool = &pool;
    m_offset = offset;
    m_cmdSize = size - ctrlSize;
    m_ctrlSize = ctrlSize;
    nvnCommandBufferSetMemoryCallback(&m_cmdBuf, fn_71007084DC);
    nvnCommandBufferSetMemoryCallbackData(&m_cmdBuf, this);
    m_init = true;
}

void CGLibCmdBuffer::begin() {
    nvnCommandBufferAddCommandMemory(&m_cmdBuf, m_pPool->m_pPool, m_offset + m_ctrlSize, m_cmdSize);
    nvnCommandBufferAddControlMemory(&m_cmdBuf, static_cast<unsigned char*>(m_pPool->m_pBuffer) + m_offset, m_ctrlSize);
    nvnCommandBufferBeginRecording(&m_cmdBuf);
    m_cmdUsed = 0;
    m_ctrlUsed = 0;
}

void CGLibCmdBuffer::end() {
    m_handle = nvnCommandBufferEndRecording(&m_cmdBuf);
    m_cmdUsed = nvnCommandBufferGetCommandMemoryUsed(&m_cmdBuf);
    m_ctrlUsed = nvnCommandBufferGetControlMemoryUsed(&m_cmdBuf);
}

void CGLibCmdBuffer::call() {
    if ((m_cmdUsed | m_ctrlUsed) != 0) {
        nvnCommandBufferCallCommands(context::CGLibSystemContext::sys()->m_pCmdBuf, 1, &m_handle);
    }
}

CGLibTexDescriptor::CGLibTexDescriptor() {}

CGLibTexDescriptor::~CGLibTexDescriptor() { release(); }

void CGLibTexDescriptor::release() {
    nvnTexturePoolFinalize(&m_texPool);
    m_pool.release();
    releaseTbl();
}

CGLibTexDescriptor_plf::~CGLibTexDescriptor_plf() {}

unsigned int CGLibTexDescriptor::setup(CGLibMemPool& pool, unsigned int offset, unsigned int num) {
    unsigned int size = context::CGLibSystemContext::s_nvTextureSize * num;
    nvnTexturePoolInitialize(&m_texPool, pool.m_pPool, offset, num);
    return size;
}

void CGLibTexDescriptor::bind() {
    nvnCommandBufferSetTexturePool(context::CGLibSystemContext::sys()->m_pipeline.m_pCmdBuf, &m_texPool);
}

void CGLibTexDescriptor_plf::bindTexture(const CGLibTextureBuffer& texture, int textureId, int imageId) {
    nvnTexturePoolRegisterTexture(&m_texPool, context::CGLibSystemContext::s_nNnumReservedTextures + textureId,
                                  texture.m_pNvnTexture, nullptr);
    if (imageId != -1) {
        nvnTexturePoolRegisterImage(&m_texPool, context::CGLibSystemContext::s_nNnumReservedTextures + imageId,
                                    texture.m_pNvnTexture, nullptr);
    }
}

int CGLibTexDescriptor_plf::setTexture(const CGLibTextureBuffer& texture) {
    return texture.m_textureId + context::CGLibSystemContext::s_nNnumReservedTextures;
}

int CGLibTexDescriptor_plf::setImage(const CGLibTextureBuffer& texture) {
    return texture.m_samplerId + context::CGLibSystemContext::s_nNnumReservedTextures;
}

CGLibSamplerDescriptor::CGLibSamplerDescriptor() {}

CGLibSamplerDescriptor::~CGLibSamplerDescriptor() { release(); }

void CGLibSamplerDescriptor::release() {
    nvnSamplerPoolFinalize(&m_samplerPool);
    m_pool.release();
    releaseTbl();
}

unsigned int CGLibSamplerDescriptor::setup(CGLibMemPool& pool, unsigned int offset, unsigned int num) {
    unsigned int size = context::CGLibSystemContext::s_nvSamplerSize * num;
    nvnSamplerPoolInitialize(&m_samplerPool, pool.m_pPool, offset, num);
    return size;
}

void CGLibSamplerDescriptor::bind() {
    nvnCommandBufferSetSamplerPool(context::CGLibSystemContext::sys()->m_pipeline.m_pCmdBuf, &m_samplerPool);
}

void CGLibSamplerDescriptor_plf::bindSampler(const CGLibSamplerParam& param, int samplerId) {
    nvnSamplerPoolRegisterSampler(&m_samplerPool, context::CGLibSystemContext::s_nNumReservedSamplers + samplerId,
                                  &param.m_sampler);
}

int CGLibSamplerDescriptor_plf::setSampler(const CGLibSampler& sampler) {
    return context::CGLibSystemContext::s_nNumReservedSamplers + sampler.m_pSamObj->m_param.m_samplerId;
}


}  // namespace grlib

// The graphics driver's allocator callbacks (CGLibDeviceObj::init hands them over): the C library's heap.
// Placeholder names: static functions, the symbols leave them unnamed.
static void* fn_7100708CBC(size_t size, size_t alignment, void*) { return aligned_alloc(alignment, size); }

static void fn_7100708CCC(void* addr, void*) { free(addr); }

static void* fn_7100708CD0(void* addr, size_t newSize, void*) { return realloc(addr, newSize); }

// the same three for the driver's developer tools
static void* fn_7100708CD4(size_t size, size_t alignment, void*) { return aligned_alloc(alignment, size); }

static void fn_7100708CE4(void* addr, void*) { free(addr); }

static void* fn_7100708CE8(void* addr, size_t newSize, void*) { return realloc(addr, newSize); }

namespace grlib {
CGLibDeviceObj::CGLibDeviceObj() {}

bool CGLibDeviceObj::init() {
    nv::SetGraphicsAllocator(fn_7100708CBC, fn_7100708CCC, fn_7100708CD0, nullptr);
    nv::SetGraphicsDevtoolsAllocator(fn_7100708CD4, fn_7100708CE4, fn_7100708CE8, nullptr);
    nv::InitializeGraphics(malloc(0x800000), 0x800000);
    m_vi.init();
    PFNNVNDEVICEGETPROCADDRESSPROC getProcAddress =
        reinterpret_cast<PFNNVNDEVICEGETPROCADDRESSPROC>(nvnBootstrapLoader("nvnDeviceGetProcAddress"));
    nvnLoadCProcs(nullptr, getProcAddress);
    {
        NVNdeviceBuilder builder;
        nvnDeviceBuilderSetDefaults(&builder);
        nvnDeviceBuilderSetFlags(&builder, 0);
        nvnDeviceInitialize(&m_device, &builder);
    }
    nvnLoadCProcs(&m_device, getProcAddress);
    int majorVersion;
    int minorVersion;
    nvnDeviceGetInteger(&m_device, static_cast<NVNdeviceInfo>(0), &majorVersion);
    nvnDeviceGetInteger(&m_device, static_cast<NVNdeviceInfo>(1), &minorVersion);
    NVNqueueBuilder builder;
    nvnQueueBuilderSetDevice(&builder, &m_device);
    nvnQueueBuilderSetDefaults(&builder);
    majorVersion = 0;
    nvnDeviceGetInteger(&m_device, static_cast<NVNdeviceInfo>(0x51), &majorVersion);
    majorVersion *= 2;
    nvnQueueBuilderSetCommandMemorySize(&builder, majorVersion);
    nvnQueueBuilderSetCommandFlushThreshold(&builder, majorVersion);
    if (!nvnQueueInitialize(&m_queue, &builder)) {
        return false;
    }
    nvnDeviceSetDepthMode(&m_device, static_cast<NVNdepthMode>(0));
    nvnDeviceSetWindowOriginMode(&m_device, static_cast<NVNwindowOriginMode>(1));
    return true;
}

void CGLibDeviceVI::init() {
    m_width = 1280;
    m_height = 720;
    nn::vi::Initialize();
    nn::vi::OpenDefaultDisplay(&m_display);
    NN_ASSERT(nn::vi::CreateLayer(&m_layer, m_display).IsSuccess());
    nn::vi::SetLayerScalingMode(m_layer, static_cast<nn::vi::ScalingMode>(2));
    NN_ASSERT(nn::vi::GetNativeWindow(&m_nativeWindow, m_layer).IsSuccess());
}

void CGLibDeviceObj::release() {
    nvnQueueFinalize(&m_queue);
    nvnDeviceFinalize(&m_device);
    nn::vi::DestroyLayer(m_vi.m_layer);
    nn::vi::CloseDisplay(m_vi.m_display);
    nn::vi::Finalize();
}

void CGLibDeviceObj::swapChain() { context::CGLibSystemContext::sys()->m_display.swapChain(&m_queue); }

CGLibDeviceVI::~CGLibDeviceVI() {}

}  // namespace grlib


namespace ml {
ScnObjAccResMdlInfo::ScnObjAccResMdlInfo(ScnObjModel* model) {
    m_drMdl = nullptr;
    m_drMdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
}

int ScnObjAccResMdlInfo::isGpuRender() const { return m_drMdl->isGpuRender(); }

void ScnObjAccResMdlInfo::setAlwaysMiddleTexStm(bool on) { m_drMdl->setAlwaysMiddleTexStm(on); }

void ScnObjAccResMdlInfo::setGpuClip(bool on) { m_drMdl->setGpuClip(on); }

void ScnObjAccResMdlInfo::setAlwaysTexStm(bool on) { m_drMdl->setAlwaysTexStm(on); }

void ScnObjAccResMdlInfo::setDblBuffAlpha(bool on) { m_drMdl->setDblBuffAlpha(on); }

void ScnObjAccResMdlInfo::setSpAlphaMode(bool on) { m_drMdl->setSpAlphaMode(on); }

void ScnObjAccResMdlInfo::setCamCheckMode(bool on) { m_drMdl->setCamCheckMode(on); }

bool ScnObjAccResMdlInfo::isCamCheckResl() const { return m_drMdl->isCamCheckResl(); }

void ScnObjAccResMdlInfo::createAfterImage(const DrMdlAfterImageParams& params) {
    if (m_drMdl->m_mdlType != 0) {
        return;
    }
    static_cast<DrMdoCtlNom*>(m_drMdl)->createAfterImage(
        params.m_params0[0], params.m_params0[1], params.m_params0[2], params.m_color0, params.m_params1[0],
        params.m_params1[1], params.m_params1[2], params.m_color1, params.m_params2[0], params.m_params2[1],
        params.m_params2[2]);
}

void ScnObjAccResMdlInfo::releaseAfterImage() {
    if (m_drMdl->m_mdlType != 0) {
        return;
    }
    static_cast<DrMdoCtlNom*>(m_drMdl)->releaseAfterImage();
}

ScnObjAccResNode::ScnObjAccResNode() : m_drMdl(nullptr) {}

ScnObjAccResNode::ScnObjAccResNode(ScnObjModel* model) : m_drMdl(static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj) {}

void ScnObjAccResNode::setDrMdl(DrMdlObj* mdl) { m_drMdl = mdl; }

int ScnObjAccResNode::getBoneMax() const { return m_drMdl->getNodeMax(); }

int ScnObjAccResNode::getBoneIndex(const char* name) const { return m_drMdl->getNodeIdx(name); }

const char* ScnObjAccResNode::getBoneName(int index) const {
    if (index < 0) {
        return nullptr;
    }
    return m_drMdl->getNodeName(index);
}

void ScnObjAccResNode::setBoneMat(int index, const mm::Mat44& mat) { m_drMdl->setResBoneMat(index, mat); }

const mm::Mat44& ScnObjAccResNode::getBoneMat(int index) const { return m_drMdl->getResBoneMat(index); }

mm::Mat44* ScnObjAccResNode::getBoneMatPtr(int index) { return m_drMdl->getResBoneMatPtr(index); }

ScnObjAccEtcParams::ScnObjAccEtcParams(ScnObjModel* model) {
    DrMdlObj* mdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
    if (mdl->m_mdlType != 0) {
        m_table = nullptr;
    } else {
        m_table = static_cast<DrMdoCtlNom*>(mdl)->m_etcParams;
    }
}

unsigned int ScnObjAccEtcParams::getMax() const {
    if (m_table == nullptr) {
        return 0;
    }
    return m_table->m_paramNum;
}

const char* ScnObjAccEtcParams::getName(unsigned int index) const {
    if (m_table == nullptr) {
        return nullptr;
    }
    if (index >= m_table->m_paramNum) {
        return nullptr;
    }
    return reinterpret_cast<const char*>(m_table->m_pams) +
           static_cast<const DrResEtcPamObj::ParamName*>(m_table->m_data)[index].m_nameOfs;
}

int ScnObjAccEtcParams::getIndex(const char* name) const {
    if (m_table != nullptr) {
        for (unsigned long i = 0; i < m_table->m_paramNum; i++) {
            if (strcmp(name, reinterpret_cast<const char*>(m_table->m_pams) +
                                 static_cast<const DrResEtcPamObj::ParamName*>(m_table->m_data)[i].m_nameOfs) == 0) {
                return i;
            }
        }
    }
    return -1;
}

void ScnObjAccEtcParams::setParams(unsigned int index, float value) {
    if (m_table != nullptr && index < m_table->m_paramNum) {
        m_table->m_params[index].setParams(value);
    }
}

void ScnObjAccEtcParams::setPreParams(unsigned int index, float value) {
    if (m_table != nullptr && index < m_table->m_paramNum) {
        m_table->m_params[index].setPreParams(value);
    }
}

void ScnObjAccEtcParams::setInitParams(unsigned int index, float value) {
    if (m_table != nullptr && index < m_table->m_paramNum) {
        m_table->m_params[index].setInitParams(value);
    }
}

void ScnObjAccEtcParams::setRimBloom(bool on) {
    if (m_table != nullptr) {
        m_table->m_flags = !on ? (m_table->m_flags & ~1) : (m_table->m_flags | 1);
    }
}

ScnObjAccResSubMesh::ScnObjAccResSubMesh(ScnObjModel* model) {
    m_mesh = nullptr;
    DrMdlObj* mdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
    if (mdl->m_mdlType == 0 && mdl->m_pWrkMatRes != nullptr) {
        MdoWrkMatRes* res = mdl->m_pWrkMatRes;
        m_mesh = static_cast<DrMdoCtlNom*>(mdl)->m_mesh;
        const MdoMdlData* data = res->m_pMdlData;
        m_subMesh = reinterpret_cast<const char*>(data) + data->m_subMeshOfs;
    }
}

int ScnObjAccResSubMesh::getExtMax() const {
    if (m_mesh == nullptr) {
        return 0;
    }
    return m_mesh->m_num;
}

int ScnObjAccResSubMesh::getExtIdx(const char* name) const {
    if (m_mesh == nullptr) {
        return -1;
    }
    return m_mesh->getIdx(name);
}

const char* ScnObjAccResSubMesh::getExtName(int index) const {
    DrResMdoMeshParts* parts = m_mesh->m_parts;
    return parts[static_cast<unsigned int>(index)].m_name;
}

void ScnObjAccResSubMesh::setExtAlpha(int index, float alpha) {
    DrResMdoMeshParts* parts = m_mesh->m_parts;
    parts[static_cast<unsigned int>(index)].setDefAlpha(alpha);
}

ScnObjAccVolumeFade::ScnObjAccVolumeFade(ScnObjModel* model) : m_material(static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj) {}

ScnObjAccVolumeFade::~ScnObjAccVolumeFade() {}

int ScnObjAccVolumeFade::getMax() const {
    if (m_material == nullptr) {
        return 0;
    }
    return m_material->getVanishEffectMax();
}

void ScnObjAccVolumeFade::setRatio(float ratio, int index) {
    if (m_material == nullptr) {
        return;
    }
    if (index >= 0) {
        MdoVanishEffectWrk* wrk = m_material->getVanishEffectWrk(index, DrMan::s_nDblIdx);
        if (wrk != nullptr) {
            wrk->m_ratio = ratio;
            wrk->m_flags |= 0x100;
        }
    } else {
        for (unsigned int i = 0; i < m_material->getVanishEffectMax(); i++) {
            MdoVanishEffectWrk* wrk = m_material->getVanishEffectWrk(i, DrMan::s_nDblIdx);
            wrk->m_ratio = ratio;
            wrk->m_flags |= 0x100;
        }
    }
}

float ScnObjAccVolumeFade::getRatio(unsigned int index) const {
    float ratio = 0.0f;
    if (m_material != nullptr) {
        MdoVanishEffectWrk* base = m_material->getVanishEffectWrk(index, 2);
        if (base != nullptr) {
            MdoVanishEffectWrk* wrk = m_material->getVanishEffectWrk(index, DrMan::s_nDblIdx);
            if (!(wrk->m_flags & 0x100)) {
                wrk = m_material->getVanishEffectWrk(index, DrMan::s_nDblStockIdx);
                if (!(wrk->m_flags & 0x100)) {
                    return base->m_ratio;
                }
            }
            ratio = wrk->m_ratio;
        }
    }
    return ratio;
}

ScnObjAccRimBloom::ScnObjAccRimBloom(ScnObjModel* model) : m_drMdl(static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj) {}

ScnObjAccRimBloom::~ScnObjAccRimBloom() {}

void ScnObjAccRimBloom::setRimColor(const mm::Col3& color) {
    if (m_drMdl != nullptr) {
        MdoRimBloomWrk* wrk = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
        if (wrk != nullptr) {
            wrk->m_color = color;
            wrk->m_flags |= 1;
        }
    }
}

void ScnObjAccRimBloom::setRimEmissive(float emissive) {
    if (m_drMdl != nullptr) {
        MdoRimBloomWrk* wrk = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
        if (wrk != nullptr) {
            wrk->m_emissive = emissive;
            wrk->m_flags |= 8;
        }
    }
}

void ScnObjAccRimBloom::setRimPower(float power) {
    if (m_drMdl != nullptr) {
        MdoRimBloomWrk* wrk = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
        if (wrk != nullptr) {
            wrk->m_power = power;
            wrk->m_flags |= 2;
        }
    }
}

void ScnObjAccRimBloom::setBlackRatio(float ratio) {
    if (m_drMdl != nullptr) {
        MdoRimBloomWrk* wrk = m_drMdl->getRimBloomWrk(DrMan::s_nDblIdx);
        if (wrk != nullptr) {
            wrk->m_blackRatio = ratio;
            wrk->m_flags |= 4;
        }
    }
}

ScnObjAccMdlParticle::ScnObjAccMdlParticle(ScnObjModel* model) {
    DrMdlObj* mdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
    if (mdl->m_mdlType != 0) {
        m_vtxMesh = nullptr;
    } else {
        m_vtxMesh = static_cast<DrMdoCtlNom*>(mdl)->m_vtxMesh;
    }
}

void ScnObjAccMdlParticle::setActive(bool active, unsigned int index) {
    if (m_vtxMesh != nullptr) {
        m_vtxMesh->setActive(active, index);
    }
}
ScnObjAccSeamPos::ScnObjAccSeamPos(ScnObjModel* model) : m_anm(nullptr) {
    DrMdlObj* mdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
    if (mdl->m_mdlType == 3) {
        m_anm = &static_cast<DrMdoCtlSeam*>(mdl)->m_instAnm;
    } else if (mdl->m_mdlType == 1) {
        m_anm = &static_cast<DrMdoCtlPos*>(mdl)->m_instAnm;
    } else {
        m_anm = nullptr;
    }
}

unsigned int ScnObjAccSeamPos::getMax() const {
    if (m_anm == nullptr) {
        return 0;
    }
    if (m_anm->m_header == nullptr) {
        return 0;
    }
    return m_anm->m_header->partsMax;
}

ScnObjAccPartsPos ScnObjAccSeamPos::getObj(unsigned int index) {
    if (m_anm == nullptr) {
        return ScnObjAccPartsPos(nullptr);
    }
    DrResMdoInstPartsObj* obj;
    if (m_anm->m_header == nullptr) {
        obj = nullptr;
    } else {
        obj = m_anm->m_parts[index];
    }
    return ScnObjAccPartsPos(obj);
}

void ScnObjAccPartsPos::setMatrix(const mm::Mat44& mat) { m_obj->setMatrix(mat); }
void ScnObjAccPartsPos::getMatrix(mm::Mat44& mat) { m_obj->getMatrix(mat); }
const char* ScnObjAccPartsPos::getName() const { return m_obj->m_names + m_obj->m_info->nameOfs; }
unsigned int ScnObjAccPartsPos::getID() const { return m_obj->m_info->id; }
bool ScnObjAccPartsPos::isPosAnm() const { return (m_obj->m_info->flags >> 4) & 1; }
bool ScnObjAccPartsPos::isNodeAnm() const { return (m_obj->m_info->flags >> 3) & 1; }
bool ScnObjAccPartsPos::isPosMatrix() const { return (m_obj->m_info->flags & 0x30) != 0; }
bool ScnObjAccPartsPos::isRandomStart() const { return (m_obj->m_info->flags >> 1) & 1; }
bool ScnObjAccPartsPos::isSwitch() const { return (m_obj->m_info->flags >> 7) & 1; }
bool ScnObjAccPartsPos::isColiOff() const { return (m_obj->m_flags >> 3) & 1; }
bool ScnObjAccPartsPos::isColiSkipData() const { return (m_obj->m_flags >> 4) & 1; }
void ScnObjAccPartsPos::setAlpha(float alpha) { m_obj->m_alpha = alpha; }
bool ScnObjAccPartsPos::isLoop() const { return (m_obj->m_flags >> 2) & 1; }
void ScnObjAccPartsPos::setPosFrame(float frame) { m_obj->setPosFrame(frame); }
float ScnObjAccPartsPos::getPosFrame() const { return m_obj->getPosFrame(); }
float ScnObjAccPartsPos::getPosMaxFrame() const { return m_obj->getPosMaxFrame(); }
float ScnObjAccPartsPos::getPosStartFrame() const { return m_obj->getPosStartFrame(); }
void ScnObjAccPartsPos::setNodeFrame(float frame) { m_obj->setNodeFrame(frame); }
float ScnObjAccPartsPos::getNodeFrame() const { return m_obj->getNodeFrame(); }
float ScnObjAccPartsPos::getNodeMaxFrame() const { return m_obj->getNodeMaxFrame(); }
float ScnObjAccPartsPos::getNodeStartFrame() const { return m_obj->getNodeStartFrame(); }
void ScnObjAccPartsPos::getAnmMatrix(mm::Mat44* mat) const { m_obj->getAnmMatrix(*mat); }
unsigned char ScnObjAccPartsPos::getSwitchID() const { return m_obj->getSwitchID(); }
void ScnObjAccPartsPos::setSwitchID(unsigned int id) { m_obj->setSwitchID(id); }

ScnObjAccSeamEtcPos::ScnObjAccSeamEtcPos(ScnObjModel* model) : m_list(nullptr) {
    DrMdlObj* mdl = static_cast<ScnObjModelDrSys*>(model)->m_pMdlObj;
    if (mdl->m_mdlType != 3) {
        m_list = nullptr;
    } else {
        m_list = &static_cast<DrMdoCtlSeam*>(mdl)->m_etcPos;
    }
}

unsigned int ScnObjAccSeamEtcPos::getObjMax() const {
    if (m_list == nullptr) {
        return 0;
    }
    return m_list->m_max;
}

ScnObjAccPartsEtcPos ScnObjAccSeamEtcPos::getObj(unsigned int index) {
    return ScnObjAccPartsEtcPos(&m_list->m_entries[index]);
}

const char* ScnObjAccPartsEtcPos::getObjName() const {
    const DrMdoCtlSeam::EtcPos::Data* data = m_entry->m_data;
    return reinterpret_cast<const char*>(data) + data->objNameOfs;
}
const char* ScnObjAccPartsEtcPos::getEffName() const {
    const DrMdoCtlSeam::EtcPos::Data* data = m_entry->m_data;
    return reinterpret_cast<const char*>(data) + data->effNameOfs;
}
float ScnObjAccPartsEtcPos::getRange() const { return m_entry->m_data->range; }
float ScnObjAccPartsEtcPos::getNearClip(unsigned int index) const { return m_entry->m_data->nearClip[index]; }
float ScnObjAccPartsEtcPos::getFarClip(unsigned int index) const { return m_entry->m_data->farClip[index]; }
unsigned int ScnObjAccPartsEtcPos::getMatrixMax() const { return m_entry->m_data->matrixMax; }
const mm::Mat44& ScnObjAccPartsEtcPos::getMatrix(unsigned int index) const {
    const DrMdoCtlSeam::EtcPos::Data* data = m_entry->m_data;
    const mm::Mat44* mats = reinterpret_cast<const mm::Mat44*>(reinterpret_cast<const char*>(data) + data->matrixOfs);
    return mats[index];
}
bool ScnObjAccPartsEtcPos::isDisp(unsigned int index) const {
    if (m_entry->m_dispOn) {
        return true;
    }
    const DrMdoCtlSeam::EtcPos::Data* data = m_entry->m_data;
    unsigned short dispIdx =
        reinterpret_cast<const unsigned short*>(reinterpret_cast<const char*>(data) + data->dispIdxOfs)[index];
    if (dispIdx != 0 && (DrMan::getIns()->m_dispOffBits[dispIdx >> 5] & (1 << (dispIdx & 0x1F))) != 0) {
        return false;
    }
    return true;
}

ScnObjAccGpuCheck::ScnObjAccGpuCheck(DrGpuCheckBase* check) : m_check(check) {}

void ScnObjAccGpuCheck::setPos(const mm::Vec3& pos, float radius) { m_check->setPos(pos, radius); }

bool ScnObjAccGpuCheck::isRender() const { return m_check->isRender(); }

DrGpuCheckBase* ScnObjAccGpuCheck::create(unsigned int arg) {
    DrCreator creator;
    return creator.createGpuCheckObj(arg);
}

ScnObjAccStmReadObj::ScnObjAccStmReadObj(DrStmReadObj* obj) : m_obj(obj) {}

void ScnObjAccStmReadObj::readType(ReadType type) {
    switch (type) {
    case READ_TYPE_0:
        m_obj->m_readType = 0;
        break;
    case READ_TYPE_1:
        m_obj->m_readType = 1;
        break;
    case READ_TYPE_2:
        m_obj->m_readType = 2;
        break;
    }
}

DrStmReadCheck* ScnObjAccStmReadObj::create(const char* name) {
    DrCreator creator;
    return creator.createStmLoadObj(name);
}


void ScnRenderDrSys::setDefaultEvn() {}

void ScnRenderDrSys::applyCamera(ml::ScnObjCam*) {}

void ScnRenderDrSys::update() {}

void ScnRenderDrSys::setup(const ml::ScnSetup*) {}

ScnRenderDrSys::~ScnRenderDrSys() {
    if (m_drMan != nullptr) {
        delete m_drMan;
        m_drMan = nullptr;
    }
}

void ScnRenderDrSys::applyBegin() { m_drMan->begin(); }

void ScnRenderDrSys::applyEnd() { m_drMan->end(); }

bool ScnRenderDrSys::applyLoopCnt() { return m_drMan->loopCnt(); }

void ScnRenderDrSys::applyUpdate(int arg) { m_drMan->apply(arg); }

void ScnRenderDrSys::applyRender(int arg) { m_drMan->render(arg); }

void ScnRenderDrSys::tail() { m_drMan->tail(); }

void ScnRenderDrSys::setMdlDblPause(bool pause) { m_drMan->m_mdlDblPause = pause; }

void ScnRenderDrSys::setGlbSpd(float speed) { m_drMan->m_glbSpd = speed; }

void ScnRenderDrSys::setCallBack(IDrDrawCallback* callback) { m_drMan->setCallBack(callback); }

void ScnRenderDrSys::releaseCallBack(IDrDrawCallback* callback) { m_drMan->releaseCallBack(callback); }

void ScnRenderDrSys::openPixelDebugWindow(WinProc* proc) { m_drMan->openPixelDebugWindow(proc); }

void ScnRenderDrSys::openHisgtramDebugWindow(WinProc* proc) { m_drMan->openHistgramDebugWindow(proc); }

ScnObjModel* ScnRenderDrSys::createMdl(Scn* scn, const void* res, const char* name, int view) {
    if (res == nullptr) {
        return nullptr;
    }
    return ScnObjModelDrSysStandard::create(scn, res, name, view);
}

ScnObj* ScnRenderDrSys::createLgt(Scn* scn, const void* res, int view) { return ScnObjLightDrSys::create(scn, res, view); }

void ScnRenderDrSys::createClip(Scn* scn, const void* res, int view) { ScnObjClipDySys::create(scn, res, view); }

ScnObjIBL* ScnRenderDrSys::createIBL(Scn* scn, const void* res, int view) { return ScnObjIBLDr::create(scn, res, view); }

void ScnRenderDrSys::createEnvColi(Scn* scn, const void* res, int view) { ScnObjEnvColiDr::create(scn, res, view); }

inline ScnRenderDrSys::ScnRenderDrSys(Scn* scn) : ScnRender(scn) {
    m_drMan = new (scn->m_allocHandle, nullptr, 0, 4, false) DrMan(scn);
}

void ScnRenderDrSys::createDrRender(Scn* scn) {
    WorkCpu::runThread(WorkCpu::getRenderCPUID(), thDrSysInitialize, scn, nullptr, nullptr, true,
                       static_cast<WKCPU_SYNC>(1));
}

unsigned int ScnRenderDrSys::thDrSysInitialize(void* arg, void*) {
    Scn* scn = static_cast<Scn*>(arg);
    if (scn->m_renderDrSys == nullptr) {
        scn->m_renderDrSys = new (scn->m_allocHandle, nullptr, 0, 4, false) ScnRenderDrSys(scn);
    }
    return 0;
}

ScnRenderDrEnvColi::ScnRenderDrEnvColi(int view) { m_envColi = DrMan::getIns()->m_envMan[view]->m_envColiMan; }

ScnRenderDrEnvColi::~ScnRenderDrEnvColi() {}

bool ScnRenderDrEnvColi::testEnvColi(const mm::Vec3& pos, float range) {
    return m_envColi->testEnvColi(nullptr, pos, range);
}

int ScnRenderDrEnvColi::getWindId() const { return m_envColi->m_result.m_windId; }

bool ScnRenderDrEnvColi::isRoom() const { return (m_envColi->m_result.m_flags >> 2) & 1; }

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc() : m_drMan(nullptr), m_postParm(nullptr), m_view(0) {
    m_drMan = DrMan::get();
    m_postParm = m_drMan->m_postParm[m_view];
}

ScnRenderDrSysParmAcc::ScnRenderDrSysParmAcc(ScnRenderDrSys* render, int view)
    : m_drMan(nullptr), m_postParm(nullptr) {
    m_drMan = render->m_drMan;
    m_postParm = m_drMan->m_postParm[view];
    m_view = view;
}

void ScnRenderDrSysParmAcc::setDOFOverride(bool enable) { m_postParm->setOverrideDOF(enable); }

void ScnRenderDrSysParmAcc::setToneMap(bool enable) { m_postParm->m_toneMap = enable; }

void ScnRenderDrSysParmAcc::setOverrideToneMap(float value) { m_postParm->setOverrideToneMap(value); }

void ScnRenderDrSysParmAcc::setMotBlurOverride(bool enable) { m_postParm->setOverrideMotBlur(enable); }

void ScnRenderDrSysParmAcc::setMotBlur(bool enable) { m_postParm->m_motBlur = enable; }

void ScnRenderDrSysParmAcc::setMotBlurDefault(bool enable) { m_drMan->m_iniSys->m_motBlurDefault = enable; }

void ScnRenderDrSysParmAcc::setDOF(bool enable) { m_postParm->setDOF(enable); }

bool ScnRenderDrSysParmAcc::isDOF() const { return m_postParm->m_dofOverride || m_postParm->m_dof; }

void ScnRenderDrSysParmAcc::setDoFPixlRatio(float ratio) { m_postParm->setDoFPixlRatio(ratio); }

void ScnRenderDrSysParmAcc::setDoFDistance(float distance) { m_postParm->setDoFDistance(distance); }

void ScnRenderDrSysParmAcc::setDoFRange(float range) { m_postParm->setDoFRange(range); }

void ScnRenderDrSysParmAcc::setDoFStrength(float strength) { m_postParm->setDoFStrength(strength); }

void ScnRenderDrSysParmAcc::setDoFLens(float lens) { m_postParm->setDoFLens(lens); }

void ScnRenderDrSysParmAcc::setDoFBlend(float blend) { m_postParm->setDoFBlend(blend); }

void ScnRenderDrSysParmAcc::setDofHLvMode(bool enable) { m_postParm->setDOFHlv(enable); }

void ScnRenderDrSysParmAcc::setDofPixlLv(int level) {
    DrPixlPostParm* postParm = m_postParm;
    if (level < 0 || level >= 3) {
        postParm->setDoFPixlLv(0);
        return;
    }
    postParm->setDoFPixlLv(level);
}

void ScnRenderDrSysParmAcc::setDOFAutoFocus(bool enable) { m_postParm->setDOFAutoFocus(enable); }

void ScnRenderDrSysParmAcc::setDOFFocusNum(int num) {
    if (num > 11U) {
        num = 0;
    }
    m_postParm->setDoFocusNum(num);
}

void ScnRenderDrSysParmAcc::setDOFFocusMin(float min) { m_postParm->setDofFocusMin(min); }

float ScnRenderDrSysParmAcc::getDoFPixlRatio() const { return m_postParm->m_dofPixlRatio; }

float ScnRenderDrSysParmAcc::getDoFDistance() const { return m_postParm->m_dofDistance; }

float ScnRenderDrSysParmAcc::getDoFRange() const { return m_postParm->m_dofRange; }

float ScnRenderDrSysParmAcc::getDoFStrength() const { return m_postParm->m_dofStrength; }

float ScnRenderDrSysParmAcc::getDoFLens() const { return m_postParm->m_dofLens; }

float ScnRenderDrSysParmAcc::getDoFBlend() const { return m_postParm->m_dofBlend; }

bool ScnRenderDrSysParmAcc::isDofHLvMode() const { return m_postParm->m_dofHLvMode; }

int ScnRenderDrSysParmAcc::getDofPixlLv() const { return m_postParm->m_dofPixlLv; }

bool ScnRenderDrSysParmAcc::isDOFAutoFocus() const { return m_postParm->m_dofAutoFocus; }

int ScnRenderDrSysParmAcc::getDOFFocusNum() const { return m_postParm->m_dofFocusNum; }

float ScnRenderDrSysParmAcc::getDOFFocusMin() const { return m_postParm->m_dofFocusMin; }

void ScnRenderDrSysParmAcc::setPlaneCloudNum(unsigned int num) {
    cloud::CloudMan* cloudMan = DrMan::getIns()->m_cloudMan;
    if (cloudMan != nullptr) {
        cloudMan->setCldNum(num);
    }
}

void ScnRenderDrSysParmAcc::setGlobalWind(const mm::Vec3& power) { m_drMan->setGlobalWind(power); }

void ScnRenderDrSysParmAcc::setAutoReduction(bool enable) { m_drMan->setAutoReduction(enable); }

void ScnRenderDrSysParmAcc::setColorFilterOverride(bool enable) { m_postParm->setOverrideColorFilter(enable); }

void ScnRenderDrSysParmAcc::setColorFilterNum(int num) { m_postParm->setColorFilterNum(num); }

void ScnRenderDrSysParmAcc::setColorFilterFarNum(int num) { m_postParm->setColorFilterFarNum(num); }

void ScnRenderDrSysParmAcc::setColorFilterFrm(float frame) { m_postParm->setColorFilterFrm(frame); }

void ScnRenderDrSysParmAcc::setRainDrop(bool enable) { m_postParm->m_rainDrop = enable; }

void ScnRenderDrSysParmAcc::setTimeVal(float time) { m_drMan->setTimeVal(time); }

void ScnRenderDrSysParmAcc::setWeather(int weather) { m_postParm->m_weather = weather; }

void ScnRenderDrSysParmAcc::setWeatherFrame(float frame) { m_postParm->setWeatherFrame(frame); }

void ScnRenderDrSysParmAcc::getWeatherFrame() const { m_drMan->weatherFrmEnd(); }

void ScnRenderDrSysParmAcc::setSeamMapAddPosMode(bool enable) { m_drMan->m_seamMapAddPosMode = enable; }

void ScnRenderDrSysParmAcc::setSeamMapReadPos(const mm::Vec3& pos) {
    m_drMan->m_seamMapReadPos = pos;
}

void ScnRenderDrSysParmAcc::setSelectIdDisp(int index, bool off) {
    if (off) {
        m_drMan->offGblIdx(index);
    } else {
        m_drMan->setGblIdx(index);
    }
}

bool ScnRenderDrSysParmAcc::isMdlAllMiddleTexStm() const { return m_drMan->isAllMiddelTexStmChk(); }

bool ScnRenderDrSysParmAcc::isSeamMapRead() const { return m_drMan->isSeamMapStmOk(); }

bool ScnRenderDrSysParmAcc::fn_710070A0DC() { return m_drMan->fn_710071E77C(); }

void ScnRenderDrSysParmAcc::setToonDirLightScale(bool enable) { m_drMan->m_toonDirLightScale = enable; }

void ScnRenderDrSysParmAcc::setToonAmbient(bool enable) {
    if (enable) {
        m_drMan->m_toonAmbient = 3;
    } else {
        m_drMan->m_toonAmbient = 0;
    }
}

void ScnRenderDrSysParmAcc::setPlayerPos(const mm::Vec3& pos) {}

void ScnRenderDrSysParmAcc::setCameraLight(bool enable) { m_drMan->m_cameraLight = enable; }

void ScnRenderDrSysParmAcc::createAddRenderView(ScnRenderDrViewCtrl* view) {
    DR_VIEW_PARAM param;
    param.m_width = view->m_width;
    param.m_height = view->m_height;
    param.m_viewNo = view->m_viewIndex + 1;
    param.m_clear = view->m_clear;
    param.m_flagA = view->m_flagA;
    param.m_flagB = view->m_flagB;
    param.m_texture = &view->m_texture;
    param.m_isReady = &view->m_isReady;
    param.m_color = view->m_color;
    param.m_scaleX = &view->m_scaleX;
    param.m_scaleY = &view->m_scaleY;
    m_drMan->createAddRenderSystem(&param);
}

void ScnRenderDrSysParmAcc::deleteAddRenderView(ScnRenderDrViewCtrl* view) {
    m_drMan->deleteAddRenderSystem(view->m_viewIndex + 1);
}

void ScnRenderDrSysParmAcc::setModelTexture(const ScnRenderDrMdlTexture& texture) {
    DR_MODEL_TEXTURE modelTexture;
    modelTexture.m_texture = texture.m_texture;
    modelTexture.m_enable = texture.m_enable;
    m_drMan->setModelTexture(&modelTexture, texture.m_slot);
}

void ScnRenderDrSysParmAcc::resetModelTexture(unsigned int slot) { m_drMan->resetModelTexture(slot); }

void ScnRenderDrSysParmAcc::setGlassBr(bool enable, unsigned int arg) { m_postParm->setGlassBrk(enable, arg); }

bool ScnRenderDrSysParmAcc::isGlassBr() { return m_postParm->m_glassBr; }

void ScnRenderDrSysParmAcc::setViewRenderSkip(unsigned int view, bool skip) {
    DrMan* drMan = DrMan::get();
    if (skip) {
        drMan->m_viewRenderSkip |= 1 << view;
    } else {
        drMan->m_viewRenderSkip &= ~(1 << view);
    }
}

void ScnRenderDrSysParmAcc::resetScene() { m_postParm->resetScene(); }

void ScnRenderDrSysParmAcc::setAutoResetScene(bool enable) { DrMan::get()->m_autoResetScene = enable; }

void ScnRenderDrSysParmAcc::setGamma(float gamma) { DrMan::get()->m_gamma = gamma; }

void ScnRenderDrSysParmAcc::setCaptureMode(bool enable) {
    DrMan* drMan = DrMan::get();
    if (enable) {
        drMan->m_captureMode[DrMan::s_nDblStockIdx] = 1;
    } else {
        drMan->m_captureMode[DrMan::s_nDblStockIdx] = 2;
    }
}

void ScnRenderDrSysParmAcc::setRenderTexMode(bool flag) {
    DrMan* drMan = DrMan::get();
    drMan->m_commonFlag = flag;
}

}  // namespace ml
