#ifndef CLASSES_GF_GFEVTMODELBLADE_STATEIDLEFIELD_H
#define CLASSES_GF_GFEVTMODELBLADE_STATEIDLEFIELD_H

#include "classes/ai/State.h"
#include "classes/gf/GfEvtModelBlade.h"
#include "classes/gf/GfMountManager.h"
#include "gf/GfGameUtil.h"
#include "mm/mtl/FixStr.h"
#include <new>

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B54208
class GfEvtModelBlade::StateIdleField : public ::ai::State {
public:
    // what GfEvtModelBlade's constructor registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateIdleField(); }
    virtual ~StateIdleField() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
};

// the slots: inline (the table has no key function; GfEvtModelBlade's constructor makes the state, so the table and the
// slots are emitted in gf_evt_model.cpp)
inline const char* GfEvtModelBlade::StateIdleField::getName() const {
    return "StateIdleField";
}
inline void GfEvtModelBlade::StateIdleField::onEnter(void* owner, ai::State* prev) {}
inline void GfEvtModelBlade::StateIdleField::onLeave(void* owner, ai::State* next) {}
inline void GfEvtModelBlade::StateIdleField::onStep(void* owner, const void* arg) {}
}  // namespace gf

#endif
