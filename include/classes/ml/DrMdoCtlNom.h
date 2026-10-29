#ifndef CLASSES_ML_DRMDOCTLNOM_H
#define CLASSES_ML_DRMDOCTLNOM_H

#include "classes/ml/DrMdlObj.h"

namespace ml { class DrMdlObj; }
namespace ml { class DrPixlShadowCacheObj; }
namespace ml { class DrResMdoMeshObj; }
namespace ml { class DrResMdoLight; }
namespace cloud { class CloudMdlDataObj; }
namespace ml { class DrResMdoVtxMeshObj; }
namespace mm { class Col3; }

namespace ml {
// table 0x7100B7B848
class DrMdoCtlNom : public ::ml::DrMdlObj {
public:
    virtual ~DrMdoCtlNom();  // slot 0
    virtual void update();  // slot 2
    virtual void dispOffUpdate();  // slot 3
    virtual void resourceInit();  // slot 5
    virtual void shadowRender();  // slot 6
    virtual bool shadowCacheRender(ml::DrPixlShadowCacheObj&);  // slot 7
    virtual void shadowCacheOnlyRender();  // slot 9
    virtual void callShadowCacheUpdate(unsigned long);  // slot 11
    virtual void occRender();  // slot 12
    virtual bool cloneMdlObj(ml::DrMdlObj*);  // slot 13
    virtual void setDisp(bool);  // slot 15
    virtual void setDeleteCall(int);  // slot 16
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
    void callLastAlphaNomRender();
    void callFastAlphaNomRender();
    void callCldBackAlphaNomRender();
    void createAfterImage(float, float, float, const mm::Col3&, float, float, float, const mm::Col3&, float, float,
                          float);
    void releaseAfterImage();
    void releaseNom();
    void nomCallRender(int pass);
    void lastAlphaCallRender();
    void fastAlphaCallRender();
    void cldBackAlphaCallRender();

    // the ScnObjAcc* accessors read these when DrMdoMat::m_mdlType is 0 (the names are not the original's)
    unsigned char pad_182[0x56];  // DrMdlObj ends at 0x182 (m_nodeMax)
    DrResMdoVtxMeshObj* m_vtxMesh;  // 0x1D8, ScnObjAccMdlParticle's
    // 0x1E0: setDisp and setDeleteCall pass the display state on to it (the name is not the original's)
    DrResMdoLight* m_light;
    DrResMdoMeshObj* m_mesh;  // 0x1E8, ScnObjAccResSubMesh's
    unsigned char pad_1F0[0x10];
    EtcParamsTable* m_etcParams;  // 0x200, ScnObjAccEtcParams's
    unsigned char pad_208[0x8];
    // 0x210: setDeleteCall stops its display (the name is not the original's)
    cloud::CloudMdlDataObj* m_cldMdlData;
    unsigned char pad_218[0x18];
    // 0x230, callShadowCacheUpdate clears the bits it is given (the name is not the original's)
    unsigned long m_shadowCacheBits;
};
}  // namespace ml

#endif
