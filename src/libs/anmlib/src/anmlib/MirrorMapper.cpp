#include "classes/anm/MirrorMapper.h"
#include "classes/anm/SimpleMapper.h"
#include "classes/anm/Skeleton.h"
#include "math.h"
#include "string.h"

namespace anm {

MirrorMapper::MirrorMapper(const Skeleton* pSkeleton, short* pBonePairTable, const mm::Quat& plane,
                           mm::mtl::IAllocator* pAllocator)
    : ReferenceObject(pAllocator), m_pSkeleton(pSkeleton), m_pairs(pAllocator), m_invariants(pAllocator) {
    pSkeleton->addRef();
    unsigned int count = pSkeleton->m_bones.size();
    m_pairs.resize(count);
    m_invariants.resize(count + 1);
    memcpy(m_pairs.data(), pBonePairTable, m_pairs.size() * sizeof(short));
    calcBoneInvariants(plane, 0.0f);
}

MirrorMapper::~MirrorMapper() {
    if (m_pSkeleton != nullptr) {
        m_pSkeleton->release();
        m_pSkeleton = nullptr;
    }
}

// the cube's 24 rotations, one per quaternion pair q/-q (the names are not the original's)
void MirrorMapper::canonicalize(float epsilon, mm::Quat* pRotation) {
    static const float s = 1.0f / sqrtf(2.0f);
    static const float h = 0.5f;
    static const mm::Quat rotations[24] = {
        mm::Quat(1.0f, 0.0f, 0.0f, 0.0f), mm::Quat(0.0f, 1.0f, 0.0f, 0.0f), mm::Quat(0.0f, 0.0f, 1.0f, 0.0f),
        mm::Quat(0.0f, 0.0f, 0.0f, 1.0f), mm::Quat(s, s, 0.0f, 0.0f),       mm::Quat(s, -s, 0.0f, 0.0f),
        mm::Quat(0.0f, s, s, 0.0f),       mm::Quat(0.0f, s, -s, 0.0f),      mm::Quat(0.0f, 0.0f, s, s),
        mm::Quat(0.0f, 0.0f, s, -s),      mm::Quat(s, 0.0f, s, 0.0f),       mm::Quat(s, 0.0f, -s, 0.0f),
        mm::Quat(0.0f, s, 0.0f, s),       mm::Quat(0.0f, s, 0.0f, -s),      mm::Quat(s, 0.0f, 0.0f, s),
        mm::Quat(s, 0.0f, 0.0f, -s),      mm::Quat(h, h, h, h),             mm::Quat(h, h, h, -h),
        mm::Quat(h, h, -h, h),            mm::Quat(h, h, -h, -h),           mm::Quat(h, -h, h, h),
        mm::Quat(h, -h, h, -h),           mm::Quat(h, -h, -h, h),           mm::Quat(h, -h, -h, -h),
    };
    for (unsigned int i = 0; i < 24; i++) {
        const mm::Quat& q = rotations[i];
        float dot = pRotation->x * q.x + pRotation->y * q.y + pRotation->z * q.z + pRotation->w * q.w;
        if (fabsf(dot) >= 1.0f - epsilon) {
            *pRotation = q;
            return;
        }
    }
}

SimpleMapper::SimpleMapper(const Skeleton& src, const Skeleton& dst, mm::mtl::IAllocator* pAllocator)
    : ReferenceObject(pAllocator), m_pSkeleton(&src), m_pTarget(&dst), m_boneMap(pAllocator),
      m_truckMaps(pAllocator) {
    m_pSkeleton->addRef();
    m_pTarget->addRef();
    unsigned int boneCount = dst.m_bones.size();
    m_boneMap.resize(boneCount);
    m_boneMap[0] = 0;
    for (unsigned int i = 1; i < boneCount; i++) {
        const char* name = dst.getBone(i).m_name;
        unsigned short bone = 0xFFFF;
        if (name != nullptr) {
            bone = src.getBoneIndex(name);
        }
        m_boneMap[i] = bone;
    }
    unsigned int slotCount = dst.m_extraTruckSlots.size();
    m_truckMaps.resize(slotCount);
    for (unsigned int i = 0; i != slotCount; i++) {
        mm::mtl::Vector<short>& map = m_truckMaps[i];
        map.setAllocator(pAllocator);
        const ExtraTruckSlot& slot = dst.m_extraTruckSlots[i];
        map.resize(slot.m_defaults.size(), -1);
        short id = src.getExtraTruckSlotID(slot.m_name);
        if (id != -1) {
            const ExtraTruckSlot& srcSlot = src.m_extraTruckSlots[id];
            for (unsigned int j = 0; j < slot.m_defaults.size(); j++) {
                short truck = srcSlot.getTruckID(slot.getTruckName(j));
                if (truck != -1) {
                    map[j] = truck;
                }
            }
        }
    }
}

SimpleMapper::~SimpleMapper() {
    if (m_pSkeleton != nullptr) {
        m_pSkeleton->release();
        m_pSkeleton = nullptr;
    }
    if (m_pTarget != nullptr) {
        m_pTarget->release();
        m_pTarget = nullptr;
    }
}

}  // namespace anm
