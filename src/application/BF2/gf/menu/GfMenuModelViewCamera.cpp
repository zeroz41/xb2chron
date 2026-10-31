#include "classes/gf/GimmickCameraParams.h"
#include "classes/gf/GfMenuModelViewCamera.h"
#include "mm/Quat.h"
#include "math.h"

namespace gf {

mm::mtl::RTTI GfMenuModelViewCamera::m_rtti("GfMenuModelViewCamera", &fw::Camera::m_rtti, nullptr);

GfMenuModelViewCamera::GfMenuModelViewCamera(const GimmickCameraParams::Param& param) : fw::Camera(fw::CAMERA_PRIO(55)) {
    m_pos = mm::Vec3(param.m_pos[0], param.m_pos[1], param.m_pos[2]);
    m_rot = mm::Vec3(param.m_rot[0], param.m_rot[1], param.m_rot[2]);
    updateLookAt();
}

void GfMenuModelViewCamera::updateLookAt() {
    mm::Vec3 eye(m_pos.x, m_pos.y, m_pos.z);
    mm::Vec3 target(0.0f, 0.0f, 1.0f);
    mm::Quat base = mm::Quat::identity;
    mm::Vec3 rot = m_rot;
    mm::Vec3 half = rot * 0.5f;
    float sx = ::sinf(half.x), cx = ::cosf(half.x), sy = ::sinf(half.y), cy = ::cosf(half.y), sz = ::sinf(half.z),
          cz = ::cosf(half.z);
    mm::Quat euler(sx * cy * cz - cx * sy * sz, cx * sy * cz + sx * cy * sz, cx * cy * sz - sx * sy * cz,
                   cx * cy * cz + sx * sy * sz);
    mm::Quat rotation = base * euler;
    rotation.rotate(target, target);
    target += eye;
    setLookAt(eye, target, 0.0f);
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
