#ifndef CLASSES_FW_TWOCHARAGROUNDSOLVER_H
#define CLASSES_FW_TWOCHARAGROUNDSOLVER_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/IkSolver.h"
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41D20; an IkSolver (its m_rtti's base)
class TwoCharaGroundSolver : public ::fw::IkSolver {
public:
    virtual ~TwoCharaGroundSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    void setEnablePlacement(bool enable);
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_20[0x88];
    int m_syncDown;  // 1 while FootIkControllerPlugin syncs down (attribute 0x2 or the "syncDownOn" ik event): the
                     // feet's placement is off (the name is not the original's)
    unsigned char pad_ac[0xd];
    bool m_enableDown;  // as PlacementGroundSolver's (the name is not the original's)
};
}  // namespace fw

#endif
