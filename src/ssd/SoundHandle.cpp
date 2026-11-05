#include "classes/ssd/SoundCore.h"
#include "classes/ssd/SystemCorePlatform.h"
#include "classes/ssd/BehaviorInstance.h"
#include "classes/ssd/XorShift128Random.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SoundEntry.h"
#include "classes/ssd/SoundGroup.h"
#include "classes/ssd/StreamController.h"
#include "classes/ssd/TextRef.h"
#include "classes/ssd/VoiceHandle.h"
#include "ssd/Debug.h"
#include "classes/ssd/List.h"

namespace ssd {

SoundHandle::~SoundHandle() {
    valid_ = false;
    Delete();
}

void SoundHandle::Quit() {
    valid_ = false;
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return;
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice != nullptr) {
        Stop(0.0f);
        voice->handle_ = nullptr;
    }
    entry_ = nullptr;
    ClearDelegate();
    if (delegates_.data_ != nullptr) {
        SoundMemory::allocator_->DeleteInstance(delegates_.data_);
    }
    delegates_.size_ = 0;
    delegates_.capacity_ = 0;
    delegates_.data_ = nullptr;
}

void SoundHandle::Init() {
    pitch_.Reset(1.0f);
    volume_.Reset(1.0f);
    pan_.Reset(0.0f);
    pad_b4 = 1.0f;
    volume2_ = 1.0f;
    pad_bc = 0.0f;
    startTime_ = 0.0;
    pad_68 = 0.0f;
    pad_c0 = false;
    pad_c4.Reset(1.0f);
    pad_dc = false;
    pad_e0.Reset(1.0f);
    ClearDelegate();
    valid_ = true;
}

bool SoundHandle::IsValidHandle() const {
    if (!valid_) {
        return false;
    }
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return false;
    }
    return core->GetVoiceHandle(voiceId_) != nullptr;
}

Result SoundHandle::AddDelegateInternal(Delegate::Handle* handle) {
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    Result result;
    {
        ScopedLock lock(core->audioLock_);
        int size = delegates_.size_;
        if (delegates_.capacity_ <= size) {
            delegates_.SetArraySize(delegates_.capacity_ + 16);
        }
        delegates_.data_[delegates_.size_] = handle;
        delegates_.size_++;
        result = notify_.AddDelegate(handle);
    }
    return set_result(result);
}

void SoundHandle::ClearDelegate() {
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return;
    }
    core->audioLock_.Lock();
    notify_.Clear();
    for (int i = 0; i < delegates_.size_; i++) {
        Delegate::Handle* handle = delegates_.data_[i];
        SoundMemory::allocator_->DeleteInstance(handle);
    }
    delegates_.size_ = 0;
    core->audioLock_.Unlock();
}

Result SoundHandle::Stop(float fadeTime) {
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return Result(-12);
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice == nullptr) {
        return Result(-29);
    }
    return set_result(voice->Stop(fadeTime));
}

Result SoundHandle::Play(const SoundEntry* entry, SoundActor* actor, float volume, float fadeTime) {
    if (!valid_) {
        Init();
    } else if (entry_ != nullptr) {
        return Result(-33);
    }
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return Result(-12);
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice != nullptr) {
        voice->Stop(0.0f);
    }
    Result result = Prepare(entry);
    if (result >= 0) {
        result = Start(actor, volume, fadeTime);
    }
    return set_result(result);
}

Result SoundHandle::Prepare(const SoundEntry* entry) {
    if (!valid_) {
        Init();
    } else if (entry_ != nullptr) {
        return Result(-33);
    }
    if (SoundCore::instance_ == nullptr) {
        return Result(-12);
    }
    VoiceHandle* voice;
    static_cast<SystemCore*>(SoundCore::instance_)->AllocVoiceHandle(0, &voice);
    if (voice == nullptr) {
        return Result(-50);
    }
    entry_ = entry;
    Result result = voice->Prepare(entry, this, &voiceId_);
    if (result < 0) {
        static_cast<SystemCore*>(SoundCore::instance_)->FreeVoiceHandle(voice);
    }
    return set_result(result);
}

