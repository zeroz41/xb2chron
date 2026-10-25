#ifndef GRLIB_CGLIBUNIBASEUTILITY_H
#define GRLIB_CGLIBUNIBASEUTILITY_H

#include "grlib/CGLibDecShader.h"

namespace mm {
class Mat44;
class Vec3;
class Vec4;
}  // namespace mm

namespace grlib {
// Writers of uniform-buffer contents (grlib/CGLibUniBaseUtility.cpp): each copies a value into the float slots
// of a uniform block, the matrices transposed.
void ShdInstancePosMatrix3x4Set(float* pDst, const mm::Mat44& mat, float w);
void ShdF32TransposeMat34(float* pDst, const float* pSrc);
void ShdMat44SetMat44(float* pDst, const mm::Mat44& mat);
void ShdMat44TransposeMat34(float* pDst, const mm::Mat44& mat);
void ShdMat44TransposeMat44(float* pDst, const mm::Mat44& mat);
void ShdMat44SetMat44Array(float* pDst, const mm::Mat44* pMat, int num);
void ShdMat44TransposeMat44Array(float* pDst, const mm::Mat44* pMat, int num);
void ShdF32SetF32Array(float* pDst, const float* pSrc, int num);
void ShdF32SetVec4(float* pDst, const float* pSrc);
void ShdVec3SetVec3(float* pDst, const mm::Vec3& v);
void ShdVec4SetVec4(float* pDst, const mm::Vec4& v);
void ShdS32SetIVec4(int* pDst, const int* pSrc);
void ShdU32SetUVec4(unsigned int* pDst, const unsigned int* pSrc);

// the base of the uniform-block writers (CGLibUniformEtcUtility): a declared shader's uniform block chosen by
// name or location, written at value offsets into the buffer getBuff returns (offset -1: the value is absent).
// The field names are not the original's.
class CGLibUniBaseUtility {
public:
    CGLibUniBaseUtility(const CGLibDecShader* pDecShader)
        : m_pDecShader(pDecShader), m_location(-1), m_size(0), m_isSet(false) {}
    virtual ~CGLibUniBaseUtility() {}  // slot 0
    virtual unsigned char* getBuff() = 0;  // slot 2
    virtual void updateData() = 0;  // slot 3
    virtual void setUniformBlock() = 0;  // slot 4
    virtual void setStorageBuffer() = 0;  // slot 5
    virtual void setMoveMem() = 0;  // slot 6

    void setF32SetMat44(unsigned int ofs, const float* pSrc);
    void setMat44SetMat44(unsigned int ofs, const mm::Mat44& mat);
    void setMat44SetMat34(unsigned int ofs, const mm::Mat44& mat);
    void setF32SetF32Array(unsigned int ofs, const float* pSrc, int num);
    void setF32SetVec4(unsigned int ofs, const float* pSrc);
    void setF32SetVec4Array(unsigned int ofs, const float* pSrc, int num);
    void setVec4SetVec4(unsigned int ofs, const mm::Vec4& v);
    void setS32SetIVec4(unsigned int ofs, int* pSrc);
    void setU32SetUVec4(unsigned int ofs, unsigned int* pSrc);
    void setUseUniformBlock(const char* name);
    void setUseUniformBlock(unsigned int location);

    const CGLibDecShader* m_pDecShader;  // 0x8
    unsigned int m_location;  // 0x10
    unsigned int m_size;  // 0x14, the block's size at m_location
    bool m_isSet;  // 0x18, cleared when a block is chosen
};
}  // namespace grlib

#endif
