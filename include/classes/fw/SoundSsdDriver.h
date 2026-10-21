#ifndef CLASSES_FW_SOUNDSSDDRIVER_H
#define CLASSES_FW_SOUNDSSDDRIVER_H

#include "classes/fw/ISoundDriver.h"

namespace fw { class SoundCategory; }
namespace fw { class SoundCategoryDebugInfo; }
namespace fw { class SoundHandleDebugInfo; }
namespace fw { class SoundOutputType; }
namespace fw { class SoundPack; }
namespace fw { class SoundPlayInfo; }
namespace fw { class SoundResult; }
namespace fw { class SoundVolumeType; }
namespace fw { class UpdateInfo; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace fw {
// a base of fw::SoundSsdDriver no evidence names yet
class TUnk_B430B8 {
public:
    virtual ~TUnk_B430B8();
};
// table 0x7100B42EF0; base at 0x8 unknown (TUnk_B430B8)
class SoundSsdDriver : public ::fw::ISoundDriver, public TUnk_B430B8 {
public:
    class SoundAllocator;
    virtual ~SoundSsdDriver();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void finalize();  // slot 3
    virtual void updateDebugInfo(mm::mtl::FixedVector<fw::SoundHandleDebugInfo, 128ul>&, mm::mtl::FixedVector<fw::SoundCategoryDebugInfo, 18ul>&);  // slot 4
    virtual void setListeningPoint(mm::Mat44 const&);  // slot 5
    virtual void getListeningPoint() const;  // slot 6
    virtual void setMasterVolume(float);  // slot 7
    virtual void setCategoryVolume(fw::SoundCategory, float, float);  // slot 8
    virtual void getCategoryVolume(fw::SoundCategory) const;  // slot 9
    virtual void setCategoryMute(fw::SoundCategory, bool, float);  // slot 10
    virtual void setCategoryPitch(fw::SoundCategory, float, float);  // slot 11
    virtual void setOutputMode(fw::SoundOutputType);  // slot 12
    virtual void addCategory(fw::SoundCategory, float, char const*);  // slot 13
    virtual void removeCategory(fw::SoundCategory);  // slot 14
    virtual void pauseCategory(fw::SoundCategory, bool, float);  // slot 15
    virtual bool isDeviceEnable() const;  // slot 16
    virtual void playBgm(char const*, float, bool, int, fw::SoundCategory);  // slot 17
    virtual void startBgm(unsigned int);  // slot 18
    virtual void stopBgm(unsigned int, float);  // slot 19
    virtual void stopBgmAll();  // slot 20
    virtual void playVoice(char const*, float, bool, fw::SoundCategory);  // slot 21
    virtual void startVoice(unsigned int);  // slot 22
    virtual void stopVoice(unsigned int, float);  // slot 23
    virtual void playSe(char const*, fw::SoundPack*, float, fw::SoundCategory);  // slot 24
    virtual void playSe(unsigned int, fw::SoundPack*, float, fw::SoundCategory);  // slot 25
    virtual void playSeEx(fw::SoundPlayInfo const&, fw::SoundResult&);  // slot 26
    virtual void stopSe(unsigned int, float);  // slot 27
    virtual void isValid(unsigned int) const;  // slot 28
    virtual void isPlaying(unsigned int) const;  // slot 29
    virtual void isPreparing(unsigned int) const;  // slot 30
    virtual void isReady(unsigned int) const;  // slot 31
    virtual void isLoop(unsigned int);  // slot 32
    virtual void isLoop(unsigned int, fw::SoundPack*);  // slot 33
    virtual void isPause(unsigned int) const;  // slot 34
    virtual void setCategory(unsigned int, fw::SoundCategory);  // slot 35
    virtual void getCategory(unsigned int);  // slot 36
    virtual void setVolume(unsigned int, float, float);  // slot 37
    virtual void getVolume(unsigned int, fw::SoundVolumeType);  // slot 38
    virtual void setPitch(unsigned int, float, float);  // slot 39
    virtual void setPan(unsigned int, float, float);  // slot 40
    virtual void setPos(unsigned int, mm::Vec3 const&);  // slot 41
    virtual void setPlayTime(unsigned int, float);  // slot 42
    virtual void getPlayTime(unsigned int, float&);  // slot 43
    virtual void getTotalTime(unsigned int, float&);  // slot 44
    virtual void setRemainLoopCount(unsigned int, int);  // slot 45
    virtual void getRemainLoopCount(unsigned int, int&);  // slot 46
    virtual void pause(unsigned int, bool, float);  // slot 47
    virtual void stopAll();  // slot 48
    virtual void stopVoiceAll();  // slot 49
    virtual void stopSeAll();  // slot 50
    virtual void pauseAll(bool, float);  // slot 51
    virtual void findSe(char const*) const;  // slot 52
    virtual void attachPoolMemory(void*, unsigned int);  // slot 53
    virtual void detachPoolMemory(void*, unsigned int);  // slot 54
};
}  // namespace fw

#endif
