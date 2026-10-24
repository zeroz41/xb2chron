#include "mm/Vec4.h"
#include "mm/Quat.h"
#include "classes/anm/Animation.h"
#include "classes/anm/UncompressAnimation.h"
#include "classes/anm/Skeleton.h"
#include "anm/BlendUtil.h"
#include "math.h"
#include "anm/Array.h"
#include "anm/QsTransform.h"
#include "anm/SerialiseArg.h"
#include "anm/TransformUtil.h"
#include "classes/anm/Binding.h"
#include "mm/MMStdBase.h"

namespace anm {

UncompressAnimation::UncompressAnimation(const SerialiseArg&) {}

int UncompressAnimation::getImplType() const {
    return 0;
}

}  // namespace anm
