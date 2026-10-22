#ifndef ANM_SPHERICALCOORDINATESIKSOLVER_H
#define ANM_SPHERICALCOORDINATESIKSOLVER_H

#include "mm/Vec3.h"

namespace anm { class QsTransform; }

namespace anm {
// anm_spherical_coordinates_ik_solver.cpp's solver (the class name is the symbols' spelling): turns a bone towards
// a target, as far as its limits allow, by the target's elevation and azimuth around the bone's forward axis
class SphericalrdinatesIkSolver {
public:
    // fw::SphericalCoordinatesIkSolver keeps one (resetLimit fills it)
    struct Limit {
        mm::Vec3 fwdLS;     // the bone's forward axis in its own space; solve asserts `!limit.fwdLS.isZero()`
        mm::Vec3 upAxisMS;  // the up axis in model space; solve asserts `!limit.upAxisMS.isZero()`
        // the turn's bounds in radians (1.0.0's reflection names fw's degrees limitAngleUp/Down/Left/Right; these
        // names are not the original's)
        float angleUp;     // elevation at most this
        float angleDown;   // elevation at least minus this
        float angleLeft;   // azimuth at least minus this
        float angleRight;  // azimuth at most this
        bool enableLimit;  // solve clamps the turn to the bounds while set (the name is not the original's)
    };

    // turns pTransform's rotation towards target (model space); always true
    static bool solve(const Limit& limit, const mm::Vec3& target, float weight, QsTransform* pTransform);
};
}  // namespace anm

#endif
