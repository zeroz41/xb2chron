#ifndef CLASSES_GF_GFMENUBLADELIST_H
#define CLASSES_GF_GFMENUBLADELIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// a GfMenuBladeList's content (0xC bytes): a blade and how the list shows it
class MenuBladeInfo {
public:
    // GfMenuBladeList::create zeroes the first two words of the list's m_dummy and leaves the third
    MenuBladeInfo() : m_blade(0), m_creator(0) {}
    unsigned int m_blade;  // GfDataBlade's blade id (GfMenuMercenariesAdapter::update_TeamStrength)
    // GfDataBlade::getCreator's for the blade (GfMenuBladeList::updateOwner stores it; the name is not the original's)
    unsigned int m_creator;
    unsigned char pad_8[0x4];
};
}  // namespace gf

namespace gf {
// table 0x7100B5F180
class GfMenuBladeList : public ::ui::UIListInfo< ::gf::MenuBladeInfo> {
public:
    virtual ~GfMenuBladeList();  // slot 0
    static GfMenuBladeList* create();
    // setupFromReleasble passes it on to setup as its SetupParam
    struct ReleasbleSetup : public ::ui::UIListInfoBase::SetupParam {};
    // the blades that can be released (GfMenuObjBladeRelease::initialize)
    void setupFromReleasble(const ReleasbleSetup& setup);
    void updateOwner();
    static bool sortTimeAscending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortTimeDescending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortNameDescending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortNameAscending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortRarityAscending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortRarityDescending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortWeaponAscending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortWeaponDescending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortAttrAscending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortAttrDescending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    // Placeholder names (this pair and the two pairs below): new in 3.0.1, nothing in 1.0.0's place names them
    // (1.0.0's sort has sortCreatorAscending/Descending where 3.0.1 has none). Members because they sit between
    // GfMenuBladeList's sort functions with their signature. What they do: order by the creator's rank (a switch
    // on m_creator 1-6 giving 0, 1, 5, 2, 3, 4; 6 otherwise), then attribute ascending, then rarity and rank
    // descending, then blade id. The two bodies are the same.
    static bool fn_710036DCE8(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool fn_710036DDCC(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortGenderDescending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool sortGenderAscending(const MenuBladeInfo& a, const MenuBladeInfo& b);
    // What they do: blades of an active mercenary team (GfDataBlade::isActivateMercenaryTeam) first (fn_710036DF68)
    // or last (fn_710036DFF0), then born time descending, then blade id.
    static bool fn_710036DF68(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool fn_710036DFF0(const MenuBladeInfo& a, const MenuBladeInfo& b);
    // What they do: order by trust rank (GfDataBlade::getTrustRank) ascending, then rarity and rank descending,
    // then blade id. The two bodies are the same.
    static bool fn_710036E078(const MenuBladeInfo& a, const MenuBladeInfo& b);
    static bool fn_710036E10C(const MenuBladeInfo& a, const MenuBladeInfo& b);
};
}  // namespace gf

#endif
