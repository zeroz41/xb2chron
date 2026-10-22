#include "math.h"
#include "mm/Math.h"
#include "anm/CoordinateUtil.h"

#include "mm/MMStdBase.h"
#include "mm/Vec3.h"

namespace anm {

void CoordinateUtil::convertRCSToSPC(mm::Vec3* pVec) {
#line 20
    MM_ASSERT(pVec);
    float radius = pVec->length();
    if (radius < 1.1920929e-07f) {
        *pVec = mm::Vec3::zero;
        return;
    }
    float elevation = mm::asin(pVec->y / radius);
    float azimuth = ::atan2f(pVec->x, pVec->z);
    pVec->x = radius;
    pVec->y = elevation;
    pVec->z = azimuth;
}

// convertSPCToRCS (0x71008845F8) is not matched yet

}  // namespace anm
