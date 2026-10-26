#ifndef CLASSES_GF_GFBLADECREATEINFO_H
#define CLASSES_GF_GFBLADECREATEINFO_H

#include "mm/mtl/FixedVector.h"

namespace gf {
// what a blade creation is built from (its constructor is gf_blade_manager's). Layout from that constructor and
// from GfMenuObjBladeCreate's destructor, which clears these four FixedVectors (sizes at 0x208, 0x250, 0x260,
// 0xA30) in reverse order. The element types are not known yet: 4-byte placeholders that fill the same bytes.
class GfBladeCreateInfo {
public:
    GfBladeCreateInfo();
    mm::mtl::FixedVector<unsigned int, 0x82> pad_0;
    mm::mtl::FixedVector<unsigned int, 0x10> pad_210;
    mm::mtl::FixedVector<unsigned int, 2> pad_258;
    unsigned char pad_268[0x748];
    mm::mtl::FixedVector<unsigned int, 0x20> pad_9B0;
};

// the blade creation GfMenuObjBladeCreate holds (its constructor only constructs the base)
class GfBladeCreate : public GfBladeCreateInfo {
public:
    GfBladeCreate();
};
}  // namespace gf

#endif
