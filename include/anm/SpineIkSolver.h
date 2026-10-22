#ifndef ANM_SPINEIKSOLVER_H
#define ANM_SPINEIKSOLVER_H

#include "mm/Vec3.h"

namespace anm { class QsTransform; }

namespace anm {
// anm_spine_ik_solver's solver (its solve sits in anm_two_joint_ik_solver.cpp's range): turns two spine bones
// towards a target. The field names are not the original's: the angles' and responses' are those of the parameter
// block fw::SpineIkSolver fills them from (1.0.0's SpineIkSolver::Param reflection)
class SpineIKSolver {
public:
    // fw::SpineIkSolver keeps one (setupLimit fills it)
    struct Description {
        // assigned in the body: the original stores the bones apart and the floats in pairs
        Description() {
            bones[0] = 0xFFFF;
            bones[1] = 0xFFFF;
            angleThreasold0 = 0.0f;
            angleThreasold1 = 0.0f;
            response0 = 0.1f;
            response1 = 0.1f;
            limitAngle0 = 1.5f;
            limitAngle1 = 1.5f;
        }

        unsigned short bones[2];  // the two bones' indices, 0xFFFF for none
        float angleThreasold0;    // radians
        float angleThreasold1;    // radians
        float response0;
        float response1;
        float limitAngle0;  // radians
        float limitAngle1;  // radians
    };
    // what solve turns the bones by (fw::SpineIkSolver::calcIK fills it)
    struct Input {
        mm::Vec3 target;   // in the frame's space
        mm::Vec3 frontMS;  // the forward axis in model space
        float weight0;
        float weight1;
    };
    // which bones solve turned
    struct Output {
        // clears both (fw::SpineIkSolver::calcIK's: the values as one word)
        Output() : flags(0), values() {}

        unsigned int flags;  // bit 0: the first bone's, bit 1: the second's
        // a value per bone solve sets with its flag (fw::SpineIkSolver::calcIK keeps them; what they are is not
        // known yet, and the name is not the original's)
        float values[2];
    };

    static void solve(const Description& desc, const Input& input, QsTransform* pTransform0, QsTransform* pTransform1,
                      Output* pOutput);
};
}  // namespace anm

#endif
