#ifndef CLASSES_GF_BGMEVENT_H
#define CLASSES_GF_BGMEVENT_H

#include "classes/gf/BgmTrack.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class BgmEvent; enum GEV : int; }

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
    // 1.0.0's out-of-line member (3.0.1 inlines it into GfFieldBgm::gevPlayEvent)
    void gevPlayEvent(GEV gev, unsigned int) {
        if (gev == GEV(13)) {
            m_requested = false;
            m_requestNo = 0;
        }
    }
    // 2.0.0's symbols name it. What it does: 1.0.0's checkStopByHandOver / updatePlaying / beginPlay sequence.
    void updateEventBgm(const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: when GfGameManager::isGameTypeIra() holds and m_overTime is negative, sets
    // m_overTimeStop.
    void setBgmClearByStopBgm();
    // 3.0.1's symbol names it. What it does: when GfEvtBgm's BGM changed from the one entry 0 plays, stops the
    // track (fading over m_fadeTime when m_useFadeTime, else 0.5, or 1 in theater mode for a set flag pair);
    // counts m_overTime down outside events and then fades the event BGM out
    void updatePlaying(const fw::UpdateInfo& info);

    unsigned char pad_638[0x4C];
    // the time updatePlaying stops the track over when m_useFadeTime is set (the name is not the original's)
    float m_fadeTime;
    unsigned char pad_688[0xC];
    // cancelOverTime clears it (the name is not the original's)
    float m_overTime;
    unsigned char pad_698[0x2];
    // updatePlaying stops over m_fadeTime instead of 0.5 while it is set (the name is not the original's)
    bool m_useFadeTime;
    unsigned char pad_69B[0x5];
    // cleared by gevPlayEvent on GEV 13 (the name is not the original's)
    bool m_requested;
    unsigned char pad_6A1[0x7F];
    // cleared by gevPlayEvent on GEV 13 (the name is not the original's)
    unsigned int m_requestNo;
    // set by setBgmClearByStopBgm (the name is not the original's)
    bool m_overTimeStop;
};
}  // namespace gf

#endif
