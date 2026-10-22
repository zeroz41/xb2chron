#include "classes/fw/Camera.h"
#include "classes/fw/CameraLayer.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/Framework.h"
#include "classes/gf/ScriptCamera.h"
#include "classes/gf/ScriptCameraEntity.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"

namespace gf {

// the constructor (0x71001D8884) and update (0x71001D8B1C) are not here yet: candidates/gf_camera_script.near.cpp's
// differ only in the operand order of the three additions that make the look-at target

ScriptCameraEntity::~ScriptCameraEntity() {}

void ScriptCameraEntity::onActivate() {}

ScriptCamera::ScriptCamera() {}

ScriptCamera::~ScriptCamera() {}

// start (0x71001D8EB0) is not here yet: candidates/gf_camera_script.near.cpp's tests the new entity for null again
// where the original keeps the first test in a flag

void ScriptCamera::end(float frames) {
    if (!m_camera) {
        return;
    }
    if (m_camera.get()->m_pushed) {
        fw::CameraManager::get()->m_layers[0].pop(m_camera, frames / 30.0f);
    }
    m_camera = nullptr;
}

void ScriptCamera::move(const mm::Vec3& pos, const mm::Vec3& rot, float frames) {
    if (!m_camera) {
        return;
    }
    static_cast<ScriptCameraEntity*>(m_camera.get())->move(pos, rot, frames);
}

const char* ScriptCameraEntity::getName() const {
    return "ScriptCameraEntity";
}

mm::mtl::RTTI ScriptCameraEntity::m_rtti("ScriptCameraEntity", &fw::Camera::m_rtti, nullptr);

}  // namespace gf
