#ifndef CLASSES_FW_IKFOOTGROUNDINTERFACE_H
#define CLASSES_FW_IKFOOTGROUNDINTERFACE_H

namespace mm { class Plane; }
namespace mm { class Vec3; }

namespace fw {
// table 0x7100B663C8; the slots' names are gf::GfComIK::FootGround's overrides'
class IKFootGroundInterface {
public:
    // not virtual (the table has no slot for it); gf::GfComIK::FootGround's complete destructor is this one
    ~IKFootGroundInterface() {}
    virtual const mm::Plane* getPlane() const = 0;  // slot 0: the ground's plane, none without ground
    virtual const mm::Vec3* getHitPos() const = 0;  // slot 1
};
}  // namespace fw

#endif
