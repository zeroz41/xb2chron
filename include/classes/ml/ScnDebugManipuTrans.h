#ifndef CLASSES_ML_SCNDEBUGMANIPUTRANS_H
#define CLASSES_ML_SCNDEBUGMANIPUTRANS_H

#include "classes/ml/ScnDebugManipuObj.h"
#include "mm/Pnt.h"

namespace ml { class DebDraw; }
namespace ml { class EventView; }

namespace ml {
// table 0x7100B77CE8
class ScnDebugManipuTrans : public ::ml::ScnDebugManipuObj {
public:
    // ScnDebugManipu::createTrans news one (no out-of-line copy)
    ScnDebugManipuTrans(Scn* scn, const mm::Mat44* mtx, const mm::Vec3* pos)
        : ScnDebugManipuObj(SCNMANIPU_TRANS, scn, mtx, pos), m_pickOfs(0, 0), m_axis(7) {}
    virtual ~ScnDebugManipuTrans();  // slot 0
    virtual void checkMouseButtonDown(ml::EventView*);  // slot 2
    virtual bool checkMouseButtonUp(ml::EventView*);  // slot 3
    virtual void checkMouseMove(ml::EventView*);  // slot 4
    virtual void setRadius(float);  // slot 5
    virtual void update();  // slot 6
    virtual void render(ml::DebDraw*);  // slot 7

    unsigned char pad_360[0x20];
    // checkMouseButtonDown's picked screen position less the mouse's; checkMouseMove adds it back (the name is not
    // the original's)
    mm::Pnt<int> m_pickOfs;  // 0x380
    int m_axis;  // 0x388 checkMouseButtonUp sets 7 (all three axes) (the name is not the original's)
};
}  // namespace ml

#endif
