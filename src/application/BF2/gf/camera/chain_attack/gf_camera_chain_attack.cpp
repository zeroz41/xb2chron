#include "classes/gf/ChainAttackCameraEntity.h"
#include "classes/gf/ChainAttackCamera.h"
#include "classes/gf/CameraUtilities.h"
#include "classes/fw/Camera.h"
#include "classes/fw/CameraLayer.h"
#include "classes/fw/CameraManager.h"
#include "classes/fw/Framework.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfObjAcc.h"
#include "gf/SDataEnemy.h"
#include "fw/Transform.h"
#include "fw/UpdateInfo.h"
#include "ml/MTRand.h"
#include "mm/Quat.h"
#include "mm/mtl/FixedVector.h"
#include "plugin/Bdat.h"
#include "math.h"

namespace gf {

// the slow-in curve, 1 - cos(t * pi / 2) written as a sine, blended by nothing toward 1 (the original's helper is
// inline; its form and name are not the original's)
static inline float slowIn(float t) {
    float v = ::sinf(t * 1.5707964f + 4.712389f) + 1.0f;
    return v + (1.0f - v) * 0.0f;
}

ChainAttackCameraEntity::~ChainAttackCameraEntity() {}

mm::mtl::IntrusivePtr<ChainAttackCameraEntity> ChainAttackCameraEntity::create() {
#line 58 "D:/Monolithsoft/BF2/prog/application/BF2/gf/camera/chain_attack/gf_camera_chain_attack.cpp"
    return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) ChainAttackCameraEntity();
}

void ChainAttackCameraEntity::onActivate() {}

void ChainAttackCameraEntity::update(const fw::UpdateInfo& info) {
    if (GfGameManager::fn_71002A9E68() && GfGameManager::isExecTutorial()) {
        return;
    }
    if (m_rate > 0.0f) {
        m_eye = m_eye + (m_endEye - m_eye) * m_rate;
        m_target = m_target + (m_endTarget - m_target) * m_rate;
    } else if (m_frames > 0.0f) {
        switch (m_moveType) {
        case 1:
            calcSpeedTypeSlowInSlowOut();
            break;
        case 2: {
            float t = slowIn(m_frame / m_frames);
            m_eye = m_startEye + (m_endEye - m_startEye) * t;
            m_target = m_startTarget + (m_endTarget - m_startTarget) * t;
            break;
        }
        case 3: {
            float t = 1.0f - slowIn(1.0f - m_frame / m_frames);
            m_eye = m_startEye + (m_endEye - m_startEye) * t;
            m_target = m_startTarget + (m_endTarget - m_startTarget) * t;
            break;
        }
        default: {
            float t = m_frame / m_frames;
            m_eye = m_startEye + t * (m_endEye - m_startEye);
            m_target = m_startTarget + t * (m_endTarget - m_startTarget);
            break;
        }
        }
        m_frame += info.m_deltaTime / (1.0f / 30.0f);
        if (m_frames < m_frame) {
            m_frame = m_frames;
        }
    }
    setLookAt(m_eye, m_target, 0.0f);
}

void ChainAttackCameraEntity::calcSpeedTypeSlowInSlowOut() {
    float t = m_frame / m_frames;
    if (t < 0.5f) {
        float e = slowIn(t + t);
        m_eye = m_startEye + e * ((m_endEye - m_startEye) * 0.5f);
        m_target = m_startTarget + e * ((m_endTarget - m_startTarget) * 0.5f);
    } else {
        float e = 1.0f - slowIn((t - 0.5f) * -2.0f + 1.0f);
        mm::Vec3 halfEye = (m_endEye - m_startEye) * 0.5f;
        mm::Vec3 halfTarget = (m_endTarget - m_startTarget) * 0.5f;
        m_eye = m_startEye + halfEye + e * halfEye;
        m_target = m_startTarget + halfTarget + e * halfTarget;
    }
}

