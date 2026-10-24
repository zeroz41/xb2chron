#ifndef CLASSES_FW_ISOUNDDRIVER_H
#define CLASSES_FW_ISOUNDDRIVER_H

namespace fw { enum SoundCategory : int; }
namespace fw { class SoundCategoryDebugInfo; }
namespace fw { class SoundHandleDebugInfo; }
namespace fw { class SoundOutputType; }
namespace fw { class SoundPack; }
namespace fw { class SoundPlayInfo; }
namespace fw { class SoundResult; }
// what getVolume reads (0: the handle's volume, 1: its distance volume, 2: a third volume; the names are not known)
namespace fw { enum SoundVolumeType : int; }
namespace fw { class UpdateInfo; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace fw {
// table 0x7100B43168
class ISoundDriver {
public:
    virtual ~ISoundDriver() {}  // slot 0
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 2
    virtual void finalize() = 0;  // slot 3
    virtual void updateDebugInfo(mm::mtl::FixedVector<fw::SoundHandleDebugInfo, 128ul>&, mm::mtl::FixedVector<fw::SoundCategoryDebugInfo, 18ul>&) = 0;  // slot 4
    virtual void setListeningPoint(mm::Mat44 const&) = 0;  // slot 5
    virtual const mm::Mat44& getListeningPoint() const = 0;  // slot 6
    virtual void setMasterVolume(float) = 0;  // slot 7
    virtual void setCategoryVolume(fw::SoundCategory, float, float) = 0;  // slot 8
    virtual void getCategoryVolume(fw::SoundCategory) const = 0;  // slot 9
    virtual void setCategoryMute(fw::SoundCategory, bool, float) = 0;  // slot 10
    virtual void setCategoryPitch(fw::SoundCategory, float, float) = 0;  // slot 11
    virtual void setOutputMode(fw::SoundOutputType) = 0;  // slot 12
    virtual void addCategory(fw::SoundCategory, float, char const*) = 0;  // slot 13
    virtual void removeCategory(fw::SoundCategory) = 0;  // slot 14
    virtual void pauseCategory(fw::SoundCategory, bool, float) = 0;  // slot 15
    virtual bool isDeviceEnable() const { return false; }  // slot 16
    virtual void playBgm(char const*, float, bool, int, fw::SoundCategory) = 0;  // slot 17
    virtual bool startBgm(unsigned int) = 0;  // slot 18
    virtual bool stopBgm(unsigned int, float) = 0;  // slot 19
    virtual void stopBgmAll() = 0;  // slot 20
    virtual void playVoice(char const*, float, bool, fw::SoundCategory) = 0;  // slot 21
    virtual bool startVoice(unsigned int) = 0;  // slot 22
    virtual bool stopVoice(unsigned int, float) = 0;  // slot 23
    virtual void playSe(char const*, fw::SoundPack*, float, fw::SoundCategory) = 0;  // slot 24
    virtual void playSe(unsigned int, fw::SoundPack*, float, fw::SoundCategory) = 0;  // slot 25
    virtual void playSeEx(fw::SoundPlayInfo const&, fw::SoundResult&) = 0;  // slot 26
    virtual bool stopSe(unsigned int, float) = 0;  // slot 27
    virtual bool isValid(unsigned int) const = 0;  // slot 28
    virtual bool isPlaying(unsigned int) const = 0;  // slot 29
    virtual bool isPreparing(unsigned int) const = 0;  // slot 30
    virtual bool isReady(unsigned int) const = 0;  // slot 31
    virtual bool isLoop(unsigned int) = 0;  // slot 32
    virtual bool isLoop(unsigned int, fw::SoundPack*) = 0;  // slot 33
    virtual bool isPause(unsigned int) const = 0;  // slot 34
    virtual void setCategory(unsigned int, fw::SoundCategory) = 0;  // slot 35
    virtual fw::SoundCategory getCategory(unsigned int) = 0;  // slot 36
    virtual void setVolume(unsigned int, float, float) = 0;  // slot 37
    virtual float getVolume(unsigned int, fw::SoundVolumeType) = 0;  // slot 38
    virtual void setPitch(unsigned int, float, float) = 0;  // slot 39
    virtual void setPan(unsigned int, float, float) = 0;  // slot 40
    virtual void setPos(unsigned int, mm::Vec3 const&) = 0;  // slot 41
    virtual bool setPlayTime(unsigned int, float) = 0;  // slot 42
    virtual bool getPlayTime(unsigned int, float&) = 0;  // slot 43
    virtual bool getTotalTime(unsigned int, float&) = 0;  // slot 44
    virtual bool setRemainLoopCount(unsigned int, int) = 0;  // slot 45
    virtual bool getRemainLoopCount(unsigned int, int&) = 0;  // slot 46
    virtual void pause(unsigned int, bool, float) = 0;  // slot 47
    virtual void stopAll() = 0;  // slot 48
    virtual void stopVoiceAll() = 0;  // slot 49
    virtual void stopSeAll() = 0;  // slot 50
    virtual void pauseAll(bool, float) = 0;  // slot 51
    virtual void findSe(char const*) const = 0;  // slot 52
    virtual void attachPoolMemory(void*, unsigned int);  // slot 53 (empty; the table's key function)
    virtual void detachPoolMemory(void*, unsigned int);  // slot 54 (empty)
};
}  // namespace fw

#endif
