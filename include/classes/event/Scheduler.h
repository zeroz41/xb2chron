#ifndef CLASSES_EVENT_SCHEDULER_H
#define CLASSES_EVENT_SCHEDULER_H

#include "classes/event/ScheduleItem.h"

namespace gf { class GF_OBJ_HANDLE; class GfObj; }

enum EVT_aimtype : int;

namespace event {
// table 0x7100B3D560
// What an event does with one object when it starts or ends (ScheManager::push builds one per object):
// exec runs three chains of steps, each step a func_* member that sets the chain's next step (the field names
// are not the original's)
class Scheduler {
public:
    typedef void (Scheduler::*Func)(gf::GfObj*);
    virtual ~Scheduler();  // slot 0
    void setup();
    void exec();
    void func_stanby(gf::GfObj* obj);
    void func_fld2evt(gf::GfObj* obj);
    void func_evt2idle(gf::GfObj* obj);
    void func_evt2fld(gf::GfObj* obj);
    void func_motionEnd(gf::GfObj* obj);
    void func_motionEnd_loop(gf::GfObj* obj);
    void func_turn(gf::GfObj* obj);
    static float getRotY(gf::GfObj* obj, gf::GfObj* target);
    void func_turn_loop(gf::GfObj* obj);
    void func_look(gf::GfObj* obj);
    static void lookTo(bool on, gf::GfObj* obj, gf::GfObj* target, EVT_aimtype aimType, bool immediate);
    void func_return(gf::GfObj* obj);
    void func_return_loop(gf::GfObj* obj);
    void func_motion(gf::GfObj* obj);
    void func_motion_loop(gf::GfObj* obj);
    void func_item(gf::GfObj* obj);
    void func_item_loop(gf::GfObj* obj);

    // bit 0: func_look still to aim (func_evt2idle sets it, func_look clears it once aimed)
    unsigned int m_state;
    // what to do, setup sets them by the object's kind: 0x4 turn to the leader, 0x8 return motion, 0x10 look,
    // 0x20 stop looking on leaving, 0x40 fade the held item out, 0x80 item fade/motion
    unsigned int m_flags;
    gf::GF_OBJ_HANDLE* m_handle;  // the object
    unsigned int m_bdatId;        // GfObjAcc::getBdatId of the object
    unsigned int m_type;          // ScheManager::push's argument: 0, 1 or 2
    EVT_aimtype m_aimType;        // func_look's lookTo argument
    ScheduleItem m_item;
    Func m_turnFunc;  // 0x50: func_motionEnd, func_turn chain
    Func m_lookFunc;  // 0x60: func_look chain
    Func m_actFunc;   // 0x70: func_return, func_motion, func_item chain
    int m_frame;      // func_return sets 360, func_motion_loop counts it down
};
}  // namespace event

#endif
