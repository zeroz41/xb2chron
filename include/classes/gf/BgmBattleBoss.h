#ifndef CLASSES_GF_BGMBATTLEBOSS_H
#define CLASSES_GF_BGMBATTLEBOSS_H

#include "classes/gf/BgmTrack.h"

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::BgmBattleBoss no evidence names yet
class TUnk_B51268 {
public:
    virtual ~TUnk_B51268();
};
// table 0x7100B51230; base at 0x630 unknown (TUnk_B51268)
class BgmBattleBoss : public ::gf::BgmTrack, public TUnk_B51268 {
public:
    virtual ~BgmBattleBoss();  // slot 0
    virtual void getTrackName() const;  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 4
};
}  // namespace gf

#endif
