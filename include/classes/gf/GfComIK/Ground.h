#ifndef CLASSES_GF_GFCOMIK_GROUND_H
#define CLASSES_GF_GFCOMIK_GROUND_H

#include "classes/gf/GfComIK.h"
#include "classes/gf/GfComIK/FootGround.h"
#include "classes/fw/IKGroundInterface.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
// table 0x7100B66350; the ground the object's ground solvers stand on
class GfComIK::Ground : public ::fw::IKGroundInterface {
public:
    Ground() {}
    virtual fw::IKFootGroundInterface* getFootGround(fw::IKFootIndex index);  // slot 0
    virtual const mm::Plane* getPlane() const;  // slot 1
    virtual const mm::Vec3* getHitPos() const;  // slot 2
    virtual const mm::Plane* getPlaneSub() const;  // slot 3
    virtual const mm::Vec3* getHitPosSub() const;  // slot 4
    virtual ~Ground();  // slot 5

    // m_result and one foot ground on it per foot, numbered from 1 (inline: the name is not the original's)
    void setup(const GfEnvProperty* result, unsigned int footCount) {
        m_result = result;
        m_feet.resize(footCount, FootGround());
        for (unsigned int i = 0; i < footCount; i++) {
            FootGround& foot = m_feet[i];
            foot.m_result = result;
            foot.m_index = i + 1;
        }
    }

    // (the names are not the original's)
    const GfEnvProperty* m_result;  // the object's property's (setup's)
    mm::mtl::FixedVector<FootGround, 6> m_feet;  // one per foot, setup's
};
}  // namespace gf

#endif
