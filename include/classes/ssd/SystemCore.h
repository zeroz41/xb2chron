#ifndef CLASSES_SSD_SYSTEMCORE_H
#define CLASSES_SSD_SYSTEMCORE_H

#include "classes/ssd/SystemCorePlatform.h"

namespace ssd { class SoundEffecter; }
namespace ssd { class SoundListener; }
namespace ssd { namespace OutputMode { class Type; }}

namespace ssd {
// table 0x7100B81D10
class SystemCore : public ::ssd::SystemCorePlatform {
public:
    virtual void GetOutputMode() const;  // slot 0
    virtual void SetOutputMode(ssd::OutputMode::Type);  // slot 1
    virtual void GetMasterVolume() const;  // slot 2
    virtual void SetMasterVolume(float, float);  // slot 3
    virtual void GetMasterPitch() const;  // slot 4
    virtual void SetMasterPitch(float, float);  // slot 5
    virtual void AddSoundListener(ssd::SoundListener*);  // slot 6
    virtual void RemoveSoundListener(ssd::SoundListener*);  // slot 7
    virtual void GetSoundEffectList(int, ssd::SoundEffecter**, int*);  // slot 8
    virtual void AddSoundEffecter(unsigned char, ssd::SoundEffecter*);  // slot 9
    virtual void RemoveSoundEffecter(ssd::SoundEffecter*);  // slot 10
    virtual bool IsActiveEffect(unsigned char);  // slot 11
    virtual void GetNumPlaySound() const;  // slot 12
    virtual void GetSpeedOfSound() const;  // slot 13
    virtual void SetSpeedOfSound(float);  // slot 14
    virtual void GetAudioCpuLoad() const;  // slot 15
    virtual void LockAudio() const;  // slot 16
    virtual void UnlockAudio() const;  // slot 17
    virtual ~SystemCore();  // slot 19
    virtual void GetDebugInfo() const;  // slot 21
};
}  // namespace ssd

#endif
