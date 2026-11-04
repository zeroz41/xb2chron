#include "gf/GfDataMercenaries.h"
#include "gf/QuestOrderParam.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/SCOM_POPUP.h"
#include "classes/gf/GfGameMercenaries.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfDataQuest.h"
#include "gf/QuestListAcc.h"
#include "gf/QuestCompleteParam.h"
#include "gf/QuestOrderParam.h"
#include "fw/UpdateInfo.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfGameCond.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/SCOM_POPUP.h"
#include "classes/gf/SCOM_SET_MERCENARIES_LEVEL.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/GfQuestReward.h"
#include "gf/GfQuestUtil.h"
#include "gf/GfKizunaringUtil.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "classes/gf/GfBdatBlade.h"
#include "classes/gf/GfBdatChrDr.h"
#include "ml/MtRand.h"

namespace gf {

bool GfKizunaringUtil::getCompleteKizunaringReward(GfQuestReward& reward, unsigned int blade) {
    // the first create config row of each crown point count (proposed name, not the original's: the symbols leave
    // it unnamed, lbl_71009BC0FC)
    static const unsigned short s_crownConfigRow[] = {0, 0x31, 0x35, 0x39, 0x3D, 0x41};
    unsigned int id;
    if (GfDataBlade::isIra(blade)) {
        GfBdatChrDr* chrDr = GfBdatChrDr::get();
        unsigned int driver = GfDataBlade::getIraDriver(blade);
        if (driver == 0) {
            return false;
        }
        id = chrDr->getChrIrKizunaReward1(chrDr->getChrDrIraParam(driver));
    } else {
        unsigned int row = s_crownConfigRow[GfDataBlade::getCrownPoint(blade)] + ml::mtRand(4);
        id = GfBdatBlade::get()->getCreateConfigValue(row);
    }
    if (id == 0) {
        return false;
    }
    if (!GfQuestUtil::getReward(reward, id, false)) {
        return false;
    }
    reward.m_trustBlade = blade;
    return true;
}

bool GfKizunaringUtil::getCompleteKizunaringRewardForDriver(GfQuestReward& reward, unsigned int driver, bool second) {
    if (GfDataDriver::isIra(driver)) {
        GfBdatChrDr* chrDr = GfBdatChrDr::get();
        unsigned int row = chrDr->getChrDrIraParam(driver);
        unsigned int id = second ? chrDr->getChrIrKizunaReward2(row) : chrDr->getChrIrKizunaReward1(row);
        if (id != 0 && GfQuestUtil::getReward(reward, id, false)) {
            return true;
        }
    }
    return GfQuestUtil::getReward(reward, 0x3A3, false);
}

GfGameMercenaries::~GfGameMercenaries() {}

void GfGameMercenaries::build(const GfSetupParam& param) {
#line 81
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfGameMercenaries(param);
}

void GfGameMercenaries::destroy() {
    GfGameMercenaries* manager = get();
    manager->finalize();
    delete manager;
}

void GfGameMercenaries::rebuildAutoStartList() {
    m_autoStartList.clear();
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int start = acc->getFLD_MercenariesMissionStart();
    unsigned int end = acc->getFLD_MercenariesMissionEnd();
    for (unsigned int mission = start; mission < end; mission++) {
        if (acc->getFLD_MercenariesMissionAutoStart(mission)) {
            m_autoStartList.push_back(mission);
        }
    }
}

void GfGameMercenaries::update(const fw::UpdateInfo& info) {
    if (GfGameManager::isGameTypeIra()) {
        return;
    }
    get()->updateMercenariesTeam(info);
}

void GfGameMercenaries::updateMercenariesTeam(const fw::UpdateInfo& info) {
    unsigned int num = GfDataMercenaries::getTeamNum();
    unsigned int max = GfDataMercenaries::getTeamMax();
    if (num < max) {
        for (unsigned int i = 0; i < max - num; i++) {
            GfDataMercenaries::addTeam();
        }
    }
    if (!GfGameManager::isStartGame() && !m_stopMissionTime) {
        mm::mtl::FixedVector<unsigned short, 3> teams;
        getTeam(teams);
        for (unsigned short team : teams) {
            GfDataMercenaries::decTeamMissionTime(team, info.m_frameTime);
        }
    }
    checkTeamMissionComplete();
}

int GfGameMercenaries::getMissionFlag(unsigned int mission) {
    return GfDataMercenaries::getMissionFlag(mission);
}

void GfGameMercenaries::setMissionComplete(unsigned int mission) {
    // read and not used: the original's call stays
    int flag = getMissionFlag(mission);
    setMissionFlag(mission, 3);
    if (GfDataMercenaries::getMissionTaskType(mission) == 2) {
        setMissionFlag(mission, 4);
    }
}

void GfGameMercenaries::setMissionFlag(unsigned int mission, unsigned int flag) {
    unsigned int old = GfDataMercenaries::getMissionFlag(mission);
    GfDataMercenaries::setMissionFlag(mission, flag);
    if (flag == 1 && old == 0) {
        unsigned char* bdat;
        unsigned int id;
        GfDataQuest::getTitle(bdat, id, GfDataMercenaries::getMissionQuestID(mission));
    } else if (flag == 4 && !GfDataMercenaries::isMissionCompleteFlag(mission)) {
        GfDataMercenaries::setMissionCompleteFlag(mission);
    }
    GfEvent::callMercenariesMissionFlag(mission, flag, old);
}

void GfGameMercenaries::addPoint(unsigned int point) {
    if (GfDataMercenaries::getLevel() == 0 || static_cast<unsigned int>(GfDataMercenaries::getLevel()) > 4) {
        return;
    }
    unsigned int current = GfDataMercenaries::getPoint();
    unsigned int total = current + point;
    unsigned int limit = GfDataMercenaries::getPointLimit();
    if (total > limit) {
        total = limit;
    }
    if (total != current) {
        GfDataMercenaries::setPoint(total);
    }
}

void GfGameMercenaries::setLevel(unsigned int level) {
    // read and not used: the original's call stays
    int current = GfDataMercenaries::getLevel();
    if (level > GfDataMercenaries::getLevelMax()) {
        level = GfDataMercenaries::getLevelMax();
    }
    GfDataMercenaries::setLevel(level);
}

bool GfGameMercenaries::getZoneMission(mm::mtl::FixedVector<unsigned short, 500>& missions, unsigned int zone) {
    if (zone == 0) {
        return false;
    }
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int start = acc->getFLD_MercenariesMissionStart();
    unsigned int end = acc->getFLD_MercenariesMissionEnd();
    for (unsigned int mission = start; mission < end; mission++) {
        if (GfDataMercenaries::getMissionFlag(mission) != 0 && GfDataMercenaries::getMissionZoneID(mission) == zone) {
            missions.push_back(mission);
        }
    }
    return !missions.empty();
}

void GfGameMercenaries::cancelMission(unsigned int mission) {
    if (mission == 0) {
        return;
    }
    unsigned int flag = GfDataMercenaries::getMissionFlag(mission);
    if (flag == 0) {
        return;
    }
    QuestID quest = GfDataMercenaries::getMissionQuestID(mission);
    GfDataMercenaries::Team* team = GfDataMercenaries::getTeamByMissionID(mission);
    unsigned int current = GfDataMercenaries::getMissionFlag(mission);
    if (team != nullptr && current == 3) {
        SCOM_POPUP::cancelMercenaryReturn(GfDataMercenaries::getMissionMapID(mission), team->m_teamId);
    }
    if (team != nullptr) {
        team->m_quest = QuestID();
        team->m_mission = 0;
        team->m_secondCount = 0.0f;
        team->m_missionTime = ElapseTime();
        team->m_missionTimeTotal = ElapseTime();
    }
    bool enable = GfDataMercenaries::isEnableOrder(mission);
    if (enable) {
        setMissionFlag(mission, 1);
    } else if (flag != 4) {
        setMissionFlag(mission, 1);
    }
}

void GfGameMercenaries::qevOrderQuest(const QuestOrderParam& param) {
    if (GfGameManager::isGameTypeIra()) {
        return;
    }
    unsigned int mission = GfDataMercenaries::getMissionByQuestID(param.m_questId);
    if (mission != 0 && GfDataMercenaries::getMissionFlag(mission) == 1) {
        setMissionFlag(mission, 2);
    }
}

void GfGameMercenaries::applyDestroyMission() {
    QuestListAcc* acc = QuestListAcc::get();
    unsigned int start = GfDataMercenaries::getStartMissionID();
    unsigned int end = GfDataMercenaries::getEndMissionID();
    for (unsigned int mission = start; mission < end; mission++) {
        if (GfDataMercenaries::getMissionFlag(mission) == 1) {
            if (unsigned int cond = acc->getListCancelCondition(GfDataMercenaries::getMissionQuestID(mission))) {
                if (GfGameCond::isGameCond(cond)) {
                    setMissionFlag(mission, 0);
                }
            }
        }
    }
}

void GfGameMercenaries::gevMercenariesMissionFlag(unsigned int mission, unsigned int flag, unsigned int old) {
    if (flag == 1 && old == 0 && GfDataMercenaries::isNewMission(mission)) {
        SCOM_POPUP::createMercenaryAdd(mission);
    }
}

bool GfGameMercenaries::isQuestMission(QuestID quest) {
    for (unsigned int mission = GfDataMercenaries::getStartMissionID(); mission < GfDataMercenaries::getEndMissionID();
         mission++) {
        if (quest == GfDataMercenaries::getMissionQuestID(mission)) {
            return GfDataMercenaries::getMissionFlag(mission) != 0;
        }
    }
    return false;
}

int GfGameMercenaries::getRewardGold(unsigned int mission, bool) {
    GfQuestReward reward;
    unsigned int gold = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)
                            ? reward.m_items[0].m_value
                            : 0;
    return gold + getRewardGoldHosei(mission, false);
}

