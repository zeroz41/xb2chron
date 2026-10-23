#ifndef CLASSES_GF_PC_STATEBATTLEBASE_H
#define CLASSES_GF_PC_STATEBATTLEBASE_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table 0x7100B66D08
class StateBattleBase : public ::gf::GfStateBase {
public:
    StateBattleBase();  // out of line (the states' create functions call it)
    virtual ~StateBattleBase() {}  // slot 0: inline (the states' deleting destructors only free them)
    virtual void recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    virtual void Enter(gf::GfComBehaviorPc*, ai::State*);  // slot 8
    virtual void Leave(gf::GfComBehaviorPc*, ai::State*);  // slot 9: out of line (0x71004E75DC)
    virtual void BeforeUpdate(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&) {}  // slot 10
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&);  // slot 11: out of line (0x71004E6DD8)
    virtual void AfterUpdate(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&) {}  // slot 12
    virtual bool IsBattleActionState() const { return false; }  // slot 13
    // what the states' onEnter/onLeave/onStep slots hand the owner to
    void enter(gf::GfComBehaviorPc* behavior, ai::State* prev);
    void leave(gf::GfComBehaviorPc* behavior, ai::State* next);
    void update(gf::GfComBehaviorPc* behavior, const fw::UpdateInfo& info);

    // the constructor (0x71004E6174) clears 0x18..0x22; enter (0x71004E6198) keeps the behavior at 0x18 while it
    // calls Enter and stores Enter's result at 0x20. Every battle state is 0x28 bytes (registerBattleStates' sizes)
    unsigned char pad_18[0x10];
};
}}  // namespace gf::pc

#endif
