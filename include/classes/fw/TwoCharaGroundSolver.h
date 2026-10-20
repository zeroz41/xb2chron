#ifndef CLASSES_FW_TWOCHARAGROUNDSOLVER_H
#define CLASSES_FW_TWOCHARAGROUNDSOLVER_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41D20
class TwoCharaGroundSolver {
public:
    virtual ~TwoCharaGroundSolver();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
};
}  // namespace fw

#endif
