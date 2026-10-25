#include "grlib/CGLibTextureBuffer.h"
#include "grlib/CGLibUtilPixel.h"
#include "grlib/CGLibAccUtilTexture.h"
#include "grlib/CGLibAcc2DTexture.h"
#include "classes/grlib/CGLibUniformEtcUtility.h"
#include "grlib/CGLibEtcUniformBlock.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibOneUniformBlock.h"
#include "grlib/CGLibTriUniformBlock.h"
#include "classes/grlib/CGLibManager.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "mm/Vec4.h"
#include "classes/grlib/context/CGLibSystemContext.h"
#include "nvn/nvn_FuncPtrInline.h"
#include <string.h>
#include "nn/os.h"
#include "grlib/CGLibSampler.h"
#include "grlib/CGLibBuffSamplerTbl.h"
#include "grlib/CGLibBuffFixAlloc.h"
#include "grlib/CGLibPixlCounter.h"
#include "grlib/CGLibOcclusionQuery.h"
#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibCtl.h"
#include "grlib/CGLibTexture.h"
#include "grlib/CGLibDecShader.h"

namespace grlib {

namespace {

// channels of a surface format (the name is not the original's)
inline unsigned int getChannelNum(GrlSurfaceFormat format) {
    switch (static_cast<int>(format)) {
    case 1: return 1;
    case 2: return 1;
    case 3: return 1;
    case 4: return 1;
    case 5: return 1;
    case 6: return 1;
    case 7: return 1;
    case 8: return 1;
    case 9: return 1;
    case 10: return 1;
    case 11: return 1;
    case 12: return 1;
    case 13: return 2;
    case 14: return 2;
    case 15: return 2;
    case 16: return 2;
    case 17: return 2;
    case 18: return 2;
    case 19: return 2;
    case 20: return 2;
    case 21: return 2;
    case 22: return 2;
    case 23: return 2;
    case 24: return 2;
    case 53: return 2;
    case 54: return 2;
    default: return 4;
    }
}

// bytes of a texel of a surface format (the name is not the original's)
inline unsigned int getTexelSize(GrlSurfaceFormat format) {
    switch (static_cast<int>(format)) {
    case 1: return 1;
    case 2: return 1;
    case 3: return 1;
    case 4: return 1;
    case 5: return 2;
    case 6: return 2;
    case 7: return 2;
    case 8: return 2;
    case 9: return 2;
    case 10: return 4;
    case 11: return 4;
    case 12: return 4;
    case 13: return 2;
    case 14: return 2;
    case 15: return 2;
    case 16: return 2;
    case 17: return 4;
    case 18: return 4;
    case 19: return 4;
    case 20: return 4;
    case 21: return 4;
    case 22: return 8;
    case 23: return 8;
    case 24: return 8;
    case 37: return 4;
    case 38: return 4;
    case 39: return 4;
    case 40: return 4;
    case 41: return 8;
    case 42: return 8;
    case 43: return 8;
    case 44: return 8;
    case 45: return 8;
    case 46: return 16;
    case 47: return 16;
    case 48: return 16;
    case 53: return 4;
    case 54: return 4;
    case 56: return 4;
    case 57: return 2;
    case 59: return 2;
    case 60: return 2;
    case 61: return 4;
    case 62: return 4;
    case 63: return 4;
    case 66: return 1;
    case 67: return 2;
    case 68: return 2;
    case 70: return 1;
    case 71: return 2;
    case 72: return 2;
    case 73: return 1;
    case 74: return 1;
    case 75: return 2;
    case 76: return 2;
    case 77: return 4;
    case 79: return 4;
    case 80: return 4;
    default: return 0;
    }
}

// index into CGLibAccUtilTexture's s_p*Call tables (the name is not the original's)
inline unsigned int getAccessType(GrlSurfaceFormat format) {
    switch (static_cast<int>(format)) {
    case 1: return 0;
    case 2: return 0;
    case 3: return 0;
    case 4: return 0;
    case 5: return 1;
    case 6: return 4;
    case 7: return 4;
    case 8: return 3;
    case 9: return 2;
    case 10: return 5;
    case 11: return 7;
    case 12: return 6;
    case 13: return 0;
    case 14: return 0;
    case 15: return 0;
    case 16: return 0;
    case 17: return 1;
    case 18: return 4;
    case 19: return 4;
    case 20: return 3;
    case 21: return 2;
    case 22: return 5;
    case 23: return 7;
    case 24: return 6;
    case 37: return 0;
    case 38: return 0;
    case 39: return 0;
    case 40: return 0;
    case 41: return 1;
    case 42: return 4;
    case 43: return 4;
    case 44: return 3;
    case 45: return 2;
    case 46: return 5;
    case 47: return 7;
    case 48: return 6;
    case 53: return 1;
    case 54: return 1;
    case 56: return 0;
    default: return 8;
    }
}

// the NVN shader stage of each stage index a program's reflection data lists. Proposed name, not the original's:
// the symbols leave it unnamed (lbl_71009CF1B0)
const NVNshaderStage s_shaderStageTbl[6] = {
    static_cast<NVNshaderStage>(0), static_cast<NVNshaderStage>(1), static_cast<NVNshaderStage>(2),
    static_cast<NVNshaderStage>(3), static_cast<NVNshaderStage>(4), static_cast<NVNshaderStage>(5),
};

}  // namespace

CGLibAcc2DTexture::CGLibAcc2DTexture() {
    m_pUnused[0] = nullptr;
    m_pUnused[1] = nullptr;
    m_isLock = false;
    m_isWrite = false;
    m_unusedFlag = false;
}

CGLibAcc2DTexture::~CGLibAcc2DTexture() {}

bool CGLibAcc2DTexture::lock(CGLibTextureBuffer& buffer) {
    m_pBuffer = &buffer;
    m_isLock = true;
    setup2DTexutreInfo(buffer, 0);
    return true;
}

unsigned int CGLibAccUtilTexture::getCalcType(GrlSurfaceFormat format) const {
    return getAccessType(format);
}

unsigned int CGLibAccUtilTexture::getCalcChanel(GrlSurfaceFormat format) const {
    return getChannelNum(format);
}

// 1.0.0's out-of-line copy (0x710079C9AC) has no 3.0.1 caller left: its only users inline it.
void CGLibAccUtilTexture::setupFormatParam() {
    m_sectorWidth = 16 / m_texelSize;
    m_sectorHeight = 2;
    m_unusedParam = 2;
    m_gobWidth = 32 / m_texelSize;
    m_gobHeight = 8;
    m_blockHeight = 8;
}

void CGLibAccUtilTexture::setup2DTexutreInfo(CGLibTextureBuffer& buffer, unsigned int mipLevel) {
    unsigned int width = buffer.m_width;
    unsigned int height = buffer.m_height;
    if (mipLevel != 0) {
        width >>= mipLevel;
        height >>= mipLevel;
        if (width == 0) width = 1;
        if (height == 0) height = 1;
    }
    m_width = width;
    m_height = height;
    m_depth = 1;
    m_sliceSize = width * height;
    m_channelNum = getCalcChanel(buffer.m_format);
    m_channelIdx = m_channelNum - 1 > 2 ? 2 : m_channelNum - 1;
    m_texelSize = getTexelSize(buffer.m_format);
    unsigned int type = getCalcType(buffer.m_format);
    m_pReadF32 = s_pReadF32Call[type];
    m_pReadInt = s_pReadIntCall[type];
    m_pWriteF32 = s_pWriteF32Call[type];
    m_pWriteInt = s_pWriteIntCall[type];
    m_pData = buffer.m_pData;
    m_dataSize = buffer.m_dataSize;
    setupFormatParam();
    m_isLinear = (buffer.m_flags & 0x20) != 0;
}

unsigned int CGLibTextureBuffer::getMipmap() const {
    return m_mipmap;
}

void CGLibAcc2DTexture::unlock() {
    if (m_isWrite) {
        nn::os::FlushDataCache(m_pBuffer->m_pData, m_pBuffer->m_dataSize);
    }
}

void CGLibAcc2DTexture::setInt(int value, unsigned int x, unsigned int y) {
    int texel[4] = {value, 0, 0, 0};
    CGLibAccUtilTexture::setInt(texel, x, y);
    m_isWrite = true;
}

void CGLibAccUtilTexture::texaccread_f32_r(float* out) {
    out[0] = (this->*m_pReadF32)(0);
}

void CGLibAccUtilTexture::texaccread_f32_rg(float* out) {
    out[0] = (this->*m_pReadF32)(0);
    out[1] = (this->*m_pReadF32)(1);
}

void CGLibAccUtilTexture::texaccread_f32_rgba(float* out) {
    out[0] = (this->*m_pReadF32)(0);
    out[1] = (this->*m_pReadF32)(1);
    out[2] = (this->*m_pReadF32)(2);
    out[3] = (this->*m_pReadF32)(3);
}

void CGLibAccUtilTexture::texaccwrite_int_r(const int* value) {
    (this->*m_pWriteInt)(value, 0);
}

void CGLibAccUtilTexture::texaccwrite_int_rg(const int* value) {
    (this->*m_pWriteInt)(value, 0);
    (this->*m_pWriteInt)(value, 1);
}

void CGLibAccUtilTexture::texaccwrite_int_rgba(const int* value) {
    (this->*m_pWriteInt)(value, 0);
    (this->*m_pWriteInt)(value, 1);
    (this->*m_pWriteInt)(value, 2);
    (this->*m_pWriteInt)(value, 3);
}

float CGLibAccUtilTexture::texaccread_f32_8(unsigned int channel) {
    return m_pTexel[channel] / 255.0f;
}

float CGLibAccUtilTexture::texaccread_f32_16_float(unsigned int channel) {
    return CGLibUtilPixel::convF16toF32(*(unsigned short*)(m_pTexel + channel * 2));
}

float CGLibAccUtilTexture::texaccread_f32_16_int(unsigned int channel) {
    return *(short*)(m_pTexel + channel * 2);
}

float CGLibAccUtilTexture::texaccread_f32_16_uint(unsigned int channel) {
    return *(unsigned short*)(m_pTexel + channel * 2);
}

float CGLibAccUtilTexture::texaccread_f32_16_unom(unsigned int channel) {
    return *(unsigned short*)(m_pTexel + channel * 2) / 65535.0f;
}

float CGLibAccUtilTexture::texaccread_f32_32_float(unsigned int channel) {
    return *(float*)(m_pTexel + channel * 4);
}

float CGLibAccUtilTexture::texaccread_f32_32_int(unsigned int channel) {
    return *(int*)(m_pTexel + channel * 4);
}

float CGLibAccUtilTexture::texaccread_f32_32_uint(unsigned int channel) {
    return *(unsigned int*)(m_pTexel + channel * 4);
}

float CGLibAccUtilTexture::texaccread_f32_err(unsigned int channel) {
    return 0.0f;
}

int CGLibAccUtilTexture::texaccread_int_8(unsigned int channel) {
    return m_pTexel[channel];
}

int CGLibAccUtilTexture::texaccread_int_16_float(unsigned int channel) {
    return CGLibUtilPixel::convF16toF32(*(unsigned short*)(m_pTexel + channel * 2)) * 255.0f;
}

int CGLibAccUtilTexture::texaccread_int_16_int(unsigned int channel) {
    return *(short*)(m_pTexel + channel * 2);
}

int CGLibAccUtilTexture::texaccread_int_16_uint(unsigned int channel) {
    return *(unsigned short*)(m_pTexel + channel * 2);
}

int CGLibAccUtilTexture::texaccread_int_16_unom(unsigned int channel) {
    return *(unsigned short*)(m_pTexel + channel * 2);
}

int CGLibAccUtilTexture::texaccread_int_32_float(unsigned int channel) {
    return *(float*)(m_pTexel + channel * 4) * 255.0f;
}

int CGLibAccUtilTexture::texaccread_int_32_int(unsigned int channel) {
    return *(int*)(m_pTexel + channel * 4);
}

int CGLibAccUtilTexture::texaccread_int_32_uint(unsigned int channel) {
    return *(unsigned int*)(m_pTexel + channel * 4);
}

int CGLibAccUtilTexture::texaccread_int_err(unsigned int channel) {
    return 0;
}

void CGLibAccUtilTexture::texaccwrite_f32_8(const float* value, unsigned int channel) {
    m_pTexel[channel] = value[channel] * 255.0f;
}

void CGLibAccUtilTexture::texaccwrite_f32_16_float(const float* value, unsigned int channel) {
    *(unsigned short*)(m_pTexel + channel * 2) = CGLibUtilPixel::convF32toF16(value[channel]);
}

void CGLibAccUtilTexture::texaccwrite_f32_16_int(const float* value, unsigned int channel) {
    *(short*)(m_pTexel + channel * 2) = value[channel];
}

void CGLibAccUtilTexture::texaccwrite_f32_16_uint(const float* value, unsigned int channel) {
    *(unsigned short*)(m_pTexel + channel * 2) = value[channel];
}

void CGLibAccUtilTexture::texaccwrite_f32_16_unom(const float* value, unsigned int channel) {
    *(unsigned short*)(m_pTexel + channel * 2) = value[channel] * 65535.0f;
}

void CGLibAccUtilTexture::texaccwrite_f32_32_float(const float* value, unsigned int channel) {
    *(float*)(m_pTexel + channel * 4) = value[channel];
}

void CGLibAccUtilTexture::texaccwrite_f32_32_int(const float* value, unsigned int channel) {
    *(int*)(m_pTexel + channel * 4) = value[channel];
}

void CGLibAccUtilTexture::texaccwrite_f32_32_uint(const float* value, unsigned int channel) {
    *(unsigned int*)(m_pTexel + channel * 4) = (int)value[channel];
}

void CGLibAccUtilTexture::texaccwrite_f32_err(const float* value, unsigned int channel) {}

void CGLibAccUtilTexture::texaccwrite_int_8(const int* value, unsigned int channel) {
    m_pTexel[channel] = value[channel];
}

void CGLibAccUtilTexture::texaccwrite_int_16_float(const int* value, unsigned int channel) {
    *(unsigned short*)(m_pTexel + channel * 2) = CGLibUtilPixel::convF32toF16(value[channel] * (1.0f / 255.0f));
}

void CGLibAccUtilTexture::texaccwrite_int_16_int(const int* value, unsigned int channel) {
    *(short*)(m_pTexel + channel * 2) = value[channel];
}

void CGLibAccUtilTexture::texaccwrite_int_16_uint(const int* value, unsigned int channel) {
    *(unsigned short*)(m_pTexel + channel * 2) = value[channel];
}

void CGLibAccUtilTexture::texaccwrite_int_16_unom(const int* value, unsigned int channel) {
    *(unsigned short*)(m_pTexel + channel * 2) = value[channel];
}

void CGLibAccUtilTexture::texaccwrite_int_32_float(const int* value, unsigned int channel) {
    *(float*)(m_pTexel + channel * 4) = value[channel] * (1.0f / 255.0f);
}

void CGLibAccUtilTexture::texaccwrite_int_32_int(const int* value, unsigned int channel) {
    *(int*)(m_pTexel + channel * 4) = value[channel];
}

void CGLibAccUtilTexture::texaccwrite_int_32_uint(const int* value, unsigned int channel) {
    *(unsigned int*)(m_pTexel + channel * 4) = value[channel];
}

void CGLibAccUtilTexture::texaccwrite_int_err(const int* value, unsigned int channel) {}

CGLibAccUtilTexture::ReadF32Func CGLibAccUtilTexture::s_pReadF32Call[9] = {
    &CGLibAccUtilTexture::texaccread_f32_8,         &CGLibAccUtilTexture::texaccread_f32_16_float,
    &CGLibAccUtilTexture::texaccread_f32_16_int,    &CGLibAccUtilTexture::texaccread_f32_16_uint,
    &CGLibAccUtilTexture::texaccread_f32_16_unom,   &CGLibAccUtilTexture::texaccread_f32_32_float,
    &CGLibAccUtilTexture::texaccread_f32_32_int,    &CGLibAccUtilTexture::texaccread_f32_32_uint,
    &CGLibAccUtilTexture::texaccread_f32_err,
};
CGLibAccUtilTexture::ReadIntFunc CGLibAccUtilTexture::s_pReadIntCall[9] = {
    &CGLibAccUtilTexture::texaccread_int_8,         &CGLibAccUtilTexture::texaccread_int_16_float,
    &CGLibAccUtilTexture::texaccread_int_16_int,    &CGLibAccUtilTexture::texaccread_int_16_uint,
    &CGLibAccUtilTexture::texaccread_int_16_unom,   &CGLibAccUtilTexture::texaccread_int_32_float,
    &CGLibAccUtilTexture::texaccread_int_32_int,    &CGLibAccUtilTexture::texaccread_int_32_uint,
    &CGLibAccUtilTexture::texaccread_int_err,
};
CGLibAccUtilTexture::WriteF32Func CGLibAccUtilTexture::s_pWriteF32Call[9] = {
    &CGLibAccUtilTexture::texaccwrite_f32_8,        &CGLibAccUtilTexture::texaccwrite_f32_16_float,
    &CGLibAccUtilTexture::texaccwrite_f32_16_int,   &CGLibAccUtilTexture::texaccwrite_f32_16_uint,
    &CGLibAccUtilTexture::texaccwrite_f32_16_unom,  &CGLibAccUtilTexture::texaccwrite_f32_32_float,
    &CGLibAccUtilTexture::texaccwrite_f32_32_int,   &CGLibAccUtilTexture::texaccwrite_f32_32_uint,
    &CGLibAccUtilTexture::texaccwrite_f32_err,
};
CGLibAccUtilTexture::WriteIntFunc CGLibAccUtilTexture::s_pWriteIntCall[9] = {
    &CGLibAccUtilTexture::texaccwrite_int_8,        &CGLibAccUtilTexture::texaccwrite_int_16_float,
    &CGLibAccUtilTexture::texaccwrite_int_16_int,   &CGLibAccUtilTexture::texaccwrite_int_16_uint,
    &CGLibAccUtilTexture::texaccwrite_int_16_unom,  &CGLibAccUtilTexture::texaccwrite_int_32_float,
    &CGLibAccUtilTexture::texaccwrite_int_32_int,   &CGLibAccUtilTexture::texaccwrite_int_32_uint,
    &CGLibAccUtilTexture::texaccwrite_int_err,
};
CGLibAccUtilTexture::ReadF32ChannelFunc CGLibAccUtilTexture::s_pReadF32Channel[3] = {
    &CGLibAccUtilTexture::texaccread_f32_r,
    &CGLibAccUtilTexture::texaccread_f32_rg,
    &CGLibAccUtilTexture::texaccread_f32_rgba,
};
CGLibAccUtilTexture::WriteIntChannelFunc CGLibAccUtilTexture::s_pWriteIntChannel[3] = {
    &CGLibAccUtilTexture::texaccwrite_int_r,
    &CGLibAccUtilTexture::texaccwrite_int_rg,
    &CGLibAccUtilTexture::texaccwrite_int_rgba,
};

void ShdInstancePosMatrix3x4Set(float* pDst, const mm::Mat44& mat, float w) {
    ShdMat44TransposeMat34(pDst, mat);
    pDst[12] = w;
}

void ShdF32TransposeMat34(float* pDst, const float* pSrc) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            pDst[i * 4 + j] = pSrc[j * 4 + i];
        }
    }
}

