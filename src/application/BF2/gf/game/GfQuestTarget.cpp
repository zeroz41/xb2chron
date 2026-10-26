#include "classes/gf/GfQuestTarget.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/GfDataQuest.h"
#include "gf/QuestChangeParam.h"
#include "gf/QuestCompleteChildParam.h"
#include "gf/QuestOrderParam.h"
#include "gf/QuestStateParam.h"
#include "gf/QuestTaskParam.h"

namespace gf {


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

}  // namespace gf
