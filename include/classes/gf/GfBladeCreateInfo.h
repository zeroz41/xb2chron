#ifndef CLASSES_GF_GFBLADECREATEINFO_H
#define CLASSES_GF_GFBLADECREATEINFO_H

#include "mm/mtl/FixedVector.h"
#include "gf/SDataBlade.h"

namespace gf {
// what a blade creation is built from (its constructor is gf_blade_manager's). Layout from that constructor and
// from GfMenuObjBladeCreate's destructor, which clears these four FixedVectors (sizes at 0x208, 0x250, 0x260,
// 0xA30) in reverse order. The element types are not known yet: 4-byte placeholders that fill the same bytes.
class GfBladeCreateInfo {
public:
    GfBladeCreateInfo();
    void clear();
    // the driver and core crystal GfBladeCreate::setupDriver / setupCoreCrystal store (the names are not the
    // original's); clear zeroes both with one store
    unsigned int m_driver;
    unsigned int m_coreCrystal;
    // GfBladeCreate::setupAddBooster pushes the booster item here (asserting `size() < capacity()`, 0x80)
    mm::mtl::FixedVector<unsigned int, 0x80> m_boosters;
    // the ideas the boosters raise: GfBladeCreate::setupAddBooster adds each booster's GfBdatItem::getBoosterIdea to
    // its category's level (SDataIdea::setLevel); the constructor zeroes it. The name is not the original's.
    SDataIdea m_idea;
    // a FixedVector whose size is at 0x250 (element type unknown: 4-byte placeholders that fill the same bytes)
    mm::mtl::FixedVector<unsigned int, 8> pad_230;
    mm::mtl::FixedVector<unsigned int, 2> pad_258;
    unsigned char pad_268[0x748];
    mm::mtl::FixedVector<unsigned int, 0x20> pad_9B0;
};

// the blade creation GfMenuObjBladeCreate holds (its constructor only constructs the base)
class GfBladeCreate : public GfBladeCreateInfo {
public:
    GfBladeCreate();
    void clear();
    void setupDriver(unsigned int driver);
    // stores the item when GfItemUtil::isValidCrystal accepts it
    bool setupCoreCrystal(unsigned int item);
    // adds a booster item (m_boosters) and raises its idea category's level by its idea value (m_idea)
    void setupAddBooster(unsigned int item);
};
}  // namespace gf

#endif
