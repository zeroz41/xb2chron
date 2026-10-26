#include <math.h>
#include <new>
#include "anm/Array.h"
#include "anm/QsTransform.h"
#include "anm/TransformUtil.h"
#include "mm/Math.h"
#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "mm/Vec4.h"
#include "mm/mtl/Vector.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "skd/CollisionObj.h"
#include "skd/Factory.h"
#include "skd/Packet.h"
#include "skd/ResSolver.h"
#include "classes/skd/CollisionObject.h"
#include "classes/skd/Dynamics.h"
#include "classes/skd/DynamicsSolver.h"

namespace skd {

CollisionObject* Factory::createColObject(const ResCollisionArray* collisions, anm::Pose& pose,
                                          mm::mtl::IAllocator* allocator) {
    if (collisions == nullptr) {
        return nullptr;
    }
    CollisionObject* colObj =
        new (allocator->allocate(sizeof(CollisionObject), 8)) CollisionObject(*collisions, pose, allocator);
    colObj->addRef();
    return colObj;
}

Dynamics* Factory::createDynamics(CollisionObject* colObj, const anm::Array<ResSolver>& solvers, anm::Pose& pose,
                                  ForceInterface* force, mm::mtl::IAllocator* allocator) {
    if (colObj == nullptr) {
        return nullptr;
    }
    Dynamics* dynamics =
        new (allocator->allocate(sizeof(Dynamics), 8)) Dynamics(*colObj, solvers, pose, force, allocator);
    dynamics->addRef();
    return dynamics;
}

// q applied to v, with the first product's terms written v first (the original's operand order; the name is not the
// original's)
static inline void rotateVector(mm::Vec3& out, const mm::Quat& q, const mm::Vec3& v) {
    float tx = (v.z * q.y - v.y * q.z) + v.x * q.w;
    float ty = (v.x * q.z - v.z * q.x) + v.y * q.w;
    float tz = (v.y * q.x - v.x * q.y) + v.z * q.w;
    float tw = -(v.x * q.x) - v.y * q.y - v.z * q.z;
    out.x = (-(q.z * ty) + q.y * tz - q.x * tw) + q.w * tx;
    out.y = (-(q.x * tz) + q.z * tx - q.y * tw) + q.w * ty;
    out.z = (-(q.y * tx) + q.x * ty - q.z * tw) + q.w * tz;
}

bool ShpereCollObj::detect(float radius, const mm::Vec3& pos, mm::Vec3* push) const {
    mm::Vec3 diff = pos - m_pos;
    float distance = diff.length();
    float limit = m_pRes->m_radius + radius;
    if (distance < limit) {
        mm::Vec3 normal;
        if (diff.isZero()) {
            normal = mm::Vec3::unitY;
        } else {
            float length = diff.length();
            if (length <= 1e-6f) {
                normal = mm::Vec3::zero;
            } else {
                float scale = 1.0f / length;
                normal.x = diff.x * scale;
                normal.y = diff.y * scale;
                normal.z = diff.z * scale;
            }
        }
        *push = (limit - distance) * normal;
        return true;
    }
    return false;
}

inline void ShpereCollObj::calc(anm::Pose& pose) {
    const anm::QsTransform& transform = pose.getBoneModelSpace(m_bone);
    mm::Vec3 offset;
    rotateVector(offset, transform.m_rotation, m_pRes->m_offset);
    mm::Vec3 translation(transform.m_translation.x, transform.m_translation.y, transform.m_translation.z);
    m_pos = translation + offset;
}

void CapsuleCollObj::calc(anm::Pose& pose) {
    const anm::QsTransform& transform = pose.getBoneModelSpace(m_bone);
    mm::Vec3 offset;
    rotateVector(offset, transform.m_rotation, m_pRes->m_offset);
    mm::Vec3 center(transform.m_translation.x + offset.x, transform.m_translation.y + offset.y,
                    transform.m_translation.z + offset.z);
    mm::Quat rotation = m_pRes->m_rotation * transform.m_rotation;
    mm::Vec3 dir = rotation.rotate(mm::Vec3::unitY);
    m_dir = dir;
    m_pos = center - (m_pRes->m_length * 0.5f) * dir;
}

// the index of the bone named `name` in the skeleton, 0xFFFF when there is no name or no such bone (the name is not
// the original's)
static inline unsigned short findBone(const anm::Skeleton* skeleton, const char* name) {
    if (name == nullptr) {
        return 0xFFFF;
    }
    return skeleton->getBoneIndex(name);
}

CollionArray::CollionArray(mm::mtl::IAllocator* allocator, const ResCollisionArray& res, const anm::Pose& pose)
    : m_pRes(&res), m_spheres(allocator), m_capsules(allocator), m_planes(allocator), m_valid(true) {
    const anm::Skeleton* skeleton = pose.m_pSkeleton;

    unsigned int count = res.m_spheres.size();
    m_spheres.reserve(count > 8 ? count : 8);
    m_spheres.resize(count);
    for (unsigned int i = 0; i < m_spheres.size(); i++) {
        m_spheres[i].m_pRes = &m_pRes->m_spheres[i];
        m_spheres[i].m_pos = mm::Vec3::zero;
        unsigned short bone = findBone(skeleton, m_spheres[i].m_pRes->m_boneName);
        if (bone == 0xFFFF) {
            m_spheres[i].m_bone = 0xFFFF;
            m_valid = false;
        } else {
            m_spheres[i].m_bone = bone;
        }
    }

    count = m_pRes->m_capsules.size();
    m_capsules.reserve(count > 8 ? count : 8);
    m_capsules.resize(count);
    for (unsigned int i = 0; i < m_capsules.size(); i++) {
        m_capsules[i].m_pRes = &m_pRes->m_capsules[i];
        m_capsules[i].m_pos = mm::Vec3::zero;
        m_capsules[i].m_dir = mm::Vec3::zero;
        unsigned short bone = findBone(skeleton, m_capsules[i].m_pRes->m_boneName);
        if (bone == 0xFFFF) {
            m_capsules[i].m_bone = 0xFFFF;
            m_valid = false;
        } else {
            m_capsules[i].m_bone = bone;
        }
    }

    count = m_pRes->m_planes.size();
    m_planes.reserve(count > 8 ? count : 8);
    m_planes.resize(count);
    for (unsigned int i = 0; i < m_planes.size(); i++) {
        m_planes[i].m_pRes = &m_pRes->m_planes[i];
        m_planes[i].m_plane = mm::Vec4::unitY;
        unsigned short bone = findBone(skeleton, m_planes[i].m_pRes->m_boneName);
        if (bone == 0xFFFF) {
            m_planes[i].m_bone = 0xFFFF;
            m_valid = false;
        } else {
            m_planes[i].m_bone = bone;
        }
    }
}

void CollionArray::update(anm::Pose& pose) {
    if (!m_valid) {
        return;
    }
    for (unsigned int i = 0; i < m_spheres.size(); i++) {
        m_spheres[i].calc(pose);
    }
    for (unsigned int i = 0; i < m_capsules.size(); i++) {
        m_capsules[i].calc(pose);
    }
    for (unsigned int i = 0; i < m_planes.size(); i++) {
        m_planes[i].calc(pose);
    }
}

}  // namespace skd
