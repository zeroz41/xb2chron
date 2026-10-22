#ifndef CLASSES_GF_SUBVIEWCAMERA_H
#define CLASSES_GF_SUBVIEWCAMERA_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/Vec3.h"
#include "classes/fw/Camera.h"

namespace fw { class UpdateInfo; }

namespace gf {
// which sub view a SubViewCamera serves (GfGameCamera::createSubViewCamera creates one per value)
enum VIEWCAM {};

// table 0x7100B45E08
class SubViewCamera : public ::fw::Camera {
public:
    SubViewCamera();  // inline in gf_camera_subview.cpp: it starts from the file's default eye and target
    virtual ~SubViewCamera();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual const char* getName() const;  // slot 3
    virtual void onActivate();  // slot 6
    virtual void update(fw::UpdateInfo const&);  // slot 8
    static mm::mtl::IntrusivePtr<SubViewCamera> create(VIEWCAM viewCam);
    static mm::mtl::RTTI m_rtti;

    VIEWCAM m_viewCam;  // create's argument
    mm::Vec3 m_eye;  // update looks from it
    mm::Vec3 m_target;  // update looks at it
};
}  // namespace gf

#endif
