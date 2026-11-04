#include "classes/tl/TitleMain.h"
#include "gf/SDataSave.h"
#include "classes/tl/TitleStatePlayEvent.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/tl/TitleMain.h"
#include "classes/gf/GfSound.h"
#include "classes/ai/State.h"
#include "mm/mtl/Delegate.h"
#include "classes/ml/MicroThread.h"
#include "MicroUpdater.h"
#include "classes/tl/TitleStateLoad.h"
#include "classes/tl/TitleStateSaveData.h"
#include "classes/tl/TitleStateMainScreen.h"
#include "classes/tl/TitleStatePlayGame.h"
#include "classes/tl/TitleStatePlayEvent.h"
#include "classes/tl/TitleStateToTitle.h"
#include "classes/tl/TitleStateSelectEvent.h"
#include "classes/tl/TitleStateSelectOption.h"
#include "classes/tl/TitleStateDestroy.h"
#include "classes/tl/TitleStateChangeGameType.h"
#include "classes/tl/TitleStateWarning.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfManager.h"
#include "gf/GfPlayFactory.h"
#include "classes/tl/TitleMenu.h"
#include "classes/gf/GfMenuObjTitle.h"
#include "classes/gf/GfMenuObjOption.h"
#include "classes/gf/GfMenuObjEvTheater.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfFieldLod.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfReqParam.h"
#include "gf/SDataOption.h"
#include "mm/Math.h"
#include "ml/WorkRootMem.h"
#include "mtl/MemManager.h"
#include <new>
#include "classes/gf/GfGameLoad.h"
#include "classes/gf/GfSequentialPlay.h"
#include "classes/gf/GfReqManager.h"
#include "classes/gf/GfMapManager.h"
#include "classes/gf/GfDataManager.h"
#include "gf/GfGameUtilSaveData.h"

// the title screen's menus and the first states' updates (TitleMain's helpers are out of line here)
namespace tl {

void TitleMenu::destroyMenuCallContext() {
    if (m_context != nullptr) {
        while (!m_context->isTerm()) {
            gf::GfSleep(1);
        }
        if (m_context != nullptr) {
            m_context->release();
            m_context = nullptr;
        }
    }
}

void TitleMenu::openTitle(bool flag) {
    gf::GfMenuManager::openFullScreen(3, flag, true);
}

bool TitleMenu::isOpenTitle() const {
    return !gf::GfMenuManager::isSwitchingFullScreen();
}

void TitleMenu::setupTitle() {
    if (m_context == nullptr) {
        m_context = gf::GfMenuCallContext::create();
    }
    gf::GfMenuObjTitle::attach(m_context);
}

bool TitleMenu::hasResultSelect() const {
    if (m_context == nullptr) {
        return false;
    }
    return !m_context->m_results.empty();
}

int TitleMenu::getResult() const {
    gf::GfMenuCallContext::GfMenuResult result;
    m_context->popResult(result);
    if (result.m_value != 0) {
        return 0;
    }
    switch (result.m_id) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 3;
    case 3: return 4;
    case 4: return 5;
    default: return 0;
    }
}

void TitleMenu::closeTitle(bool flag0, bool flag1) {
    gf::GfMenuManager::closeFullScreen(flag0, flag1);
    destroyMenuCallContext();
}

bool TitleMenu::isCloseTitle() const {
    return !gf::GfMenuManager::isOpenFullScreen();
}

void TitleMenu::openEventTheater() {
    if (m_context == nullptr) {
        m_context = gf::GfMenuCallContext::create();
    }
    if (m_context->isActive()) {
        if (m_context == nullptr) {
            m_context = gf::GfMenuCallContext::create();
        }
        gf::GfMenuObjEvTheater::fadein(m_context);
    } else {
        gf::GfMenuManager::openFullScreen(6, true, true);
    }
}

bool TitleMenu::isOpenEventTheater() const {
    return !gf::GfMenuManager::isSwitchingFullScreen();
}

void TitleMenu::setupEventTheater() {
    if (m_context == nullptr) {
        m_context = gf::GfMenuCallContext::create();
    }
    gf::GfMenuObjEvTheater::attach(m_context);
}

bool TitleMenu::hasResultEventTheater() const {
    if (m_context == nullptr) {
        return false;
    }
    return !m_context->m_results.empty();
}

bool TitleMenu::isExitEventTheater() const {
    if (m_context == nullptr) {
        return false;
    }
    return m_context->isTerm();
}

void TitleMenu::openOption() {
    gf::GfMenuManager::openFullScreen(7, false, true);
}

bool TitleMenu::isOpenOption() const {
    return !gf::GfMenuManager::isSwitchingFullScreen();
}

void TitleMenu::setupOption() {
    if (m_context == nullptr) {
        m_context = gf::GfMenuCallContext::create();
    }
    gf::GfMenuObjOption::attach(m_context);
}

bool TitleMenu::isExitOption() const {
    if (m_context == nullptr) {
        return false;
    }
    return m_context->isTerm();
}

void TitleMenu::exitOption() {
    destroyMenuCallContext();
}

int TitleMenu::getPlayEventID() const {
    gf::GfMenuCallContext::GfMenuResult result;
    m_context->popResult(result);
    return result.m_value == 0 ? result.m_id : 0;
}

void TitleMenu::exitEventTheater() {
    destroyMenuCallContext();
}

void TitleMenu::fadeoutEventTheater() {
    if (m_context == nullptr) {
        m_context = gf::GfMenuCallContext::create();
    }
    gf::GfMenuObjEvTheater::fadeout(m_context);
}

void TitleStateLoad::update(TitleMain* title, const fw::UpdateInfo& info) {
    m_timeCount.reset();
    title->m_menu.m_request = 0;
    requestState(1);
    title->m_returnSlot = static_cast<gf::SAVESLOT>(-1);
}

void TitleStateSaveData::update(TitleMain* title, const fw::UpdateInfo& info) {
    if (gf::GfGameManager::isGameTypeIra()) {
        gf::GfGameLoad load(static_cast<gf::SAVESLOT>(0x16));
        title->getSaveBuffer()->fn_7100153694();
        load.execGameLoadWithMicroThread(*title->getSaveBuffer());
        if (title->getSaveBuffer()->m_system.m_version != 0x3A15B) {
            requestState(11);
            return;
        }
    }
    title->m_menu.m_request = 0;
    requestState(2);
    title->m_returnSlot = static_cast<gf::SAVESLOT>(-1);
}

}  // namespace tl
