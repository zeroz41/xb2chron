#ifndef CLASSES_LAYER_LAYERACTBASE_H
#define CLASSES_LAYER_LAYERACTBASE_H

#include "classes/layer/LayerObj.h"

namespace layer {
// one action's record (0x2C bytes; LayerActBase::updateAction passes the running one to updatePartsAction, which
// hands it to the s_pCallActEnd function its m_endType picks). The field names are not the original's
class LyrActionData {
public:
    // bits 1..6 turn the object's STATE_ flags on/off when the action starts (LayerActBase::setupAction,
    // updateAction); bit 0 (FLAG_LOOP) makes updatePartsAction go on with m_nextIdx when the action ends
    enum { FLAG_LOOP = 0x1 };
    unsigned int m_flags;
    unsigned short m_nextIdx;  // 0x4: the action that follows (FLAG_LOOP)
    unsigned short m_endType;  // 0x6: the s_pCallActEnd index
    unsigned int m_id;  // 0x8: LayerAccAction::actionID looks for it
    // 0xC: the action's commands, from the action data's start (updatePartsAction); an earlier reading took it as the
    // base of the action's name offset in LayerAccAction::actionName, with m_nameOfs
    unsigned int m_cmdOfs;
    short m_cmdNum;  // 0x10: how many commands updatePartsAction runs
    unsigned char pad_12[0x2];
    unsigned short m_nameOfs;
    unsigned char pad_16[0x2];
    float m_sec;  // LayerAccAction::getActionSec
    unsigned char pad_1C[0x10];
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
    // runs the current action's commands (the TopDef/TopLayout updateFast)
    void updateAction();
    // takes the object's action data (data) and the block work it runs them in: an ActionWork, then one int per
    // command; starts the header's first action when its FLAG_AUTO_START is set
    void setupAction(unsigned char* work, const unsigned char* data);
    // the action commands: each reads its command at cmd, steps cmd past it and returns whether the action waits
    bool actcmd_no(const unsigned char*& cmd);
    bool actcmd_priority(const unsigned char*& cmd);
    bool actcmd_wait(const unsigned char*& cmd);
    bool actcmd_ctrlspd(const unsigned char*& cmd);
    bool actcmd_pos(const unsigned char*& cmd);
    bool actcmd_rot(const unsigned char*& cmd);
    bool actcmd_scl(const unsigned char*& cmd);
    bool actcmd_numrot(const unsigned char*& cmd);
    bool actcmd_mulcol(const unsigned char*& cmd);
    bool actcmd_addcol(const unsigned char*& cmd);

    // an object's running action data (only the action count is known; the type and field names are not the
    // original's)
    struct ActionWork {
        const unsigned char* m_data;  // the action data setupAction was given (LyrActionData::m_cmdOfs counts from it)
        const LyrActionData* m_actions;  // m_actionMax records
        int m_actionMax;  // LayerAccAction::getActionMax
        // the action running when the object's STATE_PARTS_ACTION is set (LayerAccAction::getRunningActIdx and
        // setRunningActSec)
        float m_runningSec;
        // the running action's time step and its reciprocal: the actcmd_ interpolations move 1 / ((end -
        // m_runningSec) * m_stepRate) of the way each update, none when m_stepSec is 0
        float m_stepSec;   // 0x18
        float m_stepRate;  // 0x1C
        unsigned int m_runningIdx;
        // bit 0 (FLAG_CMD_START) is set when the running action's commands start over: LayerActDef::actcmd_animfrm
        // then takes the command's start and end frames
        enum { FLAG_CMD_START = 0x1 };
        unsigned int m_flags;  // 0x24
        int* m_cmdWork;  // 0x28: one int per command, cleared by setupAction (the block follows this one)
    };
    // the action data's header (setupAction; the type and field names are not the original's)
    struct ActionHeader {
        enum { FLAG_AUTO_START = 0x1 };
        unsigned int m_flags;
        unsigned int m_actionOfs;  // the LyrActionData records, from the header's start
        int m_actionNum;  // ActionWork::m_actionMax
        int m_cmdWorkNum;  // the ints of ActionWork::m_cmdWork
        unsigned int m_startIdx;  // the action FLAG_AUTO_START starts
    };
    // the running action's start: its commands start over and its LyrActionData flags (bits 1..6) turn STATE_HIDE,
    // STATE_DISP and STATE_ANIME_PAUSE on or off (inlined in setupAction and updateAction; the name is not the
    // original's)
    void startAction() {
        m_actionData->m_flags |= ActionWork::FLAG_CMD_START;
        m_actionData->m_runningSec = 0.0f;
        const LyrActionData* action = m_actionData->m_actions + m_actionData->m_runningIdx;
        if (action->m_flags & 0x7E) {
            if (action->m_flags & 0x2) {
                m_stateFlags |= STATE_HIDE;
            } else if (action->m_flags & 0x4) {
                m_stateFlags &= ~STATE_HIDE;
            }
            if (action->m_flags & 0x8) {
                m_stateFlags |= STATE_DISP;
            } else if (action->m_flags & 0x10) {
                m_stateFlags &= ~STATE_DISP;
            }
            if (action->m_flags & 0x20) {
                m_stateFlags |= STATE_ANIME_PAUSE;
            } else if (action->m_flags & 0x40) {
                m_stateFlags &= ~STATE_ANIME_PAUSE;
            }
        }
        m_stateFlags |= STATE_PARTS_ACTION;
    }
    // the action end types' functions (by LyrActionData::m_endType)
    static bool (LayerActBase::*s_pCallActEnd[3])(const LyrActionData* data, bool cmdEnd);

    ActionWork* m_actionData;  // its actions, or null (LayerAccAction::isActionData; the name is not the original's)
};
}  // namespace layer

#endif
