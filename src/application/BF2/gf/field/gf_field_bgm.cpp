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
#include "classes/gf/GfAllocator.h"

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

GfFieldBgm::GfFieldBgm()
    : m_rscBossBattleBgmID(0), m_bossBattleBgmWait(0), m_rscBattleBgmID(0), m_rscGimmickBgmID(0),
      m_gimmickBgmID(0xFFFFFFFF), m_gimmickBgmClearWait(0), m_disableFieldBgmChange(false), m_deadSequence(false) {
#line 349
    m_tracks.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) BgmField(this));
    m_tracks.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) BgmBattle(this));
    m_tracks.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) BgmBattleBoss(this));
    m_tracks.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) BgmGimmick(this));
    m_tracks.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) BgmEvent(this));
}

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

// the BGM condition ids getBgmFileInfo marks in BgmFileInfo::m_listed (lbl_71009BA7C8; the name is not the original's)
static const unsigned short s_listedBgmCondIDs[] = {
    0x02, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x2D, 0x2E, 0x2F,
    0x30, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D,
};

bool GfFieldBgm::getBgmFileInfo(BgmFileInfo& info, const char* fileName) const {
    mm::mtl::FixStr<64> name = util::getNoPathExtName(fileName);
    GfBdatBgm* bdat = GfBdatBgm::sys();
    unsigned int id = bdat->getBgmConditionStart();
    unsigned int end = bdat->getBgmConditionEnd();
    for (; id < end; ++id) {
        for (unsigned int no = 0; no < 4; ++no) {
            bdat->getBgmConditionCondition(id, no);
            unsigned int bgmID = bdat->getBgmConditionBgmID(id, no);
            if (bgmID != 0 && strcmp(name.m_str, util::getNoPathExtName(bdat->getBgmListfilename(bgmID)).m_str) == 0) {
                info.m_bgmCondID = id;
                info.m_condNo = no;
                bool listed = false;
                for (unsigned long i = 0; i < 41; ++i) {
                    if (s_listedBgmCondIDs[i] == id) {
                        listed = true;
                        break;
                    }
                }
                info.m_listed = listed;
                info.m_bgmID = bgmID;
                return true;
            }
        }
    }
    return false;
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

void BgmTrack::copyPlayParam(BgmTrack* src) {
    stopBGM(0.0f);
    m_bgmCondID = src->m_bgmCondID;
    m_fadeVolume = src->m_fadeVolume;
    m_baseVolume = src->m_baseVolume;
    m_conds = src->m_conds;
    m_copied = true;
    if (!m_conds[0].m_handle.isValid() && m_conds[1].m_handle.isValid()) {
        m_conds[0].m_requested = m_conds[1].m_requested;
        m_conds[0].m_playNo = m_conds[1].m_playNo;
        m_conds[0].m_playing = m_conds[1].m_playing;
        m_conds[0].m_handle = m_conds[1].m_handle;
        m_conds[0].m_bgmFileName = m_conds[1].m_bgmFileName;
        m_conds[0].m_volume = m_conds[1].m_volume;
        m_conds[1].clear();
    }
    if (m_bgmCondID == 0 && m_conds[0].m_bgmFileName.length() != 0) {
        const char* name = m_conds[0].m_bgmFileName.m_str;
        // the condition id of the first BGM condition row with entry 0's BGM file (".wav" added to its name
        // without path and extension) in one of its entries, 0 when none has
        m_bgmCondID = [&]() -> unsigned int {
            GfBdatBgm* bdat = GfBdatBgm::sys();
            if (bdat == nullptr || name[0] == '\0') {
                return 0u;
            }
            mm::mtl::FixStr<64> file = util::getNoPathExtName(name);
            file += ".wav";
            unsigned int bgmID = 0;
            unsigned int i = bdat->getBgmListStart();
            unsigned int end = bdat->getBgmListEnd();
            for (; i < end; ++i) {
                const char* listName = bdat->getBgmListfilename(i);
                if (listName != nullptr && strcmp(file.m_str, listName) == 0) {
                    bgmID = i;
                    break;
                }
            }
            if (bgmID != 0) {
                unsigned int c = bdat->getBgmConditionStart();
                unsigned int condEnd = bdat->getBgmConditionEnd();
                for (; c < condEnd; ++c) {
                    if (bdat->getBgmConditionBgmID(c, 0) == bgmID || bdat->getBgmConditionBgmID(c, 1) == bgmID ||
                        bdat->getBgmConditionBgmID(c, 2) == bgmID || bdat->getBgmConditionBgmID(c, 3) == bgmID) {
                        return c;
                    }
                }
            }
            return 0u;
        }();
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

BgmTrack* GfFieldBgm::getCurrentPlayBgmTrack() {
    BgmTrack* current = nullptr;
    float volume = 0.0f;
    for (BgmTrack*& track : m_tracks) {
        if (track->isPlaying() && !(volume >= track->getVolume())) {
            current = track;
            volume = current->getVolume();
        }
    }
    return current;
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

void BgmEvent::updatePlaying(const fw::UpdateInfo& info) {
    GfEvtBgm* evtBgm = GfEvtBgm::sys();
    if (evtBgm->m_setup.pad_64) {
        m_fadeScale = evtBgm->m_setup.m_volume;
    }
    const char* name = evtBgm->m_setup.m_name.m_str;
    if (evtBgm != nullptr && strcmp(m_conds[0].m_bgmFileName.m_str, name) != 0) {
        float time;
        if (GfManager::isExecModeThater()) {
            if (evtBgm->m_setup.pad_62 && evtBgm->m_setup.pad_61) {
                time = 1.0f;
            } else {
                time = m_setup.pad_62 ? m_setup.pad_4c : 0.5f;
            }
        } else {
            time = m_setup.pad_62 ? m_setup.pad_4c : 0.5f;
        }
        stopBGM(time);
    } else if (!m_playing && evtBgm->isPlayBgm()) {
        evtBgm->setFadeoutVolume();
    }
    if (m_setup.m_overTime > 0.0f && !GfGameManager::isEvent(false)) {
        m_setup.m_overTime -= info.m_deltaTime;
        if (m_setup.m_overTime <= 0.0f) {
            m_setup.m_overTime = 0.0f;
            evtBgm->setFadeoutVolume();
        }
    }
}

void BgmEvent::beginPlay() {
    GfEvtBgm* evtBgm = GfEvtBgm::sys();
    m_volumeFades.clear();
    m_multiplyVolumes.clear();
    addVolumeFade(_gffsn::bgmvolStop, 1.0f, 20.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeLeaveGame, 1.0f, 99.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeDeadSequence, 2.0f, 99.0f, true);
    addVolumeFade(_gffsn::bgmvolFadeDisableEventBgm, evtBgm->m_setup.pad_62 ? evtBgm->m_setup.pad_4c : 0.5f,
                  evtBgm->m_setup.pad_63 ? evtBgm->m_setup.m_volumeTime : 0.5f, true);
    mm::mtl::FixStr<64> name;
    if (evtBgm->m_setup.m_noBgm) {
        BgmTrack* current = GfFieldBgm::sys()->getCurrentPlayBgmTrack();
        if (current != nullptr && current != this) {
            copyPlayParam(current);
            m_setup = evtBgm->m_setup;
            makePlayFileName(name);
            if (name.length() != 0) {
                m_bgmCondID = 0;
                evtBgm->setPlayBgmTakeOver(name.m_str);
            }
        }
    }
    if (name.length() == 0) {
        name = evtBgm->m_setup.m_name;
    }
    if (evtBgm->m_setup.pad_64) {
        m_fadeScale = evtBgm->m_setup.m_volume;
    }
    m_playTime = evtBgm->m_setup.pad_50;
    if (name.length() != 0) {
        if (strcmp(m_playBgmName.m_str, name.m_str) == 0) {
            return;
        }
        if (m_setup.m_overTime < 0.0f) {
            evtBgm->setFadeoutVolume();
            return;
        }
        m_playBgmName = name.m_str;
    }
    if (!GfGameManager::isFullScreenMenu() || GfManager::isExecModeThater()) {
        m_category = 10;
    } else {
        m_category = 3;
    }
    m_conds[0].m_bgmFileName = name;
    m_setup = evtBgm->m_setup;
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

void BgmEvent::checkStopByHandOver() {
    if (!GfEvtBgm::sys()->m_setup.pad_61) {
        return;
    }
    if (!BgmTrack::isPlaying()) {
        return;
    }
    if (GfManager::isExecModeThater()) {
        return;
    }
    BgmFileInfo info;
    GfFieldBgm* fieldBgm = GfFieldBgm::sys();
    if (fieldBgm != nullptr && fieldBgm->getBgmFileInfo(info, m_conds[0].m_bgmFileName.m_str) && info.m_listed) {
        int mapID = GfGameManager::getMapID();
        unsigned int condID = mapID != 0 ? GfBdatMaplist::sys()->getMaplistbgm_cndID(mapID) : 0;
        if (condID == info.m_bgmCondID) {
            if (BgmField* field = BgmField::sys()) {
                field->copyPlayParam(this, info);
                field->setCategoryApply(1);
                return;
            }
        }
        if (m_fieldBgm->getRscGimmickBgmID() == info.m_bgmCondID) {
            if (BgmGimmick* gimmick = BgmGimmick::sys()) {
                gimmick->copyPlayParam(this, info);
                gimmick->setCategoryApply(1);
                return;
            }
        }
    }
    if (BgmBattleBoss* boss = BgmBattleBoss::sys()) {
        const char* silent = strstr(m_conds[0].m_bgmFileName.m_str, "Silent");
        boss->copyPlayParam(this);
        boss->setCategoryApply(1);
        if (silent != nullptr) {
            boss->stopBGM(0.0f);
        }
        GfGameScene* scene = GfGameScene::sys();
        if (silent == nullptr && scene != nullptr) {
            scene->setForceBossBattleBgm(true);
        }
    }
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

void BgmEvent::updateEventBgm(const fw::UpdateInfo& info) {
    GfEvtBgm* evtBgm = GfEvtBgm::sys();
    if (evtBgm == nullptr) {
        return;
    }
    checkStopByHandOver();
    if (isPlaying()) {
        updatePlaying(info);
        return;
    }
    if (m_overTimeStop) {
        m_overTimeStop = false;
        if (GfGameScene* scene = GfGameScene::sys()) {
            switch (scene->pad_8BC) {
            case 30177:
            case 30180:
            case 30184:
            case 30186:
            case 30188:
            case 30190:
            case 30191:
            case 30193:
            case 30248:
                evtBgm->cancelOverTime();
                evtBgm->stopBgm(EventBgmSetup());
                stopBGM(0.0f);
                break;
            }
        }
    }
    if (evtBgm->isEnableEventBgm() || evtBgm->m_setup.m_noBgm) {
        beginPlay();
    }
}

bool BgmEvent::isPlaying() const {
    return BgmTrack::isPlaying();
}

void BgmEvent::cancelOverTime() {
    m_setup.m_overTime = 0.0f;
}

void BgmEvent::setBgmClearByStopBgm() {
    if (GfGameManager::isGameTypeIra() && m_setup.m_overTime < 0.0f) {
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
