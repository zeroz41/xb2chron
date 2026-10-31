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
namespace gf { class GfMenuCallContext; }

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
    // what fn_7100367C78 answers: the 8 bytes after a record's driver word (+4 and +8 of the 0x10-byte records at
    // 0x4CF28; the names are not the original's). GfMenuCharDataAdapter::fn_7100339574 shows m_rate times 100 in
    // battle and, outside battle, maps m_type 2 / 1 to fn_7100368418(1) / fn_7100368418(0).
    struct DriverGauge {
        int m_type;
        float m_rate;
    };
    // a 0x10-byte record of the three at 0x4CF28 of the instance: a driver, then the gauge fn_7100367C78 answers
    // (the names are not the original's; GfMenuCharDataAdapter::ReferenceBladeOwnerDriverConverter shows the
    // driver; fn_7100367BD8 compares the gauge's first word, which it calls a blade, with its argument;
    // fn_7100367D1C clears every m_rate)
    struct BladeOwner {
        unsigned int m_driver;
        DriverGauge m_gauge;
        unsigned char pad_C[0x4];
    };
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's
    // ReferenceBladeOwnerDriverConverter::getCharData read GfDataBlade::getSetDriver(getReferenceBladeID(index)) there).
    // A member because it sits among GfMenuReference's accessors and reads its singleton. What it does: when
    // GfMenuObjUtil::fn_710048FD30(3) holds and the singleton exists, the first of the three records at 0x4CF28
    // (0x10 apart) whose blade (+4) is the argument, else nullptr.
    static const BladeOwner* fn_7100367BD8(unsigned int blade);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among
    // GfMenuReference's accessors (between fn_7100367BD8 and fn_7100367D1C) and reads its singleton. What it does:
    // nullptr unless GfMenuObjUtil::fn_710048FD30(3) holds and the singleton exists; else the address of the +4 word
    // of the first of the three records at 0x4CF28 (0x10 apart) whose +0 word is the argument (a driver id from
    // GfMenuCharDataAdapter::fn_7100339574), nullptr when none is.
    static const DriverGauge* fn_7100367C78(unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among
    // GfMenuReference's accessors (after fn_7100367BD8) and reads its singleton. What it does: -1 unless
    // GfMenuObjUtil::fn_710048FD30(3) holds and the singleton exists; else the +4 word of the first of the three
    // records at 0x4CF28 (0x10 apart) whose +0 word is the argument, 0xFF when none is. GfMenuCharDataAdapter's
    // fn_71003391AC / fn_7100339224 / fn_710033929C pass it a driver id and compare the answer with 0, 1 and 2.
    static int fn_7100367EF4(unsigned int driver);
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among this
    // class's accessors and writes its singleton. What it does: stores the word fn_7100369304 reads (0x4CCB4);
    // callers fn_71003ADAD0, fn_71003AE838, fn_7100445830, fn_7100445F58.
    static void fn_71003692E4(unsigned int mode);
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
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Static members: their addresses lie
    // among this class's accessors (after fn_710036742C) and they read or write its singleton's word at 0x4CB84
    // (m_bladeChangeValue). fn_7100367454 stores it and, when it changed, calls GfMenuObjBladeChange::fn_7100391CDC
    // (event 0x105 to the blade change object); fn_71003674A0 returns it (callers BladeListener::reciveEvent,
    // fn_7100391EF0, fn_71003C56C0).
    static void fn_7100367454(unsigned int value);
    static unsigned int fn_71003674A0();
    // Records the layer-3 battle menu reads (the names and their fields' names are not the original's).
    // fn_7100366074's and fn_71003680AC's: four 12-byte records at 0x4CF70 of the instance (the names are not the
    // original's): a value, 4 flags (fn_710036816C sets, fn_71003682D8 tests; fn_7100366074 starts them at 1) and a
    // byte fn_7100366074 clears
    struct LayerCommand {
        unsigned int m_value;
        ::mm::mtl::Bitflag<4> m_flags;
        unsigned char m_state;
        unsigned char pad_9[0x3];
    };
    // fn_71003686A0's: two 8-byte records at 0x4CFA4 of the instance (a zeroed static one when the index is 2 or
    // more, there is no instance or menu layer 3 is not up).
    struct LayerGauge {
        LayerGauge() : m_ratio(), m_count(), m_stateA(), m_stateB() {}
        float m_ratio;          // GfMenuBattleAdapter::fn_71003336A0 shows it in percent
        unsigned char m_count;  // GfMenuBattleAdapter::fn_7100333700/fn_7100333750 show it (0..5)
        // fn_7100368570's and fn_7100368600's flags: changing them sends the party gauge's "LAY_siren" (record 0)
        // or "LAY_gauge" (record 1) events (GfMenuObjPartyGauge::fn_7100456EA0 etc.); the names are not the original's
        bool m_stateA;
        bool m_stateB;
        // no explicit tail member: fn_71003686A0's guarded dummy zeroes 7 bytes and is not merged with the file's
        // other statics, as the original's (an explicit pad byte here lets GlobalMerge take it)
    };
    // fn_71003687B0's: three 8-byte records at 0x4CFB4 of the instance (a zeroed static one otherwise)
    struct LayerGimmick {
        LayerGimmick() : m_gimmickId(), m_ratio() {}
        unsigned int m_gimmickId;  // a type-3 DataParamAcc's id (face icon, name, attribute icon)
        float m_ratio;             // GfMenuBattleAdapter::fn_710033383C shows it in percent
    };
    // fn_7100368B40's: the record at 0x4CFE4 of the instance (a zeroed static one without the instance)
    struct LayerResult {
        LayerResult() : m_number(), m_ratio(), m_numbers() {}
        unsigned int m_number;      // GfMenuBattleAdapter::fn_71003339D0 (0..999)
        float m_ratio;              // GfMenuBattleAdapter::fn_7100333A00, in percent
        unsigned int m_numbers[3];  // GfMenuBattleAdapter::fn_7100333A40, by m_index
    };
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they sit among this
    // class's accessors in gf_menu_reference and read its singleton's fields (all but fn_7100368B40 only while
    // GfMenuObjUtil::fn_710048FD30(3), menu layer 3, holds). What they do: fn_7100367FDC returns the float at
    // 0x4CF64 (0 otherwise; GfMenuBattleAdapter::fn_71003335AC shows it in percent); fn_710036805C returns the int
    // at 0x4CF68 (0 otherwise; GfMenuBattleAdapter::fn_7100333630 shows it, fn_71003335AC compares m_index with
    // it); fn_7100368418 tests bit `bit` (asserting bit < 32) of the word at 0x4CFA0 (GfMenuBattleAdapter
    // fn_7100333674 asks bit 3, fn_71003336A0/fn_7100333700/fn_7100333750 bit 4); fn_71003686A0, fn_71003687B0 and
    // fn_7100368B40 return the records above.
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they sit among this
    // class's accessors in gf_menu_reference and write its singleton's fields, only while
    // GfMenuObjUtil::fn_710048FD30(3) holds. What they do (btl::UIManager::UpdateMenuData calls each):
    // fn_7100367F98 stores the float at 0x4CF64 (fn_7100367FDC reads it); fn_7100368018 the int at 0x4CF68
    // (fn_710036805C reads it); fn_710036810C the flag at 0x4CF6C, calling TUnk_B60E28::fn_71003C3550(flag) when
    // it changes (also from fn_7100358F74); fn_7100368380 sets or clears bit `bit` (< 32) of the word at 0x4CFA0
    // (also from GfMenuManager::gevPlayerControl, GfMenuObjMainMenu2::seqExecTerm); fn_7100368498 stores record
    // `index`'s (< 2) ratio at 0x4CFA4 clamped to 0..1; fn_710036851C its count byte (+4).
    // fn_71003680AC returns record `index`'s (< 4) value at 0x4CF70 (0 otherwise) and fn_71003682D8 tests its flag
    // `flag` (both from fn_71003C662C).
    static void fn_7100367F98(float ratio);
    static void fn_7100368018(int index);
    static void fn_710036810C(bool flag);
    static void fn_7100368380(unsigned int bit, bool on);
    static void fn_7100368498(float ratio, unsigned int index);
    static void fn_710036851C(unsigned int index, unsigned char count);
    // fn_7100368744 stores record `index`'s (< 3) gimmick id and ratio at 0x4CFB4; fn_7100368570 / fn_7100368600
    // store record `index`'s (< 2) m_stateA / m_stateB, calling GfMenuObjPartyGauge's event senders when it changes.
    static void fn_7100368744(unsigned int index, unsigned int gimmickId, float ratio);
    static void fn_7100368570(unsigned int index, bool on);
    static void fn_7100368600(unsigned int index, bool on);
    static unsigned int fn_71003680AC(unsigned int index);
    static bool fn_71003682D8(unsigned int index, unsigned int flag);
    static float fn_7100367FDC();
    static int fn_710036805C();
    static bool fn_7100368418(unsigned int bit);
    static const LayerGauge* fn_71003686A0(unsigned int index);
    static const LayerGimmick* fn_71003687B0(unsigned int index);
    static const LayerResult* fn_7100368B40();
    // a 0x10-byte record at 0x4CFD4 of the instance (the names are not the original's): three words and two bytes
    // the combo route display (gf_menu_obj_combo_route_simple, fn_71003DC6FC) reads through fn_71003689C0.
    // fn_71003688E0 copies one in (an assignment copies its 14 data bytes), fn_7100368830 clears it; both refresh
    // the display (TUnk_B61408::fn_71003DC56C) when it changed.
    struct ComboRouteState {
        ComboRouteState() : m_values(), m_stateA(), m_stateB() {}
        bool operator==(const ComboRouteState& other) const {
            return m_values[0] == other.m_values[0] && m_values[1] == other.m_values[1] &&
                   m_values[2] == other.m_values[2] && m_stateA == other.m_stateA && m_stateB == other.m_stateB;
        }
        unsigned int m_values[3];
        unsigned char m_stateA;
        unsigned char m_stateB;
    };
    // the two words fn_7100368BAC forwards to TUnk_B63AE0::fn_7100448F44 (event 0x21 to LAY_result; the names are
    // not the original's)
    struct ResultPair {
        unsigned int m_first;
        unsigned int m_second;
    };
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Static members: their addresses lie
    // among this class's accessors (after fn_7100368830) and they read its singleton or forward to the menu objects
    // the reference feeds.
    // fn_7100368830: clears m_comboRoute (fn_71003688E0 with an empty record); caller btl::UIManager::UpdateMenuData.
    static void fn_7100368830();
    // fn_71003688E0: when fn_710048FD30(3) holds, copies state into m_comboRoute and, if it changed, tail-calls
    // TUnk_B61408::fn_71003DC56C (event 0x100 to attached object 0x8E); caller btl::UIManager::UpdateMenuData.
    static void fn_71003688E0(const ComboRouteState& state);
    // fn_71003689C0: m_comboRoute when fn_710048FD30(3) holds and the singleton exists, else a zeroed static dummy;
    // caller fn_71003DC6FC (gf_menu_obj_combo_route_simple).
    static const ComboRouteState* fn_71003689C0();
    // fn_7100368A44 / fn_7100368A48: tail-call TUnk_B63AE0::fn_7100448E58 (open LAY_special of object 0x90) /
    // fn_7100448ED4 (close it); caller fn_7100008554 (A48 also fn_7100009484).
    static void fn_7100368A44();
    static void fn_7100368A48();
    // fn_7100368A4C: copies result into m_layerResult, clamps its numbers to 999 and its ratio to 1.0 and, when
    // the ratio rose, tail-calls TUnk_B63AE0::fn_7100448FFC (event 0x102 to LAY_special); caller
    // btl::UIManager::UpdateMenuData.
    static void fn_7100368A4C(const LayerResult& result);
    // fn_7100368BAC: tail-calls TUnk_B63AE0::fn_7100448F44(context, pair's two words); caller fn_7100008554.
    static void fn_7100368BAC(GfMenuCallContext* context, const ResultPair& pair);

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
    // fn_7100367454 stores it, refreshing GfMenuObjBladeChange's display (fn_7100391CDC) when it changes;
    // fn_71003674A0 returns it (0 without the singleton; GfMenuObjBladeChange::BladeListener::reciveEvent reads it).
    // The name is not the original's.
    unsigned int m_bladeChangeValue;
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
    unsigned int m_challengeBattleMode;  // fn_71003692E4/fn_7100369304 (the name is not the original's)
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
    // the layer-3 battle menu's state (btl::UIManager::UpdateMenuData sets it through the accessors above; the
    // names are not the original's)
    BladeOwner m_bladeOwner[3];  // fn_7100367BD8, fn_7100367C78, fn_7100367EF4, fn_7100367D1C
    unsigned char pad_4CF58[0xC];
    float m_layerRatio;  // fn_7100367F98/fn_7100367FDC
    int m_layerIndex;    // fn_7100368018/fn_710036805C
    bool m_layerFlag;    // fn_710036810C
    unsigned char pad_4CF6D[0x3];
    LayerCommand m_layerCommand[4];
    ::mm::mtl::Bitflag<32> m_layerBits;  // fn_7100368380/fn_7100368418
    LayerGauge m_layerGauge[2];          // fn_7100368498, fn_710036851C, fn_71003686A0
    LayerGimmick m_layerGimmick[3];      // fn_71003687B0
    unsigned char pad_4CFCC[0x8];
    ComboRouteState m_comboRoute;  // fn_7100368830, fn_71003688E0, fn_71003689C0
    LayerResult m_layerResult;  // fn_7100368B40
};
}  // namespace gf

#endif
