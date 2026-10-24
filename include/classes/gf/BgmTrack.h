#ifndef CLASSES_GF_BGMTRACK_H
#define CLASSES_GF_BGMTRACK_H

#include "gf/SoundHandle.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixedVector.h"

namespace fw { class UpdateInfo; }

namespace gf {
class BgmTrack;
class GfFieldBgm;
struct ExecFadeParam;

// a BGM condition entry (1.0.0's BGMCOND::BGMCOND clears +0, constructs the SoundHandle at +4, clears +0xC, +0x10,
// +0x14 and +0x54/+0x58); size 0x5C
struct BGMCOND {
    unsigned char pad_0[0x4];
    SoundHandle m_handle;
    unsigned char pad_C[0x4C];
    // which of the BGM condition row's set conditions plays (the bgmvol checks hand it to
    // BgmTrack::getBgmConditionConditionID as the index; the name is not the original's)
    unsigned int m_conditionNo;
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
    virtual ~BgmTrack();  // slot 0
    virtual const char* getTrackName() const = 0;  // slot 2
    virtual bool isPlaying() const;  // slot 3
    virtual void update(fw::UpdateInfo const&);  // slot 4
    float getPlayTime() const;
    float getTotalTime() const;
    // the n-th set condition of the BGM condition row (1.0.0's symbol names it)
    unsigned int getBgmConditionConditionID(unsigned int id, unsigned int index) const;
    unsigned int getBgmConditionBgmID(unsigned int id, unsigned int index) const;
    // 1.0.0's out-of-line getter (3.0.1 inlines it)
    unsigned int getBgmCondID() const { return m_bgmCondID; }

    unsigned char pad_8[0x170];
    mm::mtl::FixedVector<BgmVolumeFade, 12> m_volumeFades;  // 1.0.0's addVolumeFade asserts size() < capacity()
    unsigned char pad_3C0[0xD0];
    // element type unproven (its size fits 0x170 = 4 x BGMCOND); ~BgmTrack clears its count at +0x600
    mm::mtl::FixedVector<BGMCOND, 4> m_bgmConds;
    unsigned int m_bgmCondID;  // 1.0.0's getBgmCondID reads it
    unsigned char pad_60C[0x14];
    GfFieldBgm* m_fieldBgm;  // the owner (the constructors take it)
    unsigned char pad_628[0x8];
};
}  // namespace gf

#endif