int GfGameMercenaries::getRewardExp(unsigned int mission, bool) {
    GfQuestReward reward;
    unsigned int exp = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)
                           ? reward.m_items[3].m_value
                           : 0;
    float base = exp;
    unsigned int level = GfDataMercenaries::getLevel();
    float rate = level != 0 ? QuestListAcc::get()->getFLD_MercenariesConfigValue(level + 10) : 0.0f;
    return static_cast<unsigned int>(base * rate * 0.01f) + exp;
}

int GfGameMercenaries::getRewardDevelop(unsigned int mission, bool) {
    GfQuestReward reward;
    unsigned int develop = GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)
                               ? reward.m_items[4].m_value & 0xFFFF
                               : 0;
    return develop + getRewardDevelopHosei(mission, false);
}

int GfGameMercenaries::getRewardTrust(unsigned int mission) {
    GfQuestReward reward;
    return GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)
               ? reward.m_items[5].m_value & 0xFFFF
               : 0;
}

int GfGameMercenaries::getRewardMercenariesPoint(unsigned int mission) {
    GfQuestReward reward;
    if (!GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)) {
        return 0;
    }
    return reward.m_items[7].m_value & 0xFFFF;
}

void GfGameMercenaries::execMissionRewardByTeamID(unsigned int teamId) {
    execMissionReward(GfDataMercenaries::getTeamMission(teamId));
    GfQuestManager::requestOrderAchievementQuestForce();
}

