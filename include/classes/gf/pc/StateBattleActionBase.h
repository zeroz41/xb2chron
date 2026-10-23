#ifndef CLASSES_GF_PC_STATEBATTLEACTIONBASE_H
#define CLASSES_GF_PC_STATEBATTLEACTIONBASE_H

#include "classes/gf/pc/StateBattleBase.h"

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorPc; }

namespace gf { namespace pc {
// table none (its derived classes')
// a StateBattleBase: its states' create functions construct one through StateBattleBase's constructor
class StateBattleActionBase : public ::gf::pc::StateBattleBase {
public:
    virtual ~StateBattleActionBase() {}  // slot 0: inline (the states' deleting destructors only free them)
    virtual void recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    virtual void Enter(gf::GfComBehaviorPc*, ai::State*);  // slot 8: out of line (0x71004E66FC)
    virtual void Leave(gf::GfComBehaviorPc*, ai::State*) = 0;  // slot 9
    virtual void BeforeUpdate(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&);  // slot 10
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&);  // slot 11: out of line (0x71004E6894)
    virtual void AfterUpdate(btl::BattleCharacter*, gf::GfComBehaviorPc*, fw::UpdateInfo const&);  // slot 12
    virtual bool IsBattleActionState() const { return true; }  // slot 13
};
}}  // namespace gf::pc

#endif
