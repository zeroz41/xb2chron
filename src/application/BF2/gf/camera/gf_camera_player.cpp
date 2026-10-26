#include "gf/FileStaticVec3.h"
#include "classes/gf/PlayerCamera.h"
#include "classes/fw/Framework.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/ParamManager.h"
#include "classes/gf/PlayerCameraTarget.h"
#include "classes/mm/mtl/IAllocator.h"
#include "gf/GfObjAcc.h"

namespace gf {

mm::mtl::RTTI PlayerCamera::m_rtti("PlayerCamera", &fw::Camera::m_rtti, nullptr);

PlayerCamera::~PlayerCamera() {}

void PlayerCamera::updateViewMatrix() {
    updateCollision2(m_eye, m_target);
    m_curDistance = m_distance;
    Camera::updateViewMatrix();
}

mm::mtl::IntrusivePtr<PlayerCamera> PlayerCamera::create() {
    fw::ParamAdapter param = fw::ParamManager::get()->m_paramLists[19]->getAdapter(0);
#line 233
    return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) PlayerCamera(param);
}

void PlayerCamera::resetClimb(ResetCameraWallTiming timing) {
    m_resetClimb = true;
    m_wallTiming = timing;
    m_rotateRevise = timing == 0 ? 0.666666687f : 0.233333349f;
}

void PlayerCamera::resetBattleWarp() {
    if (PlayerCameraTarget* target = PlayerCameraTarget::get()) {
        m_lookPos = target->m_position;
        m_targetPos = m_lookPos;
        m_warpPos = m_lookPos;
    }
}

void PlayerCamera::setTarget(GF_OBJ_HANDLE* handle) {
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        GfObjAcc acc(handle);
        if (acc.getType() != 5) {
            return;
        }
    }
    if (m_targetHandle == handle) {
        return;
    }
    if (m_targetHandle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        m_targetChanged = true;
    } else if (PlayerCameraTarget::get() == nullptr) {
        return;
    }
    m_targetHandle = handle;
}

bool PlayerCamera::isManual() { return m_manual; }

float PlayerCamera::getSaveYaw() const { return m_yaw; }

float PlayerCamera::getSavePitch() const { return m_pitch; }

float PlayerCamera::getSaveDistance() const { return m_distance; }

float PlayerCamera::getSaveHeight() const { return m_height; }

bool PlayerCamera::getSaveSide() const { return m_side; }

bool PlayerCamera::isSaveFreeMode() const { return m_manual; }

}  // namespace gf
