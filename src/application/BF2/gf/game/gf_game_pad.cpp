#include "fw/PadData.h"
#include "classes/gf/GfEvent.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/MsgObjectDead.h"
#include "classes/gf/GfGamePad.h"
#include "classes/gf/GfGamePad.h"
#include "classes/fw/PadManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfFieldManager.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfObj.h"
#include "fw/UpdateInfo.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataParty.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/GfPlayFactory.h"
#include "gf/MsgObjectDead.h"
#include "mm/Vec3.h"
#include "gf/GfDataUtil.h"

namespace gf {

GfGamePad::~GfGamePad() {}

void GfGamePad::build(const GfSetupParam& param) {
#line 72
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGamePad(param);
}

void GfGamePad::destroy() {
    GfGamePad* pad = get();
    pad->finalize();
    delete pad;
}

void GfGamePad::changePadInputMode() {
    m_padRelay.unbind();
    m_padRelay.bind(0, 4, getAllocator(ALLOCATOR(0)));
    if (GfManager::isExecModeDebug() || GfManager::isExecModeScenarioGame()) {
        if (GfGameManager::isEvent(false) || GfGameManager::isTalking()) {
            m_padRelay.bindAction("pause_event", this, &GfGamePad::eventInGameEventPause);
        } else if (GfGameManager::isEnableOpenMainMenuSequence()) {
            m_padRelay.bindAction("boot_mainmenu", this, &GfGamePad::eventInGameOpenMainMenu);
            m_padRelay.bindAction("call_system", this, &GfGamePad::eventInGameOpenSystemMenu);
            m_padRelay.bindAction("call_skiptravel", this, &GfGamePad::eventInGameOpenSkipTravelMenu);
            if (GfGameManager::isGameTypeIra()) {
                m_padRelay.bindAction("call_party", this, &GfGamePad::eventInGameParty);
            }
        }
    } else if (GfManager::isExecModeThater()) {
        if (GfGameManager::isEvent(false) || GfGameManager::isTalking()) {
            m_padRelay.bindAction("pause_event", this, &GfGamePad::eventInGameEventPause);
        }
    }
}

void GfGamePad::update(const fw::UpdateInfo& info) {
    GfGamePad* pad = get();
    pad->clearUniqParams();
    pad->changePadInputMode();
    pad->m_padRelay.update();
    fw::PadData& data = pad->m_padData;
    data = fw::PadManager::getControlPadData(0);
    pad->checkEmergencyEscape();
    if (GfGameManager::isEnableBattouWithHoodHomura(true) && (data.m_btn & 0x20) == 0 && (data.m_down & 4) != 0) {
        GfPlayFactory::createHoodHomuraBattou();
    }
}

void GfGamePad::checkEmergencyEscape() {
    if ((m_padData.m_btn & 0x40F8) != 0x40F8) {
        m_escapeCount = 0;
        return;
    }
    if (++m_escapeCount < 151) {
        return;
    }
    m_escapeCount = 0;
    bool cond;
    if (GfGameManager::isGameTypeIra()) {
        cond = GfGameCond::isGameCond(3877);
    } else {
        cond = GfGameCond::isGameCond(2654);
    }
    if (cond) {
        return;
    }
    if (GfDataUtil::getScenarioFlag() == 1031 && GfFieldManager::getLandmarkPoint() != 39) {
        GfFieldManager::setLandmarkPoint(39, mm::Vec3(-10.431001f, 0.998f, 0.000453f), 0.0f);
    }
    GfObj* obj = GfObjUtil::getObj(GfGameManager::getPartyLeader());
    MsgObjectDead msg(4);
    static_cast<fw::MessageObject*>(obj)->recieveMessage(&static_cast<fw::MessageObject&>(*obj), msg);
}

const fw::PadData& GfGamePad::getPadPlayer() {
    GfGamePad* pad = get();
    if (pad != nullptr) {
        return pad->m_padData;
    }
    return fw::PadManager::getControlPadData(0);
}

bool GfGamePad::isEventPause() {
    GfGamePad* pad = get();
    if (pad == nullptr) {
        return false;
    }
    return pad->m_eventPause;
}

void GfGamePad::eventInGameEventPause() {
    m_eventPause = true;
}

void GfGamePad::eventInGameOpenMainMenu() {
    if (GfGameManager::isEnableOpenMainMenu() && GfGameManager::isEnableOpenMainMenuSequence()) {
        GfEvent::callOpenMeinMenu();
        GfMenuObjUtil::playSE(3);
        GfPlayFactory::createOpenMenu2(1, static_cast<MAINMENU>(0), nullptr);
    } else {
        GfMenuObjUtil::playSE(7);
    }
}

void GfGamePad::eventInGameOpenSystemMenu() {
    if (GfGameManager::isEnableOpenMainMenu() && GfGameManager::isEnableOpenMainMenuSequence()) {
        GfEvent::callOpenMeinMenu();
        GfMenuObjUtil::playSE(3);
        GfPlayFactory::createOpenMenu2(1, static_cast<MAINMENU>(1), nullptr);
    } else {
        GfMenuObjUtil::playSE(7);
    }
}

void GfGamePad::eventInGameOpenSkipTravelMenu() {
    if (GfGameManager::isEnableOpenMainMenu() && GfGameManager::isEnableOpenMainMenuSequence() &&
        GfMenuManager::canPlayerControl() && GfMenuManager::isEnableMinimap() && !GfMenuObjUtil::isInChallengeBattleMap()) {
        GfEvent::callOpenMeinMenu();
        GfMenuObjUtil::playSE(3);
        GfPlayFactory::createOpenMenu2(1, static_cast<MAINMENU>(2), nullptr);
    } else {
        GfMenuObjUtil::playSE(7);
    }
}

void GfGamePad::eventInGameParty() {
    if (!GfGameManager::isEnableOpenMainMenu() || !GfGameManager::isEnableOpenMainMenuSequence() ||
        !GfMenuManager::canPlayerControl() || !GfMenuManager::isEnableMinimap()) {
        return;
    }
    GfObjAcc acc(GfGameManager::getControlMover());
    if (acc.getAlphaLife() < 1.0f) {
        return;
    }
    unsigned int count = 0;
    for (unsigned int party = 0; party < 3; ++party) {
        if (GfDataParty::getDriver(party, static_cast<PTPOS>(0)) != 0) {
            ++count;
        }
    }
    if (count >= 2) {
        GfPlayFactory::createPartySwitchForIra();
    }
}

void GfGamePad::gevExecState(gf::EXEC_STATE) {}

void GfGamePad::gevGameState(gf::GF_STATE, gf::GF_STATE) {}

}  // namespace gf
