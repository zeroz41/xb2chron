#ifndef CLASSES_GF_GFMENUMODELVIEWCAMERA_H
#define CLASSES_GF_GFMENUMODELVIEWCAMERA_H

#include "mm/mtl/RTTI.h"
#include "mm/Vec3.h"
#include "classes/fw/Camera.h"
#include "classes/gf/GimmickCameraParams.h"

namespace gf {
// table 0x7100B5F918: the menus' model viewer camera, standing at a position and looking along unit z turned by Euler
// angles (half angles, a quaternion; updateLookAt). The field names are not the original's (setPos and setRotY
// write them).
class GfMenuModelViewCamera : public ::fw::Camera {
public:
    GfMenuModelViewCamera(const GimmickCameraParams::Param& param);
    virtual ~GfMenuModelViewCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const;  // slot 3
    void updateLookAt();
    void setPos(const mm::Vec3& pos);
    void setRotY(float rotY);
    static mm::mtl::RTTI m_rtti;

    mm::Vec3 m_pos;
    mm::Vec3 m_rot;  // radians
};
}  // namespace gf

#endif
