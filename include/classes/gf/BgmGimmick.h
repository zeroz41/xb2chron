#ifndef CLASSES_GF_BGMGIMMICK_H
#define CLASSES_GF_BGMGIMMICK_H

#include "classes/gf/BgmTrack.h"

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::BgmGimmick no evidence names yet
class TUnk_B51370 {
public:
    virtual ~TUnk_B51370();
};
// table 0x7100B51338; base at 0x630 unknown (TUnk_B51370)
class BgmGimmick : public ::gf::BgmTrack, public TUnk_B51370 {
public:
    virtual ~BgmGimmick();  // slot 0
    virtual void getTrackName() const;  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 4
};
}  // namespace gf

#endif
