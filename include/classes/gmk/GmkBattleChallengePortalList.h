#ifndef CLASSES_GMK_TUNK_B6EE88_H
#define CLASSES_GMK_TUNK_B6EE88_H

#include "classes/gmk/TGmkList.h"
#include "classes/gmk/GmkBattleChallengePortal.h"

namespace gmk {
// table 0x7100B6EE88; base TGmkList<GmkBattleChallengePortal, ...> (table 0x7100B6EF30, magic 'BCRP'). Placeholder name: the
// list of kind 0x3D, new in 3.0.1; nothing in 1.0.0 names it. GmkSet::createGmkLists constructs it inline
// (the base's table, then this one).
// It overrides the deleting destructor.
class GmkBattleChallengePortalList : public ::gmk::TGmkList< ::gmk::GmkBattleChallengePortal, ::gmk::GmkBattleChallengePortal::BdatInfo, 1347568450u, 3u, ::gmk::GmkBattleChallengePortalGob> {
public:
    explicit GmkBattleChallengePortalList(unsigned int updateGmkNumPerFrame)
        : TGmkList(updateGmkNumPerFrame) {}
    // slot 0: inline, so its D2 is the base's (the table's slot 0 is TGmkList's D2)
    virtual ~GmkBattleChallengePortalList() {}
};
}  // namespace gmk

#endif