void ShdMat44SetMat44(float* pDst, const mm::Mat44& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pDst[i * 4 + j] = mat.m[i][j];
        }
    }
}

void ShdMat44TransposeMat34(float* pDst, const mm::Mat44& mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            pDst[i * 4 + j] = mat.m[j][i];
        }
    }
}

void ShdMat44TransposeMat44(float* pDst, const mm::Mat44& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pDst[i * 4 + j] = mat.m[j][i];
        }
    }
}

void ShdMat44SetMat44Array(float* pDst, const mm::Mat44* pMat, int num) {
    for (int i = 0; i < num; i++) {
        ShdMat44SetMat44(pDst + i * 16, pMat[i]);
    }
}

void ShdMat44TransposeMat44Array(float* pDst, const mm::Mat44* pMat, int num) {
    for (int i = 0; i < num; i++) {
        ShdMat44TransposeMat44(pDst + i * 16, pMat[i]);
    }
}

void ShdF32SetF32Array(float* pDst, const float* pSrc, int num) {
    for (int i = 0; i < num; i++) {
        pDst[i] = pSrc[i];
    }
}

void ShdF32SetVec4(float* pDst, const float* pSrc) {
    pDst[0] = pSrc[0];
    pDst[1] = pSrc[1];
    pDst[2] = pSrc[2];
    pDst[3] = pSrc[3];
}

