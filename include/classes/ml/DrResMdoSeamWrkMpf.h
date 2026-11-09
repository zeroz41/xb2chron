#ifndef CLASSES_ML_DRRESMDOSEAMWRKMPF_H
#define CLASSES_ML_DRRESMDOSEAMWRKMPF_H

#include "mtl/AllocHandle.h"
#include "ml/DrResMdoSeamMemMan.h"

namespace grlib { class CGLibVtxInstans; }
namespace ml { class DrMdoMpfMan; }
namespace ml { class DrCalcViewWork; class DrMdoCtlSeamMpfMap; }
namespace ml { struct MdoWrkMatRes; class DrResMdoSeamMemObj; class DrResMdoSeamParmRead; class DrMdoCtlMpfWork; class DrMdoCtlMpfAuto; class DrMdoCtlMpfInst; }
namespace mm { class Vec3; }
namespace ml { struct MdsMpfObjData; struct MdsMpfAutoHead; struct _wkMpfAutoBuff; class DrResMdoSeamWrkPosMpf; }

namespace ml {
// the head of an mpf model's seam data (the type name is the symbols'; the field names are not the original's)
struct MdsSeamMpfMapHead {
    // 0x0..0x10: offsets of its data blocks from the head; DrMdoCtlSeamRead::waitMpfMdlStream hands blocks 1, 3, 0
    // and 4 to DrMdoMat::initMpfMaterial
    unsigned int m_dataOfs[5];
    unsigned char pad_14[0x8];
    unsigned int m_etcOfs;  // 0x1C: the EtcEntry table (setupWork)
    int m_etcNum;           // 0x20: its entries
    unsigned int m_flags;   // 0x24: bit 0 clear makes DrResMdoSeamWrkMpf::update read it while flag 0x100 is passed
};

// table 0x7100B7DBC0
// 0x8/0x10 are DrResChankList node links (a base, as in DrResMdoSeamWrkEnv: the constructor zeroes them before it
// stores the table). m_prev (0x8) is the next work of DrMdoCtlSeam::m_mpfPool's list (DrMdoCtlSeamAll::releaseSeamAll
// walks it), m_next (0x10) the previous one.
class DrResMdoSeamWrkMpf : public DrResChankList<DrResMdoSeamWrkMpf>::Node {
public:
    // an entry (0x3C bytes) of the seam map head's mpf model table (DrMdoCtlSeam::MapHead::m_mpfMdlTblOfs); the names
    // are not the original's
    struct MapEntry {
        float m_max[3];  // 0x0: x, y, z of the box update tests the read position against
        float m_min[3];  // 0xC
        unsigned char pad_18[0xC];
        // 0x24: when not 0, a bit of DrResMdoSeamParmRead::m_mpfBits that makes update read it
        unsigned short m_bitIdx;
        unsigned char pad_26[0xE];
        unsigned int m_ofs;   // 0x34: where the mpf model data starts (DrMdoCtlSeamRead::callMpfMdlStream)
        unsigned int m_size;  // 0x38
    };
    // the mpf model data at MdsSeamMpfMapHead::m_dataOfs[2] (setupWork, update); names are not the original's
    struct MpfData {
        int m_objNum;          // 0x0
        unsigned int m_objOfs; // 0x4: the MdsMpfObjData
        unsigned char pad_8[0x14];
        int m_autoOfs;         // 0x1C: the DrMdoCtlMpfAuto data, 0 when there is none
    };
    // an entry (0x1C bytes) of the head's etc table (MdsSeamMpfMapHead::m_etcOfs); names are not the original's
    struct EtcEntry {
        int m_id;  // 0x0: the id setEtcMpfCache looks up
        unsigned char pad_4[0x18];
    };
    // the head of the data an etc stream reads (DrResMdoSeamMemObj::m_pData); names are not the original's
    struct EtcData {
        unsigned char pad_0[0x4];
        unsigned int m_posOfs;   // 0x4
        unsigned char pad_8[0x4];
        unsigned int m_infoOfs;  // 0xC
        unsigned int m_posNum;   // 0x10
    };
    // the auto-placement polygon table at MdsMpfAutoHead::m_poliOfs; names are not the original's
    struct PoliHead {
        int m_numX;               // 0x0: grid cells along x
        int m_numZ;               // 0x4: along z
        unsigned int m_entryOfs;  // 0x8: PoliEntry table
        int m_entryNum;           // 0xC
        unsigned int m_cellOfs;   // 0x10: PoliCell grid, m_numX rows of m_numZ
        unsigned char pad_14[0x4];
        float m_org[2];           // 0x18: x, z
        float m_cellSize;         // 0x20
        float m_margin;           // 0x24: seachMpfPoliPos widens the search by twice it
    };
    // an entry (0x14 bytes) of PoliHead's table; names are not the original's
    struct PoliEntry {
        int m_id;        // 0x0: the id setMpfPoliCache looks up
        float m_max[2];  // 0x4: x, z
        float m_min[2];  // 0xC: x, z
    };
    // a grid cell of PoliHead: m_num ushort PoliEntry indices m_listOfs bytes from the head; names are not the
    // original's
    struct PoliCell {
        unsigned int m_listOfs;  // 0x0
        int m_num;               // 0x4
    };
    // the head of the data a polygon stream reads (DrResMdoSeamMemObj::m_pData): setupMpfPoliWork fills a
    // _wkMpfAutoBuff from it; names are not the original's
    struct PoliData {
        unsigned int m_poliOfs;     // 0x0
        unsigned int m_tblOfs[4];   // 0x4..0x10: _wkMpfAutoBuff::m_pTbl
        unsigned int m_treeOfs;     // 0x14: 0 when there is no tree
        unsigned int m_poliListOfs; // 0x18
        unsigned int m_cellOfs;     // 0x1C
        unsigned int m_gridOfs;     // 0x20
        float m_max[2];             // 0x24: x, z
        float m_min[2];             // 0x2C: x, z
        unsigned int m_instOfs;     // 0x34: 0 when there are no instance trees
        unsigned int m_posTreeOfs;  // 0x38
        unsigned int m_idxTblOfs;   // 0x3C
    };
    // the margin update adds around m_mapEntry's box (DrMdoCtlSeamMpfMap::readMpfMapCheck stores it)
    static float SEAM_MPFMAP_READ_CHECK;

