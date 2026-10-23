#ifndef GRLIB_CGLIBUNIBASEUTILITY_H
#define GRLIB_CGLIBUNIBASEUTILITY_H

namespace mm {
class Mat44;
class Vec4;
}  // namespace mm

namespace grlib {
// Writers of uniform-buffer contents (grlib/CGLibUniBaseUtility.cpp): each copies a value into the float slots
// of a uniform block, the matrices transposed.
void ShdMat44TransposeMat34(float* pDst, const mm::Mat44& mat);
void ShdMat44TransposeMat44(float* pDst, const mm::Mat44& mat);
void ShdMat44TransposeMat44Array(float* pDst, const mm::Mat44* pMat, int num);
void ShdF32SetF32Array(float* pDst, const float* pSrc, int num);
void ShdF32SetVec4(float* pDst, const float* pSrc);
void ShdVec4SetVec4(float* pDst, const mm::Vec4& v);
}  // namespace grlib

#endif