void ShdVec3SetVec3(float* pDst, const mm::Vec3& v) {
    pDst[0] = v.x;
    pDst[1] = v.y;
    pDst[2] = v.z;
}

void ShdVec4SetVec4(float* pDst, const mm::Vec4& v) {
    pDst[0] = v.x;
    pDst[1] = v.y;
    pDst[2] = v.z;
    pDst[3] = v.w;
}

void ShdS32SetIVec4(int* pDst, const int* pSrc) {
    pDst[0] = pSrc[0];
    pDst[1] = pSrc[1];
    pDst[2] = pSrc[2];
    pDst[3] = pSrc[3];
}

void ShdU32SetUVec4(unsigned int* pDst, const unsigned int* pSrc) {
    pDst[0] = pSrc[0];
    pDst[1] = pSrc[1];
    pDst[2] = pSrc[2];
    pDst[3] = pSrc[3];
}

void CGLibUniBaseUtility::setF32SetMat44(unsigned int ofs, const float* pSrc) {
    if (ofs != 0xFFFFFFFF) {
        ShdF32SetF32Array(reinterpret_cast<float*>(getBuff() + ofs), pSrc, 16);
    }
}

void CGLibUniBaseUtility::setMat44SetMat44(unsigned int ofs, const mm::Mat44& mat) {
    if (ofs != 0xFFFFFFFF) {
        ShdMat44SetMat44(reinterpret_cast<float*>(getBuff() + ofs), mat);
    }
}

