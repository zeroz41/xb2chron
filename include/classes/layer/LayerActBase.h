#ifndef CLASSES_LAYER_LAYERACTBASE_H
#define CLASSES_LAYER_LAYERACTBASE_H

#include "classes/layer/LayerObj.h"

namespace layer {
// one action's record (the layout is not the original's)
struct LyrActionInfo {
    unsigned char pad_0[0x8];
    unsigned int m_id;  // LayerAccAction::actionID looks for it
    unsigned char pad_C[0xC];
    float m_sec;  // LayerAccAction::getActionSec
    unsigned char pad_1C[0x10];
};
// an object's action data (only the action count is known; the layout is not the original's)
class LyrActionData {
public:
    unsigned char pad_0[0x8];
    const LyrActionInfo* m_actions;  // m_actionMax records
    int m_actionMax;  // LayerAccAction::getActionMax
    // the action running when the object's STATE_PARTS_ACTION is set (LayerAccAction::getRunningActIdx and
    // setRunningActSec; the names are not the original's)
    float m_runningSec;
    unsigned char pad_18[0x8];
    int m_runningIdx;
};
}  // namespace layer

namespace layer {
// table none (its derived classes')
class LayerActBase : public ::layer::LayerObj {
public:
    virtual ~LayerActBase();  // slot 0
    virtual void updatePartsAction(layer::LyrActionData const*) {}  // slot 10
    void actionEnd();
    // what an action's end type does when it ends (returns whether the action ends; the third argument, as its
    // end-of-commands flag, actend_cmdend negates)
    bool actend_no(const LyrActionData* data, bool cmdEnd);
    bool actend_cmdend(const LyrActionData* data, bool cmdEnd);
    bool actend_on(const LyrActionData* data, bool cmdEnd);
    void actionIdx(unsigned int index);

    unsigned char pad_248[0x8];
    LyrActionData* m_actionData;  // its actions, or null (LayerAccAction::isActionData; the name is not the original's)
};
}  // namespace layer

#endif
