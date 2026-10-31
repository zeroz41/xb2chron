#ifndef CLASSES_ANM_MIRRORMAPPER_H
#define CLASSES_ANM_MIRRORMAPPER_H

#include "classes/anm/ReferenceObject.h"
#include "mm/Quat.h"
#include "mm/mtl/Vector.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }
namespace anm { class Skeleton; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// table 0x7100B810D8; a skeleton's bones paired with their mirror images (pBonePairTable) across a plane
class MirrorMapper : public ::anm::ReferenceObject {
public:
    MirrorMapper(const Skeleton* pSkeleton, short* pBonePairTable, const mm::Quat& plane,
                 mm::mtl::IAllocator* pAllocator);
    virtual ~MirrorMapper();  // slot 0
    // fills m_invariants for the plane (the constructor's tail call passes 0.0f; return type unproven, void)
    void calcBoneInvariants(const mm::Quat& plane, float);
    // pRotation snapped to the cube rotation within epsilon of it (|dot| >= 1 - epsilon), left as it is when none is;
    //  unused (parameter names inferred)
    void canonicalize(float epsilon, mm::Quat* pRotation);
    // the pose sampled through the original binding, mirrored onto the target binding's tracks
    // (MirrorAnimation::sampleTrucks)
    void mirrorPose(const Binding& original, const Binding& target, const QsTransform* pPose, QsTransform* pOut) const;
    // the extract motion mirrored across the plane (MirrorAnimation::getExtractMotion)
    void mirrorExtractMotion(const QsTransform& motion, QsTransform* pOut) const;

    const Skeleton* m_pSkeleton;  // Factory::createMirrorAnimation checks a binding against its bone count
    // per bone, the bone it mirrors onto: the constructor copies pBonePairTable into it (the name is not the
    // original's). Factory::createMirrorMapper allocates 0x70 bytes
    mm::mtl::Vector<short> m_pairs;
    // per bone and one more, the rotations calcBoneInvariants computes (the name is not the original's)
    mm::mtl::Vector<mm::Quat> m_invariants;
};
}  // namespace anm

#endif
