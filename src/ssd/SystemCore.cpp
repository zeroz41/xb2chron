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

namespace ssd {

SoundListener::SoundListener()
    : Object(ObjectType::Id(6)), registered_(false), moved_(false), changed_(false), velocityChanged_(false),
      enableDoppler_(true), scale_(1.0f) {
    Init();
}

SoundListener::~SoundListener() {
    if (registered_) {
        registered_ = false;
        SoundCore::instance_->RemoveSoundListener(this);
    }
}

void SoundListener::Init() {
    if (SoundCore::instance_ != nullptr) {
        SoundCore::instance_->AddSoundListener(this);
        registered_ = true;
    }
}

void SoundListener::SetPosition(const Vec3& position) {
    placement_.position.x = position.x;
    placement_.position.y = position.y;
    placement_.position.z = position.z;
    moved_ = true;
    changed_ = true;
}

void SoundListener::SetOrientation(const Vec3& front, const Vec3& up) {
    placement_.front.x = front.x;
    placement_.front.y = front.y;
    placement_.front.z = front.z;
    placement_.up.x = up.x;
    placement_.up.y = up.y;
    placement_.up.z = up.z;
    moved_ = true;
    changed_ = true;
}

bool SoundListener::IsEnableDoppler() const {
    return enableDoppler_;
}

void SoundListener::Vec3Transform(const Vec3* v, Vec3* out) {
    ssd::Vec3Transform(&matrix_, v, out);
}

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

SoundCore::DebugInfo SystemCore::debugInfo_;

}  // namespace ssd
