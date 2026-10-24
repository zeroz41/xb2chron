#include "gf/SDataGame.h"
#include "classes/tl/TitleMain.h"
#include "gf/SDataSave.h"
// the title screen: TitleMain and its states (the states' slots are inline: their tables are emitted with the
// registrations in TitleMain::initialize, or with the state's own out-of-line virtual)

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

namespace tl {

TitleMain* TitleMain::create() {
#line 107
    TitleMain* title = new (fw::FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) TitleMain();
    title->initialize();
    return title;
}

void TitleMain::initialize() {
    createSaveBuffer();
    m_fsm.beginSetup(this, 12);
    m_fsm.registerState<TitleStateLoad>(0);
    m_fsm.registerState<TitleStateSaveData>(1);
    m_fsm.registerState<TitleStateMainScreen>(2);
    m_fsm.registerState<TitleStatePlayGame>(6);
    m_fsm.registerState<TitleStatePlayEvent>(7);
    m_fsm.registerState<TitleStateToTitle>(8);
    m_fsm.registerState<TitleStateSelectEvent>(4);
    m_fsm.registerState<TitleStateSelectOption>(5);
    m_fsm.registerState<TitleStateDestroy>(9);
    m_fsm.registerState<TitleStateChangeGameType>(10);
    m_fsm.registerState<TitleStateWarning>(11);
    m_fsm.endSetup();
    m_fsm.setState(0);
#line 142
    m_updater = new (fw::FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) MicroUpdater<TitleMain>();
    m_updater->start(this, &fnUpdate);
}

void TitleMain::fnUpdate(TitleMain* self) {
    self->m_fsm.update(&self->m_updateInfo);
    while (self->m_fsm.m_pState->m_stateID != 9) {
        ml::MicroThread::sys()->sleep(1, true);
        self->m_fsm.update(&self->m_updateInfo);
    }
}

TitleMain::~TitleMain() {}

void TitleMain::fn_710014F5FC(float volume, float time) {
    gf::GfSound* sound = gf::GfSound::sys();
    if (sound == nullptr) {
        return;
    }
    if (m_seCategory == reinterpret_cast<gf::GF_SE_CATEGORY_HANDLE*>(-1)) {
        m_seCategory = sound->createCategoryHandle();
        if (m_seCategory == reinterpret_cast<gf::GF_SE_CATEGORY_HANDLE*>(-1)) {
            return;
        }
    }
    sound->setCategoryVolume(m_seCategory, static_cast<fw::SoundCategory>(1), volume, time);
    sound->setCategoryVolume(m_seCategory, static_cast<fw::SoundCategory>(0xD), volume, time);
    sound->setCategoryVolume(m_seCategory, static_cast<fw::SoundCategory>(0xE), volume, time);
    sound->setCategoryVolume(m_seCategory, static_cast<fw::SoundCategory>(5), volume, time);
    sound->setCategoryVolume(m_seCategory, static_cast<fw::SoundCategory>(7), volume, time);
    sound->setCategoryVolume(m_seCategory, static_cast<fw::SoundCategory>(6), volume, time);
    sound->setCategoryVolume(m_seCategory, static_cast<fw::SoundCategory>(8), volume, time);
}

void TitleMain::fn_710014F70C(float volume) {
    gf::GfSound* sound = gf::GfSound::sys();
    if (sound == nullptr) {
        return;
    }
    if (m_seCategorySub == reinterpret_cast<gf::GF_SE_CATEGORY_HANDLE*>(-1)) {
        m_seCategorySub = sound->createCategoryHandle();
        if (m_seCategorySub == reinterpret_cast<gf::GF_SE_CATEGORY_HANDLE*>(-1)) {
            return;
        }
    }
    sound->setCategoryVolume(m_seCategorySub, static_cast<fw::SoundCategory>(0xD), volume, 0.0f);
    sound->setCategoryVolume(m_seCategorySub, static_cast<fw::SoundCategory>(0xE), volume, 0.0f);
    sound->setCategoryVolume(m_seCategorySub, static_cast<fw::SoundCategory>(0), volume, 0.0f);
    sound->setCategoryVolume(m_seCategorySub, static_cast<fw::SoundCategory>(0), volume, 0.0f);
    sound->setCategoryVolume(m_seCategorySub, static_cast<fw::SoundCategory>(0), volume, 0.0f);
    sound->setCategoryVolume(m_seCategorySub, static_cast<fw::SoundCategory>(0), volume, 0.0f);
    sound->setCategoryVolume(m_seCategorySub, static_cast<fw::SoundCategory>(0), volume, 0.0f);
    sound->setCategoryVolume(m_seCategorySub, static_cast<fw::SoundCategory>(0), volume, 0.0f);
}

void TitleMain::destroy() {
    TitleMain* title = sys();
    title->finalize();
    delete title;
}

void TitleMain::stopTitleBGM(float time) {
    if (m_titleBgm.isValid()) {
        gf::GfSound* sound = gf::GfSound::sys();
        if (sound != nullptr) {
            sound->stopBgm(m_titleBgm, time);
        }
        m_titleBgm.clear();
    }
    m_isTitleBgm = false;
}

// starts nothing in 3.0.1: with no title BGM it stops it (an inline stopTitleBGM(2.0f)) and marks the title BGM set
void TitleMain::playTitleBGM() {
    if (!m_titleBgm.isValid()) {
        stopTitleBGM(2.0f);
        m_isTitleBgm = true;
    }
}

bool TitleMain::isReturnTitle() {
    TitleMain* title = sys();
    if (title == nullptr) {
        return false;
    }
    return title->m_fsm.m_pState->m_stateID == 8;
}

bool TitleMain::isStateReturnTitle() const {
    TitleMain* title = sys();
    if (title == nullptr) {
        return false;
    }
    return title->m_fsm.m_pState->m_stateID == 8;
}

gf::SDataSave* TitleMain::fn_710014FB00() {
    return m_saveBuffer;
}

gf::SDataSave* TitleMain::getSaveBuffer() {
    return m_saveBuffer;
}

gf::SDataOption* TitleMain::getOptionBuffer() {
    return m_optionBuffer;
}

void TitleMain::setupTitleOptionToGameOption() {
    if (m_optionBuffer != nullptr) {
        gf::GfManager::setupOptionData(*m_optionBuffer);
    }
}

void TitleMain::playTitleEvent(unsigned int eventID) {
    m_playTitleEvent = eventID;
    if (eventID != 0) {
        gf::GfPlayFactory::createOneEvent(eventID);
    }
}

unsigned int TitleMain::getPlayTitleEvent() {
    return m_playTitleEvent;
}

void TitleStateMainScreen::gevPlayEvent(gf::GEV gev, unsigned int arg) {
    if (gev == static_cast<gf::GEV>(0xE)) {
        m_playEvent = 1;
    }
}

void TitleStatePlayGame::gevPlayEvent(gf::GEV gev, unsigned int arg) {
    if (gev == static_cast<gf::GEV>(0xE)) {
        m_playEvent = 2;
    } else if (gev == static_cast<gf::GEV>(0xD)) {
        m_playEvent = 0;
    }
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
        TitleMain::sys()->fn_710014F5FC(1.0f, 0.0f);
        TitleMain::sys()->fn_710014F70C(1.0f);
        gf::GfGameManager::fn_71002AB894(gf::GfInfo::m_camPos);
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
        gf::GfGameManager::fn_71002AB894(mm::Vec3::zero);
    }
}

