#ifndef CLASSES_GMK_TUNK_B6E340_H
#define CLASSES_GMK_TUNK_B6E340_H

#include "classes/gmk/TGmkList.h"
#include "classes/gmk/GmkSealedStone.h"
#include "mm/mtl/Vector.h"
#include "mm/mtl/FixedQueue.h"
#include "classes/gmk/GmkSealedStoneEnergyEffectManager.h"

namespace gmk {
// table 0x7100B6E340; base TGmkList<GmkSealedStone, ...> (table 0x7100B6EFD8, magic 'SLDS'). 2.0.0's symbols name
// it: the list of kind 0x3F (not in 1.0.0). GmkSet::createGmkLists constructs it inline
// (the base's table, then this one).
// It overrides the destructors (~GmkSealedStoneList, ~GmkSealedStoneList), create (slot 9, create), dispose
// (slot 10, dispose) and update (slot 11, update).
class GmkSealedStoneList : public ::gmk::TGmkList< ::gmk::GmkSealedStone, ::gmk::GmkSealedStone::BdatInfo, 1396984915u, 1u, ::gmk::GmkSealedStoneGob> {
public:
    explicit GmkSealedStoneList(unsigned int updateGmkNumPerFrame)
        : TGmkList(updateGmkNumPerFrame), m_time(0.0f), m_effects(nullptr) {}
    virtual ~GmkSealedStoneList();  // slot 0
    virtual void create(gmk::IGmkList::CreateInfo const& info);  // slot 9 (create)
    virtual void dispose();  // slot 10 (dispose)
    virtual void update(float dt);  // slot 11 (2.0.0's symbols name it)
    // a stone's progress to pass on at a time (2.0.0's symbols name it, by
    // FixedQueue<GmkSealedStoneList::NotifyProgress, 8>::insert; the field names are not the original's)
    struct NotifyProgress {
        GmkSealedStone* m_stone;
        float m_progress;  // what GmkSealedStone::updateProgress gets
        float m_time;      // m_time's value from which update passes it on
    };
    // queues it to pass on progress to stone delay after now, in time order; a full queue drops its least advanced
    // notification first (GmkEnemyWave::updateProgress calls it; 2.0.0's symbols name it)
    void postDelayedUpdateProgress(GmkSealedStone* stone, float progress, float delay) const;
    // 0x228: the notifications in time order (createGmkLists' inline constructor zeroes the count and first, dispose
    // clears it; postDelayedUpdateProgress is const, so mutable; the names are not the original's)
    mutable mm::mtl::FixedQueue<NotifyProgress, 8> m_notifies;
    // 0x2b8: the time update counts up, from 0 at dispose (the name is not the original's)
    float m_time;
    // 0x2c0: create allocates it and fills it (GmkSealedStoneEnergyEffectManager::create); dispose deletes it (the name is not the original's)
    GmkSealedStoneEnergyEffectManager* m_effects;
};
}  // namespace gmk

#endif
