#include "classes/gf/GfMenuObjCommonText.h"
#include "gf/QuestID.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfPlayFactory.h"
#include "gf/GfReqParam.h"
#include "classes/gf/GfSequentialPlay.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfPlayComResetBlade.h"
#include "gf/GfSetupPfTalk.h"
#include "gf/ParamReturnTitle.h"
#include "gf/GfReqCommand.h"
#include "gf/GfObjAcc.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfPlayComWaitBattleEnd.h"
#include "classes/fw/Camera.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/GfFieldTbox.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfGameCond.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfPlayComMenuCommon.h"
#include "classes/gf/GfPlayComMenuChapterSave.h"
#include "classes/gf/GfPlayComMenuPrecious.h"
#include "classes/gf/GfPlayComReturnTitle.h"
#include "classes/gf/GfPlayComBattleStart.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/GfMenuObjUtil.h"

namespace gf {

bool GfPlayFactory::createReturnTitle(const ParamReturnTitle& param) {
    if (mm::mtl::PtrSingleton<GfPlayComReturnTitle>::sys() != nullptr) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(6));
    GfSequentialPlay::addReturnTitle(param);
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createOpenMenu(unsigned int menu, GfSequentialPlaySignal* signal) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::startSignal(signal);
    GfSequentialPlay::pushState(GF_STATE(6));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(0x59);
    GfSequentialPlay::endSignal(signal);
    if (GfMenuObjUtil::isValidExpansion(3) && menu == 0x24) {
        GfSequentialPlay::addOpenMenu2(1, MAINMENU(3));
    } else {
        GfSequentialPlay::addOpenMenu(menu);
    }
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createOpenMenu2(unsigned int menu, MAINMENU main, GfSequentialPlaySignal* signal) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (GfGameManager::isEvent(false)) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(0x14))) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(4))) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return false;
    }
    if (GfSequentialPlay::isInnerPause(0x11)) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::startSignal(signal);
    GfSequentialPlay::pushState(GF_STATE(6));
    GfSequentialPlay::pushPause(0x59);
    GfSequentialPlay::endSignal(signal);
    GfSequentialPlay::addOpenMenu2(menu, main);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

void GfPlayFactory::createMiniGame() {
    if (GfGameManager::isLeaveGameForDebug() || GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::pushState(GF_STATE(6));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(0x59);
    GfSequentialPlay::addMiniGame();
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
}

bool GfPlayFactory::createSalvage(GF_OBJ_HANDLE* handle) {
    if (GfGameManager::isLeaveGameForDebug() || GfSequentialPlay::isInnerState(GF_STATE(9)) || GfSequentialPlay::isInnerState(GF_STATE(0x18)) ||
        !GfGameManager::isControlFree()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0xB));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(0x10);
    GfSequentialPlay::addSalvage(handle);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createCollect(GF_OBJ_HANDLE* handle) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(0x14))) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0xC));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(0x10);
    GfSequentialPlay::addCollect(handle);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createFieldTbox(GF_OBJ_HANDLE* handle) {
    // a box still being opened
    if (mm::mtl::PtrSingleton<GfFieldTbox>::sys()->m_seq) {
        return false;
    }
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0xD));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(0x10);
    GfSequentialPlay::addFieldTbox(handle);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createMapGimmick(GF_OBJ_HANDLE* handle) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0xE));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(0x10);
    GfSequentialPlay::addMapGimmick(handle);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createGrave(GF_OBJ_HANDLE* handle) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(0x14))) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0xF));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(0x10);
    GfSequentialPlay::addGrave(handle);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createJump(GF_OBJ_HANDLE* handle) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x10));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(0x10);
    GfSequentialPlay::addJump(handle);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createWarp(GF_OBJ_HANDLE* handle) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x11));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::pushPause(0x10);
    GfSequentialPlay::addWarp(handle);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createGmkTutorial(const char* name, unsigned int id) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (!GfGameManager::isGmkTutorialOK() || GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return false;
    }
    GfGameManager::setGmkTutorialSequenceOK(true);
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x12));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::addWaitPlayerToStartGmkTuto();
    GfSequentialPlay::pushPause(0x10);
    GfSequentialPlay::addGmkTutorial(name, id);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createGmkCamera(mm::mtl::IntrusivePtr<fw::Camera> camera) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (!GfGameManager::isGmkTutorialOK() || GfSequentialPlay::isInnerState(GF_STATE(9))) {
        return false;
    }
    GfGameManager::setGmkTutorialSequenceOK(true);
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x13));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::addWaitPlayerToStartGmkTuto();
    GfSequentialPlay::pushPause(0x10);
    GfSequentialPlay::addWaitGmkCameraEnd(camera);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createGameOver() {
    if (!GfGameManager::isEnablePlayerDeadSequence()) {
        return false;
    }
    if (GfGameScene* scene = mm::mtl::PtrSingleton<GfGameScene>::sys()) {
        if (scene->getDeadType() != 0) {
            return false;
        }
        scene->setDeadType(GfPlayerDead(1));
    }
    ParamReturnTitle param;
    param.m_waitVoice = true;
    param.m_gameClear = false;
    return createReturnTitle(param);
}

