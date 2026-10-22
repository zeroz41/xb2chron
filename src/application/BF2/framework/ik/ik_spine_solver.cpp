#include "classes/fw/SpineIkSolver.h"
#include "classes/fw/IkFadeSolver.h"

namespace fw {

SpineIkSolver::~SpineIkSolver() {}

mm::mtl::RTTI SpineIkSolver::m_rtti("SpineIkSolver", &IkFadeSolver::m_rtti, nullptr);

}  // namespace fw
