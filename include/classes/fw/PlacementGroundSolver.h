#ifndef CLASSES_FW_PLACEMENTGROUNDSOLVER_H
#define CLASSES_FW_PLACEMENTGROUNDSOLVER_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/IkSolver.h"
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41A78; an IkSolver (its m_rtti's base)
class PlacementGroundSolver : public ::fw::IkSolver {
public:
    virtual ~PlacementGroundSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    void setEnablePlacement(bool enable);
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_20[0x45];
    bool m_enableDown;  // FootIkControllerPlugin's down IK (its attribute 0x8 or setEnableDownIK); solve keeps the
                        // root's height when set (the name is not the original's)
};
}  // namespace fw

#endif
