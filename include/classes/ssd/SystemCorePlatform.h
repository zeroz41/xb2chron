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
namespace ssd { namespace OutputMode { enum Type : int; }}  // the values are not known yet

namespace ssd {
// table 0x7100B81FD0 (its constructor, inline in SystemCore's, calls SoundCore's)
class SystemCorePlatform : public ::ssd::SoundCore {
public:
    virtual OutputMode::Type GetOutputMode() const = 0;  // slot 0
    virtual void SetOutputMode(OutputMode::Type) = 0;  // slot 1
    virtual float GetMasterVolume() const = 0;  // slot 2
    virtual void SetMasterVolume(float, float) = 0;  // slot 3
    virtual float GetMasterPitch() const = 0;  // slot 4
    virtual void SetMasterPitch(float, float) = 0;  // slot 5
    virtual void AddSoundListener(ssd::SoundListener*) = 0;  // slot 6
    virtual void RemoveSoundListener(ssd::SoundListener*) = 0;  // slot 7
    virtual Result GetSoundEffectList(int, ssd::SoundEffecter**, int*) = 0;  // slot 8
    virtual Result AddSoundEffecter(unsigned char, ssd::SoundEffecter*) = 0;  // slot 9
    virtual Result RemoveSoundEffecter(ssd::SoundEffecter*) = 0;  // slot 10
    virtual bool IsActiveEffect(unsigned char) = 0;  // slot 11
    virtual int GetNumPlaySound() const = 0;  // slot 12
    virtual float GetSpeedOfSound() const = 0;  // slot 13
    virtual void SetSpeedOfSound(float) = 0;  // slot 14
    virtual double GetAudioCpuLoad() const = 0;  // slot 15
    virtual void LockAudio() const = 0;  // slot 16
    virtual void UnlockAudio() const = 0;  // slot 17
    virtual void* GetPlatformDataImpl(char const* name);  // slot 18
    // inline: SystemCore's constructor and destructor inline both; the table's unit keeps a weak copy of the
    // destructor after its own code
    SystemCorePlatform() {}
    virtual ~SystemCorePlatform() {}  // slot 19
    virtual const DebugInfo* GetDebugInfo() const = 0;  // slot 21

    // an effect's bus: the effect, its buffer mixer and their channels (the field names are not the original's;
    // InitAudioDevice sets up two, on channels 6/7 and 8/9 after the six main ones)
    struct EffectBusInfo {
        // the bus counts as active while either is set (SystemCore::IsActiveEffect); [1]: QuitEffect took the
        // effect down and DeleteEffect has not freed it yet
        bool activeFlags[2];
        unsigned char effectType;  // SoundEffecter::type_ of the effect (0xFF: none)
        signed char channels[2];  // the effect's input/output channels
        unsigned char pad_5[0x3];
        float volume;
        unsigned char pad_c[0x4];
        SoundEffecter* effect;  // 0x10: InitEffect's effect (none: 0)
        void* buffer;  // 0x18: the effect's work buffer, from effectAllocator_
        nn::audio::BufferMixerType mixer;
        nn::audio::DelayType delay;
        nn::audio::I3dl2ReverbType reverb;
    };

    void InitPlatform(const SoundCore::InitParam& param);
    // sets up effect bus bus for effect / takes effect's bus down (SystemCore's AddSoundEffecter and
    // RemoveSoundEffecter call them under the audio lock)
    Result InitEffect(unsigned char bus, SoundEffecter* effect);
    Result QuitEffect(SoundEffecter* effect);
    // InitEffect's two kinds; DeleteEffect frees a bus QuitEffect took down once the renderer lets it go
    Result InitDelayEffect(unsigned char bus, SoundDelayEffecter* effect);
    Result InitI3dl2ReverbEffect(unsigned char bus, SoundI3dl2ReverbEffecter* effect);
    void DeleteEffect(EffectBusInfo& bus);
    // QuitEffect's two kinds: 2.0.0's symbols name them (out of line there); 3.0.1 has no copy, so inline
    Result QuitDelayEffect(unsigned char bus);
    Result QuitI3dl2ReverbEffect(unsigned char bus);
    // 2.0.0's symbols name it. What it does: returns 0x400 (1024, InitAudioDevice's voice-count ceiling); reads
    // nothing.
    int GetSdkVoiceCountMax();
    void InitAudioDevice(const SoundCore::InitParam& param);
    void QuitAudioDevice();
    void UpdateDevice();
    // static: StreamController::ExecOpusDecode calls it without setting x0, and it reads no member
    static double GetSystemTime();
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
