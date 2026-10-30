#ifndef CLASSES_ANM_SIMPLERETARGETANIMATION_H
#define CLASSES_ANM_SIMPLERETARGETANIMATION_H

#include "classes/anm/Animation.h"
#include "mm/mtl/FixStr.h"

namespace anm { class Binding; }
namespace anm { class ExtraBinding; }
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

    // Factory::createRetargetAnimation allocates 0xA8 bytes
    const SimpleMapper* m_pMapper;  // the constructor asserts `m_pMapper->m_pSkeletonA->getBoneCount() == ...`
    const Binding* m_pOriginal;     // the constructor's assertion names it; the slots forward to its animation
    // the original animation's name with "_simple_map" appended; m_name points at it (the name is not the original's)
    mm::mtl::FixStr<64> m_nameBuf;
    // the extra bindings createBinding allocates and hands to its binding; the destructor frees them (the name is
    // not the original's)
    ExtraBinding* m_pExtraBindings;
};
}  // namespace anm

#endif
