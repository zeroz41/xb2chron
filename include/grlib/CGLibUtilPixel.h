#ifndef GRLIB_CGLIBUTILPIXEL_H
#define GRLIB_CGLIBUTILPIXEL_H

namespace grlib {

// pixel conversions (grlib/CGLibVtxIndex.cpp's unit)
class CGLibUtilPixel {
public:
    static float convF16toF32(unsigned short value);
    static unsigned short convF32toF16(float value);
};

}  // namespace grlib

#endif
