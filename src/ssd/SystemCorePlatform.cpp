#include "nn/os.h"
#include "nn/diag.h"
#include "nn/mem.h"
#include "nn/audio.h"
#include "nn/util.h"
#include "ssd/Debug.h"
#include "ssd/MemoryBlock.h"
#include "ssd/Hash.h"
#include "ssd/Text.h"
#include "ssd/Thread.h"
#include "classes/ssd/SoundCore.h"
#include "classes/ssd/SystemCorePlatform.h"
#include "classes/ssd/SoundEffecter.h"

#include <string.h>

namespace ssd {

void SystemCorePlatform::InitPlatform(const SoundCore::InitParam& param) {
    tickFrequency_ = nn::os::GetSystemTickFrequency();
}

int SystemCorePlatform::GetSdkVoiceCountMax() {
    return 0x400;
}

// a buffer from SoundMemory::allocator_ (the name is inferred: the size is evaluated before the allocator is read)
static inline void* AllocBuffer(unsigned long size, unsigned long alignment) {
    return SoundMemory::allocator_->NewBuffer<unsigned char>(size, alignment);
}

void SystemCorePlatform::InitAudioDevice(const SoundCore::InitParam& param) {
    nn::audio::AudioRendererParameter parameter;
    nn::audio::InitializeAudioRendererParameter(&parameter);
    parameter.sampleRate = 48000;
    parameter.sampleCount = 240;
    parameter.voiceCount = 24;
    parameter.mixBufferCount = 10;
    parameter.subMixCount = 4;
    parameter.sinkCount = 1;
    parameter.effectCount = 3;
    parameter.performanceFrameCount = 0;
    NN_ABORT_UNLESS(nn::audio::IsValidAudioRendererParameter(parameter));
    int voiceCount = param.voiceNum + 32;
    parameter.voiceCount = voiceCount < 0x400 ? voiceCount : 0x400;
    NN_ABORT_UNLESS(nn::audio::IsValidAudioRendererParameter(parameter));
    sampleRate_ = parameter.sampleRate;
    sampleCount_ = parameter.sampleCount;

    workBlock_ = MemoryBlock{AllocBuffer(0x134000, 0x1000), 0x134000};
    workAllocator_.Initialize(workBlock_.address, workBlock_.size);
    effectBlock_ = MemoryBlock{AllocBuffer(0xCD000, 0x1000), 0xCD000};
    effectAllocator_.Initialize(effectBlock_.address, effectBlock_.size);
    audioDataBlock_ = MemoryBlock{AllocBuffer(param.memoryPoolSize, 0x1000), param.memoryPoolSize};
    audioDataAllocator_.Initialize(audioDataBlock_.address, audioDataBlock_.size);
    for (int i = 0; i < 6; i++) {
        mainChannels_[i] = i;
    }
    for (int i = 0; i < 2; i++) {
        EffectBusInfo& info = effectBus_[i];
        info.activeFlags[0] = false;
        info.activeFlags[1] = false;
        info.channels[0] = 6 + i * 2;
        info.channels[1] = 7 + i * 2;
        info.effectType = 0xFF;
        info.volume = 1.0f;
        info.effect = nullptr;
        info.buffer = nullptr;
        info.mixer._pEffectInfo = nullptr;
        info.delay._pEffectInfo = nullptr;
    }
    unsigned long workBufferSize = nn::audio::GetAudioRendererWorkBufferSize(parameter);
    void* workBuffer = workAllocator_.Allocate(workBufferSize, 0x1000);
    NN_ABORT_UNLESS_NOT_NULL(workBuffer);
    unsigned long configBufferSize = nn::audio::GetAudioRendererConfigWorkBufferSize(parameter);
    void* configBuffer = workAllocator_.Allocate(configBufferSize, 0x1000);
    NN_ABORT_UNLESS_NOT_NULL(configBuffer);
    NN_ABORT_UNLESS_RESULT_SUCCESS(
        nn::audio::OpenAudioRenderer(&handle_, &systemEvent_, parameter, workBuffer, workBufferSize));
    nn::audio::InitializeAudioRendererConfig(&config_, parameter, configBuffer, configBufferSize);
    NN_ABORT_UNLESS(nn::audio::AcquireFinalMix(&config_, &finalMix_, 10));
    NN_ABORT_UNLESS(
        nn::audio::AcquireMemoryPool(&config_, &audioDataPool_, audioDataBlock_.address, audioDataBlock_.size));
    NN_ABORT_UNLESS(nn::audio::RequestAttachMemoryPool(&audioDataPool_));
    NN_ABORT_UNLESS(nn::audio::AcquireMemoryPool(&config_, &effectPool_, effectBlock_.address, effectBlock_.size));
    NN_ABORT_UNLESS(nn::audio::RequestAttachMemoryPool(&effectPool_));
    nn::audio::DeviceSinkType sink;
    NN_ABORT_UNLESS_RESULT_SUCCESS(
        nn::audio::AddDeviceSink(&config_, &sink, &finalMix_, mainChannels_, 6, "MainAudioOut"));
    NN_ABORT_UNLESS_RESULT_SUCCESS(nn::audio::RequestUpdateAudioRenderer(handle_, &config_));
    NN_ABORT_UNLESS_RESULT_SUCCESS(nn::audio::StartAudioRenderer(handle_));
    nn::audio::AudioDeviceName names[3];
    nn::audio::ListAudioDeviceName(names, 3);
    set_result(Result(0));
}

Result SystemCorePlatform::InitEffect(unsigned char bus, SoundEffecter* effect) {
    if (bus >= 2) {
        return Result(-1);
    }
    switch (effect->type_) {
    case 0:
        return InitDelayEffect(bus, static_cast<SoundDelayEffecter*>(effect));
    case 1:
        return InitI3dl2ReverbEffect(bus, static_cast<SoundI3dl2ReverbEffecter*>(effect));
    }
    return Result(-1);
}

Result SystemCorePlatform::InitDelayEffect(unsigned char bus, SoundDelayEffecter* effect) {
    if (effectBus_[bus].effect != nullptr) {
        return Result(-1);
    }
    if (effectBus_[bus].activeFlags[1]) {
        return Result(-1);
    }
    if (effect->delayTime_ > effect->delayTimeMax_) {
        return Result(-1);
    }
    EffectBusInfo& info = effectBus_[bus];
    info.effect = effect;
    info.effectType = 0;
    info.volume = effect->volume_;
    nn::TimeSpan delayTimeMax = nn::TimeSpan::FromMicroSeconds(static_cast<long>(effect->delayTimeMax_ * 1000000.0));
    unsigned long size = nn::audio::GetRequiredBufferSizeForDelay(delayTimeMax, sampleRate_, 2);
    info.buffer = effectAllocator_.Allocate(size);
    NN_ABORT_UNLESS(info.buffer != nullptr);
    NN_ABORT_UNLESS_RESULT_SUCCESS(
        nn::audio::AddDelay(&config_, &info.delay, info.buffer, size, &finalMix_, delayTimeMax, 2));
    nn::audio::SetDelayInputOutput(&info.delay, info.channels, info.channels, 2);
    nn::audio::SetDelayTime(&info.delay,
                            nn::TimeSpan::FromMicroSeconds(static_cast<long>(effect->delayTime_ * 1000000.0)));
    nn::audio::SetDelayChannelSpread(&info.delay, effect->channelSpread_);
    nn::audio::SetDelayDryGain(&info.delay, effect->dryGain_);
    nn::audio::SetDelayFeedbackGain(&info.delay, effect->feedbackGain_);
    nn::audio::SetDelayInGain(&info.delay, effect->inGain_);
    nn::audio::SetDelayLowPassAmount(&info.delay, effect->lowPassAmount_);
    nn::audio::SetDelayEnabled(&info.delay, true);
    nn::audio::AddBufferMixer(&config_, &info.mixer, &finalMix_);
    nn::audio::SetBufferMixerVolume(&info.mixer, 0, effect->volume_);
    nn::audio::SetBufferMixerVolume(&info.mixer, 1, effect->volume_);
    nn::audio::SetBufferMixerInputOutput(&info.mixer, info.channels, mainChannels_, 6);
    nn::audio::SetBufferMixerEnabled(&info.mixer, true);
    info.activeFlags[0] = true;
    info.activeFlags[1] = false;
    effect->bus_ = bus;
    effect->attached_ = true;
    return Result(0);
}

Result SystemCorePlatform::InitI3dl2ReverbEffect(unsigned char bus, SoundI3dl2ReverbEffecter* effect) {
    if (effectBus_[bus].effect != nullptr) {
        return Result(-1);
    }
    if (effectBus_[bus].activeFlags[1]) {
        return Result(-1);
    }
    EffectBusInfo& info = effectBus_[bus];
    info.effect = effect;
    info.effectType = 1;
    info.volume = effect->volume_;
    unsigned long size = nn::audio::GetRequiredBufferSizeForI3dl2Reverb(sampleRate_, 2);
    info.buffer = effectAllocator_.Allocate(size);
    NN_ABORT_UNLESS(info.buffer != nullptr);
    NN_ABORT_UNLESS_RESULT_SUCCESS(
        nn::audio::AddI3dl2Reverb(&config_, &info.reverb, info.buffer, size, &finalMix_, 2));
    nn::audio::SetI3dl2ReverbInputOutput(&info.reverb, info.channels, info.channels, 2);
    if (effect->flag_20) {
        effect->flag_20 = false;
    }
    nn::audio::SetI3dl2ReverbRoomGain(&info.reverb, effect->roomGain_);
    nn::audio::SetI3dl2ReverbRoomHfGain(&info.reverb, effect->roomHfGain_);
    nn::audio::SetI3dl2ReverbLateReverbDecayTime(
        &info.reverb, nn::TimeSpan::FromMicroSeconds(static_cast<long>(effect->lateReverbDecayTime_ * 1000000.0)));
    nn::audio::SetI3dl2ReverbLateReverbHfDecayRatio(&info.reverb, effect->lateReverbHfDecayRatio_);
    nn::audio::SetI3dl2ReverbReflectionsGain(&info.reverb, effect->reflectionsGain_);
    nn::audio::SetI3dl2ReverbReflectionDelayTime(
        &info.reverb, nn::TimeSpan::FromMicroSeconds(static_cast<long>(effect->reflectionDelayTime_ * 1000000.0)));
    nn::audio::SetI3dl2ReverbReverbGain(&info.reverb, effect->reverbGain_);
    nn::audio::SetI3dl2ReverbLateReverbDelayTime(
        &info.reverb, nn::TimeSpan::FromMicroSeconds(static_cast<long>(effect->lateReverbDelayTime_ * 1000000.0)));
    nn::audio::SetI3dl2ReverbLateReverbDiffusion(&info.reverb, effect->lateReverbDiffusion_);
    nn::audio::SetI3dl2ReverbLateReverbDensity(&info.reverb, effect->lateReverbDensity_);
    nn::audio::SetI3dl2ReverbHfReference(&info.reverb, effect->hfReference_);
    nn::audio::SetI3dl2ReverbDryGain(&info.reverb, effect->dryGain_);
    nn::audio::SetI3dl2ReverbEnabled(&info.reverb, true);
    nn::audio::AddBufferMixer(&config_, &info.mixer, &finalMix_);
    nn::audio::SetBufferMixerVolume(&info.mixer, 0, info.volume);
    nn::audio::SetBufferMixerVolume(&info.mixer, 1, info.volume);
    nn::audio::SetBufferMixerInputOutput(&info.mixer, info.channels, mainChannels_, 6);
    nn::audio::SetBufferMixerEnabled(&info.mixer, true);
    info.activeFlags[0] = true;
    info.activeFlags[1] = false;
    effect->bus_ = bus;
    effect->attached_ = true;
    return Result(0);
}

void SystemCorePlatform::DeleteEffect(EffectBusInfo& bus) {
    if (!bus.activeFlags[1]) {
        return;
    }
    switch (bus.effectType) {
    case 0:
        if (!nn::audio::IsBufferMixerRemovable(&bus.mixer)) {
            return;
        }
        if (!nn::audio::IsDelayRemovable(&bus.delay)) {
            return;
        }
        nn::audio::RemoveBufferMixer(&config_, &bus.mixer, &finalMix_);
        nn::audio::RemoveDelay(&config_, &bus.delay, &finalMix_);
        break;
    case 1:
        if (!nn::audio::IsBufferMixerRemovable(&bus.mixer)) {
            return;
        }
        if (!nn::audio::IsI3dl2ReverbRemovable(&bus.reverb)) {
            return;
        }
        nn::audio::RemoveBufferMixer(&config_, &bus.mixer, &finalMix_);
        nn::audio::RemoveI3dl2Reverb(&config_, &bus.reverb, &finalMix_);
        break;
    default:
        return;
    }
    effectAllocator_.Free(bus.buffer);
    bus.buffer = nullptr;
    bus.activeFlags[1] = false;
    bus.effectType = 0xFF;
}

void SystemCorePlatform::QuitAudioDevice() {
    nn::audio::StopAudioRenderer(handle_);
    nn::audio::CloseAudioRenderer(handle_);
    nn::os::DestroySystemEvent(systemEvent_.GetBase());
    audioDataAllocator_.Finalize();
    audioDataBlock_.Free();
    effectAllocator_.Finalize();
    effectBlock_.Free();
    workAllocator_.Finalize();
    workBlock_.Free();
    set_result(Result(0));
}

void SystemCorePlatform::UpdateDevice() {
    NN_ABORT_UNLESS_RESULT_SUCCESS(nn::audio::RequestUpdateAudioRenderer(handle_, &config_));
}

double SystemCorePlatform::GetSystemTime() {
    return nn::os::ConvertToTimeSpan(nn::os::GetSystemTick()).GetNanoSeconds() / 1000000000.0;
}

void* SystemCorePlatform::GetPlatformDataImpl(const char* name) {
    if (strcmp(name, "AudioRendererConfig") == 0) {
        return &config_;
    }
    return nullptr;
}

void* SystemCorePlatform::AllocAudioDataBuffer(unsigned long size) {
    return audioDataAllocator_.Allocate(size, 0x40);
}

void SystemCorePlatform::FreeAudioDataBuffer(void* buffer) {
    audioDataAllocator_.Free(buffer);
}

}  // namespace ssd
