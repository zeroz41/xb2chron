#ifndef CLASSES_GF_GFCOMIK_FOOTGROUND_H
#define CLASSES_GF_GFCOMIK_FOOTGROUND_H

#include "classes/gf/GfComIK.h"
#include "classes/fw/IKFootGroundInterface.h"
#include "gf/GfEnvProperty.h"
#include "mm/Plane.h"
#include "mm/Vec3.h"

namespace gf {
// table 0x7100B66398; the ground under one foot
class GfComIK::FootGround : public ::fw::IKFootGroundInterface {
public:
    virtual const mm::Plane* getPlane() const;  // slot 0
    virtual const mm::Vec3* getHitPos() const;  // slot 1
    virtual ~FootGround() {}  // slot 2 (its complete destructor is fw::IKFootGroundInterface's)
    FootGround() : m_result(nullptr), m_index(0) {}

    // (the names are not the original's)
    const GfEnvProperty* m_result;  // the object's property's (setup's)
    int m_index;  // its ground's index in m_result: setup numbers the feet from 1
};
}  // namespace gf

#endif
