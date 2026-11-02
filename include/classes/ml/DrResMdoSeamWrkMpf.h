#ifndef CLASSES_ML_DRRESMDOSEAMWRKMPF_H
#define CLASSES_ML_DRRESMDOSEAMWRKMPF_H

namespace grlib { class CGLibVtxInstans; }
namespace ml { class DrCalcViewWork; class DrMdoCtlSeamMpfMap; }
namespace ml { struct MdoWrkMatRes; class DrResMdoSeamMemObj; class DrMdoCtlMpfWork; class DrMdoCtlMpfAuto; class DrMdoCtlMpfInst; }

namespace ml {
// table 0x7100B7DBC0
class DrResMdoSeamWrkMpf {
public:
    DrResMdoSeamWrkMpf();
    virtual ~DrResMdoSeamWrkMpf();  // slot 0
    void setEtcMpfCache(int idx, DrResMdoSeamMemObj* mem);
    void setMpfPoliCache(int idx, DrResMdoSeamMemObj* mem);
    // returns the state bits DrMdoCtlSeamMpfMap::updateMpfMapRenderList ors into the control's flags (0: nothing
    // changed)
    unsigned int updateRenderList(DrCalcViewWork* view, grlib::CGLibVtxInstans* inst, DrMdoCtlSeamMpfMap* ctl);

    // 0x8: the next work of DrMdoCtlSeam::m_pMpfList (DrMdoCtlSeamAll::releaseSeamAll walks it; the name is not
    // the original's)
    DrResMdoSeamWrkMpf* m_pLink;
    unsigned char pad_10[0x8];
    unsigned long m_readState;  // 0x18: cleared by the destructor (the name is not the original's)
    unsigned char pad_20[0x2C];
    unsigned short pad_4C;      // 0x4C: zeroed by the constructor
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
    unsigned int pad_E8;         // 0xE8: zeroed by the constructor
};
}  // namespace ml

#endif
