#include "btl/EffectMoveComponent.h"

#include <math.h>
#include "anm/QsTransform.h"
#include "btl/Misc.h"
#include "fw/Transform.h"
#include "fw/TransformUtil.h"
#include "fw/UpdateInfo.h"
#include "gf/GfObjAcc.h"
#include "mm/Mat44.h"

namespace btl {

const EffectMoveComponent::UpdateFunc EffectMoveComponent::m_apUpdateFuncList[6] = {
    &EffectMoveComponent::UpdateNormal,  &EffectMoveComponent::UpdateNormal,  &EffectMoveComponent::UpdateHoming,
    &EffectMoveComponent::UpdateBounce,  &EffectMoveComponent::UpdateLinkObj, &EffectMoveComponent::UpdateUp,
};

EffectMoveComponent::EffectMoveComponent() {
    Initialize();
}

void EffectMoveComponent::Initialize() {
    m_velocity = mm::Vec3::zero;
    m_dir = mm::Vec3::zero;
    m_time = 0.0f;
    m_type = MOVE_TYPE_NONE;
}

}  // namespace btl

namespace fw {

void TransformUtil::mul(const Transform& lhs, const anm::QsTransform& rhs, float scale, Transform* pOut) {
    mm::Vec3 position(rhs.m_translation.x, rhs.m_translation.y, rhs.m_translation.z);
    pOut->position = lhs.position + lhs.rotation.rotate(position) * scale;
    pOut->rotation = rhs.m_rotation * lhs.rotation;
}

}  // namespace fw

namespace btl {

void EffectMoveComponent::UpdateNormal(float dt, float frame, const mm::Vec3& pos) {
    if (dt <= 1e-06f) {
        m_velocity = mm::Vec3::zero;
        return;
    }
    float length = m_speed * m_speedRate * frame;
    mm::Vec3 move;
    move.x = m_dir.x * length;
    move.y = m_dir.y * length;
    move.z = m_dir.z * length;
    m_moveLength += length;
    m_moveLengthXZ += Misc::CalcLengthXZ(move);
    if (m_gravity != 0.0f) {
        float prev = m_gravityTime;
        m_gravityTime += dt;
        move.y -= m_gravity * (m_gravityTime * m_gravityTime - prev * prev);
    }
    m_velocity = move;
    if (m_accel != 0.0f) {
        if (m_accelTimer < m_accelWait) {
            m_accelTimer += frame;
        } else {
            float speed = m_accel * frame + m_speed;
            bool under = m_accel > 0.0f ? speed < m_speedLimit : speed > m_speedLimit;
            m_speed = under ? speed : m_speedLimit;
        }
    }
}

void EffectMoveComponent::UpdateBounce(float dt, float frame, const mm::Vec3& pos) {}

void EffectMoveComponent::UpdateLinkObj(float dt, float frame, const mm::Vec3& pos) {
    mm::Vec3 target = mm::Mat44::identity.getTrans();
    gf::GfObjAcc acc(m_linkObj.m_obj);
    int bone = acc.getBoneIdx(m_linkObj.m_bone);
    if (bone >= 0) {
        fw::Transform transform;
        acc.getBoneTransform(transform, bone);
        target = transform.position;
    }
    float rate;
    if (m_linkObj.m_time <= frame) {
        m_linkObj.m_time = 0.0f;
        rate = 1.0f;
    } else {
        rate = frame / m_linkObj.m_time;
        m_linkObj.m_time -= frame;
    }
    mm::Vec3 next = (1.0f - rate) * pos + target * rate;
    m_velocity.x = next.x - pos.x;
    m_velocity.y = next.y - pos.y;
    m_velocity.z = next.z - pos.z;
    if (rate < 1.0f && m_gravity != 0.0f) {
        float speed = m_speed * frame;
        float y = m_dir.y * speed;
        float prev = m_gravityTime;
        m_gravityTime += dt;
        float time = m_gravityTime;
        y -= m_gravity * (time * time - prev * prev);
        m_velocity.y = m_velocity.y + fmaxf(y, 0.0f);
    }
}

void EffectMoveComponent::UpdateUp(float dt, float frame, const mm::Vec3& pos) {
    float time = m_up.m_time;
    float rate;
    if (time <= frame) {
        rate = time / frame;
        m_up.m_time = 0.0f;
    } else {
        rate = frame;
        m_up.m_time = time - frame;
    }
    m_velocity.x = 0.0f;
    m_velocity.z = 0.0f;
    m_velocity.y += rate * m_speed;
}

void EffectMoveComponent::Update(const fw::UpdateInfo& info, const mm::Vec3& pos) {
    if (m_type == MOVE_TYPE_NONE) {
        return;
    }
    float dt = info.m_deltaTime;
    float frame = dt * 30.0f;
    m_time += dt;
    (this->*m_apUpdateFuncList[m_type - 1])(dt, frame, pos);
}

}  // namespace btl
