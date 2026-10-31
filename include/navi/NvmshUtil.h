#ifndef NAVI_NVMSHUTIL_H
#define NAVI_NVMSHUTIL_H

#include "mm/Vec3.h"
#include "navi/NvmshResData.h"

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

// a mesh query's input and result (0xB0 bytes, NvmshAcObjBase::seachNaviMesh fills one on the stack; only the
// members NvmshUtilColi reads are declared, the names are not the original's)
class NvmshColiResult {
public:
    unsigned char pad_0[0xA0];
    _NaviCalcResTbl* m_tbl;  // the layer's resources (NvmshAcObjBase::seachNaviMesh's _NaviCalcResTbl*)
    _NaviCalcResInfo* m_info;  // the read bank's work (its _NaviCalcResInfo*)
};

// navigation mesh collision queries (no table, made on the stack). The field names are not the original's.
class NvmshUtilColi {
public:
    NvmshUtilColi();
    // clears the attribute bits when clear is set, else sets them
    void setAttr(bool clear, unsigned int attr);
    bool testPointRadius(NvmshColiResult* result);
    bool testWideAreaOldMeshPointRay(NvmshColiResult* result, const _NaviStMeshId* id);
    bool treePointRay(const _NvMhMeshTree* tree);
    bool treeRadiusRay(const _NvMhMeshTree* tree);
    bool treeRangeRay(const _NvMhMeshTree* tree);
    bool coliMeshPointRay(int mesh);
    bool coliMeshRangeAddRay(int mesh);
    bool coliMeshRangeRay(int mesh);

    // m_conect and m_adj for obj, the navi tested (the name is not the original's)
    void setConect(const _NaviCalcResTbl* tbl, const NvmshResObj* obj) {
        const unsigned short* cells = reinterpret_cast<const unsigned short*>(tbl->m_conectBlocks[0]);
        int n = cells[tbl->m_info->m_worldHead->m_gridW * obj->m_head->m_cellY + obj->m_head->m_cellX];
        m_conect = reinterpret_cast<const unsigned short*>(tbl->m_conectBlocks[7]) +
                   reinterpret_cast<const unsigned short*>(tbl->m_conectBlocks[1])[n * 2 - 1];
        m_adj = obj->m_blocks[6];
    }

    unsigned int* m_bits;  // a bit per mesh tested (the read bank's _NaviCalcResInfo::m_bufs[0])
    NvmshColiResult* m_result;
    NvmshResObj* m_obj;  // the navi tested
    const NvmshResObj::Head* m_head;  // m_obj's head
    unsigned char pad_20[0x8];
    const unsigned char* m_adj;  // m_obj's block 6
    const unsigned short* m_conect;  // the navi's connection entries (the layer's connection block 7)
    unsigned char pad_38[0x8];
    mm::Vec3 m_max;  // the query's bounds, relative to the navi's tree origin
    mm::Vec3 m_min;
    unsigned char pad_60[0x10];
    float m_radius;  // 3.0
    float m_radiusSq;
    int m_meshIdx;  // -1
    short m_meshSub;  // -1
    unsigned char pad_7E[0x2];
    unsigned int m_attr;  // 0x80, setAttr's bits
    int m_hitNum;  // 0; non-zero: the tests set m_adj and m_conect
    // NvmshAcObjBase::seachNaviMesh's options (the names are not the original's): with pad_38's value, with
    // pad_60's vector, with m_meshSub (testPointRay skips the way points when that mesh was hit), and the way
    // point test
    bool m_useParam;
    bool m_useVec;
    bool m_useOldMesh;
    bool m_useWayPoint;
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
