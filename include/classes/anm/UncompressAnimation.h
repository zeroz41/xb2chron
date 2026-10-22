#ifndef CLASSES_ANM_UNCOMPRESSANIMATION_H
#define CLASSES_ANM_UNCOMPRESSANIMATION_H

#include "anm/Array.h"
#include "anm/QsTransform.h"
#include "classes/anm/Animation.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }
namespace anm { class SerialiseArg; }

namespace anm {
// table 0x7100B81318; an animation kept as every track's transform at every frame
class UncompressAnimation : public ::anm::Animation {
public:
    UncompressAnimation(const SerialiseArg& arg);

    virtual ~UncompressAnimation() {}  // slot 0
    virtual int getImplType() const;  // slot 2
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const;  // slot 3

    // the transforms frame by frame, each frame's tracks together (the name is not the original's)
    Array<QsTransform> m_transforms;
};
}  // namespace anm

#endif
