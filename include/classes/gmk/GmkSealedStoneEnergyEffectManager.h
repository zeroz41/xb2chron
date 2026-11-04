#ifndef CLASSES_GMK_GMKSEALEDSTONEENERGYEFFECTMANAGER_H
#define CLASSES_GMK_GMKSEALEDSTONEENERGYEFFECTMANAGER_H

#include "mm/mtl/Vector.h"

namespace gmk {
// 2.0.0's symbols name it (and Vector<GmkSealedStoneEnergyEffectManager::EffectInfo>, the vector create grows). A
// class with no table, 0x30 bytes (GmkSealedStoneList::create's `new`, cited from gmk_sealed_stone_impl.h): a vector
// of 0x60-byte entries, each holding an fw::EffectManager handle at 0x40. The field names are not the original's.
class GmkSealedStoneEnergyEffectManager {
public:
    struct EffectInfo {
        unsigned char pad_0[0x40];
        unsigned int m_effectHandle;  // 0x40: dispose kills it
        unsigned char pad_44[0x1c];
    };
    // the original's constructor stores only the vector (nothing at 0x0)
    GmkSealedStoneEnergyEffectManager() {}
    ~GmkSealedStoneEnergyEffectManager() { dispose(); }
    // 2.0.0's symbols name it. GmkSealedStoneList::dispose and this destructor call it. What it does: when the vector
    // holds entries, kills each entry's effect (fw::EffectManager::kill) and frees the vector (Vector::destroy, inline).
    void dispose();
    // 2.0.0's symbols name it. GmkSealedStoneList::create (fn_71005BA900) tail-calls it with the object it has just
    // allocated. What it does: fills the entries from the field's effect pack (gf::GfFieldManager::getEffectPack,
    // fw::EffectManager::search; asserts; calls dispose and Vector<EffectInfo>::expand).
    void create();
    void* pad_0;
    mm::mtl::Vector<EffectInfo> m_entries;  // 0x8
};
}  // namespace gmk

#endif
