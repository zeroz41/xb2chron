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
#include "ml/MtRand.h"
#include "gf/FileStaticVec3.h"
#include "classes/gf/GfReqManager.h"
#include "classes/gf/GfScriptManager.h"
#include "classes/gf/GfMovieManager.h"
#include "classes/fw/CommonResource.h"
#include "gf/GfParamIkReflection.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfMemManager.h"

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
    fw::fn_71001996F0(s_pThis->m_setupParam.m_dlcCameraParam);
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

bool GfManager::fn_710032A1DC() {
    return GfGameManager::fn_71002A9E68();
}

void GfManager::fn_710032A1E0(bool flag) {
    if (s_pThis) {
        s_pThis->m_stopUpdate = flag;
    }
}

void GfManager::fn_710032A1FC(bool flag) {
    if (fw::Framework* framework = fw::Framework::get()) {
        framework->fn_71001836D0(flag);
    }
    if (fw::EffectManager* effect = fw::EffectManager::get()) {
        effect->fn_710017CB08(flag);
    }
    if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
        sound->fn_71001A0EF8(flag);
    }
    GfGameManager::fn_71002AC558(flag);
    fw::fn_71001996F0(flag);
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

void GfManager::fn_710032A958(const fw::UpdateInfo& info) {
    if (GfGameManager* game = GfGameManager::get()) {
        game->fn_71002AC9C0(info);
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
        framework->fn_710018369C(info);
        if (GfMenuManager* menu = GfMenuManager::get()) {
            menu->postUpdate(info);
        }
        framework->fn_71001836A8();
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