bool GfPlayFactory::createTalk(const GfSetupPfTalk& talk) {
    if (GfGameManager::isLeaveGameForDebug() || GfSequentialPlay::isInnerState(GF_STATE(9)) || !GfGameManager::isTalkOK()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::addCallbackEventSequence(talk.m_eventId, true);
    GfSequentialPlay::pushState(GF_STATE(4));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::addEventPlayerStop(true);
    GfSequentialPlay::pushPause(0x10);
    GfSequentialPlay::addTalk(talk);
    GfSequentialPlay::popPause();
    GfSequentialPlay::popState();
    GfSequentialPlay::addEventFade();
    GfSequentialPlay::addCallbackEventSequence(talk.m_eventId, false);
    GfSequentialPlay::addIraCampSaveForEvent();
    GfSequentialPlay::addWait(0.5f);
    GfSequentialPlay::addEventPlayerStop(false);
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createMapjump(const GfMapjumpInfo& info) {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    if (info.m_flags.m_stopPlayer) {
        GfSequentialPlay::addEventPlayerStop(true);
    }
    GfSequentialPlay::pushState(GF_STATE(info.m_flags.m_stopPlayer ? 9 : 8));
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::addMapjump(info);
    GfSequentialPlay::popState();
    if (info.m_flags.m_stopPlayer) {
        GfSequentialPlay::addEventPlayerStop(false);
    }
    return GfSequentialPlay::play();
}

bool GfPlayFactory::createEventMapjump(const GfMapjumpInfo& info) {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x14));
    GfSequentialPlay::pushState(GF_STATE(8));
    GfSequentialPlay::addCallbackEventSequence(0, true);
    GfSequentialPlay::addWaitBattleEnd(0);
    GfSequentialPlay::addMapjump(info);
    GfSequentialPlay::addCallbackEventSequence(0, false);
    GfSequentialPlay::popState();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createOneEventForGimmick(unsigned int id) {
    if (GfSequentialPlay::isInnerState(GF_STATE(6)) || GfSequentialPlay::isInnerState(GF_STATE(0xC))) {
        return false;
    }
    return createOneEvent(id);
}

bool GfPlayFactory::createEventAfterScript(int id) {
    if (!GfGameManager::isScenarioGame() || GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::pushPause(0x11);
    GfSequentialPlay::pushState(GF_STATE(6));
    GfSequentialPlay::addAfterEventScript(id);
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createQuestUIOrder(QuestID id, bool flag1, bool flag2) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(flag1));
    GfSequentialPlay::pushPause(0x11);
    GfSequentialPlay::pushState(GF_STATE(6));
    GfSequentialPlay::addQuestUIOrder(id, flag2);
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createQuestUIComplete(QuestID id, QuestID next, QSTATE state) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushPause(0x11);
    GfSequentialPlay::pushState(GF_STATE(6));
    GfSequentialPlay::addQuestUIComplete(id, next, state);
    GfSequentialPlay::addIraCampSaveForEvent();
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createQuestUIComplete(QuestID id) {
    if (!GfGameManager::isScenarioGame() || GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::addQuestUIComplete(id, QuestID(), QSTATE(0));
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createMenuPrecious(unsigned int id, bool flag) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(GfPlayComMenuPrecious::s_activate < 1 && flag));
    GfSequentialPlay::pushPause(0x11);
    GfSequentialPlay::pushState(GF_STATE(6));
    GfSequentialPlay::addMenuPrecious(id);
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createEventWait(float time, GF_OBJ_HANDLE* handle) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(7));
    GfSequentialPlay::addWaitEvent(time, handle);
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

int GfPlayFactory::createCommonMessage(unsigned int id) {
    int handle = -1;
    if ((GfGameManager::isScenarioGame() || GfManager::isExecModeDebug()) && !GfGameManager::isLeaveGameForDebug()) {
        if (!GfGameManager::isControlFree()) {
            GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
            GfSequentialPlay::pushPause(0x11);
            GfSequentialPlay::pushState(GF_STATE(6));
            GfSequentialPlay::addEventFade();
            handle = GfSequentialPlay::addMenuCommon(id);
            GfSequentialPlay::popState();
            GfSequentialPlay::popPause();
            GfSequentialPlay::play();
        } else if (!GfSequentialPlay::isPlay()) {
            GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
            GfSequentialPlay::pushState(GF_STATE(6));
            GfSequentialPlay::pushPause(0x11);
            GfSequentialPlay::addEventFade();
            handle = GfSequentialPlay::addMenuCommon(id);
            GfSequentialPlay::popPause();
            GfSequentialPlay::popState();
            GfSequentialPlay::addWait(0.5f);
            GfSequentialPlay::play();
        }
    }
    return handle;
}

int GfPlayFactory::createCommonMessage(const MenuCommonWindowParam& param) {
    int handle = -1;
    if ((GfGameManager::isScenarioGame() || GfManager::isExecModeDebug()) && !GfGameManager::isLeaveGameForDebug()) {
        if (!GfGameManager::isControlFree()) {
            GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
            GfSequentialPlay::pushPause(0x11);
            GfSequentialPlay::pushState(GF_STATE(6));
            GfSequentialPlay::addEventFade();
            handle = GfSequentialPlay::addMenuCommon(param);
            GfSequentialPlay::popState();
            GfSequentialPlay::popPause();
            GfSequentialPlay::play();
        } else if (!GfSequentialPlay::isPlay()) {
            GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
            GfSequentialPlay::pushState(GF_STATE(6));
            GfSequentialPlay::pushPause(0x11);
            GfSequentialPlay::addEventFade();
            handle = GfSequentialPlay::addMenuCommon(param);
            GfSequentialPlay::popPause();
            GfSequentialPlay::popState();
            GfSequentialPlay::addWait(0.5f);
            GfSequentialPlay::play();
        }
    }
    return handle;
}

bool GfPlayFactory::isDispCommonMessage(unsigned int id) {
    return GfPlayComMenuCommon::isDisp(id);
}

int GfPlayFactory::getDispCommonMessage(unsigned int id) {
    return GfPlayComMenuCommon::getResult(id);
}

bool GfPlayFactory::isDispChapterSave() {
    return GfPlayComMenuChapterSave::isDisp();
}

void GfPlayFactory::createOpenChapterSave(unsigned int id) {
    if (!GfGameManager::isScenarioGame() || GfGameManager::isLeaveGameForDebug()) {
        return;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::pushPause(0x11);
    GfSequentialPlay::pushState(GF_STATE(6));
    GfSequentialPlay::addMenuChapterSave(id);
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
}

void GfPlayFactory::createOpenZoneUI(unsigned int id) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::addEventFade();
    GfSequentialPlay::addMenuZone(id);
    GfSequentialPlay::play();
}

void GfPlayFactory::createOpenChapterUI(unsigned int id) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::addEventFade();
    GfSequentialPlay::addMenuChapter(id);
    GfSequentialPlay::play();
}

void GfPlayFactory::createOpenChapterEndUI(unsigned int id) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::addMenuChapterEnd(id);
    GfSequentialPlay::play();
}

