#ifndef CLASSES_ML_SCNDEBUGMANIPUROT_H
#define CLASSES_ML_SCNDEBUGMANIPUROT_H

namespace ml { class DebDraw; }
namespace ml { class EventView; }

namespace ml {
// table 0x7100B77C98
class ScnDebugManipuRot {
public:
    virtual ~ScnDebugManipuRot();  // slot 0
    virtual void checkMouseButtonDown(ml::EventView*);  // slot 2
    virtual bool checkMouseButtonUp(ml::EventView*);  // slot 3
    virtual void checkMouseMove(ml::EventView*);  // slot 4
    virtual void setRadius(float);  // slot 5
    virtual void update();  // slot 6
    virtual void render(ml::DebDraw*);  // slot 7
};
}  // namespace ml

#endif
