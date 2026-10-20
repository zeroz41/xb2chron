#ifndef CLASSES_GF_BGMBATTLE_H
#define CLASSES_GF_BGMBATTLE_H

#include "classes/gf/BgmTrack.h"

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::BgmBattle no evidence names yet
class TUnk_B51210 {
public:
    virtual ~TUnk_B51210();
};
// table 0x7100B511D8; base at 0x630 unknown (TUnk_B51210)
class BgmBattle : public ::gf::BgmTrack, public TUnk_B51210 {
public:
    virtual ~BgmBattle();  // slot 0
    virtual void getTrackName() const;  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 4
};
}  // namespace gf

#endif
