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
                manager->m_layers[0].push(m_camera, 0.0f);
            }
        }
    }
}

GfDeadCamera::~GfDeadCamera() {
    if (m_camera) {
        if (fw::CameraManager* manager = fw::CameraManager::get()) {
            manager->m_layers[0].pop(m_camera, 0.0f);
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

void GfGameFallDeadCamera::update(const fw::UpdateInfo&) {
    // the look-at point is picked per branch (the original passes it from each): the player's position plus the
    // offset taken on activation while there is a player, else the last one
    const mm::Vec3* lookAt;
    if (PlayerCameraTarget* target = PlayerCameraTarget::get()) {
        mm::Vec3 position = target->m_position + m_offset;
        m_target = position;
        lookAt = &m_target;
    } else {
        lookAt = &m_target;
    }
    setLookAt(m_eye, *lookAt, 0.0f);
}

}  // namespace gf
