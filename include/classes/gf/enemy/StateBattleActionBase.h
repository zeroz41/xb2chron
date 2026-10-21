#ifndef CLASSES_GF_ENEMY_STATEBATTLEACTIONBASE_H
#define CLASSES_GF_ENEMY_STATEBATTLEACTIONBASE_H

#include "classes/gf/GfStateBase.h"

namespace ai { class State; }
namespace btl { class BattleCharacter; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace fw { class UpdateInfo; }
namespace gf { class GfComBehaviorEnemy; }

namespace gf { namespace enemy {
// table none (its derived classes')
class StateBattleActionBase : public ::gf::GfStateBase {
public:
    virtual ~StateBattleActionBase();  // slot 0
    virtual void recieveMessage(void*, fw::MessageObject*, fw::Message&);  // slot 7
    virtual void Enter(gf::GfComBehaviorEnemy*, ai::State*) = 0;  // slot 8
    virtual void Leave(gf::GfComBehaviorEnemy*, ai::State*) = 0;  // slot 9
    virtual void BeforeUpdate(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&);  // slot 10
    virtual void Update(btl::BattleCharacter*, gf::GfComBehaviorEnemy*, fw::UpdateInfo const&) = 0;  // slot 11
    virtual void vf12();  // slot 12
    virtual bool IsBattleActionState() const { return true; }  // slot 13
};
}}  // namespace gf::enemy

#endif
