#ifndef CLASSES_FW_LOOKIKSOLVER_H
#define CLASSES_FW_LOOKIKSOLVER_H

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B41A40
class LookIkSolver {
public:
    virtual ~LookIkSolver();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void solve(fw::UpdateInfo const&);  // slot 3
    virtual bool isEnable() const;  // slot 4
};
}  // namespace fw

#endif
