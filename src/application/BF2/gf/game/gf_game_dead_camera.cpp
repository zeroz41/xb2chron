#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/Camera.h"
#include "classes/fw/CameraLayer.h"
#include "classes/fw/CameraManager.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/PlayerCameraTarget.h"
#include "classes/gf/GfGameFallDeadCamera.h"
#include "classes/gf/GfDeadCamera.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfDeadCamera::GfDeadCamera(GfPlayerDead dead) {
    if (dead == GfPlayerDead(4)) {
#line 38
        m_camera = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfGameFallDeadCamera();
        if (m_camera) {
            if (fw::CameraManager* manager = fw::CameraManager::get()) {
                manager->m_layer.push(m_camera, 0.0f);
            }
        }
    }
}

GfDeadCamera::~GfDeadCamera() {
    if (m_camera) {
        if (fw::CameraManager* manager = fw::CameraManager::get()) {
            manager->m_layer.pop(m_camera, 0.0f);
        }
        m_camera = nullptr;
    }
}

GfGameFallDeadCamera::~GfGameFallDeadCamera() {}

void GfGameFallDeadCamera::onActivate() {
    if (PlayerCameraTarget* target = PlayerCameraTarget::get()) {
        m_offset = GfInfo::m_camTgt - target->m_position;
    }
    m_target = GfInfo::m_camTgt;
    m_eye = GfInfo::m_camPos;
    m_fov = GfInfo::m_camFov;
    setLookAt(m_eye, m_target, 0.0f);
}

// GfGameFallDeadCamera::update (0x71002A5204) is not matched yet

}  // namespace gf
