#ifndef CLASSES_ML_SCNOBJCAM_H
#define CLASSES_ML_SCNOBJCAM_H

#include "classes/ml/ScnObj.h"

namespace ml { class DebDraw; }

namespace ml {
// table 0x7100B77D38
class ScnObjCam : public ::ml::ScnObj {
public:
    enum RENDER_INFO : int;
    virtual ~ScnObjCam();  // slot 0
    virtual void update();  // slot 2
    virtual void renderDebug(ml::DebDraw*);  // slot 3
    virtual void apply();  // slot 4
    virtual void getName() const;  // slot 6
};
}  // namespace ml

#endif
