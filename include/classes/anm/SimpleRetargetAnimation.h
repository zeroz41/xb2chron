#ifndef CLASSES_ANM_SIMPLERETARGETANIMATION_H
#define CLASSES_ANM_SIMPLERETARGETANIMATION_H

#include "classes/anm/Animation.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }
namespace anm { class SimpleMapper; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// table 0x7100B812D8; a binding's animation carried over to another skeleton through a SimpleMapper
class SimpleRetargetAnimation : public ::anm::Animation {
public:
    SimpleRetargetAnimation(const Binding* pBinding, const SimpleMapper* pMapper, mm::mtl::IAllocator* pAllocator);
    virtual ~SimpleRetargetAnimation();  // slot 0
    virtual int getImplType() const;  // slot 2
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const;  // slot 3
    virtual bool getExtractMotion(float, anm::QsTransform*) const;  // slot 4
    virtual bool getDeltaExtractMotion(float, float, bool, anm::QsTransform*) const;  // slot 5
    // the binding of the carried-over animation to the mapper's other skeleton
    Binding* createBinding();

    unsigned char pad_48[0x60];  // Factory::createRetargetAnimation allocates 0xA8 bytes
};
}  // namespace anm

#endif
