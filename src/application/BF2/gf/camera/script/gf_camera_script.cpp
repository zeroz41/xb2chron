#include "classes/gf/ScriptCameraEntity.h"
#include "classes/fw/Camera.h"
#include "classes/fw/CameraLayer.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/Framework.h"
#include "classes/gf/ScriptCamera.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"

namespace gf {

// the constructor (0x71001D8884) is not here yet: the body in ctor_candidate.cpp differs only in the operand order
// of the first of the three additions that make the look-at target (the direction's x plus m_pos.x)

ScriptCameraEntity::~ScriptCameraEntity() {}

void ScriptCameraEntity::onActivate() {}

void ScriptCameraEntity::update(const fw::UpdateInfo& info) {
    if (m_frames > 0.0f) {
        calcSpeedTypeLinearSpacing();
        m_frame += info.m_deltaTime / (1.0f / 30.0f);
        if (m_frames < m_frame) {
            m_frame = m_frames;
        }
    }
    mm::Vec3 target;
    target = getDirection();
    target += m_pos;
    setLookAt(m_pos, target, m_rot.z);
}

ScriptCamera::ScriptCamera() {}

ScriptCamera::~ScriptCamera() {}

void ScriptCamera::start(const mm::Vec3& pos, const mm::Vec3& rot, float frames) {
    if (m_camera) {
        return;
    }
    m_camera = ScriptCameraEntity::create(pos, rot);
    float time = frames / 30.0f;
    fw::CameraManager::get()->m_layers[0].push(m_camera, time);
}

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
