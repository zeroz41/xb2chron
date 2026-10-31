#include "classes/ssd/SoundListener.h"
#include "classes/ssd/SoundCore.h"
#include "ssd/Math.h"

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

}  // namespace ssd
