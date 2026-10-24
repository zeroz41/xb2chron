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

    // the fields' names are not the original's: the fw pose samplers read them
    const Skeleton* m_pSkeleton;  // the constructor's skeleton: the samplers find the slot's index in it
    const ExtraTruckSlot* m_pSlot;  // the constructor's slot: the samplers find it by its name
    float* m_pValues;  // the samplers sample the slot's values into it
    unsigned int m_count;  // how many values m_pValues holds
    unsigned char pad_34[0x1C];  // Factory::createExtraTruckBuffer allocates 0x50 bytes
};
}  // namespace anm

#endif
