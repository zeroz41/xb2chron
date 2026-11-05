#ifndef CLASSES_ML_DRMDOCTLMPF_H
#define CLASSES_ML_DRMDOCTLMPF_H

#include "classes/ml/DrMdlObj.h"

namespace ml { class DrMdoCtlMpfWork; class DrMdoCtlMpfAuto; class DrMdoCtlMpfInst; class DrResMdoSeamWrkPosMpf; }
namespace ml { class DrResMdoSortMpf; struct MdsMpfObjData; }

namespace ml {
// table 0x7100B7B7B0
class DrMdoCtlMpf : public ::ml::DrMdlObj {
public:
    // the head of the data DrMdlMan::createMdl hands the constructor (the type and field names are not the
    // original's): blocks 1, 3, 0 and 5 go to DrMdoMat::initMpfMaterial (5 may be 0: none), m_mpfOfs to setupMpf
    struct DataHeader {
        unsigned char pad_0[0x8];
        unsigned int m_dataOfs[6];  // 0x8..0x1C
        unsigned char pad_20[0x8];
        unsigned int m_mpfOfs;  // 0x28
    };
    // one entry of an object's render list (m_pRenderEntry): a part of its top header and the entry after it, 0 at
    // the end (the type and field names are not the original's)
    struct RenderEntry {
        unsigned short m_infoIdx;  // 0x0
        unsigned short m_next;  // 0x2: 1-based index into m_pRenderEntry
    };

    DrMdoCtlMpf(const void* data, const char* name, DrMan* drMan, int viewNum);  // DrMdlMan::createMdl news it
    virtual ~DrMdoCtlMpf();  // slot 0
    virtual void update();  // slot 2
    virtual void resourceInit();  // slot 5
    void setupMpf(const unsigned char* data);
    void releaseMpf();
    void calcMpfRenderList();
    bool calcMpfMatSetup();
    void defMpfrender();
    void defMpfZPreRender();
    void callZPrepassRender();
    void callRenderMpf();

    // Field names below are not the original's.
    // 0x190: 8 per object (one per render pass), the first m_pRenderEntry of that object's list or null
    RenderEntry** m_pRenderList;
    RenderEntry* m_pRenderEntry;  // 0x198: MdoMdlData::m_infoTotal entries
    int pad_1A0;  // 0x1A0: calcMpfRenderList clears it
    int m_objNum;  // 0x1A4
    const MdsMpfObjData* m_pObjData;  // 0x1A8
    unsigned char* m_pWorkBuf;  // 0x1B0: setupMpf's work memory, holding the five objects below
    void* pad_1B8;  // 0x1B8: freed by releaseMpf
    unsigned int pad_1C0;
    DrMdoCtlMpfWork* m_pMpfWork;  // 0x1C8: m_pWorkBuf + 0x0
    DrMdoCtlMpfAuto* m_pMpfAuto;  // 0x1D0: m_pWorkBuf + 0x48
    DrMdoCtlMpfInst* m_pMpfInst;  // 0x1D8: m_pWorkBuf + 0x1B8
    DrResMdoSeamWrkPosMpf* m_pPosMpf;  // 0x1E0: m_pWorkBuf + 0x1D0
    DrResMdoSortMpf* m_pSortMpf;  // 0x1E8: after the render list work
    unsigned char pad_1F0[0x10];  // sizeof 0x200 (DrMdlMan::createMdl news that much)
};
}  // namespace ml

#endif
