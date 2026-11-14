#ifndef GF_GFENEMYBATTLEPROPERTY_H
#define GF_GFENEMYBATTLEPROPERTY_H

#include "mm/Vec3.h"

namespace gf { class GfComPropertyEnemy; }
namespace gf { class MsgObjectNotifyDamage; }

namespace gf { namespace enemy {
// no table: an enemy's battle state, held by its GfComPropertyEnemy (which calls Initialize from setup,
// Update from flush and Finalize from cleanup)
class GfEnemyBattleProperty {
public:
    GfEnemyBattleProperty();
    void Initialize(const GfComPropertyEnemy& property);
    void Finalize(const GfComPropertyEnemy& property);
    void Update(const GfComPropertyEnemy& property);
    // the distances it returns home at: its own (Initialize: -1.0), or BtlSystemBalanceAccess's while BattleGlobal's
    // pad_bit30 is set
    float GetReturnHomeDistance() const;
    float GetReturnHomeCharacterDistance() const;
    // hands the damage to its battle character (none: nothing)
    void NotifyDamage(const MsgObjectNotifyDamage& msg);

    mm::Vec3 pad_0;  // Initialize zeroes it
    // btl::CharacterManager::Register's for the enemy (the constructor: -1; Finalize releases it); 1.0.0's
    // GetCharacterParameterConst looks the character up by it (the name is not the original's)
    int m_characterIndex;
    // 1.0.0's GetReturnHomeDistance returns it outside battle (Initialize: -1.0; the name is not the original's)
    float m_returnHomeDistance;
    // GetReturnHomeCharacterDistance returns it (Initialize: -1.0; the name is not the original's)
    float m_returnHomeCharacterDistance;
    // Initialize zeroes both; StateBattle::Enter sets them from the enemy's getChrEnArrangeBatAreaType and its
    // getRscEnActType (the names are not the original's)
    unsigned char m_batAreaType;
    unsigned char m_actType;
    bool pad_1e;  // the constructor and Initialize clear it, Update tests, sets and clears it
    bool pad_1f;  // the constructor and Initialize clear it, Update tests and clears it, sets it at its end
};
}}  // namespace gf::enemy

#endif
