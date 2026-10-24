#include "grlib/CGLibTextureBuffer.h"
#include "grlib/CGLibUtilPixel.h"
#include "grlib/CGLibAccUtilTexture.h"
#include "grlib/CGLibAcc2DTexture.h"
#include "classes/grlib/CGLibUniformEtcUtility.h"
#include "nn/os.h"

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

void CGLibUniformEtcUtility::updateData() {}

}  // namespace grlib
