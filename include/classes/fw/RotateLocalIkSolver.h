#ifndef CLASSES_FW_ROTATELOCALIKSOLVER_H
#define CLASSES_FW_ROTATELOCALIKSOLVER_H

#include "classes/fw/IkFadeSolver.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41AF8
class RotateLocalIkSolver : public ::fw::IkFadeSolver {
public:
    virtual ~RotateLocalIkSolver();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
};
}  // namespace fw

#endif
