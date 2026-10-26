#ifndef CLASSES_GF_NPC_STATETALK_H
#define CLASSES_GF_NPC_STATETALK_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gf { class GfComBehaviorNpc; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf { namespace npc {
// table 0x7100B66AE0
class StateTalk : public ::gf::GfStateBase {
public:
    // a step of the state: the sequence onStep runs, none when null
    typedef void (StateTalk::*Seq)(GfComBehaviorNpc& owner, const fw::UpdateInfo& info);

    StateTalk();  // out of line: create calls it (defined with the table, in this state's unit)
    // what GfComBehaviorNpc::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateTalk; }
    virtual ~StateTalk();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the constructor sets them up (0x68 bytes: Hfsm::registerState<StateTalk>)
    void enter(GfComBehaviorNpc* owner, ai::State* prev);
    inline void leave(GfComBehaviorNpc* owner, ai::State* next);  // onLeave inlines it
    inline void update(GfComBehaviorNpc* owner, const fw::UpdateInfo& info);  // onStep inlines it
    // lets the party's drivers and blades pass through npcs and mobs while the talk runs (false), or not (true)
    void setCollideNpcMob(bool collide);
    void setCollideNpcMob(GF_OBJ_HANDLE* handle, bool collide);
    void seqWaitTalkEnd(GfComBehaviorNpc& owner, const fw::UpdateInfo& info);
    void seqWaitTurnEnd(GfComBehaviorNpc& owner, const fw::UpdateInfo& info);
    TFieldExecCmd<GfComAsm> m_execCmd;
    Seq m_seq;
    // whether it came from StateIdle (state 0): the talk then ends with a turn back (the name is not the original's)
    bool m_fromIdle;
};
}}  // namespace gf::npc

#endif
