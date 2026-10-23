#ifndef CLASSES_GF_GFMENUREFERENCE_H
#define CLASSES_GF_GFMENUREFERENCE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace ui { class UIStr; }
namespace gf { class GfMenuReference; }
namespace gf { class GfMenuEnemyList; }
namespace gf { class GfMenuItemList; }

namespace gf {
// table 0x7100B5EF48
class GfMenuReference : public ::mm::mtl::PtrSingleton< ::gf::GfMenuReference> {
public:
    class REFLIST;
    // a route of the elemental combo the menu shows (8 bytes each, 7 of them; the names are not the original's)
    struct ElementComboRoot {
        unsigned int m_comboId;  // GfMenuElementComboAdapter::ReferenceRouteConverter's combo
        unsigned char pad_4[0x4];
    };
    // an arts palette slot's arts (the first fields of a 0x28-byte record; the names are not the original's):
    // GfMenuBattleAdapter's arts slot callbacks read them
    struct ArtsPaletteInfo {
        unsigned short m_artsId;  // 0 for an empty slot
        unsigned char pad_2[0x2];
        float m_recast;  // update_ArtsSlotRecast shows it in percent and the slot while it is above 0
    };
    // the icons of an arts palette slot (from 8 in the same record; the names are not the original's, they follow
    // the GfMenuBattleAdapter callbacks that show them)
    struct ArtsPaletteIconInfo {
        int m_type;      // update_ArtsSlotIconType
        int m_enhance;   // update_ArtsSlotIconEnhance
        int m_reaction;  // update_ArtsSlotIconReaction
        unsigned char pad_C[0x4];
        int m_range;     // update_ArtsSlotIconRange
    };
    virtual ~GfMenuReference();  // slot 0
    static void setReferenceString(ui::UIStr& text, unsigned short index);
    static unsigned int getReferenceDriverID(unsigned int index);
    static unsigned int getReferenceBladeID(unsigned int index);
    static unsigned int getReferenceZoneID();  // GfMenuZoneAdapter::ReferenceZoneConverter's zone
    static unsigned int getReferenceShopID();  // the shop the menu was opened for (GfMenuShopAdapter::ReferenceConverter)
    static unsigned int getReferenceWorldMapID();  // GfMenuWorldMapAdapter::ReferenceConverter's map
    // the number at an index, and its range (GfMenuGameAdapter::update_ReferenceNum)
    static int getReferenceNumber(unsigned int index);
    static int getReferenceNumberMin(unsigned int index);
    static int getReferenceNumberMax(unsigned int index);
    static const ElementComboRoot* getElementComboRootInfo(unsigned int route);  // a dummy past the 7th
    static int getElementComboRootCurrent();
    // the lists the link-jump menu shows (null without the singleton): its enemies and its items; clearLinkList
    // clears both (their slot 2)
    static void clearLinkList();
    static GfMenuEnemyList* getEnemyLinkList();
    static GfMenuItemList* getItemLinkList();  // the route the combo is on (GfMenuElementComboAdapter compares)
    // the arts palette's slots (0..8; a static dummy past them or without the singleton)
    static const ArtsPaletteInfo* getArtsPaletteInfo(unsigned char slot);
    static const ArtsPaletteIconInfo* getArtsPaletteIconInfo(unsigned char slot);
    static int getArtsPaletteElementType(unsigned char slot);  // GfMenuBattleAdapter formats "elemental%02d" from it
    static bool isArtsPaletteEnable(unsigned char slot);
    static unsigned int getArtsPaletteDisable(unsigned char slot);  // bit 0 and bit 1 hide the slot
    static int getChainNum();
    // the chain attack's numbers GfMenuBattleAdapter shows (the ratios in percent)
    static float getChainAttackActionRecast();
    static int getChainAttackActionCount();
    static float getChainAttackDamageRatio();
    static float getChainAttackExpRatio();
    static int getChainAttackTotalDamage();
    static int getChainAttackBurstCount();
    static float getAwakeningRestTimeRatio();
    static int getElementComboParty(unsigned int index);
    static float getElementComboPartyTimeLeft(unsigned int index);
    static bool isWeaponJustRange();
    static bool isReversePaletteBtnState(unsigned int slot, unsigned int state);
};
}  // namespace gf

#endif
