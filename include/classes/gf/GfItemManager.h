#ifndef CLASSES_GF_GFITEMMANAGER_H
#define CLASSES_GF_GFITEMMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GfItemManager; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B56C48
class GfItemManager : public ::mm::mtl::PtrSingleton< ::gf::GfItemManager> {
public:
    GfItemManager(const GfSetupParam& param);
    virtual ~GfItemManager();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    // 1.0.0's: makes the item box singleton and sets it up (3.0.1 inlines it in the constructor)
    void initialize(const GfSetupParam& param);
    // 1.0.0's: deletes the item box singleton (3.0.1 inlines it in destroy)
    void finalize();

    bool m_initialized;  // inferred name: initialize sets it, finalize clears it (1.0.0's isInitialized reads it)
};

// 1.0.0's GfRecipeOrbUtil::getRecipeInfo(RecipeInfo&, unsigned int) fills it from the orb recipe BDAT. The field and
// struct names are inferred (not the original's); the getters' names are 1.0.0's.
struct RecipeInfo {
    // a result's value and its count (getOrbRecipeRarity / getOrbRecipeRscCat, getOrbRecipeAssortNumber)
    struct Result {
        unsigned short m_value;
        unsigned short m_number;
    };
    // an item result: getOrbRecipeItemID, getOrbRecipeItemNumber
    struct Item {
        unsigned short m_item;
        unsigned short m_number;
    };
    const Result& getResultRarity() const;
    const Result& getResultColleCategory() const;
    const ::mm::mtl::FixedVector<Item, 8>& getResultItems() const;

    unsigned int m_recipe;
    int m_recipeType;  // GfBdatItem::getOrbRecipeRecipeType: 0 rarity, 1 collectible category, 2 items
    Result m_resultRarity;
    Result m_resultColleCategory;
    ::mm::mtl::FixedVector<Item, 8> m_resultItems;
};
}  // namespace gf

#endif
