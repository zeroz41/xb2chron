#ifndef ML_ATTRTRANSFORM_H
#define ML_ATTRTRANSFORM_H

#include "mm/Mat44.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"

namespace ml {
// a scene object's transform, 0x140 bytes (ScnObjCam's render information starts with one: setLookAt updates it;
// ScnObjModel's and ScnObjLight's per-thread information is one: their getTrans return it). clear sets the
// fields below; the names are not the original's
class AttrTransform {
public:
    void update();
    void clear();

    mm::Vec3 m_pos;     // ScnObjCam::setPos and ScnObjModel::setPos write it; clear zeroes it
    // update starts from a copy of m_pos; fw::NaviManager::update reads the camera's
    mm::Vec3 m_posGbl;
    mm::Vec3 m_scl;     // ScnObjModel::setScl's; clear sets (1, 1, 1)
    mm::Mat44 m_mat;    // ScnObjModel::setMat's; clear sets the identity
    // ScnObjModelDrSysStandard::apply copies it and scales its rows by m_scl for the draw model (the name is not
    // the original's)
    mm::Mat44 m_worldMat;  // 0x70, clear sets the identity
    unsigned char pad_B0[0x40];  // clear sets an identity matrix here
    mm::Vec3 m_rot;     // ScnObjModel::setRot's; clear zeroes it
    unsigned char pad_100[0x10];  // clear zeroes a Vec3 here
    mm::Quat m_quat;    // ScnObjModel::addRot(Quat)'s
    unsigned char pad_120[0x10];  // clear sets an identity Quat here
    unsigned int m_flags;  // clear zeroes it; setMat sets bit 0, addRot(Quat) bit 1
    unsigned char pad_134[0xC];
};
}  // namespace ml

#endif