void CGLibUniBaseUtility::setMat44SetMat34(unsigned int ofs, const mm::Mat44& mat) {
    if (ofs != 0xFFFFFFFF) {
        ShdF32SetF32Array(reinterpret_cast<float*>(getBuff() + ofs), &mat.m[0][0], 12);
    }
}

void CGLibUniBaseUtility::setF32SetF32Array(unsigned int ofs, const float* pSrc, int num) {
    if (ofs != 0xFFFFFFFF) {
        ShdF32SetF32Array(reinterpret_cast<float*>(getBuff() + ofs), pSrc, num);
    }
}

void CGLibUniBaseUtility::setF32SetVec4(unsigned int ofs, const float* pSrc) {
    if (ofs != 0xFFFFFFFF) {
        ShdF32SetVec4(reinterpret_cast<float*>(getBuff() + ofs), pSrc);
    }
}

void CGLibUniBaseUtility::setVec4SetVec4(unsigned int ofs, const mm::Vec4& v) {
    if (ofs != 0xFFFFFFFF) {
        ShdVec4SetVec4(reinterpret_cast<float*>(getBuff() + ofs), v);
    }
}

void CGLibUniBaseUtility::setS32SetIVec4(unsigned int ofs, int* pSrc) {
    if (ofs != 0xFFFFFFFF) {
        ShdS32SetIVec4(reinterpret_cast<int*>(getBuff() + ofs), pSrc);
    }
}

void CGLibUniBaseUtility::setU32SetUVec4(unsigned int ofs, unsigned int* pSrc) {
    if (ofs != 0xFFFFFFFF) {
        ShdU32SetUVec4(reinterpret_cast<unsigned int*>(getBuff() + ofs), pSrc);
    }
}

void CGLibUniBaseUtility::setUseUniformBlock(const char* name) {
    setUseUniformBlock(m_pDecShader->getCurrentShader().getUniformBlockOfs(name));
}

void CGLibUniBaseUtility::setUseUniformBlock(unsigned int location) {
    m_location = location;
    m_size = m_pDecShader->getCurrentShader().getUniformBlockSize(location);
    m_isSet = false;
    setMoveMem();
}

CGLibUniformEtcUtility::CGLibUniformEtcUtility(const CGLibDecShader* pDecShader)
    : CGLibUniBaseUtility(pDecShader) {}

