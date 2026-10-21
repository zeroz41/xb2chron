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
    virtual ~StateBattleBase();  // slot 0
    virtual void recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    virtual void Enter(gf::GfComBehaviorPc*, ai::State*);  // slot 8
    virtual void Leave(gf::GfComBehaviorPc*, ai::State*) {}  // slot 9
    virtual void BeforeUpdate(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&) {}  // slot 10
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&) {}  // slot 11
    virtual void AfterUpdate(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&) {}  // slot 12
    virtual bool IsBattleActionState() const { return false; }  // slot 13
};
}}  // namespace gf::pc

#endif
