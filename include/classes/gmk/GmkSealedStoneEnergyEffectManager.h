#ifndef CLASSES_GMK_GMKSEALEDSTONEENERGYEFFECTMANAGER_H
#define CLASSES_GMK_GMKSEALEDSTONEENERGYEFFECTMANAGER_H

#include "mm/Vec3.h"
#include "mm/mtl/Vector.h"

namespace gmk {
// 2.0.0's symbols name it (and Vector<GmkSealedStoneEnergyEffectManager::EffectInfo>, the vector create grows). A
// class with no table, 0x30 bytes (GmkSealedStoneList::create's `new`, cited from gmk_sealed_stone_impl.h): a vector
// of 0x60-byte entries, each holding an fw::EffectManager handle at 0x40. The field names are not the original's.
class GmkSealedStoneEnergyEffectManager {
public:
    // the layout of copy_construct_n<EffectInfo> (four Vec3s, 8 bytes copied as one, a Vec3), as
    // gf::GfFobjGottenEffectManager::EffectInfo's
    struct EffectInfo {
        mm::Vec3 m_points[4];         // update moves the effect along them (the name is not the original's)
        unsigned int m_effectHandle;  // 0x40: dispose kills it
        float m_time;                 // 0x44: update adds its time step; past 0.8 the entry ends (the name is not the original's)
        mm::Vec3 m_targetPos;         // 0x50: update reads it against m_points[3] (the name is not the original's)
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
    // 2.0.0's symbols name it; GmkSealedStoneList::update calls it while it exists
    void update(float dt);
    // what create finds as "ma40a_01_140_dlc" in the field's effect pack (fw::EffectManager::search; the name is not
    // the original's)
    void* m_effectRes;
    mm::mtl::Vector<EffectInfo> m_entries;  // 0x8
};
}  // namespace gmk

#endif