unsigned char* CGLibUniformEtcUtility::getBuff() {
    return static_cast<unsigned char*>(m_block.getBuff());
}

void* CGLibEtcUniformBlock::getBuff() {
    return m_pBuff;
}

void CGLibUniformEtcUtility::updateData() {}

void CGLibUniformEtcUtility::setUniformBlock() {
    m_block.setUniformBlock(m_location);
}

void CGLibEtcUniformBlock::setUniformBlock(unsigned int location) {
    ::grlib::context::CGLibSystemContext* pSys = ::grlib::context::CGLibSystemContext::sys();
    pSys->m_pipeline.m_pShader->setUniformBlock(location, pSys->m_pipeline.m_pCmdBuf, m_gpuAddress, m_size);
}

// 3.0.1's linker dropped this (no caller left); 1.0.0 has it (0x71007A4AE4)
void CGLibEtcUniformBlock::setStorageBuffer(unsigned int location) {
    ::grlib::context::CGLibSystemContext* pSys = ::grlib::context::CGLibSystemContext::sys();
    pSys->m_pipeline.m_pShader->setStorageBuffer(location, pSys->m_pipeline.m_pCmdBuf, m_gpuAddress, m_size);
}

void CGLibUniformEtcUtility::setStorageBuffer() {
    m_block.setStorageBuffer(m_location);
}

void CGLibShader_plf::setUniformBlock(unsigned int location, NVNcommandBuffer* pCmdBuf, unsigned long gpuAddress, unsigned int size) {
    const CGLibShaderResourceTbl& tbl = m_pInfo->m_uniformBlocks;
    if (location < tbl.m_locationNum) {
        unsigned int idx = (m_pData + tbl.m_locationTblOfs)[location];
        if (idx != 0xFF) {
            const CGLibShaderBufferInfo& info = reinterpret_cast<const CGLibShaderBufferInfo*>(m_pData + tbl.m_entryOfs)[idx];
            unsigned int num = info.m_stageNum;
            const unsigned char* pStage = m_pData + info.m_stageOfs;
            for (unsigned int i = 0; i < num; i++, pStage += 2) {
                nvnCommandBufferBindUniformBuffer(pCmdBuf, s_shaderStageTbl[pStage[0]], pStage[1], gpuAddress, static_cast<int>(size));
            }
        }
    }
}

void CGLibShader_plf::setStorageBuffer(unsigned int location, NVNcommandBuffer* pCmdBuf, unsigned long gpuAddress, unsigned int size) {
    const CGLibShaderResourceTbl& tbl = m_pInfo->m_storageBuffers;
    if (location < tbl.m_locationNum) {
        unsigned int idx = (m_pData + tbl.m_locationTblOfs)[location];
        if (idx != 0xFF) {
            const CGLibShaderBufferInfo& info = reinterpret_cast<const CGLibShaderBufferInfo*>(m_pData + tbl.m_entryOfs)[idx];
            unsigned int num = info.m_stageNum;
            const unsigned char* pStage = m_pData + info.m_stageOfs;
            for (unsigned int i = 0; i < num; i++, pStage += 2) {
                nvnCommandBufferBindStorageBuffer(pCmdBuf, s_shaderStageTbl[pStage[0]], pStage[1], gpuAddress, static_cast<int>(size));
            }
        }
    }
}

void CGLibShader_plf::setTextureHandle(unsigned int location, NVNcommandBuffer* pCmdBuf, unsigned long handle) {
    const CGLibShaderResourceTbl& tbl = m_pInfo->m_textures;
    if (location < tbl.m_locationNum) {
        unsigned int idx = (m_pData + tbl.m_locationTblOfs)[location];
        if (idx != 0xFF) {
            const CGLibShaderTextureInfo& info = reinterpret_cast<const CGLibShaderTextureInfo*>(m_pData + tbl.m_entryOfs)[idx];
            unsigned int num = info.m_stageNum;
            const unsigned char* pStage = m_pData + info.m_stageOfs;
            for (unsigned int i = 0; i < num; i++, pStage += 2) {
                nvnCommandBufferBindTexture(pCmdBuf, s_shaderStageTbl[pStage[0]], pStage[1], handle);
            }
        }
    }
}

void CGLibShader_plf::setImageHandle(unsigned int location, NVNcommandBuffer* pCmdBuf, unsigned long handle) {
    const CGLibShaderResourceTbl& tbl = m_pInfo->m_images;
    if (location < tbl.m_locationNum) {
        unsigned int idx = (m_pData + tbl.m_locationTblOfs)[location];
        if (idx != 0xFF) {
            const CGLibShaderTextureInfo& info = reinterpret_cast<const CGLibShaderTextureInfo*>(m_pData + tbl.m_entryOfs)[idx];
            unsigned int num = info.m_stageNum;
            const unsigned char* pStage = m_pData + info.m_stageOfs;
            for (unsigned int i = 0; i < num; i++, pStage += 2) {
                nvnCommandBufferBindImage(pCmdBuf, s_shaderStageTbl[pStage[0]], pStage[1], handle);
            }
        }
    }
}

unsigned int CGLibShader::getTextureLocation(const char* name) const {
    int num = m_pInfo->m_textures.m_num;
    const CGLibShaderTextureInfo* pInfo =
        reinterpret_cast<const CGLibShaderTextureInfo*>(m_pData + m_pInfo->m_textures.m_entryOfs);
    for (unsigned int i = 0; i < num; i++, pInfo++) {
        if (strcmp(reinterpret_cast<const char*>(m_pData + pInfo->m_nameOfs), name) == 0) {
            return pInfo->m_location;
        }
    }
    return -1;
}

unsigned int CGLibShader::getUniformBlockOfs(const char* name) const {
    int num = m_pInfo->m_uniformBlocks.m_num;
    const CGLibShaderBufferInfo* pInfo =
        reinterpret_cast<const CGLibShaderBufferInfo*>(m_pData + m_pInfo->m_uniformBlocks.m_entryOfs);
    for (unsigned int i = 0; i < num; i++, pInfo++) {
        if (strcmp(reinterpret_cast<const char*>(m_pData + pInfo->m_nameOfs), name) == 0) {
            return pInfo->m_location;
        }
    }
    return -1;
}

