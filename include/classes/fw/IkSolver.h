#ifndef CLASSES_FW_IKSOLVER_H
#define CLASSES_FW_IKSOLVER_H

#include "mm/mtl/RTTI.h"
namespace fw {
// table 0x7100B41B78
class IkSolver {
public:
    virtual ~IkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void vf3() = 0;  // slot 3
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
