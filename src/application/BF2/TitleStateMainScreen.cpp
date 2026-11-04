#include "classes/tl/TitleMain.h"
#include "gf/SDataSaveIra.h"
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
#include "classes/gf/SCOM_FADE.h"
#include "classes/gf/GfGameEvent.h"
#include "classes/fw/Framework.h"
#include "classes/ml/Scn.h"
#include "fw/RenderParam.h"
#include "ml/MTRand.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "mm/Col4.h"
#include "gf/GfGameUtilSaveData.h"
#include "gf/GfDataUtil.h"
#include "gf/GfGameUtil.h"

// the title states with their own tables (MainScreen, PlayGame, PlayEvent) and the other states' updates
namespace tl {

void TitleStateMainScreen::gevPlayEvent(gf::GEV gev, unsigned int arg) {
    if (gev == static_cast<gf::GEV>(0xE)) {
        m_playEvent = 1;
    }
}

namespace {
// the title events playTitleEvent picks one of at random (lbl_71009B9508) and by the save data's chapter
// (lbl_71009B950E); the names are not the original's
const unsigned short s_randomTitleEvents[3] = {0x296F, 0x2970, 0x2971};
const unsigned short s_chapterTitleEvents[11] = {0x2711, 0x2908, 0x2909, 0x290A, 0x290B, 0x290C,
                                                 0x290D, 0x290E, 0x290F, 0x2910, 0x2911};
}  // namespace

void TitleStateMainScreen::playTitleEvent(TitleMain* title) {
    m_playEvent = 0;
    gf::SCOM_FADE::create(0, 0, mm::Col4::black);
    gf::SCOM_FADE::create(1, 0, mm::Col4::black);
    gf::SCOM_FADE::create(2, 0, mm::Col4::black);
    unsigned short event;
    if (gf::GfManager::isGameTypeIra()) {
        event = title->TitleMain::isTitleEventClearGame() ? 0x29D6 : 0x29D5;
    } else if (gf::GfDataUtil::isClearTwiceGame(title->getSaveBuffer()->m_game)) {
        unsigned int index = ml::mtRand(3);
        event = s_randomTitleEvents[index > 2 ? 2 : index];
    } else if (title->TitleMain::isTitleEventClearGame()) {
        event = gf::GfDataBlade::isHomuriNameHikari(title->getSaveBuffer()->m_game) ? 0x296E : 0x296D;
    } else {
        unsigned int chapter = title->getChapterIdFromSaveData();
        event = s_chapterTitleEvents[chapter > 11 ? 11 : chapter];
    }
    title->playTitleEvent(event);
    while (m_playEvent != 1) {
        TitleMain::sleep(1);
    }
    fw::RenderParam::resetScene();
    ml::ScnRenderDrSysParmAcc acc(fw::Framework::sys()->m_scn->m_renderDrSys, 0);
    acc.weatherFrmEnd();
    gf::SCOM_FADE::create(0, 15, mm::Col4::zero);
    gf::SCOM_FADE::create(1, 15, mm::Col4::zero);
    gf::SCOM_FADE::create(2, 15, mm::Col4::zero);
}

bool TitleStateMainScreen::dispTitleMenu(TitleMain* title, bool flag) {
    TitleMenu& menu = title->m_menu;
    title->playTitleBGM();
    menu.openTitle(flag);
    while (!menu.isOpenTitle()) {
        if (title->m_reqDestroy) {
            requestState(9);
            return true;
        }
        TitleMain::sleep(1);
    }
    menu.setupTitle();
    return false;
}

bool TitleStateMainScreen::checkMenuResult(TitleMain* title) {
    TitleMenu& menu = title->m_menu;
    while (true) {
        if (menu.hasResultSelect()) {
            menu.m_request = menu.getResult();
            return false;
        }
        if (title->m_reqReturnTitle) {
            menu.closeTitle(true, true);
            title->m_reqReturnTitle = false;
            requestState(8);
            return true;
        }
        if (title->m_reqDestroy) {
            menu.closeTitle(true, true);
            requestState(9);
            return true;
        }
        bool change = title->m_reqChangeGameType;
        title->m_reqChangeGameType = false;
        if (change) {
            menu.m_request = 6;
            return false;
        }
        TitleMain::sleep(1);
    }
}

void TitleStateMainScreen::update(TitleMain* title, const fw::UpdateInfo& info) {
    int request = title->m_menu.m_request;
    title->m_menu.m_request = 0;
    title->m_reqReturnTitle = false;
    if (title->m_eventRequest.m_event != 0) {
        requestState(4);
        return;
    }
    loadSaveDataForTitle(title);
    bool flag = request != 3;
    if (flag) {
        playTitleEvent(title);
    }
    if (dispTitleMenu(title, flag)) {
        return;
    }
    if (checkMenuResult(title)) {
        return;
    }
    waitTitleMenuDestroy(title);
}

void TitleStatePlayGame::gevPlayEvent(gf::GEV gev, unsigned int arg) {
    if (gev == static_cast<gf::GEV>(0xE)) {
        m_playEvent = 2;
    } else if (gev == static_cast<gf::GEV>(0xD)) {
        m_playEvent = 0;
    }
}

void TitleStateToTitle::update(TitleMain* title, const fw::UpdateInfo& info) {
    gf::GfManager::execToAdvertize();
    title->m_menu.m_request = 0;
    while (gf::GfSequentialPlay::isPlay()) {
        TitleMain::sleep(1);
    }
    while (gf::GfReqManager::isExistCommand(nullptr)) {
        TitleMain::sleep(1);
    }
    while (!gf::GfMapManager::isMapReady()) {
        TitleMain::sleep(1);
    }
    gf::GfManager::setupReturnTitle();
    if (title->m_reqDestroy) {
        requestState(9);
    } else {
        requestState(2);
    }
}

void fn_7100154638() {
    gf::SDataOption* option = gf::GfDataManager::getDataOption();
    gf::SDataOption* titleOption = &TitleMain::sys()->getOptionBuffer();
    if (!gf::GfGameManager::isGameTypeIra() && !gf::GfGameUtil::isAdvancedGameOption()) {
        option->m_soundUi.m_flagA = 0;
        option->m_soundUi.m_flagB = 0;
        option->m_soundUi.m_flagC = 0;
        titleOption->m_soundUi.m_flagA = 0;
        titleOption->m_soundUi.m_flagB = 0;
        titleOption->m_soundUi.m_flagC = 0;
    }
    bool clear = gf::GfGameManager::isGameTypeIra() ? gf::GfGameManager::isClearGame()
                                                     : gf::GfGameUtil::isAdvancedDifficulity();
    if (!clear) {
        if (option->m_soundUi.m_keyD > 1) {
            option->m_soundUi.m_keyD = 0;
        }
        if (titleOption->m_soundUi.m_keyD > 1) {
            titleOption->m_soundUi.m_keyD = 0;
        }
    }
}

bool TitleStateSelectEvent::eventMenuResult(TitleMain* title) {
    TitleMenu& menu = title->m_menu;
    while (true) {
        if (menu.hasResultEventTheater()) {
            int event = menu.getPlayEventID();
            if (event == 0) {
                return true;
            }
            TitleMain::EventRequest request = title->m_eventTemplate;
            request.m_event = event;
            title->m_eventRequest = request;
            return false;
        }
        if (menu.isExitEventTheater()) {
            menu.exitEventTheater();
            title->m_reqReturnTitle = false;
            title->m_eventRequest = TitleMain::EventRequest();
            gf::GfManager::setExec(static_cast<gf::EXEC_STATE>(2));
            requestState(2);
            return true;
        }
        TitleMain::sleep(1);
    }
}

void TitleStateSelectEvent::enter(TitleMain* title, ai::State* prev) {
    gf::GfGameEvent::stop();
    while (gf::GfGameEvent::isPlaying()) {
        TitleMain::sleep(1);
    }
    if (gf::GfGameManager::getMapJumpID() != static_cast<unsigned int>(-1)) {
        gf::GfMapjumpInfo info(static_cast<unsigned int>(-1));
        gf::GfPlayFactory::createMapjump(info);
        TitleMain::sleep(30);
        while (gf::GfGameManager::isMapjump()) {
            TitleMain::sleep(1);
        }
    }
    gf::GfManager::setExec(static_cast<gf::EXEC_STATE>(3));
    gf::SCOM_FADE::create(0, 0, mm::Col4::black);
    gf::SCOM_FADE::create(1, 15, mm::Col4::zero);
    gf::SCOM_FADE::create(2, 15, mm::Col4::zero);
}

void TitleStateSelectEvent::update(TitleMain* title, const fw::UpdateInfo& info) {
    title->m_menu.openEventTheater();
    while (!title->m_menu.isOpenEventTheater()) {
        if (title->m_reqDestroy) {
            requestState(9);
            return;
        }
        TitleMain::sleep(1);
    }
    title->m_menu.setupEventTheater();
    if (eventMenuResult(title)) {
        return;
    }
    title->m_menu.fadeoutEventTheater();
    requestState(7);
}

void TitleStateSelectOption::enter(TitleMain* title, ai::State* prev) {}

void TitleStateSelectOption::update(TitleMain* title, const fw::UpdateInfo& info) {
    title->m_menu.openOption();
    while (!title->m_menu.isOpenOption()) {
        if (title->m_reqDestroy) {
            requestState(9);
            return;
        }
        TitleMain::sleep(1);
    }
    title->m_menu.setupOption();
    while (!title->m_menu.isExitOption()) {
        TitleMain::sleep(1);
    }
    title->m_menu.exitOption();
    while (!title->m_menu.isCloseTitle()) {
        TitleMain::sleep(1);
    }
    title->m_reqReturnTitle = false;
    requestState(2);
}

namespace {
// reverses the animation of the field LOD object the id names, when it has one (the name is not the original's)
inline void setLodAnimReverse(unsigned short lodId) {
    gf::GfFieldLod* lod = gf::GfFieldLod::sys();
    if (lod != nullptr) {
        int bdatId = lod->findBdatIdByLodId(lodId);
        if (bdatId != 0) {
            lod->setAnimReverse(bdatId, false, true);
        }
    }
}
}  // namespace

void TitleStatePlayEvent::gevPlayEvent(gf::GEV gev, unsigned int arg) {
    if (gev == static_cast<gf::GEV>(0xE)) {
        TitleMain::sys()->setMaskVolumeFade(1.0f, 0.0f);
        TitleMain::sys()->setMaskVolumeGameSe(1.0f);
        gf::GfGameManager::setControlMoverPositionForNoPlayer(gf::GfInfo::m_camPos);
        if (arg == 0x272A) {
            setLodAnimReverse(0x193);
            setLodAnimReverse(0x19A);
            setLodAnimReverse(0x199);
            setLodAnimReverse(0x19B);
        }
    } else if (gev == static_cast<gf::GEV>(0xD)) {
        if (arg != 0) {
            m_endArg = true;
        }
        gf::GfGameManager::setControlMoverPositionForNoPlayer(mm::Vec3::zero);
    }
}

void TitleStateWarning::enter(TitleMain* title, ai::State* prev) {
    gf::GfMenuManager::startBtlchTutorial(10);
}

void TitleStateWarning::update(TitleMain* title, const fw::UpdateInfo& info) {
    if (gf::GfMenuManager::isOpenBtlchTutorial()) {
        return;
    }
    title->m_menu.m_request = 0;
    requestState(2);
    title->m_returnSlot = static_cast<gf::SAVESLOT>(-1);
}

inline const char* TitleStateMainScreen::getName() const {
    return "TitleStateMainScreen";
}
inline void TitleStateMainScreen::onEnter(void* owner, ai::State* prev) {
    gf::GfEvent::addEventCallback(this);
        static_cast<TitleMain*>(owner)->setMaskVolumeGameSe(0.0f);
}
inline void TitleStateMainScreen::onLeave(void* owner, ai::State* next) {
    gf::GfEvent::removeEventCallback(this);
}
inline void TitleStateMainScreen::onStep(void* owner, const void* arg) {
    update(static_cast<TitleMain*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* TitleStatePlayGame::getName() const {
    return "TitleStatePlayGame";
}
inline void TitleStatePlayGame::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<TitleMain*>(owner), prev);
}
inline void TitleStatePlayGame::onLeave(void* owner, ai::State* next) {
    gf::GfEvent::removeEventCallback(this);
}
inline void TitleStatePlayGame::onStep(void* owner, const void* arg) {
    TitleMain* title = static_cast<TitleMain*>(owner);
    while (!title->m_reqReturnTitle) {
        if (title->m_reqDestroy) {
            requestState(9);
            return;
        }
        TitleMain::sleep(1);
    }
    title->m_reqReturnTitle = false;
    requestState(8);
}

inline const char* TitleStatePlayEvent::getName() const {
    return "TitleStatePlayEvent";
}
inline void TitleStatePlayEvent::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<TitleMain*>(owner), prev);
}
inline void TitleStatePlayEvent::onLeave(void* owner, ai::State* next) {
    if (m_openBtlModelView) {
        gf::GfMenuObjEvTheater::dispOffScreen(false);
        gf::GfMenuManager::closeBtlModelView();
    }
    gf::GfEvent::removeEventCallback(this);
}
inline void TitleStatePlayEvent::onStep(void* owner, const void* arg) {
    update(static_cast<TitleMain*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

void fn_710015678C(gf::RQ_SETUP_PARTY& party, unsigned int driver, unsigned int blade) {
    if (driver == 0) {
        return;
    }
    for (int i = 0; i < 10; i++) {
        if (party.m_drivers[i].m_driver == driver) {
            return;
        }
    }
    for (int i = 0; i < 10; i++) {
        gf::RQ_SETUP_PARTY::Driver& entry = party.m_drivers[i];
        if (entry.m_driver == 0) {
            entry.m_driver = driver;
            if (blade == 0) {
                blade = gf::GfDataDriver::getDefaultBlade(driver, 0);
            }
            entry.m_blades[0] = blade;
            entry.m_activeIndex = 0;
            return;
        }
    }
}

}  // namespace tl
