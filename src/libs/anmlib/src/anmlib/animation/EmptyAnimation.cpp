#include "math.h"
#include "anm/Array.h"
#include "mm/Vec4.h"
#include "classes/anm/Animation.h"
#include "classes/anm/EmptyAnimation.h"
#include "anm/SerialiseArg.h"
#include "anm/Locomotion.h"
#include "anm/TransformUtil.h"
#include "anm/QsTransform.h"
#include "mm/Math.h"
#include "mm/MMStdBase.h"

namespace anm {

EmptyAnimation::EmptyAnimation(const SerialiseArg&) {}

void EmptyAnimation::sampleTrucks(float, const anm::Binding&, anm::QsTransform*) const {}

int EmptyAnimation::getImplType() const {
    return 2;
}

}  // namespace anm
