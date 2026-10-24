#ifndef CLASSES_GF_NPC_STATETALK_H
#define CLASSES_GF_NPC_STATETALK_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include <new>

namespace ai { class State; }
namespace gf { class GfComAsm; }

namespace gf { namespace npc {
// table 0x7100B66AE0
class StateTalk : public ::gf::GfStateBase {
public:
    StateTalk();  // out of line: create calls it (defined with the table, in another unit)
    // what GfComBehaviorNpc::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateTalk; }
    virtual ~StateTalk();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the constructor sets them up (0x68 bytes: Hfsm::registerState<StateTalk>)
    TFieldExecCmd<GfComAsm> m_execCmd;
    void* pad_50;
    void* pad_58;
    bool pad_60;
};
}}  // namespace gf::npc

#endif
