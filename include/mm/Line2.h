#ifndef MM_LINE2_H
#define MM_LINE2_H

#include "mm/Vec3.h"

namespace mm {
// a segment: its direction and its two ends (fw::PrimCapsule::setup fills it; the field names are not the
// original's)
class Line2 {
public:
    // the shortest distance between two segments, and between a segment and a point
    static float getNearestLength(const Line2& a, const Line2& b);
    static float getNearestLength(const Line2& line, const Vec3& point);

    Vec3 m_dir;  // from the second end to the first, of length 1 (zero for a segment too short)
    Vec3 m_start;
    Vec3 m_end;
};
}  // namespace mm

#endif
