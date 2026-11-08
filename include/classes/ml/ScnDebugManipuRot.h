#ifndef CLASSES_ML_SCNDEBUGMANIPUROT_H
#define CLASSES_ML_SCNDEBUGMANIPUROT_H

#include "classes/ml/ScnDebugManipuObj.h"

namespace ml { class DebDraw; }
namespace ml { class EventView; }

namespace ml {
// table 0x7100B77C98
class ScnDebugManipuRot : public ::ml::ScnDebugManipuObj {
public:
    // ScnDebugManipu::createRot news one (no out-of-line copy)
    ScnDebugManipuRot(Scn* scn, const mm::Mat44* mtx, const mm::Vec3* pos)
        : ScnDebugManipuObj(SCNMANIPU_ROT, scn, mtx, pos), pad_970(0), m_radius(70.0f), m_radiusOuter(80.0f) {}
    virtual ~ScnDebugManipuRot();  // slot 0
    virtual void checkMouseButtonDown(ml::EventView*);  // slot 2
    virtual bool checkMouseButtonUp(ml::EventView*);  // slot 3
    virtual void checkMouseMove(ml::EventView*);  // slot 4
    virtual void setRadius(float);  // slot 5
    virtual void update();  // slot 6
    virtual void render(ml::DebDraw*);  // slot 7

    unsigned char pad_360[0x610];
    int pad_970;  // the constructor zeroes it
    unsigned char pad_974[0x1C];
    float m_radius;       // 0x990 setRadius's (70 for a radius not above 0) (the name is not the original's)
    float m_radiusOuter;  // setRadius's radius plus 10 (the name is not the original's)
    unsigned char pad_998[0x18];  // createRot news 0x9B0 bytes
};
}  // namespace ml

#endif
