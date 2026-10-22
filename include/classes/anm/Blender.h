#ifndef CLASSES_ANM_BLENDER_H
#define CLASSES_ANM_BLENDER_H

#include "classes/anm/ReferenceObject.h"

namespace anm { class Skeleton; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// table 0x7100B81118
class Blender : public ::anm::ReferenceObject {
public:
    Blender(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator);
    virtual ~Blender();  // slot 0

    unsigned char pad_18[0x38];  // Factory::createBlender allocates 0x50 bytes
};
}  // namespace anm

#endif
