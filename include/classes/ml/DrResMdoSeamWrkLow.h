#ifndef CLASSES_ML_DRRESMDOSEAMWRKLOW_H
#define CLASSES_ML_DRRESMDOSEAMWRKLOW_H

#include "ml/DrResMdoSeamMemMan.h"

namespace grlib { class CGLibVtxInstans; }
namespace grlib { class CGLibTriUniformArray; }
namespace mtl { class ALLOC_HANDLE; }
namespace ml { struct MdoWrkMatRes; class DrResMdoSeamMemObj; struct MdsSeamLowData; class DrResMdoAlpTbl; }

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
// The field names are not the original's. Its list links (m_prev at 0x08, m_next at 0x10) come from the Node base:
// the constructor zeroes them before its other fields, as the other seam works' do.
class DrResMdoSeamWrkLow : public DrResChankList<DrResMdoSeamWrkLow>::Node {
public:
    // a render list entry (0xC bytes; DrMdoCtlSeamLowMap::createLowZPrePassDisplayList); names are not the original's
    struct RenderEntry {
        unsigned int m_infoOfs;   // 0x0: the MdsMdlInfoHeader, from MdoWrkMatRes::m_pMdlInfo
        unsigned short m_next;    // 0x4: the next entry + 1 in m_renderEntries, 0 at the list's end
        unsigned short pad_6;     // zeroed by stockRenderListLowMap
        unsigned short m_alpIdx;  // 0x8: partsZPrePassRender's alpha table entry
        // 0xA: bit 1 sets DrMdoSetup::m_stateFlags bit 29 for the part's pre-pass render
        unsigned short m_flags;
    };
    DrResMdoSeamWrkLow();
    virtual ~DrResMdoSeamWrkLow();  // slot 0
    void release();
    // adds an entry to list (base + pass): to the pre-pass lists when zPrePass (the parameter names are not the
    // original's)
    void stockRenderListLowMap(int base, unsigned int pass, unsigned int infoOfs, int alpIdx, bool zPrePass);
    void setupWork(MdoWrkMatRes* matRes, grlib::CGLibTriUniformArray* triArray, mtl::ALLOC_HANDLE handle,
                   const MdsSeamLowMapHead* head, const MdsSeamLowData* data, unsigned int num);

    unsigned char pad_18[0x10];
    // 0x28: the low map's material, deallocated by release; DrMdoCtlSeamLowMap::releaseFreeSeamLow releases it
    // with DrMdoMat::releaseBaseMapSeamMat first (the name is not the original's)
    MdoWrkMatRes* m_matRes;
    // 0x30: the memory its stream reads into (callLowMdlStream); zeroed by the constructor and release (the name is
    // not the original's)
    DrResMdoSeamMemObj* m_memObj;
    RenderEntry* m_renderEntries;         // 0x38: RenderEntry::m_next - 1 indexes it
    // 0x40: its m_inst is released and destroyed by release; createLowZPrePassDisplayList passes it to
    // partsZPrePassRender as the DrResMdoAlpTbl* (symbol)
    DrResMdoAlpTbl* m_instans;
    // 0x48..0x50: m_renderList, m_renderLast and m_renderNum of the lists stockRenderListLowMap fills when its last
    // argument is false (the names are not the original's)
    RenderEntry** m_drawList;
    RenderEntry** m_drawLast;
    RenderEntry** m_renderList;           // 0x58: by pass, the first entry
    RenderEntry** m_renderLast;           // 0x60: by list, its last entry (the name is not the original's)
    int* m_drawNum;                       // 0x68 (the name is not the original's)
    unsigned char pad_70[0x8];
    int* m_renderNum;                     // 0x78: [0] the pre-pass lists in m_renderList
    unsigned char pad_80[0x8];
    void* m_buf2;                         // 0x88: deallocated by release
    unsigned char pad_90[0xC];
    // 0x9C: zeroed by the constructor and release; createLowZPrePassDisplayList skips the work without bit 2
    unsigned int m_cacheFlags;
    int m_dataIdx;                        // 0xA0: its MapHead::m_lowMdlTblOfs entry (callLowMdlStream); zeroed by the constructor
    int m_renderCnt;                      // 0xA4: the entries of m_renderEntries in use (the name is not the original's)
    int pad_A8;
    int pad_AC;
    int m_readSize;                       // 0xB0: releaseFreeSeamLow takes it off DrMdoCtlSeam::m_lowMemSize
    int pad_B4;
};
}  // namespace ml

#endif
