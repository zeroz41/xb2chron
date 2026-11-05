#include "classes/btl/UIManager.h"
#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/gf/GfMenuObjDamageBuff.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/btl/UIManager.h"
#include "btl/challenge_battle_manager.h"
#include "btl/siren_battle_manager.h"
#include "classes/btl/BattleCharacter.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/btl/BtlSystemBalanceAccess.h"
#include "classes/btl/ChainAttackManager.h"
#include "classes/btl/CharacterManager.h"
#include "classes/btl/CharacterParameter.h"
#include "classes/btl/SpAttackManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjActionWindow.h"
#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/gf/GfMenuObjBattleTelop.h"
#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/gf/GfMenuObjChainIcon.h"
#include "classes/gf/GfMenuObjDamageBuff.h"
#include "classes/gf/GfMenuObjElementEff.h"
#include "classes/gf/GfMenuObjSpecialGauge.h"
#include "classes/gf/GfMenuReference.h"
#include "gf/pc/StateUtil.h"
#include "fw/UpdateInfo.h"
#include "mm/Vec3.h"
#include "plugin/Bdat.h"
#include <algorithm>

namespace btl {

UIManager::~UIManager() {}

void UIManager::Destroy() {
    if (sys() != nullptr) {
        delete sys();
    }
}

void UIManager::NotifyMapChange() {
    int base = 0xC710 - Bdat::getIdTop(gf::GfDataBdat::getFP(0xFF));
    if (gf::GfGameFlag::getLocal(1, base + 0xC)) {
        gf::GfGameFlag::setLocal(1, base + 0xD, 1);
    }
    pad_bit19 = false;
}

void UIManager::NotifyRecordUpdate(gf::GF_OBJ_HANDLE* obj) {
    pad_38 = obj;
}

void UIManager::PreUpdate(const fw::UpdateInfo& info) {}

void UIManager::Update(const fw::UpdateInfo& info) {
    sys()->UpdateProc(info);
}

void UIManager::UpdateProc(const fw::UpdateInfo& info) {
    UpdateMenuData(info);
    if (m_elementCombo.m_exit) {
        if (m_elementCombo.m_context == nullptr || m_elementCombo.m_context->isTerm()) {
            m_elementCombo.clear();
        }
    }
    UpdateRescueUI();
    UpdatePartyGauge();
    UpdateBattleTime();
    UpdateTutorial(info);
}

void UIManager::UpdateRescueUI() {
    if (m_rescueObj != reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)) {
        if (!m_rescueOpen) {
            // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B94520)
            static unsigned int s_rescueKey = gf::pc::StateUtil::getFwPadKey("battle_rescue");
            gf::GfMenuObjActionWindow::OpenParam param;
            param.m_obj = m_rescueObj;
            param.m_button = s_rescueKey;
            gf::GfMenuObjActionWindow::openBattle(param);
            m_rescueOpen = true;
        }
    } else if (m_rescueOpen) {
        gf::GfMenuObjActionWindow::closeBattle();
        m_rescueOpen = false;
    }
    m_rescueObj = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
}

