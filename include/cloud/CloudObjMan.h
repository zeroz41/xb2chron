#ifndef CLOUD_CLOUDOBJMAN_H
#define CLOUD_CLOUDOBJMAN_H



#include "cloud/CloudList.h"
#include "cloud/CloudMdlDataObj.h"
#include "classes/cloud/CloudObj.h"

namespace ml { class IDrDrawWorkInfo; }

namespace cloud {
class CloudObj;
class CloudObjReduction;
class CloudCalcParams;
class CloudObjFlow;
class CloudObjMdl;
class CloudObjPlane;

// CloudMan's object manager (0x70, no class table: CloudMan's destructor calls its destructor directly). Field
// names are not the original's.
class CloudObjMan {
public:
    CloudObjMan();
    ~CloudObjMan();
    void creataFastSetup();
    bool update(const ml::IDrDrawWorkInfo* info);
    bool isRender() const;
    void alphaRender(const ml::IDrDrawWorkInfo* info);
    CloudObjFlow* createFlow();
    CloudObjMdl* createMdl();
    CloudMdlDataObj* createMdlData(const void* data);
    void releaseMdlData(CloudMdlDataObj* obj);

    CloudList<CloudObj> m_objList;          // 0x0
    CloudList<CloudMdlDataObj> m_mdlList;   // 0x18
    CloudObjFlow* m_pFlow;                  // 0x30, createFlow's
    CloudCalcParams* m_pCalcParams;    // 0x38
    CloudObjReduction* m_pReduction;   // 0x40
    CloudObjMdl* m_pMdl;                    // 0x48, createMdl's
    CloudObjPlane* m_pPlane;                // 0x50, CloudObjReduction::counterRender counts its two DEF uniforms
    bool m_isEnable;                   // 0x58, true from the constructor; isRender needs it
    bool m_planeOn;                    // 0x59, CloudMan::planeOn
    bool m_planeSideOn;                // 0x5A, CloudMan::planeSideOn
    bool m_planeHide;                  // 0x5B, CloudObjPlane::alphaRender skips the plane while set
    bool m_skyOn;                      // 0x5C, CloudMan::skyOn
    bool m_skyHide;                    // 0x5D, CloudObjSky::alphaRender skips the sky while set
    bool m_skyHideFrame;               // 0x5E, the same, cleared by update every frame
    unsigned char pad_5F[0x2];
    bool m_mdlOn;                      // 0x61, CloudMan::mdlOn
    bool m_mdlHide;                    // 0x62, CloudObjMdl's renders skip while set
    unsigned char pad_63[0x3];
    bool m_isHole;                     // 0x66, CloudMan::isHole
    bool m_planeCountSkip;             // 0x67, CloudObjReduction::counterRender skips the plane's first uniform
    bool m_planeUniSkip;               // 0x68, with m_planeUniSkip2: CloudObjPlane skips its uniform update
    bool m_planeUniSkip2;              // 0x69, true from the constructor and from update
    unsigned char pad_6A[0x6];
};
}  // namespace cloud

#endif
