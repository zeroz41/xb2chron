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
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfReqParam.h"
#include "gf/SDataOption.h"
#include "mm/Math.h"
#include "ml/WorkRootMem.h"
#include "mtl/MemManager.h"
#include <new>
#include "classes/gf/GfSequentialPlay.h"
#include "classes/gf/GfReqManager.h"
#include "classes/gf/GfMapManager.h"

namespace tl {

TitleMain::TitleMain()
    : m_fsm(fw::FrameworkMemory::getAllocator(5)), m_updater(nullptr), m_reqDestroy(false), m_reqReturnTitle(false),
      m_titleBgm(0), m_isTitleBgm(false), m_returnSlot(static_cast<gf::SAVESLOT>(-1)), m_saveBuffer(nullptr),
      m_optionBuffer(nullptr), m_playTitleEvent(0),
      m_seCategory(reinterpret_cast<gf::GF_SE_CATEGORY_HANDLE*>(-1)),
      m_seCategorySub(reinterpret_cast<gf::GF_SE_CATEGORY_HANDLE*>(-1)), m_isClear(false), m_newGameAdv(false),
      m_reqChangeGameType(false), m_flag21B(false) {}

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

void TitleMain::update(const fw::UpdateInfo& info) {
    TitleMain* title = sys();
    if (title == nullptr) {
        return;
    }
    if (title->m_isTitleBgm) {
        gf::GfSound* sound = gf::GfSound::sys();
        if (sound != nullptr && !sound->isPlaying(title->m_titleBgm)) {
            if (gf::GfManager::fn_710032A1DC()) {
                title->m_titleBgm = sound->playBgm("stream/bgm/m204.wav", 1.0f, false, -1, static_cast<fw::SoundCategory>(3));
            } else {
                title->m_titleBgm = sound->playBgm("stream/bgm/m02.wav", 1.0f, false, -1, static_cast<fw::SoundCategory>(3));
            }
        }
    }
    title->m_updater->update();
}

void TitleMain::returnTitle(gf::SAVESLOT slot) {
    TitleMain* title = sys();
    if (title == nullptr) {
        return;
    }
    title->m_returnSlot = slot;
    switch (title->m_fsm.m_pState->m_stateID) {
    case 2:
    case 6:
    case 7:
        title->m_reqReturnTitle = true;
        break;
    }
    title->fn_710014F5FC(0.0f, gf::GfManager::isExecModeThater() ? 0.0f : 2.0f);
    title->fn_710014F70C(0.0f);
}

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

void TitleMain::createSaveBuffer() {
    if (gf::SDataSave* save = m_saveBuffer) {
        save->m_system.m_version = 0x3A15B;
        save->m_system.m_systemValue = 0;
        new (&save->m_game) gf::SDataGame();
    } else {
        m_saveBuffer = new (ml::WorkRootMem::getMemTMP(), nullptr, 0, 4, false) gf::SDataSave();
    }
    if (m_optionBuffer == nullptr) {
        m_optionBuffer = new (ml::WorkRootMem::getMemTMP(), nullptr, 0, 4, false) gf::SDataOption();
    } else {
        m_optionBuffer->clear();
    }
    gf::GfMenuManager::initOptionData(*m_optionBuffer);
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

gf::SDataOption& TitleMain::getOptionBuffer() {
    return *m_optionBuffer;
}

void TitleMain::setupTitleOptionToGameOption() {
    if (m_optionBuffer != nullptr) {
        gf::GfManager::setupOptionData(*m_optionBuffer);
    }
}

// the chapter of the saved scenario (scenario flag 1 / 1000, 1 to 10); 0 without a valid save or scenario
unsigned int TitleMain::getChapterIdFromSaveData() {
    gf::SDataSave* save = m_saveBuffer;
    if (save->m_system.m_version != 0x3A15B) {
        return 0;
    }
    unsigned short scenario = save->m_game.m_gameFlag.m_flag16[1];
    if (scenario == 0) {
        return 0;
    }
    return mm::clamp<unsigned int>(scenario / 1000, 1, 10);
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

void TitleMain::fn_710014FBAC() {
    m_newGameAdv = false;
    if (m_saveBuffer->m_system.m_version != 0x3A15B) {
        return;
    }
    if (gf::GfDataBlade::fn_710023217C(m_saveBuffer->m_game)) {
        if (m_saveBuffer->m_game.m_gameClearCount == 0) {
            m_saveBuffer->m_game.m_gameClearCount = 1;
        }
        if (gf::GfDataBlade::fn_7100231EB8(m_saveBuffer->m_game) >= 10032) {
            m_newGameAdv = true;
        }
    }
    if (m_saveBuffer->m_game.m_gameClearCount != 0) {
        m_isClear = true;
    }
    if (gf::GfDataBlade::fn_7100232244(m_saveBuffer->m_game)) {
        m_newGameAdv = false;
    }
}

bool TitleMain::fn_710014FC5C() {
    if (m_saveBuffer->m_system.m_version == 0x3A15B && gf::GfDataBlade::fn_710023217C(m_saveBuffer->m_game)) {
        return m_newGameAdv;
    }
    return false;
}

unsigned short TitleMain::fn_710014FCB0(unsigned int event) {
    if (m_saveBuffer != nullptr) {
        for (gf::SDataGameSavedEvent& row : m_saveBuffer->m_game.m_savedEvents) {
            if (row.m_event == event) {
                return row.m_weather;
            }
        }
    }
    return 0;
}

unsigned int TitleMain::fn_710014FD10(unsigned int event) {
    if (m_saveBuffer != nullptr) {
        for (gf::SDataGameSavedEvent& row : m_saveBuffer->m_game.m_savedEvents) {
            if (row.m_event == event) {
                return row.m_time.hour;
            }
        }
    }
    return 12;
}

bool TitleMain::fn_710014FD74() {
    gf::SDataSave* save = m_saveBuffer;
    if (save->m_system.m_version != 0x3A15B) {
        return true;
    }
    return !gf::GfDataBlade::fn_71002325AC(save->m_game);
}

void TitleMain::fn_710014FDB8(bool flag) {
    gf::GfManager::fn_710032A1FC(flag);
    m_isClear = false;
    m_newGameAdv = false;
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
