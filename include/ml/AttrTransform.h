#ifndef ML_ATTRTRANSFORM_H
#define ML_ATTRTRANSFORM_H

#include "mm/Vec3.h"

namespace ml {
// a scene object's transform (ScnObjCam's render information starts with one: setLookAt updates it)
class AttrTransform {
public:
    void update();
    void clear();

    mm::Vec3 m_pos;     // ScnObjCam::setPos writes it; clear zeroes it (the name is not the original's)
    // update starts from a copy of m_pos; fw::NaviManager::update reads the camera's (the name is not the
    // original's)
    mm::Vec3 m_posGbl;
};
}  // namespace ml

#endif
