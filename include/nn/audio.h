#ifndef NN_AUDIO_H
#define NN_AUDIO_H

#include "nn/os.h"
#include "nn/result.h"

// NintendoSDK 3.5.0's nn::audio, as far as the module imports it. Sizes are the ones ssd::SystemCorePlatform's
// layout shows.
namespace nn { namespace audio {

struct AudioRendererParameter {
    int sampleRate;
    int sampleCount;
    int mixBufferCount;
    int subMixCount;
    int voiceCount;
    int sinkCount;
    int effectCount;
    int performanceFrameCount;
    bool isVoiceDropEnabled;
    int splitterCount;
    int splitterSendChannelCount;
    int renderingDevice;
    int executionMode;
    unsigned int _magic;
};

struct AudioRendererHandle {
    void* _handle;
    void* _context;
};

// 0x70 bytes: ssd::SystemCorePlatform's at 0x168 is followed by its handle at 0x1D8
struct AudioRendererConfig {
    void* pad_0[0xE];
};

struct FinalMixType {
    void* _pMixInfo;
};
struct MemoryPoolType {
    // the pool's state (GetMemoryPoolState; fw::SoundPoolMemory compares it with 3) (values not declared here)
    enum State : int;
    void* _pMemoryPoolInfo;
};
struct DeviceSinkType {
    void* _pSinkInfo;
};
struct DelayType {
    void* _pEffectInfo;
};
struct I3dl2ReverbType {
    void* _pEffectInfo;
};
struct BufferMixerType {
    void* _pEffectInfo;
};
struct AudioDeviceName {
    char name[0x100];
};

void InitializeAudioRendererParameter(AudioRendererParameter* parameter);
bool IsValidAudioRendererParameter(const AudioRendererParameter& parameter);
unsigned long GetAudioRendererWorkBufferSize(const AudioRendererParameter& parameter);
unsigned long GetAudioRendererConfigWorkBufferSize(const AudioRendererParameter& parameter);
Result OpenAudioRenderer(AudioRendererHandle* handle, os::SystemEvent* systemEvent,
                         const AudioRendererParameter& parameter, void* workBuffer, unsigned long workBufferSize);
void CloseAudioRenderer(AudioRendererHandle handle);
Result StartAudioRenderer(AudioRendererHandle handle);
void StopAudioRenderer(AudioRendererHandle handle);
Result RequestUpdateAudioRenderer(AudioRendererHandle handle, const AudioRendererConfig* config);
void InitializeAudioRendererConfig(AudioRendererConfig* config, const AudioRendererParameter& parameter,
                                   void* buffer, unsigned long size);
bool AcquireFinalMix(AudioRendererConfig* config, FinalMixType* finalMix, int bufferCount);
bool AcquireMemoryPool(AudioRendererConfig* config, MemoryPoolType* pool, void* address, unsigned long size);
bool RequestAttachMemoryPool(MemoryPoolType* pool);
// fw::SoundPoolMemory's detach and release
bool RequestDetachMemoryPool(MemoryPoolType* pool);
MemoryPoolType::State GetMemoryPoolState(const MemoryPoolType* pool);
void ReleaseMemoryPool(AudioRendererConfig* config, MemoryPoolType* pool);
Result AddDeviceSink(AudioRendererConfig* config, DeviceSinkType* sink, FinalMixType* finalMix,
                     const signed char* input, int inputCount, const char* name);
int ListAudioDeviceName(AudioDeviceName* names, int count);

// effects (ssd::SystemCorePlatform's InitDelayEffect / InitI3dl2ReverbEffect / QuitEffect / DeleteEffect)
unsigned long GetRequiredBufferSizeForDelay(TimeSpan delayTimeMax, int sampleRate, int channelCount);
Result AddDelay(AudioRendererConfig* config, DelayType* delay, void* buffer, unsigned long bufferSize,
                FinalMixType* finalMix, TimeSpan delayTimeMax, int channelCount);
void* RemoveDelay(AudioRendererConfig* config, DelayType* delay, FinalMixType* finalMix);
bool IsDelayRemovable(const DelayType* delay);
void SetDelayInputOutput(DelayType* delay, const signed char* input, const signed char* output, int count);
void SetDelayTime(DelayType* delay, TimeSpan time);
void SetDelayChannelSpread(DelayType* delay, float channelSpread);
void SetDelayDryGain(DelayType* delay, float dryGain);
void SetDelayFeedbackGain(DelayType* delay, float feedbackGain);
void SetDelayInGain(DelayType* delay, float inGain);
void SetDelayLowPassAmount(DelayType* delay, float lowPassAmount);
void SetDelayEnabled(DelayType* delay, bool enabled);

unsigned long GetRequiredBufferSizeForI3dl2Reverb(int sampleRate, int channelCount);
Result AddI3dl2Reverb(AudioRendererConfig* config, I3dl2ReverbType* reverb, void* buffer, unsigned long bufferSize,
                      FinalMixType* finalMix, int channelCount);
void* RemoveI3dl2Reverb(AudioRendererConfig* config, I3dl2ReverbType* reverb, FinalMixType* finalMix);
bool IsI3dl2ReverbRemovable(const I3dl2ReverbType* reverb);
void SetI3dl2ReverbInputOutput(I3dl2ReverbType* reverb, const signed char* input, const signed char* output,
                               int count);
void SetI3dl2ReverbRoomGain(I3dl2ReverbType* reverb, float gain);
void SetI3dl2ReverbRoomHfGain(I3dl2ReverbType* reverb, float gain);
void SetI3dl2ReverbLateReverbDecayTime(I3dl2ReverbType* reverb, TimeSpan time);
void SetI3dl2ReverbLateReverbHfDecayRatio(I3dl2ReverbType* reverb, float ratio);
void SetI3dl2ReverbReflectionsGain(I3dl2ReverbType* reverb, float gain);
void SetI3dl2ReverbReflectionDelayTime(I3dl2ReverbType* reverb, TimeSpan time);
void SetI3dl2ReverbReverbGain(I3dl2ReverbType* reverb, float gain);
void SetI3dl2ReverbLateReverbDelayTime(I3dl2ReverbType* reverb, TimeSpan time);
void SetI3dl2ReverbLateReverbDiffusion(I3dl2ReverbType* reverb, float diffusion);
void SetI3dl2ReverbLateReverbDensity(I3dl2ReverbType* reverb, float density);
void SetI3dl2ReverbHfReference(I3dl2ReverbType* reverb, float hfReference);
void SetI3dl2ReverbDryGain(I3dl2ReverbType* reverb, float gain);
void SetI3dl2ReverbEnabled(I3dl2ReverbType* reverb, bool enabled);

Result AddBufferMixer(AudioRendererConfig* config, BufferMixerType* mixer, FinalMixType* finalMix);
void RemoveBufferMixer(AudioRendererConfig* config, BufferMixerType* mixer, FinalMixType* finalMix);
bool IsBufferMixerRemovable(const BufferMixerType* mixer);
void SetBufferMixerVolume(BufferMixerType* mixer, int index, float volume);
void SetBufferMixerInputOutput(BufferMixerType* mixer, const signed char* input, const signed char* output,
                               int count);
void SetBufferMixerEnabled(BufferMixerType* mixer, bool enabled);

// a voice's source buffer (the SDK's field names)
struct WaveBuffer {
    void* buffer;
    unsigned long size;
    int startSampleOffset;
    int endSampleOffset;
    bool loop;
    bool isEndOfStream;
    const void* pContext;
    unsigned long contextSize;
};
struct VoiceType {
    // SetVoicePlayState's states (VoiceHandle::UpdateAudioInternal starts its channels with 0)
    enum PlayState { PlayState_Started, PlayState_Stopped, PlayState_Paused };

    void* _pVoiceInfo;
};
// the oldest buffer the renderer has finished with, or null
const WaveBuffer* GetReleasedWaveBuffer(VoiceType* voice);
bool IsVoiceValid(const VoiceType* voice);
long GetVoicePlayedSampleCount(const VoiceType* voice);
int GetWaveBufferCount(const VoiceType* voice);
void SetVoicePlayState(VoiceType* voice, VoiceType::PlayState state);
void ReleaseVoiceSlot(AudioRendererConfig* config, VoiceType* voice);

}}  // namespace nn::audio

#endif
