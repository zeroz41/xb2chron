#include "classes/gf/GfMenuCharDataAdapter.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/GfObjConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/PartyDriverConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/PartyBladeConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/DriverListConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/BladeListConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/EnemyListConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/EnBookListConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/ReferenceDriverConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/ReferenceBladeConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/ReferenceBladeOwnerDriverConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/NamedListConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/ReferenceBladeSetConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/BladeListOwnerDriverConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/BladeListSetDriverConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/IraDriverListFormConverter.h"
#include "classes/gf/GfMenuCharDataAdapter/NpcIDListConverter.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfDataParty.h"
#include "mm/mtl/FixedVector.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "gf/GfObjAcc.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/SDataBlade.h"
#include "gf/GfDataDriverSkill.h"
#include "gf/GfDataBladeSkill.h"
#include "gf/GfDataBladeArtsN.h"
#include "gf/GfDataEnBook.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfDataFieldSkill.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/GfEquipUtil.h"
#include "ui/UIStr.h"
#include "ui/uiDateTime.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfBdatRsc.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfDataBladeArts.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfWeapon.h"
#include "gf/GfDataBattle.h"
#include "classes/gf/GfDataManager.h"
#include "gf/SDataGame.h"
#include "btl/Utility.h"
#include "classes/gf/GfMenuManager.h"
#include "gf/GfItemUtil.h"
#include "gf/GfMenuItemUtil.h"
#include "classes/gf/GfGameEnv.h"
#include "classes/gf/GfBdatChrBl.h"
#include "classes/gf/GfBdatItem.h"
#include "gf/GfDataNpc.h"
#include "gf/GfGameUtil.h"

