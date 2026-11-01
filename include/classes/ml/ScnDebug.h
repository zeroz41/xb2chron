#ifndef CLASSES_ML_SCNDEBUG_H
#define CLASSES_ML_SCNDEBUG_H

#include "classes/ml/IScnRender.h"
#include "classes/ml/IWorkEvent.h"
#include "classes/ml/ScnDebugManipu.h"
#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"

namespace ml { class Scn; }
namespace ml { enum SCNPRIO_CB : int; }

namespace ml { class DebDraw; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace ml {
// table 0x7100B77BA8
class ScnDebug : public ::ml::IWorkEvent, public ::ml::IScnRender {
public:
    // Scn::init news one; it news its manipulator from the same allocator (no out-of-line copy in 1.0.0 or 3.0.1;
    // inlined: the manipulator's allocation temporary sits above init's own)
    ScnDebug(Scn* scn, mtl::ALLOC_HANDLE mem) : m_scn(scn), m_manipu(nullptr), pad_20(-1), pad_28(0), pad_30(true) {
        m_manipu = new (mem, nullptr, 0, 4, false) ScnDebugManipu(scn);
    }
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

    Scn* m_scn;  // 0x10 the constructor's scene (the name is not the original's)
    ScnDebugManipu* m_manipu;  // 0x18 (the name is not the original's)
    int pad_20;  // the constructor sets -1
    unsigned long pad_28;  // the constructor clears it
    bool pad_30;  // the constructor sets it
};
}  // namespace ml

#endif
