#ifndef CLASSES_GF_GFEVTMODELENEMY_STATESTARTBATTLE_H
#define CLASSES_GF_GFEVTMODELENEMY_STATESTARTBATTLE_H

#include "classes/ai/State.h"
#include "classes/gf/GfEvtModelEnemy.h"
#include "classes/gf/GfMountManager.h"
#include "gf/GfGameUtil.h"
#include "mm/mtl/FixStr.h"
#include <new>

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B543B8
class GfEvtModelEnemy::StateStartBattle : public ::ai::State {
public:
    // what GfEvtModelEnemy's constructor registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateStartBattle(); }
    virtual ~StateStartBattle() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfEvtModelEnemy* owner, ai::State* prev);
    void update(GfEvtModelEnemy* owner, const fw::UpdateInfo& info);
};

// the slots: inline (the table has no key function; GfEvtModelEnemy's constructor makes the state, so the table and the
// slots are emitted in gf_evt_model.cpp)
inline const char* GfEvtModelEnemy::StateStartBattle::getName() const {
    return "StateStartBattle";
}
inline void GfEvtModelEnemy::StateStartBattle::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfEvtModelEnemy*>(owner), prev);
}
inline void GfEvtModelEnemy::StateStartBattle::onLeave(void* owner, ai::State* next) {}
inline void GfEvtModelEnemy::StateStartBattle::onStep(void* owner, const void* arg) {
    update(static_cast<GfEvtModelEnemy*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}
}  // namespace gf

#endif
