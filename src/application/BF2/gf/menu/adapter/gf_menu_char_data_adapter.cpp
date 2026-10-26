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
#include "classes/gf/TUnk_B5B878.h"
#include "classes/gf/TUnk_B5B908.h"
#include "classes/gf/TUnk_B5B938.h"
#include "classes/gf/TUnk_B5B968.h"
#include "classes/gf/TUnk_B5B9C8.h"
#include "classes/gf/TUnk_B5B9F8.h"
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
    {&GfMenuCharDataAdapter::fn_7100338A74, {1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_InMercenry, {3, 0, 0}},
    {&GfMenuCharDataAdapter::update_EN_BookID, {0, 0, 9999}},
    {&GfMenuCharDataAdapter::fn_7100338D80, {0, 0, 999}},
    {&GfMenuCharDataAdapter::update_EN_Family, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_EN_Genus, {2, 0, 0}},
    {&GfMenuCharDataAdapter::update_EN_RewardExp, {0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_EN_RewardGold, {0, 0, 999999999}},
    {&GfMenuCharDataAdapter::fn_7100339058, {7, 4, 0}},
    {&GfMenuCharDataAdapter::fn_7100339108, {7, 4, 0}},
    {&GfMenuCharDataAdapter::fn_71003391AC, {3, 0, 0}},
    {&GfMenuCharDataAdapter::fn_7100339224, {3, 0, 0}},
    {&GfMenuCharDataAdapter::fn_710033929C, {3, 0, 0}},
    {&GfMenuCharDataAdapter::fn_7100339314, {3, 0, 0}},
    {&GfMenuCharDataAdapter::fn_71003393E4, {3, 0, 0}},
    {&GfMenuCharDataAdapter::fn_71003394AC, {3, 0, 0}},
    {&GfMenuCharDataAdapter::fn_7100339574, {0, 0, 100}},
    {&GfMenuCharDataAdapter::fn_71003396C4, {3, 0, 0}},
    {&GfMenuCharDataAdapter::fn_710033973C, {1, 0, 0}},
    {&GfMenuCharDataAdapter::fn_7100339800, {1, 0, 0}},
    {&GfMenuCharDataAdapter::fn_710033987C, {2, 0, 0}},
    {&GfMenuCharDataAdapter::fn_71003399DC, {1, 0, 0}},
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

bool GfMenuCharDataAdapter::fn_7100338D80(const DataParamAcc& acc) {
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

bool GfMenuCharDataAdapter::fn_71003391AC(const DataParamAcc& acc) {
    if (GfMenuObjUtil::fn_710048FD30(3) && acc.getObjType() == 3) {
        return GfMenuReference::fn_7100367EF4(getDriverId(acc)) == 0;
    }
    return false;
}

bool GfMenuCharDataAdapter::fn_7100339224(const DataParamAcc& acc) {
    if (GfMenuObjUtil::fn_710048FD30(3) && acc.getObjType() == 3) {
        return GfMenuReference::fn_7100367EF4(getDriverId(acc)) == 1;
    }
    return false;
}

bool GfMenuCharDataAdapter::fn_710033929C(const DataParamAcc& acc) {
    if (GfMenuObjUtil::fn_710048FD30(3) && acc.getObjType() == 3) {
        return GfMenuReference::fn_7100367EF4(getDriverId(acc)) != 2;
    }
    return false;
}

bool GfMenuCharDataAdapter::fn_71003396C4(const DataParamAcc& acc) {
    if (GfMenuObjUtil::fn_710048FD30(3) && acc.getObjType() == 3) {
        return !GfDataDriver::fn_7100237A94(getDriverId(acc));
    }
    return false;
}

bool GfMenuCharDataAdapter::fn_7100339800(const DataParamAcc& acc) {
    if (GfMenuObjUtil::fn_710048FD30(3) && acc.getObjType() == 6) {
        unsigned int value = GfDataBlade::fn_710024DA88(getBladeId(acc));
        if (value != 0) {
            setNumber(value - 0xED03);
            return true;
        }
    }
    return false;
}

bool GfMenuCharDataAdapter::fn_71003399DC(const DataParamAcc& acc) {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
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

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromGfObj(unsigned int handle, unsigned int kind,
                                                              GF_OBJ_HANDLE* object, bool changed) {
#line 962
    GfObjConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjConverter(object);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromPartyDriver(unsigned int handle, unsigned int kind,
                                                                    unsigned char party, bool changed) {
#line 969
    PartyDriverConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        PartyDriverConverter(party);
    return createFromCoverter(handle, kind, converter, changed);
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

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromEnemyList(unsigned int handle, unsigned int kind,
                                                                  const GfMenuEnemyList* list, int index,
                                                                  bool changed) {
#line 999
    EnemyListConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        EnemyListConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromEnBookList(unsigned int handle, unsigned int kind,
                                                                   const GfMenuIDList* list, int index,
                                                                   bool changed) {
#line 1006
    EnBookListConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        EnBookListConverter(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::fn_710033A1F0(unsigned int handle, unsigned int kind,
                                                            const GfMenuIDList* list, int index, bool changed) {
#line 1013
    TUnk_B5B878* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5B878(list, index);
    return createFromCoverter(handle, kind, converter, changed);
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

GfMenuCharDataAdapter* GfMenuCharDataAdapter::fn_710033A3D4(unsigned int handle, unsigned int kind,
                                                            unsigned int index, int slot, bool changed) {
#line 1041
    TUnk_B5B908* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5B908(index, slot);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::fn_710033A480(unsigned int handle, unsigned int kind,
                                                            const GfMenuBladeList* list, int index, bool changed) {
#line 1055
    TUnk_B5B938* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5B938(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::fn_710033A5D0(unsigned int handle, unsigned int kind,
                                                            const GfMenuBladeList* list, int index, bool changed) {
#line 1062
    TUnk_B5B968* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5B968(list, index);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::createFromReferenceBladeOwnerDriver(unsigned int handle,
                                                                                  unsigned int kind,
                                                                                  unsigned int blade, bool changed) {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return nullptr;
    }
#line 1082
    ReferenceBladeOwnerDriverConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        ReferenceBladeOwnerDriverConverter(blade);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::fn_710033A7EC(unsigned int handle, unsigned int kind,
                                                            const GfMenuDriverList* list, unsigned int index,
                                                            unsigned int party, bool changed) {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return nullptr;
    }
#line 1092
    TUnk_B5B9C8* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5B9C8(list, index, party);
    return createFromCoverter(handle, kind, converter, changed);
}

GfMenuCharDataAdapter* GfMenuCharDataAdapter::fn_710033A940(unsigned int handle, unsigned int kind,
                                                            const GfMenuIDList* list, int index, bool changed) {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return nullptr;
    }
#line 1102
    TUnk_B5B9F8* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5B9F8(list, index);
    return createFromCoverter(handle, kind, converter, changed);
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

void TUnk_B5B878::getCharData(unsigned char& objType, unsigned int& objId) {
    int index = m_index;
    if (index == -1) {
        index = m_list->getIndex(true);
    }
    if (index != -1 && index < m_list->getSize()) {
        unsigned int id = m_list->getContents(m_list->getPageIndex(index)).m_id;
        objType = 5;
        if (GfGameManager::fn_71002A9E68()) {
            objId = mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys()->fn_71001F4EB8(id);
        } else {
            objId = mm::mtl::PtrSingleton<GfBdatChrEnArrange>::sys()->fn_71001F4DE8(id);
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

void TUnk_B5B908::getCharData(unsigned char& objType, unsigned int& objId) {
    DataParamAcc acc(3, GfMenuReference::getReferenceDriverID(m_index), static_cast<GimmickType>(0));
    if (acc.isValid()) {
        if (GfMenuObjUtil::fn_710048FD30(3)) {
            mm::mtl::FixedVector<unsigned short, 32> drivers;
            GfDataDriver::fn_71002416B4(drivers, getDriverId(acc));
            if (static_cast<unsigned long>(m_slot) < drivers.size()) {
                objType = 4;
                objId = GfDataDriver::isActivateUnuse(drivers[m_slot]) ? 0 : GfDataBlade::fn_7100237B70(drivers[m_slot], -1);
            }
        } else {
            unsigned int blade = GfMenuObjUtil::getBladeIDFromDriverSlot(getDriverId(acc), m_slot);
            objType = 4;
            objId = blade;
        }
    }
}

void TUnk_B5B938::getCharData(unsigned char& objType, unsigned int& objId) {
    int index = m_index;
    if (index == -1) {
        index = m_list->getIndex(true);
    }
    if (index != -1 && index < m_list->getSize()) {
        objType = 3;
        objId = GfDataBlade::getCreator(m_list->getContents(m_list->getPageIndex(index)).m_blade);
    }
}

void TUnk_B5B968::getCharData(unsigned char& objType, unsigned int& objId) {
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
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        const GfMenuReference::BladeOwner* owner = GfMenuReference::fn_7100367BD8(m_blade);
        if (owner != nullptr) {
            objType = 3;
            objId = owner->m_driver;
        }
    }
}

void TUnk_B5B9C8::getCharData(unsigned char& objType, unsigned int& objId) {
    objType = 3;
    objId = 0;
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        unsigned int driver = m_list->getContents(m_index).m_driver;
        if (driver != 0) {
            int partyId = GfDataParty::getDriverPartyID(driver);
            if (partyId != -1) {
                objId = GfDataParty::getDriver(partyId, m_party);
            }
        }
    }
}

void TUnk_B5B9F8::getCharData(unsigned char& objType, unsigned int& objId) {
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
