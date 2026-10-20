#ifndef CLASSES_ML_DRENVIRONMENTOBJ_H
#define CLASSES_ML_DRENVIRONMENTOBJ_H

namespace ml {
// table 0x7100B7B1F8
class DrEnvironmentObj {
public:
    virtual ~DrEnvironmentObj();  // slot 0
    virtual void resourceInit();  // slot 2
    virtual void update();  // slot 3
    virtual void renderLgt();  // slot 4
    virtual void debugRenderLgt();  // slot 5
    virtual void debugRenderLgt2D();  // slot 6
    virtual void setFrame(float) = 0;  // slot 7
    virtual void changeMemCall(void const*) = 0;  // slot 8
};
}  // namespace ml

#endif
