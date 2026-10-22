#ifndef FW_TWOJOINTIKSOLVER_H
#define FW_TWOJOINTIKSOLVER_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/fw/IkFadeSolver.h"

namespace anm { class Pose; }
namespace fw { class ReferenceFrame; }
namespace fw { class UpdateInfo; }

namespace fw {
// 1.0.0 table 0x7101178928 (names from its symbols); 3.0.1 has none: its linker dropped the class code as unused, only
// its RTTI and its file's strings remain.
class TwoJointIkSolver : public ::fw::IkFadeSolver {
public:
    struct Description;

    TwoJointIkSolver();
    virtual ~TwoJointIkSolver();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual void calcIK(fw::UpdateInfo const&);  // slot 7
    // a solver set up from `desc`, or null when setupLimit fails
    static TwoJointIkSolver* create(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame,
                                    anm::Pose& pose);
    bool setupLimit(const Description& desc, mm::mtl::IntrusivePtr<fw::ReferenceFrame>& frame, anm::Pose& pose);
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_38[0x88];  // 1.0.0's allocation: 0xC0 bytes
};
}  // namespace fw

#endif
