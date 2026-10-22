#ifndef ANM_LOOKATIKSOLVER_H
#define ANM_LOOKATIKSOLVER_H

#include "mm/Vec3.h"

namespace anm { class QsTransform; }

namespace anm {
// anm_look_at_ik_solver.cpp's solver: turns a bone towards a target, within its limits (the field names are its
// assertions' spelling where one names them)
class LookAtIKSolver {
public:
    // fw::LookAtIkSolver keeps one (resetLimit fills it)
    struct Limit {
        mm::Vec3 fwdLS;        // the bone's forward axis in its own space; solve asserts `!limit.fwdLS.isZero()`
        mm::Vec3 pad_10;       // unknown: fw::LookAtIkSolver::resetLimit zeroes it; solve does not read it
        mm::Vec3 limitAxisMS;  // solve asserts `!limit.limitAxisMS.isZero()`
        float limitAngle;      // radians; solve asserts `(0.0f <= limit.limitAngle) && (limit.limitAngle <= PI)`
    };
    // the turn's bounds in radians around upAxisMS (solve asserts each one's range)
    struct RangeLimit {
        float limitAngleUp;
        float limitAngleDown;
        float limitAngleLeft;
        float limitAngleRight;
        mm::Vec3 upAxisMS;  // solve asserts `!pRange->upAxisMS.isZero()`
    };

    // turns pTransform's rotation towards target (model space), by weight; pRange may be null
    static void solve(const Limit& limit, const mm::Vec3& target, float weight, QsTransform* pTransform,
                      RangeLimit* pRange);
};
}  // namespace anm

#endif
