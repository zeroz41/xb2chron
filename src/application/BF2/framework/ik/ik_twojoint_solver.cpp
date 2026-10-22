#include "fw/TwoJointIkSolver.h"
#include "fw/Allocator.h"
#include "classes/mm/mtl/IAllocator.h"

namespace fw {

// 1.0.0's (name from its symbols); 3.0.1's linker dropped it as unused, leaving only its file string in this
// file's .rodata.
TwoJointIkSolver* TwoJointIkSolver::create(const Description& desc, mm::mtl::IntrusivePtr<ReferenceFrame>& frame,
                                           anm::Pose& pose) {
#line 30
    TwoJointIkSolver* solver = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) TwoJointIkSolver();
    if (!solver->setupLimit(desc, frame, pose)) {
        if (solver != nullptr) {
            solver->release();
        }
        return nullptr;
    }
    solver->addRef();
    return solver;
}

mm::mtl::RTTI TwoJointIkSolver::m_rtti("TwoJointIkSolver", &IkFadeSolver::m_rtti, nullptr);

}  // namespace fw
