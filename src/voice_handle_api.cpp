#include "nn/audio.h"
#include "classes/ssd/SoundCore.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/StreamController.h"
#include "classes/ssd/VoiceHandle.h"
#include "classes/ssd/Allocator.h"
#include "classes/ssd/SoundCore.h"
#include "classes/ssd/StreamController.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/VoiceHandle.h"
#include "classes/ssd/WaveSource.h"

namespace ssd {

unsigned char* VoiceHandle::adpcmSplitBuffer_;

void VoiceHandle::AllocAdpcmSplitBuffer() {
    adpcmSplitBuffer_ = SoundMemory::allocator_->NewBuffer<unsigned char>(0x10000, 0x10);
}

void VoiceHandle::FreeAdpcmSplitBuffer() {
    if (adpcmSplitBuffer_ != nullptr) {
        SoundMemory::allocator_->DeleteBuffer(adpcmSplitBuffer_);
        adpcmSplitBuffer_ = nullptr;
    }
}

VoiceHandle::~VoiceHandle() {}

void VoiceHandle::Init(int index) {
    pad_670 = 24000;
    channelCount_ = 0;
    index_ = index;
    audioData_ = nullptr;
    pad_678 = 12000;
    for (int i = 0; i < 8; i++) {
        channels_[i].voice._pVoiceInfo = nullptr;
        channels_[i].pad_98 = nullptr;
        channels_[i].pad_b0 = 0;
    }
    pad_660 = 0;
    state_ = 0;
    pad_48 = 0;
    id_ = 0;
    handle_ = nullptr;
    entry_ = nullptr;
    stream_ = nullptr;
    bufferProcess_ = &VoiceHandle::NullBufferProcess;
    seek_ = 0;
    pad_680 = 0;
    pad_688 = 0;
    playPosition_ = 0;
    pad_698 = 0;
    seekTime_ = 0.0f;
    pad_6a8 = 0;
    volume_ = SoundHandle::FadeValue();
}

void VoiceHandle::Quit() {
    if (audioData_ != nullptr) {
        static_cast<SystemCorePlatform*>(SoundCore::instance_)->FreeAudioDataBuffer(audioData_);
        audioData_ = nullptr;
    }
}

void* VoiceHandle::AllocHWVoice() {
    return nullptr;
}

Result VoiceHandle::ForceStop() {
    stopping_ = true;
    pad_37 = false;
    pad_32 = false;
    state_ = 9;
    if (handle_ != nullptr) {
        handle_->voiceId_ = 0;
        handle_ = nullptr;
    }
    return set_result(Result(0));
}

Result VoiceHandle::SetPlayTime(float time) {
    SystemCore* system = static_cast<SystemCore*>(SoundCore::instance_);
    system->LockAudio();
    seekTime_ = time;
    seek_ = 3;
    system->UnlockAudio();
    return Result(0);
}

Result VoiceHandle::GetRemainLoopCount(int* count) const {
    if (count == nullptr) {
        return Result(-6);
    }
    if (stream_ == nullptr) {
        return Result(-6);
    }
    *count = stream_->remainLoopCount_;
    return Result(0);
}

Result VoiceHandle::SetRemainLoopCount(int count) {
    if (stream_ == nullptr) {
        return Result(-6);
    }
    stream_->remainLoopCount_ = count;
    return Result(0);
}

void VoiceHandle::UpdateAudioFrame(float frameTime) {
    if (stream_ != nullptr) {
        UpdateAudioStream(frameTime);
    } else {
        UpdateAudioInternal(frameTime);
    }
}

void VoiceHandle::DeleteStream() {
    if (stream_ != nullptr) {
        stream_->QuitStream();
        StreamController* stream = stream_;
        SoundMemory::allocator_->DeleteInstance(stream);
        state_ = 1;
        stream_ = nullptr;
    }
}

void VoiceHandle::StreamingBufferProcess() {
    for (int i = 0; i < channelCount_; i++) {
        const nn::audio::WaveBuffer* buffer = nn::audio::GetReleasedWaveBuffer(&channels_[i].voice);
        if (i == 0 && buffer != nullptr) {
            playPosition_ += buffer->size;
            pad_680 = 0;
            releasedBuffers_++;
            queuedBuffers_--;
        }
    }
    if (releasedBuffers_ != 0) {
        AddStreamingBuffer();
    }
    endOfStream_ |= queuedBuffers_ == 0;
}

void VoiceHandle::NullBufferProcess() {}

}  // namespace ssd
