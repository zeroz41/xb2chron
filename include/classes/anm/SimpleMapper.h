#ifndef CLASSES_ANM_SIMPLEMAPPER_H
#define CLASSES_ANM_SIMPLEMAPPER_H

#include "classes/anm/ReferenceObject.h"

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
    unsigned char pad_20[0x58];  // Factory::createSimpleMapper allocates 0x78 bytes
};
}  // namespace anm

#endif
