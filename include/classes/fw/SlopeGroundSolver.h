#ifndef CLASSES_FW_SLOPEGROUNDSOLVER_H
#define CLASSES_FW_SLOPEGROUNDSOLVER_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/IkSolver.h"
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41B48; an IkSolver (its m_rtti's base)
class SlopeGroundSolver : public ::fw::IkSolver {
public:
    virtual ~SlopeGroundSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    void setEnablePlacement(bool enable);
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_20[0x68];
    bool m_enableSlope;  // slopeBody tilts the body only when set; FootIkControllerPlugin sets it with the placement
                         // (the name is not the original's)
};
}  // namespace fw

#endif
