#ifndef CLASSES_GF_GFEVTMODELBLADE_STATEENDBATTLE_H
#define CLASSES_GF_GFEVTMODELBLADE_STATEENDBATTLE_H

#include "classes/ai/State.h"
#include "classes/gf/GfEvtModelBlade.h"
#include "classes/gf/GfMountManager.h"
#include "gf/GfGameUtil.h"
#include "mm/mtl/FixStr.h"
#include <new>

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B542E0
class GfEvtModelBlade::StateEndBattle : public ::ai::State {
public:
    // what GfEvtModelBlade's constructor registers with its Fsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateEndBattle(); }
    virtual ~StateEndBattle() {}  // slot 0
    virtual const char* getName() const;  // slot 2
    virtual void onEnter(void*, ai::State*);  // slot 3
    virtual void onLeave(void*, ai::State*);  // slot 4
    virtual void onStep(void*, void const*);  // slot 5
    // the state's own functions; the slots above hand them the owner
    void enter(GfEvtModelBlade* owner, ai::State* prev) {
        if (GfMountManager::getMountType(owner->m_handle, static_cast<GFATTACH>(0)) != 2) {
            mm::mtl::FixStr<32> command;
            GfGameUtil::makeCommandBattle(command, false);
            mm::mtl::FixStr<32> state;
            GfGameUtil::makeStateBattle(state, owner->m_handle, false);
            fn_710029C9B4(owner->m_handle, command, state);
        }
    }
    void leave(GfEvtModelBlade* owner, ai::State* next) {
        GfMountManager::execMount(owner->m_handle, static_cast<GFATTACH>(0), static_cast<OPTMNT>(2));
    }
    void update(GfEvtModelBlade* owner, const fw::UpdateInfo& info);
};

// the slots: inline (the table has no key function; GfEvtModelBlade's constructor makes the state, so the table and the
// slots are emitted in gf_evt_model.cpp)
inline const char* GfEvtModelBlade::StateEndBattle::getName() const {
    return "StateEndBattle";
}
inline void GfEvtModelBlade::StateEndBattle::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<GfEvtModelBlade*>(owner), prev);
}
inline void GfEvtModelBlade::StateEndBattle::onLeave(void* owner, ai::State* next) {
    leave(static_cast<GfEvtModelBlade*>(owner), next);
}
inline void GfEvtModelBlade::StateEndBattle::onStep(void* owner, const void* arg) {
    update(static_cast<GfEvtModelBlade*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}
}  // namespace gf

#endif
