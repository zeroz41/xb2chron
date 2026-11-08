#ifndef ML_DRMDOCTLMPFAUTO_H
#define ML_DRMDOCTLMPFAUTO_H

namespace mm { class Vec3; }
namespace ml { class DrMdoMpfMan; class DrCalcViewWork; class DrMdoCtlMpfWork; }

namespace ml {
// The auto-placement data header DrMdoCtlMpfAuto::m_pHeader points to (DrResMdoSeamWrkMpf::seachMpfPoliPos takes
// it as a const MdsMpfAutoHead*). Only the fields this unit's matched functions read are spelled out; field names
// are not the original's.
struct MdsMpfAutoHead {
    int m_num;  // 0x0: entries; calcWorkSize/setupAutoMpf size the per-entry tables by it
    unsigned int m_entryOfs;  // 0x4: DrMdoCtlMpfAuto::m_pEntry
    // 0x8..0x28: the one buffer's tables setupAutoMpf builds when m_poliOfs is 0 (same order as
    // DrResMdoSeamWrkMpf::PoliData)
    unsigned int m_buffPoliOfs;  // 0x8
    unsigned int m_buffTblOfs[4];  // 0xC..0x18
    unsigned int m_buffTreeOfs;  // 0x1C: 0 when there is no tree
    unsigned int m_buffPoliListOfs;  // 0x20
    unsigned int m_buffCellOfs;  // 0x24
    unsigned int m_buffGridOfs;  // 0x28
    float m_buffMax[2];  // 0x2C: x, z
    float m_buffMin[2];  // 0x34: x, z
    int m_instType;  // 0x3C: the instance tables are used only while it is -13
    unsigned int m_instOfs;  // 0x40: 0 when there are no instance trees
    unsigned int m_posTreeOfs;  // 0x44
    unsigned int m_idxTblOfs;  // 0x48
    unsigned int m_tblOfs[4];  // 0x4C..0x58: DrMdoCtlMpfAuto::m_pPoliData, m_pTbl
    // 0x5C: 0 makes setupAutoMpf build a one-buffer table in the work (0x78 more bytes); seachMpfPoli returns at
    // once while 0
    unsigned int m_poliOfs;
};

// One placement polygon (0x24 bytes: the buffer's polygon table steps by it); calcColiChk reads it.
struct MdsMpfAutoPoli {
    unsigned int m_vtx[3];  // 0x0: x, z pairs of the buffer's first table
    unsigned int m_col[3];  // 0xC: 4-byte colours (r, g, b, a) of the buffer's fourth table, by vertex
    unsigned int m_planeIdx;  // 0x18: 3 floats of the buffer's second table, the height over x, z
    unsigned int m_normalIdx;  // 0x1C: 3 floats of the buffer's third table
    unsigned int m_lodMask;  // 0x20: tested against DrMdoCtlMpfAuto::m_lodMask
};

// One grid node of a buffer's placement tree (0xC bytes: the buffer's tree table steps by it). Only the fields this
// unit's matched functions read are spelled out; field names are not the original's.
struct MdsMpfAutoTree {
    unsigned int m_cellOfs;  // 0x0: first cell of this grid in the buffer's cell table
    unsigned short m_scaleIdx;  // 0x4: x, z cells per unit, an entry of the buffer's grid table
    unsigned short m_orgIdx;  // 0x6: x, z origin, an entry of the buffer's grid table
    unsigned short m_lodMask;  // 0x8: tested against DrMdoCtlMpfAuto::m_lodMask
    unsigned char m_numX;  // 0xA: cells along x
    unsigned char m_numZ;  // 0xB: cells along z (a row of cells)
};

// One node of a buffer's instance position tree (0x20 bytes: the buffer's position tree table steps by it). Field
// names are not the original's.
struct MdsMpfAutoPosTree {
    float m_max[2];  // 0x0: x, z
    float m_min[2];  // 0x8: x, z
    unsigned int m_childIdx;  // 0x10: first child, an entry of the buffer's index table
    unsigned int m_instIdx;  // 0x14: first instance, an entry of the buffer's index table
    unsigned short m_childNum;  // 0x18
    unsigned short m_instNum;  // 0x1A
    unsigned int m_lodMask;  // 0x1C: tested against DrMdoCtlMpfAuto::m_lodMask
};

// One auto-placed work entry (0x58 bytes: DrMdoMpfMan::freeMemWork clears that much), the head of a block of the
// manager's work memory: m_num 0x20-byte points follow it from 0x58. A free block sits in DrMdoMpfMan's free list, a
// used one in its owner's chain, both through m_pNext/m_pPrev. Field names are not the original's.
struct _MPFWorkAutoInf {
    // One stored point (0x20 bytes) of the m_num after the head (the name is not the original's).
    struct Point {
        unsigned char pad_0[0x20];
    };

