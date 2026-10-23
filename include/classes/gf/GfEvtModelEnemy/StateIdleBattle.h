#ifndef CLASSES_GF_GFEVTMODELENEMY_STATEIDLEBATTLE_H
#define CLASSES_GF_GFEVTMODELENEMY_STATEIDLEBATTLE_H

#include "classes/ai/State.h"
#include "classes/gf/GfEvtModelEnemy.h"
#include "classes/gf/GfMountManager.h"
#include "gf/GfGameUtil.h"
#include "mm/mtl/FixStr.h"
#include <new>

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B54370
class GfEvtModelEnemy::StateIdleBattle : public ::ai::State {
public:
    // what GfEvtModelEnemy's constructor registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateIdleBattle(); }
    virtual ~StateIdleBattle() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};

// the slots: inline (the table has no key function; GfEvtModelEnemy's constructor makes the state, so the table and the
// slots are emitted in gf_evt_model.cpp)
inline const char* GfEvtModelEnemy::StateIdleBattle::getName() const {
    return "StateIdleBattle";
}
inline void GfEvtModelEnemy::StateIdleBattle::onEnter(void* owner, ai::State* prev) {}
inline void GfEvtModelEnemy::StateIdleBattle::onLeave(void* owner, ai::State* next) {}
inline void GfEvtModelEnemy::StateIdleBattle::onStep(void* owner, const void* arg) {}
}  // namespace gf

#endif
