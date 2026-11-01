#include "classes/gf/GfObjPropertyEnemy.h"
#include "classes/gf/GfObjPropertyBlade.h"
#include "gf/GfGameUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "btl/Misc.h"
#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter/IConverter.h"
#include "classes/gf/GfMenuGfObjAdapter/PartyDriverConverter.h"
#include "classes/gf/GfMenuGfObjAdapter/PartyBladeConverter.h"
#include "classes/gf/GfMenuGfObjAdapter/TargetEnemyConverter.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameVisible.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/GfObjPropertyCharacter.h"
#include "ui/UIStr.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"

namespace gf {

// Display callback and plugin settings for each adapter type, in create's index order.
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B5C160)
static GfMenuGfObjAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuGfObjAdapter::update_NowHp, {0, 0, 9999}},
    {&GfMenuGfObjAdapter::update_Battle, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_InfoBody, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_InfoDisp, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_InfoIcon, {1, 0, 0}},
    {&GfMenuGfObjAdapter::update_TargetDisp, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_AccessDisp, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_Lv, {0, 1, 999}},
    {&GfMenuGfObjAdapter::update_EN_ArtsName, {2, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ArtsID, {0, 0, 65535}},
    {&GfMenuGfObjAdapter::update_EN_ElemComboName, {2, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_Aggressive, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_Link, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_Arts, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_FightComboIcon, {1, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_FightComboName, {2, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_FightComboTime, {0, 0, 100}},
    {&GfMenuGfObjAdapter::update_EN_FightComboSuspend, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ElemComboLv, {0, 0, 2}},
    {&GfMenuGfObjAdapter::update_EN_ElemComboTime, {0, 0, 100}},
    {&GfMenuGfObjAdapter::update_EN_ElemComboState, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ElemComboAttrIcon, {1, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ElemComboAttrCol, {8, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ElemComboAttrPtn, {9, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ElemComboSuspend, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_WeakAttrIcon, {1, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_WeakAttrColor, {8, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ResAttrOn, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ResAttrTarget, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ResAttrBurst, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ResAttrHP, {1, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_ElemEffID, {0, 0, 65535}},
    {&GfMenuGfObjAdapter::update_EN_TypeIcon, {1, 0, 0}},
    {&GfMenuGfObjAdapter::update_EN_Scout, {1, 0, 0}},
    {&GfMenuGfObjAdapter::fn_710033FB0C, {3, 0, 0}},
    {&GfMenuGfObjAdapter::fn_710033FB70, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_BL_Kizuna, {0, 0, 7}},
    {&GfMenuGfObjAdapter::update_BL_Special, {0, 0, 100}},
    {&GfMenuGfObjAdapter::update_BL_SpecialLv, {0, 0, 4}},
    {&GfMenuGfObjAdapter::update_BL_ChangeRecast, {0, 0, 100}},
    {&GfMenuGfObjAdapter::update_BL_ChangeRecast2, {0, 0, 100}},
    {&GfMenuGfObjAdapter::update_BL_DispCurrent, {3, 0, 0}},
    {&GfMenuGfObjAdapter::update_BL_DispComboReady, {3, 0, 0}},
    {&GfMenuGfObjAdapter::fn_7100340094, {1, 0, 0}},
    {&GfMenuGfObjAdapter::fn_7100340154, {0, 0, 9999}},
};

namespace {
// inline (the name is not the original's): the object's enemy property when the object is an enemy
inline GfObjPropertyEnemy* getEnemyProperty(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 5) {
        return nullptr;
    }
    GfObjProperty* property = GfObjUtil::getProperty(handle);
    if (property == nullptr) {
        return nullptr;
    }
    return property->getEnemy();
}
// inline (the name is not the original's): the object's property as an enemy's, without checking its type
inline GfObjPropertyEnemy* getEnemy(GF_OBJ_HANDLE* handle) {
    GfObjProperty* property = GfObjUtil::getProperty(handle);
    if (property == nullptr) {
        return nullptr;
    }
    return property->getEnemy();
}
// inline (the name is not the original's): the object's property as a blade's, without checking its type
inline GfObjPropertyBlade* getBlade(GF_OBJ_HANDLE* handle) {
    GfObjProperty* property = GfObjUtil::getProperty(handle);
    if (property == nullptr) {
        return nullptr;
    }
    return property->getBlade();
}
}  // namespace

GfMenuGfObjAdapter::~GfMenuGfObjAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
}

GfMenuGfObjAdapter* GfMenuGfObjAdapter::create(unsigned int handle, unsigned int type, GF_OBJ_HANDLE* obj,
                                               bool changed) {
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
    bool managerFlag = !(type == 2 || type == 3);
#line 266
    GfMenuGfObjAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuGfObjAdapter(plugin, managerFlag, changed);
    if (adapter == nullptr) {
        return nullptr;
    }
    adapter->m_update.set(adapter, setup.func);
    adapter->m_handle = obj;
    plugin->release();
    return adapter;
}

bool GfMenuGfObjAdapter::update_NowHp(GF_OBJ_HANDLE* handle) {
    unsigned int hp;
    unsigned int maxHp;
    if (!GfGameUtil::getNowHpForUi(handle, &hp) || !GfGameUtil::getMaxHpForUi(handle, &maxHp)) {
        return false;
    }
    setNumberMax(maxHp);
    setNumber(hp);
    return true;
}

bool GfMenuGfObjAdapter::update_Battle(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() == 5) {
        return true;
    }
    GfObjProperty* property = GfObjUtil::getProperty(handle);
    if (property == nullptr) {
        return false;
    }
    return property->m_character != nullptr && property->m_character->pad_30;
}

bool GfMenuGfObjAdapter::update_InfoBody(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if ((acc.getAttribute() & 8) == 0 && !GfGameVisible::isVisible(handle)) {
        return false;
    }
    if (GfMenuManager::isBattleState(1) && acc.getType() == 5) {
        GfObjProperty* property = GfObjUtil::getProperty(handle);
        if (property == nullptr) {
            return false;
        }
        GfObjPropertyCharacter* character = property->m_character;
        if (character == nullptr) {
            return false;
        }
        if (GfMenuManager::getTargetObjHandle() == handle) {
            if (character->pad_30) {
                return false;
            }
        } else if (!character->pad_30) {
            return false;
        }
    }
    if (GfGameUtil::isUiNameDistMatch(handle)) {
        return true;
    }
    return GfMenuManager::getTargetObjHandle() == handle;
}

bool GfMenuGfObjAdapter::update_InfoDisp(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if ((acc.getAttribute() & 8) == 0 && !GfGameVisible::isVisible(handle)) {
        return false;
    }
    return GfGameUtil::isUiInfoIconDistMatch(handle);
}

bool GfMenuGfObjAdapter::update_InfoIcon(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if ((acc.getAttribute() & 8) == 0 && !GfGameVisible::isVisible(handle)) {
        return false;
    }
    int icon = GfGameUtil::getUiInfoIconBdatId(handle);
    if (icon == -1) {
        return false;
    }
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    return GfGameUtil::isUiInfoIconDistMatch(handle);
}

bool GfMenuGfObjAdapter::update_TargetDisp(GF_OBJ_HANDLE* handle) {
    return GfMenuManager::getTargetObjHandle() == handle;
}

bool GfMenuGfObjAdapter::update_AccessDisp(GF_OBJ_HANDLE* handle) {
    return GfMenuManager::getAccessObjHandle() == handle;
}

bool GfMenuGfObjAdapter::update_EN_Lv(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    bool result;
    if (acc.isValid()) {
        setNumber(acc.getLevel(false));
        result = true;
    } else {
        result = false;
    }
    return result;
}

bool GfMenuGfObjAdapter::update_EN_ArtsName(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemy(handle);
    if (enemy == nullptr || enemy->m_artsId == 0) {
        return false;
    }
    ui::UIStr name = GfMenuObjUtil::getEnemyArtsName(enemy->m_artsId);
    bool result;
    if (name.isValid()) {
        setText(name);
        result = true;
    } else {
        result = false;
    }
    return result;
}

bool GfMenuGfObjAdapter::update_EN_ArtsID(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemy(handle);
    if (enemy == nullptr) {
        return false;
    }
    setNumber(enemy->m_artsId);
    return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboName(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 5) {
        return false;
    }
    GfObjPropertyEnemy* enemy = getEnemy(handle);
    if (enemy == nullptr || enemy->m_elementComboId == 0) {
        return false;
    }
    ui::UIStr name = GfMenuObjUtil::getElementComboName(enemy->m_elementComboId);
    setText(name);
    return true;
}

bool GfMenuGfObjAdapter::update_EN_Aggressive(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 5) {
        return false;
    }
    GF_OBJ_HANDLE* obj = acc.getHandle();
    GfGameUtil::UiEnemyStatusIconInfo info;
    if (obj == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    info.create(obj);
    return info.m_aggressive;
}

bool GfMenuGfObjAdapter::update_EN_Link(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 5) {
        return false;
    }
    GF_OBJ_HANDLE* obj = acc.getHandle();
    GfGameUtil::UiEnemyStatusIconInfo info;
    if (obj == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return false;
    }
    info.create(obj);
    return info.m_link;
}

bool GfMenuGfObjAdapter::update_EN_Arts(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    return enemy->m_artsId != 0;
}

bool GfMenuGfObjAdapter::update_EN_FightComboIcon(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemy(handle);
    if (enemy == nullptr || enemy->m_fightCombo == 0) {
        return false;
    }
    setNumber(enemy->m_fightCombo - 1);
    return true;
}

bool GfMenuGfObjAdapter::update_EN_FightComboName(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemy(handle);
    if (enemy == nullptr || enemy->m_fightCombo == 0) {
        return false;
    }
    unsigned int id = GfMenuObjUtil::getMsgIDFromList(0x13F, enemy->m_fightCombo);
    setText(ui::UIStr(GfDataBdat::getFP(0x120), id));
    return true;
}

bool GfMenuGfObjAdapter::update_EN_FightComboTime(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemy(handle);
    if (enemy == nullptr) {
        return false;
    }
    setNumber(enemy->m_fightComboTime * 100.0f);
    return true;
}

bool GfMenuGfObjAdapter::update_EN_FightComboSuspend(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    return enemy->m_fightComboSuspend;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboLv(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr || enemy->m_elementComboId == 0 || enemy->m_elementComboLv == 0) {
        return false;
    }
    setNumber(enemy->m_elementComboLv - 1);
    return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboTime(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr || enemy->m_elementComboId == 0 || enemy->m_elementComboLv == 3) {
        return false;
    }
    setNumber(enemy->m_elementComboTime * 100.0f);
    return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboState(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    return enemy->m_elementComboId != 0;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboAttrIcon(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr || enemy->m_elementComboId == 0) {
        return false;
    }
    unsigned char attr = GfMenuObjUtil::getElementComboAtr(enemy->m_elementComboId);
    if (attr == 0) {
        return false;
    }
    setNumber(attr);
    return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboAttrCol(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr || enemy->m_elementComboId == 0) {
        return false;
    }
    mm::mtl::FixStr<32> color;
    color.format("elemental%02d", GfMenuObjUtil::getElementComboAtr(enemy->m_elementComboId));
    setColor(color.m_str);
    return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboAttrPtn(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr || enemy->m_elementComboId == 0) {
        return false;
    }
    mm::mtl::FixStr<32> pattern;
    pattern.format("element%02d", GfMenuObjUtil::getElementComboAtr(enemy->m_elementComboId));
    setTextFacePattern(pattern.m_str);
    return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboSuspend(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    return enemy->m_elementComboSuspend;
}

namespace {
// inline (the name is not the original's): the highest element (1..8) the flags hold, 0 for none
inline unsigned int getWeakAttr(unsigned int flags) {
    unsigned int attr = 0;
    if (flags & 2) attr = 1;
    if (flags & 4) attr = 2;
    if (flags & 8) attr = 3;
    if (flags & 0x10) attr = 4;
    if (flags & 0x20) attr = 5;
    if (flags & 0x40) attr = 6;
    if (flags & 0x80) attr = 7;
    if (flags & 0x100) attr = 8;
    return attr;
}
}  // namespace

bool GfMenuGfObjAdapter::update_EN_WeakAttrIcon(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    unsigned int attr = getWeakAttr(enemy->m_weakAttr);
    setNumber(attr);
    return attr != 0;
}

bool GfMenuGfObjAdapter::update_EN_WeakAttrColor(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    unsigned int attr = getWeakAttr(enemy->m_weakAttr);
    mm::mtl::FixStr<32> color;
    color.format("elemental%02d", attr);
    setColor(color.m_str);
    return attr != 0;
}

bool GfMenuGfObjAdapter::update_EN_ResAttrOn(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    if (enemy->m_resAttrList.size() > m_index) {
        unsigned int attr = enemy->m_resAttrList[m_index];
        if (attr >= 1 && attr <= 8) {
            return enemy->m_resAttrs[attr].m_flags & 1;
        }
    }
    return false;
}

bool GfMenuGfObjAdapter::update_EN_ResAttrTarget(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    if (enemy->m_resAttrList.size() > m_index) {
        unsigned int attr = enemy->m_resAttrList[m_index];
        if (attr >= 1 && attr <= 8) {
            unsigned short flags = enemy->m_resAttrs[attr].m_flags;
            if ((flags & 4) == 0) {
                return (flags >> 1) & 1;
            }
        }
    }
    return false;
}

bool GfMenuGfObjAdapter::update_EN_ResAttrBurst(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    if (enemy->m_resAttrList.size() > m_index) {
        unsigned int attr = enemy->m_resAttrList[m_index];
        if (attr >= 1 && attr <= 8) {
            return (enemy->m_resAttrs[attr].m_flags >> 2) & 1;
        }
    }
    return false;
}

bool GfMenuGfObjAdapter::update_EN_ResAttrHP(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    if (enemy->m_resAttrList.size() > m_index) {
        unsigned int attr = enemy->m_resAttrList[m_index];
        if (attr >= 1 && attr <= 8) {
            const GfObjPropertyEnemy::ResAttr& res = enemy->m_resAttrs[attr];
            int level = res.m_level;
            setNumber(attr * 4 - 1 - level);
            return true;
        }
    }
    return false;
}

bool GfMenuGfObjAdapter::update_EN_ElemEffID(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    setNumber(enemy->m_elemEffId);
    return true;
}

bool GfMenuGfObjAdapter::update_EN_TypeIcon(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 5) {
        return false;
    }
    if (GfMenuObjUtil::isEnemyBoss(handle)) {
        setNumber(2);
    } else if (GfMenuObjUtil::isEnemyNamed(handle)) {
        setNumber(1);
    } else {
        setNumber(0);
    }
    return true;
}

bool GfMenuGfObjAdapter::update_EN_Scout(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr || !enemy->m_scout) {
        return false;
    }
    setNumber(0);
    return true;
}

bool GfMenuGfObjAdapter::fn_710033FB0C(GF_OBJ_HANDLE* handle) {
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    return enemy->pad_154;
}

bool GfMenuGfObjAdapter::fn_710033FB70(GF_OBJ_HANDLE* handle) {
    if (!GfMenuObjUtil::fn_710048FD30(1) && !GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    GfObjPropertyEnemy* enemy = getEnemyProperty(handle);
    if (enemy == nullptr) {
        return false;
    }
    return enemy->pad_155;
}

bool GfMenuGfObjAdapter::update_BL_Kizuna(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 4) {
        return false;
    }
    GfObjPropertyBlade* blade = getBlade(handle);
    if (blade == nullptr) {
        return false;
    }
    setNumber(btl::Misc::GetKizunaStage(blade->m_kizuna, nullptr) + 1);
    return true;
}

bool GfMenuGfObjAdapter::update_BL_Special(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 4) {
        return false;
    }
    GfObjPropertyBlade* blade = getBlade(handle);
    if (blade == nullptr) {
        return false;
    }
    int number;
    if (m_index == blade->m_specialLv) {
        number = blade->m_specialGauge * 100.0f;
    } else if (m_index > blade->m_specialLv) {
        number = 0;
    } else {
        number = getNumberMax();
    }
    setNumber(number);
    return number > 0;
}

bool GfMenuGfObjAdapter::update_BL_SpecialLv(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 4) {
        return false;
    }
    GfObjPropertyBlade* blade = getBlade(handle);
    if (blade == nullptr) {
        return false;
    }
    setNumber(blade->m_specialLv);
    return true;
}

bool GfMenuGfObjAdapter::update_BL_ChangeRecast(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 4) {
        return false;
    }
    if (GfMenuManager::isBattleState(5)) {
        DataParamAcc param(handle);
        if (!param.isValid()) {
            return false;
        }
        if (param.isValid() && param.getBdatId() == 1003) {
            if (GfMenuManager::isBattleState(3)) {
                setNumber(100);
                return true;
            }
        } else if (GfDataBlade::getSetDriver(1003) ==
                   GfDataBlade::getSetDriver(param.isValid() ? param.getBdatId() : 0)) {
            setNumber(0);
            return false;
        }
    }
    GfObjPropertyBlade* blade = getBlade(handle);
    if (blade == nullptr) {
        return false;
    }
    setNumber(blade->m_changeRecast * 100.0f);
    return blade->m_changeRecast > 0.0f;
}

bool GfMenuGfObjAdapter::update_BL_ChangeRecast2(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 4) {
        return false;
    }
    if (GfMenuManager::isBattleState(5)) {
        DataParamAcc param(handle);
        if (!param.isValid()) {
            return false;
        }
        if (param.isValid() && param.getBdatId() == 1003) {
            if (GfMenuManager::isBattleState(3)) {
                return false;
            }
            setNumber(GfMenuReference::getAwakeningRestTimeRatio() * 100.0f);
            return true;
        }
    }
    return false;
}

bool GfMenuGfObjAdapter::update_BL_DispCurrent(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 4) {
        return false;
    }
    if (GfMenuManager::isBattleState(3)) {
        int id = GfMenuReference::getChainAttackActionPartyID();
        if (id >= 0 && static_cast<unsigned int>(id) < 3) {
            return false;
        }
    }
    return GfMenuObjUtil::getLeaderBladeHandle(true) == handle;
}

