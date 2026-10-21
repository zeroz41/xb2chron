#ifndef CLASSES_ML_SCNDEBUGMANIPUTRANS_H
#define CLASSES_ML_SCNDEBUGMANIPUTRANS_H

namespace ml { class DebDraw; }
namespace ml { class EventView; }

namespace ml {
// table 0x7100B77CE8
class ScnDebugManipuTrans {
public:
    virtual ~ScnDebugManipuTrans();  // slot 0
    virtual void checkMouseButtonDown(ml::EventView*);  // slot 2
    virtual bool checkMouseButtonUp(ml::EventView*);  // slot 3
    virtual void checkMouseMove(ml::EventView*);  // slot 4
    virtual void setRadius(float);  // slot 5
    virtual void update();  // slot 6
    virtual void render(ml::DebDraw*);  // slot 7
};
}  // namespace ml

#endif
