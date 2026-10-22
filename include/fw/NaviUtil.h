#ifndef FW_NAVIUTIL_H
#define FW_NAVIUTIL_H

#include "mm/Vec3.h"

namespace fw {

// navigation mesh queries
class NaviUtil {
public:
    // navi::NvmshAccUtil::testNaviColi's answer. The parameters' meanings are not known yet.
    static bool testNaviColi(mm::Vec3& out, const mm::Vec3& pos, float param0, float param1);
    // tests the straight line from start to end on the navigation mesh, out the point it reaches; 2 when it
    // reaches end (GfGamePlayerFormation::updateImpl's test). The parameters' meanings are not known yet.
    static int testNaviStraightLine(mm::Vec3& out, const mm::Vec3& start, const mm::Vec3& end, float param0,
                                    float param1);
    // navi::NvmshAccUtil::checkNaviFindPos's answer; the last parameter is not passed on
    static int testNaviFindPos(const mm::Vec3& pos0, float param0, float param1, float param2,
                               const mm::Vec3& pos1, float param3, float param4, float param5, int param6);
};

}  // namespace fw

#endif
