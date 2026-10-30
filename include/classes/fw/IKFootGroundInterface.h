#ifndef CLASSES_FW_IKFOOTGROUNDINTERFACE_H
#define CLASSES_FW_IKFOOTGROUNDINTERFACE_H

#include "classes/fw/PlaneRayCaster.h"

namespace mm { class Plane; }
namespace mm { class Vec3; }

namespace fw {
// table 0x7100B663C8; the slots' names are gf::GfComIK::FootGround's overrides'
class IKFootGroundInterface {
public:
    // not virtual (the table has no slot for it); gf::GfComIK::FootGround's complete destructor is this one: the
    // derived destructor is replaced by its only base's, so the ray caster is this class's member (GfComIK::setup
    // builds it between this class's table store and FootGround's)
    ~IKFootGroundInterface() {}
    virtual const mm::Plane* getPlane() const = 0;  // slot 0: the ground's plane, none without ground
    virtual const mm::Vec3* getHitPos() const = 0;  // slot 1

    PlaneRayCaster m_rayCaster;  // (the name is not the original's)
};
}  // namespace fw

#endif
