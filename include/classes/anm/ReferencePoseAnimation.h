#ifndef CLASSES_ANM_REFERENCEPOSEANIMATION_H
#define CLASSES_ANM_REFERENCEPOSEANIMATION_H

#include "classes/anm/Animation.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }

namespace anm {
// table 0x7100B81298
class ReferencePoseAnimation : public ::anm::Animation {
public:
    virtual ~ReferencePoseAnimation();  // slot 0
    virtual int getImplType() const;  // slot 2
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const;  // slot 3
};
}  // namespace anm

#endif
