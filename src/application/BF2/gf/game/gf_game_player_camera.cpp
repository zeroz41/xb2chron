#include "classes/gf/IGfEvent.h"
#include "classes/fw/MessageObject.h"
#include "classes/fw/CameraTarget.h"
#include "classes/fw/CameraManager.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/PlayerCamera.h"
#include "classes/gf/PlayerCameraTarget.h"
#include "gf/MsgPcResetCamera.h"
#include "classes/gf/GfGamePlayerCamera.h"
#include "classes/fw/CameraLayer.h"
#include "classes/gf/GfAllocator.h"
#include "fw/Message.h"

namespace gf {

void GfGamePlayerCamera::build(const GfSetupParam& param) {
#line 29
    GfGamePlayerCamera* camera = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGamePlayerCamera();
    camera->setup();
}

void GfGamePlayerCamera::destroy() {
    GfGamePlayerCamera* camera = get();
    camera->cleanup();
    delete camera;
}

void GfGamePlayerCamera::cleanup() {
    GfEvent::removeEventCallback(this);
    if (m_target) {
        m_target = nullptr;
        if (fw::CameraManager* manager = fw::CameraManager::get()) {
            manager->m_target = m_target;
        }
    }
    if (m_camera) {
        if (fw::CameraManager* manager = fw::CameraManager::get()) {
            manager->m_layers[0].pop(m_camera, 0.0f);
        }
        m_camera = nullptr;
    }
}

void GfGamePlayerCamera::resetCameraForSceneJump() {
    GfGamePlayerCamera* self = get();
    if (self == nullptr) {
        return;
    }
    fw::CameraManager* manager = fw::CameraManager::get();
    if (manager == nullptr) {
        return;
    }
    if (self->m_camera) {
        manager->m_layers[0].pop(self->m_camera, 0.0f);
        self->m_camera = nullptr;
    }
    self->m_camera = PlayerCamera::create();
    manager->m_layers[0].push(self->m_camera, 0.0f);
}

void GfGamePlayerCamera::resetCamera() {
    if (PlayerCamera* camera = getPlayerCamera()) {
        camera->reset();
    }
}

void GfGamePlayerCamera::requestResetCamera() {
    GfGamePlayerCamera* self = get();
    if (self == nullptr) {
        return;
    }
    if (self->m_target) {
        self->m_target->requestResetCamera();
    }
}

void GfGamePlayerCamera::resetCameraClimb(ResetCameraWallTiming timing) {
    if (PlayerCamera* camera = getPlayerCamera()) {
        camera->resetClimb(timing);
    }
}

void GfGamePlayerCamera::resetCameraLoad() {
    if (PlayerCamera* camera = getPlayerCamera()) {
        camera->resetLoad();
    }
}

void GfGamePlayerCamera::resetCameraBattleWarp() {
    if (PlayerCamera* camera = getPlayerCamera()) {
        camera->resetBattleWarp();
    }
}

void GfGamePlayerCamera::setTargetObject(GF_OBJ_HANDLE* handle) {
    if (PlayerCamera* camera = getPlayerCamera()) {
        camera->setTarget(handle);
    }
}

bool GfGamePlayerCamera::isManualCamera() {
    bool hasCamera = false;
    bool manual;
    if (PlayerCamera* camera = getPlayerCamera()) {
        manual = camera->isManual();
        hasCamera = true;
    }
    return hasCamera && manual;
}

float GfGamePlayerCamera::getSaveYaw() {
    if (PlayerCamera* camera = getPlayerCamera()) {
        return camera->getSaveYaw();
    }
    return 0.0f;
}

float GfGamePlayerCamera::getSavePitch() {
    if (PlayerCamera* camera = getPlayerCamera()) {
        return camera->getSavePitch();
    }
    return 0.0f;
}

float GfGamePlayerCamera::getSaveDistance() {
    if (PlayerCamera* camera = getPlayerCamera()) {
        return camera->getSaveDistance();
    }
    return 6.0f;
}

float GfGamePlayerCamera::getSaveHeight() {
    if (PlayerCamera* camera = getPlayerCamera()) {
        return camera->getSaveHeight();
    }
    return 0.0f;
}

bool GfGamePlayerCamera::getSaveSide() {
    if (PlayerCamera* camera = getPlayerCamera()) {
        return camera->getSaveSide();
    }
    return true;
}

bool GfGamePlayerCamera::isSaveFreeMode() {
    bool hasCamera = false;
    bool freeMode;
    if (PlayerCamera* camera = getPlayerCamera()) {
        freeMode = camera->isSaveFreeMode();
        hasCamera = true;
    }
    return hasCamera && freeMode;
}

GfGamePlayerCamera::~GfGamePlayerCamera() {}

void GfGamePlayerCamera::gevPartyMemberOK(bool ok) {
    if (!ok) {
        return;
    }
    if (!m_target) {
        m_target = PlayerCameraTarget::create();
        if (fw::CameraManager* manager = fw::CameraManager::get()) {
            manager->m_target = m_target;
        }
    }
    if (m_camera) {
        return;
    }
    m_camera = PlayerCamera::create();
    if (fw::CameraManager* manager = fw::CameraManager::get()) {
        manager->m_layers[0].push(m_camera, 0.0f);
    }
}

bool GfGamePlayerCamera::recieveMessage(fw::MessageObject* sender, fw::Message& msg) {
    if (msg.m_id == MsgPcResetCamera::ID) {
        procMsgPcResetCamera(sender, static_cast<MsgPcResetCamera&>(msg));
        return true;
    }
    return false;
}

}  // namespace gf
