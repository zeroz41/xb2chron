#include "classes/gf/GimmickCameraParams.h"
#include "classes/gf/GfMenuModelViewCamera.h"

namespace gf {

mm::mtl::RTTI GfMenuModelViewCamera::m_rtti("GfMenuModelViewCamera", &fw::Camera::m_rtti, nullptr);

GfMenuModelViewCamera::GfMenuModelViewCamera(const GimmickCameraParams::Param& param) : fw::Camera(fw::CAMERA_PRIO(55)) {
    m_pos = mm::Vec3(param.m_pos[0], param.m_pos[1], param.m_pos[2]);
    m_rot = mm::Vec3(param.m_rot[0], param.m_rot[1], param.m_rot[2]);
    updateLookAt();
}

GfMenuModelViewCamera::~GfMenuModelViewCamera() {
    ;  // a statement the build compiles away: the table store stays
}

void GfMenuModelViewCamera::setPos(const mm::Vec3& pos) {
    m_pos = pos;
    updateLookAt();
}

void GfMenuModelViewCamera::setRotY(float rotY) {
    m_rot.y = rotY;
    updateLookAt();
}

const char* GfMenuModelViewCamera::getName() const {
    return "GfMenuModelViewCamera";
}

}  // namespace gf
