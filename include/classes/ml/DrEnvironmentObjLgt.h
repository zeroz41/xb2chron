#ifndef CLASSES_ML_DRENVIRONMENTOBJLGT_H
#define CLASSES_ML_DRENVIRONMENTOBJLGT_H

#include "classes/ml/DrEnvironmentObj.h"

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
};
}  // namespace ml

#endif
