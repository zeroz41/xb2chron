#include "classes/ssd/SoundListener.h"
#include "classes/ssd/SoundParam.h"
#include "classes/ssd/TextRef.h"
#include "ssd/Text.h"
#include "classes/ssd/SoundCore.h"
#include "classes/ssd/SystemCorePlatform.h"
#include "classes/ssd/BehaviorInstance.h"
#include "classes/ssd/XorShift128Random.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SoundEntry.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/VoiceHandle.h"
#include "classes/ssd/SoundBank.h"
#include "classes/ssd/StreamController.h"
#include "classes/ssd/SoundActor.h"
#include "ssd/Debug.h"

namespace ssd {

void SoundParam::Init() {
    name_.text_[0] = 0;
    flag4c_ = false;
    groupId_ = 1;
    flag4e_ = true;
    value54_ = 0.0f;
    flag4f_ = false;
    value50_ = 1.0f;
    value58_ = 1.0f;
    value5c_ = 0.0f;
    flag60_ = false;
    flag61_ = false;
    flag62_ = false;
    flag63_ = false;
    flag64_ = false;
    flag65_ = false;
    flag66_ = false;
    flag67_ = false;
    flag68_ = false;
    flag69_ = true;
    flag6a_ = true;
    flag6b_ = false;
    flag6c_ = false;
    flag6d_ = false;
    flag6e_ = false;
    flag6f_ = false;
    flag70_ = false;
    flag71_ = false;
    flag72_ = false;
    flag73_ = false;
    value74_ = 1.0f;
    value78_ = 100.0f;
    value7c_ = 0.0f;
    value80_ = 1.0f;
    value84_ = 0.0f;
    value88_ = 1.0f;
    value8c_ = 0;
    value90_ = 1.0f;
}

SoundParam::Name& SoundParam::Name::operator=(const TextRef& text) {
    if (text.type_ == TextEncodeType_Utf8) {
        Utf8ToUTF16(text.utf8_, text_, 0x20);
        hash_.Clear();
        hash_.CalcTextHash(text_);
    } else {
        CopyText(text_, text.tchar_, 0x20);
        hash_.Clear();
        hash_ = text.hash_;
    }
    return *this;
}

SystemCore::SystemCore() : pad_2e8(), pad_4a0(nullptr) {}

SystemCore::~SystemCore() {}

void SystemCore::SetMasterVolume(float volume, float fadeTime) {
    masterVolume_.Start(this, &SystemCore::MasterVolumeBehavior, volume, fadeTime);
}

void SystemCore::MasterVolumeBehavior(float frameTime) {}

void SystemCore::SetMasterPitch(float pitch, float fadeTime) {
    masterPitch_.Start(this, &SystemCore::MasterPitchBehavior, pitch, fadeTime);
}

void SystemCore::MasterPitchBehavior(float frameTime) {}

OutputMode::Type SystemCore::GetOutputMode() const {
    return outputMode_;
}

void SystemCore::SetOutputMode(OutputMode::Type mode) {
    outputMode_ = mode;
}

float SystemCore::GetMasterVolume() const {
    return masterVolume_.value_;
}

float SystemCore::GetMasterPitch() const {
    return masterPitch_.value_;
}

int SystemCore::GetNumPlaySound() const {
    return playVoices_.count_;
}

float SystemCore::GetSpeedOfSound() const {
    return speedOfSound_;
}

void SystemCore::SetSpeedOfSound(float speed) {
    speedOfSound_ = speed;
}

double SystemCore::GetAudioCpuLoad() const {
    const CpuLoad& load = cpuLoad_[1 - cpuLoadIndex_];
    if (load.frameTime != 0.0) {
        return load.processTime / load.frameTime;
    }
    return 0.0;
}

void SystemCore::LockAudio() const {
    audioLock_.Lock();
}

void SystemCore::UnlockAudio() const {
    audioLock_.Unlock();
}

const SoundCore::DebugInfo* SystemCore::GetDebugInfo() const {
    return &debugInfo_;
}

Result SystemCore::SetCategory(const SoundCategory& category) {
    if (category.id_ == 0) {
        return Result(-1);
    }
    for (int i = 1; i < categories_.size_; i++) {
        if (categories_.data_[i].id_ == category.id_) {
            categories_.data_[i] = category;
            {
                ScopedLock lock(audioLock_);
                for (VoiceHandle* voice = static_cast<VoiceHandle*>(playVoices_.head_.next);
                     voice != static_cast<VoiceHandle*>(&playVoices_.head_);
                     voice = static_cast<VoiceHandle*>(voice->next)) {
                    SoundHandle* handle = voice->handle_;
                    if (handle != nullptr && handle->category_.id_ == category.id_) {
                        handle->category_ = category;
                    }
                }
            }
            return set_result(Result(0));
        }
    }
    ScopedLock lock(audioLock_);
    int size = categories_.size_;
    if (categories_.capacity_ <= size) {
        categories_.SetSize(categories_.capacity_ + 16);
    }
    categories_.data_[categories_.size_] = category;
    categories_.size_++;
    return set_result(Result(0));
}

SoundCategory* SystemCore::GetCategory(int id) const {
    SoundCategory* category = categories_.data_;
    if (id != 0) {
        for (SoundCategory* it = categories_.data_; it != categories_.data_ + categories_.size_; ++it) {
            if (it->id_ == id) {
                return it;
            }
        }
    }
    return category;
}

Result SystemCore::GetCategory(int id, SoundCategory* category) const {
    for (SoundCategory* it = categories_.data_; it != categories_.data_ + categories_.size_; ++it) {
        if (it->id_ == id) {
            *category = *it;
            return set_result(Result(0));
        }
    }
    return set_result(Result(-42));
}

Result SystemCore::AllocVoiceHandle(int kind, VoiceHandle** voice) {
    VoiceHandle* handle = static_cast<VoiceHandle*>(freeVoices_.head_.next);
    if (static_cast<VoiceHandle*>(&freeVoices_.head_) == handle) {
        handle = nullptr;
    } else {
        freeVoices_.Remove(handle);
        playVoices_.PushBack(handle);
        int serial = voiceSerial_;
        handle->state_ = 5;
        handle->allocated_ = 1;
        handle->id_ = handle->index_ + (serial << 8);
        voiceSerial_ = voiceSerial_ > 0xFFFFE ? 1 : voiceSerial_ + 1;
        handle->source_ = nullptr;
    }
    *voice = handle;
    return set_result(Result(0));
}

void SystemCore::FreeVoiceHandle(VoiceHandle* voice) {
    playVoices_.Remove(voice);
    freeVoices_.PushBack(voice);
    voice->state_ = 0;
    voice->handle_ = nullptr;
    voice->id_ = 0;
    set_result(Result(0));
}

VoiceHandle* SystemCore::GetVoiceHandle(unsigned int id) const {
    set_result(Result(0));
    if (id == 0) {
        return nullptr;
    }
    unsigned int index = id & 0xFF;
    VoiceHandle* voice = &voices_[index];
    return voice->id_ == id ? voice : nullptr;
}

void SystemCore::StopActor(SoundActor* actor, float fadeTime) {
    set_result(Result(0));
    ScopedLock lock(audioLock_);
    for (VoiceHandle* voice = static_cast<VoiceHandle*>(playVoices_.head_.next);
         voice != static_cast<VoiceHandle*>(&playVoices_.head_); voice = static_cast<VoiceHandle*>(voice->next)) {
        SoundHandle* handle = voice->handle_;
        if (handle != nullptr && handle->actor_ == actor) {
            handle->Stop(fadeTime);
        }
    }
}

void SystemCore::PauseActor(SoundActor* actor, bool pause, float fadeTime) {
    set_result(Result(0));
    ScopedLock lock(audioLock_);
    for (VoiceHandle* voice = static_cast<VoiceHandle*>(playVoices_.head_.next);
         voice != static_cast<VoiceHandle*>(&playVoices_.head_); voice = static_cast<VoiceHandle*>(voice->next)) {
        SoundHandle* handle = voice->handle_;
        if (handle != nullptr && handle->actor_ == actor) {
            handle->Pause(pause, fadeTime);
        }
    }
}

int SystemCore::GetPlaySoundHandleFromActor(const SoundActor* actor, Array<SoundHandle*>* handles) const {
    set_result(Result(0));
    ScopedLock lock(audioLock_);
    for (const VoiceHandle* voice = static_cast<const VoiceHandle*>(playVoices_.head_.next);
         voice != static_cast<const VoiceHandle*>(&playVoices_.head_); voice = static_cast<const VoiceHandle*>(voice->next)) {
        SoundHandle* handle = voice->handle_;
        if (handle != nullptr && handle->actor_ == actor) {
            int size = handles->size_;
            if (handles->capacity_ <= size) {
                handles->SetArraySize(handles->capacity_ + 16);
            }
            handles->data_[handles->size_] = handle;
            handles->size_++;
        }
    }
    return handles->size_;
}

void SystemCore::ConnectActor(SoundActor* actor) {
    ScopedLock lock(audioLock_);
    actors_.PushBack(actor);
    actor->linked_ = true;
}

void SystemCore::DisconnectActor(SoundActor* actor) {
    ScopedLock lock(audioLock_);
    for (VoiceHandle* voice = static_cast<VoiceHandle*>(playVoices_.head_.next);
         voice != static_cast<VoiceHandle*>(&playVoices_.head_); voice = static_cast<VoiceHandle*>(voice->next)) {
        SoundHandle* handle = voice->handle_;
        if (handle != nullptr && handle->actor_ == actor) {
            handle->actor_ = nullptr;
        }
    }
    if (actor->linked_) {
        actor->linked_ = false;
        actors_.Remove(actor);
    }
}

void SystemCore::StopSound(float fadeTime) {
    set_result(Result(0));
    ScopedLock lock(audioLock_);
    for (VoiceHandle* voice = static_cast<VoiceHandle*>(playVoices_.head_.next);
         voice != static_cast<VoiceHandle*>(&playVoices_.head_); voice = static_cast<VoiceHandle*>(voice->next)) {
        if (voice->handle_ != nullptr) {
            voice->handle_->Stop(fadeTime);
        }
    }
}

void SystemCore::RemoveBank(SoundBank* bank) {
    ScopedLock lock(audioLock_);
    banks_.Remove(bank);
    set_result(Result(0));
}

void SystemCore::AddBank(SoundBank* bank) {
    ScopedLock lock(audioLock_);
    banks_.PushBack(bank);
    set_result(Result(0));
}

void SystemCore::StopBank(SoundBank* bank, float fadeTime) {
    ScopedLock lock(audioLock_);
    for (VoiceHandle* voice = static_cast<VoiceHandle*>(playVoices_.head_.next);
         voice != static_cast<VoiceHandle*>(&playVoices_.head_); voice = static_cast<VoiceHandle*>(voice->next)) {
        if (voice->entry_->bank_ == bank) {
            voice->handle_->Stop(fadeTime);
        }
    }
    set_result(Result(0));
}

void SystemCore::AddSoundListener(SoundListener* listener) {
    ScopedLock lock(audioLock_);
    int index = -1;
    for (int i = 0; i < listeners_.size_; i++) {
        if (listeners_.data_[i] == listener) {
            index = i;
            break;
        }
    }
    if (index < 0) {
        int size = listeners_.size_;
        if (listeners_.capacity_ <= size) {
            listeners_.SetArraySize(listeners_.capacity_ + 16);
        }
        listeners_.data_[listeners_.size_] = listener;
        listeners_.size_++;
    }
    // a listener added again rebuilds its matrix
    listener->dirty_.changed = true;
}

void SystemCore::StreamThreadEntry(SystemCore* core, void* userData) {
    core->StreamThreadImpl();
}

void SystemCore::AudioThreadEntry(SystemCore* core, void* userData) {
    core->startTime_ = core->GetSystemTime();
    core->frameStartTime_ = core->startTime_;
    while (!core->audioThread_.closing_) {
        nn::os::WaitSystemEvent(core->systemEvent_.GetBase());
        double time = core->audioFrameCount_ / core->audioFrameRate_;
        core->appliedFrameRate_ = core->audioFrameRate_;
        core->audioTime_ = time;
        core->AudioFrameProcess();
        core->audioFrameCount_++;
    }
}

void SystemCore::AddStreamController(StreamController* controller) {
    ScopedLock lock(audioLock_);
    streams_.PushBack(controller);
}

void SystemCore::RemoveStreamController(StreamController* controller) {
    ScopedLock lock(audioLock_);
    streams_.Remove(controller);
}

Result SystemCore::GetSoundEffectList(int max, SoundEffecter** effects, int* count) {
    ScopedLock lock(audioLock_);
    int n = 0;
    for (int i = 0; i < 2; i++) {
        if (effectBus_[i].effect != nullptr && n < max) {
            n++;
            effects[i] = effectBus_[i].effect;
        }
    }
    return Result(0);
}

bool SystemCore::IsActiveEffect(unsigned char bus) {
    if (bus >= 2) {
        return false;
    }
    return effectBus_[bus].effect != nullptr || effectBus_[bus].activeFlags[0] || effectBus_[bus].activeFlags[1];
}

Result SystemCore::AddSoundEffecter(unsigned char bus, SoundEffecter* effect) {
    ScopedLock lock(audioLock_);
    return InitEffect(bus, effect);
}

Result SystemCore::RemoveSoundEffecter(SoundEffecter* effect) {
    ScopedLock lock(audioLock_);
    return QuitEffect(effect);
}

SoundCore::DebugInfo SystemCore::debugInfo_;

}  // namespace ssd
