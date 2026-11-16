#include "gf/GfSetupParam.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfDataManager.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfFieldManager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfSound.h"
#include "gf/GfStaticRes.h"
#include "ml/TimeCount.h"
#include "classes/fw/Framework.h"
#include "classes/gf/GfPause.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfMapManager.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/btl/BattleManager.h"
#include "gf/GfReqCommand.h"
#include "classes/fw/EffectManager.h"
#include "classes/fw/SoundManager.h"
#include "fw/FwDebug.h"
#include "ml/MTRand.h"
#include "gf/FileStaticVec3.h"
#include "classes/gf/GfReqManager.h"
#include "classes/gf/GfScriptManager.h"
#include "classes/gf/GfMovieManager.h"
#include "classes/fw/CommonResource.h"
#include "fw/RenderParam.h"
#include "gf/GfParamIkReflection.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfMemManager.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfDataStore.h"
#include "gf/GfGameUtil.h"
#include "gf/GfGameUtilSaveData.h"
#include "gf/GfDataEvent.h"
#include "gf/GfPlayFactory.h"
#include "gf/GfReqParam.h"
#include "gf/EvtTheaterParam.h"
#include "gf/ParamReturnTitle.h"
#include "gf/GfDataUtil.h"
#include "gf/GfDataParty.h"
#include "gf/SDataGame.h"
#include "gf/SDataDlc.h"
#include "classes/gf/GfGameEvent.h"

