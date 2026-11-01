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
namespace ml { class DrResChkList; }
namespace ml { class DrResMdoLodObj; }
namespace ml { class DrResEtcPamObj; }
namespace ml { class DrResMdoMorpObj; }
namespace ml { class DrResMdoSortNomFastApha; }
namespace ml { class DrResMdoSortNomLastApha; }
namespace ml { class DrResMdoSortNomCldBackApha; }
namespace ml { struct MdsMdlTopHeader; }

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
    void nomRender(const MdsMdlTopHeader*, DrResChkList*);
    void shwRender(const MdsMdlTopHeader*, DrResChkList*);
    void zPrePassRender();
    void thicknessRender(bool);
    void shadowMapDirRender(int);

    // What m_alphaSort points to: setupWorkMdl places it in the work buffer (0x30 bytes) and fills each sort object
    // and its per-MdoWrkMatRes::m_mdlTopNum check-list table when the model has that alpha pass. The type and field
    // names are not the original's.
    struct AlphaSortWork {
        DrResMdoSortNomFastApha* m_fast;  // 0x0
        DrResMdoSortNomLastApha* m_last;  // 0x8
        DrResMdoSortNomCldBackApha* m_cldBack;  // 0x10
        DrResChkList** m_fastChk;  // 0x18, fastAlphaCallRender's
        DrResChkList** m_lastChk;  // 0x20, lastAlphaCallRender's
        DrResChkList** m_cldBackChk;  // 0x28, cldBackAlphaCallRender's
    };

    // the ScnObjAcc* accessors read these when DrMdoMat::m_mdlType is 0 (the names are not the original's)
    unsigned char pad_18C[0x4];  // DrMdoNode ends at 0x18C
    // 0x190: per MdoWrkMatRes::m_mdlTopNum top header, one check list per pass: [0..5] by m_renderPass
    // (nomCallRender), [6] directional shadow, [7] thickness (the name is not the original's)
    DrResChkList* (*m_passChk)[8];
    // 0x198: the check-list nodes; a node's m_next is 1 + the index of the next one, 0 ends the list (the name
    // is not the original's)
    DrResChkList* m_chkPool;
    unsigned char pad_1A0[0x18];
    AlphaSortWork* m_alphaSort;  // 0x1B8 (the name is not the original's)
    unsigned char pad_1C0[0x8];
    DrResMdoMorpObj* m_morpObj;  // 0x1C8, callNomSetupRender updates it (the name is not the original's)
    unsigned char pad_1D0[0x8];
    DrResMdoVtxMeshObj* m_vtxMesh;  // 0x1D8, ScnObjAccMdlParticle's
    // 0x1E0: setDisp and setDeleteCall pass the display state on to it (the name is not the original's)
    DrResMdoLight* m_light;
    DrResMdoMeshObj* m_mesh;  // 0x1E8, ScnObjAccResSubMesh's
    // 0x1F0: setupWorkMdl creates it in the work buffer; the alpha passes hand its m_dispBits to createWeightVtx
    // (the name is not the original's)
    DrResMdoLodObj* m_lodObj;
    unsigned char pad_1F8[0x8];
    DrResEtcPamObj* m_etcParams;  // 0x200, ScnObjAccEtcParams's
    unsigned char pad_208[0x8];
    // 0x210: setDeleteCall stops its display (the name is not the original's)
    cloud::CloudMdlDataObj* m_cldMdlData;
    unsigned char pad_218[0x18];
    // 0x230, callShadowCacheUpdate clears the bits it is given (the name is not the original's)
    unsigned long m_shadowCacheBits;
};
}  // namespace ml

#endif
