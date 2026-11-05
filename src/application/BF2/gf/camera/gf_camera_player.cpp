#include "gf/FileStaticVec3.h"
#include "classes/gf/PlayerCamera.h"
#include "classes/fw/Framework.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/ParamManager.h"
#include "classes/gf/PlayerCameraTarget.h"
#include "classes/mm/mtl/IAllocator.h"
#include "gf/GfObjAcc.h"
#include "gf/GfDataUtil.h"
#include "classes/gf/GfDataManager.h"
#include "gf/SDataOption.h"
#include "mm/Quat.h"
#include "mm/Math.h"

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

void PlayerCamera::resetClimb() {
    if (PlayerCameraTarget* target = PlayerCameraTarget::get()) {
        float yaw = getYaw(target->m_front, mm::Vec3::unitZ);
        m_curYaw = yaw;
        m_yaw = yaw;
        const Param* param = static_cast<const Param*>(m_param.m_entry->m_data);
        mm::Vec3 eye(0.0f, param->m_cameraHeight, -param->m_distanceDefault);
        mm::Vec3 look(0.0f, param->m_lookHeight, 0.0f);
        mm::Vec3 dir = look - eye;
        mm::Vec3 front = mm::Vec3::unitZ;
        m_defaultPitch = getPitch(dir, front);
        m_curDistance = m_distance;
        m_curPitch = 0.0f;
        m_pitch = 0.0f;
        m_curHeight = m_height;
        m_lookPos = target->m_position;
        m_targetPos = m_lookPos;
        m_targetChanged = false;
        m_warpPos = m_lookPos;
        m_resetting = false;
        m_sloping = false;
        mm::Vec3 rot(0.0f, m_curYaw, 0.0f);
        mm::Vec3 half = rot * 0.5f;
        float sx = ::sinf(half.x), cx = ::cosf(half.x), sy = ::sinf(half.y), cy = ::cosf(half.y),
              sz = ::sinf(half.z), cz = ::cosf(half.z);
        mm::Quat q(sx * cy * cz - cx * sy * sz, cx * sy * cz + sx * cy * sz, cx * cy * sz - sx * sy * cz,
                   cx * cy * cz + sx * sy * sz);
        q.rotate(m_offset, m_curDistance * mm::Vec3::unitZ);
        m_offset += m_targetPos;
        GfDataUtil::setCameraYaw(m_yaw);
        GfDataUtil::setCameraPitch(m_pitch);
    }
}

void PlayerCamera::resetClimb(ResetCameraWallTiming timing) {
    m_resetClimb = true;
    m_wallTiming = timing;
    m_rotateRevise = timing == 0 ? 0.666666687f : 0.233333349f;
}

