#ifndef CLASSES_GF_BGMEVENT_H
#define CLASSES_GF_BGMEVENT_H

#include "classes/gf/BgmTrack.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class BgmEvent; }

namespace gf {
// table 0x7100B51288; a BgmTrack at 0 (GfEvtBgm::getPlayBgmTime hands the singleton to BgmTrack::getPlayTime as
// it is), its PtrSingleton at 0x630 (1.0.0's constructor stores PtrSingleton<BgmEvent>'s table there and the
// object less 0x630 in its s_instance)
class BgmEvent : public BgmTrack, public ::mm::mtl::PtrSingleton< ::gf::BgmEvent> {
public:
    virtual ~BgmEvent();  // slot 0
    virtual const char* getTrackName() const;  // slot 2
    virtual bool isPlaying() const;  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 4
    void cancelOverTime();

    unsigned char pad_638[0x5C];
    // cancelOverTime clears it (the name is not the original's)
    float m_overTime;
};
}  // namespace gf

#endif