    unsigned short m_num;  // 0x0: points stored after the head
    unsigned short m_flags;  // 0x2: getMemWork sets 2 and the owner's draw bits
    // 0x4: x, y (height), z; x and z are DrMdoCtlMpfAuto::m_workParam4/m_workParamC, CreateDisplayList clip tests
    // the point
    float m_pos[3];
    unsigned int m_param10;  // 0x10: DrMdoCtlMpfAuto::m_workParam10
    short m_param14[2];  // 0x14: DrMdoCtlMpfAuto::m_workShort
    short m_param18;  // 0x18: DrMdoCtlMpfAuto::m_workParam18
    unsigned short m_capacity;  // 0x1A: points the block holds
    unsigned int m_size;  // 0x1C: bytes of the block, head included
    float m_scale;  // 0x20: 1 or 0 by the owner's bit 7
    unsigned char pad_24[0x4];
    _MPFWorkAutoInf* m_pNext;  // 0x28: next entry of the same chain (autoMpfRelease walks it)
    _MPFWorkAutoInf* m_pPrev;  // 0x30
    _MPFWorkAutoInf* m_pBlockNext;  // 0x38: the block after this one in memory
    _MPFWorkAutoInf* m_pBlockPrev;  // 0x40: the block before this one in memory
    unsigned char pad_48[0x10];
};

// One placement buffer (0x70 bytes: setupAutoMpf puts its one-buffer table right after one). setupAutoMpf fills
// the rectangle from the head's floats at 0x2C..0x38. Only the fields this unit's matched functions read are
// spelled out; field names are not the original's.
struct _wkMpfAutoBuff {
    // One placed instance (0xC0 bytes: the buffer's instance table steps by it); the name is not the original's.
    struct Inst {
        unsigned char pad_0[0xA0];
        float m_max[2];  // 0xA0: x, z
        float m_min[2];  // 0xA8: x, z
        unsigned char pad_B0[0x4];
        unsigned int m_lodMask;  // 0xB4: tested against DrMdoCtlMpfAuto::m_lodMask
        unsigned char pad_B8[0x8];
    };

    float m_max[2];  // 0x0: x, z; gridInstColiCalc skips the buffer when the position lies past it
    float m_min[2];  // 0x8: x, z
    const MdsMpfAutoPoli* m_pPoli;  // 0x10: polygons (0x24 bytes each) the cell lists name
    const unsigned char* m_pTbl[4];  // 0x18..0x30: four more tables (DrResMdoSeamWrkMpf::setupMpfPoliWork)
    const MdsMpfAutoTree* m_pTree;  // 0x38, null when the head has no tree
    // 0x40: polygon lists a negative cell names (bit 31 cleared): a count, then that many m_pPoli entries
    const unsigned int* m_pPoliList;
    // 0x48: grid cells: 0 empty, bit 31 set a polygon list (m_pPoliList entry), else a child m_pTree entry
    const unsigned int* m_pCell;
    const float (*m_pGrid)[2];  // 0x50: x, z pairs the trees' m_scaleIdx/m_orgIdx name
    const Inst* m_pInstData;  // 0x58, null when the head has no instance trees
    const MdsMpfAutoPosTree* m_pPosTree;  // 0x60
    const unsigned int* m_pIdxTbl;  // 0x68: child and instance entries the position trees name
};

// Placed at 0x48 of DrResMdoSeamWrkMpf's work memory, after DrMdoCtlMpfWork (0x170 bytes, no vtable: its
// constructor stores no table). Field names are not the original's.
class DrMdoCtlMpfAuto {
public:
    DrMdoCtlMpfAuto();
    ~DrMdoCtlMpfAuto();
    static int calcWorkSize(const unsigned char* data);
    void setupAutoMpf(const unsigned char* data, const unsigned char* autoData, unsigned char* work);
    void CreateDisplayList(DrCalcViewWork* view, DrMdoCtlMpfWork* work);
    void autoMpfCalc(bool, bool, DrCalcViewWork* view, DrMdoCtlMpfWork* work, DrMdoMpfMan* mpfMan);
    void changeMemAutoMpf(const unsigned char* data, const unsigned char* autoData);
    void setBuffTbl(_wkMpfAutoBuff** buffTbl, int buffNum);
    void autoMpfRelease();
    void resetPrePos();
    bool calcColiChk(const MdsMpfAutoPoli* poli);
    void gridTreeColiCalc(const MdsMpfAutoTree* tree);
    void StockPoint();
    void getMemWork(_MPFWorkAutoInf* inf);
    bool setHeMemWork(int idx);
    void gridInstColiCalc();
    void seachInstTree(const MdsMpfAutoPosTree* tree);
    bool gridColiInstPosRangeChk(const MdsMpfAutoPosTree* tree);
    // true when a buffer overlapping the x/z rectangle has a hit in its tree or its instance trees
    bool gridChkColiRange(float maxX, float minX, float maxZ, float minZ);
    bool gridColiRangeChk(const MdsMpfAutoTree* tree);

