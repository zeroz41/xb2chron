#ifndef CLASSES_GF_GFMENUREFERENCE_H
#define CLASSES_GF_GFMENUREFERENCE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "ui/UIStr.h"
#include "mm/mtl/Bitflag.h"
#include "mm/mtl/FixedList.h"
#include "gf/GfMenuItemUtil.h"

namespace ui { class UIStr; }
namespace gf { class GfMenuReference; }
namespace gf { class GfMenuEnemyList; }
namespace gf { class GfMenuItemList; }
namespace gf { class MenuItemInfo; }
namespace gf { class GfSetupParam; }
namespace gf { class GfMenuCallContext; }
namespace gf { enum GFDIFF : int; }  // the game difficulty (2.0.0's symbols name it; its values are not known)

namespace gf {
// table 0x7100B5EF48
class GfMenuReference : public ::mm::mtl::PtrSingleton< ::gf::GfMenuReference> {
public:
    static void setPartyStatusLock(unsigned int index, bool lock);  // 1.0.0 symbol
    // 1.0.0 symbol (GfMenuManager::gevBattleEnd passes 0 in 1.0.0 and 3.0.1); 3.0.1's copy still carries a
    // placeholder name (fn_71003670E4)
    static void setChainNum(unsigned int num);
    // 2.0.0's symbols name it. What it does: GfMenuManager::gevBattleEnd tail-calls it, without arguments, after
    // GfMenuObjPartyGauge::close when GfMenuObjUtil::isValidExpansion(3) holds.
    static void resetIraCharRecast();
    // the four operation buttons' commands setupIraOperation copies (2.0.0's symbols name the type; the layout is
    // the four words setupIraOperation reads, the field name is not the original's)
    struct IraOperationBtnSetting {
        unsigned int m_command[4];
    };
    // 2.0.0's symbols name it. What it does: copies the setting's four values into the four 12-byte records at
    // 0x4CF70 of the instance (each record: the value, 1, a cleared byte); its one caller, btl::UIManager::Create,
    // passes {0, 3, 1, 2}.
    static void setupIraOperation(const IraOperationBtnSetting& values);
    class REFLIST;
    // a route of the elemental combo the menu shows (8 bytes each, 7 of them; 1.0.0's setElemComboRootInfo names
    // the type, the field names are not the original's)
    struct ElemComboRoot {
        // getElementComboRootInfo's dummy is zeroed when first used
        ElemComboRoot() : m_comboId(), m_flags() {}
        unsigned int m_comboId;  // GfMenuElementComboAdapter::ReferenceRouteConverter's combo
        // copied through Bitflag's operator= (setElemComboRootInfo); the flags' meaning and the name are not known
        ::mm::mtl::Bitflag<32> m_flags;
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
    // what getIraCharProperty answers: the 8 bytes after a record's driver word (+4 and +8 of the 0x10-byte records at
    // 0x4CF28; 2.0.0's symbols name the type, the field names are not the original's).
    // GfMenuCharDataAdapter::update_IRA_ChangeRecast shows m_rate times 100 in battle and, outside battle, maps m_type
    // 2 / 1 to isIraFlag(1) / isIraFlag(0).
    struct IraCharProperty {
        int m_type;
        float m_rate;
        // copied through Bitflag's operator= (setIraCharInfo, setIraCharProperty); the flags' meaning and the name are
        // not known
        ::mm::mtl::Bitflag<32> m_flags;
    };
    // a 0x10-byte record of the three at 0x4CF28 of the instance: a driver, then the gauge getIraCharProperty answers
    // (2.0.0's symbols name the type, the field names are not the original's; the adapter's
    // GfMenuCharDataAdapter::ReferenceBladeOwnerDriverConverter shows the
    // driver; getIraCharInfoFromFromID compares the gauge's first word, which it calls a blade, with its argument;
    // resetIraCharRecast clears every m_rate)
    struct IraCharInfo {
        unsigned int m_driver;
        IraCharProperty m_gauge;
    };
    // 2.0.0's symbols name it. What it does: when GfMenuObjUtil::isValidExpansion(3) holds and the singleton exists,
    // the first of the three records at 0x4CF28 (0x10 apart) whose blade (+4) is the argument, else nullptr.
    static const IraCharInfo* getIraCharInfoFromFromID(unsigned int blade);
    // 2.0.0's symbols name it. What it does: nullptr unless GfMenuObjUtil::isValidExpansion(3) holds and the singleton
    // exists; else the address of the +4 word of the first of the three records at 0x4CF28 (0x10 apart) whose +0 word
    // is the argument (a driver id from GfMenuCharDataAdapter::update_IRA_ChangeRecast), nullptr when none is.
    static const IraCharProperty* getIraCharProperty(unsigned int driver);
    // 2.0.0's symbols name it. What it does: -1 unless GfMenuObjUtil::isValidExpansion(3) holds and the singleton
    // exists; else the +4 word of the first of the three records at 0x4CF28 (0x10 apart) whose +0 word is the argument,
    // 0xFF when none is. GfMenuCharDataAdapter's update_IRA_IsFrontBtl / update_IRA_IsBackBtl /
    // update_IRA_NotReserveBtl pass it a driver id and compare the answer with 0, 1 and 2.
    static int getIraCharForm(unsigned int driver);
    // 2.0.0's symbols name it. What it does: false unless GfMenuObjUtil::isValidExpansion(3) holds, slot < 3 and the
    // singleton exists; else whether the record at 0x4CF28 + slot * 0x10 differs from the argument in its first two
    // words, then copies the argument into it. Its one caller, GfMenuManager::gevChangeParty, passes slots 0-2 with
    // {driver of party slot, slot} or {0, 0xFF} when the slot has no driver.
    static bool setIraCharInfo(unsigned int slot, const IraCharInfo& owner);
    // 2.0.0's symbols name it. What it does: while GfMenuObjUtil::isValidExpansion(3) holds, copies the gauge into the
    // record of that driver; a gauge type whose bit (1 << type) is new in m_gaugeTypeBits and differs from the record's
    // sets it, then GfMenuObjCharChange::changeFormation when bits 0 and 1 are both set, changeBlade when bit 2 is. Its
    // one caller is btl::UIManager::UpdateMenuData.
    static void setIraCharProperty(unsigned int driver, const IraCharProperty& gauge);
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
    // 1.0.0's symbol; stores a route when it is below 7 and the singleton exists (btl::UIManager::UpdateMenuData)
    static void setElemComboRootInfo(unsigned int route, const ElemComboRoot& info);
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
    // the blade set `party`'s driver puts `slot` on (set + slot wrapped at getBladeSlotMax; the set is the one the
    // battle started with in battle, the slot of blade 1001 for driver 1's sets 3 and 4), -1 for an invalid driver
    // or slot (1.0.0 symbol; the parameter names are not the original's)
    static int getBladeSetIDFromParty(unsigned int party, unsigned int slot);
    static void postReset();  // clears state 2 of every slot's reverse palette button
    // 2.0.0's symbols name it. What it does: the item type the menu references (an ItemType::Type, valid from 1 to 20:
    // the singleton's word at 0x4CCB8), 0 without the singleton; GfMenuGameAdapter's types 18 to 20,
    // GfMenuObjItemList2's and GfMenuObjHanaPartsMake's refreshItemList read it.
    static unsigned int getReferenceItemType();
    // 2.0.0's symbols name it. What it does: the singleton's word at 0x4CCB4 (0 without the singleton);
    // gf_menu_btlch_adapter's callbacks pass it to GfGameManager::fn_71002AC60C as the record's mode and its adapter's
    // update marks itself changed when it changes.
    static unsigned int getReferenceBtlchDifficulty();
    // 2.0.0's symbols name it. What it does: stores the word getReferenceBtlchDifficulty reads (0x4CCB4); callers
    // fn_71003ADAD0, refreshDifficulty, fn_7100445830, updateNamedIDList.
    static void setReferenceBtlchDifficulty(GFDIFF mode);
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
    // a virtual blade's equipped orb and the orb's slot (8 bytes; the names are not the original's)
    struct BladeVirtualOrb {
        unsigned int m_orb;
        unsigned int m_slot;
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
    // 2.0.0's symbols name it. What it does: stores the item type getReferenceItemType reads (0x4CCB8).
    static void setReferenceItemType(ItemType::Type type);
    static void setDriverVirtualLevel(unsigned int level);
    static unsigned int getDriverVirtualLevel();
    static void setDriverVirtualBladeID(unsigned int blade);
    static unsigned int getDriverVirtualBladeID();
    // 1.0.0 symbols (3.0.1's copies still carry placeholder names: fn_7100369404, fn_7100369424, fn_710036944C,
    // getDriverVirtualEquipAcc; same place among the accessors, same fields, moved 0x10 like their neighbours)
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
    // 2.0.0's symbols name them. What they do: setChainAttackOverkillBonus stores m_chainAttackExtraNumber
    // (btl::UIManager::UpdateMenuData passes ChainAttackManager's halfword at 0x19FE), getChainAttackOverkillBonus
    // returns it (0 without the singleton; GfMenuBattleAdapter::update_ChainAttackOverkillBonus shows it);
    // setBattleTime stores m_timeSeconds (Start, End, Retry, UpdateBattleTime), getBattleTime returns it
    // (GfMenuBattleAdapter::update_BattleTime); setVisionTimeRatio stores m_challengeRatio clamped to 0..1
    // (GfMenuObjButtonChallenge2::seqRunningV2, seqMovePush, seqWaitMashingV2), getVisionTimeRatio returns it
    // (GfMenuBattleAdapter::update_VisionTimeRatio).
    static void setChainAttackOverkillBonus(unsigned int number);
    static unsigned int getChainAttackOverkillBonus();
    static void setBattleTime(float seconds);
    static float getBattleTime();
    static void setVisionTimeRatio(float ratio);
    static float getVisionTimeRatio();
    // the battle mode setBattleMode stores (2.0.0's symbols name the enum; its values are not known)
    enum BTL_MODE {};
    // 2.0.0's symbols name them. What they do: they read or write the singleton's word at 0x4CB84
    // (m_bladeChangeValue). setBattleMode stores it and, when it changed, calls GfMenuObjBladeChange::refreshBattleMode
    // (event 0x105 to the blade change object); getBattleMode returns it (callers BladeListener::reciveEvent,
    // TUnk_B5FEE8::reciveEvent, GfMenuObjCharChange::MainListener::reciveEvent).
    static void setBattleMode(BTL_MODE value);
    static unsigned int getBattleMode();
    // an operation button (one of the four records below) and a button's state (one of a record's four flags); 2.0.0's
    // symbols name both enums, their values are not known. The button's type is unsigned: isIraOperationBtnState
    // compares it unsigned and zero-extends it (the fixed underlying type is inferred from that)
    enum IRA_OPERATION_BTN : unsigned int {};
    enum BTN_STATUS {};
    // Records the layer-3 battle menu reads (the names and their fields' names are not the original's).
    // setupIraOperation's and getIraOperationBtnCommand's: four 12-byte records at 0x4CF70 of the instance (the names
    // are not the original's): a value, 4 flags (setIraOperationBtnState sets, isIraOperationBtnState tests;
    // setupIraOperation starts them at 1) and a byte setupIraOperation clears
    struct LayerCommand {
        unsigned int m_value;
        ::mm::mtl::Bitflag<4> m_flags;
        unsigned char m_state;
        unsigned char pad_9[0x3];
    };
    // getIraSirenInfo's: two 8-byte records at 0x4CFA4 of the instance (a zeroed static one when the index is 2 or
    // more, there is no instance or menu layer 3 is not up).
    struct LayerGauge {
        LayerGauge() : m_ratio(), m_count(), m_stateA(), m_stateB() {}
        float m_ratio;          // GfMenuBattleAdapter::update_IraSirenGaugeEN shows it in percent
        unsigned char m_count;  // GfMenuBattleAdapter::update_IraSirenLvPT/update_IraSirenLvEN show it (0..5)
        // setIraSirenInfoDown's and setIraSirenInfoCompete's flags: changing them sends the party gauge's "LAY_siren"
        // (record 0) or "LAY_gauge" (record 1) events (GfMenuObjPartyGauge::setLockSirenEN etc.); the names are not the
        // original's
        bool m_stateA;
        bool m_stateB;
        // no explicit tail member: getIraSirenInfo's guarded dummy zeroes 7 bytes and is not merged with the file's
        // other statics, as the original's (an explicit pad byte here lets GlobalMerge take it)
    };
    // getIraChainInfo's: three 8-byte records at 0x4CFB4 of the instance (a zeroed static one otherwise)
    struct LayerGimmick {
        LayerGimmick() : m_gimmickId(), m_ratio() {}
        unsigned int m_gimmickId;  // a type-3 DataParamAcc's id (face icon, name, attribute icon)
        float m_ratio;             // GfMenuBattleAdapter::update_IraChainRecast shows it in percent
    };
    // getOCGInfo's: the record at 0x4CFE4 of the instance (a zeroed static one without the instance; 2.0.0's symbols
    // name the type, the field names are not the original's)
    struct OCGInfo {
        OCGInfo() : m_number(), m_ratio(), m_numbers() {}
        unsigned int m_number;      // GfMenuBattleAdapter::update_OCGGearCount (0..999)
        float m_ratio;              // GfMenuBattleAdapter::update_OCGTimeRatio, in percent
        unsigned int m_numbers[3];  // GfMenuBattleAdapter::update_OCGBonus, by m_index
    };
    // 2.0.0's symbols name them. What they do: getIraSpecialArtsRecast returns the float at 0x4CF64 (0 otherwise;
    // GfMenuBattleAdapter::update_IraSpecialRecast shows it in percent); getIraSpecialArtsLv returns the int at 0x4CF68
    // (0 otherwise; GfMenuBattleAdapter::update_IraSpecialLv shows it, update_IraSpecialRecast compares m_index with
    // it); isIraFlag tests bit `bit` (asserting bit < 32) of the word at 0x4CFA0 (GfMenuBattleAdapter
    // update_IraTalentArtsEnable asks bit 3, update_IraSirenGaugeEN/update_IraSirenLvPT/update_IraSirenLvEN bit 4);
    // getIraSirenInfo, getIraChainInfo and getOCGInfo return the records above. The setters write the singleton's
    // fields only while GfMenuObjUtil::isValidExpansion(3) holds (btl::UIManager::UpdateMenuData calls each):
    // setIraSpecialArtsRecast stores the float at 0x4CF64
    // (getIraSpecialArtsRecast reads it); setIraSpecialArtsLv the int at 0x4CF68 (getIraSpecialArtsLv reads it);
    // setIraOperationDisp the flag at 0x4CF6C, calling GfMenuObjCharChange::reverse(flag) when it changes (also from
    // GfMenuManager::changeBattleState); setIraFlag sets or clears bit `bit` (< 32) of the word at 0x4CFA0 (also from
    // GfMenuManager::gevPlayerControl, GfMenuObjMainMenu2::seqExecTerm); setIraSirenInfoGauge stores record
    // `index`'s (< 2) ratio at 0x4CFA4 clamped to 0..1; setIraSirenInfoLv its count byte (+4).
    // getIraOperationBtnCommand returns record `index`'s (< 4) value at 0x4CF70 (0 otherwise) and
    // isIraOperationBtnState tests its flag `flag` (both from GfMenuObjCharChange::CommandListener::reciveEvent).
    static void setIraSpecialArtsRecast(float ratio);
    static void setIraSpecialArtsLv(unsigned int index);
    static void setIraOperationDisp(bool flag);
    static void setIraFlag(unsigned int bit, bool on);
    static void setIraSirenInfoGauge(unsigned int index, float ratio);
    static void setIraSirenInfoLv(unsigned int index, unsigned char count);
    // setIraChainInfo stores record `index`'s (< 3) gimmick id and ratio at 0x4CFB4; setIraSirenInfoDown /
    // setIraSirenInfoCompete store record `index`'s (< 2) m_stateA / m_stateB, calling GfMenuObjPartyGauge's event
    // senders when it changes.
    static void setIraChainInfo(unsigned int index, unsigned int gimmickId, float ratio);
    static void setIraSirenInfoDown(unsigned int index, bool on);
    static void setIraSirenInfoCompete(unsigned int index, bool on);
    static unsigned int getIraOperationBtnCommand(unsigned int index);
    static bool isIraOperationBtnState(IRA_OPERATION_BTN index, BTN_STATUS flag);
    static float getIraSpecialArtsRecast();
    static int getIraSpecialArtsLv();
    static bool isIraFlag(unsigned int bit);
    static const LayerGauge* getIraSirenInfo(unsigned int index);
    static const LayerGimmick* getIraChainInfo(unsigned int index);
    static const OCGInfo* getOCGInfo();
    // a 0x10-byte record at 0x4CFD4 of the instance (the names are not the original's): three words and two bytes
    // the combo route display (gf_menu_obj_combo_route_simple, TUnk_B61450::reciveEvent) reads through getIraBladeComboInfo.
    // updateIraBladeCombo copies one in (an assignment copies its 14 data bytes), resetIraBladeCombo clears it; both
    // refresh the display (GfMenuObjComboRouteSimple::refresh) when it changed. 2.0.0's symbols name the type.
    struct IraBladeComboInfo {
        IraBladeComboInfo() : m_values(), m_stateA(), m_stateB() {}
        bool operator==(const IraBladeComboInfo& other) const {
            return m_values[0] == other.m_values[0] && m_values[1] == other.m_values[1] &&
                   m_values[2] == other.m_values[2] && m_stateA == other.m_stateA && m_stateB == other.m_stateB;
        }
        unsigned int m_values[3];
        unsigned char m_stateA;
        unsigned char m_stateB;
    };
    // the two words startOCGResult forwards to GfMenuObjOCG::openResult (event 0x21 to LAY_result; 2.0.0's symbols
    // name the type, the field names are not the original's)
    struct OCGResult {
        unsigned int m_first;
        unsigned int m_second;
    };
    // 2.0.0's symbols name them. What they do: they read the singleton or forward to the menu objects the reference
    // feeds.
    // resetIraBladeCombo: clears m_comboRoute (updateIraBladeCombo with an empty record); caller
    // btl::UIManager::UpdateMenuData.
    static void resetIraBladeCombo();
    // updateIraBladeCombo: when isValidExpansion(3) holds, copies state into m_comboRoute and, if it changed,
    // tail-calls GfMenuObjComboRouteSimple::refresh (event 0x100 to attached object 0x8E); caller
    // btl::UIManager::UpdateMenuData.
    static void updateIraBladeCombo(const IraBladeComboInfo& state);
    // getIraBladeComboInfo: m_comboRoute when isValidExpansion(3) holds and the singleton exists, else a zeroed static
    // dummy; caller TUnk_B61450::reciveEvent (gf_menu_obj_combo_route_simple).
    static const IraBladeComboInfo* getIraBladeComboInfo();
    // openOCG / closeOCG: tail-call GfMenuObjOCG::openGear (open LAY_special of object 0x90) /
    // closeGear (close it); caller UpdateOCG (A48 also EndOCG).
    static void openOCG();
    static void closeOCG();
    // setOCGInfo: copies result into m_layerResult, clamps its numbers to 999 and its ratio to 1.0 and, when
    // the ratio rose, tail-calls GfMenuObjOCG::noticeExtend (event 0x102 to LAY_special); caller
    // btl::UIManager::UpdateMenuData.
    static void setOCGInfo(const OCGInfo& result);
    // startOCGResult: tail-calls GfMenuObjOCG::openResult(context, pair's two words); caller UpdateOCG.
    static void startOCGResult(GfMenuCallContext* context, const OCGResult& pair);
    // resetReferenceParam: with the singleton, zeroes the reference driver/blade ids, the team/zone/mission/shop/world
    // map ids, the challenge battle mode, the item type, and the driver and blade virtual records (resetDriverVirtual
    // and resetBladeVirtual's stores); caller GfMenuManager::setupGame.
    static void resetReferenceParam();

