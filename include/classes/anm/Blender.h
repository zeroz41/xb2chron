#ifndef CLASSES_ANM_BLENDER_H
#define CLASSES_ANM_BLENDER_H

#include "classes/anm/ReferenceObject.h"
#include "anm/QsTransform.h"
#include "mm/mtl/Vector.h"

namespace anm { class Control; }
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
    // fw::AnimBlenderUpdater::update passes it UpdateInfo::m_deltaTime
    void update(float dt);

    // the scratch buffers the samplers blend in (Blender::Work::~Work is the symbols'; 0xA0 bytes, the constructor's
    // allocation). The field names are not the original's
    struct Work {
        ~Work();

        mm::mtl::Vector<float> m_weights;          // per bone (or extra-track value), the weights' sum
        mm::mtl::Vector<QsTransform> m_transforms;  // per bone, a control's sampled transform
        mm::mtl::Vector<float> m_extraValues;      // per extra-track value, a control's sampled value
        mm::mtl::Vector<bool> m_partial;           // per bone, sampleTrucksMS's partial space conversions'
    };

    // Factory::createBlender allocates 0x50 bytes
    mm::mtl::Vector<Control*> m_controls;  // addControl's, each referenced (the name is not the original's)
    const Skeleton* m_pSkeleton;  // the constructor asserts `m_pSkeleton`
    Work* m_pWork;                // the constructor's (the name is not the original's)
};
}  // namespace anm

#endif
