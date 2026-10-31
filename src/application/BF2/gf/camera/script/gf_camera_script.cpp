#include "classes/gf/ScriptCameraEntity.h"
#include "classes/fw/Camera.h"
#include "classes/fw/CameraLayer.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/Framework.h"
#include "classes/gf/ScriptCamera.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"

namespace gf {

ScriptCameraEntity::ScriptCameraEntity(const mm::Vec3& pos, const mm::Vec3& rot)
    : ::fw::Camera(static_cast< ::fw::CAMERA_PRIO>(0x37)), m_startPos(pos), m_startRot(rot), m_endPos(pos),
      m_endRot(rot), m_pos(pos), m_rot(rot), m_frames(0.0f), m_frame(0.0f) {
    m_fov = 45.0f;
    m_nearClip = 0.4f;
    m_farClip = 80000.0f;
    mm::Vec3 target;
    getDirection(target);
    target += m_pos;
    setLookAt(m_pos, target, m_rot.z);
}

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
    getDirection(target);
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
