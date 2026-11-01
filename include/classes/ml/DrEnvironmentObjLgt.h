#ifndef CLASSES_ML_DRENVIRONMENTOBJLGT_H
#define CLASSES_ML_DRENVIRONMENTOBJLGT_H

#include "classes/ml/DrEnvironmentObj.h"
#include <string.h>

namespace ml { class DrCalcViewWork; }
namespace ml { class DrEnvironmentLgtList; }
namespace ml { class DrLightObj; }
namespace ml { class DrShdLgtMan; }
namespace ml { struct LgtObjData; }

namespace ml {
// table 0x7100B7B270
class DrEnvironmentObjLgt : public ::ml::DrEnvironmentObj {
public:
    // 1.0.0 has it out of line; 3.0.1 inlines it into DrEnvironmentMan::createObj
    DrEnvironmentObjLgt(const void* resource, DrMan* drMan, DrLightMan* lightMan, DrFogMan* fogMan, int lgtArg)
        : DrEnvironmentObj(drMan, lightMan, fogMan) {
        m_lgtArg = lgtArg;
        m_work2 = nullptr;
        m_captureMode = 0;
        m_lgtArray[0] = nullptr;
        m_work[3] = nullptr;
        m_work[4] = nullptr;
        m_work[1] = nullptr;
        m_work[2] = nullptr;
        m_resource = resource;
        m_weatherNum = 0;
        m_work[0] = nullptr;
        memset(&m_lgtArray[1], 0, 0x20);
        memset(m_lgtArrayNum, 0, 0x20);
        m_updateReq = 1;
    }
    virtual ~DrEnvironmentObjLgt();  // slot 0
    virtual void resourceInit();  // slot 2
    virtual void update();  // slot 3
    virtual void renderLgt();  // slot 4
    virtual void debugRenderLgt();  // slot 5
    virtual void debugRenderLgt2D();  // slot 6
    virtual void setFrame(float);  // slot 7
    virtual void changeMemCall(void const*);  // slot 8

    void releaseLgt();
    void setupLgt(int);

    // per light type callbacks (s_pCallEnvRelase, s_pCallEnvChk, s_pCallCalcEnv, s_pCallLgtRender, s_pCallLgtRender2D)
    void callback_Relase_Non(DrLightObj* light);
    void callback_Relase_Point(DrLightObj* light);
    void callback_Relase_Spot(DrLightObj* light);
    bool callback_Chk_non(DrEnvironmentLgtList* list, DrCalcViewWork* work, const LgtObjData* data);
    bool callback_Calc_Non(DrEnvironmentLgtList* list, DrCalcViewWork* work);
    bool callback_Calc_LocalIBL(DrEnvironmentLgtList* list, DrCalcViewWork* work);
    void callback_Ren_Non(DrLightObj* light, DrShdLgtMan* shdLgtMan);
    void callback_Ren_Point(DrLightObj* light, DrShdLgtMan* shdLgtMan);
    void callback_Ren_Spot(DrLightObj* light, DrShdLgtMan* shdLgtMan);
    void callback_Ren2D_Non(DrLightObj* light, DrShdLgtMan* shdLgtMan);
    void callback_Ren2D_LocalIBL(DrLightObj* light, DrShdLgtMan* shdLgtMan);

    // indexed by LgtObjData::m_type (7 light types)
    static void (DrEnvironmentObjLgt::*s_pCallLgtRender[7])(DrLightObj*, DrShdLgtMan*);
    static void (DrEnvironmentObjLgt::*s_pCallLgtRender2D[7])(DrLightObj*, DrShdLgtMan*);
};
}  // namespace ml

#endif
