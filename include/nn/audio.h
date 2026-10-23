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
Result AddDeviceSink(AudioRendererConfig* config, DeviceSinkType* sink, FinalMixType* finalMix,
                     const signed char* input, int inputCount, const char* name);
int ListAudioDeviceName(AudioDeviceName* names, int count);

}}  // namespace nn::audio

#endif
