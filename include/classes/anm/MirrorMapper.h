#ifndef CLASSES_ANM_MIRRORMAPPER_H
#define CLASSES_ANM_MIRRORMAPPER_H

#include "classes/anm/ReferenceObject.h"

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

    const Skeleton* m_pSkeleton;  // Factory::createMirrorAnimation checks a binding against its bone count
    unsigned char pad_20[0x50];   // Factory::createMirrorMapper allocates 0x70 bytes
};
}  // namespace anm

#endif
