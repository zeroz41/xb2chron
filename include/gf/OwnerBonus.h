#ifndef GF_OWNERBONUS_H
#define GF_OWNERBONUS_H

namespace gf {

// the owner bonuses the party's precious items grant, one sum per bonus type (GfGameUtil::getOwnerBonus adds an
// item's value to its type's entry, capped at the type's maximum)
struct OwnerBonus {
    short m_values[15];  // by bonus type; 11 widens the lure reach (isActiveRangeLure) (the name is not the original's)
};

}  // namespace gf

#endif
