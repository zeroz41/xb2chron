#ifndef CLASSES_GF_GFOBJPROPERTYCHARACTER_H
#define CLASSES_GF_GFOBJPROPERTYCHARACTER_H

#include <string.h>
#include "mm/mtl/Array.h"
#include "classes/gf/GfAllocator.h"
#include "plugin/Bdat.h"

namespace gf {
// no table: the character part of a driver's, blade's or enemy's property (at their 0x88; GfObjProperty's
// m_character points at it). Its constructor is out of line in gf_obj_property (the three constructors call it).
// The member names are not the original's.
class GfObjPropertyCharacter {
public:
    // one entry per row of the BTL_Buff table (the constructor sizes m_buffs by its ID count)
    struct Buff {
        unsigned short pad_0;
        unsigned int pad_4;
    };

    GfObjPropertyCharacter() {
        memset(pad_0, 0, 0xE);  // pad_0 to pad_C
        pad_28 = -1;
        pad_30 = false;
        unsigned char* fp = Bdat::getFP("BTL_Buff");
        if (fp != nullptr && Bdat::getIdCount(fp) != 0) {
            m_buffs.setAllocator(getAllocator(ALLOCATOR(0)));
            m_buffs.reserve(Bdat::getIdCount(fp));
            reset();
        }
    }
    // clears what the constructor clears and every entry of m_buffs (the constructors of the three properties
    // that hold one call it again)
    void reset() {
        memset(pad_0, 0, 0xE);  // pad_0 to pad_C
        pad_28 = -1;
        for (Buff* it = m_buffs.begin(); it != m_buffs.end(); ++it) {
            it->pad_0 = 0;
            it->pad_4 = 0;
        }
    }

    // 0x0..0xE: cleared (as one 14-byte block) by the constructor and reset
    unsigned char pad_0[0x8];
    // added to the UI HP (GfGameUtil::getNowHpForUi) by GfMenuGfObjAdapter::fn_7100340154
    int pad_8;
    unsigned char pad_C[0x2];
    mm::mtl::Array<Buff> m_buffs;  // 0x10
    long pad_28;  // -1 from the constructor and reset
    bool pad_30;  // false from the constructor
};
}  // namespace gf

#endif
