#ifndef CLASSES_SSD_SYSTEMCOREPLATFORM_H
#define CLASSES_SSD_SYSTEMCOREPLATFORM_H

namespace ssd { class SoundEffecter; }
namespace ssd { class SoundListener; }
namespace ssd { namespace OutputMode { class Type; }}

namespace ssd {
// table 0x7100B81FD0
class SystemCorePlatform {
public:
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
    virtual void GetPlatformDataImpl(char const*);  // slot 18
    virtual ~SystemCorePlatform();  // slot 19
    virtual void GetDebugInfo() const = 0;  // slot 21
};
}  // namespace ssd

#endif
