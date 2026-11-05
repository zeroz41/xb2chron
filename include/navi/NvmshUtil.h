#ifndef NAVI_NVMSHUTIL_H
#define NAVI_NVMSHUTIL_H

#include "mm/Vec3.h"
#include "navi/NvmshResData.h"
#include "classes/navi/NvmshAcObjBase.h"

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
    // the tables NAVI_UTIL_ADJTBL points at, one per connection count
    static const unsigned char NAVI_UTIL_ADJTBL3[3 * 3];
    static const unsigned char NAVI_UTIL_ADJTBL4[4 * 4];
    static const unsigned char NAVI_UTIL_ADJTBL5[5 * 5];
    static const unsigned char NAVI_UTIL_ADJTBL6[6 * 6];
};

// a mesh query's input and result (0xB0 bytes, NvmshAcObjBase::seachNaviMesh fills one on the stack; only the
// members NvmshUtilColi reads are declared, the names are not the original's)
class NvmshColiResult {
public:
    unsigned char pad_0[0x20];
    mm::Vec3 m_hitPos;  // NvmshAcObjBase::seachNaviMesh copies it to _NaviTempColiResl::m_pos
    unsigned char pad_30[0x40];
    _NaviStMeshId m_hitMesh;  // NvmshAcObjBase::seachNaviMesh copies it to _NaviTempColiResl::m_mesh
    unsigned char pad_74[0x18];
    float m_radiusSq;  // the query radius squared (seachNaviMesh's setup); copied to _NaviTempColiResl::m_radiusSq
    unsigned char pad_90[0xC];
    // seachNaviMesh's setup sets m_isHit when the radius is not 0 and clears m_isWayPoint (read as one halfword)
    unsigned short m_isHit : 8;
    unsigned short m_isWayPoint : 8;
    unsigned char pad_9E[0x2];
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

// a node of a navi layer's connection graph (block 2 of _NvMhConectData, 0xC bytes; the type and member names are
// not the original's): m_linkNum links from m_linkOfs in block 3
struct _NvMhConectNode {
    unsigned char pad_0[0x2];
    unsigned char m_linkNum;
    unsigned char pad_3;
    unsigned int m_linkOfs;
    unsigned char pad_8[0x4];
};

// a connection's two ends (block 4 of _NvMhConectData, 0x8 bytes; block 3's links index it: bits 0-27 the pair,
// bit 31 the end; the names are not the original's)
struct _NvMhConectPair {
    struct End {
        unsigned short pad_0;
        unsigned short m_node;  // the node (block 2 index) at this end
    };
    End m_ends[2];
};

// what NvmshAcObjBase::checkConectRoot passes NvmshUtilConect's searches (on its stack; the member names are not
// the original's)
class NvmshConectResult {
public:
    _NaviCalcResTbl* m_tbl;
    _NaviCalcResInfo* m_info;  // m_bufs[0]: a bit per usable node, m_bufs[1]: a cost per node (bit 15: reached
                               // from the goal)
    unsigned char* m_route;  // the route is stored back from m_route + m_routeSize (NvmshAcObjBase's 0x30/0x38)
    int m_routeSize;
    int m_routeNum;
    int m_linkIdx;
    _NaviStMeshId m_start;
    _NaviStMeshId m_goal;
};

// A* searches over the navigation mesh's connections (no table, made on the stack)
class NvmshUtilConect {
public:
    NvmshUtilConect();
    bool seachConectAStar(NvmshConectResult* result, bool flag);
    bool seachSeamConectAStar(NvmshConectResult* result, bool flag);
    bool calcConectAStar();
    bool calcSeamAStar();
    void stockResult(int node, const unsigned char* pri, int fastNum, int endNum);
    int stockFastResult(unsigned short* route, int node, int num);
    int stockEndResult(unsigned short* route, int node, int num);

    NvmshConectResult* m_result;
    bool m_flag;  // the seach functions' flag (the name is not the original's)
    bool m_running;  // cleared by the constructor (the name is not the original's)
};

// an A* search's result (only what NvmshUtilSeach::seachAStar clears; the name of the field is not the
// original's)
class NvmshAStarResult {
public:
    // the layout is NvmshAcObjBase::findPosRoot's setup and read back (the member names are not the original's)
    mm::Vec3 m_startPos;
    mm::Vec3 m_goalPos;
    _NaviCalcResTbl* m_tbl;
    _NaviCalcResInfo* m_info;
    _NaviStMeshId* m_route;  // the route's meshes (NvmshAcObjBase's route buffer)
    int m_routeNum;  // the route's length (read back into NvmshAcObjBase::m_route50)
    int m_routeMax;  // the room in m_route
    NvmshAcObjBase::ReadCell* m_cells;  // the cells the route crosses (NvmshAcObjBase::m_readCells)
    int m_count;  // m_cells' count
    _NaviStMeshId m_start;
    _NaviStMeshId m_goal;
    unsigned char pad_54[0xC];
};

// A* searches over the navigation mesh (no table, made on the stack)
class NvmshUtilSeach {
public:
    NvmshUtilSeach();
    bool seachAStar(NvmshAStarResult* result);
    bool calcAStar();

    NvmshAStarResult* m_result;
    // NvmshAcObjBase::findPosRoot sets them from its status bits 17 and 18; the constructor clears them (the names
    // are not the original's)
    bool m_option0;
    bool m_option1;
    unsigned char pad_A[0x126];  // the object is 0x130 bytes (findPosRoot's stack)
};

}  // namespace navi

#endif
