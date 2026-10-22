#ifndef CLASSES_ANM_EXTRATRUCKBUFFER_H
#define CLASSES_ANM_EXTRATRUCKBUFFER_H

#include "classes/anm/ReferenceObject.h"

namespace anm { class Skeleton; }
namespace anm { struct ExtraTruckSlot; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// table 0x7100B81058; the values of one of a skeleton's extra-track slots
class ExtraTruckBuffer : public ::anm::ReferenceObject {
public:
    ExtraTruckBuffer(const Skeleton& skeleton, const ExtraTruckSlot& slot, mm::mtl::IAllocator* pAllocator);
    virtual ~ExtraTruckBuffer();  // slot 0

    unsigned char pad_18[0x38];  // Factory::createExtraTruckBuffer allocates 0x50 bytes
};
}  // namespace anm

#endif