Result SoundHandle::Start(SoundActor* actor, float volume, float fadeTime) {
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return Result(-12);
    }
    if (entry_ == nullptr) {
        return Result(-20);
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice == nullptr) {
        return Result(-29);
    }
    if (actor == nullptr) {
        actor = core->pad_4a0;
    }
    actor_ = actor;
    const SoundGroup* group = entry_->GetSoundGroup();
    if (group == nullptr) {
        group = &core->group_;
    }
    groupId_ = group->id_;
    category_ = *core->GetCategory(entry_->param_.flag4e_);
    pitch_.Reset(1.0f);
    pan_.Reset(0.0f);
    volume_.Reset(volume);
    startTime_ = SystemCorePlatform::GetSystemTime();
    return set_result(voice->Start(fadeTime, pad_68 != 0.0f));
}

Result SoundHandle::Pause(bool pause, float fadeTime) {
    if (!valid_ || entry_ == nullptr) {
        return Result(-5);
    }
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return Result(-12);
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice == nullptr) {
        return Result(-29);
    }
    return set_result(voice->Pause(pause, fadeTime));
}

int SoundHandle::GetState() const {
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return -1;
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice == nullptr) {
        return 0;
    }
    return voice->state_;
}

bool SoundHandle::IsPlay() const {
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return false;
    }
    return core->GetVoiceHandle(voiceId_) != nullptr;
}

Result SoundHandle::GetPlayTime(float* time) const {
    *time = 0.0f;
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return Result(-12);
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice == nullptr) {
        return Result(-29);
    }
    return set_result(voice->GetPlayTime(time));
}

Result SoundHandle::SetPlayTime(float time) {
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return Result(-12);
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice == nullptr) {
        return Result(-29);
    }
    return set_result(voice->SetPlayTime(time));
}

void SoundHandle::SetCategoryId(int id) {
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core != nullptr) {
        category_ = *core->GetCategory(id);
    }
}

void SoundHandle::SetPitch(float pitch, float fadeTime) {
    pitch_.Set(pitch, fadeTime);
}

void SoundHandle::SetVolume(float volume, float fadeTime) {
    volume_.Set(volume, fadeTime);
}

void SoundHandle::SetPan(float pan, float fadeTime) {
    pan_.Set(pan, fadeTime);
}

Result SoundHandle::GetDataTime(float* time) const {
    *time = 0.0f;
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return Result(-12);
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice == nullptr) {
        return Result(-29);
    }
    const WaveSource* source = voice->stream_ != nullptr ? &voice->stream_->source_ : voice->source_;
    *time = source->loaded_ ? source->format_.data.pad_14 / source->format_.data.sampleRate : 0.0f;
    return set_result(Result(0));
}

float SoundHandle::GetDistanceVolume() const {
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        log_error(Result(-12), Debug::LogFlag::Type(0x7FFFFFFF), TextRef::EmptyText, TextRef::EmptyText);
        return 0.0f;
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice == nullptr) {
        log_error(Result(-29), Debug::LogFlag::Type(2), TextRef::EmptyText, TextRef::EmptyText);
        return 0.0f;
    }
    return voice->pad_6f0;
}

Result SoundHandle::GetRemainLoopCount(int* count) const {
    *count = 0;
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return Result(-12);
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice == nullptr) {
        return Result(-29);
    }
    if (voice->stream_ == nullptr) {
        return Result(-44);
    }
    return set_result(voice->GetRemainLoopCount(count));
}

Result SoundHandle::SetRemainLoopCount(int count) {
    SystemCore* core = static_cast<SystemCore*>(SoundCore::instance_);
    if (core == nullptr) {
        return Result(-12);
    }
    VoiceHandle* voice = core->GetVoiceHandle(voiceId_);
    if (voice == nullptr) {
        return Result(-29);
    }
    if (voice->stream_ == nullptr) {
        return Result(-44);
    }
    if (!voice->stream_->source_.format_.loop.loop) {
        return Result(-1);
    }
    return set_result(voice->SetRemainLoopCount(count));
}

void SoundHandle::UpdateAudioFrame(float frameTime) {
    pitch_.Update(frameTime);
    volume_.Update(frameTime);
}
}  // namespace ssd

template ssd::List<ssd::Delegate::Handle>::Node::~Node();

namespace ssd {

}  // namespace ssd