    DrResMdoSeamWrkMpf();
    virtual ~DrResMdoSeamWrkMpf();  // slot 0
    void setupWork(MdoWrkMatRes* matRes, mtl::ALLOC_HANDLE handle, const MdsSeamMpfMapHead* head, DrMdoMpfMan* mpfMan);
    void setEtcMpfCache(int idx, DrResMdoSeamMemObj* mem);
    void setMpfPoliCache(int idx, DrResMdoSeamMemObj* mem);
    // returns the state bits DrMdoCtlSeamMpfMap::updateMpfMapRenderList ors into the control's flags (0: nothing
    // changed)
    unsigned int updateRenderList(DrCalcViewWork* view, grlib::CGLibVtxInstans* inst, DrMdoCtlSeamMpfMap* ctl);
    void releaseCache(DrMdoCtlSeamMpfMap* ctl);
    // returns true when the work wants to be read (the caller is DrMdoCtlSeamMpfMap::readMpfMapCheck)
    bool update(const DrResMdoSeamParmRead* parm, bool force, unsigned int flags);
    void setupMpfPoliWork(int idx);
    void seachMpfPoli(DrResMdoSeamParmRead* parm, DrMdoCtlSeamMpfMap* ctl);
    // true when it stocked a polygon cache to read for pos
    bool seachMpfPoliPos(const MdsMpfAutoHead* head, const mm::Vec3& pos, DrResMdoSeamParmRead* parm);

