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

bool PlaneRayCaster::castRay(const mm::Vec3& from, const mm::Vec3& to, mm::Vec3* pHitPos, mm::Vec3* pNormal) {
    bool result = false;
    if (m_ground) {
        if (const mm::Plane* plane = m_ground->getPlane()) {
            float fromDistance = from.dot(plane->normal) + plane->d;
            float toDistance = to.dot(plane->normal) + plane->d;
            if (fromDistance >= 0.0f && toDistance <= 0.0f) {
                float dx = to.x - from.x;
                float dy = to.y - from.y;
                float dz = to.z - from.z;
                mm::Vec3 dir(dx, dy, dz);
                float denom = fabsf(dx * plane->normal.x + dy * plane->normal.y + dz * plane->normal.z);
                float t = denom > 1.1920929e-07f ? fabsf(fromDistance) / denom : 0.0f;
                *pHitPos = dir * t + from;
                *pNormal = plane->normal;
                result = true;
            }
        }
    }
    return result;
}

}  // namespace fw
