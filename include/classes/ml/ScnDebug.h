#ifndef CLASSES_ML_SCNDEBUG_H
#define CLASSES_ML_SCNDEBUG_H

#include "classes/ml/IScnRender.h"
#include "classes/ml/IWorkEvent.h"
#include "classes/ml/ScnDebugManipu.h"

namespace ml { class Scn; }
namespace ml { enum SCNPRIO_CB : int; }

namespace ml { class DebDraw; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace ml {
// table 0x7100B77BA8
class ScnDebug : public ::ml::IWorkEvent, public ::ml::IScnRender {
public:
    virtual ~ScnDebug();  // slot 0
    virtual void cbRenderAfter(ml::Scn*, ml::SCNPRIO_CB);  // slot 8
    ScnDebugManipu* getManipulator();
    bool isPickManipu() const;
    void clrManipulator();
    // a translation or rotation manipulator on the matrix and position given, by the manipulator owner
    void setManipulatorTrans(const mm::Mat44* mtx, const mm::Vec3* pos);
    void setManipulatorRot(const mm::Mat44* mtx, const mm::Vec3* pos);
    // the manipulator's drawing (1.0.0 keeps it out of line; 3.0.1's cbRenderAfter inlines it)
    void render(DebDraw* draw) {
        if (m_manipu != nullptr) {
            m_manipu->render(draw);
        }
    }

    unsigned char pad_10[0x8];
    ScnDebugManipu* m_manipu;  // 0x18 (the name is not the original's)
};
}  // namespace ml

#endif