    // 0x18: the memory its stream reads into (DrMdoCtlSeamRead::callMpfMdlStream); cleared by the destructor (the
    // name is not the original's)
    DrResMdoSeamMemObj* m_memObj;
    DrMdoMpfMan* m_mpfMan;       // 0x20: setupWork's mpfMan (the name is not the original's)
    const MapEntry* m_mapEntry;  // 0x28: set by DrMdoCtlSeamRead::callMpfMdlStream (the name is not the original's)
    // Field names below up to m_dataIdx are not the original's.
    const MdsSeamMpfMapHead* m_head;  // 0x30: setupWork's head
    const MdsMpfObjData* m_objData;   // 0x38
    const EtcEntry* m_etcEntry;       // 0x40: m_etcNum entries
    unsigned char pad_48[0x4];
    // 0x4C: zeroed by the constructor; its m_mapEntry's index (DrMdoCtlSeamRead::callMpfMdlStream; the name is not the
    // original's)
    unsigned short m_dataIdx;
    // 0x4E: DrMdoCtlSeamMpfMap::createMpfZPrePassDisplayList skips the work while 0 (the name is not the original's)
    unsigned short m_dispOn;
    short m_etcNum;   // 0x50: head's m_etcNum (the name is not the original's)
    short m_objNum;   // 0x52 (the name is not the original's)
    // 0x54: etc works in m_etcWorkTbl (setEtcMpfCache); setupWork and the destructor clear it (the name is not the
    // original's)
    short m_dispNum;
    short m_readCnt;  // 0x56: update counts it (the name is not the original's)
    int m_poliNum;    // 0x58: polygon caches set (setMpfPoliCache; the name is not the original's)
    // 0x5C: DrMdoCtlSeamRead::waitMpfEtcStream/waitMpfPoliStream set bit 0 when the stream ends without data (the
    // name is not the original's)
    unsigned int m_cacheFlags;
    // 0x60..0x6C: four counts DrMdoCtlSeamMpfMap::updateMpfMapRenderList adds to the control's m_mpfRenderNum
    // (the name is not the original's)
    int m_renderNum[4];
    // Field names below are not the original's.
    MdoWrkMatRes* m_matRes;      // 0x70: setupWork's matRes; the destructor frees it
    unsigned char* m_workBuf;    // 0x78: setupWork's work memory, holding the three objects below
    unsigned int* m_etcBits;   // 0x80: one bit per etc entry with a cache
    unsigned int* m_poliBits;  // 0x88: one bit per polygon entry with a cache
    unsigned int* m_poliHitBits;  // 0x90: one bit per polygon entry seachMpfPoli finds near a read position
    unsigned short* m_poliIdx;    // 0x98: per cache, its polygon entry
    int m_poliHitBitsSize;        // 0xA0: bytes of m_poliHitBits (and of m_poliBits)
    int m_etcBitsSize;            // 0xA4: bytes of m_etcBits
    _wkMpfAutoBuff* m_buffWork;   // 0xA8: the placement buffers m_buffTbl points to
    _wkMpfAutoBuff** m_buffTbl;          // 0xB0: per cache, its placement buffer
    DrResMdoSeamMemObj** m_poliMemTbl;   // 0xB8: per cache, its memory
    DrMdoCtlMpfWork* m_mpfWork;  // 0xC0: m_workBuf + 0x0
    DrMdoCtlMpfAuto* m_mpfAuto;  // 0xC8: m_workBuf + 0x48
    DrMdoCtlMpfInst* m_mpfInst;  // 0xD0: m_workBuf + 0x1B8
    DrResMdoSeamWrkPosMpf* m_etcWork;      // 0xD8: m_etcNum works; zeroed by the constructor
    DrResMdoSeamWrkPosMpf** m_etcWorkTbl;  // 0xE0: the works set, m_dispNum entries
    unsigned int m_readSize;     // 0xE8: zeroed by the constructor; m_mapEntry's size (the name is not the original's)
};
}  // namespace ml

#endif
