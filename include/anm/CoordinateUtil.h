#ifndef ANM_COORDINATEUTIL_H
#define ANM_COORDINATEUTIL_H

namespace mm { class Vec3; }

namespace anm {
// conversions between rectangular coordinates (x, y, z) and spherical ones (radius, elevation, azimuth), in place
class CoordinateUtil {
public:
    // (x, y, z) to (length, arc sine of y over it, atan2 of x and z); a vector too short for that becomes zero
    static void convertRCSToSPC(mm::Vec3* pVec);
    // (radius, elevation, azimuth) back to (x, y, z)
    static void convertSPCToRCS(mm::Vec3* pVec);
};
}  // namespace anm

#endif
