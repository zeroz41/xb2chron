#ifndef CLASSES_ML_DRENVIRONMENTOBJLGT_H
#define CLASSES_ML_DRENVIRONMENTOBJLGT_H

#include "classes/ml/DrEnvironmentObj.h"

namespace ml { class DrCalcViewWork; }
namespace ml { class DrEnvironmentLgtList; }
namespace ml { class DrLightObj; }
namespace ml { class DrShdLgtMan; }
namespace ml { struct LgtObjData; }

namespace ml {
// table 0x7100B7B270
class DrEnvironmentObjLgt : public ::ml::DrEnvironmentObj {
public:
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
};
}  // namespace ml

#endif
