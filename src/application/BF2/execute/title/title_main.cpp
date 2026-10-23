// the title screen: TitleMain and its states (the states' slots are inline: their tables are emitted with the
// registrations in TitleMain::initialize, or with the state's own out-of-line virtual)

#include "classes/ai/State.h"
#include "mm/mtl/Delegate.h"
#include "classes/ml/MicroThread.h"
#include "MicroUpdater.h"
#include "classes/tl/TitleMain.h"
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

}  // namespace tl
