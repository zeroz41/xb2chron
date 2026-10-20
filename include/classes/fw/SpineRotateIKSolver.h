#ifndef CLASSES_FW_SPINEROTATEIKSOLVER_H
#define CLASSES_FW_SPINEROTATEIKSOLVER_H

#include "classes/fw/IkFadeSolver.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41C30
class SpineRotateIKSolver : public ::fw::IkFadeSolver {
public:
    virtual ~SpineRotateIKSolver();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
};
}  // namespace fw

#endif
