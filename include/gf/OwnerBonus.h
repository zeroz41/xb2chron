#ifndef GF_OWNERBONUS_H
#define GF_OWNERBONUS_H

namespace gf {

// the owner bonuses the party's precious items grant, one sum per bonus type (GfGameUtil::getOwnerBonus adds an
// item's value to its type's entry, capped at the type's maximum)
struct OwnerBonus {
    short m_values[15];  // by bonus type; 11 widens the lure reach (isActiveRangeLure) (the name is not the original's)
    // MoveUtilField::getSpeedEffect adds it to type 1's value in hundredths for the run speed's rate;
    // GfGameUtil::getOwnerBonus leaves it (the name is not the original's)
    float m_speedRate;
};

}  // namespace gf

#endif