    unsigned char pad_8[0x4C590];
    // a list of REFLISTs (the name is not the original's): postUpdate walks it with the list at 0x4C7D8 and calls
    // FixedList<REFLIST*, 32>::erase, the destructor clears it, finalize waits until it is empty
    ::mm::mtl::FixedList<REFLIST*, 32> m_refList;
    unsigned char pad_4C7D8[0x268];
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
    // setChainAttackOverkillBonus/getChainAttackOverkillBonus's number (the name is not the original's):
    // btl::UIManager::UpdateMenuData sets it from ChainAttackManager's halfword at 0x19FE after
    // setChainAttackBurstCount; GfMenuBattleAdapter's entry 17, between the chain attack ratios, shows it
    unsigned int m_chainAttackExtraNumber;
    unsigned char pad_4CB64[0xC];
    unsigned short m_chainNum;
    unsigned char pad_4CB72[0xE];
    HOMURA_MODE m_homuraModeInBattle;
    // setBattleMode stores it, refreshing GfMenuObjBladeChange's display (refreshBattleMode) when it changes;
    // getBattleMode returns it (0 without the singleton; GfMenuObjBladeChange::BladeListener::reciveEvent reads it).
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
    // setReferenceBtlchDifficulty/getReferenceBtlchDifficulty's difficulty (the name is not the original's)
    unsigned int m_challengeBattleMode;
    unsigned int m_referenceItemType;  // getReferenceItemType's item type (the name is not the original's)
    unsigned int m_driverVirtualLevel;
    unsigned int m_driverVirtualBladeID;
    unsigned int m_driverVirtualBladeSlot;
    unsigned int m_driverVirtualEquipAcc;
    unsigned int m_driverVirtualEquipAccSlot;
    int m_driverAddIdeaLv[4];
    unsigned int m_bladeVirtualEquipWpnChip;
    // the virtual blade's orb and its slot (set/getBladeVirtualEquipOrb, set/getBladeVirtualEquipOrbSlot): one
    // record, as resetBladeVirtual's single 8-byte clear after the chip's 4-byte one shows (the type's and its
    // fields' names are not the original's)
    BladeVirtualOrb m_bladeVirtualEquipOrb;
    unsigned char pad_4CCEC[0x4];
    ui::UIStr m_referenceString[13];  // getReferenceString/setReferenceString
    ArtsPaletteSlot m_artsPaletteEx[6];  // slots 3..8
    unsigned int m_partyStatusLock;  // setPartyStatusLock's locks; clearPartyStatusLock clears them
    unsigned char pad_4CF1C[0x4];
    // setBattleTime/getBattleTime's seconds (the name is not the original's): GfMenuBattleAdapter::update_BattleTime
    // shows them as minutes and seconds
    float m_timeSeconds;
    // setVisionTimeRatio/getVisionTimeRatio's ratio, kept within 0..1 (the name is not the original's): set by
    // GfMenuObjButtonChallenge2's sequences, shown in percent by GfMenuBattleAdapter::update_VisionTimeRatio
    float m_challengeRatio;
    // the layer-3 battle menu's state (btl::UIManager::UpdateMenuData sets it through the accessors above; the
    // names are not the original's)
    IraCharInfo m_bladeOwner[3];  // getIraCharInfoFromFromID, getIraCharProperty, getIraCharForm, resetIraCharRecast
    unsigned char pad_4CF58[0xC];
    float m_layerRatio;  // setIraSpecialArtsRecast/getIraSpecialArtsRecast
    int m_layerIndex;    // setIraSpecialArtsLv/getIraSpecialArtsLv
    bool m_layerFlag;    // setIraOperationDisp
    unsigned char pad_4CF6D[0x3];
    LayerCommand m_layerCommand[4];
    ::mm::mtl::Bitflag<32> m_layerBits;  // setIraFlag/isIraFlag
    LayerGauge m_layerGauge[2];          // setIraSirenInfoGauge, setIraSirenInfoLv, getIraSirenInfo
    LayerGimmick m_layerGimmick[3];      // getIraChainInfo
    // the gauge types setIraCharProperty has seen, a bit each (the name is not the original's)
    unsigned int m_gaugeTypeBits;
    unsigned char pad_4CFD0[0x4];
    IraBladeComboInfo m_comboRoute;  // resetIraBladeCombo, updateIraBladeCombo, getIraBladeComboInfo
    OCGInfo m_layerResult;  // getOCGInfo
};
}  // namespace gf

#endif
