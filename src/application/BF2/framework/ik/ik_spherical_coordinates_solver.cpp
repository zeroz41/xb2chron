#include "classes/fw/SphericalCoordinatesIkSolver.h"
#include "classes/fw/IkSolver.h"

namespace fw {

SphericalCoordinatesIkSolver::~SphericalCoordinatesIkSolver() {}

mm::mtl::RTTI SphericalCoordinatesIkSolver::m_rtti("SphericalCoordinatesIkSolver", &IkSolver::m_rtti, nullptr);

}  // namespace fw
