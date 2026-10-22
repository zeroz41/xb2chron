#include "classes/fw/RotateIkSolver.h"
#include "classes/fw/RotateLocalIkSolver.h"
#include "classes/fw/IkFadeSolver.h"

namespace fw {

RotateIkSolver::~RotateIkSolver() {}

RotateLocalIkSolver::~RotateLocalIkSolver() {}

mm::mtl::RTTI RotateIkSolver::m_rtti("RotateIkSolver", &IkFadeSolver::m_rtti, nullptr);
mm::mtl::RTTI RotateLocalIkSolver::m_rtti("RotateLocalIkSolver", &IkFadeSolver::m_rtti, nullptr);

}  // namespace fw
