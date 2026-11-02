#ifndef ML_DRMDOCTLMPFAUTO_H
#define ML_DRMDOCTLMPFAUTO_H

namespace mm { class Vec3; }
namespace ml { struct MdsMpfAutoTree; }
namespace ml { struct MdsMpfAutoPosTree; }
namespace ml { class DrMdoMpfMan; }

namespace ml {
// The auto-placement data header DrMdoCtlMpfAuto::m_pHeader points to (DrResMdoSeamWrkMpf::seachMpfPoliPos takes
// it as a const MdsMpfAutoHead*). Only the fields this unit's matched functions read are spelled out; field names
// are not the original's.
struct MdsMpfAutoHead {
    int m_num;  // 0x0: entries; calcWorkSize/setupAutoMpf size the per-entry tables by it
    unsigned char pad_4[0x58];
    // 0x5C: 0 makes setupAutoMpf build a one-buffer table in the work (0x78 more bytes); seachMpfPoli returns at
    // once while 0
    unsigned int m_poliOfs;
};

// One auto-placed work entry (0x58 bytes: DrMdoMpfMan::freeMemWork clears that much). Only the link this unit's
// matched functions follow is spelled out; the field name is not the original's.
struct _MPFWorkAutoInf {
    unsigned char pad_0[0x28];
    _MPFWorkAutoInf* m_pNext;  // 0x28: next entry of the same chain (autoMpfRelease walks it)
    unsigned char pad_30[0x28];
};

// One placement buffer (0x70 bytes: setupAutoMpf puts its one-buffer table right after one). setupAutoMpf fills
// the rectangle from the head's floats at 0x2C..0x38. Only the fields this unit's matched functions read are
// spelled out; field names are not the original's.
struct _wkMpfAutoBuff {
    float m_max[2];  // 0x0: x, z; gridInstColiCalc skips the buffer when the position lies past it
    float m_min[2];  // 0x8: x, z
    unsigned char pad_10[0x28];
    const MdsMpfAutoTree* m_pTree;  // 0x38, null when the head has no tree
    unsigned char pad_40[0x18];
    const unsigned char* m_pInstData;  // 0x58, null when the head has no instance trees
    const MdsMpfAutoPosTree* m_pPosTree;  // 0x60
    unsigned char pad_68[0x8];
};

// Placed at 0x48 of DrResMdoSeamWrkMpf's work memory, after DrMdoCtlMpfWork (0x170 bytes, no vtable: its
// constructor stores no table). Field names are not the original's.
class DrMdoCtlMpfAuto {
public:
    DrMdoCtlMpfAuto();
    ~DrMdoCtlMpfAuto();
    static int calcWorkSize(const unsigned char* data);
    void setBuffTbl(_wkMpfAutoBuff** buffTbl, int buffNum);
    void autoMpfRelease();
    void resetPrePos();
    void gridTreeColiCalc(const MdsMpfAutoTree* tree);
    void StockPoint();
    void gridInstColiCalc();
    void seachInstTree(const MdsMpfAutoPosTree* tree);
    bool gridColiInstPosRangeChk(const MdsMpfAutoPosTree* tree);
    // true when a buffer overlapping the x/z rectangle has a hit in its tree or its instance trees
    bool gridChkColiRange(float maxX, float minX, float maxZ, float minZ);
    bool gridColiRangeChk(const MdsMpfAutoTree* tree);

    const MdsMpfAutoHead* m_pHeader;  // 0x0, setupAutoMpf's head argument
    unsigned char pad_8[0x20];
    const unsigned char* m_pPoliData;  // 0x28: setupAutoMpf sets it to data + the head's offset at 0x4C
    unsigned char pad_30[0x28];
    _wkMpfAutoBuff* m_pCurBuff;  // 0x58: the buffer gridInstColiCalc is testing
    _wkMpfAutoBuff** m_pBuffTbl;  // 0x60
    int m_buffNum;  // 0x68
    unsigned int m_autoFlags;  // 0x6C: DrResMdoSeamWrkMpf::seachMpfPoli clears bit 6
    unsigned int m_lodMask;  // 0x70: autoMpfCalc stores 1 << a data byte
    unsigned char pad_74[0xC];
    int m_workNum;  // 0x80: autoMpfCalc's loop bound
    int m_workNum2;  // 0x84: cleared with m_workNum by the constructor
    float m_rangeMin[2];  // 0x88: x, z of gridChkColiRange's rectangle
    float m_rangeMax[2];  // 0x90: x, z
    unsigned char pad_98[0x28];
    mm::Vec3* m_pPrePos;  // 0xC0: m_pHeader->m_num positions, resetPrePos sets them to -100000
    unsigned char pad_C8[0x8];
    float m_pos[3];  // 0xD0: x, y, z; gridInstColiCalc tests x and z against each buffer's rectangle
    unsigned char pad_DC[0x1C];
    int m_hitNum;  // 0xF8: gridInstColiCalc clears it, the tree tests count up
    unsigned char pad_FC[0x5C];
    _MPFWorkAutoInf** m_pWorkTbl;  // 0x158: m_pHeader->m_num chains, autoMpfRelease frees them
    _MPFWorkAutoInf** m_pWorkLast;  // 0x160: per entry, cleared with m_pWorkTbl
    DrMdoMpfMan* m_pMpfMan;  // 0x168: owns the work autoMpfRelease frees
};
}  // namespace ml

#endif
