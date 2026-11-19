#ifndef CLASSES_GF_BGMEVENT_H
#define CLASSES_GF_BGMEVENT_H

#include "classes/gf/BgmTrack.h"
#include "classes/gf/GfEvtBgm.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class BgmEvent; enum GEV : int; }

namespace gf {
// table 0x7100B51288; a BgmTrack at 0 (GfEvtBgm::getPlayBgmTime hands the singleton to BgmTrack::getPlayTime as
// it is), its PtrSingleton at 0x630 (1.0.0's constructor stores PtrSingleton<BgmEvent>'s table there and the
// object less 0x630 in its s_instance)
class BgmEvent : public BgmTrack, public ::mm::mtl::PtrSingleton< ::gf::BgmEvent> {
public:
    // inline: GfFieldBgm's constructor builds it in place (the symbols have no out-of-line copy)
    explicit BgmEvent(GfFieldBgm* fieldBgm) : BgmTrack(fieldBgm, false), m_setup(), m_playBgmName(),
                                              m_overTimeStop(false) {}
    virtual ~BgmEvent();  // slot 0
    virtual const char* getTrackName() const;  // slot 2
    virtual bool isPlaying() const;  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 4
    void cancelOverTime();
    // 1.0.0's out-of-line member (3.0.1 inlines it into GfFieldBgm::gevPlayEvent)
    void gevPlayEvent(GEV gev, unsigned int) {
        if (gev == GEV(13)) {
            m_playBgmName.clear();
        }
    }
    // 3.0.1's symbols name them. checkStopByHandOver: while GfEvtBgm's setup has pad_61 set and the track plays
    // (outside theater mode), hands the entries over to the field or gimmick track when the BGM file's condition is
    // theirs, else to the boss track (stopped at once for a "Silent" BGM, else GfGameScene's forced boss BGM set).
    // beginPlay: rebuilds the volume fades from GfEvtBgm's setup and starts its BGM (or the one taken over from the
    // track that plays) unless it already plays.
    void checkStopByHandOver();
    void beginPlay();
    // 2.0.0's symbols name it. What it does: 1.0.0's checkStopByHandOver / updatePlaying / beginPlay sequence.
    void updateEventBgm(const fw::UpdateInfo& info);
    // 2.0.0's symbols name it. What it does: when GfGameManager::isGameTypeIra() holds and m_setup.m_overTime is
    // negative, sets m_overTimeStop.
    void setBgmClearByStopBgm();
    // 3.0.1's symbol names it. What it does: when GfEvtBgm's BGM changed from the one entry 0 plays, stops the
    // track (fading over m_setup.pad_4c when m_setup.pad_62 is set, else 0.5, or 1 in theater mode for a set flag
    // pair); counts m_setup.m_overTime down outside events and then fades the event BGM out
    void updatePlaying(const fw::UpdateInfo& info);

    // a copy of GfEvtBgm's setup (beginPlay assigns GfEvtBgm::m_setup to it: the name's strcpy, then 0x22 bytes
    // copied; the constructor builds it with EventBgmSetup's constructor's stores). updatePlaying stops over its
    // pad_4c while pad_62 is set, cancelOverTime clears its m_overTime (the name is not the original's)
    EventBgmSetup m_setup;
    // the BGM beginPlay last started (it returns when the new name equals it; gevPlayEvent clears it on GEV 13;
    // LEN 128 by the `m_nLen < LEN` check; the name is not the original's)
    mm::mtl::FixStr<128> m_playBgmName;
    // set by setBgmClearByStopBgm (the name is not the original's)
    bool m_overTimeStop;
};
}  // namespace gf

#endif
