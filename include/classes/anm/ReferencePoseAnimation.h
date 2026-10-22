#ifndef CLASSES_ANM_REFERENCEPOSEANIMATION_H
#define CLASSES_ANM_REFERENCEPOSEANIMATION_H

#include "classes/anm/Animation.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }
namespace anm { class Skeleton; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// table 0x7100B81298; a skeleton's reference pose as an animation
class ReferencePoseAnimation : public ::anm::Animation {
public:
    ReferencePoseAnimation(const Skeleton* pSkeleton, mm::mtl::IAllocator* pAllocator);
    virtual ~ReferencePoseAnimation();  // slot 0
    virtual int getImplType() const;  // slot 2
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const;  // slot 3
    // the binding of the reference pose to the skeleton
    Binding* createBinding();

    unsigned char pad_48[0x8];  // Factory::createReferencePoseAnimation allocates 0x50 bytes
};
}  // namespace anm

#endif
