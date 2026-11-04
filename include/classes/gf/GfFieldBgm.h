#ifndef CLASSES_GF_GFFIELDBGM_H
#define CLASSES_GF_GFFIELDBGM_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfFieldBgm; class BgmTrack; class MapjumpCallbackInfo; enum GEV : int; }

namespace gf {
// table 0x7100B511B8
class GfFieldBgm : public ::mm::mtl::PtrSingleton< ::gf::GfFieldBgm> {
public:
    GfFieldBgm();  // GfFieldSound::initialize creates it
    virtual ~GfFieldBgm();  // slot 0
    void update(const fw::UpdateInfo& info);  // GfFieldSound::update forwards to it
    // stops every track and resets its volumes (1.0.0's symbol, called from the same place: GfFieldSound::clear)
    void destroy();
    void stopBgmForDebug(bool stop);
    void setGimmickBgmID(unsigned int id);
    void setRscBattleBgmID(unsigned int id);
    void gevBattleEnd();
    void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);
    void gevPause(unsigned int prev, unsigned int cur);
    // 1.0.0's out-of-line member (3.0.1 inlines it into gevPause)
    void setPause(bool pause);
    void gevPlayEvent(GEV gev, unsigned int param);
    // 2.0.0's symbols name it. A member: GfPlayComEvent::gevPlayEvent calls
    // it on GfFieldBgm's instance (it then ignores this). What it does: hands the name to gf::BgmField's instance
    // (BgmTrack::playForEventTheater) when there is one; its only caller passes GfPlayComEvent's BGM name on GEV 14.
    void playFieldBgmForce(const char* name);
    bool isBossBgmCopied() const;  // 1.0.0's symbol at the same place, with the same caller (GfFieldSound::gevBattleEnd)
    // the playing track with the highest volume (1.0.0's symbol), none when nothing plays
    BgmTrack* getCurrentPlayBgmTrack();
    // 1.0.0's out-of-line getters (3.0.1 inlines them)
    unsigned int getRscFieldBgmID() const;
    unsigned int getRscGimmickBgmID() const { return m_rscGimmickBgmID; }
    unsigned int getRscBossBattleBgmID() const { return m_rscBossBattleBgmID; }
    unsigned int getRscBattleBgmID() const { return m_rscBattleBgmID; }
    bool isDisableFieldBgmChange() const { return m_disableFieldBgmChange; }

    // the tracks the constructor creates (field, battle, boss, gimmick, event; gevPause pauses each)
    mm::mtl::FixedVector<BgmTrack*, 16> m_tracks;
    unsigned int m_rscBossBattleBgmID;  // 1.0.0's getRscBossBattleBgmID reads it
    // cleared when setRscBattleBgmID sets a boss battle BGM id (the name is not the original's)
    // update counts it up (signed) while the boss BGM waits to play and drops the boss id after 300 frames
    int m_bossBattleBgmWait;
    unsigned int m_rscBattleBgmID;  // 1.0.0's getRscBattleBgmID reads it
    unsigned int m_rscGimmickBgmID;  // 1.0.0's getRscGimmickBgmID reads it
    unsigned int m_gimmickBgmID;  // setGimmickBgmID stores it
    // set to 30 when setGimmickBgmID clears a set gimmick BGM (the name is not the original's)
    // update counts it down as signed and applies m_gimmickBgmID when it reaches 0
    int m_gimmickBgmClearWait;
    bool m_disableFieldBgmChange;  // 1.0.0's isDisableFieldBgmChange reads it
    // bgmvolFadeDeadSequence fades out while it is set (the name is not the original's)
    bool m_deadSequence;
};
}  // namespace gf

#endif
