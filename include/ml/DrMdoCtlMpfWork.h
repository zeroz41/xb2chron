#ifndef ML_DRMDOCTLMPFWORK_H
#define ML_DRMDOCTLMPFWORK_H

namespace ml { class DrMdoMpfMan; }
namespace ml { struct MdsMpfObjData; }
namespace ml { struct MdsMpfPosData; }
namespace ml { struct _MPFWorkAutoInf; }
namespace ml { class DrCalcViewWork; }
namespace grlib { class CGLibVtxInstans; }

namespace ml {
class DrMdoCtlMpfWork;

// A chunk of an object's render list: m_num entries, then the setter that adds the next one (fast set for the
// first, count set while the chunk has room, change set chains a new chunk). Field names are not the original's.
struct _wkMpfObjBuff {
    int m_num;
    union {
        const MdsMpfPosData** m_pPosList;
        const _MPFWorkAutoInf** m_pAutoList;
    };
    _wkMpfObjBuff* m_pNext;
    union {
        void (DrMdoCtlMpfWork::*m_pPosSet)(_wkMpfObjBuff*, const MdsMpfPosData*, int);
        void (DrMdoCtlMpfWork::*m_pAutoSet)(_wkMpfObjBuff*, const _MPFWorkAutoInf*, int);
    };
};

// Same with a per-entry alpha byte (16 entries per chunk).
struct _wkMpfAlphaObjBuff {
    int m_num;
    union {
        const MdsMpfPosData** m_pPosList;
        const _MPFWorkAutoInf** m_pAutoList;
    };
    unsigned char* m_pAlpha;
    _wkMpfAlphaObjBuff* m_pNext;
    union {
        void (DrMdoCtlMpfWork::*m_pPosSet)(_wkMpfAlphaObjBuff*, const MdsMpfPosData*, int, float);
        void (DrMdoCtlMpfWork::*m_pAutoSet)(_wkMpfAlphaObjBuff*, const _MPFWorkAutoInf*, int);
    };
};

// The entry storage a chunk's list points into, allocated with the chunk (type and field names are not the
// original's; the auto alpha lists stop before m_alpha).
struct _wkMpfObjList {
    union {
        const MdsMpfPosData* m_pos[64];
        const _MPFWorkAutoInf* m_auto[64];
    };
};

struct _wkMpfAlphaObjList {
    union {
        const MdsMpfPosData* m_pos[16];
        const _MPFWorkAutoInf* m_auto[16];
    };
    unsigned char m_alpha[16];
};

struct _wkMpfObjChunk {
    _wkMpfObjBuff m_head;
    _wkMpfObjList m_list;
};

struct _wkMpfAlphaObjChunk {
    _wkMpfAlphaObjBuff m_head;
    _wkMpfAlphaObjList m_list;
};

// One MPF object's list state, 0x40 bytes: the createAuto*/createPos*RenderList symbols name the type (their first
// parameter; createAutoList/createPosList pass &m_pObjSelect[idx]). The field names are not the original's.
struct _wkMpfObjSelect {
    unsigned char pad_0[0x10];
    // 0x10: 16 counters DrMdoCtlMpfAuto::CreateDisplayList counts listed auto points into, by a hash of the point
    unsigned short* m_pHashCount;
    unsigned char pad_18[0x8];
    unsigned short m_objChk;  // 0x20, returned by getObjChk; a failed allocation takes one off
    // 0x22, bit 0: createAutoList/createPosList build the model render list, else the billboard one
    unsigned char m_selFlags;
    unsigned char pad_23[0xD];
    _wkMpfObjBuff* m_pLastBuff;  // 0x30
    _wkMpfAlphaObjBuff* m_pLastAlphaBuff;  // 0x38
};

// One MPF object's data, 0x18 bytes (DrMdoCtlMpfWork::m_pObjData is an array of them). Only the field
// createAutoList/createPosList read is known; the field names are not the original's.
struct MdsMpfObjData {
    unsigned short pad_0;
    // 0x2: in hundredths; createAutoList/createPosList hand the render list builders m_range * 0.01f
    unsigned short m_range;
    unsigned char pad_4[0x8];
    // 0xC: DrMdoCtlMpf::calcMpfRenderList hands it to DrMdoCtlMpfInst::calcMpfObjTree (the name is not the original's)
    float m_treeParam;
    unsigned char pad_10[0x8];
};

// Placed at the start of DrResMdoSeamWrkMpf's work memory (0x48 bytes, no vtable).
class DrMdoCtlMpfWork {
public:
    DrMdoCtlMpfWork();