CGLibDblUniformBlock::CGLibDblUniformBlock() {}

CGLibDblUniformBlock::~CGLibDblUniformBlock() {
    release();
}

void CGLibDblUniformBlock::release() {
    CGLibMemHandle::free(m_mem);
    m_pBuff[0] = nullptr;
    m_pBuff[1] = nullptr;
}

void CGLibDblUniformBlock::setup(int size) {
    release();
    unsigned int alignSize = size + (0x100 - size % 0x100) % 0x100;
    CGLibMemHandle::allocUniform(m_mem, alignSize * 2);
    m_pBuff[0] = static_cast<unsigned char*>(m_mem.m_pMem);
    m_pBuff[1] = m_pBuff[0] + alignSize;
    m_size = size;
    ::grlib::context::CGLibSystemContext::sys()->getUniformoGpuAddress(m_gpuAddress[0], m_mem);
    m_gpuAddress[1] = m_gpuAddress[0] + alignSize;
}

unsigned int CGLibDblUniformBlock::setupArray(int size, CGLibMemType& mem, unsigned int ofs) {
    unsigned int alignSize = size + (0x100 - size % 0x100) % 0x100;
    CGLibMemHandle::setMemBuff(m_mem, static_cast<unsigned char*>(mem.m_pMem) + ofs);
    m_pBuff[0] = static_cast<unsigned char*>(m_mem.m_pMem);
    m_pBuff[1] = m_pBuff[0] + alignSize;
    m_size = size;
    ::grlib::context::CGLibSystemContext::sys()->getUniformoGpuAddress(m_gpuAddress[0], mem);
    m_gpuAddress[0] += ofs;
    m_gpuAddress[1] = m_gpuAddress[0] + alignSize;
    return alignSize * 2;
}

void CGLibDblUniformBlock::updateData() {
    updateData(0, m_size);
}

void CGLibDblUniformBlock::updateData(unsigned int ofs, unsigned int size) {
    nn::os::FlushDataCache(m_pBuff[CGLibManager::s_nDblNowIdx] + ofs, size);
}

unsigned char* CGLibDblUniformBlock::getBuff() {
    return m_pBuff[CGLibManager::s_nDblNowIdx];
}

void CGLibDblUniformBlock::setUniformBlock(unsigned int location) {
    ::grlib::context::CGLibSystemContext* pSys = ::grlib::context::CGLibSystemContext::sys();
    pSys->m_pipeline.m_pShader->setUniformBlock(location, pSys->m_pipeline.m_pCmdBuf, getGPUAdress(), m_size);
}

void CGLibDblUniformBlock::setStorageBuffer(unsigned int location) {
    ::grlib::context::CGLibSystemContext* pSys = ::grlib::context::CGLibSystemContext::sys();
    pSys->m_pipeline.m_pShader->setStorageBuffer(location, pSys->m_pipeline.m_pCmdBuf, getGPUAdress(), m_size);
}

void CGLibDblUniformBlock::setUniformBlock(unsigned int location, unsigned int ofs, unsigned int size) {
    ::grlib::context::CGLibSystemContext* pSys = ::grlib::context::CGLibSystemContext::sys();
    pSys->m_pipeline.m_pShader->setUniformBlock(location, pSys->m_pipeline.m_pCmdBuf, getGPUAdress() + ofs, size);
}

void CGLibDblUniformBlock::setStorageBuffer(unsigned int location, unsigned int ofs, unsigned int size) {
    ::grlib::context::CGLibSystemContext* pSys = ::grlib::context::CGLibSystemContext::sys();
    pSys->m_pipeline.m_pShader->setStorageBuffer(location, pSys->m_pipeline.m_pCmdBuf, getGPUAdress() + ofs, size);
}

unsigned long CGLibDblUniformBlock_plf::getGPUAdress() const {
    return m_gpuAddress[CGLibManager::s_nDblNowIdx];
}

CGLibOneUniformBlock::CGLibOneUniformBlock() : m_pBuff(nullptr), m_gpuAddress(0) {}

CGLibOneUniformBlock::~CGLibOneUniformBlock() {
    release();
}

void CGLibOneUniformBlock::release() {
    CGLibMemHandle::free(m_mem);
    m_pBuff = nullptr;
}

void CGLibOneUniformBlock::setup(int size) {
    release();
    CGLibMemHandle::allocUniform(m_mem, size + (0x100 - size % 0x100) % 0x100);
    m_pBuff = static_cast<unsigned char*>(m_mem.m_pMem);
    m_size = size;
    ::grlib::context::CGLibSystemContext::sys()->getUniformoGpuAddress(m_gpuAddress, m_mem);
}

void CGLibOneUniformBlock::setup(CGLibVtlMemPool* pool, unsigned int size, unsigned int ofs) {
    release();
    CGLibMemHandle::setMemBuff(m_mem, pool->m_pMem + ofs);
    m_pBuff = static_cast<unsigned char*>(m_mem.m_pMem);
    m_size = size;
    m_gpuAddress = pool->m_gpuAddress + ofs;
}

unsigned int CGLibOneUniformBlock::setupArray(int size, CGLibMemType& mem, unsigned int ofs) {
    CGLibMemHandle::setMemBuff(m_mem, static_cast<unsigned char*>(mem.m_pMem) + ofs);
    m_pBuff = static_cast<unsigned char*>(m_mem.m_pMem);
    m_size = size;
    ::grlib::context::CGLibSystemContext::sys()->getUniformoGpuAddress(m_gpuAddress, mem);
    m_gpuAddress += ofs;
    return size + (0x100 - size % 0x100) % 0x100;
}

void CGLibOneUniformBlock::setupArray(CGLibVtlMemPool* pool, unsigned int size, unsigned int ofs) {
    CGLibMemHandle::setMemBuff(m_mem, pool->m_pMem + ofs);
    m_pBuff = static_cast<unsigned char*>(m_mem.m_pMem);
    m_size = size;
    m_gpuAddress = pool->m_gpuAddress + ofs;
}

void CGLibOneUniformBlock::updateData() {
    updateData(0, m_size);
}

