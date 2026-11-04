#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class DataParamAcc; }
namespace gf { class GfMenuBladeList; }
namespace gf { class GfMenuDriverList; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfMenuEnemyList; }
namespace gf { class GfMenuIDList; }

namespace gf {
// a base of gf::GfMenuCharDataAdapter no evidence names yet
class TUnk_B5A8E8 {
public:
    virtual void changeCharData(unsigned char, unsigned int) = 0;
};
// a base of gf::GfMenuCharDataAdapter no evidence names yet
class TUnk_B5A900 {
public:
    virtual void changeGfObj(gf::GF_OBJ_HANDLE*) = 0;
};
// a base of gf::GfMenuCharDataAdapter no evidence names yet
class TUnk_B5A918 {
public:
    virtual void changePartyDriver(unsigned char) = 0;
};
// a base of gf::GfMenuCharDataAdapter no evidence names yet
class TUnk_B5A930 {
public:
    virtual void changePartyBlade(unsigned char, unsigned char) = 0;
};
// table 0x7100B5A8A0; base at 0x30 unknown (TUnk_B5A8E8), base at 0x38 unknown (TUnk_B5A900), base at 0x40 unknown
// (TUnk_B5A918), base at 0x48 unknown (TUnk_B5A930)
class GfMenuCharDataAdapter : public ::gf::GfMenuAdapter, public TUnk_B5A8E8, public TUnk_B5A900, public TUnk_B5A918,
                              public TUnk_B5A930 {
public:
    class BladeListConverter;
    class BladeListOwnerDriverConverter;
    class BladeListSetDriverConverter;
    class DriverListConverter;
    class EnBookListConverter;
    class EnemyListConverter;
    class GfObjConverter;
    class IConverter;
    class IraDriverListFormConverter;
    class NamedListConverter;
    class NpcIDListConverter;
    class PartyBladeConverter;
    class PartyDriverConverter;
    class ReferenceBladeConverter;
    class ReferenceBladeOwnerDriverConverter;
    class ReferenceBladeSetConverter;
    class ReferenceDriverConverter;
    struct TypeSetup {
        bool (GfMenuCharDataAdapter::*func)(const DataParamAcc&);
        GfMenuAdapter::PluginSetup plugin;
    };
    // 1.0.0 has it out of line; 3.0.1's create has it inline
    GfMenuCharDataAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), m_objType(0), m_virtualMode(0), m_objId(0),
          m_index(0), m_slotList(nullptr) {}
    virtual ~GfMenuCharDataAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void changeCharData(unsigned char objType, unsigned int objId);  // slot 3
    virtual void changeGfObj(gf::GF_OBJ_HANDLE*);  // slot 4
    virtual void changePartyDriver(unsigned char);  // slot 5
    virtual void changePartyBlade(unsigned char, unsigned char);  // slot 6
    void setSlotList(GfMenuBladeList* list);
    static GfMenuCharDataAdapter* create(unsigned int handle, unsigned int type, unsigned char objType,
                                         unsigned int objId, bool changed);
    // an adapter on the handle for the object the converter names; the adapter owns the converter (1.0.0 has it
    // out of line, 3.0.1's createFrom* inline it)
    static GfMenuCharDataAdapter* createFromCoverter(unsigned int handle, unsigned int kind, IConverter* converter,
                                                     bool changed);
    static GfMenuCharDataAdapter* createFromGfObj(unsigned int handle, unsigned int kind, GF_OBJ_HANDLE* object,
                                                  bool changed);
    static GfMenuCharDataAdapter* createFromPartyDriver(unsigned int handle, unsigned int kind, unsigned char party,
                                                        bool changed);
    // the blade in that (back) slot of the party driver's; flag: the slot getters'
    static GfMenuCharDataAdapter* createFromPartyBlade(unsigned int handle, unsigned int kind, unsigned char party,
                                                       int slot, bool changed, bool back, bool flag);
    // an adapter on the handle for an enemy list's entry at an index
    static GfMenuCharDataAdapter* createFromEnemyList(unsigned int handle, unsigned int kind, const GfMenuEnemyList* list, int index,
                                    bool);
    // an adapter on the handle for a driver list's entry at an index
    static GfMenuCharDataAdapter* createFromDriverList(unsigned int handle, unsigned int kind, const GfMenuDriverList* list, int index,
                                     bool);
    // an adapter on the handle for a blade list's entry at an index
    static GfMenuCharDataAdapter* createFromBladeList(unsigned int handle, unsigned int kind, const GfMenuBladeList* list,
                                                      int index, bool);
    // 2.0.0's symbols name it. A member: it sits among GfMenuCharDataAdapter's functions with createFromBladeList's
    // arguments, and its code ends in create. What it does: news a 0x18-byte object (table 0x7100B5B938) holding the
    // blade list and index (-1: the list's index), reads the entry's GfDataBlade::getCreator, creates the adapter
    // (create(handle, kind, 3, ..)) and stores the object at the adapter's 0x70. Callers:
    // GfMenuObjBladeRelease::initialize ("IMG_list_bl_info_dr@%02d", kind 3), GfMenuObjBladeSet2::setupBldeList,
    // GfMenuObjMercenaryForm::initialize.
    static GfMenuCharDataAdapter* createFromBladeListOwnerDriver(unsigned int handle, unsigned int kind,
                                                                 const GfMenuBladeList* list, unsigned int index,
                                                                 bool changed);
    // 2.0.0's symbols name it. A member: it sits among GfMenuCharDataAdapter's createFrom* (after
    // createFromBladeListOwnerDriver) with createFromBladeList's arguments, and its code ends in create. What it does:
    // news a 0x18-byte BladeListSetDriverConverter holding the blade list and index (-1: the list's index): the entry's
    // GfDataBlade::getSetDriver (type 3). Caller: gf_menu_obj_btlch_order's GfMenuObjBtlchOrder::initialize.
    static GfMenuCharDataAdapter* createFromBladeListSetDriver(unsigned int handle, unsigned int kind,
                                                               const GfMenuBladeList* list, unsigned int index,
                                                               bool changed);
    // an adapter on the handle for an enemy book list's entry at an index (its base enemy)
    static GfMenuCharDataAdapter* createFromEnBookList(unsigned int handle, unsigned int kind, const GfMenuIDList* list,
                                                       int index, bool changed);
    // 2.0.0's symbols name it. What it does: news a 0x18-byte NamedListConverter holding the ID list and index (-1: the
    // list's index); the entry's id gives an enemy (type 5) through GfBdatChrEnArrange's getBTL_NamedListIraEnemyID or
    // getBTL_NamedListEnemyID (GfGameManager::isGameTypeIra chooses). Callers: gf_menu_obj_named_dialog's fn_71004452C4
    // and gf_menu_obj_named_list's fn_7100445830.
    static GfMenuCharDataAdapter* createFromNamedList(unsigned int handle, unsigned int kind, const GfMenuIDList* list,
                                                int index, bool changed);
    static GfMenuCharDataAdapter* createFromReferenceBlade(unsigned int handle, unsigned int kind, unsigned int index,
                                                           bool changed);
    static GfMenuCharDataAdapter* createFromReferenceDriver(unsigned int handle, unsigned int kind, unsigned int index,
                                                            bool changed);
    // 2.0.0's symbols name it. What it does: news a 0x10-byte ReferenceBladeSetConverter holding a reference driver
    // index and a slot: the blade (type 4) in that slot of the referenced driver. Callers:
    // GfMenuObjCmnStatus::setDrPageParam, GfMenuObjPouch2::setupResult/setupPartyInfo, GfMenuObjCmnStatus::setDrPageParamIra.
    static GfMenuCharDataAdapter* createFromReferenceBladeSet(unsigned int handle, unsigned int kind, unsigned int index, int slot,
                                                bool changed);
    // the driver that owns the referenced blade (3.0.1: GfMenuReference::getIraCharInfoFromFromID's record)
    static GfMenuCharDataAdapter* createFromReferenceBladeOwnerDriver(unsigned int handle, unsigned int kind,
                                                                      unsigned int blade, bool changed);
    // 2.0.0's symbols name it. A member: it sits among GfMenuCharDataAdapter's createFrom* (after
    // createFromReferenceBladeOwnerDriver) with createFromDriverList's list, and its code ends in create. What it does:
    // nullptr unless GfMenuObjUtil::isValidExpansion(3); news a 0x18-byte IraDriverListFormConverter holding the driver
    // list, an index and a party: the driver (type 3) of that party (GfDataParty::getDriver) at the list's driver's
    // party index. Caller: gf_menu_obj_party_form3's GfMenuObjPartyForm3::setupDriverSelect (which passes the same list to
    // createFromDriverList).
    static GfMenuCharDataAdapter* createFromIraDriverListForm(unsigned int handle, unsigned int kind,
                                                              const GfMenuDriverList* list, int index,
                                                              unsigned int party, bool changed);
    // 2.0.0's symbols name it. What it does: nullptr unless GfMenuObjUtil::isValidExpansion(3); news a 0x18-byte
    // NpcIDListConverter holding the ID list and index (-1: the list's index): the entry's id as an NPC (type 6).
    // Callers: gf_menu_obj_hitonowa's GfMenuObjHitonowa::initialize, gf_menu_obj_npc_telop's GfMenuObjNpcTelop::initialize (its
    // GfMenuIDList).
    static GfMenuCharDataAdapter* createFromNpcIDList(unsigned int handle, unsigned int kind, const GfMenuIDList* list,
                                                int index, bool changed);
    unsigned int getBL_FieldSkillIndex(const DataParamAcc& acc);
    unsigned int getBL_SkillIndex(const DataParamAcc& acc);
    // the type table's update_*, in its order
    bool update_HpMax(const DataParamAcc& acc);
    bool update_Lv(const DataParamAcc& acc);
    bool update_Name(const DataParamAcc& acc);
    bool update_FaceIcon(const DataParamAcc& acc);
    bool update_PhysDef(const DataParamAcc& acc);
    bool update_EtherDef(const DataParamAcc& acc);
    bool update_Guard(const DataParamAcc& acc);
    bool update_AutoAtkDmg(const DataParamAcc& acc);
    bool update_Critical(const DataParamAcc& acc);
    bool update_HobbyName(const DataParamAcc& acc);
    bool update_HobbyIcon(const DataParamAcc& acc);
    bool update_FavoriteItemName(const DataParamAcc& acc);
    bool update_FavoriteItemIcon(const DataParamAcc& acc);
    bool update_Strength(const DataParamAcc& acc);
    bool update_EtherPow(const DataParamAcc& acc);
    bool update_Dex(const DataParamAcc& acc);
    bool update_Agl(const DataParamAcc& acc);
    bool update_Luck(const DataParamAcc& acc);
    bool update_AttrName(const DataParamAcc& acc);
    bool update_DR_Exp(const DataParamAcc& acc);
    bool update_DR_ExpNext(const DataParamAcc& acc);
    bool update_DR_ExpBonus(const DataParamAcc& acc);
    bool update_DR_ExpProgress(const DataParamAcc& acc);
    bool update_DR_ExpProgressBonus(const DataParamAcc& acc);
    bool update_DR_LevelUpEnable(const DataParamAcc& acc);
    bool update_DR_Wp(const DataParamAcc& acc);
    bool update_DR_Sp(const DataParamAcc& acc);
    bool update_DR_SetBladeFace(const DataParamAcc& acc);
    bool update_DR_Bustup(const DataParamAcc& acc);
    bool update_DR_BustupPlate(const DataParamAcc& acc);
    bool update_DR_BladeEnable(const DataParamAcc& acc);
    bool update_DR_KizunaRingOpen(const DataParamAcc& acc);
    bool update_DR_KizunaRingMax(const DataParamAcc& acc);
    bool update_DR_IdeaPoint(const DataParamAcc& acc);
    bool update_DR_IdeaLv(const DataParamAcc& acc);
    bool update_DR_ExpNextVirtual(const DataParamAcc& acc);
    bool update_DR_ClassName(const DataParamAcc& acc);
    bool update_DR_ClassBuffName(const DataParamAcc& acc);  // 1.0.0's name: its type table holds it in the same slot (37)
    bool update_DR_ClassBuffVal(const DataParamAcc& acc);
    bool update_DR_ClassBuffLv(const DataParamAcc& acc);  // 1.0.0's name: its type table holds it in the same slot (39)
    bool update_DR_BtlFace(const DataParamAcc& acc);  // 1.0.0's name: its type table holds it in the same slot (40)
    bool update_BL_WeaponIcon(const DataParamAcc& acc);  // 1.0.0's name: its type table holds it in the same slot (41)
    bool update_BL_AttrIcon(const DataParamAcc& acc);  // 1.0.0's name: its type table holds it in the same slot (42)
    bool update_BL_SpecialName(const DataParamAcc& acc);
    bool update_BL_SpecialDesc(const DataParamAcc& acc);
    bool update_BL_ArtsName(const DataParamAcc& acc);
    bool update_BL_ArtsDesc(const DataParamAcc& acc);
    bool update_BL_FieldSkillName(const DataParamAcc& acc);
    bool update_BL_FieldSkillDesc(const DataParamAcc& acc);
    bool update_BL_FieldSkillLv(const DataParamAcc& acc);
    bool update_BL_SkillName(const DataParamAcc& acc);
    bool update_BL_SkillDesc(const DataParamAcc& acc);
    bool update_BL_SkillLv(const DataParamAcc& acc);
    bool update_BL_RareIcon(const DataParamAcc& acc);
    bool update_BL_Bustup(const DataParamAcc& acc);
    bool update_BL_Power(const DataParamAcc& acc);
    bool update_BL_Attr(const DataParamAcc& acc);
    bool update_BL_AttrCol(const DataParamAcc& acc);
    bool update_BL_AttrCol2(const DataParamAcc& acc);  // 1.0.0's name: its type table holds it in the same slot (58)
    bool update_BL_GenderIcon(const DataParamAcc& acc);
    bool update_BL_Enable(const DataParamAcc& acc);
    bool update_BL_DR_Name(const DataParamAcc& acc);  // 1.0.0's name: its type table holds it in the same slot (61)
    bool update_BL_DR_Face(const DataParamAcc& acc);  // 1.0.0's name: its type table holds it in the same slot (62)
    bool update_BL_weaponTypeName(const DataParamAcc& acc);
    bool update_BL_GenderText(const DataParamAcc& acc);
    bool update_BL_RoleName(const DataParamAcc& acc);
    bool update_BL_RoleIcon(const DataParamAcc& acc);
    bool update_BL_ChangeBtnIcon(const DataParamAcc& acc);
    bool update_BL_IdeaPoint(const DataParamAcc& acc);
    bool update_BL_IdeaLv(const DataParamAcc& acc);
    bool update_BL_RecastLv(const DataParamAcc& acc);  // 1.0.0's name: its type table holds it in the same slot (70)
    bool update_BL_BtlSkillIcon(const DataParamAcc& acc);
    bool update_BL_BtlSkillLv(const DataParamAcc& acc);
    bool update_BL_Selectable(const DataParamAcc& acc);
    bool update_BL_Selectable2(const DataParamAcc& acc);
    bool update_BL_Releasable(const DataParamAcc& acc);
    bool update_BL_AffinityIcon(const DataParamAcc& acc);
    bool update_BL_AffinityText(const DataParamAcc& acc);
    bool update_BL_KizunaRingOpen(const DataParamAcc& acc);
    bool update_BL_KizunaRingMax(const DataParamAcc& acc);
    bool update_BL_CorrectiveTypeName(const DataParamAcc& acc);
    bool update_BL_CorrectiveValue(const DataParamAcc& acc);
    bool update_BL_OrbSlotEnable(const DataParamAcc& acc);
    bool fn_71003386E0(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 83
    bool update_BL_Rank(const DataParamAcc& acc);
    bool update_BL_Rarity(const DataParamAcc& acc);
    bool update_BL_CVName(const DataParamAcc& acc);
    bool update_BL_IlustName(const DataParamAcc& acc);
    bool update_BL_TeamName(const DataParamAcc& acc);
    bool update_BL_WpnImage(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 89
    bool update_BL_InMercenry(const DataParamAcc& acc);
    bool update_EN_BookID(const DataParamAcc& acc);
    bool update_EN_BaseLv(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 92
    bool update_EN_Family(const DataParamAcc& acc);
    bool update_EN_Genus(const DataParamAcc& acc);
    bool update_EN_RewardExp(const DataParamAcc& acc);
    bool update_EN_RewardGold(const DataParamAcc& acc);
    bool update_EN_DefeatedTime(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 97
    bool update_EN_DefeatedTime2(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 98
    bool update_IRA_IsFrontBtl(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 99
    bool update_IRA_IsBackBtl(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 100
    bool update_IRA_NotReserveBtl(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 101
    bool update_IRA_IsFront(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 102
    bool update_IRA_IsBack(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 103
    bool update_IRA_NotReserve(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 104
    bool update_IRA_ChangeRecast(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 105
    bool update_IRA_TypeBlade(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 106
    bool update_IRA_BackDrFace(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 107
    bool update_IRA_NpcFaceIcon(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 108
    bool update_IRA_TeamName(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 109
    bool update_IRA_TalentIcon(const DataParamAcc& acc);  // placeholder: new in 3.0.1 (1.0.0's type table has no slot for it), the type table's slot 110

    mm::mtl::Delegate<bool(const DataParamAcc&)> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the object from it; owned
    unsigned char m_objType;  // DataParamAcc's type: 3 driver, 4 blade (the name is not the original's)
    // 1: the getters take their flag, update applies GfMenuReference's virtual values (the name is not the original's)
    unsigned char m_virtualMode;
    unsigned char pad_7A[2];
    unsigned int m_objId;  // DataParamAcc's id (the name is not the original's)
    unsigned int m_index;  // a weapon point, blade slot, skill or idea index (the name is not the original's)
    unsigned char pad_84[4];
    GfMenuBladeList* m_slotList;  // setSlotList's, referenced; the destructor releases it
};
}  // namespace gf

#endif