bool GfMenuGfObjAdapter::update_BL_DispComboReady(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 4 || GfMenuManager::isBattleState(3)) {
        return false;
    }
    GfObjPropertyBlade* blade = getBlade(handle);
    if (blade == nullptr) {
        return false;
    }
    if (blade->m_comboReady & 1) {
        return true;
    }
    return (blade->m_comboReady & 2) != 0;
}

bool GfMenuGfObjAdapter::fn_7100340094(GF_OBJ_HANDLE* handle) {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    GfObjAcc acc(handle);
    if (acc.getType() != 6) {
        return false;
    }
    switch (GfDataBlade::fn_710024DD94(acc.fn_7100523B74())) {
    case 0:
    case 2:
        if (!fn_71002D9B5C(handle)) {
            return false;
        }
        setNumber(0);
        return true;
    case 1:
    case 3:
        setNumber(1);
        return true;
    default:
        return true;
    }
}

bool GfMenuGfObjAdapter::fn_7100340154(GF_OBJ_HANDLE* handle) {
    if (!GfMenuObjUtil::fn_710048FD30(3)) {
        return false;
    }
    GfObjProperty* property = GfObjUtil::getProperty(handle);
    if (property == nullptr) {
        return false;
    }
    GfObjPropertyCharacter* character = property->m_character;
    if (character == nullptr) {
        return false;
    }
    unsigned int hp;
    unsigned int maxHp;
    if (!GfGameUtil::getNowHpForUi(handle, &hp) || !GfGameUtil::getMaxHpForUi(handle, &maxHp)) {
        return false;
    }
    setNumber(character->pad_8 + hp);
    setNumberMax(maxHp);
    return true;
}