    static int calcRenderListWork(int objNum, const MdsMpfObjData* objData);
    void changeMemWork(const MdsMpfObjData* objData);
    int getObjChk(int idx);
    // returns the bytes of buf it used (DrMdoCtlMpf::setupMpf)
    int setupRenderListWork(unsigned char* buf, int objNum, const MdsMpfObjData* objData, DrMdoMpfMan* mpfMan);
    void beginList();

    void auto_fastSet(_wkMpfObjBuff* buff, const _MPFWorkAutoInf* inf, int idx);
    void auto_alpha_fastSet(_wkMpfAlphaObjBuff* buff, const _MPFWorkAutoInf* inf, int idx);
    void mpf_fastSet(_wkMpfObjBuff* buff, const MdsMpfPosData* pos, int idx);
    void mpf_alpha_fastSet(_wkMpfAlphaObjBuff* buff, const MdsMpfPosData* pos, int idx, float alpha);
    void mpf_countSet(_wkMpfObjBuff* buff, const MdsMpfPosData* pos, int idx);
    void mpf_changeSet(_wkMpfObjBuff* buff, const MdsMpfPosData* pos, int idx);
    void auto_countSet(_wkMpfObjBuff* buff, const _MPFWorkAutoInf* inf, int idx);
    void auto_changeSet(_wkMpfObjBuff* buff, const _MPFWorkAutoInf* inf, int idx);
    void mpf_alpha_countSet(_wkMpfAlphaObjBuff* buff, const MdsMpfPosData* pos, int idx, float alpha);
    void mpf_alpha_changeSet(_wkMpfAlphaObjBuff* buff, const MdsMpfPosData* pos, int idx, float alpha);
    void auto_alpha_countSet(_wkMpfAlphaObjBuff* buff, const _MPFWorkAutoInf* inf, int idx);
    void auto_alpha_changeSet(_wkMpfAlphaObjBuff* buff, const _MPFWorkAutoInf* inf, int idx);

    void createAutoList(int idx, DrCalcViewWork* view, grlib::CGLibVtxInstans* inst);
    void createPosList(int idx, grlib::CGLibVtxInstans* inst);
    void createPosMdlRenderList(_wkMpfObjSelect* sel, grlib::CGLibVtxInstans* inst, float range, _wkMpfObjBuff* buff,
                                _wkMpfAlphaObjBuff* alphaBuff);
    void createPosBillRenderList(_wkMpfObjSelect* sel, grlib::CGLibVtxInstans* inst, float range, _wkMpfObjBuff* buff,
                                 _wkMpfAlphaObjBuff* alphaBuff);
    void createAutoMdlRenderList(_wkMpfObjSelect* sel, DrCalcViewWork* view, grlib::CGLibVtxInstans* inst, float range,
                                 _wkMpfObjBuff* buff, _wkMpfAlphaObjBuff* alphaBuff);
    void createAutoBillRenderList(_wkMpfObjSelect* sel, DrCalcViewWork* view, grlib::CGLibVtxInstans* inst, float range,
                                  _wkMpfObjBuff* buff, _wkMpfAlphaObjBuff* alphaBuff);

    unsigned char pad_0[0x10];
    // 0x10/0x18, by object: the render list chunks createAutoList/createPosList hand the builders (the names are
    // not the original's)
    _wkMpfObjBuff** m_ppObjBuff;
    _wkMpfAlphaObjBuff** m_ppAlphaObjBuff;
    _wkMpfObjSelect* m_pObjWork;  // 0x20
    unsigned char pad_28[0x8];
    DrMdoMpfMan* m_pMpfMan;  // 0x30
    const MdsMpfObjData* m_pObjData;  // 0x38, set by changeMemWork
    int m_objNum;  // 0x40
    unsigned char pad_44[0x4];
};
}  // namespace ml

#endif