void PlayerCamera::resetLoad() {
    if (PlayerCameraTarget* target = PlayerCameraTarget::get()) {
        const Param* sideParam = m_param.get<Param>();
        float yaw = GfDataUtil::getCameraYaw();
        m_curYaw = yaw;
        m_yaw = yaw;
        const Param* param = static_cast<const Param*>(m_param.m_entry->m_data);
        mm::Vec3 eye(0.0f, param->m_cameraHeight, -param->m_distanceDefault);
        mm::Vec3 look(0.0f, param->m_lookHeight, 0.0f);
        mm::Vec3 dir = look - eye;
        mm::Vec3 front = mm::Vec3::unitZ;
        m_defaultPitch = getPitch(dir, front);
        float pitch = GfDataUtil::getCameraPitch();
        m_curPitch = pitch;
        m_pitch = pitch;
        float distance = GfDataUtil::getPlayerCameraDistance();
        m_curDistance = distance;
        m_distance = distance;
        float height = GfDataUtil::getCameraHeight();
        m_curHeight = height;
        m_height = height;
        m_side = GfDataUtil::getCameraSide();
        float side = sideParam->m_sideDistance[m_side];
        m_curSideDistance = side;
        m_sideDistance = side;
        m_lookPos = target->m_position;
        m_targetPos = m_lookPos;
        m_targetChanged = false;
        m_warpPos = m_lookPos;
        m_manual = GfDataUtil::isCameraFreeMode();
        m_resetting = false;
        m_sloping = false;
        mm::Vec3 rot(0.0f, m_curYaw, 0.0f);
        mm::Vec3 half = rot * 0.5f;
        float sx = ::sinf(half.x), cx = ::cosf(half.x), sy = ::sinf(half.y), cy = ::cosf(half.y),
              sz = ::sinf(half.z), cz = ::cosf(half.z);
        mm::Quat q(sx * cy * cz - cx * sy * sz, cx * sy * cz + sx * cy * sz, cx * cy * sz - sx * sy * cz,
                   cx * cy * cz + sx * sy * sz);
        q.rotate(m_offset, m_curDistance * mm::Vec3::unitZ);
        m_offset += m_targetPos;
    }
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

float PlayerCamera::getYaw(const mm::Vec3& dir, const mm::Vec3& front) {
    mm::Vec3 a(dir.x, 0.0f, dir.z);
    mm::Vec3 b(front.x, 0.0f, front.z);
    if (a.isZero() || b.isZero()) {
        return m_yaw;
    }
    {
        float length = a.length();
        if (length <= 1e-6f) {
            a = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            a.x = a.x * scale;
            a.y = a.y * scale;
            a.z = a.z * scale;
        }
    }
    {
        float length = b.length();
        if (length <= 1e-6f) {
            b = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            b.x = b.x * scale;
            b.y = b.y * scale;
            b.z = b.z * scale;
        }
    }
    float cosine = b.dot(a);
    if (cosine < -1.0f) {
        cosine = -1.0f;
    } else if (cosine > 1.0f) {
        cosine = 1.0f;
    }
    float angle = mm::acos(cosine);
    mm::Vec3 axis = b.cross(a);
    axis.normalize();
    return axis.y < 0.0f ? 6.28318548f - angle : angle;
}

float PlayerCamera::getPitch(const mm::Vec3& dir, const mm::Vec3& front) {
    float yaw = getYaw(dir, front);
    mm::Vec3 a = dir;
    mm::Vec3 b = front;
    if (a.isZero() || b.isZero()) {
        return m_pitch;
    }
    float half = -yaw * 0.5f;
    float s = ::sinf(half);
    float c = ::cosf(half);
    mm::Quat q(0.0f, s, 0.0f, c);
    mm::Vec3 r = q.rotate(a);
    {
        float length = r.length();
        if (length <= 1e-6f) {
            r = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            r.x = scale * r.x;
            r.y = scale * r.y;
            r.z = scale * r.z;
        }
    }
    {
        float length = b.length();
        if (length <= 1e-6f) {
            b = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            b.x = b.x * scale;
            b.y = b.y * scale;
            b.z = b.z * scale;
        }
    }
    float cosine = b.dot(r);
    if (cosine < -1.0f) {
        cosine = -1.0f;
    } else if (cosine > 1.0f) {
        cosine = 1.0f;
    }
    float angle = mm::acos(cosine);
    mm::Vec3 axis = b.cross(r);
    axis.normalize();
    return axis.x < 0.0f ? -angle : angle;
}

bool PlayerCamera::getHitPosition(const fw::ColiCheckConfig& config, const mm::Vec3& start, const mm::Vec3& end,
                                  mm::Vec3& hit) {
    hit = mm::Vec3::zero;
    m_coliResult.clear();
    if (!fw::ColiCheck::testLineChara(m_coliResult, start, end, config)) {
        return false;
    }
    mm::Vec3 position = m_coliResult.getPosition(0);
    mm::Vec3 normal = m_coliResult.getNormal(0);
    mm::Vec3 dir = end - start;
    float length = dir.length();
    if (length <= 1e-6f) {
        dir = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        dir.x = dir.x * scale;
        dir.y = dir.y * scale;
        dir.z = dir.z * scale;
    }
    if (normal.dot(dir) < 0.0f) {
        hit = position;
        return true;
    }
    return false;
}

float PlayerCamera::getSaveYaw() const { return m_yaw; }

float PlayerCamera::getSavePitch() const { return m_pitch; }

float PlayerCamera::getSaveDistance() const { return m_distance; }

float PlayerCamera::getSaveHeight() const { return m_height; }

unsigned char PlayerCamera::getSaveSide() const { return m_side; }

bool PlayerCamera::isSaveFreeMode() const { return m_manual; }

}  // namespace gf