namespace gf {

// each execution state's ExecFlags (by EXEC_STATE; bit 1 has no reader here)
static const unsigned short s_execFlags[] = {0, 4, 9, 8, 3, 0};

GfManager* GfManager::s_pThis;

// the time since the game was set up (the name is not the original's): gevGameState reads the load's seconds
static ml::TimeCount s_gameTime;

void GfManager::setExec(EXEC_STATE state) {
    if (GfManager* manager = s_pThis) {
        manager->m_execState = state;
        manager->m_execFlags = s_execFlags[static_cast<unsigned int>(state)];
        if (manager->m_initialized) {
            GfEvent::callExecState(state);
        }
    }
}

GfManager::~GfManager() {
    s_pThis = nullptr;
}

void GfManager::initialize() {
    fw::Framework::addPauseCallback(this);
    GfEvent::build(m_setupParam);
    createGfParameter();
    bindPadResources();
    bindGFSoundSource();
    GfPause::build(m_setupParam);
    GfInfo::build(m_setupParam);
    GfMemManager::build(m_setupParam);
    GfDataManager::build(m_setupParam);
    GfScriptManager::build(m_setupParam);
    GfReqManager::build(m_setupParam);
    GfAssetManager::build(m_setupParam);
    GfObjManager::build(m_setupParam);
    GfSound::build(m_setupParam);
    GfMapManager::build(m_setupParam);
    GfGameManager::build(m_setupParam);
    GfFieldManager::build(m_setupParam);
    GfMenuManager::build(m_setupParam);
    GfGameManager::setState(GF_STATE(3), false);
    GfMovieManager::build(m_setupParam);
    GfEvent::addEventCallback(this);
    while (!GfMenuManager::isInitialized()) {
        GfSleep(1);
    }
    btl::BattleManager::build(m_setupParam);
    fw::RenderParam::setRenderTypeDlc(s_pThis->m_setupParam.m_dlcCameraParam);
    m_initialized = true;
}

void GfManager::destroy() {
    GfManager* manager = s_pThis;
    manager->finalize();
    delete manager;
    GfMemManager::destroyCoreMemory();
    GfStaticRes::finalize();
}

void GfManager::finalize() {
    GfGameManager::leaveGameForDebug();
    GfSleep(30);
    GfGameManager::destroyBattleEnemy();
    while (!GfGameManager::isField()) {
        GfSleep(1);
    }
    m_destroyNow = true;
    GfReqCommand::reqDestroyGf();
    while (GfReqManager::isExistCommand(nullptr)) {
        GfSleep(1);
    }
    GfEvent::removeEventCallback(this);
    btl::BattleManager::destroy();
    GfMovieManager::destroy();
    GfGameManager::setState(GF_STATE(2), false);
    GfMenuManager::destroy();
    GfFieldManager::destroy();
    GfGameManager::destroy();
    GfMapManager::destroy();
    GfSound::destroy();
    GfObjManager::destroy();
    GfAssetManager::destroy();
    GfReqManager::destroy();
    GfScriptManager::destroy();
    GfDataManager::destroy();
    GfMemManager::destroy();
    GfInfo::destroy();
    GfPause::destroy();
    unrbindGFSoundSource();
    unbindPadResource();
    destroyGfParameter();
    GfEvent::destroy();
    fw::Framework::removePauseCallback(this);
    m_initialized = false;
}

GfSetupParam& GfManager::getSetupParam() {
    return s_pThis->m_setupParam;
}

bool GfManager::isDestroyNow() {
    if (s_pThis) {
        return s_pThis->m_destroyNow;
    }
    return false;
}

void GfManager::updatePauseCallback() {
    if (s_pThis) {
        GfInfo::apply();
    }
}

bool GfManager::isExecKillPartyCreate() {
    if (s_pThis) {
        return s_pThis->m_execFlags & EXEC_FLAG_KILL_PARTY_CREATE;
    }
    return false;
}

bool GfManager::isExecModeScenarioGame() {
    if (s_pThis) {
        return s_pThis->m_execFlags & EXEC_FLAG_SCENARIO_GAME;
    }
    return false;
}

bool GfManager::isExecModeAdvertize() {
    if (s_pThis) {
        return s_pThis->m_execFlags & EXEC_FLAG_ADVERTIZE;
    }
    return false;
}

bool GfManager::isExecModeTool() {
    if (s_pThis) {
        return s_pThis->m_execState == EXEC_STATE(4);
    }
    return false;
}

bool GfManager::isExecModeDebug() {
    if (s_pThis) {
        return s_pThis->m_execState == EXEC_STATE(0);
    }
    return false;
}

bool GfManager::isExecModeThater() {
    if (s_pThis) {
        return s_pThis->m_execState == EXEC_STATE(3);
    }
    return false;
}

void GfManager::setupNewGame(const SDataSystem&, const SDataGame& game, const SDataOption&, const SDataGameIra&) {
    GfGameUtil::setupNewGameParam(game);
    s_pThis->m_gameMode = GAME_MODE_NEW;
    GfGameParty::setupNewGameParty();
    if (GfFieldTime* time = GfFieldTime::get()) {
        ElapseTime elapse = {0, 0, 0};
        time->setElapseTime(elapse);
        time->setTime(12, 0);
    }
}

void GfManager::setupPowerNewGame(const SDataSystem&, const SDataGame& game, const SDataOption&,
                                  const SDataGameIra& ira) {
    GfGameUtil::setupPoweredNewGameParam(game, ira);
    GfDataStore::fn_710022D55C();
    GfMenuManager::setupGame();
    GfGameManager::setupGame(GAME_TYPE(GfGameManager::isGameTypeIra()));
    GfFieldManager::setupGame();
    s_pThis->m_gameMode = GAME_MODE_NEW;
    GfGameParty::setupPoweredNewGameParty();
    if (GfFieldTime* time = GfFieldTime::get()) {
        time->setTime(12, 0);
    }
}

void GfManager::setupContinueGame(const SDataSystem& system, const SDataGame& game, const SDataOption& option,
                                  const SDataGameIra& ira) {
    s_pThis->m_gameMode = GAME_MODE_CONTINUE;
    GfDataManager::clear();
    GfAssetManager::clear();
    GfFieldManager::clear();
    GfGameManager::clear();
    GfDataManager::setupGame(&system, &game, &option, &ira);
    GfGameManager::setupGame(GAME_TYPE(GfGameManager::isGameTypeIra()));
    GfFieldManager::setupGame();
    s_pThis->m_loadGameTime = 0.0f;
    s_gameTime.reset();
}

void GfManager::setupEventTheater(const SDataGame& game) {
    s_pThis->m_gameMode = GAME_MODE_NONE;
    GfDataManager::clear();
    GfAssetManager::clear();
    GfFieldManager::clear();
    GfGameManager::clear();
    GfGameUtil::setChangeClothes(*GfDataManager::getDataGame(), game);
    GfDataManager::setupGame(nullptr, nullptr, GfGameUtilSaveData::getValidOptionData(), nullptr);
    GfGameManager::setupGame(GAME_TYPE(GfGameManager::isGameTypeIra()));
    GfFieldManager::setupGame();
}

void GfManager::setupReturnTitle() {
    s_pThis->m_gameMode = GAME_MODE_NONE;
    GfDataManager::clear();
    GfAssetManager::clear();
    GfFieldManager::clear();
    GfGameManager::clear();
    GfDataManager::setupGame(nullptr, nullptr, nullptr, nullptr);
    GfGameManager::setupGame(GAME_TYPE(GfGameManager::isGameTypeIra()));
    GfFieldManager::setupGame();
}

void GfManager::setupOptionData(const SDataOption& option) {
    GfDataManager::setupOptionData(option);
    if (GfSound* sound = GfSound::get()) {
        sound->setupGame();
    }
}

bool GfManager::isContinueGame() {
    if (s_pThis) {
        return s_pThis->m_gameMode == GAME_MODE_CONTINUE;
    }
    return false;
}

bool GfManager::isNewGame() {
    if (s_pThis) {
        return s_pThis->m_gameMode == GAME_MODE_NEW;
    }
    return false;
}

bool GfManager::isGameTypeIra() {
    return GfGameManager::isGameTypeIra();
}

void GfManager::setBusyForChangeGame(bool flag) {
    if (s_pThis) {
        s_pThis->m_stopUpdate = flag;
    }
}

void GfManager::resetGameType(bool flag) {
    if (fw::Framework* framework = fw::Framework::get()) {
        framework->setupThreadPostUpdate(flag);
    }
    if (fw::EffectManager* effect = fw::EffectManager::get()) {
        effect->setIra(flag);
    }
    if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
        sound->setupGameType(flag);
    }
    GfGameManager::resetGameType(flag);
    fw::RenderParam::setRenderTypeDlc(flag);
}