void UIManager::UpdateTutorial(const fw::UpdateInfo& info) {
    if (pad_e0 > 0.0f) {
        pad_e0 -= info.m_frameTime;
    }
    if (m_tutorials.empty()) {
        return;
    }
    if (!((BattleGlobal::sys()->pad_bit1 &&
           CharacterManager::sys()->IsExistBattleEnemy(nullptr, reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1), false) &&
           BattleGlobal::sys()->IsEnableBattle()) ||
          ChallengeBattleManager::sys()->IsProc())) {
        m_tutorials.clear();
        pad_e0 = 0.0f;
        pad_bit17 = false;
        pad_bit18 = false;
        return;
    }
    // the least time a queued tutorial waits while the battle is busy: 0.3 s in 1/0x40000 units
    unsigned int minTime;
    if (!((!BattleGlobal::sys()->m_challengeAnySuccess && ChainAttackManager::sys()->IsProc(false)) ||
          BattleGlobal::sys()->m_uniteComboCamera || BattleGlobal::sys()->pad_bit12 ||
          BattleGlobal::sys()->m_elementalCombo.m_camera || SpAttackManager::sys()->m_camera ||
          !SirenBattleManager::sys()->IsEnableOperate() || BattleGlobal::sys()->IsFutureView())) {
        minTime = 0;
    } else {
        minTime = 0x13333;
    }
    unsigned int step = info.m_frameTime * 0x40000;
    if (step != 0) {
        step++;
    }
    std::for_each(m_tutorials.begin(), m_tutorials.end(), [&](TutorialInfo& tutorial) {
        if (tutorial.m_time <= step) {
            tutorial.m_time = 0;
        } else {
            tutorial.m_time -= step;
        }
        tutorial.m_time = tutorial.m_time > minTime ? tutorial.m_time : minTime;
    });
    if (minTime != 0 || BattleGlobal::sys()->pad_bit43) {
        return;
    }
    for (TutorialInfo* it = m_tutorials.begin(); it != m_tutorials.end(); ++it) {
        if (it->m_time != 0) {
            continue;
        }
        if (it->pad_bit30 && !(it->pad_bit31 ? pad_bit16 : pad_bit15)) {
            continue;
        }
        if (it->m_id != 0x1C || !ChallengeBattleManager::sys()->IsResult()) {
            if (gf::GfMenuManager::startTutorial(it->m_id)) {
                pad_e0 = 1.0f;
                BattleGlobal::sys()->SetPause(8, true);
            }
        }
        m_tutorials.erase(it);
        pad_bit17 = false;
        pad_bit18 = false;
        for (TutorialInfo* rest = m_tutorials.begin(); rest != m_tutorials.end(); ++rest) {
            if (rest->m_force) {
                pad_bit17 = true;
            }
            if (rest->pad_bit30) {
                pad_bit18 = true;
            }
        }
        return;
    }
}

bool UIManager::RegisterTutorial(unsigned int id, float time, bool force) {
    int top = Bdat::getIdTop(gf::GfDataBdat::getFP(0xFF + BattleGlobal::sys()->m_challengeAnySuccess));
    if (gf::GfGameFlag::getLocal(1, id + 0xC710 - top)) {
        return false;
    }
    TutorialInfo info;
    info.m_id = id;
    info.m_time = time * 0x40000;
    info.m_force = force;
    if (force) {
        pad_bit17 = true;
    }
    if (id == 0x6C || (force && id != 1 && id != 0x66)) {
        info.pad_bit31 = id == 0x6C;
        info.pad_bit30 = true;
        pad_bit18 = true;
    }
    m_tutorials.push_back(info);
    return true;
}

unsigned int UIManager::StartElementalComboDirectionUI(int combo) {
    if (m_elementCombo.m_context != nullptr) {
        m_elementCombo.m_context->reset();
    } else {
        m_elementCombo.m_context = gf::GfMenuCallContext::create();
    }
    unsigned int id;
    if (m_elementCombo.m_context != nullptr) {
        id = m_elementComboSerial;
        m_elementComboSerial = id < 0xFFFFFFFE ? id + 1 : 1;
        gf::GfMenuObjElementEff::StartParam param;
        param.m_combo = combo;
        gf::GfMenuObjElementEff::start(m_elementCombo.m_context, param);
    } else {
        id = 0;
    }
    m_elementCombo.m_id = id;
    m_elementCombo.m_type = combo;
    m_elementCombo.m_exit = false;
    return id;
}

void UIManager::ExitElementalComboDirectionUI(unsigned int id) {
    if (id != 0 && !m_elementCombo.m_exit && m_elementCombo.m_id == id) {
        gf::GfMenuObjElementEff::cancel(m_elementCombo.m_context);
        m_elementCombo.m_exit = true;
    }
}

void UIManager::SetKakuseiData(bool kakusei, bool other, float rate) {
    m_kakusei = kakusei;
    m_kakuseiRate = rate;
    m_kakuseiOther = other;
}

void UIManager::RegisterRescueUI(gf::GF_OBJ_HANDLE* obj) {
    m_rescueObj = obj;
}

void UIManager::DispChainUI(gf::GF_OBJ_HANDLE* obj) {
    gf::GfMenuObjChainIcon::OpenParam param;
    param.m_obj = obj;
    gf::GfMenuObjChainIcon::open(param);
}

