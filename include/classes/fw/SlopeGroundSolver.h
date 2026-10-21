#ifndef CLASSES_FW_SLOPEGROUNDSOLVER_H
#define CLASSES_FW_SLOPEGROUNDSOLVER_H

#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41B48
class SlopeGroundSolver {
public:
    virtual ~SlopeGroundSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