GfMenuGfObjAdapter* GfMenuGfObjAdapter::createFromPartyDriver(unsigned int handle, unsigned int type,
                                                              unsigned char driver, bool changed) {
    PartyDriverConverter* converter =
#line 294
        new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PartyDriverConverter(driver);
    GfMenuGfObjAdapter* adapter = create(handle, type, converter->getGfObjHandle(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuGfObjAdapter* GfMenuGfObjAdapter::createFromPartyBlade(unsigned int handle, unsigned int type,
                                                             unsigned char driver, int blade, bool changed,
                                                             bool flag) {
    PartyBladeConverter* converter =
#line 301
        new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) PartyBladeConverter(driver, blade, flag);
    GfMenuGfObjAdapter* adapter = create(handle, type, converter->getGfObjHandle(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuGfObjAdapter* GfMenuGfObjAdapter::createFromTargetEnemy(unsigned int handle, unsigned int type,
                                                              bool changed) {
    TargetEnemyConverter* converter =
#line 308
        new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TargetEnemyConverter();
    GfMenuGfObjAdapter* adapter = create(handle, type, converter->getGfObjHandle(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

void GfMenuGfObjAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        changeGfObj(m_converter->getGfObjHandle());
    }
    if ((m_flags & 3) != 0 && m_update.isValid()) {
        setDisp(m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) ? m_update(m_handle) : false);
        m_flags &= ~1;
    }
}

void GfMenuGfObjAdapter::changeGfObj(GF_OBJ_HANDLE* handle) {
    if (m_handle != handle) {
        m_handle = handle;
        setChange();
    }
}

void GfMenuGfObjAdapter::changePartyDriver(unsigned char driver) {
    if (m_converter != nullptr && m_converter->fromPartyDriver() != nullptr) {
        PartyDriverConverter* converter = m_converter->fromPartyDriver();
        converter->m_driver = driver;
    }
}

void GfMenuGfObjAdapter::changePartyBlade(unsigned char driver, unsigned char blade) {
    if (m_converter != nullptr && m_converter->fromPartyBlade() != nullptr) {
        PartyBladeConverter* converter = m_converter->fromPartyBlade();
        converter->m_driver = driver;
        converter->m_blade = blade;
    }
}

}  // namespace gf
