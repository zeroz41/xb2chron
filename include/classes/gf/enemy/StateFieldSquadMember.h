#ifndef CLASSES_GF_ENEMY_STATEFIELDSQUADMEMBER_H
#define CLASSES_GF_ENEMY_STATEFIELDSQUADMEMBER_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include <new>

namespace ai { class State; }
namespace gf { class GfComAsm; }

namespace gf { namespace enemy {
// table 0x7100B65D28
class StateFieldSquadMember : public ::gf::GfStateBase {
public:
    StateFieldSquadMember();  // out of line (StateFieldWalk's unit): create calls it
    // what GfComBehaviorEnemy::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldSquadMember; }
    virtual ~StateFieldSquadMember();  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // what its constructor sets (0x71004B7C28 / 0x71004B8B54; the pads' use is not known)
    TFieldExecCmd<GfComAsm> m_execCmd;
    void* pad_50;
    void* pad_58;
    bool pad_60;
    unsigned int pad_64;
};
}}  // namespace gf::enemy

#endif
