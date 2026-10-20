#ifndef CLASSES_GF_BGMFIELD_H
#define CLASSES_GF_BGMFIELD_H

#include "classes/gf/BgmTrack.h"

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::BgmField no evidence names yet
class TUnk_B51318 {
public:
    virtual ~TUnk_B51318();
};
// table 0x7100B512E0; base at 0x630 unknown (TUnk_B51318)
class BgmField : public ::gf::BgmTrack, public TUnk_B51318 {
public:
    virtual ~BgmField();  // slot 0
    virtual void getTrackName() const;  // slot 2
    virtual void update(fw::UpdateInfo const&);  // slot 4
};
}  // namespace gf

#endif
