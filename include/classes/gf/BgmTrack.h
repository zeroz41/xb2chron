#ifndef CLASSES_GF_BGMTRACK_H
#define CLASSES_GF_BGMTRACK_H

#include "gf/SoundHandle.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixStr.h"

namespace fw { class UpdateInfo; }

namespace gf {
class BgmTrack;
class GfFieldBgm;
struct ExecFadeParam;

// a BGM condition entry (1.0.0's BGMCOND::BGMCOND clears +0, constructs the SoundHandle at +4, clears +0xC, +0x10,
// +0x14 and +0x54/+0x58); size 0x5C
struct BGMCOND {
    // the values 1.0.0's BGMCOND::clear zeroes besides the handle and the name: the volume (BgmTrack::getVolume
    // returns the first entry's with a valid handle), +0xC (unproven), +0x10/+0x11 (1.0.0's isInvalidPlay counts an
    // entry with no handle as invalid unless +0x11 is set); the names are not the original's
    float m_volume;
    SoundHandle m_handle;
    unsigned int m_playNo;
    bool m_playing;
    bool m_requested;
    // the BGM file it plays (1.0.0's BGMCOND::isSilentPlay compares it with "SilentBgm"; BgmTrack::isPlaying
    // counts an entry with a name as playing; the name is not the original's)
    mm::mtl::FixStr<64> m_bgmFileName;
    // which of the BGM condition row's set conditions plays (the bgmvol checks hand it to
    // BgmTrack::getBgmConditionConditionID as the index; the name is not the original's)
    unsigned int m_conditionNo;
    // BgmTrack's constructor builds one on the stack and inlines this into its four entries
    BGMCOND() : m_volume(0.0f), m_playNo(0), m_playing(false), m_requested(false), m_conditionNo(0) {}

    // 1.0.0's out-of-line BGMCOND::clear (3.0.1 inlines it into BgmTrack::stopCondBGM): the name emptied when set,
    // the handle cleared when valid, the values zeroed
    void clear() {
        if (m_bgmFileName.length() != 0) {
            m_bgmFileName = "";
        }
        if (m_handle.isValid()) {
            m_handle.clear();
        }
        m_volume = 0.0f;
        m_playing = false;
        m_requested = false;
        m_playNo = 0;
    }
};

// one volume fade of a track (1.0.0's BgmTrack::addVolumeFade(func, out, in, flag) stores the invoker and the
// function, then the two times and the flag; the names are not the original's)
struct BgmVolumeFade {
    mm::mtl::Delegate<float(ExecFadeParam&)> m_func;
    float m_fadeOutTime;  // the time the check's fade out takes (used when it returns a negative step)
    float m_fadeInTime;   // the time its fade in takes
    bool m_flag;
};

// what a volume fade check reads (BgmTrack::getPlayVolume builds it on the stack: the track, the frame's update
// info, the fade, the condition entry it plays)
struct ExecFadeParam {
    BgmTrack* m_track;
    const fw::UpdateInfo* m_updateInfo;
    const BgmVolumeFade* m_fade;
    const BGMCOND* m_cond;
};

// table 0x7100B51390
class BgmTrack {
public:
    BgmTrack(GfFieldBgm* fieldBgm, bool battle);
    virtual ~BgmTrack();  // slot 0
    // 1.0.0's out-of-line BgmTrack::addVolumeFade(func, out, in, flag) (3.0.1's constructors inline it): a check
    // added to the volume fades
    void addVolumeFade(float (*func)(ExecFadeParam&), float fadeOutTime, float fadeInTime, bool flag) {
        BgmVolumeFade fade;
        fade.m_func.set(func);
        fade.m_fadeOutTime = fadeOutTime;
        fade.m_fadeInTime = fadeInTime;
        fade.m_flag = flag;
        m_volumeFades.push_back(fade);
    }
    virtual const char* getTrackName() const = 0;  // slot 2
    virtual bool isPlaying() const;  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 4
    void setPause(bool pause);
    void setCategoryApply(unsigned char category);
    float getPlayTime() const;
    float getTotalTime() const;
    // the n-th set condition of the BGM condition row (1.0.0's symbol names it)
    unsigned int getBgmConditionConditionID(unsigned int id, unsigned int index) const;
    unsigned int getBgmConditionBgmID(unsigned int id, unsigned int index) const;
    // 1.0.0's out-of-line getter (3.0.1 inlines it)
    unsigned int getBgmCondID() const { return m_bgmCondID; }

    // placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. What it does: BgmBattle::update calls it
    // with the field BGM's battle BGM id when the track's condition id differs (it sits where 1.0.0's
    // BgmTrack::play(unsigned int) sat, after the constructor; the BgmBattle constructor calls it too)
    void fn_7100263490(unsigned int id);
    // 1.0.0's symbol: 3.0.1's fn_7100263FF0 has the body of 1.0.0's BgmTrack::stopBGM(float) (each entry stopped,
    // the fade pair set to 0/1, the condition id cleared unless m_keepBgmCondID, entry 0's name emptied)
    void stopBGM(float time);
    // 1.0.0's out-of-line symbol (3.0.1 inlines it): the volume of the first entry with a valid handle, else 0
    float getVolume() const {
        for (unsigned long i = 0; i < 4; ++i) {
            if (m_conds[i].m_handle.isValid()) {
                return m_conds[i].m_volume;
            }
        }
        return 0.0f;
    }
    // 1.0.0's symbol: 3.0.1's fn_7100266B18 has the body of 1.0.0's BgmTrack::stopCondBGM(float, BGMCOND&) (the
    // entry's BGM stopped over time when GfSound exists and the handle is valid, then BGMCOND::clear), with the
    // fade time cut to 1 while a theater-mode event is skipped
    void stopCondBGM(float time, BGMCOND& cond);

    // the four condition entries (1.0.0 has FixedArray<BGMCOND, 4>::assign; isPlaying reads 4 entries of 0x5C
    // from +8)
    mm::mtl::FixedArray<BGMCOND, 4> m_conds;
    mm::mtl::FixedVector<BgmVolumeFade, 12> m_volumeFades;  // 1.0.0's addVolumeFade asserts size() < capacity()
    unsigned char pad_3C0[0xD0];
    // element type unproven (its size fits 0x170 = 4 x BGMCOND); ~BgmTrack clears its count at +0x600
    mm::mtl::FixedVector<BGMCOND, 4> m_bgmConds;
    unsigned int m_bgmCondID;  // 1.0.0's getBgmCondID reads it
    // the constructor's flag: BgmBattle and BgmBattleBoss pass true, the other tracks false (the name is not the
    // original's)
    bool m_battle;
    unsigned char pad_60D[0x1];
    // stopBGM keeps m_bgmCondID while it is set (the name is not the original's)
    bool m_keepBgmCondID;
    unsigned char pad_60F[0x1];
    // GfFieldBgm::destroy resets it to 1 with the fade pair (the name is not the original's)
    float m_baseVolume;
    // stopBGM sets them to 0 and 1, GfFieldBgm::destroy both to 1 (the names are not the original's)
    float m_fadeVolume;
    float m_fadeScale;
    unsigned int pad_61C;  // the constructor clears it
    GfFieldBgm* m_fieldBgm;  // the owner (the constructors take it)
    bool m_pause;  // setPause stores it (1.0.0's symbol names the setter)
    // GfFieldBgm::isBossBgmCopied reads it on the boss track (the name is not the original's)
    bool m_copied;
    unsigned char m_category;  // setCategoryApply stores it (the name is not the original's)
    unsigned char pad_62B[0x5];
};
}  // namespace gf

#endif