inline const char* TitleStateLoad::getName() const {
    return "TitleStateLoad";
}
inline void TitleStateLoad::onEnter(void* owner, ai::State* prev) {}
inline void TitleStateLoad::onLeave(void* owner, ai::State* next) {}
inline void TitleStateLoad::onStep(void* owner, const void* arg) {
    update(static_cast<TitleMain*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* TitleStateSaveData::getName() const {
    return "TitleStateSaveData";
}
inline void TitleStateSaveData::onEnter(void* owner, ai::State* prev) {}
inline void TitleStateSaveData::onLeave(void* owner, ai::State* next) {}
inline void TitleStateSaveData::onStep(void* owner, const void* arg) {
    fn_710015359C(static_cast<TitleMain*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* TitleStateMainScreen::getName() const {
    return "TitleStateMainScreen";
}
inline void TitleStateMainScreen::onEnter(void* owner, ai::State* prev) {
    gf::GfEvent::addEventCallback(this);
        static_cast<TitleMain*>(owner)->fn_710014F70C(0.0f);
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
        gf::GfMenuObjEvTheater::fn_71003FEE10(false);
        gf::GfMenuManager::closeBtlModelView();
    }
    gf::GfEvent::removeEventCallback(this);
}
inline void TitleStatePlayEvent::onStep(void* owner, const void* arg) {
    update(static_cast<TitleMain*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* TitleStateToTitle::getName() const {
    return "TitleStateToTitle";
}
inline void TitleStateToTitle::onEnter(void* owner, ai::State* prev) {}
inline void TitleStateToTitle::onLeave(void* owner, ai::State* next) {}
inline void TitleStateToTitle::onStep(void* owner, const void* arg) {
    update(static_cast<TitleMain*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* TitleStateSelectEvent::getName() const {
    return "TitleStateSelectEvent";
}
inline void TitleStateSelectEvent::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<TitleMain*>(owner), prev);
}
inline void TitleStateSelectEvent::onLeave(void* owner, ai::State* next) {}
inline void TitleStateSelectEvent::onStep(void* owner, const void* arg) {
    update(static_cast<TitleMain*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* TitleStateSelectOption::getName() const {
    return "TitleStateSelectOption";
}
inline void TitleStateSelectOption::onEnter(void* owner, ai::State* prev) {
    enter(static_cast<TitleMain*>(owner), prev);
}
inline void TitleStateSelectOption::onLeave(void* owner, ai::State* next) {}
inline void TitleStateSelectOption::onStep(void* owner, const void* arg) {
    update(static_cast<TitleMain*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* TitleStateDestroy::getName() const {
    return "TitleStateDestroy";
}
inline void TitleStateDestroy::onEnter(void* owner, ai::State* prev) {}
inline void TitleStateDestroy::onLeave(void* owner, ai::State* next) {}
inline void TitleStateDestroy::onStep(void* owner, const void* arg) {}

inline const char* TitleStateChangeGameType::getName() const {
    return "TitleStateChangeGameType";
}
inline void TitleStateChangeGameType::onEnter(void* owner, ai::State* prev) {}
inline void TitleStateChangeGameType::onLeave(void* owner, ai::State* next) {}
inline void TitleStateChangeGameType::onStep(void* owner, const void* arg) {
    fn_7100156288(static_cast<TitleMain*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

inline const char* TitleStateWarning::getName() const {
    return "TitleStateWarning";
}
inline void TitleStateWarning::onEnter(void* owner, ai::State* prev) {
    fn_71001565A0(static_cast<TitleMain*>(owner), prev);
}
inline void TitleStateWarning::onLeave(void* owner, ai::State* next) {}
inline void TitleStateWarning::onStep(void* owner, const void* arg) {
    fn_71001565A8(static_cast<TitleMain*>(owner), *static_cast<const fw::UpdateInfo*>(arg));
}

// the title screen's menus
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

bool TitleMenu::fn_7100153350() const {
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

bool TitleMenu::fn_71001533B8() const {
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

}  // namespace tl
