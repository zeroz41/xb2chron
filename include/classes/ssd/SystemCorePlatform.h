#ifndef CLASSES_SSD_SYSTEMCOREPLATFORM_H
#define CLASSES_SSD_SYSTEMCOREPLATFORM_H

#include "classes/ssd/SoundCore.h"
#include "nn/audio.h"
#include "nn/mem.h"
#include "nn/os.h"
#include "ssd/MemoryBlock.h"

namespace ssd { class SoundEffecter; }
namespace ssd { class SoundDelayEffecter; }
namespace ssd { class SoundI3dl2ReverbEffecter; }
namespace ssd { class SoundListener; }
namespace ssd { namespace OutputMode { class Type; }}

namespace ssd {
// table 0x7100B81FD0 (its constructor, inline in SystemCore's, calls SoundCore's)
class SystemCorePlatform : public ::ssd::SoundCore {
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
    virtual void* GetPlatformDataImpl(char const* name);  // slot 18
    virtual ~SystemCorePlatform();  // slot 19
    virtual void GetDebugInfo() const = 0;  // slot 21

    // an effect's bus: the effect, its buffer mixer and their channels (the field names are not the original's;
    // InitAudioDevice sets up two, on channels 6/7 and 8/9 after the six main ones)
    struct EffectBusInfo {
        unsigned char pad_0[0x2];
        unsigned char busNumber;  // 0xFF: none
        signed char input;
        signed char output;
        unsigned char pad_5[0x3];
        float volume;
        unsigned char pad_c[0x4];
        void* pad_10[0x4];
        unsigned char pad_30[0x8];
    };

    void InitPlatform(const SoundCore::InitParam& param);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because SystemCore::Init, which
    // runs SystemCorePlatform's InitPlatform and InitAudioDevice, calls it between them and it sits in this
    // unit's code. What it does: returns 0x400 (1024, InitAudioDevice's voice-count ceiling); reads nothing.
    int fn_710089E218();
    void InitAudioDevice(const SoundCore::InitParam& param);
    void QuitAudioDevice();
    void UpdateDevice();
    double GetSystemTime();
    // audio data memory from the platform's allocator (nn::mem::StandardAllocator::Allocate / Free)
    void* AllocAudioDataBuffer(unsigned long size);
    void FreeAudioDataBuffer(void* buffer);

    // the field names are not the original's
    double tickFrequency_;                          // GetSystemTickFrequency(), set by InitPlatform
    MemoryBlock workBlock_;                         // 0x134000 bytes for the renderer's work buffers
    nn::mem::StandardAllocator workAllocator_;
    MemoryBlock effectBlock_;                       // 0xCD000 bytes, the renderer's second memory pool
    nn::mem::StandardAllocator effectAllocator_;
    nn::audio::MemoryPoolType effectPool_;
    MemoryBlock audioDataBlock_;                    // InitParam::memoryPoolSize bytes, the first memory pool
    nn::mem::StandardAllocator audioDataAllocator_;  // AllocAudioDataBuffer's
    nn::audio::MemoryPoolType audioDataPool_;
    nn::os::SystemEvent systemEvent_;
    nn::audio::AudioRendererConfig config_;  // GetPlatformDataImpl("AudioRendererConfig")
    nn::audio::AudioRendererHandle handle_;
    signed char mainChannels_[6];  // 0..5, the device sink's inputs
    unsigned char pad_1ee[0x2];
    EffectBusInfo effectBus_[2];
    nn::audio::FinalMixType finalMix_;
    int sampleRate_;
    int sampleCount_;
};
}  // namespace ssd

#endif
