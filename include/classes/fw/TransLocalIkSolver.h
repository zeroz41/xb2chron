#ifndef CLASSES_FW_TRANSLOCALIKSOLVER_H
#define CLASSES_FW_TRANSLOCALIKSOLVER_H

#include "classes/fw/IkFadeSolver.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41CD0
class TransLocalIkSolver : public ::fw::IkFadeSolver {
public:
    virtual ~TransLocalIkSolver();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
};
}  // namespace fw

#endif