void GfPlayFactory::createOpenDummyTutorial(unsigned int id) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::addMenuDummyTutorial(id);
    GfSequentialPlay::play();
}

void GfPlayFactory::createBattleStart(bool flag) {
    int enable = !GfGameManager::isLeaveGameForDebug();
    if (mm::mtl::PtrSingleton<GfPlayComBattleStart>::sys() == nullptr && enable) {
        GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
        GfSequentialPlay::addBattleStart(flag);
        GfSequentialPlay::play();
    }
}

void GfPlayFactory::createGimmickTaskComplete(gmk::GmkType type, unsigned int id, float time) {
    if (GfGameManager::isLeaveGameForDebug()) {
        return;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::pushState(GF_STATE(0x15));
    GfSequentialPlay::addGimmickTaskComplete(type, id, time);
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
}

bool GfPlayFactory::createChainAttack() {
    if (GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    if (!GfGameManager::isControlFree()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushPause(0x11);
    GfSequentialPlay::pushState(GF_STATE(0x16));
    GfSequentialPlay::addChainAttack();
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createArtsMovie(const char* name) {
    if (GfGameManager::isLeaveGameForDebug() || !GfGameManager::isControlFree()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushPause(0x11);
    GfSequentialPlay::pushState(GF_STATE(0x17));
    GfSequentialPlay::addArtsMovie(name);
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createResetBladeForBattleEnd(unsigned int slot, int setId, bool stopPlayer) {
    if (GfPlayComResetBlade::isPlaying(slot)) {
        return false;
    }
    GfObjAcc acc(GfGameParty::getHandleDriver(slot, 0));
    if (acc.isBattle()) {
        return false;
    }
    if (GfPlayComWaitBattleEnd::s_activate >= 1) {
        GfReqCommand::reqChangeBladeWithSetId(slot, setId, true);
        return true;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(0x14))) {
        return false;
    }
    if (GfSequentialPlay::isSequenceSpecialAction()) {
        return false;
    }
    if (GfSequentialPlay::isExistResetBladeParty(slot)) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    if (stopPlayer) {
        GfSequentialPlay::addResetBladePlayerStop(true);
    }
    GfSequentialPlay::pushState(GF_STATE(0x18));
    GfSequentialPlay::addResetBlade(slot, setId);
    GfSequentialPlay::popState();
    if (stopPlayer) {
        GfSequentialPlay::addResetBladePlayerStop(false);
    }
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createResetBladeForBladeSwitch(unsigned int slot, int setId) {
    if (GfPlayComResetBlade::isPlaying(slot)) {
        return false;
    }
    GfObjAcc acc(GfGameParty::getHandleDriver(slot, 0));
    if (acc.isBattle()) {
        return false;
    }
    if (GfPlayComWaitBattleEnd::s_activate >= 1) {
        GfReqCommand::reqChangeBladeWithSetId(slot, setId, true);
        return true;
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(0x14))) {
        return false;
    }
    if (GfSequentialPlay::isSequenceSpecialAction()) {
        return false;
    }
    if (GfSequentialPlay::isExistResetBladeParty(slot)) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x18));
    GfSequentialPlay::addResetBlade(slot, setId);
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createPartySwitchForIra() {
    if (!GfGameCond::isGameCond(
            static_cast<unsigned short>(Bdat::getValCheck(GfDataBdat::getFP(0x17E), "cond", 0x2F, 2)))) {
        return false;
    }
    for (unsigned int i = 0; i < 3; i++) {
        if (GfPlayComResetBlade::isPlaying(i)) {
            return false;
        }
    }
    if (GfSequentialPlay::isInnerState(GF_STATE(0x14))) {
        return false;
    }
    if (GfSequentialPlay::isSequenceSpecialAction()) {
        return false;
    }
    for (unsigned int i = 0; i < 3; i++) {
        if (GfSequentialPlay::isExistResetBladeParty(i)) {
            return false;
        }
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x18));
    GfSequentialPlay::addMoverSwitch();
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createBladeSwitch() {
    if (GfSequentialPlay::isInnerState(GF_STATE(0x14))) {
        return false;
    }
    if (GfSequentialPlay::isSequenceSpecialAction()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x18));
    GfSequentialPlay::addResetBlade(0, 0);
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createBladeSwitchFR() {
    if (GfSequentialPlay::isInnerState(GF_STATE(0x14))) {
        return false;
    }
    if (GfSequentialPlay::isSequenceSpecialAction()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x18));
    GfSequentialPlay::addResetBlade(0, 1);
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createBladeSwitchBR() {
    if (GfSequentialPlay::isInnerState(GF_STATE(0x14))) {
        return false;
    }
    if (GfSequentialPlay::isSequenceSpecialAction()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x18));
    GfSequentialPlay::addResetBlade(0, 2);
    GfSequentialPlay::popState();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createMenuObjCommonText(GfMenuObjCommonText::OpenKizunaParam& param) {
    if ((!GfGameManager::isScenarioGame() && !GfManager::isExecModeDebug()) || GfGameManager::isLeaveGameForDebug()) {
        return false;
    }
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(1));
    GfSequentialPlay::pushPause(0x11);
    GfSequentialPlay::pushState(GF_STATE(6));
    GfSequentialPlay::addEventFade();
    GfSequentialPlay::addMenuObjCommonText(param);
    GfSequentialPlay::popState();
    GfSequentialPlay::popPause();
    GfSequentialPlay::play();
    return true;
}

bool GfPlayFactory::createHoodHomuraBattou() {
    GfSequentialPlay::beginCommand(GfSequentialPlay::TYPE(0));
    GfSequentialPlay::pushState(GF_STATE(0x18));
    GfSequentialPlay::addHoodHomuraBattou();
    GfSequentialPlay::popState();
    return GfSequentialPlay::play();
}

}  // namespace gf
