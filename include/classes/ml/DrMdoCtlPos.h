#ifndef CLASSES_ML_DRMDOCTLPOS_H
#define CLASSES_ML_DRMDOCTLPOS_H

#include "classes/ml/DrMdlObj.h"
#include "ml/DrResMdoInstAnmObj.h"

namespace ml { class DrPixlShadowCacheObj; }
namespace ml { class DrResMdoInstMdlInfo; }
namespace ml { class DrCalcCpPlaneObj; }
namespace ml { class DrCalcViewWork; }
namespace ml { class DrPixlShadowObj; }

namespace ml {
// one 0x20-byte node of a position model's range tree (type name from nomTreeShadowRenderMdl's symbol; the field
// names are not the original's)
struct MdsPosRangeTreeData {
    float m_center[3];          // 0x0
    float m_radius;             // 0xC: chankShadowRenderMdl's clip test radius
    unsigned char pad_10[0x4];
    unsigned int m_childOfs;    // 0x14: offset of the child node index table (u16) from the position data
    unsigned int m_mdlOfs;      // 0x18: offset of the model index table (u32) from the position data
    unsigned short m_childNum;  // 0x1C
    unsigned short m_mdlNum;    // 0x1E
};
}  // namespace ml

namespace ml {
// table 0x7100B7B8E0
class DrMdoCtlPos : public ::ml::DrMdlObj {
public:
    virtual ~DrMdoCtlPos();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void resourceInit();  // slot 5
    virtual void shadowRender();  // slot 6
    virtual bool shadowCacheRender(ml::DrPixlShadowCacheObj&);  // slot 7
    virtual void shadowCacheAddRender(int);  // slot 8
    virtual void callShadowCacheUpdate(unsigned long);  // slot 11
    virtual void occRender();  // slot 12
    virtual void setDeleteCall(int);  // slot 16
    void releasePos();
    void callZpreePassRenderPosAll();
    void callThicknessRenderFirstPosAll();
    void callThicknessRenderSecondPosAll();
    void callRenderPosAll();
    void callGBuffRenderPosAll();
    void callAlphaRenderPosAll();
    void callSpAlphaRenderPosAll();
    void callLightPrePassRenderPosAll();
    void callRefractionRenderPosAll();
    void callPosRender(unsigned int pass);
    void createZBuffRenderDisplayList();
    void createThicknessRenderDisplayListSub(bool first);
    void nomTreeShadowRenderMdl(const MdsPosRangeTreeData* tree, DrPixlShadowObj* shadow);

    // the head of the position data at 0x1A8 (the type and field names are not the original's)
    struct PosHead {
        unsigned char pad_0[0x2C];
        int m_treeNum;  // 0x2C: shadowRender walks this many nodes of m_pRangeTree
    };

    // the names are not the original's
    unsigned char pad_18C[0x1C];
    const PosHead* m_pPosHead;  // 0x1A8
    unsigned char pad_1B0[0x18];
    const MdsPosRangeTreeData* m_pRangeTree;  // 0x1C8
    unsigned char pad_1D0[0x18];
    DrResMdoInstAnmObj m_instAnm;  // 0x1E8: releasePos releases it; ScnObjAccSeamPos reads it (m_mdlType 1)
    unsigned char pad_218[0x40];
    // 0x258: setDeleteCall calls its releaseCall (the name is not the original's)
    DrResMdoInstMdlInfo* m_instMdlInfo;
    unsigned char pad_260[0xE8];
    DrCalcViewWork* m_pViewWork;  // 0x348: shadowRender takes the calc manager's view work (the name is not the original's)
    unsigned char pad_350[0x8];
    // 0x358: setDeleteCall releases and clears it (the name is not the original's)
    DrCalcCpPlaneObj* m_cpPlane;
    unsigned char pad_360[0x8];
    // 0x368: callShadowCacheUpdate clears the bits it is given; when any of them is in 0x370, it clears 0x370 and
    // 0x378 too (the names are not the original's)
    unsigned long m_shadowCacheBits;
    unsigned long m_shadowCacheReq;
    unsigned int m_shadowCacheCount;
};
}  // namespace ml

#endif
