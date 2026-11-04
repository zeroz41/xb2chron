#include "classes/btl/UIManager.h"
#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/gf/GfMenuObjDamageBuff.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/btl/UIManager.h"
#include "classes/btl/BattleGlobal.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameFlag.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjActionWindow.h"
#include "classes/gf/GfMenuObjArtsPalette.h"
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

void UIManager::DispUniteComboUI(const mm::Vec3& pos, int param0, int param1) {
    gf::GfMenuObjDamageBuff::OpenUniteParam param;
    param.m_pos = pos;
    param.m_eventParam0 = param0;
    param.m_eventParam1 = param1;
    gf::GfMenuObjDamageBuff::openUniteCombo(param);
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
