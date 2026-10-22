#ifndef CLASSES_SSD_SOUNDCORE_H
#define CLASSES_SSD_SOUNDCORE_H

#include "nn/os.h"
#include "ssd/Debug.h"

namespace ssd { class Allocator; }
namespace ssd { class SoundCategory; }
namespace ssd { class SoundEffecter; }
namespace ssd { class SoundListener; }
namespace ssd { namespace OutputMode { class Type; }}

namespace ssd {
// table 0x7100B81B70: the sound library's interface; its one instance is a SystemCore (NewInstance), whose
// functions its own forward to. The virtuals are SystemCorePlatform's, pure here.
class SoundCore {
public:
    // a library thread's parameters (the field names are not the original's): SystemCore::Init hands the mask,
    // the priority and the stack size to Thread::CreateThreadImpl. 1.0.0 has the constructor out of line in
    // SoundCore.cpp; 3.0.1 keeps no copy, so it is inline here.
    struct ThreadParam {
        ThreadParam()
            : coreMask(nn::os::GetThreadAvailableCoreMask()), priority(0), idealCore(-1), stackSize(0) {}

        unsigned long coreMask;
        int priority;
        int idealCore;
        unsigned long stackSize;
    };

    // what SoundCore::Init sets the library up with (the field names are not the original's): the audio and
    // stream threads' parameters, the number of voices SystemCore::Init allocates, the log message method and
    // time-stamp type Init installs, and the size of the third memory pool InitAudioDevice allocates
    struct InitParam {
        InitParam();

        ThreadParam audioThread;
        ThreadParam streamThread;
        int voiceNum;
        LogMethod messageMethod;
        LogTimeStamp::Type timeStampType;
        unsigned int memoryPoolSize;
    };

    SoundCore();

    virtual void GetOutputMode() const = 0;  // slot 0
    virtual void SetOutputMode(ssd::OutputMode::Type) = 0;  // slot 1
    virtual void GetMasterVolume() const = 0;  // slot 2
    virtual void SetMasterVolume(float, float) = 0;  // slot 3
    virtual void GetMasterPitch() const = 0;  // slot 4
    virtual void SetMasterPitch(float, float) = 0;  // slot 5
    virtual void AddSoundListener(ssd::SoundListener*) = 0;  // slot 6
    virtual void RemoveSoundListener(ssd::SoundListener*) = 0;  // slot 7
    virtual void GetSoundEffectList(int, ssd::SoundEffecter**, int*) = 0;  // slot 8
    virtual void AddSoundEffecter(unsigned char, ssd::SoundEffecter*) = 0;  // slot 9
    virtual void RemoveSoundEffecter(ssd::SoundEffecter*) = 0;  // slot 10
    virtual bool IsActiveEffect(unsigned char) = 0;  // slot 11
    virtual void GetNumPlaySound() const = 0;  // slot 12
    virtual void GetSpeedOfSound() const = 0;  // slot 13
    virtual void SetSpeedOfSound(float) = 0;  // slot 14
    virtual void GetAudioCpuLoad() const = 0;  // slot 15
    virtual void LockAudio() const = 0;  // slot 16
    virtual void UnlockAudio() const = 0;  // slot 17
    virtual void GetPlatformDataImpl(char const*) = 0;  // slot 18
    virtual ~SoundCore();  // slot 19
    virtual void GetDebugInfo() const = 0;  // slot 21

    static SoundCore* NewInstance(Allocator* allocator);
    static void DeleteInstance();
    // the library's version (1.0.0 has it out of line in SoundCore.cpp, 3.0.1 keeps no copy: Init inlines it)
    void GetVersion(int* major, int* minor, int* revision, int* build, char16_t* buildType) {
        if (major != nullptr) {
            *major = 5;
        }
        if (minor != nullptr) {
            *minor = 1;
        }
        if (revision != nullptr) {
            *revision = 0;
        }
        if (build != nullptr) {
            *build = 1462;
        }
        if (buildType != nullptr) {
            const char16_t* text = u"Release";
            while ((*buildType++ = *text++) != u'\0') {
            }
        }
    }
    Result Init(const InitParam& param);
    Result Quit(bool);
    Result SetCategory(const SoundCategory& category);
    Result ResetCategory(int categoryId);
    void UpdateGameFrame(float frameTime);
    void StopSound(float fadeTime);
    LogTimeStamp::Type GetLogTimeStampType() const;

    static SoundCore* instance_;
    static const char* audioRendererConfigName_;

    // the last result (set_result; the constructor starts it at 0x80000000) and whether Init has run and
    // Quit has not yet (the names are not the original's)
    Result result_;
    bool initialized_;
};
}  // namespace ssd

#endif
