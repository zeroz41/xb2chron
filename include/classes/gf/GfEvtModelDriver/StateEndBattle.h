#ifndef CLASSES_GF_GFEVTMODELDRIVER_STATEENDBATTLE_H
#define CLASSES_GF_GFEVTMODELDRIVER_STATEENDBATTLE_H

#include "classes/ai/State.h"
#include "classes/gf/GfEvtModelDriver.h"
#include "classes/gf/GfMountManager.h"
#include "gf/GfGameUtil.h"
#include "mm/mtl/FixStr.h"
#include <new>

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B541C0
class GfEvtModelDriver::StateEndBattle : public ::ai::State {
public:
    // what GfEvtModelDriver's constructor registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateEndBattle(); }
    virtual ~StateEndBattle() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfEvtModelDriver* owner, ai::State* prev);
    void leave(GfEvtModelDriver* owner, ai::State* next) {
        owner->setWeaponFieldMount();
    }
    void update(GfEvtModelDriver* owner, const fw::UpdateInfo& info);
};

// the slots: inline (the table has no key function; GfEvtModelDriver's constructor makes the state, so the table and the
// slots are emitted in gf_evt_model.cpp)
inline const char* GfEvtModelDriver::StateEndBattle::getName() const {
    return "StateEndBattle";
}
inline void GfEvtModelDriver::StateEndBattle::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfEvtModelDriver*>(owner), prev);
}
inline void GfEvtModelDriver::StateEndBattle::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfEvtModelDriver*>(owner), next);
}
inline void GfEvtModelDriver::StateEndBattle::onStep(void* owner, const void* arg) {
    update(static_cast<GfEvtModelDriver*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}
}  // namespace gf

#endif
