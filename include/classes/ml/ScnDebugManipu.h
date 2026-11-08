#ifndef CLASSES_ML_SCNDEBUGMANIPU_H
#define CLASSES_ML_SCNDEBUGMANIPU_H

#include "classes/ml/IWorkEvent.h"
#include "ml/CriticalSection.h"
#include "classes/ml/ScnDebugManipuObj.h"

namespace ml { class AttrTransform; }
namespace ml { class Scn; }
namespace ml { class ScnDebugManipuObj; }

namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace ml {
// table 0x7100B77C48
class ScnDebugManipu : public ::ml::IWorkEvent {
public:
    // Scn::init news one for the scene's ScnDebug (no out-of-line copy in 1.0.0 or 3.0.1)
    explicit ScnDebugManipu(Scn* scn) : m_scn(scn), m_obj(nullptr), m_disp(true) {}
    void createTrans(const mm::Mat44* mtx, const mm::Vec3* pos);
    void createRot(const mm::Mat44* mtx, const mm::Vec3* pos);
    virtual ~ScnDebugManipu();  // slot 0
    // the manipulator given up (1.0.0 keeps it out of line; 3.0.1's ScnDebug::clrManipulator inlines it)
    void clear();
    // shows or hides the manipulator (1.0.0 keeps it out of line; 3.0.1's createTrans/createRot inline it)
    void setDisp(bool disp) {
        CS cs(m_cs);
        m_disp = disp;
        if (m_obj != nullptr) {
            m_obj->m_disp = disp;
        }
    }
    void setTrans(const AttrTransform& trans);
    // whether the manipulator is picked (1.0.0 keeps it out of line; 3.0.1's ScnDebug::isPickManipu inlines it)
    bool isPick() const;
    // the manipulator's transform: the calculation thread's (true) or the render thread's (false); none without one
    const AttrTransform* getTrans(bool cpu) const;
    // the shown manipulator's drawing (1.0.0 keeps it out of line; 3.0.1's ScnDebug::cbRenderAfter inlines it)
    void render(DebDraw* draw) {
        CS cs(m_cs);
        if (m_disp && m_obj != nullptr) {
            m_obj->render(draw);
        }
    }

    CriticalSection m_cs;  // 0x8 (the name is not the original's)
    Scn* m_scn;  // 0x30 the constructor's scene (the name is not the original's)
    ScnDebugManipuObj* m_obj;  // 0x38 the manipulator createTrans/createRot make (the name is not the original's)
    bool m_disp;  // 0x40 1.0.0's setDisp writes it (the name is not the original's)
};
}  // namespace ml

#endif
