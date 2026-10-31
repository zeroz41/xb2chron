#ifndef CLASSES_LAYER_LAYERACTBASE_H
#define CLASSES_LAYER_LAYERACTBASE_H

#include "classes/layer/LayerObj.h"

namespace layer {
// one action's record (the layout is not the original's)
struct LyrActionInfo {
    unsigned char pad_0[0x8];
    unsigned int m_id;  // LayerAccAction::actionID looks for it
    // its name's offset in the action data's m_nameTbl is the sum of these two (LayerAccAction::actionName; the
    // names are not the original's)
    unsigned int m_nameBase;
    unsigned char pad_10[0x4];
    unsigned short m_nameOfs;
    unsigned char pad_16[0x2];
    float m_sec;  // LayerAccAction::getActionSec
    unsigned char pad_1C[0x10];
};
// an object's action data (only the action count is known; the layout is not the original's)
class LyrActionData {
public:
    const char* m_nameTbl;  // the actions' names (LayerAccAction::actionName; the name is not the original's)
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
    virtual ~LayerActBase() {}  // slot 0
    virtual void updatePartsAction(layer::LyrActionData const*) {}  // slot 10
    void actionEnd();
    // what an action's end type does when it ends (returns whether the action ends; the third argument, as its
    // end-of-commands flag, actend_cmdend negates)
    bool actend_no(const LyrActionData* data, bool cmdEnd);
    bool actend_cmdend(const LyrActionData* data, bool cmdEnd);
    bool actend_on(const LyrActionData* data, bool cmdEnd);
    void actionIdx(unsigned int index);
    // the action commands: each reads its command at cmd, steps cmd past it and returns whether the action waits
    bool actcmd_no(const unsigned char*& cmd);
    bool actcmd_priority(const unsigned char*& cmd);
    bool actcmd_wait(const unsigned char*& cmd);
    bool actcmd_ctrlspd(const unsigned char*& cmd);

    LyrActionData* m_actionData;  // its actions, or null (LayerAccAction::isActionData; the name is not the original's)
};
}  // namespace layer

#endif
