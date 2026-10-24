#include "classes/fw/IkFadeSolver.h"
#include "mm/Plane.h"
#include "anm/LookAtIkSolver.h"
#include "classes/anm/RaycastInterface.h"
#include "classes/fw/IKFootGroundInterface.h"
#include "classes/fw/PlaneRayCaster.h"
#include "classes/fw/LookAtIkSolver.h"
#include "classes/fw/IkSolver.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/anm/Pose.h"
#include "classes/anm/Skeleton.h"
#include "anm/QsTransform.h"
#include "fw/Allocator.h"
#include "fw/UpdateInfo.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/Quat.h"
#include "math.h"

namespace fw {

PlaneRayCaster::PlaneRayCaster() : m_ground(nullptr) {}

void PlaneRayCaster::bind(IKFootGroundInterface& ground) {
    m_ground = &ground;
}

}  // namespace fw
