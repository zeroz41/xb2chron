#include "classes/gf/BgmTrack.h"
#include "classes/gf/GfFieldBgm.h"
#include "classes/gf/BgmGimmick.h"
#include "classes/gf/BgmBattle.h"
#include "classes/gf/BgmBattleBoss.h"
#include "classes/gf/BgmField.h"
#include "classes/gf/BgmEvent.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfBdatMaplist.h"
#include "classes/gf/BgmTrack.h"
#include "classes/gf/GfFieldBgm.h"
#include "classes/gf/BgmGimmick.h"
#include "classes/gf/BgmBattle.h"
#include "classes/gf/BgmBattleBoss.h"
#include "classes/gf/BgmField.h"
#include "classes/gf/BgmEvent.h"
#include "classes/gf/GfGameScene.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfBdatBgm.h"
#include "classes/gf/GfBdatMaplist.h"
#include "classes/gf/GfDeadCamera.h"
#include "classes/gf/GfEvtBgm.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfManager.h"

namespace gf {
namespace _gffsn {

bool s_bStopBGM;

// the step a fade check returns: towards silence (negative) while fadeOut, else towards full volume, over time
// (1.0.0's out-of-line symbol; 3.0.1 inlines it everywhere)
float bgmvolControlFade(const fw::UpdateInfo& info, float time, bool fadeOut) {
    if (time < 1e-6f) {
        return fadeOut ? -1.0f : 1.0f;
    }
    float step = info.m_deltaTime / time;
    return fadeOut ? -step : step;
}

float bgmvolIsBattleDead(ExecFadeParam& param) {
    bool fadeOut = GfGameManager::getDeadType() == 1;
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolAdvertize(ExecFadeParam& param) {
    return bgmvolControlFade(*param.m_updateInfo,
                             GfManager::isExecModeAdvertize() ? param.m_fade->m_fadeOutTime
                                                              : param.m_fade->m_fadeInTime,
                             GfManager::isExecModeAdvertize());
}

float bgmvolStop(ExecFadeParam& param) {
    return bgmvolControlFade(*param.m_updateInfo,
                             s_bStopBGM ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, s_bStopBGM);
}



float bgmvolMapMatch(ExecFadeParam& param) {
    bool fadeOut = param.m_track->m_fieldBgm->getRscFieldBgmID() != param.m_track->getBgmCondID();
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolGimmickMatch(ExecFadeParam& param) {
    bool fadeOut = param.m_track->m_fieldBgm->getRscGimmickBgmID() != param.m_track->getBgmCondID();
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolFadeGimmick(ExecFadeParam& param) {
    bool fadeOut = param.m_track->m_fieldBgm->getRscGimmickBgmID() != 0;
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolBattleBoss(ExecFadeParam& param) {
    bool fadeOut = param.m_track->m_fieldBgm->getRscBossBattleBgmID() != 0 || GfGameManager::isForceBossBattleBgm();
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolNotBattleBoss(ExecFadeParam& param) {
    bool fadeOut = !(param.m_track->m_fieldBgm->getRscBossBattleBgmID() != 0 || GfGameManager::isForceBossBattleBgm());
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolFadeEvent(ExecFadeParam& param) {
    bool fadeOut = BgmBattleBoss::get()->getBgmCondID() == 0x55 && param.m_track->m_fieldBgm->getRscBossBattleBgmID() != 0x55;
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolFadeBattleEvent(ExecFadeParam& param) {
    bool fadeOut = GfGameScene::get()->m_battleEventBgm;
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolFadeBattle(ExecFadeParam& param) {
    bool fadeOut = GfGameManager::isBattle() || GfGameManager::isForceBossBattleBgm();
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolFadeNotBattle(ExecFadeParam& param) {
    bool fadeOut = !(GfGameManager::isBattle() || GfGameManager::isForceBossBattleBgm());
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolFadeLeaveGame(ExecFadeParam& param) {
    bool fadeOut = GfGameManager::isLeaveGameForDebug();
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolFadeDeadSequence(ExecFadeParam& param) {
    bool fadeOut = param.m_track->m_fieldBgm->m_deadSequence;
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolFadeEnableEventBgm(ExecFadeParam& param) {
    bool fadeOut = GfEvtBgm::get()->isEnableEventBgm() || GfGameManager::isForceEventBgm();
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

float bgmvolFadeDisableEventBgm(ExecFadeParam& param) {
    bool fadeOut = !(GfEvtBgm::get()->isEnableEventBgm() || GfGameManager::isForceEventBgm());
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

}  // namespace _gffsn

void GfFieldBgm::stopBgmForDebug(bool stop) {
    _gffsn::s_bStopBGM = stop;
}

void GfFieldBgm::setGimmickBgmID(unsigned int id) {
    if (id == 0 && m_gimmickBgmID != 0) {
        m_gimmickBgmClearWait = 30;
    }
    m_gimmickBgmID = id;
}


unsigned int GfFieldBgm::getRscFieldBgmID() const {
    unsigned int mapId = GfGameManager::getMapID();
    if (mapId == 0) {
        return 0;
    }
    return GfBdatMaplist::get()->getMaplistbgm_cndID(mapId);
}

void BgmEvent::cancelOverTime() {
    m_overTime = 0.0f;
}

BgmTrack::~BgmTrack() {}
const char* BgmGimmick::getTrackName() const { return "GimmickBGM"; }
const char* BgmBattle::getTrackName() const { return "BattleBGM"; }
const char* BgmBattleBoss::getTrackName() const { return "BossBGM"; }
BgmEvent::~BgmEvent() {}
const char* BgmEvent::getTrackName() const { return "EventBGM"; }
const char* BgmField::getTrackName() const { return "FieldBGM"; }


}  // namespace gf
