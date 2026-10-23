#ifndef CLASSES_GF_GFCOMIK_FOOTGROUND_H
#define CLASSES_GF_GFCOMIK_FOOTGROUND_H

#include "classes/gf/GfComIK.h"
#include "classes/fw/IKFootGroundInterface.h"
#include "classes/fw/PlaneRayCaster.h"
#include "mm/Plane.h"
#include "mm/Vec3.h"

namespace gf {
// what the ground solvers' results hold for the object (GfComProperty's; GfComIK's grounds read it). The class and
// field names are not the original's.
struct IKGroundResult {
    struct Hit {
        mm::Vec3 pos;
        mm::Plane plane;
        unsigned char pad_30[0x20];
    };
    // the hit at an index holds while bit index + 1 of m_flags is set (0 the main ground, 1-6 the feet, 7 the sub
    // ground: the grounds' getPlane and getHitPos read them so)
    Hit m_hits[8];
    unsigned char pad_280[0x50];
    unsigned int m_flags;
    bool m_valid;  // the grounds read none of it while clear
};

// table 0x7100B66398; the ground under one foot
class GfComIK::FootGround : public ::fw::IKFootGroundInterface {
public:
    virtual const mm::Plane* getPlane() const;  // slot 0
    virtual const mm::Vec3* getHitPos() const;  // slot 1
    virtual ~FootGround() {}  // slot 2 (its complete destructor is fw::IKFootGroundInterface's)

    // (the names are not the original's)
    fw::PlaneRayCaster m_rayCaster;
    const IKGroundResult* m_result;
    int m_index;  // its hit's index in m_result: setup numbers the feet from 1
};
}  // namespace gf

#endif
