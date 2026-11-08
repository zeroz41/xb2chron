#ifndef CLASSES_GF_ENEMY_STATEFIELDIDLE_H
#define CLASSES_GF_ENEMY_STATEFIELDIDLE_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gf { class GfComBehaviorEnemy; }

namespace gf { namespace enemy {
// table 0x7100B65F40
class StateFieldIdle : public ::gf::GfStateBase {
public:
    // a step of the state: update runs it, none when null
    typedef void (StateFieldIdle::*Seq)(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    // a state ID and a name for it: enter looks up the command it starts and the actMove column it reads the idle
    // time from by the state's ID (the names are not the original's)
    struct StateName {
        unsigned int m_stateId;
        const char* m_name;
    };
    StateFieldIdle() : pad_18(0), pad_58(0.0f), pad_5c(0.0f), m_seq(nullptr) {}
    // what GfComBehaviorEnemy::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldIdle; }
    virtual ~StateFieldIdle() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateFieldIdle"; }  // slot 2
    // the slots hand the owner to the state's own functions
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorEnemy*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfComBehaviorEnemy*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        update(static_cast<GfComBehaviorEnemy*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
    }
    void enter(GfComBehaviorEnemy* owner, ai::State* prev);
    void leave(GfComBehaviorEnemy* owner, ai::State* next);
    void update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info);
    void seqFlyInsectIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    void seqOthersIdle(GfComBehaviorEnemy& owner, const fw::UpdateInfo& info);
    unsigned int pad_18;
    TFieldExecCmd<GfComAsm> m_execCmd;
    // update adds dt to pad_58 and leaves the state once it reaches pad_5c (when pad_5c is not 0); update reads
    // pad_5c from the idle motion's playback time while it is negative; seqFlyInsectIdle copies pad_5c into pad_58
    // on arriving (the names are not known)
    float pad_58;
    float pad_5c;
    Seq m_seq;
};
}}  // namespace gf::enemy

#endif
