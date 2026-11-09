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

void CoordinateUtil::convertSPCToRCS(mm::Vec3* pVec) {
#line 45
    MM_ASSERT(pVec);
    float elevation = pVec->y;
    float sinElevation = ::sinf(elevation);
    float cosElevation = ::cosf(elevation);
    float azimuth = pVec->z;
    float sinAzimuth = ::sinf(azimuth);
    float cosAzimuth = ::cosf(azimuth);
    float radius = pVec->x;
    float horizontal = cosElevation * radius;
    float z = cosAzimuth * horizontal;
    float x = sinAzimuth * horizontal;
    pVec->x = x;
    pVec->y = sinElevation * radius;
    pVec->z = z;
}

}  // namespace anm
