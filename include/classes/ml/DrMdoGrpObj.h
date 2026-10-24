#ifndef CLASSES_ML_DRMDOGRPOBJ_H
#define CLASSES_ML_DRMDOGRPOBJ_H

#include "classes/ml/DrMdlBase.h"

namespace ml { class DrPixlShadowCacheObj; }

namespace ml {
// table 0x7100B7AC78
class DrMdoGrpObj : public ::ml::DrMdlBase {
public:
    virtual ~DrMdoGrpObj();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void resourceInit() {}  // slot 5
    virtual void shadowRender();  // slot 6
    virtual bool shadowCacheRender(ml::DrPixlShadowCacheObj&);  // slot 7
    virtual void shadowCacheOnlyRender();  // slot 9
    virtual void callShadowCacheUpdate(unsigned long);  // slot 11
    virtual void occRender();  // slot 12
    void callNomSetupRender();
    void callZSortNomZpreePassRender();
    void callZSortThicknessRenderFirst();
    void callZSortThicknessRenderSecond();
    void callZSortNomRender();
    void callZSortGBuffRender();
    void callZSortLightPrePassRender();
    void callZSortNomAlphaRender();
    void callZSortNomSpAlphaRender();
    void callZSortNomRefractionRender();

    // the names below are not the original's
    // one list of objects (the constructor zeroes both words)
    struct MdlList {
        DrMdlBase* m_pTop;
        unsigned char pad_8[0x8];
    };
    unsigned char pad_28[0x8];
    MdlList** m_ppList;  // 0x30, the constructor points it after its MdlList entries in the same allocation
    unsigned char pad_38[0x34];
    int m_listNum;  // 0x6C, the count the render passes walk
};
}  // namespace ml

#endif