namespace gf {

namespace {
// the object's driver id, 0 unless it is a valid driver (the name is not the original's)
inline unsigned int getDriverId(const DataParamAcc& acc) {
    if (acc.isValid() && acc.getObjType() == 3) {
        return acc.getBdatId();
    }
    return 0;
}
// the object's blade id, 0 when it is not valid (the name is not the original's)
inline unsigned int getBladeId(const DataParamAcc& acc) {
    return acc.isValid() ? acc.getBdatId() : 0;
}
}  // namespace

// per type: the update_* update shows and the plugin create makes (proposed name, not the original's: the symbols
// leave it unnamed, lbl_7100B5A948)
static GfMenuCharDataAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuCharDataAdapter::update_HpMax, {0, 0, 9999}},
    {&GfMenuCharDataAdapter::update_Lv, {0, 0, 99}},
    {&GfMenuCharDataAdapter::update_Name, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_FaceIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_PhysDef, {0, 0, 100}},
    {&GfMenuCharDataAdapter::update_EtherDef, {0, 0, 100}},
    {&GfMenuCharDataAdapter::update_Guard, {0, 0, 100}},
    {&GfMenuCharDataAdapter::update_AutoAtkDmg, {0, 0, 99999}},
    {&GfMenuCharDataAdapter::update_Critical, {0, 0, 100}},
    {&GfMenuCharDataAdapter::update_HobbyName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_HobbyIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_FavoriteItemName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_FavoriteItemIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_Strength, {0, 0, 999}},
    {&GfMenuCharDataAdapter::update_EtherPow, {0, 0, 999}},
    {&GfMenuCharDataAdapter::update_Dex, {0, 0, 999}},
    {&GfMenuCharDataAdapter::update_Agl, {0, 0, 999}},
    {&GfMenuCharDataAdapter::update_Luck, {0, 0, 999}},
    {&GfMenuCharDataAdapter::update_AttrName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_Exp, {0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_DR_ExpNext, {0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_DR_ExpBonus, {0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_DR_ExpProgress, {0, 0, 100}},
    {&GfMenuCharDataAdapter::update_DR_ExpProgressBonus, {0, 0, 100}},
    {&GfMenuCharDataAdapter::update_DR_LevelUpEnable, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_Wp, {0, 0, 9999999}},
    {&GfMenuCharDataAdapter::update_DR_Sp, {0, 0, 9999999}},
    {&GfMenuCharDataAdapter::update_DR_SetBladeFace, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_Bustup, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_BustupPlate, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_BladeEnable, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_KizunaRingOpen, {0, 0, 99}},
    {&GfMenuCharDataAdapter::update_DR_KizunaRingMax, {0, 0, 99}},
    {&GfMenuCharDataAdapter::update_DR_IdeaPoint, {0, 0, 10000}},
    {&GfMenuCharDataAdapter::update_DR_IdeaLv, {0, 0, 10}},
    {&GfMenuCharDataAdapter::update_DR_ExpNextVirtual, {0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_DR_ClassName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_ClassBuffName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_ClassBuffVal, {0, -99, 99}},
    {&GfMenuCharDataAdapter::update_DR_ClassBuffLv, {0, 0, 3}},
    {&GfMenuCharDataAdapter::update_DR_BtlFace, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_WeaponIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_AttrIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_SpecialName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_SpecialDesc, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_ArtsName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_ArtsDesc, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_FieldSkillName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_FieldSkillDesc, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_FieldSkillLv, {0, 0, 9}},
    {&GfMenuCharDataAdapter::update_BL_SkillName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_SkillDesc, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_SkillLv, {0, 0, 5}},
    {&GfMenuCharDataAdapter::update_BL_RareIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Bustup, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Power, {0, 0, 99}},
    {&GfMenuCharDataAdapter::update_BL_Attr, {0, 0, 9}},
    {&GfMenuCharDataAdapter::update_BL_AttrCol, {8, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_AttrCol2, {8, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_GenderIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Enable, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_DR_Name, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_DR_Face, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_weaponTypeName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_GenderText, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_RoleName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_RoleIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_ChangeBtnIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_IdeaPoint, {0, 0, 10000}},
    {&GfMenuCharDataAdapter::update_BL_IdeaLv, {0, 0, 10}},
    {&GfMenuCharDataAdapter::update_BL_RecastLv, {0, 0, 5}},
    {&GfMenuCharDataAdapter::update_BL_BtlSkillIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_BtlSkillLv, {0, 0, 5}},
    {&GfMenuCharDataAdapter::update_BL_Selectable, {8, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Selectable2, {8, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Releasable, {8, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_AffinityIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_AffinityText, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_KizunaRingOpen, {0, 0, 99}},
    {&GfMenuCharDataAdapter::update_BL_KizunaRingMax, {0, 0, 99}},
    {&GfMenuCharDataAdapter::update_BL_CorrectiveTypeName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_CorrectiveValue, {0, 0, 100}},
    {&GfMenuCharDataAdapter::update_BL_OrbSlotEnable, {3, 0, 0}},
    {&GfMenuCharDataAdapter::fn_71003386E0, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Rank, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Rarity, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_CVName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_IlustName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_TeamName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_WpnImage, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_InMercenry, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_EN_BookID, {0, 0, 9999}},
    {&GfMenuCharDataAdapter::update_EN_BaseLv, {0, 0, 999}},
    {&GfMenuCharDataAdapter::update_EN_Family, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_EN_Genus, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_EN_RewardExp, {0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_EN_RewardGold, {0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_EN_DefeatedTime, {7, 4, 0}},
    {&GfMenuCharDataAdapter::update_EN_DefeatedTime2, {7, 4, 0}},
    {&GfMenuCharDataAdapter::update_IRA_IsFrontBtl, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_IRA_IsBackBtl, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_IRA_NotReserveBtl, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_IRA_IsFront, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_IRA_IsBack, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_IRA_NotReserve, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_IRA_ChangeRecast, {0, 0, 100}},
    {&GfMenuCharDataAdapter::update_IRA_TypeBlade, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_IRA_BackDrFace, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_IRA_NpcFaceIcon, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_IRA_TeamName, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_IRA_TalentIcon, {1, 0, 0}},
};

GfMenuCharDataAdapter::~GfMenuCharDataAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
    if (m_slotList != nullptr) {
        m_slotList->release();
        m_slotList = nullptr;
    }
}

void GfMenuCharDataAdapter::setSlotList(GfMenuBladeList* list) {
    if (m_slotList != nullptr) {
        m_slotList->release();
        m_slotList = nullptr;
    }
    m_slotList = list;
    m_slotList->addRef();
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::create(unsigned int handle, unsigned int type, unsigned char objType,
                                                     unsigned int objId, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 931
    GfMenuCharDataAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuCharDataAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_objType = objType;
    adapter->m_objId = objId;
    plugin->release();
    return adapter;
}

bool GfMenuCharDataAdapter::update_HpMax(const DataParamAcc& acc) {
    setNumber(acc.getHpMax(m_virtualMode == 1));
    return true;
}

bool GfMenuCharDataAdapter::update_Lv(const DataParamAcc& acc) {
    if (acc.getObjType() == 3 || acc.getObjType() == 4 || acc.getObjType() == 5) {
        setNumber(acc.getLevel(m_virtualMode == 1));
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_Name(const DataParamAcc& acc) {
    setText(GfMenuObjUtil::getName(acc));
    return true;
}

bool GfMenuCharDataAdapter::update_FaceIcon(const DataParamAcc& acc) {
    int icon = GfMenuObjUtil::getFaceIconID(acc);
    if (icon == 0) {
        return false;
    }
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    return true;
}

bool GfMenuCharDataAdapter::update_PhysDef(const DataParamAcc& acc) {
    setNumber(acc.getPArmor(m_virtualMode == 1));
    return true;
}

bool GfMenuCharDataAdapter::update_EtherDef(const DataParamAcc& acc) {
    setNumber(acc.getEArmor(m_virtualMode == 1));
    return true;
}

bool GfMenuCharDataAdapter::update_Guard(const DataParamAcc& acc) {
    setNumber(acc.getGuardRate(m_virtualMode == 1));
    return true;
}

bool GfMenuCharDataAdapter::update_AutoAtkDmg(const DataParamAcc& acc) {
    unsigned int min = acc.getNorAtkDmgMin(m_virtualMode == 1);
    unsigned int max = acc.getNorAtkDmgMax(m_virtualMode == 1);
    setNumber((min + max) / 2);
    return true;
}

bool GfMenuCharDataAdapter::update_Critical(const DataParamAcc& acc) {
    setNumber(acc.getCriticalRate(m_virtualMode == 1));
    return true;
}

bool GfMenuCharDataAdapter::update_Strength(const DataParamAcc& acc) {
    setNumber(acc.getStrength(m_virtualMode == 1));
    return true;
}

bool GfMenuCharDataAdapter::update_EtherPow(const DataParamAcc& acc) {
    setNumber(acc.getPowerEther(m_virtualMode == 1));
    return true;
}

bool GfMenuCharDataAdapter::update_Dex(const DataParamAcc& acc) {
    setNumber(acc.getDex(m_virtualMode == 1));
    return true;
}

bool GfMenuCharDataAdapter::update_Agl(const DataParamAcc& acc) {
    setNumber(acc.getAgility(m_virtualMode == 1));
    return true;
}

bool GfMenuCharDataAdapter::update_Luck(const DataParamAcc& acc) {
    setNumber(acc.getLuck(m_virtualMode == 1));
    return true;
}

bool GfMenuCharDataAdapter::update_DR_Exp(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    unsigned int used = GfDataDriver::getExpUsed(getDriverId(acc));
    setNumber(used + acc.getBattleExp());
    return true;
}

bool GfMenuCharDataAdapter::update_DR_ExpNext(const DataParamAcc& acc) {
    if (acc.getObjType() == 3) {
        setNumber(acc.getExpNext(false));
        return acc.getLevel(false) < 99;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_DR_ExpBonus(const DataParamAcc& acc) {
    if (acc.getObjType() == 3) {
        setNumber(acc.getExp());
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_DR_LevelUpEnable(const DataParamAcc& acc) {
    if (acc.getObjType() == 3) {
        return GfDataDriver::isEnableLevelUp(getDriverId(acc));
    }
    return false;
}

bool GfMenuCharDataAdapter::update_DR_Wp(const DataParamAcc& acc) {
    if (acc.getObjType() == 3) {
        setNumber(acc.getWeaponPoint(m_index));
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_DR_Sp(const DataParamAcc& acc) {
    if (acc.getObjType() == 3) {
        setNumber(acc.getSkillPoint());
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_DR_Bustup(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    setNumber(GfMenuObjUtil::convMenuDriverID(getDriverId(acc)));
    return true;
}

bool GfMenuCharDataAdapter::update_DR_BustupPlate(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    unsigned int id = GfMenuObjUtil::convMenuDriverID(getDriverId(acc));
    setNumber(id == 0 ? 0 : id - 1);
    return true;
}

bool GfMenuCharDataAdapter::update_DR_BladeEnable(const DataParamAcc& acc) {
    if (acc.getObjType() == 3) {
        return GfMenuObjUtil::isValidBlade(acc.getBlade(m_index, false));
    }
    return false;
}

bool GfMenuCharDataAdapter::update_DR_KizunaRingOpen(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    setNumber(GfDataDriverSkill::getValidSkillNum(getDriverId(acc), false));
    return true;
}

bool GfMenuCharDataAdapter::update_DR_KizunaRingMax(const DataParamAcc& acc) {
    if (acc.getObjType() == 3) {
        setNumber(15);
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_DR_IdeaPoint(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    SDataIdea* idea = GfDataDriver::getSDataIdea(getDriverId(acc));
    setNumber(idea->m_ideas[m_index].m_point);
    return true;
}

bool GfMenuCharDataAdapter::update_DR_IdeaLv(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    SDataIdea* idea = GfDataDriver::getSDataIdea(getDriverId(acc));
    int level = idea->m_ideas[m_index].m_level;
    if (m_virtualMode != 0) {
        unsigned int max = 15;
        setNumberMax(max);
        level += GfMenuReference::getDriverAddIdeaLv(m_index);
        if (level < 0) {
            level = 0;
        }
        if (level > max) {
            level = max;
        }
    }
    setNumber(level);
    return true;
}

bool GfMenuCharDataAdapter::update_DR_ClassBuffVal(const DataParamAcc& acc) {
    if (acc.getObjType() == 3) {
        setNumber(GfMenuObjUtil::getDriverClassBuffRatio(acc.getClass(m_virtualMode == 1), m_index));
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_BL_ArtsName(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int arts = acc.getBladeArtsN(m_index, false);
    if (arts == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataBladeArtsN::getName(bdat, id, arts)) {
        return false;
    }
    setText(ui::UIStr(bdat, id));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_ArtsDesc(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int arts = acc.getBladeArtsN(m_index, false);
    if (arts == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataBladeArtsN::getCaption(bdat, id, arts)) {
        return false;
    }
    setText(ui::UIStr(bdat, id));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_FieldSkillName(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int index = getBL_FieldSkillIndex(acc);
    if (index > 2) {
        return false;
    }
    unsigned int skill = acc.getFieldSkill(index, false);
    if (skill == 0) {
        return false;
    }
    if (acc.getFieldSkillLevel(index, false) == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataFieldSkill::getName(bdat, id, skill)) {
        return false;
    }
    setText(ui::UIStr(bdat, id));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_FieldSkillDesc(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int index = getBL_FieldSkillIndex(acc);
    if (index > 2) {
        return false;
    }
    unsigned int skill = acc.getFieldSkill(index, false);
    if (skill == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataFieldSkill::getCaption(bdat, id, skill)) {
        return false;
    }
    setText(ui::UIStr(bdat, id));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_FieldSkillLv(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int index = getBL_FieldSkillIndex(acc);
    if (index > 2) {
        return false;
    }
    if (acc.getFieldSkill(index, false) == 0) {
        return false;
    }
    setNumber(acc.getFieldSkillLevel(index, false));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_SkillName(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int index = getBL_SkillIndex(acc);
    if (index > 2) {
        return false;
    }
    unsigned int skill = acc.getBladeSkill(index, false);
    if (skill == 0) {
        return false;
    }
    if (acc.getBladeSkillLevel(index, false) == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataBladeSkill::getName(bdat, id, skill)) {
        return false;
    }
    setText(ui::UIStr(bdat, id));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_SkillLv(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int index = getBL_SkillIndex(acc);
    if (index > 2) {
        return false;
    }
    setNumber(acc.getBladeSkillLevel(index, false));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_RareIcon(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned short icon = GfMenuObjUtil::getBladeRareIconID(getBladeId(acc));
    if (icon == 0) {
        return false;
    }
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_Bustup(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    setNumber(GfMenuObjUtil::convMenuBladeID(getBladeId(acc)));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_Power(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        setNumber(acc.getBladePower(m_virtualMode == 1));
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_BL_Attr(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    setNumber(GfMenuObjUtil::getBladeAttributeID(getBladeId(acc)));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_AttrCol(const DataParamAcc& acc) {
    return acc.getObjType() == 4;
}

bool GfMenuCharDataAdapter::update_BL_GenderIcon(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    int icon;
    if (GfDataBlade::isMale(getBladeId(acc))) {
        icon = 0;
    } else {
        icon = GfDataBlade::isFemale(getBladeId(acc)) ? 1 : 2;
    }
    setNumber(icon);
    return true;
}

bool GfMenuCharDataAdapter::update_BL_Enable(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        return GfMenuObjUtil::isValidBlade(getBladeId(acc));
    }
    return false;
}

bool GfMenuCharDataAdapter::update_BL_RoleName(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned char* bdat = GfDataBdat::getFP(277);
    if (bdat == nullptr) {
        return false;
    }
    setText(ui::UIStr(bdat, acc.getRole(false)));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_IdeaPoint(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    SDataIdea* idea = GfDataBlade::getSDataIdea(getBladeId(acc));
    setNumber(idea->m_ideas[m_index].m_point);
    return true;
}

bool GfMenuCharDataAdapter::update_BL_IdeaLv(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    SDataIdea* idea = GfDataBlade::getSDataIdea(getBladeId(acc));
    setNumber(idea->m_ideas[m_index].m_level);
    return true;
}

bool GfMenuCharDataAdapter::update_BL_BtlSkillIcon(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        acc.getBladeSkill(m_index, false);
        setNumber(0);
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_BL_BtlSkillLv(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        setNumber(acc.getBladeSkillLevel(m_index, false));
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_BL_Selectable(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        setMulColor(GfMenuObjUtil::isBladeSelectable(getBladeId(acc), m_slotList) ? nullptr : "unuse");
    }
    return true;
}

bool GfMenuCharDataAdapter::update_BL_Selectable2(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        if (GfMenuReference::getReferenceDriverID(0) == 1) {
            setMulColor("white");
        } else {
            setMulColor(GfDataBlade::isEnableEngageRex(getBladeId(acc)) ? "unuse" : "white");
        }
    }
    return true;
}

bool GfMenuCharDataAdapter::update_BL_Releasable(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        setMulColor(GfMenuObjUtil::isBladeReleasable(getBladeId(acc), m_slotList) ? nullptr : "unuse");
    }
    return true;
}

bool GfMenuCharDataAdapter::update_BL_AffinityIcon(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int rank = GfDataBlade::getTrustRank(getBladeId(acc));
    if (rank >= 2) {
        setNumber(rank - 1);
    }
    return rank != 0;
}

bool GfMenuCharDataAdapter::update_BL_RoleIcon(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    switch (acc.getRole(false)) {
    case 1:
        setNumber(1);
        return true;
    case 2:
        setNumber(0);
        return true;
    case 3:
        setNumber(2);
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::fn_71003386E0(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    if (GfGameManager::isClearGame() && GfMenuObjUtil::isBladeHana(getBladeId(acc)) &&
        GfMenuObjUtil::isBladeHanaInMercenary()) {
        return true;
    }
    return GfDataBlade::fn_71002383C8(getBladeId(acc));
}

bool GfMenuCharDataAdapter::update_BL_AffinityText(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int rank = GfDataBlade::getTrustRank(getBladeId(acc));
    setText(ui::UIStr(GfDataBdat::getFP(0x128), rank));
    return rank != 0;
}

bool GfMenuCharDataAdapter::update_BL_KizunaRingOpen(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    setNumber(GfDataBlade::getKizunaringCompleteNum(getBladeId(acc)));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_KizunaRingMax(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    setNumber(GfDataBlade::getKizunaringMax(getBladeId(acc)));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_CorrectiveValue(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    if (GfMenuObjUtil::getBladeCorrectiveType(getBladeId(acc)) == 0) {
        return false;
    }
    setNumber(GfMenuObjUtil::getBladeCorrectiveRatio(getBladeId(acc)));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_OrbSlotEnable(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        return m_index < GfEquipUtil::getEquipOrbMax(getBladeId(acc));
    }
    return false;
}

bool GfMenuCharDataAdapter::update_BL_Rank(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        unsigned int blade = getBladeId(acc);
        if (GfMenuObjUtil::isValidBlade(blade)) {
            setNumber(GfMenuObjUtil::getBladeRank(blade));
            return true;
        }
    }
    return false;
}

bool GfMenuCharDataAdapter::update_BL_Rarity(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        unsigned int blade = getBladeId(acc);
        if (GfMenuObjUtil::isValidBlade(blade)) {
            setNumber(GfMenuObjUtil::getBladeRarity(blade));
            return true;
        }
    }
    return false;
}

bool GfMenuCharDataAdapter::update_BL_InMercenry(const DataParamAcc& acc) {
    if (acc.getObjType() == 4) {
        return GfDataBlade::isActivateMercenaryTeam(getBladeId(acc));
    }
    return false;
}

bool GfMenuCharDataAdapter::update_EN_BookID(const DataParamAcc& acc) {
    if (acc.getObjType() != 5) {
        return false;
    }
    setNumber(GfDataEnBook::getEnBoolId(getBladeId(acc)));
    return true;
}

bool GfMenuCharDataAdapter::update_EN_BaseLv(const DataParamAcc& acc) {
    if (acc.getObjType() != 5) {
        return false;
    }
    setNumber(mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys()->getChrEnArrangeLv(getBladeId(acc)));
    return true;
}

bool GfMenuCharDataAdapter::update_EN_RewardExp(const DataParamAcc& acc) {
    if (acc.getObjType() == 5) {
        setNumber(acc.getLevelExp());
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_EN_RewardGold(const DataParamAcc& acc) {
    if (acc.getObjType() == 5) {
        setNumber(acc.getLevelGold());
        return true;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_IRA_IsFrontBtl(const DataParamAcc& acc) {
    if (GfMenuObjUtil::isValidExpansion(3) && acc.getObjType() == 3) {
        return GfMenuReference::getIraCharForm(getDriverId(acc)) == 0;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_IRA_IsBackBtl(const DataParamAcc& acc) {
    if (GfMenuObjUtil::isValidExpansion(3) && acc.getObjType() == 3) {
        return GfMenuReference::getIraCharForm(getDriverId(acc)) == 1;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_IRA_NotReserveBtl(const DataParamAcc& acc) {
    if (GfMenuObjUtil::isValidExpansion(3) && acc.getObjType() == 3) {
        return GfMenuReference::getIraCharForm(getDriverId(acc)) != 2;
    }
    return false;
}

bool GfMenuCharDataAdapter::update_IRA_TypeBlade(const DataParamAcc& acc) {
    if (GfMenuObjUtil::isValidExpansion(3) && acc.getObjType() == 3) {
        return !GfDataDriver::isIraFront(getDriverId(acc));
    }
    return false;
}

bool GfMenuCharDataAdapter::update_IRA_NpcFaceIcon(const DataParamAcc& acc) {
    if (GfMenuObjUtil::isValidExpansion(3) && acc.getObjType() == 6) {
        unsigned int value = GfDataNpc::getHitonowaFlag2Index(getBladeId(acc));
        if (value != 0) {
            setNumber(value - 0xED03);
            return true;
        }
    }
    return false;
}

bool GfMenuCharDataAdapter::update_IRA_TalentIcon(const DataParamAcc& acc) {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    int icon = GfMenuObjUtil::getFaceIconID(acc);
    if (icon == 0) {
        return false;
    }
    if (icon == 0x149) {
        icon = 0x143;
    }
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    return true;
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromCoverter(unsigned int handle, unsigned int kind,
                                                                 IConverter* converter, bool changed) {
    unsigned char objType;
    unsigned int objId;
    converter->getCharData(objType, objId);
    GfMenuCharDataAdapter* adapter = create(handle, kind, objType, objId, changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

bool GfMenuCharDataAdapter::update_EN_DefeatedTime2(const DataParamAcc& acc) {
    if (acc.getObjType() != 5 || !GfGameManager::isEnableNamedRecord()) {
        return false;
    }
    ui::uiDateTime time = {};
    unsigned int sec = GfGameUtil::getClearNamedTime(getBladeId(acc));
    time.minute = sec / 60;
    time.sec = sec % 60;
    setTime(time);
    return true;
}

bool GfMenuCharDataAdapter::update_BL_CorrectiveTypeName(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned char* bdat = GfDataBdat::getFP(0x125);
    if (bdat == nullptr) {
        return false;
    }
    unsigned int type = GfMenuObjUtil::getBladeCorrectiveType(getBladeId(acc));
    if (type == 0) {
        return false;
    }
    setText(ui::UIStr(bdat, type));
    return true;
}

bool GfMenuCharDataAdapter::update_DR_ClassBuffLv(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    unsigned int driverClass;
    if (GfMenuObjUtil::isValidExpansion(3)) {
        driverClass = GfGameUtil::getGroupClass(getDriverId(acc));
    } else {
        driverClass = acc.getClass(m_virtualMode == 1);
    }
    unsigned char level = GfMenuObjUtil::getDriverClassBuffLv(driverClass, m_index);
    if (level == 0) {
        return false;
    }
    setNumber(level - 1);
    return true;
}

bool GfMenuCharDataAdapter::update_BL_CVName(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int blade = getBladeId(acc);
    if (!GfMenuObjUtil::isValidBlade(blade)) {
        return false;
    }
    unsigned int name = GfDataBlade::getMenuCastName(blade);
    if (name == 0) {
        return false;
    }
    setText(ui::UIStr(GfDataBdat::getFP(0x137), name));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_IlustName(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int blade = getBladeId(acc);
    if (!GfMenuObjUtil::isValidBlade(blade)) {
        return false;
    }
    unsigned int name = GfDataBlade::getMenuIlustName(blade);
    if (name == 0) {
        return false;
    }
    setText(ui::UIStr(GfDataBdat::getFP(0x138), name));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_TeamName(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int blade = getBladeId(acc);
    if (!GfMenuObjUtil::isValidBlade(blade)) {
        return false;
    }
    ui::UIStr name;
    if (!GfMenuObjUtil::getBladeTeamName(blade, name)) {
        return false;
    }
    setText(name);
    return true;
}

bool GfMenuCharDataAdapter::update_EN_DefeatedTime(const DataParamAcc& acc) {
    if (acc.getObjType() != 5 || !GfGameManager::isEnableNamedRecord()) {
        return false;
    }
    ui::uiDateTime time = {};
    unsigned int mode = GfMenuReference::getReferenceBtlchDifficulty();
    unsigned int sec = GfGameUtil::getClearNamedTime(getBladeId(acc), static_cast<GFDIFF>(mode));
    time.minute = sec / 60;
    time.sec = sec % 60;
    setTime(time);
    return true;
}

bool GfMenuCharDataAdapter::update_DR_SetBladeFace(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    unsigned int blade = acc.getBlade(-1, false);
    if (blade == 0 || GfDataBlade::isDummyBlade(blade)) {
        return false;
    }
    DataParamAcc bladeAcc(4, blade, GimmickType(0));
    int icon = GfMenuObjUtil::getFaceIconID(bladeAcc);
    if (icon == 0) {
        return false;
    }
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_AttrIcon(const DataParamAcc& acc) {
    int icon;
    if (GfMenuObjUtil::isValidExpansion(3) && acc.getObjType() == 3) {
        icon = static_cast<unsigned short>(acc.getAttribute(-1, m_virtualMode == 1) + 0x9E);
    } else {
        if (acc.getObjType() != 4) {
            return false;
        }
        icon = static_cast<unsigned short>(GfMenuObjUtil::getBladeAttributeIconID(getBladeId(acc)));
        if (icon == 0) {
            return false;
        }
    }
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    return true;
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromGfObj(unsigned int handle, unsigned int kind,
                                                              GF_OBJ_HANDLE* object, bool changed) {
#line 962
    GfObjConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjConverter(object);
    return createFromCoverter(handle, kind, converter, changed);
}

bool GfMenuCharDataAdapter::update_BL_weaponTypeName(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned char* weapons = GfDataBdat::getFP(0x141);
    unsigned char weaponType = GfDataBlade::getSDataBlade(getBladeId(acc))->m_weaponType;
    unsigned char* names = GfDataBdat::getFP(0x1CF);
    setText(ui::UIStr(names, static_cast<unsigned short>(Bdat::getVal(weapons, "name", weaponType))));
    return true;
}

bool GfMenuCharDataAdapter::update_AttrName(const DataParamAcc& acc) {
    if (acc.getObjType() != 4 && acc.getObjType() != 5) {
        return false;
    }
    unsigned char* attributes = GfDataBdat::getFP(0x13E);
    unsigned int attribute = acc.getAttribute(-1, false);
    unsigned char* names = GfDataBdat::getFP(0x114);
    setText(ui::UIStr(names, static_cast<unsigned short>(Bdat::getVal(attributes, "name", Bdat::getIdTop(names) + attribute))));
    return true;
}

bool GfMenuCharDataAdapter::update_IRA_BackDrFace(const DataParamAcc& acc) {
    if (!GfMenuObjUtil::isValidExpansion(3) || acc.getObjType() != 3) {
        return false;
    }
    int icon = GfMenuObjUtil::getFaceIconID(DataParamAcc(3, GfDataDriver::getIraBack(getDriverId(acc)), GimmickType(0)));
    if (icon == 0) {
        return false;
    }
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_AttrCol2(const DataParamAcc& acc) {
    unsigned int attribute;
    if (GfMenuObjUtil::isValidExpansion(3) && acc.getObjType() == 3) {
        attribute = acc.getAttribute(-1, m_virtualMode == 1);
    } else {
        if (acc.getObjType() != 4) {
            return false;
        }
        attribute = GfMenuObjUtil::getBladeAttributeID(getBladeId(acc));
    }
    mm::mtl::FixStr<32> color;
    color.format("elemental%02d", attribute);
    setColor(color.m_str);
    return true;
}

bool GfMenuCharDataAdapter::update_IRA_IsBack(const DataParamAcc& acc) {
    if (!GfMenuObjUtil::isValidExpansion(3) || acc.getObjType() != 3) {
        return false;
    }
    unsigned int party = GfGameParty::getPartyId(3, getDriverId(acc));
    if (party == 0xFFFFFFFF) {
        return false;
    }
    return GfGameParty::getDriverBdatId(party, 1) == getDriverId(acc);
}

bool GfMenuCharDataAdapter::update_IRA_NotReserve(const DataParamAcc& acc) {
    if (!GfMenuObjUtil::isValidExpansion(3) || acc.getObjType() != 3) {
        return false;
    }
    unsigned int party = GfGameParty::getPartyId(3, getDriverId(acc));
    if (party == 0xFFFFFFFF) {
        return false;
    }
    return GfGameParty::getDriverBdatId(party, 2) != getDriverId(acc);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromPartyDriver(unsigned int handle, unsigned int kind,
                                                                    unsigned char party, bool changed) {
#line 969
    PartyDriverConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        PartyDriverConverter(party);
    return createFromCoverter(handle, kind, converter, changed);
}

bool GfMenuCharDataAdapter::update_IRA_IsFront(const DataParamAcc& acc) {
    if (!GfMenuObjUtil::isValidExpansion(3) || acc.getObjType() != 3) {
        return false;
    }
    unsigned int party = GfGameParty::getPartyId(3, getDriverId(acc));
    if (party == 0xFFFFFFFF) {
        return false;
    }
    return GfGameParty::getDriverBdatId(party, 0) == getDriverId(acc);
}

bool GfMenuCharDataAdapter::update_DR_ClassBuffName(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    unsigned int driverClass;
    if (GfMenuObjUtil::isValidExpansion(3)) {
        driverClass = GfGameUtil::getGroupClass(getDriverId(acc));
    } else {
        driverClass = acc.getClass(m_virtualMode == 1);
    }
    unsigned int type = GfMenuObjUtil::getDriverClassBuffType(driverClass, m_index);
    if (type == 0) {
        return false;
    }
    setText(ui::UIStr(GfDataBdat::getFP(0x127), type));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_DR_Name(const DataParamAcc& acc) {
    unsigned int driver = GfDataBlade::getCreator(getBladeId(acc));
    if (GfMenuObjUtil::isValidExpansion(3)) {
        driver = GfDataDriver::getIraFront(GfDataBlade::getIraDriver(getBladeId(acc)));
    }
    if (driver == 0) {
        return false;
    }
    {
        DataParamAcc driverAcc(3, driver, GimmickType(0));
        setText(GfMenuObjUtil::getName(driverAcc));
        return true;
    }
}

bool GfMenuCharDataAdapter::update_BL_DR_Face(const DataParamAcc& acc) {
    unsigned int driver = GfDataBlade::getCreator(getBladeId(acc));
    if (GfMenuObjUtil::isValidExpansion(3)) {
        driver = GfDataDriver::getIraFront(GfDataBlade::getIraDriver(getBladeId(acc)));
    }
    if (driver == 0) {
        return false;
    }
    {
        DataParamAcc driverAcc(3, driver, GimmickType(0));
        int icon = GfMenuObjUtil::getFaceIconID(driverAcc);
        if (icon == 0) {
            return false;
        }
        setNumber(GfMenuBdat::getIconImageIndex(icon));
        return true;
    }
}

bool GfMenuCharDataAdapter::update_DR_BtlFace(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    int face;
    if (getDriverId(acc) == 1 && GfGameManager::isRexAwakening()) {
        face = 8;
    } else if (GfMenuObjUtil::isValidExpansion(3) && getDriverId(acc) == 0x14 && GfMenuObjUtil::isIraSinMaskOff()) {
        face = 0xB;
    } else {
        int icon = acc.getIconData();
        if (icon == 0) {
            return false;
        }
        face = GfMenuBdat::getIconImageIndex(icon);
    }
    setNumber(face);
    return true;
}

bool GfMenuCharDataAdapter::update_DR_ExpNextVirtual(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    if (GfMenuReference::getDriverVirtualLevel() == 0) {
        if (acc.getObjType() != 3) {
            return false;
        }
        setNumber(acc.getExpNext(false));
        return acc.getLevel(false) < 99;
    }
    setNumber(GfDataDriver::getExpSetLevel(getDriverId(acc), GfMenuReference::getDriverVirtualLevel() + 1));
    return GfMenuReference::getDriverVirtualLevel() + 1 < 100;
}

bool GfMenuCharDataAdapter::update_EN_Family(const DataParamAcc& acc) {
    if (acc.getObjType() != 5) {
        return false;
    }
    GfBdatRsc* rsc = mm::mtl::PtrSingleton<GfBdatRsc>::sys();
    if (rsc == nullptr) {
        return false;
    }
    unsigned char* families = GfDataBdat::getFP(0x157);
    if (families == nullptr) {
        return false;
    }
    unsigned int id = GfDataEnemy::getRscIdByArrangeId(getBladeId(acc));
    if (id == 0) {
        return false;
    }
    unsigned int family = rsc->getRscEnTypeFamily(id);
    if (family == 0) {
        return false;
    }
    unsigned int name = static_cast<unsigned short>(Bdat::getVal(families, "name", family - 1));
    setText(ui::UIStr(GfDataBdat::getFP(0x130), name));
    return true;
}

bool GfMenuCharDataAdapter::update_DR_ExpProgress(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    if (acc.getLevel(false) < 99) {
        float exp = acc.getBattleExp();
        float next = GfDataDriver::getExpSetLevel(getDriverId(acc), acc.getLevel(false) + 1);
        unsigned int progress;
        if (exp >= next) {
            progress = 100;
        } else {
            progress = exp / next * 100.0f;
        }
        setNumber(progress);
    } else {
        setNumber(0);
    }
    setNumberMax(100);
    return true;
}

bool GfMenuCharDataAdapter::update_BL_SpecialName(const DataParamAcc& acc) {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        if (acc.getObjType() != 4 && acc.getObjType() != 3) {
            return false;
        }
    } else if (acc.getObjType() != 4) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    bool found;
    if (m_index < 3) {
        unsigned int arts = acc.getBladeArts(m_index, false);
        if (arts == 0) {
            return false;
        }
        found = GfDataBladeArts::getName(bdat, id, arts);
    } else {
        unsigned int arts = acc.getBladeArtsEx(false);
        if (arts == 0) {
            return false;
        }
        found = GfDataBladeArts::getExName(bdat, id, arts);
    }
    if (!found) {
        return false;
    }
    setText(ui::UIStr(bdat, id));
    return true;
}

bool GfMenuCharDataAdapter::update_BL_SpecialDesc(const DataParamAcc& acc) {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        if (acc.getObjType() != 4 && acc.getObjType() != 3) {
            return false;
        }
    } else if (acc.getObjType() != 4) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    bool found;
    if (m_index < 3) {
        unsigned int arts = acc.getBladeArts(m_index, false);
        if (arts == 0) {
            return false;
        }
        found = GfDataBladeArts::getCaption(bdat, id, arts);
    } else {
        unsigned int arts = acc.getBladeArtsEx(false);
        if (arts == 0) {
            return false;
        }
        found = GfDataBladeArts::getExCaption(bdat, id, arts);
    }
    if (!found) {
        return false;
    }
    setText(ui::UIStr(bdat, id));
    return true;
}

bool GfMenuCharDataAdapter::update_DR_ExpProgressBonus(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    if (acc.getLevel(false) < 99) {
        float exp = acc.getBattleExp() + acc.getExp();
        float next = GfDataDriver::getExpSetLevel(getDriverId(acc), acc.getLevel(false) + 1);
        unsigned int progress;
        if (exp >= next) {
            progress = 100;
        } else {
            progress = exp / next * 100.0f;
        }
        setNumber(progress);
    } else {
        setNumber(0);
    }
    return true;
}

bool GfMenuCharDataAdapter::update_BL_GenderText(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    int gender;
    if (GfDataBlade::isMale(getBladeId(acc))) {
        gender = 0;
    } else if (GfDataBlade::isFemale(getBladeId(acc))) {
        gender = 1;
    } else {
        gender = 2;
    }
    unsigned char* genders = GfDataBdat::getFP(0x142);
    int top = Bdat::getIdTop(genders);
    unsigned char* names = GfDataBdat::getFP(0xF5);
    setText(ui::UIStr(names, static_cast<unsigned short>(Bdat::getVal(genders, "name", top + gender))));
    return true;
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromPartyBlade(unsigned int handle, unsigned int kind,
                                                                   unsigned char party, int slot, bool changed,
                                                                   bool back, bool flag) {
#line 976
    PartyBladeConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        PartyBladeConverter(party, slot, back, flag);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromDriverList(unsigned int handle, unsigned int kind,
                                                                   const GfMenuDriverList* list, int index,
                                                                   bool changed) {
    if (handle == 0) {
        return nullptr;
    }
#line 985
    DriverListConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        DriverListConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromBladeList(unsigned int handle, unsigned int kind,
                                                                  const GfMenuBladeList* list, int index,
                                                                  bool changed) {
#line 992
    BladeListConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        BladeListConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

bool GfMenuCharDataAdapter::update_BL_SkillDesc(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int index = getBL_SkillIndex(acc);
    if (index >= 3) {
        return false;
    }
    unsigned int skill = acc.getBladeSkill(index, false);
    if (skill == 0) {
        return false;
    }
    if (acc.getBladeSkillLevel(index, false) == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataBladeSkill::getEnhanceCaption(bdat, id, skill, acc.getBladeSkillLevel(index, false))) {
        return false;
    }
    unsigned short enhance = GfDataBladeSkill::getEnhance(skill, acc.getBladeSkillLevel(index, false));
    ui::UIStr text(bdat, id);
    text.m_ownerId = enhance;
    setText(text);
    return true;
}

bool GfMenuCharDataAdapter::update_BL_RecastLv(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    unsigned int blade = getBladeId(acc);
    unsigned char* levels = GfDataBdat::getFP(0x172);
    float time = btl::Utility::GetBladeCoolTime(blade);
    if (m_virtualMode != 0 && GfMenuReference::getBladeVirtualEquipOrb() != 0) {
        unsigned int slot = GfMenuReference::getBladeVirtualEquipOrbSlot();
        unsigned int orb = GfMenuReference::getBladeVirtualEquipOrb();
        unsigned short equipped = GfDataBlade::getEquipOrb(blade, slot);
        GfDataBlade::setEquipOrb(blade, orb, slot);
        time = btl::Utility::GetBladeCoolTime(blade);
        GfDataBlade::setEquipOrb(blade, equipped, slot);
    }
    float frames = time * 30.0f;
    setNumber(GfMenuBdat::getValueLevel(levels, static_cast<int>(frames + (frames > 0.0f ? 0.5f : -0.5f))));
    return true;
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromEnemyList(unsigned int handle, unsigned int kind,
                                                                  const GfMenuEnemyList* list, int index,
                                                                  bool changed) {
#line 999
    EnemyListConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        EnemyListConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

bool GfMenuCharDataAdapter::update_IRA_ChangeRecast(const DataParamAcc& acc) {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return false;
    }
    if (!GfGameManager::isBattle()) {
        const GfMenuReference::IraCharProperty* gauge = GfMenuReference::getIraCharProperty(getDriverId(acc));
        if (gauge == nullptr) {
            return false;
        }
        unsigned int bit;
        if (gauge->m_type == 2) {
            bit = 1;
        } else if (gauge->m_type == 1) {
            bit = 0;
        } else {
            return false;
        }
        setNumber(GfMenuReference::isIraFlag(bit) ? 100 : 0);
        return false;
    } else {
        if (acc.getObjType() != 3) {
            return false;
        }
        const GfMenuReference::IraCharProperty* gauge = GfMenuReference::getIraCharProperty(getDriverId(acc));
        if (gauge == nullptr) {
            return false;
        }
        setNumber(gauge->m_rate * 100.0f);
        if (!GfMenuManager::isBattleState(0) && gauge->m_rate >= 1.0f) {
            setNumber(0);
            return false;
        }
        return gauge->m_rate > 0.0f;
    }
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromEnBookList(unsigned int handle, unsigned int kind,
                                                                   const GfMenuIDList* list, int index,
                                                                   bool changed) {
#line 1006
    EnBookListConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        EnBookListConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

bool GfMenuCharDataAdapter::update_IRA_TeamName(const DataParamAcc& acc) {
    if (!GfMenuObjUtil::isValidExpansion(3) || acc.getObjType() != 3) {
        return false;
    }
    unsigned int driver = getDriverId(acc);
    unsigned char* teams = GfDataBdat::getFP(0x89);
    if (teams == nullptr || Bdat::getMember(teams, "TeamName") == nullptr) {
        return false;
    }
    unsigned short name = 0;
    for (int i = 0; i < Bdat::getIdCount(teams); i++) {
        int id = Bdat::getIdTop(teams) + i;
        if (driver == static_cast<unsigned short>(Bdat::getVal(teams, "driverID", id))) {
            name = Bdat::getVal(teams, "TeamName", id);
            break;
        }
    }
    if (name == 0) {
        return false;
    }
    setText(ui::UIStr(GfDataBdat::getFP(0x1A8), name));
    return true;
}

bool GfMenuCharDataAdapter::update_HobbyIcon(const DataParamAcc& acc) {
    if (acc.getObjType() != 3 && acc.getObjType() != 4) {
        return false;
    }
    unsigned int item = 0;
    unsigned int id = 0;
    if (acc.getObjType() == 3) {
        id = getDriverId(acc);
        item = GfDataDriver::getFavorite(id, static_cast<FAVORITE>(m_index));
        if (item == 0) {
            return false;
        }
    } else if (acc.getObjType() == 4) {
        id = getBladeId(acc);
        item = GfDataBlade::getFavorite(id, static_cast<FAVORITE>(m_index));
        if (item == 0) {
            return false;
        }
    }
    unsigned int stat = GfMenuObjUtil::getFavoriteStat(acc.getObjType(), id, static_cast<FAVORITE>(m_index != 0 ? 1 : 0));
    if (stat == 2) {
        return false;
    }
    unsigned int number = 0;
    if (stat == 1) {
        number = 0x40;
    } else if (!GfMenuItemUtil::getIconNumber(static_cast<ItemType::Type>(10), item, number, false)) {
        return false;
    }
    setNumber(number);
    return true;
}

bool GfMenuCharDataAdapter::update_FavoriteItemIcon(const DataParamAcc& acc) {
    if (acc.getObjType() != 3 && acc.getObjType() != 4) {
        return false;
    }
    unsigned int id = 0;
    unsigned int item = 0;
    if (acc.getObjType() == 3) {
        id = getDriverId(acc);
        item = GfDataDriver::getFavorite(id, static_cast<FAVORITE>(m_index + 2));
        if (item == 0) {
            return false;
        }
    } else if (acc.getObjType() == 4) {
        id = getBladeId(acc);
        item = GfDataBlade::getFavorite(id, static_cast<FAVORITE>(m_index + 2));
        if (item == 0) {
            return false;
        }
    }
    unsigned int stat = GfMenuObjUtil::getFavoriteStat(acc.getObjType(), id, static_cast<FAVORITE>(m_index != 0 ? 3 : 2));
    if (stat == 2) {
        return false;
    }
    unsigned int number = 0;
    if (stat == 1) {
        number = 0x40;
    } else {
        ItemProperty property;
        GfItemUtil::getProperty(property, item, 0);
        if (property.m_favoriteKey >= 12) {
            if (!GfMenuItemUtil::getIconNumber(static_cast<ItemType::Type>(10), property.m_favoriteKey, number, false)) {
                return false;
            }
        } else {
            return false;
        }
    }
    setNumber(number);
    return true;
}

bool GfMenuCharDataAdapter::update_BL_ChangeBtnIcon(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    if (!GfDataBlade::isSetBlade(getBladeId(acc))) {
        return false;
    }
    DataParamAcc driverAcc(3, GfDataBlade::getSetDriver(getBladeId(acc)), GimmickType(0));
    if (!driverAcc.isValid()) {
        return false;
    }
    // the buttons of the driver's three blade slots
    const unsigned int buttons[] = {0x1000, 0x2000, 0x4000};
    for (int i = 0; i < 3; i++) {
        if (driverAcc.getBlade(i, false) == getBladeId(acc)) {
            setNumber(GfMenuBdat::getIconImageIndex(GfMenuObjUtil::getBtnIconNumber(buttons[i])));
            return true;
        }
    }
    return false;
}

bool GfMenuCharDataAdapter::update_HobbyName(const DataParamAcc& acc) {
    if (acc.getObjType() != 3 && acc.getObjType() != 4) {
        return false;
    }
    unsigned int id = 0;
    unsigned int item = 0;
    if (acc.getObjType() == 3) {
        id = getDriverId(acc);
        item = GfDataDriver::getFavorite(id, static_cast<FAVORITE>(m_index));
    } else if (acc.getObjType() == 4) {
        id = getBladeId(acc);
        item = GfDataBlade::getFavorite(id, static_cast<FAVORITE>(m_index));
    }
    unsigned int stat = GfMenuObjUtil::getFavoriteStat(acc.getObjType(), id, static_cast<FAVORITE>(m_index != 0 ? 1 : 0));
    unsigned int file;
    unsigned int name;
    if (stat == 1) {
        name = static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x15A), "name", 1));
        file = 0xF5;
    } else if (stat == 2) {
        name = static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x15A), "name", 2));
        file = 0xF5;
    } else if (item >= 12) {
        name = item - 11;
        file = 0x12F;
    } else {
        return false;
    }
    setText(ui::UIStr(GfDataBdat::getFP(file), name));
    return true;
}

bool GfMenuCharDataAdapter::update_FavoriteItemName(const DataParamAcc& acc) {
    if (acc.getObjType() != 3 && acc.getObjType() != 4) {
        return false;
    }
    unsigned int item = 0;
    unsigned int id = 0;
    if (acc.getObjType() == 3) {
        id = getDriverId(acc);
        item = GfDataDriver::getFavorite(id, static_cast<FAVORITE>(m_index + 2));
    } else if (acc.getObjType() == 4) {
        id = getBladeId(acc);
        item = GfDataBlade::getFavorite(id, static_cast<FAVORITE>(m_index + 2));
    }
    unsigned int stat = GfMenuObjUtil::getFavoriteStat(acc.getObjType(), id, static_cast<FAVORITE>(m_index != 0 ? 3 : 2));
    ui::UIStr text;
    if (stat != 1) {
        if (stat == 2) {
            unsigned int name = static_cast<unsigned short>(Bdat::getVal(GfDataBdat::getFP(0x15A), "name", 2));
            text.copy(ui::UIStr(GfDataBdat::getFP(0xF5), name));
        } else {
            GfMenuItemUtil::getItemName(10, item, text);
        }
        if (text.isValid()) {
            setText(text);
            return true;
        }
    }
    return false;
}

bool GfMenuCharDataAdapter::update_BL_WeaponIcon(const DataParamAcc& acc) {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        unsigned int blade;
        if (acc.getObjType() == 3) {
            blade = GfDataDriver::getIraBlade(getDriverId(acc), -1);
        } else if (acc.getObjType() == 4) {
            blade = getBladeId(acc);
        } else {
            blade = 0;
        }
        unsigned int type = GfDataBlade::getBladeWpnType(blade);
        if (type == 0) {
            return false;
        }
        // the weapon types in the order of their icons
        const unsigned int types[] = {0x1C, 0x1D, 0x1E, 0x12, 0x1F, 1, 0x20, 7, 0xE};
        int icon = 0;
        while (types[icon] != type) {
            if (++icon >= 9) {
                return false;
            }
        }
        setNumber(icon);
    } else {
        if (acc.getObjType() != 4) {
            return false;
        }
        unsigned int type = GfDataBlade::getBladeWpnType(getBladeId(acc));
        if (type == 0) {
            return false;
        }
        if (GfMenuObjUtil::isValidExpansion(1)) {
            if (type == 0x21) {
                type = 0x1B;
            } else if (type == 0x22) {
                type = 0x1C;
            }
        }
        if (GfGameAoc::get()->fn_71002A75DC(0x20301)) {
            if (type == 0x24) {
                type = 0x1D;
            } else if (type == 0x23) {
                type = 0x1E;
            }
        }
        setNumber(type - 1);
    }
    return true;
}

bool GfMenuCharDataAdapter::update_BL_WpnImage(const DataParamAcc& acc) {
    if (acc.getObjType() != 4) {
        return false;
    }
    GfBdatItem* items = mm::mtl::PtrSingleton<GfBdatItem>::sys();
    unsigned int weapon = acc.getEquipWeapon(0, m_virtualMode == 1);
    if (weapon == 0) {
        return false;
    }
    GfBdatChrBl* blades = mm::mtl::PtrSingleton<GfBdatChrBl>::sys();
    if (blades->getChrBlPrivateWpnR(getBladeId(acc)) != 0 && blades->isChrBlFlagOnlyWpn(getBladeId(acc)) &&
        GfDataBlade::getBladeWpnType(getBladeId(acc)) != 1) {
        weapon = blades->getChrBlDefWeapon(getBladeId(acc));
    }
    unsigned int rsc = 0;
    if (!GfDataBlade::isCommonBlade(getBladeId(acc))) {
        GfBdatChrBl* chrBl = mm::mtl::PtrSingleton<GfBdatChrBl>::sys();
        if (items->isPcWpnFlagPrivate(weapon) || GfMenuObjUtil::isValidExpansion(3)) {
            rsc = chrBl->getChrBlPrivateWpnR_Driver(getBladeId(acc)) != 0
                      ? chrBl->getChrBlPrivateWpnR_Driver(getBladeId(acc))
                      : (chrBl->getChrBlPrivateWpnR(getBladeId(acc)) != 0 ? chrBl->getChrBlPrivateWpnR(getBladeId(acc)) : 0);
        }
    }
    if (rsc == 0) {
        rsc = items->getPcWpnRscR(weapon);
        if (rsc == 0) {
            return false;
        }
    }
    int image = mm::mtl::PtrSingleton<GfBdatRsc>::sys()->getRSC_PcWpnMenuImageID(rsc);
    if (image == 0) {
        return false;
    }
    setNumber(image);
    return true;
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromNamedList(unsigned int handle, unsigned int kind,
                                                            const GfMenuIDList* list, int index, bool changed) {
#line 1013
    NamedListConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        NamedListConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

bool GfMenuCharDataAdapter::update_DR_ClassName(const DataParamAcc& acc) {
    if (acc.getObjType() != 3) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataBattle::getClassName(bdat, id, acc.getClass(m_virtualMode == 1))) {
        return false;
    }
    if (bdat == nullptr || id == 0) {
        return false;
    }
    setText(ui::UIStr(bdat, id));
    return true;
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromReferenceDriver(unsigned int handle, unsigned int kind,
                                                                        unsigned int index, bool changed) {
#line 1020
    ReferenceDriverConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ReferenceDriverConverter(index);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromReferenceBlade(unsigned int handle, unsigned int kind,
                                                                       unsigned int index, bool changed) {
#line 1027
    ReferenceBladeConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ReferenceBladeConverter(index);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromReferenceBladeSet(unsigned int handle, unsigned int kind,
                                                            unsigned int index, int slot, bool changed) {
#line 1041
    ReferenceBladeSetConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ReferenceBladeSetConverter(index, slot);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromBladeListOwnerDriver(unsigned int handle, unsigned int kind,
                                                                             const GfMenuBladeList* list,
                                                                             unsigned int index, bool changed) {
#line 1055
    BladeListOwnerDriverConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        BladeListOwnerDriverConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromBladeListSetDriver(unsigned int handle, unsigned int kind,
                                                                           const GfMenuBladeList* list,
                                                                           unsigned int index, bool changed) {
#line 1062
    BladeListSetDriverConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        BladeListSetDriverConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

bool GfMenuCharDataAdapter::update_EN_Genus(const DataParamAcc& acc) {
    if (acc.getObjType() != 5) {
        return false;
    }
    GfBdatRsc* rsc = mm::mtl::PtrSingleton<GfBdatRsc>::sys();
    if (rsc == nullptr) {
        return false;
    }
    unsigned int id = GfDataEnemy::getRscIdByArrangeId(getBladeId(acc));
    if (id == 0) {
        return false;
    }
    unsigned int name = rsc->getRscEnGenusNAME(rsc->getRscEnTypeGenus(id));
    setText(ui::UIStr(GfDataBdat::getFP(0x19A), name));
    return true;
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromReferenceBladeOwnerDriver(unsigned int handle,
                                                                                  unsigned int kind,
                                                                                  unsigned int blade, bool changed) {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return nullptr;
    }
#line 1082
    ReferenceBladeOwnerDriverConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ReferenceBladeOwnerDriverConverter(blade);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromIraDriverListForm(unsigned int handle, unsigned int kind,
                                                            const GfMenuDriverList* list, int index,
                                                            unsigned int party, bool changed) {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return nullptr;
    }
#line 1092
    IraDriverListFormConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        IraDriverListFormConverter(list, index, party);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromNpcIDList(unsigned int handle, unsigned int kind,
                                                            const GfMenuIDList* list, int index, bool changed) {
    if (!GfMenuObjUtil::isValidExpansion(3)) {
        return nullptr;
    }
#line 1102
    NpcIDListConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        NpcIDListConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

void GfMenuCharDataAdapter::update(fw::UpdateInfo const&) {
    if (m_converter != nullptr) {
        unsigned char objType = 0;
        unsigned int objId = 0;
        m_converter->getCharData(objType, objId);
        changeCharData(objType, objId);
    }
    if ((m_flags & 3) != 0 && m_update.isValid()) {
        DataParamAcc acc(m_objType, m_objId, GimmickType(0));
        bool disp = false;
        if (acc.isValid()) {
            acc.setMenuParam();
            if (m_virtualMode != 0) {
                switch (m_objType) {
                case 3:
                    if (GfMenuReference::getDriverVirtualLevel() != 0) {
                        acc.setVirtualLevel(GfMenuReference::getDriverVirtualLevel());
                    }
                    if (GfMenuReference::getDriverVirtualBladeID() != 0) {
                        unsigned int blade = GfMenuReference::getDriverVirtualBladeID();
                        int slot = GfMenuReference::getDriverVirtualBladeSlot();
                        if (getDriverId(acc) == GfDataBlade::getSetDriver(blade)) {
                            slot = GfDataBlade::getDriverSetID(blade);
                        }
                        acc.setVirtualSetBlade(GfMenuReference::getDriverVirtualBladeID(), slot);
                    }
                    // the original asks isValidExpansion(3) up to three times on one path (its code has the three
                    // separate calls); with layer 3, slot 0 is the extra accessory (setVirtualEquipWpnAcce), slot n index n - 1
                    if (GfMenuReference::getDriverVirtualEquipAcc() != 0) {
                        if (GfMenuObjUtil::isValidExpansion(3)) {
                            unsigned int slot = GfMenuReference::getDriverVirtualEquipAccSlot();
                            if (slot == 0) {
                                acc.setVirtualEquipWpnAcce(GfMenuReference::getDriverVirtualEquipAcc());
                            } else {
                                acc.setVirtualEquipAcc(slot - 1, GfMenuReference::getDriverVirtualEquipAcc());
                            }
                        } else if (GfMenuObjUtil::isValidExpansion(3)) {
                            unsigned int slot = GfMenuReference::getDriverVirtualEquipAccSlot();
                            if (slot != 0) {
                                acc.setVirtualEquipAcc(slot - 1, GfMenuReference::getDriverVirtualEquipAcc());
                            }
                        } else {
                            bool layer = GfMenuObjUtil::isValidExpansion(3);
                            unsigned int slot = GfMenuReference::getDriverVirtualEquipAccSlot();
                            if (layer) {
                                if (slot != 0) {
                                    acc.setVirtualEquipAcc(slot - 1, GfMenuReference::getDriverVirtualEquipAcc());
                                }
                            } else {
                                acc.setVirtualEquipAcc(slot, GfMenuReference::getDriverVirtualEquipAcc());
                            }
                        }
                    }
                    break;
                case 4:
                    if (GfMenuReference::getBladeVirtualEquipWpnChip() != 0) {
                        acc.setVirtualEquipWpnChip(GfMenuReference::getBladeVirtualEquipWpnChip());
                    }
                    if (GfMenuReference::getBladeVirtualEquipOrb() != 0) {
                        unsigned int slot = GfMenuReference::getBladeVirtualEquipOrbSlot();
                        acc.setVirtualEquipOrb(GfMenuReference::getBladeVirtualEquipOrb(), slot);
                    }
                    break;
                }
            }
            if (acc.getObjType() == 4 && !GfMenuObjUtil::isIraDummyBlade(getBladeId(acc)) &&
                !GfMenuObjUtil::isValidBlade(getBladeId(acc))) {
                disp = false;
            } else {
                disp = m_update(acc);
            }
        }
        setDisp(disp);
        m_flags &= ~1;
    }
}

void GfMenuCharDataAdapter::changeCharData(unsigned char objType, unsigned int objId) {
    if (m_objType != objType) {
        m_objType = objType;
        setChange();
    }
    if (m_objId != objId) {
        m_objId = objId;
        setChange();
    }
}

void GfMenuCharDataAdapter::changeGfObj(GF_OBJ_HANDLE* handle) {
    if (m_converter != nullptr && m_converter->fromGfObj() != nullptr) {
        m_converter->fromGfObj()->m_handle = handle;
    }
}

void GfMenuCharDataAdapter::changePartyDriver(unsigned char party) {
    if (m_converter != nullptr && m_converter->fromPartyDriver() != nullptr) {
        PartyDriverConverter* converter = m_converter->fromPartyDriver();
        converter->m_party = party;
    }
}

void GfMenuCharDataAdapter::changePartyBlade(unsigned char party, unsigned char slot) {
    if (m_converter != nullptr && m_converter->fromPartyBlade() != nullptr) {
        PartyBladeConverter* converter = m_converter->fromPartyBlade();
        converter->m_party = party;
        converter->m_slot = slot;
    }
}

unsigned int GfMenuCharDataAdapter::getBL_FieldSkillIndex(const DataParamAcc& acc) {
    unsigned int count = 0;
    for (unsigned int i = 0; i < 3; i++) {
        if (acc.getFieldSkill(i, false) != 0 && acc.getFieldSkillLevel(i, false) != 0) {
            if (count == m_index) {
                return i;
            }
            count++;
        }
    }
    return 3;
}

unsigned int GfMenuCharDataAdapter::getBL_SkillIndex(const DataParamAcc& acc) {
    unsigned int count = 0;
    for (unsigned int i = 0; i < 3; i++) {
        if (acc.getBladeSkill(i, false) != 0 && acc.getBladeSkillLevel(i, false) != 0) {
            if (count == m_index) {
                return i;
            }
            count++;
        }
    }
    return 3;
}

void GfMenuCharDataAdapter::GfObjConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    GfObjAcc acc(m_handle);
    objType = acc.getType();
    objId = acc.getBdatId();
}

GfMenuCharDataAdapter::GfObjConverter* GfMenuCharDataAdapter::GfObjConverter::fromGfObj() {
    return this;
}

GfMenuCharDataAdapter::PartyDriverConverter* GfMenuCharDataAdapter::IConverter::fromPartyDriver() {
    return nullptr;
}

GfMenuCharDataAdapter::PartyBladeConverter* GfMenuCharDataAdapter::IConverter::fromPartyBlade() {
    return nullptr;
}

GfMenuCharDataAdapter::GfObjConverter* GfMenuCharDataAdapter::IConverter::fromGfObj() {
    return nullptr;
}

void GfMenuCharDataAdapter::PartyDriverConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    GfObjAcc acc(GfGameParty::getHandleDriver(m_party, 0));
    objType = acc.getType();
    objId = acc.getBdatId();
}

GfMenuCharDataAdapter::PartyDriverConverter* GfMenuCharDataAdapter::PartyDriverConverter::fromPartyDriver() {
    return this;
}

void GfMenuCharDataAdapter::PartyBladeConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    unsigned int party = getParty();
    bool back = m_back;
    objType = 4;
    if (back) {
        objId = GfMenuObjUtil::getBladeIDFromPartyBackSlot(party, m_slot, m_flag);
    } else {
        objId = GfMenuObjUtil::getBladeIDFromPartySlot(party, m_slot, m_flag);
    }
}

GfMenuCharDataAdapter::PartyBladeConverter* GfMenuCharDataAdapter::PartyBladeConverter::fromPartyBlade() {
    return this;
}

void GfMenuCharDataAdapter::DriverListConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    int index = m_index;
    if (index == -1) {
        index = m_list->getIndex(true);
    }
    if (index != -1 && index < m_list->getSize()) {
        objType = 3;
        objId = m_list->getContents(m_list->getPageIndex(index)).m_driver;
    }
}

void GfMenuCharDataAdapter::BladeListConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    int index = m_index;
    if (index == -1) {
        index = m_list->getIndex(true);
    }
    if (index != -1 && index < m_list->getSize()) {
        objType = 4;
        objId = m_list->getContents(m_list->getPageIndex(index)).m_blade;
    }
}

void GfMenuCharDataAdapter::EnemyListConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    int index = m_index;
    if (index == -1) {
        index = m_list->getIndex(true);
    }
    if (index != -1 && index < m_list->getSize()) {
        objType = 5;
        objId = m_list->getContents(m_list->getPageIndex(index)).m_enemyId;
    }
}

void GfMenuCharDataAdapter::EnBookListConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    int index = m_index;
    if (index == -1) {
        index = m_list->getIndex(true);
    }
    if (index != -1 && index < m_list->getSize()) {
        unsigned int id = m_list->getContents(m_list->getPageIndex(index)).m_id;
        objType = 5;
        objId = mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys()->getBTL_EnBookBaseEnemyID(id);
    }
}

void GfMenuCharDataAdapter::NamedListConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    int index = m_index;
    if (index == -1) {
        index = m_list->getIndex(true);
    }
    if (index != -1 && index < m_list->getSize()) {
        unsigned int id = m_list->getContents(m_list->getPageIndex(index)).m_id;
        objType = 5;
        if (GfGameManager::isGameTypeIra()) {
            objId = mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys()->getBTL_NamedListIraEnemyID(id);
        } else {
            objId = mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys()->getBTL_NamedListEnemyID(id);
        }
    }
}

void GfMenuCharDataAdapter::ReferenceDriverConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    objType = 3;
    objId = GfMenuReference::getReferenceDriverID(m_index);
}

void GfMenuCharDataAdapter::ReferenceBladeConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    objType = 4;
    objId = GfMenuReference::getReferenceBladeID(m_index);
}

void GfMenuCharDataAdapter::ReferenceBladeSetConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    DataParamAcc acc(3, GfMenuReference::getReferenceDriverID(m_index), static_cast<GimmickType>(0));
    if (acc.isValid()) {
        if (GfMenuObjUtil::isValidExpansion(3)) {
            mm::mtl::FixedVector<unsigned short, 32> drivers;
            GfDataDriver::getIraBack(drivers, getDriverId(acc));
            if (static_cast<unsigned long>(m_slot) < drivers.size()) {
                objType = 4;
                objId = GfDataDriver::isActivateUnuse(drivers[m_slot]) ? 0 : GfDataDriver::getIraBlade(drivers[m_slot], -1);
            }
        } else {
            unsigned int blade = GfMenuObjUtil::getBladeIDFromDriverSlot(getDriverId(acc), m_slot);
            objType = 4;
            objId = blade;
        }
    }
}

void GfMenuCharDataAdapter::BladeListOwnerDriverConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    int index = m_index;
    if (index == -1) {
        index = m_list->getIndex(true);
    }
    if (index != -1 && index < m_list->getSize()) {
        objType = 3;
        objId = GfDataBlade::getCreator(m_list->getContents(m_list->getPageIndex(index)).m_blade);
    }
}

void GfMenuCharDataAdapter::BladeListSetDriverConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    int index = m_index;
    if (index == -1) {
        index = m_list->getIndex(true);
    }
    if (index != -1 && index < m_list->getSize()) {
        objType = 3;
        objId = GfDataBlade::getSetDriver(m_list->getContents(m_list->getPageIndex(index)).m_blade);
    }
}

void GfMenuCharDataAdapter::ReferenceBladeOwnerDriverConverter::getCharData(unsigned char& objType,
                                                                            unsigned int& objId) {
    objType = 3;
    objId = 0;
    if (GfMenuObjUtil::isValidExpansion(3)) {
        const GfMenuReference::IraCharInfo* owner = GfMenuReference::getIraCharInfoFromFromID(m_blade);
        if (owner != nullptr) {
            objType = 3;
            objId = owner->m_driver;
        }
    }
}

void GfMenuCharDataAdapter::IraDriverListFormConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    objType = 3;
    objId = 0;
    if (GfMenuObjUtil::isValidExpansion(3)) {
        unsigned int driver = m_list->getContents(m_index).m_driver;
        if (driver != 0) {
            int partyId = GfDataParty::getDriverPartyID(driver);
            if (partyId != -1) {
                objId = GfDataParty::getDriver(partyId, m_party);
            }
        }
    }
}

void GfMenuCharDataAdapter::NpcIDListConverter::getCharData(unsigned char& objType, unsigned int& objId) {
    int index = m_index;
    if (index == -1) {
        index = m_list->getIndex(true);
    }
    if (index != -1 && index < m_list->getSize()) {
        unsigned int id = m_list->getContents(m_list->getPageIndex(index)).m_id;
        objType = 6;
        objId = id;
    }
}

}  // namespace gf
