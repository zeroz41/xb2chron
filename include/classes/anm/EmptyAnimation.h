#ifndef CLASSES_ANM_EMPTYANIMATION_H
#define CLASSES_ANM_EMPTYANIMATION_H

#include "classes/anm/Animation.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }

namespace anm {
// table 0x7100B81218
class EmptyAnimation : public ::anm::Animation {
public:
    virtual ~EmptyAnimation();  // slot 0
    virtual void getImplType() const;  // slot 2
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const;  // slot 3
};
}  // namespace anm

#endif