    // One entry of m_pEntry (0xC bytes; the name is not the original's).
    struct Entry {
        unsigned char pad_0[0x4];
        unsigned char m_objIdx;  // 0x4: the DrMdoCtlMpfWork object CreateDisplayList lists the entry's work under
        unsigned char pad_5[0x7];
    };

    const MdsMpfAutoHead* m_pHeader;  // 0x0, setupAutoMpf's head argument
    const Entry* m_pEntry;  // 0x8: m_pHeader->m_num entries
    const unsigned char* m_pTbl[3];  // 0x10..0x20: data + the head's offsets at 0x50..0x58
    const unsigned char* m_pPoliData;  // 0x28: setupAutoMpf sets it to data + the head's offset at 0x4C
    const unsigned int* m_pIdxTbl;  // 0x30: the instance trees' index table
    const unsigned char* m_pColTbl;  // 0x38: the buffer's fourth table (4-byte colours)
    unsigned char pad_40[0x10];
    _wkMpfAutoBuff* m_pBuff;  // 0x50: the one buffer setupAutoMpf builds at the start of the work
    _wkMpfAutoBuff* m_pCurBuff;  // 0x58: the buffer gridInstColiCalc is testing
    _wkMpfAutoBuff** m_pBuffTbl;  // 0x60
    int m_buffNum;  // 0x68
    unsigned int m_autoFlags;  // 0x6C: DrResMdoSeamWrkMpf::seachMpfPoli clears bit 6
    unsigned int m_lodMask;  // 0x70: autoMpfCalc stores 1 << a data byte
    int m_param74;  // 0x74: setupAutoMpf clears it
    unsigned char pad_78[0x4];
    int m_workIdx;  // 0x7C: the m_pWorkTbl chain getMemWork links new work into
    int m_workNum;  // 0x80: autoMpfCalc's loop bound
    int m_workNum2;  // 0x84: cleared with m_workNum by the constructor
    float m_rangeMin[2];  // 0x88: x, z of gridChkColiRange's rectangle
    float m_rangeMax[2];  // 0x90: x, z
    // 0x98..0xAC: copied into each work entry setHeMemWork fills
    int m_workShort[2];  // 0x98
    unsigned int m_workParam4;  // 0xA0
    unsigned int m_workParamC;  // 0xA4
    int m_workParam18;  // 0xA8
    unsigned int m_workParam10;  // 0xAC
    unsigned char pad_B0[0x10];
    mm::Vec3* m_pPrePos;  // 0xC0: m_pHeader->m_num positions, resetPrePos sets them to -100000
    unsigned char pad_C8[0x8];
    float m_pos[3];  // 0xD0: x, y, z; gridInstColiCalc tests x and z against each buffer's rectangle
    // The colour bytes a hit carries (the name is not the original's).
    struct Color {
        unsigned char r, g, b, a;
    };
    // One stored height (8 bytes): m_pHit holds up to 10 per position (the name is not the original's).
    struct Hit {
        float m_y;  // 0x0
        Color m_col;  // 0x4
    };
    Color m_col;  // 0xDC: stored with each hit
    float m_normal[3];  // 0xE0: calcColiChk sets it from the hit polygon's normal (x and z negated)
    unsigned char pad_EC[0x4];
    Hit* m_pHit;  // 0xF0: m_hitNum entries
    int m_hitNum;  // 0xF8: gridInstColiCalc clears it, the tree tests count up
    unsigned char pad_FC[0xC];
    unsigned char* m_pStockBuf[5];  // 0x108: 0x20-byte points stocked per height, setHeMemWork copies them out
    float m_stockHeight[5];  // 0x130
    int m_stockNum[5];  // 0x144: points in each m_pStockBuf, setHeMemWork clears it
    _MPFWorkAutoInf** m_pWorkTbl;  // 0x158: m_pHeader->m_num chains, autoMpfRelease frees them
    _MPFWorkAutoInf** m_pWorkLast;  // 0x160: per entry, cleared with m_pWorkTbl
    DrMdoMpfMan* m_pMpfMan;  // 0x168: owns the work autoMpfRelease frees
};
}  // namespace ml

#endif
