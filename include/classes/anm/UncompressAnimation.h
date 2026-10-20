#ifndef CLASSES_ANM_UNCOMPRESSANIMATION_H
#define CLASSES_ANM_UNCOMPRESSANIMATION_H

#include "classes/anm/Animation.h"

namespace anm { class Binding; }
namespace anm { class QsTransform; }

namespace anm {
// table 0x7100B81318
class UncompressAnimation : public ::anm::Animation {
public:
    virtual ~UncompressAnimation();  // slot 0
    virtual void getImplType() const;  // slot 2
    virtual void sampleTrucks(float, anm::Binding const&, anm::QsTransform*) const;  // slot 3
};
}  // namespace anm

#endif
