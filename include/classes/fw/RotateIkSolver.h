#ifndef CLASSES_FW_ROTATEIKSOLVER_H
#define CLASSES_FW_ROTATEIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/IkFadeSolver.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41AA8
class RotateIkSolver : public ::fw::IkFadeSolver {
public:
    virtual ~RotateIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
