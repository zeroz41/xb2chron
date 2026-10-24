#ifndef CLASSES_GF_ENEMY_STATEFIELDSPAWN_H
#define CLASSES_GF_ENEMY_STATEFIELDSPAWN_H

#include "classes/gf/GfStateBase.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorEnemy; }

namespace gf { namespace enemy {
// table 0x7100B65F90
class StateFieldSpawn : public ::gf::GfStateBase {
public:
    StateFieldSpawn() : pad_18(false) {}
    // what GfComBehaviorEnemy::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldSpawn; }
    virtual ~StateFieldSpawn() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateFieldSpawn"; }  // slot 2
    // the slots hand the owner to the state's own functions
    virtual void onEnter(void* owner, ai::State* prev) { enter(static_cast<GfComBehaviorEnemy*>(owner), prev); }  // slot 3
    virtual void onLeave(void* owner, ai::State* next) { leave(static_cast<GfComBehaviorEnemy*>(owner), next); }  // slot 4
    virtual void onStep(void* owner, const void* arg) {  // slot 5
        update(static_cast<GfComBehaviorEnemy*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
    }
    void enter(GfComBehaviorEnemy* owner, ai::State* prev);
    void leave(GfComBehaviorEnemy* owner, ai::State* next);
    void update(GfComBehaviorEnemy* owner, const fw::UpdateInfo& info);
    bool pad_18;
};
}}  // namespace gf::enemy

#endif
