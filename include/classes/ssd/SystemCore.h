#ifndef CLASSES_SSD_SYSTEMCORE_H
#define CLASSES_SSD_SYSTEMCORE_H

#include "classes/ssd/BehaviorInstance.h"
#include "classes/ssd/List.h"
#include "classes/ssd/SystemCorePlatform.h"
#include "classes/ssd/XorShift128Random.h"
#include "ssd/Mutex.h"

namespace ssd { class SoundEffecter; }
namespace ssd { class SoundListener; }
namespace ssd { class VoiceHandle; }
namespace ssd { namespace OutputMode { enum Type : int; }}  // the values are not known yet

namespace ssd {
// table 0x7100B81D10
class SystemCore : public ::ssd::SystemCorePlatform {
public:
    SystemCore();
    virtual OutputMode::Type GetOutputMode() const;  // slot 0
    virtual void SetOutputMode(OutputMode::Type);  // slot 1
    virtual float GetMasterVolume() const;  // slot 2
    virtual void SetMasterVolume(float, float);  // slot 3
    virtual float GetMasterPitch() const;  // slot 4
    virtual void SetMasterPitch(float, float);  // slot 5
    virtual void AddSoundListener(ssd::SoundListener*);  // slot 6
    virtual void RemoveSoundListener(ssd::SoundListener*);  // slot 7
    virtual void GetSoundEffectList(int, ssd::SoundEffecter**, int*);  // slot 8
    virtual void AddSoundEffecter(unsigned char, ssd::SoundEffecter*);  // slot 9
    virtual void RemoveSoundEffecter(ssd::SoundEffecter*);  // slot 10
    virtual bool IsActiveEffect(unsigned char);  // slot 11
    virtual int GetNumPlaySound() const;  // slot 12
    virtual float GetSpeedOfSound() const;  // slot 13
    virtual void SetSpeedOfSound(float);  // slot 14
    virtual double GetAudioCpuLoad() const;  // slot 15
    virtual void LockAudio() const;  // slot 16
    virtual void UnlockAudio() const;  // slot 17
    virtual ~SystemCore();  // slot 19
    virtual const DebugInfo* GetDebugInfo() const;  // slot 21

    Result Init(const SoundCore::InitParam& param);
    Result Quit();
    Result SetCategory(const SoundCategory& category);
    Result ResetCategory(int categoryId);
    void UpdateGameFrame(float frameTime);
    void StopSound(float fadeTime);

    VoiceHandle* GetVoiceHandle(unsigned int id) const;  // 0 when no voice has the id
    void MasterVolumeBehavior(float frameTime);
    void MasterPitchBehavior(float frameTime);

    static DebugInfo debugInfo_;

    // one audio frame's processing time and the frame's length (the names are not the original's)
    struct CpuLoad {
        double processTime;
        double frameTime;
    };

    // SoundCore::NewInstance allocates 0xA28 bytes for the instance; SystemCorePlatform's fields end at 0x270.
    // The field names are not the original's.
    unsigned char pad_270[0x78];
    void* pad_2e8[2];  // the constructor zeroes both
    unsigned char pad_2f8[0x8];
    OutputMode::Type outputMode_;
    unsigned char pad_304[0x4];
    BehaviorInstance<SystemCore> masterVolume_;  // 0x308
    BehaviorInstance<SystemCore> masterPitch_;  // 0x350
    unsigned char pad_398[0x8];
    List<VoiceHandle> playVoices_;  // 0x3A0: GetNumPlaySound counts it
    unsigned char pad_3c8[0x28];
    VoiceHandle* voices_;  // 0x3F0: Init allocates them
    unsigned char pad_3f8[0xe8];
    float speedOfSound_;  // 0x4E0
    unsigned char pad_4e4[0x224];
    mutable Mutex audioLock_;  // 0x708: LockAudio / UnlockAudio
    unsigned char pad_730[0x270];
    XorShift128Random random_;  // 0x9A0
    unsigned char pad_9b8[0x40];
    CpuLoad cpuLoad_[2];  // 0x9F8: GetAudioCpuLoad reads the one cpuLoadIndex_ does not select
    unsigned char pad_a18[0x8];
    int cpuLoadIndex_;
    unsigned char pad_a24[0x4];
};
}  // namespace ssd

#endif
