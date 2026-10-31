#ifndef NAVI_NVMSHACCUTIL_H
#define NAVI_NVMSHACCUTIL_H

namespace mm { class Vec3; }
namespace navi { class NvmshManager; }

namespace navi {
// queries on the navigation mesh, made on a stack object (fw::NaviUtil's functions)
class NvmshAccUtil {
public:
    NvmshAccUtil();  // takes NvmshManager's instance
    bool testNaviColi(mm::Vec3& out, const mm::Vec3& pos, float param0, float param1, int param2);
    // testNaviColi passes 0.01 for range (the parameter names are not the original's)
    bool testNaviColiRange(mm::Vec3& out, const mm::Vec3& pos, float range, float param0, float param1,
                           int param2);
    int testNaviStraightLine(mm::Vec3& out, const mm::Vec3& start, const mm::Vec3& end, float param0,
                             float param1, int param2);
    int checkNaviFindPos(const mm::Vec3& pos0, float param0, float param1, float param2, float param3,
                         const mm::Vec3& pos1, float param4, float param5, float param6, float param7,
                         int param8);

    NvmshManager* m_manager;  // the constructor's (NvmshManager's instance; the name is not the original's)
    bool m_flag;  // cleared by the constructor (the name is not the original's)
    unsigned char pad_9[0x7];
};
}  // namespace navi

#endif