void ChainAttackCameraEntity::setPoint(const mm::Vec3& startEye, const mm::Vec3& startTarget,
                                       const mm::Vec3& endEye, const mm::Vec3& endTarget) {
    if (!(startTarget - startEye).isZero()) {
        m_startEye = startEye;
        m_startTarget = startTarget;
    } else {
        m_startEye = m_eye;
        m_startTarget = m_target;
    }
    m_endEye = endEye;
    m_endTarget = endTarget;
    m_eye = m_startEye;
    m_target = m_startTarget;
    mm::Vec3 midEye = m_startEye + (m_endEye - m_startEye) * 0.5f;
    mm::Vec3 midTarget = m_startTarget + (m_endTarget - m_startTarget) * 0.5f;
    mm::Vec3 coliStartEye = m_eye;
    mm::Vec3 coliStartTarget = m_target;
    mm::Vec3 coliMidEye = midEye;
    mm::Vec3 coliMidTarget = midTarget;
    mm::Vec3 coliEndEye = m_endEye;
    mm::Vec3 coliEndTarget = m_endTarget;
    CameraUtilities::updateCollision(m_coliConfig, coliStartEye, coliStartTarget, getFov(), getNearClip());
    CameraUtilities::updateCollision(m_coliConfig, coliMidEye, coliMidTarget, getFov(), getNearClip());
    CameraUtilities::updateCollision(m_coliConfig, coliEndEye, coliEndTarget, getFov(), getNearClip());
    float startRate = (coliStartEye - coliStartTarget).length() / (m_eye - m_target).length();
    float midRate = (coliMidEye - coliMidTarget).length() / (midEye - midTarget).length();
    float endRate = (coliEndEye - coliEndTarget).length() / (m_endEye - m_endTarget).length();
    float rate = startRate <= midRate ? startRate : midRate;
    rate = rate <= endRate ? rate : endRate;
    if (rate < 1.0f) {
        m_startEye = rate * (m_eye - m_target) + m_target;
        m_eye = m_startEye;
        m_endEye = rate * (m_endEye - m_endTarget) + m_endTarget;
    }
}

ChainAttackCamera::ChainAttackCamera() : m_sizeMask(0xf), m_target(reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
    m_coliConfig.m_option = false;
    m_coliConfig.m_mode = 1;
    m_coliConfig.m_flags = 9;
    m_coliConfig.m_mask = ~8u;
}

ChainAttackCamera::~ChainAttackCamera() {}

