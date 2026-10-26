#ifndef CLASSES_ML_SCNDEBUGMANIPUROT_H
#define CLASSES_ML_SCNDEBUGMANIPUROT_H

#include "classes/ml/ScnDebugManipuObj.h"

namespace ml { class DebDraw; }
namespace ml { class EventView; }

namespace ml {
// table 0x7100B77C98
class ScnDebugManipuRot : public ::ml::ScnDebugManipuObj {
public:
    virtual ~ScnDebugManipuRot();  // slot 0
    virtual void checkMouseButtonDown(ml::EventView*);  // slot 2
    virtual bool checkMouseButtonUp(ml::EventView*);  // slot 3
    virtual void checkMouseMove(ml::EventView*);  // slot 4
    virtual void setRadius(float);  // slot 5
    virtual void update();  // slot 6
    virtual void render(ml::DebDraw*);  // slot 7

    unsigned char pad_360[0x630];
    float m_radius;       // 0x990 setRadius's (70 for a radius not above 0) (the name is not the original's)
    float m_radiusOuter;  // setRadius's radius plus 10 (the name is not the original's)
};
}  // namespace ml

#endif
