#include "classes/gf/GfQuestTarget.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfDataQuest.h"
#include "gf/QuestChangeParam.h"
#include "gf/QuestCompleteChildParam.h"
#include "gf/QuestOrderParam.h"
#include "gf/QuestStateParam.h"
#include "gf/QuestTaskParam.h"

namespace gf {

// Placeholder name: 1.0.0's copy (0x7100371C58) is unnamed as well, a file-local function. What it does: the icon
// type of a talk target: walks the quest's task list (fn_710030A840), and for talk tasks (6) compares
// QuestListAcc's getTalkMapID/getTalkNpcID with the info's map and id, for condition tasks (10) getConditionMapID/
// getConditionNpcID, collect tasks (3) go to fn_710030AB00; it reads GfQuestInfo::getState/isParent and
// GfQuestUtil::getDummyTalkGroup.
static unsigned int fn_710030B16C(TargetInfo* info);

GfQuestTarget::GfQuestTarget() {
    GfQuestManager::addEvent(this);
}

GfQuestTarget::~GfQuestTarget() {
    GfQuestManager::removeEvent(this);
}

void GfQuestTarget::update(const fw::UpdateInfo& info) {
    typedef ::mm::mtl::FixedList<TargetCache, 512>::iterator iterator;
    for (iterator it = m_targetCache.begin(); it != m_targetCache.end(); ++it) {
        if (!(*it).m_destroy) {
            if (++(*it).m_frames > 300) {
                (*it).m_destroy = true;
            }
        }
    }
    for (iterator it = m_targetCache.begin(); it != m_targetCache.end(); ++it) {
        if (it->m_destroy) {
            m_targetCache.erase(it);
            return;
        }
    }
}

void GfQuestTarget::gevMapjump(GEV gev, const MapjumpCallbackInfo& info) {
    if (gev == GEV(4)) {
        m_targetCache.clear();
    }
}

void GfQuestTarget::destroyTargetQuest(QuestID questId) {
    typedef ::mm::mtl::FixedList<TargetCache, 512>::iterator iterator;
    for (iterator it = m_targetCache.begin(); it != m_targetCache.end(); ++it) {
        if ((*it).m_questId == questId) {
            (*it).m_destroy = true;
        }
    }
}

void GfQuestTarget::qevChangeTaskState(const QuestTaskParam& param) {
    destroyTargetQuest(param.m_questId);
}

void GfQuestTarget::qevChangeQuestState(const QuestStateParam& param) {
    destroyTargetQuest(param.m_questId);
}

void GfQuestTarget::qevOrderQuest(const QuestOrderParam& param) {
    destroyTargetQuest(GfDataQuest::getListNextQuestA(param.m_questId));
}

void GfQuestTarget::qevCompleteChildQuest(const QuestCompleteChildParam& param) {
    destroyTargetQuest(param.m_questId);
    QuestID current = GfQuestManager::getProgressCurrentQuest(QTYPE(0));
    if (!(current == param.m_questId)) {
        destroyTargetQuest(current);
    }
}

void GfQuestTarget::qevChangeCurrentQuest(const QuestChangeParam& param) {
    destroyTargetQuest(param.m_questId2);
    destroyTargetQuest(param.m_questId);
}

void GfQuestTarget::qevChangeTaskCondition(const QuestTaskParam& param) {
    destroyTargetQuest(param.m_questId);
}

unsigned int GfQuestTarget::getIconTypeTalk(unsigned int npcId, QuestID questId, unsigned int mapId, bool flag) {
    TargetInfo info;
    // no map means the current one
    if (mapId == 0) {
        mapId = GfGameManager::getMapID();
    }
    info.setupForTalk(questId, npcId, reinterpret_cast<GF_OBJ_HANDLE*>(-1), mapId, flag);
    return fn_710030B16C(&info);
}

unsigned int GfQuestTarget::getIconTypeTalk(GF_OBJ_HANDLE* handle, QuestID questId, unsigned int mapId, bool flag) {
    DataParamAcc acc(handle);
    TargetInfo info;
    unsigned int npcId = acc.isValid() ? acc.getBdatId() : 0;
    if (mapId == 0) {
        mapId = GfGameManager::getMapID();
    }
    info.setupForTalk(questId, npcId, handle, mapId, flag);
    return fn_710030B16C(&info);
}

}  // namespace gf
