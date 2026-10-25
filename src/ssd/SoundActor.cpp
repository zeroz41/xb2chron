#include "ssd/Debug.h"
#include "classes/ssd/Array.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SystemCore.h"
#include "classes/ssd/SoundActor.h"
#include "classes/ssd/SoundActor3D.h"
#include "classes/ssd/SoundActor.h"
#include "classes/ssd/SoundActor3D.h"
#include "classes/ssd/Array.h"
#include "classes/ssd/SoundHandle.h"
#include "classes/ssd/SystemCore.h"

namespace ssd {

SoundActor::SoundActor() : SoundActor(ObjectType::Id(8)) {}

SoundActor::~SoundActor() {
    Quit();
}

Result SoundActor::Init() {
    if (connected_) {
        return Result(-15);
    }
    static_cast<SystemCore*>(SoundCore::instance_)->ConnectActor(this);
    connected_ = true;
    return set_result(Result(0));
}

Result SoundActor::Quit() {
    if (!connected_) {
        return Result(-15);
    }
    connected_ = false;
    static_cast<SystemCore*>(SoundCore::instance_)->DisconnectActor(this);
    return set_result(Result(0));
}

Result SoundActor::Stop(float fadeTime) {
    static_cast<SystemCore*>(SoundCore::instance_)->StopActor(this, fadeTime);
    return Result(0);
}

Result SoundActor::Pause(bool pause, float fadeTime) {
    static_cast<SystemCore*>(SoundCore::instance_)->PauseActor(this, pause, fadeTime);
    return Result(0);
}

void SoundActor::SetVolume(float volume, float fadeTime) {
    volume_ = volume;
}

void SoundActor::SetCategoryId(int id) {
    SoundCore* core = SoundCore::instance_;
    Array<SoundHandle*> handles;
    core->LockAudio();
    static_cast<SystemCore*>(core)->GetPlaySoundHandleFromActor(this, &handles);
    for (SoundHandle* handle : handles) {
        handle->SetCategoryId(id);
    }
    core->UnlockAudio();
}

void SoundActor::UpdateGameFrame(float) {}

SoundActor3D::SoundActor3D()
    : SoundActor(ObjectType::Id(9)), velocity_{0.0f, 0.0f, 0.0f}, pad_68(true), positionSet_(false), pad_6a(0), velocitySet_(false), listener_(nullptr) {
    is3D_ = true;
}

SoundActor3D::~SoundActor3D() {}

Result SoundActor3D::Init() {
    SoundActor::Init();
    positionSet_ = false;
    velocitySet_ = false;
    listener_ = nullptr;
    return Result(0);
}

void SoundActor3D::SetListener(const SoundListener* listener) {
    listener_ = listener;
}

void SoundActor3D::SetPosition(const Vec3& position) {
    position_.x = position.x;
    position_.y = position.y;
    position_.z = position.z;
    positionSet_ = true;
}

void SoundActor3D::SetVelocity(const Vec3& velocity) {
    velocity_.x = velocity.x;
    velocity_.y = velocity.y;
    velocity_.z = velocity.z;
    velocitySet_ = true;
}

void SoundActor3D::UpdateGameFrame(float) {
    if (positionSet_) {
        if (!velocitySet_) {
            Vec3 velocity = {lastPosition_.x - position_.x, lastPosition_.y - position_.y,
                             lastPosition_.z - position_.z};
            velocity_ = velocity;
        }
        lastPosition_ = position_;
        velocitySet_ = false;
        positionSet_ = false;
    }
}

}  // namespace ssd
