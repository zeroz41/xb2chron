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
    StateFieldIdle() : pad_18(0), pad_58(nullptr), pad_60(nullptr), pad_68(nullptr) {}
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
    unsigned int pad_18;
    TFieldExecCmd<GfComAsm> m_execCmd;
    void* pad_58;
    void* pad_60;
    void* pad_68;
};
}}  // namespace gf::enemy

#endif
