#ifndef CLASSES_ML_DRRESMDOSEAMWRKLOW_H
#define CLASSES_ML_DRRESMDOSEAMWRKLOW_H

namespace grlib { class CGLibVtxInstans; }
namespace grlib { class CGLibTriUniformArray; }
namespace mtl { class ALLOC_HANDLE; }
namespace ml { struct MdoWrkMatRes; class DrResMdoSeamMemObj; struct MdsSeamLowData; }

namespace ml {
// The head of a seam low map's data (the name is from setupWork's symbol; the field names are not the original's,
// laid out like MdsSeamInstMapHead's).
struct MdsSeamLowMapHead {
    unsigned char pad_0[0x8];
    // 0x8..0x10: offsets of data blocks: [1] and [0] go to DrMdoMat::initBaseMapMaterial, [2] (0 when there is
    // none) is the MdsSeamInstMatBlock of the material resources (DrMdoCtlSeamLowMap::initLowMapParts)
    unsigned int m_dataOfs[3];
    unsigned char pad_14[0x4];
    // 0x18..0x20: initBaseMapMaterial's third, fifth and fourth data blocks
    unsigned int m_matOfs[3];
};

// table 0x7100B7DB98
// The field names are not the original's.
class DrResMdoSeamWrkLow {
public:
    DrResMdoSeamWrkLow();
    virtual ~DrResMdoSeamWrkLow();  // slot 0
    void release();
    void setupWork(MdoWrkMatRes* matRes, grlib::CGLibTriUniformArray* triArray, mtl::ALLOC_HANDLE handle,
                   const MdsSeamLowMapHead* head, const MdsSeamLowData* data, unsigned int num);

    DrResMdoSeamWrkLow* m_prev;           // 0x08: list links, zeroed by the constructor
    DrResMdoSeamWrkLow* m_next;           // 0x10
    unsigned char pad_18[0x10];
    // 0x28: the low map's material, deallocated by release; DrMdoCtlSeamLowMap::releaseFreeSeamLow releases it
    // with DrMdoMat::releaseBaseMapSeamMat first (the name is not the original's)
    MdoWrkMatRes* m_matRes;
    // 0x30: the memory its stream reads into (callLowMdlStream); zeroed by the constructor and release (the name is
    // not the original's)
    DrResMdoSeamMemObj* m_memObj;
    unsigned char pad_38[0x8];
    grlib::CGLibVtxInstans* m_instans;    // 0x40: released and destroyed by release
    unsigned char pad_48[0x40];
    void* m_buf2;                         // 0x88: deallocated by release
    unsigned char pad_90[0xC];
    int m_num;                            // 0x9C: zeroed by the constructor and release
    int m_dataIdx;                        // 0xA0: its MapHead::m_lowMdlTblOfs entry (callLowMdlStream); zeroed by the constructor
    int pad_A4;
    int pad_A8;
    int pad_AC;
    int m_readSize;                       // 0xB0: releaseFreeSeamLow takes it off DrMdoCtlSeam::m_lowMemSize
    int pad_B4;
};
}  // namespace ml

#endif
