#ifndef GRLIB_CGLIBUTILSH_H
#define GRLIB_CGLIBUTILSH_H

#include "mm/Vec3.h"

namespace grlib {

// a cube map face's u and v directions and its axis, per face (+x, -x, +y, -y, +z, -z): AMD CubeMapGen's table of
// the same name (grlib/CGLibVtxIndex.cpp's unit)
extern mm::Vec3 sgFace2DMapping[6][3];

// cube map texel helpers for spherical harmonics (AMD CubeMapGen's functions of the same names; grlib/CGLibVtxIndex.cpp's
// unit)
class CGLibUtilSH {
public:
    // the unit vector through the centre of texel (u, v) of the face of a size x size cube map
    static void TexelCoordToVect(mm::Vec3& vect, int face, float u, float v, int size);
    // the solid angle texel (u, v) of the face subtends
    static float TexelCoordSolidAngle(int face, float u, float v, int size);
};

}  // namespace grlib

#endif
