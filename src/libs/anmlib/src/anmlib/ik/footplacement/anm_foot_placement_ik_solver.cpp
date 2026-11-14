#include "classes/anm/FootPlacementIKSolver.h"
#include <new>

namespace anm {

// the constructor (0x7100869F44), doFootPlacement, castFoot and TransformUtil::calcShortestRotationLimit
// are not here yet

FootPlacementIKSolver* FootPlacementIKSolver::create(const Description& desc, mm::mtl::IAllocator& allocator) {
    FootPlacementIKSolver* solver =
        new (allocator.allocate(sizeof(FootPlacementIKSolver), 16)) FootPlacementIKSolver(desc, allocator);
    solver->addRef();
    return solver;
}

FootPlacementIKSolver::~FootPlacementIKSolver() {}

}  // namespace anm