bool GfManager::isExistSaveData() {
    if (GfManager* manager = get()) {
        return manager->m_saveDataCreated;
    }
    return false;
}

void GfManager::setSaveDataCreated() {
    if (GfManager* manager = get()) {
        manager->m_saveDataCreated = true;
    }
}

void GfManager::startGame(bool saveDataCreated, bool clearGameCheck) {
    if (GfManager* manager = get()) {
        manager->m_saveDataCreated = saveDataCreated;
    }
    setExec(EXEC_STATE(1));
    if (isContinueGame()) {
        GfMapjumpInfo info(0);
        info.m_flags = GfMapjumpInfo::Flags();
        if (!GfGameManager::isGameTypeIra() || GfDataUtil::getSkipTravelID() != 0) {
            // the saved rotation's z read as a word: 1234 there means the save keeps no position (the game starts at
            // the skip travel point only)
            int mark = *reinterpret_cast<const int*>(&GfDataManager::getDataGame()->m_saveRot[0].z);
            unsigned int map = GfDataUtil::getSkipTravelID();
            if (mark == 1234) {
                info.m_map = map;
                info.pad_4 = 0;
            } else {
                const mm::Vec3* pos = GfDataParty::getSavePos(0, true);
                const mm::Vec3* rot = GfDataParty::getSaveRot(0, true);
                mm::Vec3 rad(rot->x * 0.017453292f, rot->y * 0.017453292f, rot->z * 0.017453292f);
                info.setupForSaveData(map, *pos, rad, GfDataUtil::isStartChapterSave());
            }
        } else {
            unsigned int word = GfDataManager::getDataGameIra()->m_word;
            const mm::Vec3* pos = GfDataParty::getSavePos(0, true);
            const mm::Vec3* rot = GfDataParty::getSaveRot(0, true);
            float rotY = rot->y * 0.017453292f;
            info.m_map = 0;
            info.pad_4 = word;
            info.m_pos = *pos;
            info.m_rotY = rotY;
            info.m_setRotY = true;
        }
        GfPlayFactory::createMapjump(info);
        if (GfDataUtil::isStartChapterSave()) {
            GfPlayFactory::createOneEvent(GfDataUtil::getEventChapterSave());
        } else {
            GfDataUtil::getAutoEventAfterLoad();
        }
    } else if (isNewGame()) {
        GfGameEvent::finishNewGameWait();
        if (GfDataUtil::isClearGameCheck()) {
            GfDataUtil::setClearGameCheck(false);
        }
    } else if (clearGameCheck) {
        GfDataUtil::setClearGameCheck(true);
    }
    GfGameManager::setStartGame();
}

