#ifndef CLASSES_ML_DRRESMDOSEAMWRKMPF_H
#define CLASSES_ML_DRRESMDOSEAMWRKMPF_H

#include "mtl/AllocHandle.h"

namespace grlib { class CGLibVtxInstans; }
namespace ml { class DrMdoMpfMan; }
namespace ml { class DrCalcViewWork; class DrMdoCtlSeamMpfMap; }
namespace ml { struct MdoWrkMatRes; class DrResMdoSeamMemObj; class DrMdoCtlMpfWork; class DrMdoCtlMpfAuto; class DrMdoCtlMpfInst; }

namespace ml {
// the head of an mpf model's seam data (the type name is the symbols'; the field names are not the original's)
struct MdsSeamMpfMapHead {
    // 0x0..0x10: offsets of its data blocks from the head; DrMdoCtlSeamRead::waitMpfMdlStream hands blocks 1, 3, 0
    // and 4 to DrMdoMat::initMpfMaterial
    unsigned int m_dataOfs[5];
};

// table 0x7100B7DBC0
class DrResMdoSeamWrkMpf {
public:
    // an entry (0x3C bytes) of the seam map head's mpf model table (DrMdoCtlSeam::MapHead::m_mpfMdlTblOfs); the names
    // are not the original's
    struct MapEntry {
        unsigned char pad_0[0x34];
        unsigned int m_ofs;   // 0x34: where the mpf model data starts (DrMdoCtlSeamRead::callMpfMdlStream)
        unsigned int m_size;  // 0x38
    };
    DrResMdoSeamWrkMpf();
    virtual ~DrResMdoSeamWrkMpf();  // slot 0
    void setupWork(MdoWrkMatRes* matRes, mtl::ALLOC_HANDLE handle, const MdsSeamMpfMapHead* head, DrMdoMpfMan* mpfMan);
    void setEtcMpfCache(int idx, DrResMdoSeamMemObj* mem);
    void setMpfPoliCache(int idx, DrResMdoSeamMemObj* mem);
    // returns the state bits DrMdoCtlSeamMpfMap::updateMpfMapRenderList ors into the control's flags (0: nothing
    // changed)
    unsigned int updateRenderList(DrCalcViewWork* view, grlib::CGLibVtxInstans* inst, DrMdoCtlSeamMpfMap* ctl);

    // 0x8: the next work of DrMdoCtlSeam::m_pMpfList (DrMdoCtlSeamAll::releaseSeamAll walks it; the name is not
    // the original's)
    DrResMdoSeamWrkMpf* m_pLink;
    DrResMdoSeamWrkMpf* m_pBackLink;  // 0x10: the previous work (the name is not the original's)
    // 0x18: the memory its stream reads into (DrMdoCtlSeamRead::callMpfMdlStream); cleared by the destructor (the
    // name is not the original's)
    DrResMdoSeamMemObj* m_memObj;
    unsigned char pad_20[0x8];
    const MapEntry* m_mapEntry;  // 0x28: set by DrMdoCtlSeamRead::callMpfMdlStream (the name is not the original's)
    unsigned char pad_30[0x1C];
    // 0x4C: zeroed by the constructor; its m_mapEntry's index (DrMdoCtlSeamRead::callMpfMdlStream; the name is not the
    // original's)
    unsigned short m_dataIdx;
    unsigned char pad_4E[0x6];
    unsigned short m_dispNum;   // 0x54: setupWork and the destructor clear it (the name is not the original's)
    unsigned char pad_56[0x6];
    // 0x5C: DrMdoCtlSeamRead::waitMpfEtcStream/waitMpfPoliStream set bit 0 when the stream ends without data (the
    // name is not the original's)
    unsigned int m_cacheFlags;
    // 0x60..0x6C: four counts DrMdoCtlSeamMpfMap::updateMpfMapRenderList adds to the control's m_mpfRenderNum
    // (the name is not the original's)
    int m_renderNum[4];
    // Field names below are not the original's.
    MdoWrkMatRes* m_matRes;      // 0x70: setupWork's matRes; the destructor frees it
    unsigned char* m_workBuf;    // 0x78: setupWork's work memory, holding the three objects below
    unsigned char pad_80[0x40];
    DrMdoCtlMpfWork* m_mpfWork;  // 0xC0: m_workBuf + 0x0
    DrMdoCtlMpfAuto* m_mpfAuto;  // 0xC8: m_workBuf + 0x48
    DrMdoCtlMpfInst* m_mpfInst;  // 0xD0: m_workBuf + 0x1B8
    unsigned char pad_D8[0x8];   // 0xD8: zeroed by the constructor
    unsigned char pad_E0[0x8];
    unsigned int m_readSize;     // 0xE8: zeroed by the constructor; m_mapEntry's size (the name is not the original's)
};
}  // namespace ml

#endif
