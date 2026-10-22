#include "classes/fw/LookAtIkSolver.h"
#include "classes/fw/IkFadeSolver.h"

namespace fw {

LookAtIkSolver::~LookAtIkSolver() {}

mm::mtl::RTTI LookAtIkSolver::m_rtti("LookAtIkSolver", &IkFadeSolver::m_rtti, nullptr);

}  // namespace fw
