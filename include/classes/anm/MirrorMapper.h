#ifndef CLASSES_ANM_MIRRORMAPPER_H
#define CLASSES_ANM_MIRRORMAPPER_H

#include "classes/anm/ReferenceObject.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }
namespace anm { class Skeleton; }
namespace mm { class Quat; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// table 0x7100B810D8; a skeleton's bones paired with their mirror images (pBonePairTable) across a plane
class MirrorMapper : public ::anm::ReferenceObject {
public:
    MirrorMapper(const Skeleton* pSkeleton, short* pBonePairTable, const mm::Quat& plane,
                 mm::mtl::IAllocator* pAllocator);
    virtual ~MirrorMapper();  // slot 0
    // the pose sampled through the original binding, mirrored onto the target binding's tracks
    // (MirrorAnimation::sampleTrucks)
    void mirrorPose(const Binding& original, const Binding& target, const QsTransform* pPose, QsTransform* pOut) const;
    // the extract motion mirrored across the plane (MirrorAnimation::getExtractMotion)
    void mirrorExtractMotion(const QsTransform& motion, QsTransform* pOut) const;

    const Skeleton* m_pSkeleton;  // Factory::createMirrorAnimation checks a binding against its bone count
    unsigned char pad_20[0x50];   // Factory::createMirrorMapper allocates 0x70 bytes
};
}  // namespace anm

#endif
