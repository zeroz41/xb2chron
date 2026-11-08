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
    // only the flags: threadval's buffers of transforms are built with a zero at 0x130 each
    AttrTransform() : m_flags(0) {}
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
    mm::Mat44 pad_B0;  // clear sets the identity
    mm::Vec3 m_rot;     // ScnObjModel::setRot's; clear zeroes it
    // clear zeroes it; a Vec3: ScnDebugManipu::setTrans's copy copies its three floats one by one
    mm::Vec3 pad_100;
    mm::Quat m_quat;    // ScnObjModel::addRot(Quat)'s
    mm::Quat pad_120;  // clear sets the identity
    unsigned int m_flags;  // clear zeroes it; setMat sets bit 0, addRot(Quat) bit 1
    // 0x134-0x140 is tail padding: ScnDebugManipu::setTrans's copy ends its last memcpy at m_flags
};
}  // namespace ml

#endif