void UIManager::DispBuffUI(const mm::Vec3& pos, int type, bool flag) {
    unsigned char* fp = gf::GfDataBdat::getFP(0x11);
    unsigned char name = Bdat::getValCheckU8(fp, "Name", type);
    if (name != 0) {
        gf::GfMenuObjDamageBuff::OpenParam param;
        param.m_type = Bdat::getFlagVal(fp, "Flag", type, "Buff") == 0;
        param.m_resist = flag;
        param.m_icon = Bdat::getValCheckU16(fp, "Icon", type);
        param.m_bdat = gf::GfDataBdat::getFP(0x196);
        param.m_nameId = name;
        param.m_pos = pos;
        gf::GfMenuObjDamageBuff::open(param);
    }
}

void UIManager::DispSystemMessageUI(const BattleCharacter* chara, int type, bool flag) {
    gf::GfMenuObjDamageBuff::OpenParam param;
    param.m_type = !flag;
    param.m_bdat = gf::GfDataBdat::getFP(0x196);
    param.m_nameId = BtlSystemBalanceAccess::sys()->pad_D6[type];
    param.m_pos = chara->m_pos;
    param.m_pos.y += chara->GetCharacterParameterConst(true)->pad_38;
    gf::GfMenuObjDamageBuff::open(param);
}

void UIManager::DispElementalEffectUI(gf::GF_OBJ_HANDLE* obj, int type) {
    const BattleCharacter* chara = CharacterManager::sys()->GetCharacterConst(obj);
    if (chara == nullptr) {
        return;
    }
    const CharacterParameter* cp = chara->GetCharacterParameterConst(true);
    if (cp == nullptr) {
        return;
    }
    unsigned char caption = Bdat::getValCheckU8(gf::GfDataBdat::getFP(0x24), "Caption", type);
    if (caption != 0) {
        gf::GfMenuObjDamageBuff::OpenParam param;
        param.m_type = !chara->m_isPlayer;
        param.m_bdat = gf::GfDataBdat::getFP(0x196);
        param.m_nameId = caption;
        param.m_pos = chara->m_pos;
        param.m_pos.y += cp->pad_38;
        gf::GfMenuObjDamageBuff::open(param);
    }
}

void UIManager::DispUniteComboUI(const mm::Vec3& pos, int param0, int param1) {
    gf::GfMenuObjDamageBuff::OpenUniteParam param;
    param.m_pos = pos;
    param.m_eventParam0 = param0;
    param.m_eventParam1 = param1;
    gf::GfMenuObjDamageBuff::openUniteCombo(param);
}

void UIManager::DispUniteComboUI(int param0, int param1, unsigned short value0, unsigned short value1,
                                 unsigned short value2, unsigned char sub0, unsigned char sub1, unsigned char sub2) {
    gf::GfMenuObjBattleTelop::OpenUniteParam param;
    param.m_param0 = param0;
    param.m_param1 = param1;
    if (value0 != 0) {
        gf::GfMenuObjBattleTelop::UniteCombo combo;
        combo.m_type = 0;
        combo.m_sub = sub0;
        combo.m_value = value0;
        param.m_combos.push_back(combo);
    }
    if (value1 != 0) {
        gf::GfMenuObjBattleTelop::UniteCombo combo;
        combo.m_type = 1;
        combo.m_sub = sub1;
        combo.m_value = value1;
        param.m_combos.push_back(combo);
    }
    if (value2 != 0) {
        gf::GfMenuObjBattleTelop::UniteCombo combo;
        combo.m_type = 2;
        combo.m_sub = sub2;
        combo.m_value = value2;
        param.m_combos.push_back(combo);
    }
    gf::GfMenuObjBattleTelop::openUniteCombo(param);
}

void UIManager::NotifyInput(INPUT_TYPE type, int arg) {
    switch (type) {
    case 0:
        gf::GfMenuObjArtsPalette::push(arg);
        break;
    case 1:
        gf::GfMenuObjBladeChange::pushBladeChange(arg);
        break;
    case 2:
        gf::GfMenuObjSpecialGauge::push();
        break;
    case 3:
        pad_bit11 = true;
        break;
    case 4:
        pad_bit12 = true;
        break;
    case 5:
        pad_bit13 = true;
        break;
    case 6:
        pad_bit14 = true;
        break;
    case 7:
        gf::GfMenuObjBladeChange::pushBladeChange(0);
        break;
    case 8:
        gf::GfMenuObjBladeChange::pushBladeChange(3);
        break;
    case 9:
        gf::GfMenuObjBladeChange::pushBladeChange(1);
        break;
    }
}

}  // namespace btl
