#ifndef CLASSES_FW_FOOTPLACEMENTIKSOLVER_H
#define CLASSES_FW_FOOTPLACEMENTIKSOLVER_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41968
class FootPlacementIKSolver {
public:
    virtual ~FootPlacementIKSolver();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
};
}  // namespace fw

#endif
