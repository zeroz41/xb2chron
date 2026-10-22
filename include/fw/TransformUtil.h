#ifndef FW_TRANSFORMUTIL_H
#define FW_TRANSFORMUTIL_H

#include "fw/Transform.h"

namespace anm { class QsTransform; }

namespace fw {
// transform helpers (application/BF2/battle/EffectMoveComponent's unit holds them)
class TransformUtil {
public:
    // lhs times rhs into pOut (fw::TwoCharaGroundSolver passes a frame's world transform, a bone's model-space
    // transform and 1.0; the parameter names are not the original's)
    static void mul(const Transform& lhs, const anm::QsTransform& rhs, float scale, Transform* pOut);
};
}  // namespace fw

#endif
