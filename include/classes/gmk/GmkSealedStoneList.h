#ifndef CLASSES_GMK_TUNK_B6E340_H
#define CLASSES_GMK_TUNK_B6E340_H

#include "classes/gmk/TGmkList.h"
#include "classes/gmk/GmkSealedStone.h"
#include "mm/mtl/Vector.h"
#include "classes/gmk/GmkSealedStoneEnergyEffectManager.h"

namespace gmk {
// table 0x7100B6E340; base TGmkList<GmkSealedStone, ...> (table 0x7100B6EFD8, magic 'SLDS'). Placeholder name: the
// list of kind 0x3F, new in 3.0.1; nothing in 1.0.0 names it. GmkSet::createGmkLists constructs it inline
// (the base's table, then this one).
// It overrides the destructors (fn_71005C41F0, fn_71005C4224), create (slot 9, fn_71005BA900), dispose
// (slot 10, fn_71005BABD8) and update (slot 11, update).
class GmkSealedStoneList : public ::gmk::TGmkList< ::gmk::GmkSealedStone, ::gmk::GmkSealedStone::BdatInfo, 1396984915u, 1u, ::gmk::GmkSealedStoneGob> {
public:
    explicit GmkSealedStoneList(unsigned int updateGmkNumPerFrame)
        : TGmkList(updateGmkNumPerFrame), pad_2a8(nullptr), pad_2b0(nullptr), pad_2b8(0),
          m_effects(nullptr) {}
    virtual ~GmkSealedStoneList();  // slot 0
    virtual void create(gmk::IGmkList::CreateInfo const& info);  // slot 9 (fn_71005BA900)
    virtual void dispose();  // slot 10 (fn_71005BABD8)
    virtual void update(float dt);  // slot 11 (2.0.0's symbols name it)
    unsigned char pad_228[0x80];  // fields: size from createGmkLists' `new` (0x2d0)
    // Placeholder members (nothing names them): createGmkLists' inline constructor zeroes all four (8-, 8-, 4- and
    // 8-byte stores). Its dispose (fn_71005BABD8) frees m_effects and zeroes it, and zeroes pad_2a8, pad_2b0 and pad_2b8 again.
    void* pad_2a8;
    void* pad_2b0;
    int pad_2b8;
    // 0x2c0: create allocates it and fills it (GmkSealedStoneEnergyEffectManager::create); dispose deletes it (the name is not the original's)
    GmkSealedStoneEnergyEffectManager* m_effects;
};
}  // namespace gmk

#endif
