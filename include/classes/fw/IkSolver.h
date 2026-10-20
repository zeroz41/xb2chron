#ifndef CLASSES_FW_IKSOLVER_H
#define CLASSES_FW_IKSOLVER_H

namespace fw {
// table 0x7100B41B78
class IkSolver {
public:
    virtual ~IkSolver();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual void vf3() = 0;  // slot 3
};
}  // namespace fw

#endif
