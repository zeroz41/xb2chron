#ifndef CLASSES_ML_DRSHDLGTTILEBASEDDR_H
#define CLASSES_ML_DRSHDLGTTILEBASEDDR_H

#include "classes/ml/DrShdLgtDynamic.h"
#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibUniformArray.h"

namespace ml { class DrLightMan; }
namespace ml { class DrMan; }
namespace ml { class DrLightObjPnt; }
namespace ml { class DrLightObjSpt; }
namespace ml { class DrShdLgtMan; }

namespace ml {
// table 0x7100B7E568
class DrShdLgtTileBasedDr : public ::ml::DrShdLgtDynamic {
public:
    explicit DrShdLgtTileBasedDr(DrMan* drMan);
    virtual ~DrShdLgtTileBasedDr();  // slot 0
    virtual void stockBegin();  // slot 2
    virtual void stockEnd() {}  // slot 3
    virtual void update();  // slot 4
    virtual void addViewInfo(int);  // slot 6
    virtual void delViewInfo(int);  // slot 7
    virtual void stockPntList(ml::DrLightObjPnt*);  // slot 8
    virtual void stockSptList(ml::DrLightObjSpt*);  // slot 9
    virtual void render(ml::DrShdLgtMan*, ml::DrLightMan*);  // slot 10
    virtual void debugRender();  // slot 11

    // sets up every view's buffers (the constructor's body; ends with addViewInfo(0))
    void createWork();

    // one view's light buffers (0xD8 bytes; createWork sets up four, stockBegin indexes them by m_cateIdx). The
    // struct and field names are not the original's (named after DrShdLgtClustered::ViewWork)
    struct ViewWork {
        grlib::CGLibDblUniformBlock pntLight;  // 0x0, 0x30 bytes per light (0x100 lights for view 0, 0x10 others)
        grlib::CGLibDblUniformBlock sptLight;  // 0x38, 0x40 bytes per light
        grlib::CGLibDblUniformBlock param;     // 0x70, 0x280 bytes
        grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> blocks;  // 0xA8, 27 blocks of 0x10 bytes
        int pntNum;  // 0xD0, stockBegin clears it; stockPntList stops at the view's light count
        int sptNum;  // 0xD4
    };
    // one point light in a view's pntLight buffer (0x30 bytes, stockPntList fills it; the names are not the original's)
    struct PntLightEntry {
        float color[3];     // 0x0
        float param2;       // 0xC, DrLightObjPnt::m_lightParam2
        float pos[3];       // 0x10, in view space
        float size;         // 0x1C
        float invSize;      // 0x20
        float zero;         // 0x24
        unsigned int rate;  // 0x28, m_lightRate * 255 with m_bLightFlag in bit 31
        float param;        // 0x2C, DrLightObjPnt::m_lightParam
    };
    DrMan* m_pDrMan;  // 0x10, the constructor's renderer (the name is not the original's)
    ViewWork m_viewWork[4];  // 0x18
    // the names below are not the original's (as DrShdLgtClustered's)
    void* m_pWork = nullptr;      // 0x378, the destructor frees it
    int m_pntBuffRest = 0;        // 0x380, stockBegin: the view's pntLight size; stockPntList takes 0x30 per light
    int m_sptBuffRest = 0;        // 0x384
    PntLightEntry* m_pPntBuff = nullptr;  // 0x388, the next point light's entry in pntLight's buffer
    float* m_pSptBuff = nullptr;  // 0x390 (0x398, the size DrShdLgtHybrid's constructor allocates)
};
}  // namespace ml

#endif