// 3.0.1's linker dropped this (no caller); 1.0.0 has it (0x71007A5FA0)
void CGLibOneUniformBlock::updateData(unsigned int ofs, unsigned int size) {
    nn::os::FlushDataCache(m_pBuff + ofs, size);
}

void CGLibOneUniformBlock::setUniformBlock(unsigned int location) {
    ::grlib::context::CGLibSystemContext* pSys = ::grlib::context::CGLibSystemContext::sys();
    pSys->m_pipeline.m_pShader->setUniformBlock(location, pSys->m_pipeline.m_pCmdBuf, m_gpuAddress, m_size);
}

void CGLibOneUniformBlock::setStorageBuffer(unsigned int location) {
    ::grlib::context::CGLibSystemContext* pSys = ::grlib::context::CGLibSystemContext::sys();
    pSys->m_pipeline.m_pShader->setStorageBuffer(location, pSys->m_pipeline.m_pCmdBuf, m_gpuAddress, m_size);
}

void CGLibOneUniformBlock::setStorageBuffer(unsigned int location, unsigned int ofs, unsigned int size) {
    ::grlib::context::CGLibSystemContext* pSys = ::grlib::context::CGLibSystemContext::sys();
    pSys->m_pipeline.m_pShader->setStorageBuffer(location, pSys->m_pipeline.m_pCmdBuf, m_gpuAddress + ofs, size);
}

unsigned char* CGLibOneUniformBlock::getMapping() {
    return m_pBuff;
}

CGLibTriUniformBlock::CGLibTriUniformBlock() : m_pBuff(), m_gpuAddress() {}

CGLibTriUniformBlock::~CGLibTriUniformBlock() {
    release();
}

void CGLibTriUniformBlock::release() {
    for (int i = 0; i < 3; i++) {
        m_gpuAddress[i] = 0;
    }
    CGLibMemHandle::free(m_mem);
    for (int i = 0; i < 3; i++) {
        m_pBuff[i] = nullptr;
    }
}

unsigned int CGLibTriUniformBlock::setupArray(int size, CGLibMemType& mem, unsigned int ofs) {
    unsigned int alignSize = size + (0x100 - size % 0x100) % 0x100;
    m_size = size;
    CGLibMemHandle::setMemBuff(m_mem, static_cast<unsigned char*>(mem.m_pMem) + ofs);
    unsigned char* pMem = static_cast<unsigned char*>(m_mem.m_pMem);
    m_pBuff[0] = pMem;
    m_pBuff[1] = pMem + alignSize;
    m_pBuff[2] = pMem + alignSize * 2;
    ::grlib::context::CGLibSystemContext::sys()->getUniformoGpuAddress(m_gpuAddress[0], mem);
    m_gpuAddress[0] += ofs;
    m_gpuAddress[1] = m_gpuAddress[0] + alignSize;
    m_gpuAddress[2] = m_gpuAddress[0] + alignSize * 2;
    return alignSize * 3;
}

void CGLibTriUniformBlock::updateData() {
    updateData(0, m_size);
}

// 3.0.1's linker dropped this (no caller); 1.0.0 has it (0x71007A673C)
void CGLibTriUniformBlock::updateData(unsigned int ofs, unsigned int size) {
    nn::os::FlushDataCache(m_pBuff[CGLibManager::s_nTriNowIdx] + ofs, size);
}

void CGLibTriUniformBlock::updateOldData() {
    unsigned int size = m_size;
    int idx = CGLibManager::s_nTriNowIdx;
    nn::os::FlushDataCache(m_pBuff[idx < 1 ? 2 : idx - 1], size);
}

unsigned char* CGLibTriUniformBlock::getBuff() {
    return m_pBuff[CGLibManager::s_nTriNowIdx];
}

unsigned char* CGLibTriUniformBlock::getOldBuff() {
    int idx = CGLibManager::s_nTriNowIdx;
    return m_pBuff[idx < 1 ? 2 : idx - 1];
}

void CGLibTriUniformBlock::setUniformBlock(unsigned int location) {
    ::grlib::context::CGLibSystemContext* pSys = ::grlib::context::CGLibSystemContext::sys();
    pSys->m_pipeline.m_pShader->setUniformBlock(location, pSys->m_pipeline.m_pCmdBuf, m_gpuAddress[CGLibManager::s_nTriNowIdx], m_size);
}

CGLibEtcUniformBlock::CGLibEtcUniformBlock() : m_size(0) {
    ::grlib::context::CGLibSystemContext::sys()->getGlbUniformParam(m_pBuff, m_gpuAddress);
}

CGLibEtcUniformBlock::~CGLibEtcUniformBlock() {}

void CGLibEtcUniformBlock::updateData(unsigned int size) {
    m_size = size;
    if (size != 0) {
        ::grlib::context::CGLibSystemContext::sys()->nextGlbUniformOfs(size);
    }
}

void CGLibEtcUniformBlock::Rebuilding() {
    ::grlib::context::CGLibSystemContext::sys()->getGlbUniformParam(m_pBuff, m_gpuAddress);
}

void CGLibEtcUniformBlock::setMoveMem(unsigned int size) {
    if (size != 0) {
        m_size = size;
        ::grlib::context::CGLibSystemContext::sys()->nextGlbUniformOfs(size);
    }
}

}  // namespace grlib

