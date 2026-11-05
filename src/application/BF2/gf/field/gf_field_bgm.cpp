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
#include "mm/Math.h"
#include "gf/GfUtil.h"
#include "classes/gf/GfBdatBgm.h"
#include "classes/gf/GfDeadCamera.h"
#include "classes/gf/GfEvtBgm.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfSound.h"
#include "classes/gf/GfPause.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/SkipManager.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfPlayComEventFade.h"
#include "gf/GfDataUtil.h"

namespace gf {
namespace _gffsn {

// where streamed BGM files live and their folder (makePlayFileName and streamPlay build the play path from them)
const char* s_szStreamPath = "/stream/";
const char* s_szBgmPath = "/bgm/";

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


float bgmvolCondition(ExecFadeParam& param) {
    bool fadeOut = !GfGameCond::isGameCond(
        param.m_track->getBgmConditionConditionID(param.m_track->m_bgmCondID, param.m_cond->m_conditionNo));
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

}  // namespace _gffsn

unsigned int BgmTrack::getBgmConditionConditionID(unsigned int id, unsigned int index) const {
    GfBdatBgm* bdat = GfBdatBgm::sys();
    unsigned int count = 0;
    for (unsigned int i = 0; i < 4; i++) {
        unsigned int cond = bdat->getBgmConditionCondition(id, i);
        if (cond == 0) {
            continue;
        }
        if (count == index) {
            return cond;
        }
        count++;
    }
    return 0;
}

namespace _gffsn {

float bgmvolBossCondition(ExecFadeParam& param) {
    bool fadeOut = !(GfGameCond::isGameCond(param.m_track->getBgmConditionConditionID(
                         param.m_track->m_bgmCondID, param.m_cond->m_conditionNo)) ||
                     GfGameManager::isForceBossBattleBgm());
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
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

float bgmvolFadeOCG(ExecFadeParam& param) {
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

// 2.0.0's symbols name it. What it does: a volume fade check like the others: fades out while the game data's local
// flag (GfDataUtil::getScenarioFlag) is 11091 or 11116 and GfPlayComEventFade::s_activate is set, else fades in.
float bgmvolFadeEnableEvent1763(ExecFadeParam& param) {
    bool fadeOut = (GfDataUtil::getScenarioFlag() == 11091 || GfDataUtil::getScenarioFlag() == 11116) &&
                   GfPlayComEventFade::s_activate != 0;
    return bgmvolControlFade(*param.m_updateInfo,
                             fadeOut ? param.m_fade->m_fadeOutTime : param.m_fade->m_fadeInTime, fadeOut);
}

}  // namespace _gffsn

void GfFieldBgm::destroy() {
    for (BgmTrack* track : m_tracks) {
        track->stopBGM(2.0f);
        track->m_baseVolume = 1.0f;
        track->m_fadeVolume = 1.0f;
        track->m_fadeScale = 1.0f;
        track->m_category = 1;
    }
}

void GfFieldBgm::update(const fw::UpdateInfo& info) {
    if (m_rscBossBattleBgmID != 0 && m_rscBossBattleBgmID != 0xFF && !BgmBattleBoss::get()->isPlaying() &&
        !GfPause::isPause(0x59)) {
        if (m_bossBattleBgmWait++ >= 299) {
            m_rscBossBattleBgmID = 0;
            m_bossBattleBgmWait = 0;
        }
    }
    if (--m_gimmickBgmClearWait <= 0 && m_gimmickBgmID != 0xFFFFFFFF) {
        m_rscGimmickBgmID = m_gimmickBgmID;
        m_gimmickBgmID = 0xFFFFFFFF;
    }
    if (!m_disableFieldBgmChange) {
        for (BgmTrack* track : m_tracks) {
            track->update(info);
        }
    }
}

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

void GfFieldBgm::playFieldBgmForce(const char* name) {
    if (BgmField* field = BgmField::get()) {
        field->playForEventTheater(name);
    }
}

BgmBattle::BgmBattle(GfFieldBgm* fieldBgm) : BgmTrack(fieldBgm, true) {
    addVolumeFade(_gffsn::bgmvolStop, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolCondition, 4.0f, 4.0f, true);
    addVolumeFade(_gffsn::bgmvolBattleBoss, 2.0f, 8.0f, false);
    addVolumeFade(_gffsn::bgmvolFadeNotBattle, 2.0f, 2.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeLeaveGame, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeDeadSequence, 2.0f, 99.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeEnableEventBgm, 2.0f, 2.0f, true);
    m_keepBgmCondID = true;
    play(m_fieldBgm->getRscBattleBgmID());
}

BgmTrack::BgmTrack(GfFieldBgm* fieldBgm, bool battle)
    : m_bgmCondID(0), m_battle(battle), m_keepBgmCondID(false), m_baseVolume(1.0f), m_fadeVolume(1.0f),
      m_fadeScale(1.0f), m_playTime(0.0f), m_fieldBgm(fieldBgm), m_copied(false), m_category(1) {
    m_conds.assign(BGMCOND());
    for (unsigned int i = 0; i < 4; i++) {
        m_conds[i].m_conditionNo = i;
    }
}

void BgmTrack::play(unsigned int id) {
    if (m_bgmCondID != 0) {
        for (unsigned long i = 0; i < 4; ++i) {
            if (!(m_conds[i].m_volume <= 0.0f)) {
                return;
            }
        }
        stopBGM(0.0f);
    }
    m_bgmCondID = id;
}

void BgmBattle::update(const fw::UpdateInfo& info) {
    if (getBgmCondID() != m_fieldBgm->getRscBattleBgmID()) {
        play(m_fieldBgm->getRscBattleBgmID());
    }
    BgmTrack::update(info);
}

BgmBattleBoss::BgmBattleBoss(GfFieldBgm* fieldBgm) : BgmTrack(fieldBgm, true) {
    addVolumeFade(_gffsn::bgmvolStop, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolBossCondition, 4.0f, 4.0f, true);
    addVolumeFade(_gffsn::bgmvolNotBattleBoss, 8.0f, 2.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeOCG, 2.0f, 2.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeNotBattle, 2.0f, 2.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeLeaveGame, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeDeadSequence, 2.0f, 99.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeEnableEventBgm, 2.0f, 2.0f, true);
    play(m_fieldBgm->getRscBossBattleBgmID());
}

void BgmTrack::stopBGM(float time) {
    for (unsigned long i = 0; i < 4; ++i) {
        stopCondBGM(time, m_conds[i]);
    }
    m_fadeVolume = 0.0f;
    m_fadeScale = 1.0f;
    if (!m_keepBgmCondID) {
        m_bgmCondID = 0;
    }
    m_conds[0].m_bgmFileName = "";
}

bool BgmTrack::makePlayFileName(mm::mtl::FixStr<64>& name) const {
    for (const BGMCOND& cond : m_conds) {
        if (cond.m_bgmFileName.length() == 0) {
            if (!cond.m_handle.isValid()) {
                continue;
            }
            if (unsigned int bgmID = m_bgmCondID != 0 ? getBgmConditionBgmID(m_bgmCondID, cond.m_conditionNo) : 0) {
                const char* fileName = GfBdatBgm::sys()->getBgmListfilename(bgmID);
                if (util::getFilePtrFromPath(fileName) != fileName) {
                    name.format("%s%s", _gffsn::s_szStreamPath, fileName);
                } else {
                    name.format("%s%s%s", _gffsn::s_szStreamPath, _gffsn::s_szBgmPath, fileName);
                }
                return true;
            }
        }
        if (cond.m_bgmFileName.length() != 0) {
            name = cond.m_bgmFileName;
            return true;
        }
    }
    return false;
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

void BgmTrack::copyPlayParam(BgmTrack* src, const BgmFileInfo& info) {
    stopBGM(0.0f);
    m_bgmCondID = info.m_bgmCondID;
    m_fadeVolume = src->m_fadeVolume;
    m_baseVolume = src->m_baseVolume;
    m_playing = true;
    for (BGMCOND& cond : m_conds) {
        cond.clear();
    }
    SoundHandle handle;
    float volume = 0.0f;
    for (BGMCOND& cond : src->m_conds) {
        if (cond.m_handle.isValid()) {
            handle = cond.m_handle;
            volume = cond.m_volume;
            cond.m_handle.clear();
            break;
        }
    }
    if (handle.isValid()) {
        m_conds[info.m_condNo].m_playNo = info.m_bgmID;
        m_conds[info.m_condNo].m_handle = handle;
        m_conds[info.m_condNo].m_volume = volume;
    }
    if (GfSound* sound = GfSound::get()) {
        for (BGMCOND& cond : src->m_conds) {
            if (cond.m_handle.isValid()) {
                sound->setCategory(cond.m_handle, fw::SoundCategory(m_category));
            }
        }
    }
    src->m_bgmCondID = 0;
    src->m_baseVolume = 0.0f;
    src->m_fadeVolume = 0.0f;
    for (BGMCOND& cond : src->m_conds) {
        cond.clear();
    }
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

void BgmEvent::setBgmClearByStopBgm() {
    if (GfGameManager::isGameTypeIra() && m_overTime < 0.0f) {
        m_overTimeStop = true;
    }
}

void BgmEvent::update(const fw::UpdateInfo& info) {
    updateEventBgm(info);
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

BgmField::BgmField(GfFieldBgm* fieldBgm) : BgmTrack(fieldBgm, false) {
    addVolumeFade(_gffsn::bgmvolAdvertize, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolStop, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolCondition, 4.0f, 4.0f, true);
    addVolumeFade(_gffsn::bgmvolMapMatch, 4.0f, 4.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeBattle, 2.0f, 2.0f, false);
    addVolumeFade(_gffsn::bgmvolFadeLeaveGame, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeGimmick, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeEnableEventBgm, 2.0f, 2.0f, true);
    addVolumeFade(_gffsn::bgmvolIsBattleDead, 2.0f, 2.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeBattleEvent, 2.0f, 2.0f, true);
}

BgmField::~BgmField() {}

void BgmField::update(const fw::UpdateInfo& info) {
    unsigned int id = m_fieldBgm->getRscFieldBgmID();
    if (getBgmCondID() != id) {
        if (getBgmCondID() != 0) {
            stopBGM(4.0f);
        }
        m_bgmCondID = id;
    }
    BgmTrack::update(info);
}

BgmGimmick::BgmGimmick(GfFieldBgm* fieldBgm) : BgmTrack(fieldBgm, false) {
    addVolumeFade(_gffsn::bgmvolAdvertize, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolStop, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolCondition, 4.0f, 4.0f, true);
    addVolumeFade(_gffsn::bgmvolGimmickMatch, 4.0f, 4.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeBattle, 2.0f, 2.0f, false);
    addVolumeFade(_gffsn::bgmvolFadeLeaveGame, 1.0f, 1.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeEnableEventBgm, 2.0f, 2.0f, true);
    addVolumeFade(_gffsn::bgmvolIsBattleDead, 2.0f, 2.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeBattleEvent, 2.0f, 2.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeEnableEvent1763, 2.0f, 2.0f, false);
}

void BgmGimmick::update(const fw::UpdateInfo& info) {
    unsigned int id = m_fieldBgm->getRscGimmickBgmID();
    if (getBgmCondID() != id) {
        if (getBgmCondID() != 0) {
            stopBGM(4.0f);
        }
        m_bgmCondID = id;
    }
    BgmTrack::update(info);
}

void BgmTrack::calcMultiplyVolume(const fw::UpdateInfo& info) {
    float volume = 1.0f;
    float fadeOutTime = 5.0f;
    float fadeInTime = 5.0f;
    for (MultiplyVolume& entry : m_multiplyVolumes) {
        volume *= entry.m_func(entry.m_fadeOutTime, entry.m_fadeInTime, entry.m_param);
        fadeOutTime = fadeOutTime > entry.m_fadeOutTime ? entry.m_fadeOutTime : fadeOutTime;
        fadeInTime = fadeInTime > entry.m_fadeInTime ? entry.m_fadeInTime : fadeInTime;
    }
    if (volume < m_baseVolume) {
        m_baseVolume -= info.m_deltaTime / fadeOutTime;
        mm::clampSelf(m_baseVolume, volume, 1.0f);
    } else if (volume > m_baseVolume) {
        m_baseVolume += info.m_deltaTime / fadeInTime;
        mm::clampSelf(m_baseVolume, 0.0f, volume);
    }
}

bool BgmTrack::getPlayVolume(float& volume, const fw::UpdateInfo& info, const BGMCOND& cond, bool fadeOut) {
    ExecFadeParam param;
    param.m_cond = &cond;
    param.m_track = this;
    param.m_updateInfo = &info;
    volume = cond.m_volume;
    float minStep = 0.0f;
    bool result = false;
    for (const BgmVolumeFade& fade : m_volumeFades) {
        param.m_fade = &fade;
        float step = fade.m_func(param);
        if (fadeOut) {
            step = step > 0.0f ? -step : step;
        }
        if (minStep > step) {
            minStep = step;
            result = fade.m_flag;
        }
    }
    if (minStep < 0.0f) {
        volume += minStep;
        if (volume < 0.0f) {
            volume = 0.0f;
        } else if (volume > 1.0f) {
            volume = 1.0f;
        }
        return result || fadeOut;
    }
    float maxStep = 0.0f;
    for (const BgmVolumeFade& fade : m_volumeFades) {
        param.m_fade = &fade;
        float step = fade.m_func(param);
        maxStep = maxStep < step ? step : maxStep;
    }
    if (maxStep > 0.0f) {
        volume += maxStep;
        if (volume < 0.0f) {
            volume = 0.0f;
        } else if (volume > 1.0f) {
            volume = 1.0f;
        }
    }
    return false;
}

void BgmTrack::stopCondBGM(float time, BGMCOND& cond) {
    GfSound* sound = GfSound::sys();
    if (sound != nullptr && cond.m_handle.isValid()) {
        if (time > 1.0f) {
            event::SkipManager* skip = mm::mtl::Singleton<event::SkipManager>::getPtr();
            if (GfManager::isExecModeThater() && skip->isSkip()) {
                time = 1.0f;
            }
        }
        sound->stopBgm(cond.m_handle, time);
    }
    cond.clear();
}

unsigned int BgmTrack::getBgmConditionBgmID(unsigned int id, unsigned int index) const {
    GfBdatBgm* bdat = GfBdatBgm::sys();
    unsigned int count = 0;
    for (unsigned int i = 0; i < 4; i++) {
        unsigned int bgm = bdat->getBgmConditionBgmID(id, i);
        if (bgm == 0) {
            continue;
        }
        if (count == index) {
            return bgm;
        }
        count++;
    }
    return 0;
}

BgmTrack::~BgmTrack() {}
BgmGimmick::~BgmGimmick() {}
const char* BgmGimmick::getTrackName() const { return "GimmickBGM"; }
BgmBattle::~BgmBattle() {}
const char* BgmBattle::getTrackName() const { return "BattleBGM"; }
BgmBattleBoss::~BgmBattleBoss() {}
const char* BgmBattleBoss::getTrackName() const { return "BossBGM"; }
BgmEvent::~BgmEvent() {}
const char* BgmEvent::getTrackName() const { return "EventBGM"; }
const char* BgmField::getTrackName() const { return "FieldBGM"; }


}  // namespace gf
