#include "classes/ssd/Allocator.h"
#include "classes/ssd/List.h"
#include "classes/ssd/TextRef.h"
#include "classes/ssd/TextFixedBase.h"
#include "classes/ssd/TextFixed.h"
#include "classes/ssd/Array.h"
#include "classes/ssd/SoundParam.h"
#include "classes/ssd/SoundGroup.h"
#include "classes/ssd/WaveSource.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/SoundEntry.h"
#include "classes/ssd/SoundBank.h"
#include "classes/ssd/SoundBank.h"
#include "classes/ssd/SoundCore.h"
#include "classes/ssd/SoundEntry.h"
#include "classes/ssd/SoundGroup.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/WaveSource.h"
#include "ssd/Debug.h"

namespace ssd {

SoundEntry::SoundEntry() : Object(ObjectType::Id(2)), source_(nullptr), bank_(nullptr), deleteOnRemove_(false) {}

SoundEntry::~SoundEntry() {}

SoundBank::SoundBank() : Object(ObjectType::Id(3)), id_(-1) {}

SoundBank::~SoundBank() {
    if (id_ >= 0) {
        Quit();
    }
    id_ = -1;
}

Result SoundBank::Quit() {
    SoundCore* core = SoundCore::instance_;
    if (core == nullptr) {
        return Result(-1);
    }
    if (id_ < 0) {
        return Result(-14);
    }
    if (GetReferenceCounter() != 0) {
        return Result(-120);
    }
    if (NumSoundEntry() != 0) {
        return Result(-122);
    }
    SystemCore* system = static_cast<SystemCore*>(core);
    system->audioLock_.Lock();
    SoundEntry* entry = static_cast<SoundEntry*>(entries_.head_.next);
    while (entry != static_cast<SoundEntry*>(&entries_.head_)) {
        SoundEntry* next = static_cast<SoundEntry*>(static_cast<List<SoundEntry>::Node*>(entry)->next);
        entries_.Remove(entry);
        entry = next;
    }
    groups_.size_ = 0;
    system->audioLock_.Unlock();
    system->RemoveBank(this);
    if (groups_.data_ != nullptr) {
        SoundMemory::allocator_->DeleteInstance(groups_.data_);
    }
    groups_.size_ = 0;
    groups_.capacity_ = 0;
    groups_.data_ = nullptr;
    id_ = -1;
    return set_result(Result(0));
}

Result SoundBank::Init(int id, const TextRef& name) {
    SoundCore* core = SoundCore::instance_;
    if (core == nullptr) {
        return Result(-1);
    }
    id_ = id;
    name_.Set(name);
    static_cast<SystemCore*>(core)->AddBank(this);
    return set_result(Result(0));
}

int SoundBank::GetReferenceCounter() const {
    if (SoundCore::instance_ == nullptr) {
        return 0;
    }
    if (id_ < 0) {
        return 0;
    }
    int count = 0;
    const SoundEntry* entry = static_cast<const SoundEntry*>(entries_.head_.next);
    while (entry != static_cast<const SoundEntry*>(&entries_.head_)) {
        count += entry->source_->referenceCount_;
        entry = static_cast<const SoundEntry*>(static_cast<const List<SoundEntry>::Node*>(entry)->next);
    }
    return count;
}

int SoundBank::NumSoundEntry() const {
    return entries_.count_;
}

SoundEntry* SoundBank::AddSoundEntry(SoundEntry* entry) {
    SoundCore* core = SoundCore::instance_;
    if (core == nullptr || id_ < 0) {
        return nullptr;
    }
    entry->bank_ = this;
    SystemCore* system = static_cast<SystemCore*>(core);
    system->audioLock_.Lock();
    entries_.PushBack(entry);
    system->audioLock_.Unlock();
    return entry;
}

Result SoundBank::RemoveSoundEntry(SoundEntry* entry) {
    SoundCore* core = SoundCore::instance_;
    if (core == nullptr) {
        return Result(-12);
    }
    if (id_ < 0) {
        return Result(-14);
    }
    if (entry == nullptr) {
        return Result(-6);
    }
    SystemCore* system = static_cast<SystemCore*>(core);
    system->audioLock_.Lock();
    entries_.Remove(entry);
    system->audioLock_.Unlock();
    if (entry->deleteOnRemove_) {
        SoundMemory::allocator_->DeleteInstance(entry);
    }
    return set_result(Result(0));
}

Result SoundBank::Stop(float fadeTime) {
    SoundCore* core = SoundCore::instance_;
    if (core == nullptr) {
        return Result(-12);
    }
    if (id_ < 0) {
        return Result(-14);
    }
    static_cast<SystemCore*>(core)->StopBank(this, fadeTime);
    return set_result(Result(0));
}

}  // namespace ssd