namespace grlib {

// ---- CGLibSampler ----

namespace {

// the border colour of each GrlTexBorderType. Proposed name, not the original's: the symbols leave it unnamed
// (lbl_71009CEE0C)
const mm::Col4 s_borderColorTbl[3] = {
    mm::Col4(0.0f, 0.0f, 0.0f, 0.0f),
    mm::Col4(0.0f, 0.0f, 0.0f, 1.0f),
    mm::Col4(1.0f, 1.0f, 1.0f, 1.0f),
};

}  // namespace


CGLibSampler::~CGLibSampler() {
    release();
}

void CGLibSampler::release() {
    if (m_pSamObj != nullptr) {
        context::CGLibSystemContext::sys()->m_samplerTbl.freeSampler(m_pSamObj);
    }
}

void CGLibSampler::initSampler(GrlTexClamp clamp, GrlTexMagFilterType filter) {
    m_params = CGLibWkrSamplerParams();
    setClamp(clamp, clamp, clamp);
    if (filter == 0) {
        setFilter(filter, static_cast<GrlTexMinFilterType>(0), static_cast<GrlTexTexAnisoRatio>(0));
    } else {
        setFilter(filter, static_cast<GrlTexMinFilterType>(1), static_cast<GrlTexTexAnisoRatio>(0));
    }
}

void CGLibSampler::setClamp(GrlTexClamp s, GrlTexClamp t, GrlTexClamp r) {
    m_params.m_clampS = s;
    m_params.m_clampT = t;
    m_params.m_clampR = r;
    if (s > 5 || t > 5 || r > 5) {
        m_params.m_border = 1;
    } else {
        m_params.m_border = 0;
    }
}

void CGLibSampler::setFilter(GrlTexMagFilterType mag, GrlTexMinFilterType min, GrlTexTexAnisoRatio aniso) {
    m_params.m_magFilter = mag;
    m_params.m_minFilter = min;
    m_params.m_aniso = aniso;
}

void CGLibSampler::setLOD(float lod) {
    m_params.m_lod = lod;
}

void CGLibSampler::setDepthCompare(GrlTexCompare compare) {
    m_params.m_compare = compare;
}

void CGLibSampler::setBorderType(GrlTexBorderType type) {
    setBorderColor(s_borderColorTbl[type]);
}

void CGLibSampler::setBorderColor(const mm::Col4& color) {
    m_params.m_borderColor.r = color.r;
    m_params.m_borderColor.g = color.g;
    m_params.m_borderColor.b = color.b;
    m_params.m_borderColor.a = color.a;
}

void CGLibSampler::updateData() {
    release();
    m_pSamObj = context::CGLibSystemContext::sys()->m_samplerTbl.allocSampler(m_params);
}

// ---- CGLibOcclusionQuery ----

CGLibOcclusionQuery::CGLibOcclusionQuery() : m_pReport(nullptr), m_id(0), m_validMask(0), m_writeIdx(0), m_readIdx(1) {}

void CGLibOcclusionQuery::release() {
    if (m_pReport != nullptr) {
        context::CGLibSystemContext::sys()->m_occlusion.freeID(m_id);
        m_pReport = nullptr;
        m_id = 0;
    }
}

void CGLibOcclusionQuery::beginQuery() {
    nvnCommandBufferResetCounter(context::CGLibSystemContext::sys()->m_pipeline.m_pCmdBuf, static_cast<NVNcounterType>(1));
}



// ---- CGLibPixlCounter ----

CGLibPixlCounter::CGLibPixlCounter() : m_gpuAddress(0) {}

void CGLibPixlCounter::release() {
    CGLibMemHandle::free(m_mem);
    m_gpuAddress = 0;
}

void CGLibPixlCounter::beginCounter() {
    nvnCommandBufferResetCounter(context::CGLibSystemContext::sys()->m_pipeline.m_pCmdBuf, static_cast<NVNcounterType>(1));
}

void CGLibPixlCounter::endCounter() {
    context::CGLibSystemContext* pSys = context::CGLibSystemContext::sys();
    if (m_gpuAddress == 0) {
        CGLibMemHandle::allocUniform(m_mem, 0x100);
        context::CGLibSystemContext::sys()->getUniformoGpuAddress(m_gpuAddress, m_mem);
    }
    nvnCommandBufferReportCounter(pSys->m_pipeline.m_pCmdBuf, static_cast<NVNcounterType>(1), m_gpuAddress);
}


// ---- small accessors ----

void CGLibRenderTargetBase::setColorInvalidate() {}

unsigned int CGLibColorBuffer::getWidth() const {
    return m_width;
}

unsigned int CGLibColorBuffer::getHeight() const {
    return m_height;
}

unsigned int CGLibTextureBuffer::getWidth() const {
    return m_width;
}

unsigned int CGLibTextureBuffer::getHeight() const {
    return m_height;
}

GrlSurfaceFormat CGLibTextureBuffer::getFormat() const {
    return m_format;
}

void CGLibRenderTarget::clearTexture(const mm::Col4& color, GrlClaerMask mask) {
    CGLibDepthCtl::clearColorBuffer(m_colorBuffer, color, mask);
}

void CGLibRenderTarget::clearIntTexture(const int* values, GrlClaerMask mask) {
    CGLibDepthCtl::clearIntColorBuffer(m_colorBuffer, values, mask);
}

bool CGLibTextureBuffer::isTexture1D() const {
    return m_type == 1;
}

bool CGLibTextureBuffer::isTexture3D() const {
    return m_type == 5;
}

bool CGLibTextureBuffer::isInitialized() const {
    return m_flags & 1;
}

float CGLibTextureBuffer::get1PixelTextureInfo() {
    float value;
    CGLibTexture::get1PixelTextureInfo(&value, *this);
    return value;
}

unsigned int CGLibDepthBuffer::getWidth() const {
    return m_width;
}

unsigned int CGLibDepthBuffer::getHeight() const {
    return m_height;
}

void CGLibDepthBuffer::invalidate() {}

// ---- CGLibDecShader / CGLibDecShdExtTbl ----

unsigned int CGLibDecShader::calcTblSize(const void* data) {
    const CGLibDecShaderData* pData = static_cast<const CGLibDecShaderData*>(data);
    if (pData->m_magic != 0x54434C53) {
        return 0;
    }
    if ((pData->m_version >> 1) != 0x801) {
        return 0;
    }
    return pData->m_declNum;
}

unsigned int CGLibDecShader::getDeclarationMax() const {
    return m_pData->m_declNum;
}

CGLibDecShdExtTbl::CGLibDecShdExtTbl() {
    m_current = 0;
    m_pTbl = nullptr;
    m_pDecShader = nullptr;
}

void CGLibDecShdExtTbl::setTbl(unsigned char* pTbl) {
    m_pTbl = pTbl;
}

void CGLibDecShdExtTbl::setObj(CGLibDecShader* pDecShader) {
    m_pDecShader = pDecShader;
    int num = pDecShader->getDeclarationMax();
    for (int i = 0; i < num; i++) {
        m_pTbl[i] = 0;
    }
    m_current = 0;
}


}  // namespace grlib
