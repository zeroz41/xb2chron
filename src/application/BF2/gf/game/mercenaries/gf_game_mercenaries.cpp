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

namespace gf {

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
    if (GfGameManager::fn_71002A9E68()) {
        return;
    }
    get()->updateMercenariesTeam(info);
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

void GfGameMercenaries::qevOrderQuest(const QuestOrderParam& param) {
    if (GfGameManager::fn_71002A9E68()) {
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
