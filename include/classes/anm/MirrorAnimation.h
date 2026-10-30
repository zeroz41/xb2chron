#ifndef CLASSES_ANM_MIRRORANIMATION_H
#define CLASSES_ANM_MIRRORANIMATION_H

#include "classes/anm/Animation.h"
#include "mm/mtl/FixStr.h"

namespace anm { class Binding; }
namespace anm { class MirrorMapper; }
namespace anm { class QsTransform; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {
// table 0x7100B81258; a binding's animation mirrored through a MirrorMapper
class MirrorAnimation : public ::anm::Animation {
public:
    MirrorAnimation(const Binding* pBinding, const MirrorMapper* pMapper, mm::mtl::IAllocator* pAllocator);
    virtual ~MirrorAnimation();  // slot 0
    virtual int getImplType() const;  // slot 2
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const;  // slot 3
    virtual bool getExtractMotion(float, anm::QsTransform*) const;  // slot 4
    virtual bool getDeltaExtractMotion(float, float, bool, anm::QsTransform*) const;  // slot 5
    // the binding of the mirrored animation to the mapper's skeleton
    Binding* createBinding();

    // Factory::createMirrorAnimation allocates 0xA0 bytes
    const MirrorMapper* m_pMapper;  // the constructor's parameter pMapper; the slots mirror through it
    const Binding* m_pOriginal;     // the binding whose animation is mirrored; the slots forward to its animation
    // the original animation's name with "_mirror" appended; m_name points at it (the name is not the original's)
    mm::mtl::FixStr<64> m_nameBuf;
};
}  // namespace anm

#endif
