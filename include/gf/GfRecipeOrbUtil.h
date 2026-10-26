#ifndef GF_GFRECIPEORBUTIL_H
#define GF_GFRECIPEORBUTIL_H

#include "mm/mtl/FixedVector.h"


namespace gf {
// an item getRecipeItemsByItemBox takes from the box for a recipe: the item and how many (it stores
// item | count << 16). The struct name is 1.0.0's (its signatures); the field names are not the original's.
struct OrbRecipe {
    unsigned short m_item;
    unsigned short m_number;
};

// the orb (core crystal) recipes' helpers (functions, by its symbols)
class GfRecipeOrbUtil {
public:
    static bool getRecipeItemsByItemBox(::mm::mtl::FixedVector<OrbRecipe, 128>& items, unsigned int recipe);
    // GfBdatItem::getEmptyOrbRecipe of the item
    static unsigned int getRecipeID(unsigned int item);
    // GfBdatItem::getEmptyOrbEquipItemID of the item
    static unsigned int getEquipOrb(unsigned int item);
    // whether the item box holds what the recipe needs (getRecipeItemsByItemBox's answer)
    static bool isEnableRecipe(unsigned int recipe);
};
}  // namespace gf

#endif
