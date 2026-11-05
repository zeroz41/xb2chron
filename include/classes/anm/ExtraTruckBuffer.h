#ifndef CLASSES_ANM_EXTRATRUCKBUFFER_H
#define CLASSES_ANM_EXTRATRUCKBUFFER_H

#include "classes/anm/ReferenceObject.h"
#include "mm/mtl/Vector.h"

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
    // the samplers sample the slot's values into it (the constructor sizes it to the slot's defaults and copies them)
    mm::mtl::Vector<float> m_values;
};
}  // namespace anm

#endif
