#ifndef CLASSES_ML_DRMDOCTLPOS_H
#define CLASSES_ML_DRMDOCTLPOS_H

#include "classes/ml/DrMdlObj.h"
#include "ml/DrResMdoInstAnmObj.h"
#include "ml/DrResMdoPos.h"

namespace ml { class DrPixlShadowCacheObj; }
namespace ml { class DrResMdoInstMdlInfo; }
namespace ml { class DrCalcCpPlaneObj; }
namespace ml { class DrCalcViewWork; }
namespace ml { class DrPixlShadowObj; }
namespace ml { struct MdoArgInst; }
namespace ml { class DrResMdoSortPos; }

namespace ml {
// one 0x20-byte node of a position model's range tree (type name from nomTreeShadowRenderMdl's symbol; the field
// names are not the original's)
struct MdsPosRangeTreeData {
    float m_center[3];          // 0x0
    float m_radius;             // 0xC: chankShadowRenderMdl's clip test radius
    // 0x10: chankRenderMdl/nomTreeShadowRenderMdl skip the node while the squared distance from the view position is
    // greater
    float m_distSq;
    unsigned int m_childOfs;    // 0x14: offset of the child node index table (u16) from the position data
    unsigned int m_mdlOfs;      // 0x18: offset of the model index table (u32) from the position data
    unsigned short m_childNum;  // 0x1C
    unsigned short m_mdlNum;    // 0x1E

    // the clip tests take the centre as a vector
    const mm::Vec3& center() const { return reinterpret_cast<const mm::Vec3&>(m_center); }
    // the child node indices, m_childOfs bytes from the position data
    const unsigned short* childTbl(const void* top) const {
        return reinterpret_cast<const unsigned short*>(static_cast<const unsigned char*>(top) + m_childOfs);
    }
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
    void createMdlList();
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
    bool chankRenderMdl(const MdsPosRangeTreeData* tree, MdoArgInst& arg);
    bool clipRenderMdl(const MdsPosRangeTreeData* tree, MdoArgInst& arg);
    void chankShadowRenderMdl(const MdsPosRangeTreeData* tree, DrPixlShadowCacheObj& cache);
    void clipShadowRenderMdl(const MdsPosRangeTreeData* tree, DrPixlShadowCacheObj& cache);
    void nomTreeShadowRenderMdl(const MdsPosRangeTreeData* tree, DrPixlShadowObj* shadow);
    void nomTreeListShadowRenderMdl(const MdsPosRangeTreeData* tree, DrPixlShadowObj* shadow);

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
    unsigned char pad_1D0[0x8];
    int m_posNum;  // 0x1D8: releasePos destroys this many of m_pPosList and clears it
    unsigned char pad_1DC[0x4];
    DrResMdoPos* m_pPosList;  // 0x1E0
    DrResMdoInstAnmObj m_instAnm;  // 0x1E8: releasePos releases it; ScnObjAccSeamPos reads it (m_mdlType 1)
    unsigned char pad_218[0x8];
    // 0x220-0x238: work buffers releasePos deallocates (the names are not the original's)
    void* m_pWorkA;
    void** m_ppBuffList;  // 0x228: m_buffNum buffers
    void* m_pWorkB;       // 0x230
    int m_buffNum;        // 0x238
    unsigned char pad_23C[0x10];
    int pad_24C;  // resourceInit clears it
    DrResMdoPosAddList* m_pAddList;  // 0x250: releasePos releases and clears it
    // 0x258: setDeleteCall calls its releaseCall (the name is not the original's)
    DrResMdoInstMdlInfo* m_instMdlInfo;
    unsigned char pad_260[0x8];
    DrResMdoSortPos* m_pSortPos;  // 0x268: releasePos destroys it in place
    unsigned char pad_270[0xD8];
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
    // 0x37C: shadowCacheRender sets it from DrPixlShadowCacheMan::SHADOW_CHECK_RANGE_TBL (the name is not the
    // original's)
    float m_shadowRange;
};
}  // namespace ml

#endif