void GfGameMercenaries::setMissionCompleteForce(unsigned int mission) {
    if (GfDataMercenaries::Team* team = GfDataMercenaries::getTeamByMissionID(mission)) {
        team->m_missionTime = ElapseTime();
        team->m_missionTimeTotal = ElapseTime();
        team->m_missionEnd = true;
    }
}

int GfGameMercenaries::getRewardGoldHosei(unsigned int mission, bool) {
    GfQuestReward reward;
    float gold = 0.0f;
    if (GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)) {
        gold = reward.m_items[0].m_value;
    }
    float rate = 0.0f;
    if (unsigned int level = GfDataMercenaries::getLevel()) {
        rate = QuestListAcc::get()->getFLD_MercenariesConfigValue(level + 10);
    }
    return static_cast<unsigned int>(gold * rate * 0.01f);
}

int GfGameMercenaries::getRewardDevelopHosei(unsigned int mission, bool) {
    GfQuestReward reward;
    float develop = 0.0f;
    if (GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)) {
        develop = static_cast<unsigned short>(reward.m_items[4].m_value);
    }
    float rate = 0.0f;
    if (unsigned int level = GfDataMercenaries::getLevel()) {
        rate = QuestListAcc::get()->getFLD_MercenariesConfigValue(level + 10);
    }
    return static_cast<unsigned int>(develop * rate * 0.01f);
}

bool GfGameMercenaries::getRewardItem(unsigned int& item, unsigned int& count, unsigned int mission,
                                      QUEST_REWARD slot) {
    GfQuestReward reward;
    if (!GfQuestUtil::getReward(reward, GfDataMercenaries::getMissionRewardID(mission), false)) {
        return false;
    }
    unsigned int value = reward.m_items[slot].m_value;
    item = value & 0xFFFF;
    count = value >> 16;
    return item != 0;
}

void GfGameMercenaries::setupNewGameParam() {
    if (GfGameManager::isGameTypeIra()) {
        return;
    }
    unsigned int start = GfDataMercenaries::getStartMissionID();
    unsigned int end = GfDataMercenaries::getEndMissionID();
    for (unsigned int mission = start; mission < end; mission++) {
        setMissionFlag(mission, 0);
    }
}

void GfGameMercenaries::stopMissionTime(bool stop) {
    if (GfGameMercenaries* self = get()) {
        self->m_stopMissionTime = stop;
    }
}

void GfGameMercenaries::gevMapjump(GEV gev, const MapjumpCallbackInfo&) {
    if (gev == 7) {
        if (GfGameMercenaries* self = get()) {
            self->m_stopMissionTime = false;
        }
    }
}

}  // namespace gf
