#ifndef FW_NAVIUTIL_H
#define FW_NAVIUTIL_H

#include "mm/Vec3.h"

namespace fw {

// navigation mesh queries
class NaviUtil {
public:
    // tests the straight line from start to end on the navigation mesh, out the point it reaches; 2 when it
    // reaches end (GfGamePlayerFormation::updateImpl's test). The parameters' meanings are not known yet.
    static int testNaviStraightLine(mm::Vec3& out, const mm::Vec3& start, const mm::Vec3& end, float param0,
                                    float param1);
};

}  // namespace fw

#endif
