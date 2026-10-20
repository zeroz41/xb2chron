#ifndef CLASSES_FW_LOOKATIKSOLVER_H
#define CLASSES_FW_LOOKATIKSOLVER_H

#include "classes/fw/IkFadeSolver.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B419F0
class LookAtIkSolver : public ::fw::IkFadeSolver {
public:
    virtual ~LookAtIkSolver();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void onDisable();  // slot 6
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
};
}  // namespace fw

#endif