void ChainAttackCamera::setup(GF_OBJ_HANDLE* attacker, GF_OBJ_HANDLE* target) {
    if (attacker == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfObjAcc acc(attacker);
    if (acc.getType() == 5) {
        return;
    }
    m_target = target;
    if (target == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        GfObjAcc attackerAcc(attacker);
        GF_OBJ_HANDLE* attackerTarget = attackerAcc.getTarget();
        m_target = attackerTarget != reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? attackerTarget : attacker;
    }
    m_sizeMask = 0xf;
    DataParamAcc data(m_target);
    const SDataEnemy* enemy = data.getSDataEnemy();
    if (enemy != nullptr) {
        switch (enemy->m_enSize) {
        case 0:
            m_sizeMask = 1;
            break;
        case 1:
            m_sizeMask = 2;
            break;
        case 2:
            m_sizeMask = 4;
            break;
        case 3:
            m_sizeMask = 8;
            break;
        }
    }
    int startId = lottery(0);
    int endId = lottery(1);
    Param param;
    getParam(startId, param);
    getParam(endId, m_param);
    mm::Vec3 attackerPos;
    mm::Vec3 targetPos;
    CameraUtilities::getCameraLookBonePosition(attacker, attackerPos);
    CameraUtilities::getCameraLookBonePosition(m_target, targetPos);
    const fw::Transform& transform = acc.getWorldTransform();
    updateParam(param, transform, attackerPos, targetPos);
    updateParam(m_param, transform, attackerPos, targetPos);
    m_param.m_startPos = mm::Vec3::zero;
    m_param.m_startLook = mm::Vec3::zero;
    if (!(attackerPos - param.m_startLook).isZero()) {
        CameraUtilities::updateCollision(m_coliConfig, param.m_startLook, attackerPos, 45.0f, 0.4f);
    }
    if (!(attackerPos - param.m_endLook).isZero()) {
        CameraUtilities::updateCollision(m_coliConfig, param.m_endLook, attackerPos, 45.0f, 0.4f);
    }
    if (!(attackerPos - param.m_startPos).isZero()) {
        CameraUtilities::updateCollision(m_coliConfig, param.m_startPos, attackerPos, 45.0f, 0.4f);
    }
    if (!(attackerPos - param.m_endPos).isZero()) {
        CameraUtilities::updateCollision(m_coliConfig, param.m_endPos, attackerPos, 45.0f, 0.4f);
    }
    if (!(attackerPos - m_param.m_endLook).isZero()) {
        CameraUtilities::updateCollision(m_coliConfig, m_param.m_endLook, attackerPos, 45.0f, 0.4f);
    }
    if (!(attackerPos - m_param.m_endPos).isZero()) {
        CameraUtilities::updateCollision(m_coliConfig, m_param.m_endPos, attackerPos, 45.0f, 0.4f);
    }
    if (!m_camera) {
        m_camera = ChainAttackCameraEntity::create();
    }
    if (!m_camera->m_pushed) {
        fw::CameraManager::get()->m_layers[0].push(m_camera, 0.0f);
    }
    ChainAttackCameraEntity* camera = static_cast<ChainAttackCameraEntity*>(m_camera.get());
    if (camera != nullptr && camera->m_pushed) {
        camera->m_frame = 0.0f;
        float rate = param.m_speedNum * 0.0001f;
        camera->m_frames = param.m_speedType == 0 ? 0.0f : param.m_speedNum;
        camera->m_rate = param.m_speedType == 0 ? rate : 0.0f;
        camera->m_moveType = param.m_moveType;
        camera->setPoint(param.m_startPos, param.m_startLook, param.m_endPos, param.m_endLook);
    }
}

int ChainAttackCamera::lottery(unsigned char camType) {
    unsigned char* fp = GfDataBdat::getFP(0x14);
    int top = Bdat::getIdTop(fp);
    int count = Bdat::getIdCount(fp);
    mm::mtl::FixedVector<int, 64> ids;
    for (int id = top; id < top + count; id++) {
        if ((Bdat::getValCheckU8(fp, "EnSize", id) & m_sizeMask) != 0 &&
            Bdat::getValCheckU8(fp, "CamType", id) == camType) {
            ids.push_back(id);
        }
    }
    if (ids.empty()) {
        for (int id = top; id < top + count; id++) {
            if (Bdat::getValCheckU8(fp, "CamType", id) == camType) {
                ids.push_back(id);
            }
        }
    }
    int index = (int)ml::mtRand() % ids.size();
    return ids[index];
}

void ChainAttackCamera::getParam(int id, Param& param) {
    unsigned char* fp = GfDataBdat::getFP(0x14);
    param.m_speedType = Bdat::getValCheckU8(fp, "SpeedType", id);
    param.m_speedNum = Bdat::getValCheckU16(fp, "SpeedNum", id);
    param.m_moveType = Bdat::getValCheckU8(fp, "MoveType", id);
    param.m_startLookPosType = Bdat::getValCheckU8(fp, "S_LookPosType", id);
    param.m_startPos.x = (int)Bdat::getValCheck(fp, "S_PosX", id, 6);
    param.m_startPos.y = (int)Bdat::getValCheck(fp, "S_PosY", id, 6);
    param.m_startPos.z = (int)Bdat::getValCheck(fp, "S_PosZ", id, 6);
    param.m_startLook.x = (int)Bdat::getValCheck(fp, "S_LookX", id, 6);
    param.m_startLook.y = (int)Bdat::getValCheck(fp, "S_LookY", id, 6);
    param.m_startLook.z = (int)Bdat::getValCheck(fp, "S_LookZ", id, 6);
    param.m_endLookPosType = Bdat::getValCheckU8(fp, "E_LookPosType", id);
    param.m_endPos.x = (int)Bdat::getValCheck(fp, "E_PosX", id, 6);
    param.m_endPos.y = (int)Bdat::getValCheck(fp, "E_PosY", id, 6);
    param.m_endPos.z = (int)Bdat::getValCheck(fp, "E_PosZ", id, 6);
    param.m_endLook.x = (int)Bdat::getValCheck(fp, "E_LookX", id, 6);
    param.m_endLook.y = (int)Bdat::getValCheck(fp, "E_LookY", id, 6);
    param.m_endLook.z = (int)Bdat::getValCheck(fp, "E_LookZ", id, 6);
    param.m_startPos.x *= 0.01f;
    param.m_startPos.y *= 0.01f;
    param.m_startPos.z *= 0.01f;
    param.m_startLook.x *= 0.01f;
    param.m_startLook.y *= 0.01f;
    param.m_startLook.z *= 0.01f;
    param.m_endPos.x *= 0.01f;
    param.m_endPos.y *= 0.01f;
    param.m_endPos.z *= 0.01f;
    param.m_endLook.x *= 0.01f;
    param.m_endLook.y *= 0.01f;
    param.m_endLook.z *= 0.01f;
}

void ChainAttackCamera::updateParam(Param& param, const fw::Transform& transform, const mm::Vec3& attackerPos,
                                    const mm::Vec3& targetPos) {
    transform.rotation.rotate(param.m_startPos, param.m_startPos);
    transform.rotation.rotate(param.m_startLook, param.m_startLook);
    transform.rotation.rotate(param.m_endPos, param.m_endPos);
    transform.rotation.rotate(param.m_endLook, param.m_endLook);
    param.m_startPos += attackerPos;
    param.m_startLook += param.m_startLookPosType == 0 ? attackerPos : targetPos;
    param.m_endPos += attackerPos;
    param.m_endLook += param.m_endLookPosType == 0 ? attackerPos : targetPos;
}

void ChainAttackCamera::start() {}

void ChainAttackCamera::end() {
    destroyCamera(&m_camera, 0.0f);
}

void ChainAttackCamera::destroyCamera(mm::mtl::IntrusivePtr<fw::Camera>* camera, float time) {
    if (!*camera) {
        return;
    }
    if ((*camera)->m_pushed) {
        fw::CameraManager::get()->m_layers[0].pop(*camera, time);
    }
    *camera = nullptr;
}

void ChainAttackCamera::change(GF_OBJ_HANDLE* attacker) {
    if (attacker == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfObjAcc acc(attacker);
    int startId = lottery(0);
    int endId = lottery(1);
    Param startParam;
    Param param;
    getParam(startId, startParam);
    getParam(endId, param);
    mm::Vec3 attackerPos;
    mm::Vec3 targetPos;
    CameraUtilities::getCameraLookBonePosition(attacker, attackerPos);
    CameraUtilities::getCameraLookBonePosition(m_target, targetPos);
    const fw::Transform& transform = acc.getWorldTransform();
    updateParam(startParam, transform, attackerPos, targetPos);
    updateParam(param, transform, attackerPos, targetPos);
    param.m_startPos = startParam.m_startPos;
    param.m_startLook = startParam.m_startLook;
    if (!(attackerPos - param.m_startLook).isZero()) {
        CameraUtilities::updateCollision(m_coliConfig, param.m_startLook, attackerPos, 45.0f, 0.4f);
    }
    if (!(attackerPos - param.m_endLook).isZero()) {
        CameraUtilities::updateCollision(m_coliConfig, param.m_endLook, attackerPos, 45.0f, 0.4f);
    }
    if (!(attackerPos - param.m_startPos).isZero()) {
        CameraUtilities::updateCollision(m_coliConfig, param.m_startPos, attackerPos, 45.0f, 0.4f);
    }
    if (!(attackerPos - param.m_endPos).isZero()) {
        CameraUtilities::updateCollision(m_coliConfig, param.m_endPos, attackerPos, 45.0f, 0.4f);
    }
    ChainAttackCameraEntity* camera = static_cast<ChainAttackCameraEntity*>(m_camera.get());
    if (camera != nullptr && camera->m_pushed) {
        camera->m_frame = 0.0f;
        float rate = param.m_speedNum * 0.0001f;
        camera->m_frames = param.m_speedType == 0 ? 0.0f : param.m_speedNum;
        camera->m_rate = param.m_speedType == 0 ? rate : 0.0f;
        camera->m_moveType = param.m_moveType;
        camera->setPoint(param.m_startPos, param.m_startLook, param.m_endPos, param.m_endLook);
    }
}

const char* ChainAttackCameraEntity::getName() const {
    return "ChainAttackCameraEntity";
}

mm::mtl::RTTI ChainAttackCameraEntity::m_rtti("ChainAttackCameraEntity", &fw::Camera::m_rtti, nullptr);

}  // namespace gf
