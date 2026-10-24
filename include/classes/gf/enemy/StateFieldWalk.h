#ifndef CLASSES_GF_ENEMY_STATEFIELDWALK_H
#define CLASSES_GF_ENEMY_STATEFIELDWALK_H

#include "classes/gf/GfStateBase.h"
#include "classes/gf/TFieldExecCmd.h"
#include "mm/Vec3.h"
#include <new>

namespace ai { class State; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComAsm; }
namespace gf { class GfComBehaviorEnemy; }

namespace gf { namespace enemy {
// table 0x7100B66030
class StateFieldWalk : public ::gf::GfStateBase {
public:
    StateFieldWalk() : pad_18(false), pad_19(false), pad_1c(0), pad_58(nullptr), pad_60(nullptr), pad_68(0), pad_70(mm::Vec3::zero), pad_80(-1), pad_84(-1), pad_88(false), pad_8c(0), pad_90(0), pad_94(0.0f), pad_98(5.0f), pad_9c(0.0f) {}
    // what GfComBehaviorEnemy::createFsm registers with its Hfsm: the state made in a state buffer
    static ai::State* create(void* buffer) { return new (buffer) StateFieldWalk; }
    virtual ~StateFieldWalk() {}  // slot 0: inline (emitted with the table by the registering unit)
    virtual const char* getName() const { return "StateFieldWalk"; }  // slot 2
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
    bool pad_19;
    unsigned int pad_1c;
    TFieldExecCmd<GfComAsm> m_execCmd;
    void* pad_58;
    void* pad_60;
    unsigned int pad_68;
    mm::Vec3 pad_70;
    int pad_80;
    int pad_84;
    bool pad_88;
    unsigned int pad_8c;
    unsigned int pad_90;
    float pad_94;
    float pad_98;
    float pad_9c;
};
}}  // namespace gf::enemy

#endif
