#ifndef GRLIB_CGLIBACCUTILTEXTURE_H
#define GRLIB_CGLIBACCUTILTEXTURE_H

#include "grlib/GrlTypes.h"

namespace grlib { class CGLibTextureBuffer; }

namespace grlib {

// texel reader/writer of a locked texture: setup2DTexutreInfo picks the format's accessors from the s_p*Call
// tables, setInt computes the texel's address (linear or block-linear) and writes it through s_pWriteIntChannel.
// Member names other than the functions' and the tables' are not the original's.
class CGLibAccUtilTexture {
public:
    typedef float (CGLibAccUtilTexture::*ReadF32Func)(unsigned int);
    typedef int (CGLibAccUtilTexture::*ReadIntFunc)(unsigned int);
    typedef void (CGLibAccUtilTexture::*WriteF32Func)(const float*, unsigned int);
    typedef void (CGLibAccUtilTexture::*WriteIntFunc)(const int*, unsigned int);
    typedef void (CGLibAccUtilTexture::*ReadF32ChannelFunc)(float*);
    typedef void (CGLibAccUtilTexture::*WriteIntChannelFunc)(const int*);

    void setInt(const int* value, unsigned int x, unsigned int y);
    // the texel at x, y as floats, into out (2.0.0 names it; 3.0.1's callers inline it)
    void getF32(float* out, unsigned int x, unsigned int y);
    void setup2DTexutreInfo(CGLibTextureBuffer& buffer, unsigned int mipLevel);
    // the block-linear (GOB) layout's parameters for m_texelSize
    void setupFormatParam();
    // index into the s_p*Call tables for a format
    unsigned int getCalcType(GrlSurfaceFormat format) const;
    // channels of a format
    unsigned int getCalcChanel(GrlSurfaceFormat format) const;
    // texel index of x, y (linear or block-linear)
    unsigned int getOfsPixelPos(unsigned int x, unsigned int y) const;
    unsigned int getSquaringPixel(unsigned int pos) const;

    void texaccread_f32_r(float* out);
    void texaccread_f32_rg(float* out);
    void texaccread_f32_rgba(float* out);
    void texaccwrite_int_r(const int* value);
    void texaccwrite_int_rg(const int* value);
    void texaccwrite_int_rgba(const int* value);

    float texaccread_f32_8(unsigned int channel);
    float texaccread_f32_16_float(unsigned int channel);
    float texaccread_f32_16_int(unsigned int channel);
    float texaccread_f32_16_uint(unsigned int channel);
    float texaccread_f32_16_unom(unsigned int channel);
    float texaccread_f32_32_float(unsigned int channel);
    float texaccread_f32_32_int(unsigned int channel);
    float texaccread_f32_32_uint(unsigned int channel);
    float texaccread_f32_err(unsigned int channel);
    int texaccread_int_8(unsigned int channel);
    int texaccread_int_16_float(unsigned int channel);
    int texaccread_int_16_int(unsigned int channel);
    int texaccread_int_16_uint(unsigned int channel);
    int texaccread_int_16_unom(unsigned int channel);
    int texaccread_int_32_float(unsigned int channel);
    int texaccread_int_32_int(unsigned int channel);
    int texaccread_int_32_uint(unsigned int channel);
    int texaccread_int_err(unsigned int channel);
    void texaccwrite_f32_8(const float* value, unsigned int channel);
    void texaccwrite_f32_16_float(const float* value, unsigned int channel);
    void texaccwrite_f32_16_int(const float* value, unsigned int channel);
    void texaccwrite_f32_16_uint(const float* value, unsigned int channel);
    void texaccwrite_f32_16_unom(const float* value, unsigned int channel);
    void texaccwrite_f32_32_float(const float* value, unsigned int channel);
    void texaccwrite_f32_32_int(const float* value, unsigned int channel);
    void texaccwrite_f32_32_uint(const float* value, unsigned int channel);
    void texaccwrite_f32_err(const float* value, unsigned int channel);
    void texaccwrite_int_8(const int* value, unsigned int channel);
    void texaccwrite_int_16_float(const int* value, unsigned int channel);
    void texaccwrite_int_16_int(const int* value, unsigned int channel);
    void texaccwrite_int_16_uint(const int* value, unsigned int channel);
    void texaccwrite_int_16_unom(const int* value, unsigned int channel);
    void texaccwrite_int_32_float(const int* value, unsigned int channel);
    void texaccwrite_int_32_int(const int* value, unsigned int channel);
    void texaccwrite_int_32_uint(const int* value, unsigned int channel);
    void texaccwrite_int_err(const int* value, unsigned int channel);

    // indexed by the format's access type (9 types, the last the error accessor)
    static ReadF32Func s_pReadF32Call[9];
    static ReadIntFunc s_pReadIntCall[9];
    static WriteF32Func s_pWriteF32Call[9];
    static WriteIntFunc s_pWriteIntCall[9];
    // indexed by the channel count - 1 (r, rg, rgba)
    static ReadF32ChannelFunc s_pReadF32Channel[3];
    static WriteIntChannelFunc s_pWriteIntChannel[3];

    ReadF32Func m_pReadF32;            // 0x00
    ReadIntFunc m_pReadInt;            // 0x10
    WriteF32Func m_pWriteF32;          // 0x20
    WriteIntFunc m_pWriteInt;          // 0x30
    unsigned int m_channelNum;         // 0x40
    unsigned int m_texelSize;          // 0x44: bytes
    unsigned int m_channelIdx;         // 0x48: into s_pReadF32Channel/s_pWriteIntChannel
    unsigned int m_width;              // 0x4C
    unsigned int m_height;             // 0x50
    unsigned int m_depth;              // 0x54
    unsigned int m_sliceSize;          // 0x58: texels
    unsigned int m_sectorWidth;        // 0x5C: texels of a 16-byte GOB sector row
    unsigned int m_sectorHeight;       // 0x60
    unsigned int m_unusedParam;        // 0x64: set to 2, read by nothing in 3.0.1
    unsigned int m_gobWidth;           // 0x68: texels of a 32-byte half GOB row
    unsigned int m_gobHeight;          // 0x6C
    unsigned int m_blockHeight;        // 0x70
    unsigned int m_dataSize;           // 0x74
    unsigned char* m_pData;            // 0x78
    unsigned char* m_pTexel;           // 0x80: the texel setInt addressed
    bool m_isLinear;                   // 0x88
};

}  // namespace grlib

#endif
