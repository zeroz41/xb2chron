#ifndef CLASSES_ANM_BLENDER_H
#define CLASSES_ANM_BLENDER_H

#include "classes/anm/ReferenceObject.h"

namespace anm { class Control; }
namespace anm { class QsTransform; }
namespace anm { class Skeleton; }
namespace mm { namespace mtl { class IAllocator; }}

namespace anm {
// table 0x7100B81118
class Blender : public ::anm::ReferenceObject {
public:
    Blender(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator);
    virtual ~Blender();  // slot 0
    // the controls' animations blended: count transforms (sampleTrucksMS's in model space)
    void sampleTrucks(unsigned int count, QsTransform* pOut);
    void sampleTrucksMS(unsigned int count, QsTransform* pOut);
    void sampleExtraTrucks(unsigned short slot, unsigned int count, float* pOut);
    bool addControl(Control* pControl);
    bool removeControl(Control* pControl);

    unsigned char pad_18[0x28];  // Factory::createBlender allocates 0x50 bytes
    const Skeleton* m_pSkeleton;  // the constructor's (the name is not the original's)
    unsigned char pad_48[0x8];
};
}  // namespace anm

#endif
