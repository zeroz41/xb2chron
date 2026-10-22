#ifndef GF_GFENEMYBATTLEPROPERTY_H
#define GF_GFENEMYBATTLEPROPERTY_H

#include "mm/Vec3.h"

namespace gf { class GfComPropertyEnemy; }

namespace gf { namespace enemy {
// no table: an enemy's battle state, held by its GfComPropertyEnemy (which calls Initialize from setup,
// Update from flush and Finalize from cleanup)
class GfEnemyBattleProperty {
public:
    GfEnemyBattleProperty();
    void Initialize(const GfComPropertyEnemy& property);
    void Finalize(const GfComPropertyEnemy& property);
    void Update(const GfComPropertyEnemy& property);

    mm::Vec3 pad_0;  // Initialize zeroes it
    // btl::CharacterManager::Register's for the enemy (the constructor: -1; Finalize releases it); 1.0.0's
    // GetCharacterParameterConst looks the character up by it (the name is not the original's)
    int m_characterIndex;
    // 1.0.0's GetReturnHomeDistance returns it outside battle (Initialize: -1.0; the name is not the original's)
    float m_returnHomeDistance;
    unsigned char pad_18[0x8];
};
}}  // namespace gf::enemy

#endif
