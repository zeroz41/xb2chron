#ifndef CLASSES_ANM_SIMPLEMAPPER_H
#define CLASSES_ANM_SIMPLEMAPPER_H

#include "classes/anm/ReferenceObject.h"
#include "mm/mtl/Vector.h"

namespace anm { class Skeleton; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// table 0x7100B810F8; one skeleton's bones paired with another's
class SimpleMapper : public ::anm::ReferenceObject {
public:
    SimpleMapper(const Skeleton& src, const Skeleton& dst, mm::mtl::IAllocator* pAllocator);
    virtual ~SimpleMapper();  // slot 0

    // Factory::createRetargetAnimation checks a binding against its bone count (the name is not the original's)
    const Skeleton* m_pSkeleton;
    // the skeleton mapped onto (the constructor's dst; counted like m_pSkeleton; the name is not the original's).
    // Factory::createSimpleMapper allocates 0x78 bytes
    const Skeleton* m_pTarget;
    // per target bone, the bone of m_pSkeleton with its name, 0xFFFF for none (the name is not the original's)
    mm::mtl::Vector<short> m_boneMap;
    // per target extra-track slot, per value, the matching truck of m_pSkeleton's slot of that name, -1 for none
    // (the name is not the original's)
    mm::mtl::Vector<mm::mtl::Vector<short> > m_truckMaps;
};
}  // namespace anm

#endif
