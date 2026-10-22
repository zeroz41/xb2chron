#ifndef CLASSES_ANM_ANIMATION_H
#define CLASSES_ANM_ANIMATION_H

#include "anm/AnimationObject.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }

namespace anm {
// table none (its derived classes')
class Animation : public ::anm::AnimationObject {
public:
    // trivial and inline: a derived class's slot holds AnimationObject's
    virtual ~Animation() {}  // slot 0
    virtual int getImplType() const = 0;  // slot 2: which kind (the type is not the original's)
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const = 0;  // slot 3
    virtual void getExtractMotion(float, anm::QsTransform*) const;  // slot 4
    virtual void getDeltaExtractMotion(float, float, bool, anm::QsTransform*) const;  // slot 5
};
}  // namespace anm

#endif
