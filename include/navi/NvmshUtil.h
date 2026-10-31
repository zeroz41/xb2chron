#ifndef NAVI_NVMSHUTIL_H
#define NAVI_NVMSHUTIL_H

#include "mm/Vec3.h"

namespace navi { class NvmshColiResult; }
namespace navi { class NvmshResObj; }
namespace navi { class NvmshConectResult; }

namespace navi {

// a navigation mesh adjacency entry (only the bits NvmshUtil::getConectDirXY reads; the names are not the
// original's)
struct _NvMhMeshAdjacency {
    unsigned short pad_0;
    unsigned short m_info;  // bits 4-5: the direction NAVI_UTIL_OFFX/OFFY step to
};

// the navigation mesh's helpers (no table, statics only)
class NvmshUtil {
public:
    // the priority table entry for the connection of a and b (num per row, the triangle above the diagonal),
    // plus one
    static int getConectPriIdx(int a, int b, int num, const unsigned char* table);
    // the grid step of adj's direction
    static void getConectDirXY(int& x, int& y, const _NvMhMeshAdjacency* adj);
    // the point of the segment a-b nearest to pos, its parameter clamped to [min, max]
    static void getPosCenterToLine(mm::Vec3& out, const mm::Vec3& pos, const mm::Vec3& a, const mm::Vec3& b,
                                   float min, float max);
    // the point of the segment a-b nearest to pos in XZ, kept at least len from both ends (the middle when the
    // segment is shorter than 2 len)
    static void getPosCenterToXZLineLength(mm::Vec3& out, const mm::Vec3& pos, const mm::Vec3& a,
                                           const mm::Vec3& b, float len);
    // whether the XZ ray pos + t dir (t in [0, 1]) crosses the segment a-b
    static bool getSubLineToLine(const mm::Vec3& pos, const mm::Vec3& dir, const mm::Vec3& a, const mm::Vec3& b);
    // as above, both parameters in [min, max]
    static bool getSubLineToLine(const mm::Vec3& pos, const mm::Vec3& dir, const mm::Vec3& a, const mm::Vec3& b,
                                 float min, float max);
    // the mean of polygon idx's vertices
    static void getPoliCenter(mm::Vec3& out, const NvmshResObj* obj, int idx);

    static const int NAVI_UTIL_OFFX[4];
    static const int NAVI_UTIL_OFFY[4];
    // the connection priority tables for 3, 4, 5 and 6 connections (num x num bytes each, symmetric; calcAStar
    // and NvmshAcObjBase::calcConectOptimization read it)
    static const unsigned char* NAVI_UTIL_ADJTBL[4];
};

// navigation mesh collision queries (no table, made on the stack). The field names are not the original's.
class NvmshUtilColi {
public:
    NvmshUtilColi();
    // clears the attribute bits when clear is set, else sets them
    void setAttr(bool clear, unsigned int attr);
    bool testPointRadius(NvmshColiResult* result);

    unsigned char pad_0[0x70];
    float m_radius;  // 3.0 (the name is not the original's)
    unsigned char pad_74[0x4];
    int m_meshIdx;  // -1
    short m_meshSub;  // -1
    unsigned char pad_7E[0x2];
    unsigned int m_attr;  // 0x80, setAttr's bits
    int m_hitNum;  // 0
    short m_count0;  // 0
    short m_count1;  // 0
};

// A* searches over the navigation mesh's connections (no table, made on the stack)
class NvmshUtilConect {
public:
    NvmshUtilConect();
    bool seachConectAStar(NvmshConectResult* result, bool flag);
    bool seachSeamConectAStar(NvmshConectResult* result, bool flag);
    bool calcConectAStar();
    bool calcSeamAStar();

    NvmshConectResult* m_result;
    bool m_flag;  // the seach functions' flag (the name is not the original's)
    bool m_running;  // cleared by the constructor (the name is not the original's)
};

// an A* search's result (only what NvmshUtilSeach::seachAStar clears; the name of the field is not the
// original's)
class NvmshAStarResult {
public:
    unsigned char pad_0[0x48];
    int m_count;
};

// A* searches over the navigation mesh (no table, made on the stack)
class NvmshUtilSeach {
public:
    NvmshUtilSeach();
    bool seachAStar(NvmshAStarResult* result);
    bool calcAStar();

    NvmshAStarResult* m_result;
    short m_count;  // cleared by the constructor (the name is not the original's)
};

}  // namespace navi

#endif
