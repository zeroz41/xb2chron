#ifndef CLASSES_GF_GFMENUREFERENCE_H
#define CLASSES_GF_GFMENUREFERENCE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "ui/UIStr.h"
#include "mm/mtl/Bitflag.h"

namespace ui { class UIStr; }
namespace gf { class GfMenuReference; }
namespace gf { class GfMenuEnemyList; }
namespace gf { class GfMenuItemList; }
namespace gf { class MenuItemInfo; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B5EF48
class GfMenuReference : public ::mm::mtl::PtrSingleton< ::gf::GfMenuReference> {
public:
    static void setPartyStatusLock(unsigned int index, bool lock);  // 1.0.0 symbol
    // 1.0.0 symbol (GfMenuManager::gevBattleEnd passes 0 in 1.0.0 and 3.0.1); 3.0.1's copy still carries a
    // placeholder name (fn_71003670E4)
    static void setChainNum(unsigned int num);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its address lies in
    // gf_menu_reference's unit, between GfMenuReference's functions. What it does: GfMenuManager::gevBattleEnd
    // tail-calls it, without arguments, after GfMenuObjPartyGauge::close when GfMenuObjUtil::fn_710048FD30(3) holds.
    static void fn_7100367D1C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member: its address lies in
    // gf_menu_reference's unit and it reads PtrSingleton<GfMenuReference>::sys() only. What it does: copies four
    // values into the four 12-byte records at 0x4CF70 of the instance (each record: the value, 1, a cleared byte);
    // its one caller, btl::UIManager::Create, passes {0, 3, 1, 2}.
    static void fn_7100366074(const unsigned int* values);
    class REFLIST;
    // a route of the elemental combo the menu shows (8 bytes each, 7 of them; 1.0.0's setElemComboRootInfo names
    // the type, the field names are not the original's)
    struct ElemComboRoot {
        // getElementComboRootInfo's dummy is zeroed when first used
        ElemComboRoot() : m_comboId(), pad_4() {}
        unsigned int m_comboId;  // GfMenuElementComboAdapter::ReferenceRouteConverter's combo
        unsigned char pad_4[0x4];
    };
    // an arts palette slot's arts (the first fields of a 0x28-byte record; the names are not the original's):
    // GfMenuBattleAdapter's arts slot callbacks read them
    struct ArtsPaletteInfo {
        // getArtsPaletteInfo's dummy is zeroed when first used
        ArtsPaletteInfo() : m_artsId(), pad_2(), m_recast() {}
        unsigned short m_artsId;  // 0 for an empty slot
        unsigned char pad_2[0x2];
        float m_recast;  // update_ArtsSlotRecast shows it in percent and the slot while it is above 0
    };
    // the icons of an arts palette slot (from 8 in the same record; the names are not the original's, they follow
    // the GfMenuBattleAdapter callbacks that show them)
    struct ArtsPaletteIconInfo {
        // getArtsPaletteIconInfo's dummy is zeroed when first used
        ArtsPaletteIconInfo() : m_type(), m_enhance(), m_reaction(), pad_C(), m_range() {}
        int m_type;      // update_ArtsSlotIconType
        int m_enhance;   // update_ArtsSlotIconEnhance
        int m_reaction;  // update_ArtsSlotIconReaction
        unsigned char pad_C[0x4];
        int m_range;     // update_ArtsSlotIconRange
    };
    virtual ~GfMenuReference();  // slot 0
    static void setReferenceString(ui::UIStr& text, unsigned short index);
    // the text of the reference at that index (GfMenuTagAchievement::convBegin tests it valid before using it)
    static const ui::UIStr& getReferenceString(unsigned short index);
    static unsigned int getReferenceDriverID(unsigned int index);
    static unsigned int getReferenceBladeID(unsigned int index);
    // GfMenuFieldSkill::start sets slot 5 to 0 (the parameter names are not the original's)
    static void setReferenceBladeID(unsigned int index, unsigned int blade);
    static unsigned int getReferenceTeamID();  // GfMenuMercenariesAdapter::ReferenceTeamConverter's team
    static unsigned int getReferenceZoneID();  // GfMenuZoneAdapter::ReferenceZoneConverter's zone
    static unsigned int getReferenceShopID();  // the shop the menu was opened for (GfMenuShopAdapter::ReferenceConverter)
    static unsigned int getReferenceWorldMapID();  // GfMenuWorldMapAdapter::ReferenceConverter's map
    // the number at an index, and its range (GfMenuGameAdapter::update_ReferenceNum)
    static int getReferenceNumber(unsigned int index);
    static int getReferenceNumberMin(unsigned int index);
    static int getReferenceNumberMax(unsigned int index);
    static const ElemComboRoot* getElementComboRootInfo(unsigned int route);  // a dummy past the 7th
    static int getElementComboRootCurrent();
    // the lists the link-jump menu shows (null without the singleton): its enemies and its items; clearLinkList
    // clears both (their slot 2)
    static void clearLinkList();
    // add an enemy (a CHR_EnArrange row) or an item to the link-jump lists (GfMenuTagLink::convBegin)
    static void addEnemyLink(unsigned int enemy);
    static void addItemLink(const MenuItemInfo& item);
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
    // 1.0.0 symbols; the parameter names are not the original's
    static void setReversePaletteBtnState(unsigned int slot, unsigned int state, bool on);
    static void postReset();  // clears state 2 of every slot's reverse palette button
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's GfMenuObjItemList2::refreshItemList
    // has no call where 3.0.1's calls it). A member because its unit is gf_menu_reference and it reads this class's
    // singleton. What it does: the item type the menu references (an ItemType::Type, valid from 1 to 20: the
    // singleton's word at 0x4CCB8), 0 without the singleton; GfMenuGameAdapter's types 18 to 20, GfMenuObjItemList2's
    // and GfMenuObjHanaPartsMake's refreshItemList read it.
    static unsigned int fn_710036934C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its unit is
    // gf_menu_reference and it reads this class's singleton. What it does: the singleton's word at 0x4CCB4 (0 without
    // the singleton); gf_menu_btlch_adapter's callbacks pass it to GfGameManager::fn_71002AC60C as the record's mode
    // and its adapter's update marks itself changed when it changes.
    static unsigned int fn_7100369304();
    // the battle's Homura/Hikari mode the menu shows (1.0.0's enum; its values are not known)
    enum HOMURA_MODE {};
    // a party member's elemental combo (8 bytes each, 2 of them; the names are not the original's)
    struct ElementComboParty {
        unsigned int m_party;
        float m_timeLeft;
    };
    // a number the menu references and its range (12 bytes each, 8 of them; the names follow 1.0.0's accessors)
    struct ReferenceNumber {
        int m_min;
        int m_max;
        int m_number;
    };
    // an arts palette slot's record (0x28 bytes; the name is not the original's)
    struct ArtsPaletteSlot {
        ArtsPaletteInfo m_info;
        ArtsPaletteIconInfo m_iconInfo;
        int m_elementType;  // getArtsPaletteElementType
        bool m_enable;      // isArtsPaletteEnable; setArtsPaletteEnable sets it with the disable bits
        unsigned char pad_21[0x3];
        unsigned int m_disable;  // getArtsPaletteDisable
    };
    GfMenuReference(const GfSetupParam& param);
    void finalize();
    static void setArtsPaletteEnable(unsigned char slot, bool enable, unsigned int disable);
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isInitialized();
    static void resetDriverVirtual();
    static void resetBladeVirtual();
    static void setPaletteModeReverse(bool reverse);
    static void setWeaponJustRange(bool range);
    static void setAwakeningRestTimeRatio(float ratio);
    static void setChainAttackActionPartyID(int party);
    static int getChainAttackActionPartyID();
    static void setChainAttackDamageRatio(float ratio);
    static void setChainAttackTotalDamage(unsigned int damage);
    static void setChainAttackBurstCount(unsigned int count);
    static void setElementComboParty(unsigned int index, unsigned int party, float timeLeft);
    static void setHomuraModeInBattle(HOMURA_MODE mode);
    static HOMURA_MODE getHomuraModeInBattle();
    static void setReferenceDriverID(unsigned int index, unsigned int driver);
    static void setReferenceNumber(unsigned int index, int number);
    static void setReferenceTeamID(unsigned int team);
    static void setReferenceZoneID(unsigned int zone);
    static void setReferenceMissionID(unsigned int mission);
    static unsigned int getReferenceMissionID();
    static void setReferenceShopID(unsigned int shop);
    static void setReferenceWorldMapID(unsigned int map);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits between this
    // class's accessors and writes the word fn_710036934C reads. What it does: stores the item type (0x4CCB8).
    static void fn_710036932C(unsigned int type);
    static void setDriverVirtualLevel(unsigned int level);
    static unsigned int getDriverVirtualLevel();
    static void setDriverVirtualBladeID(unsigned int blade);
    static unsigned int getDriverVirtualBladeID();
    // 1.0.0 symbols (3.0.1's copies still carry placeholder names: fn_7100369404, fn_7100369424, fn_710036944C,
    // fn_710036946C; same place among the accessors, same fields, moved 0x10 like their neighbours)
    static void setDriverVirtualBladeSlot(unsigned int slot);
    static unsigned int getDriverVirtualBladeSlot();
    static void setDriverVirtualEquipAcc(unsigned int acc);
    static unsigned int getDriverVirtualEquipAcc();
    static void setDriverVirtualEquipAccSlot(unsigned int slot);
    static unsigned int getDriverVirtualEquipAccSlot();
    static void resetDriverAddIdeaLv();
    static void setDriverAddIdeaLv(unsigned int index, int level);
    static int getDriverAddIdeaLv(unsigned int index);
    static void setBladeVirtualEquipWpnChip(unsigned int chip);
    static unsigned int getBladeVirtualEquipWpnChip();
    static void setBladeVirtualEquipOrb(unsigned int orb);
    static unsigned int getBladeVirtualEquipOrb();
    static void setBladeVirtualEquipOrbSlot(unsigned int slot);
    static unsigned int getBladeVirtualEquipOrbSlot();
    static void clearPartyStatusLock();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (1.0.0 goes from
    // getChainAttackBurstCount to setElemComboRootInfo). Members because they sit between this class's accessors
    // and read or write its singleton's fields. What they do: fn_7100367360 stores m_chainAttackExtraNumber
    // (btl::UIManager::UpdateMenuData passes ChainAttackManager's halfword at 0x19FE), fn_7100367380 returns it
    // (0 without the singleton; GfMenuBattleAdapter::fn_71003331F8 shows it); fn_71003673A8 stores m_timeSeconds
    // (fn_71000255A8, fn_710002568C, fn_710002579C, fn_71000B233C), fn_71003673C8 returns it
    // (GfMenuBattleAdapter::fn_71003333D0); fn_71003673F0 stores m_challengeRatio clamped to 0..1
    // (GfMenuObjButtonChallenge2::seqRunningV2, seqMovePush, seqWaitMashingV2), fn_710036742C returns it
    // (GfMenuBattleAdapter::fn_710033355C).
    static void fn_7100367360(unsigned int number);
    static unsigned int fn_7100367380();
    static void fn_71003673A8(float seconds);
    static float fn_71003673C8();
    static void fn_71003673F0(float ratio);
    static float fn_710036742C();

    unsigned char pad_8[0x4CA38];
    bool m_initialized;  // isInitialized
    unsigned char pad_4CA41[0x7F];
    ArtsPaletteSlot m_artsPalette[3];  // slots 0..2
    unsigned char pad_4CB38[0x4];
    bool m_weaponJustRange;
    unsigned char pad_4CB3D[0x3];
    float m_awakeningRestTimeRatio;
    float m_chainAttackActionRecast;
    unsigned int m_chainAttackActionCount;
    int m_chainAttackActionPartyID;
    float m_chainAttackDamageRatio;
    float m_chainAttackExpRatio;
    unsigned int m_chainAttackTotalDamage;
    unsigned int m_chainAttackBurstCount;
    // fn_7100367360/fn_7100367380's number (the name is not the original's): btl::UIManager::UpdateMenuData sets
    // it from ChainAttackManager's halfword at 0x19FE after setChainAttackBurstCount; GfMenuBattleAdapter's entry
    // 17, between the chain attack ratios, shows it
    unsigned int m_chainAttackExtraNumber;
    unsigned char pad_4CB64[0xC];
    unsigned short m_chainNum;
    unsigned char pad_4CB72[0xE];
    HOMURA_MODE m_homuraModeInBattle;
    unsigned char pad_4CB84[0x4];
    bool m_paletteModeReverse;  // 1.0.0's isPaletteModeReverse reads it
    unsigned char pad_4CB89[0x3];
    // every arts palette's reverse button states (is/setReversePaletteBtnState; the name is not the original's)
    ::mm::mtl::Bitflag<8> m_reversePaletteBtnState[4];
    unsigned char pad_4CB9C[0x4];
    GfMenuEnemyList* m_enemyLinkList;
    GfMenuItemList* m_itemLinkList;
    ElemComboRoot m_elemComboRoot[7];  // getElementComboRootInfo
    ElementComboParty m_elementComboParty[2];
    unsigned char pad_4CBF8[0x8];
    unsigned int m_referenceDriverID[8];
    unsigned int m_referenceBladeID[8];
    ReferenceNumber m_referenceNumber[8];
    unsigned int m_referenceTeamID;
    unsigned int m_referenceZoneID;
    unsigned int m_referenceMissionID;
    unsigned int m_referenceShopID;
    unsigned int m_referenceWorldMapID;
    unsigned char pad_4CCB4[0x4];
    unsigned int m_referenceItemType;  // fn_710036934C's item type (the name is not the original's)
    unsigned int m_driverVirtualLevel;
    unsigned int m_driverVirtualBladeID;
    unsigned int m_driverVirtualBladeSlot;
    unsigned int m_driverVirtualEquipAcc;
    unsigned int m_driverVirtualEquipAccSlot;
    int m_driverAddIdeaLv[4];
    unsigned int m_bladeVirtualEquipWpnChip;
    unsigned int m_bladeVirtualEquipOrb;
    unsigned int m_bladeVirtualEquipOrbSlot;
    unsigned char pad_4CCEC[0x4];
    ui::UIStr m_referenceString[13];  // getReferenceString/setReferenceString
    ArtsPaletteSlot m_artsPaletteEx[6];  // slots 3..8
    unsigned int m_partyStatusLock;  // setPartyStatusLock's locks; clearPartyStatusLock clears them
    unsigned char pad_4CF1C[0x4];
    // fn_71003673A8/fn_71003673C8's seconds (the name is not the original's): GfMenuBattleAdapter::fn_71003333D0
    // shows them as minutes and seconds
    float m_timeSeconds;
    // fn_71003673F0/fn_710036742C's ratio, kept within 0..1 (the name is not the original's): set by
    // GfMenuObjButtonChallenge2's sequences, shown in percent by GfMenuBattleAdapter::fn_710033355C
    float m_challengeRatio;
    unsigned char pad_4CF28[0xD0];
};
}  // namespace gf

#endif
