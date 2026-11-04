#ifndef CLASSES_GMK_TUNK_B6ED38_H
#define CLASSES_GMK_TUNK_B6ED38_H

#include "classes/gmk/TGmkList.h"
#include "classes/gmk/GmkBattleChallengeReward.h"

namespace gmk {
// table 0x7100B6ED38; base TGmkList<GmkBattleChallengeReward, ...> (table 0x7100B6EDE0, magic 'BCRW'). Placeholder name: the
// list of kind 0x3C, new in 3.0.1; nothing in 1.0.0 names it. GmkSet::createGmkLists constructs it inline
// (the base's table, then this one).
// It overrides the destructor and getInst (slot 6, fn_71005CF9E8: the base's code).
class GmkBattleChallengeRewardList : public ::gmk::TGmkList< ::gmk::GmkBattleChallengeReward, ::gmk::GmkBattleChallengeReward::BdatInfo, 1465008962u, 3u, ::gmk::GmkBattleChallengeRewardGob> {
public:
    explicit GmkBattleChallengeRewardList(unsigned int updateGmkNumPerFrame)
        : TGmkList(updateGmkNumPerFrame) {}
    // slot 0: inline, so its D2 is the base's (the table's slot 0 is TGmkList's D2)
    virtual ~GmkBattleChallengeRewardList() {}
    // slot 6 (fn_71005CF9E8): its own copy of the base's code (an inline override, like GmkEnemyList's)
    virtual gmk::AGmkBase* getInst(unsigned int index) const { return TGmkList::getInst(index); }
};
}  // namespace gmk

#endif
