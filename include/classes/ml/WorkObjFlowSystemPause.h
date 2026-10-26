#ifndef CLASSES_ML_WORKOBJFLOWSYSTEMPAUSE_H
#define CLASSES_ML_WORKOBJFLOWSYSTEMPAUSE_H

#include "classes/ml/WorkObj.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace ml {
// the work that pauses the system flow; a singleton (PtrSingleton<WorkObjFlowSystemPause>'s instance at 0x7100ED09E0).
// The bases are inferred from its name and the singleton's field at 0x1B4 (as WorkFlowSetup's 0x1B0 follows its
// PtrSingleton base at 0x1A8); no table of its own is named.
class WorkObjFlowSystemPause : public ::ml::WorkObj, public ::mm::mtl::PtrSingleton<WorkObjFlowSystemPause> {
public:
    // how far the pause has faded in: (frames + 1) / 5, at most 1, times 0.4; 0 with no pause
    static float getRate();

    unsigned char pad_1b0[0x4];
    int m_frame;  // 0x1B4 getRate's frame count (the name is not the original's)
};
}  // namespace ml

#endif
