#include "classes/gf/BgmTrack.h"
#include "classes/gf/GfFieldBgm.h"
#include "classes/gf/BgmGimmick.h"
#include "classes/gf/BgmBattle.h"
#include "classes/gf/BgmBattleBoss.h"
#include "classes/gf/BgmField.h"
#include "classes/gf/BgmEvent.h"
#include "classes/gf/GfGameScene.h"
#include "gf/MapjumpCallbackInfo.h"
#include "classes/gf/GfBdatMaplist.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfBdatBgm.h"
#include "classes/gf/GfDeadCamera.h"
#include "classes/gf/GfEvtBgm.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfSound.h"

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

GfFieldBgm::~GfFieldBgm() {
    for (BgmTrack** it = m_tracks.begin(); it != m_tracks.end(); ++it) {
        if (*it != nullptr) {
            delete *it;
            *it = nullptr;
        }
    }
}

void GfFieldBgm::setRscBattleBgmID(unsigned int id) {
    if (id != 0) {
        if (GfBdatBgm::get()->getBgmConditionPriority(id) <= 1) {
            m_rscBossBattleBgmID = 0;
            m_rscBattleBgmID = id;
        } else if (BgmBattle::get()->getBgmCondID() == id) {
            m_rscBossBattleBgmID = 0;
        } else {
            m_rscBossBattleBgmID = id;
            m_bossBattleBgmWait = 0;
        }
    } else {
        m_rscBossBattleBgmID = 0;
        m_rscBattleBgmID = 0;
    }
}

void GfFieldBgm::gevBattleEnd() {
    m_rscBossBattleBgmID = 0;
    m_rscBattleBgmID = 0;
}

void GfFieldBgm::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    switch (gev) {
    case GEV(1):
        if (info.m_jumpKind == 2) {
            m_deadSequence = true;
        }
        m_disableFieldBgmChange = true;
        break;
    case GEV(6):
        if (info.m_jumpKind == 2) {
            m_deadSequence = false;
        }
        m_disableFieldBgmChange = false;
        break;
    default:
        break;
    }
}

inline void GfFieldBgm::setPause(bool pause) {
    for (BgmTrack* track : m_tracks) {
        track->setPause(pause);
    }
}

void GfFieldBgm::gevPause(unsigned int prev, unsigned int cur) {
    if (!(prev & 4) && (cur & 4)) {
        setPause(true);
    } else if ((prev & 4) && !(cur & 4)) {
        setPause(false);
    }
}

void GfFieldBgm::gevPlayEvent(GEV gev, unsigned int param) {
    if (gev == GEV(13)) {
        if (BgmEvent* event = BgmEvent::get()) {
            event->gevPlayEvent(gev, param);
        }
    }
}

void BgmTrack::setPause(bool pause) {
    m_pause = pause;
    if (GfSound* sound = GfSound::get()) {
        for (unsigned long i = 0; i < 4; ++i) {
            BGMCOND& cond = m_conds[i];
            if (cond.m_handle.isValid()) {
                sound->setPause(cond.m_handle, pause, 0.0f);
            }
        }
    }
}

bool GfFieldBgm::isBossBgmCopied() const {
    BgmBattleBoss* boss = BgmBattleBoss::get();
    return boss != nullptr ? boss->m_copied : false;
}

void GfFieldBgm::fn_7100262E58(const mm::mtl::FixStr<64>& name) {
    if (BgmField* field = BgmField::get()) {
        field->fn_7100262E70(name.m_str);
    }
}

void BgmBattle::update(const fw::UpdateInfo& info) {
    if (getBgmCondID() != m_fieldBgm->getRscBattleBgmID()) {
        fn_7100263490(m_fieldBgm->getRscBattleBgmID());
    }
    BgmTrack::update(info);
}

bool BgmTrack::isPlaying() const {
    for (unsigned long i = 0; i < 4; ++i) {
        const BGMCOND& cond = m_conds[i];
        if (cond.m_bgmFileName.length() != 0 || cond.m_handle.isValid()) {
            return true;
        }
    }
    return false;
}

void BgmTrack::setCategoryApply(unsigned char category) {
    m_category = category;
    if (GfSound* sound = GfSound::get()) {
        for (unsigned long i = 0; i < 4; ++i) {
            BGMCOND& cond = m_conds[i];
            if (cond.m_handle.isValid()) {
                sound->setCategory(cond.m_handle, fw::SoundCategory(category));
            }
        }
    }
}

bool BgmEvent::isPlaying() const {
    return BgmTrack::isPlaying();
}

void BgmEvent::cancelOverTime() {
    m_overTime = 0.0f;
}

void BgmEvent::update(const fw::UpdateInfo& info) {
    fn_7100265120(info);
    BgmTrack::update(info);
}

float BgmTrack::getPlayTime() const {
    float result = 0.0f;
    if (GfSound* sound = GfSound::get()) {
        for (unsigned long i = 0; i < 4; ++i) {
            const BGMCOND& cond = m_conds[i];
            if (cond.m_handle.isValid()) {
                float time;
                result = sound->getPlayTime(cond.m_handle, time) ? time : 0.0f;
                break;
            }
        }
    }
    return result;
}

float BgmTrack::getTotalTime() const {
    float result = 0.0f;
    if (GfSound* sound = GfSound::get()) {
        for (unsigned long i = 0; i < 4; ++i) {
            const BGMCOND& cond = m_conds[i];
            if (cond.m_handle.isValid()) {
                float time;
                result = sound->getTotalTime(cond.m_handle, time) ? time : 0.0f;
                break;
            }
        }
    }
    return result;
}

BgmTrack::~BgmTrack() {}
const char* BgmGimmick::getTrackName() const { return "GimmickBGM"; }
const char* BgmBattle::getTrackName() const { return "BattleBGM"; }
const char* BgmBattleBoss::getTrackName() const { return "BossBGM"; }
BgmEvent::~BgmEvent() {}
const char* BgmEvent::getTrackName() const { return "EventBGM"; }
const char* BgmField::getTrackName() const { return "FieldBGM"; }


}  // namespace gf
