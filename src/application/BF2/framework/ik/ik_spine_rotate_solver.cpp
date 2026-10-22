#include "classes/fw/SpineRotateIKSolver.h"
#include "classes/fw/IkFadeSolver.h"

namespace fw {

SpineRotateIKSolver::~SpineRotateIKSolver() {}

mm::mtl::RTTI SpineRotateIKSolver::m_rtti("SpineRotateIKSolver", &IkFadeSolver::m_rtti, nullptr);

}  // namespace fw