void GfManager::execToAdvertize() {
    if (!isExecModeThater()) {
        setExec(EXEC_STATE(2));
    }
    GfGameManager::leaveGameForDebug();
    GfMapjumpInfo info(0);
    info.m_flags = GfMapjumpInfo::Flags();
    info.m_map = static_cast<unsigned int>(-1);
    info.pad_4 = 0;
    info.m_flags.m_startChapter = true;
    GfPlayFactory::createMapjump(info);
}

void GfManager::gevGameState(GF_STATE, GF_STATE next) {
    if (m_loadGameTime != 0.0f) {
        return;
    }
    switch (next) {
    case 0:
    case 1:
    case 2:
    case 8:
        return;
    default:
        m_loadGameTime = s_gameTime.getSecLap();
        GfEvent::callLoadGameTime(m_loadGameTime);
        break;
    }
}

void GfManager::activate() {
    if (GfFieldManager* field = GfFieldManager::get()) {
        field->setSuspendGame(false);
    }
}

void GfManager::updateAfterLayer(const fw::UpdateInfo& info) {
    if (GfGameManager* game = GfGameManager::get()) {
        game->updateAfterLayer(info);
    }
}

void GfManager::postUpdate(const fw::UpdateInfo& info) {
    if (s_pThis == nullptr || s_pThis->m_stopUpdate) {
        return;
    }
    GfInfo::apply();
    if (GfMapManager* map = GfMapManager::get()) {
        map->postUpdate(info);
    }
    if (GfFieldManager* field = GfFieldManager::get()) {
        field->postUpdate(info);
    }
    if (btl::BattleManager* battle = btl::BattleManager::get()) {
        battle->postUpdate(info);
    }
    if (GfGameManager* game = GfGameManager::get()) {
        game->postUpdate(info);
    }
    if (fw::Framework* framework = fw::Framework::get()) {
        framework->startThreadPostUpdate(info);
        if (GfMenuManager* menu = GfMenuManager::get()) {
            menu->postUpdate(info);
        }
        framework->waitThreadPostUpdate();
    }
    if (GfObjManager* obj = GfObjManager::get()) {
        obj->postUpdate(info);
    }
    if (GfPause::get()) {
        GfPause::update();
    }
}

void GfManager::update(const fw::UpdateInfo& info) {
    if (s_pThis == nullptr || !s_pThis->m_initialized) {
        return;
    }
    fw::debug::drawCompareZ(true);
    ml::TimeCount timer;
    if (s_pThis == nullptr || s_pThis->m_stopUpdate) {
        return;
    }
    GfInfo::apply();
    if (GfReqManager* req = GfReqManager::get()) {
        req->update(info);
    }
    if (GfAssetManager* asset = GfAssetManager::get()) {
        asset->update(info);
    }
    if (GfObjManager* obj = GfObjManager::get()) {
        obj->update(info);
    }
    if (GfSound* sound = GfSound::get()) {
        sound->update(info);
    }
    if (GfMapManager* map = GfMapManager::get()) {
        map->update(info);
    }
    if (GfGameManager* game = GfGameManager::get()) {
        game->update(info);
    }
    if (GfFieldManager* field = GfFieldManager::get()) {
        field->update(info);
    }
    if (!GfGameManager::isStopBattleSequence()) {
        btl::BattleManager::update(info);
    }
    if (GfMenuManager::get()) {
        GfMenuManager::update(info);
    }
    if (GfGameManager* game = GfGameManager::get()) {
        game->updateParam(info);
    }
    s_pThis->m_frameCount++;
    // the frame's clock stirs the random sequence: its low four bits draw that many numbers
    long lap;
    timer.getClockLap(lap);
    int count = lap & 0xF;
    for (int i = 0; i < count; i++) {
        ml::mtRandf1();
    }
}

}  // namespace gf
