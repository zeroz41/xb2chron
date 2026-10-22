#include "classes/gf/GfQuestEvent.h"
#include "classes/gf/GfQuestManager.h"
#include "gf/GfDataQuest.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfQuestTask.h"
#include "gf/GfPlayFactory.h"
#include "gf/QuestTaskParam.h"

namespace gf {

GfQuestEvent::GfQuestEvent() : m_dispEntry(false), m_dispResult(false) {}

GfQuestEvent::~GfQuestEvent() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

bool GfQuestEvent::setQuestEntry(unsigned int id) {
    GfQuestEvent* event = get();
    if (event == nullptr) {
        return false;
    }
    if (GfQuestManager::openOrder(id, true)) {
        event->m_dispEntry = GfDataQuest::getListVisible(id);
    }
    return true;
}

int GfQuestEvent::getQuestState(unsigned int id) {
    return GfQuestInfo::getState(id);
}

void GfQuestEvent::setQuestComp(unsigned int id, unsigned int task) {
    QuestTaskParam param(id, task, TASK_STATE(0));
    GfQuestTask::completeTask(param);
}

bool GfQuestEvent::getQuestComp(unsigned int id, unsigned int task) {
    QuestTaskParam param(id, task, TASK_STATE(0));
    return GfQuestInfo::isCompleteTask(param);
}

bool GfQuestEvent::isActive() {
    GfQuestEvent* event = get();
    if (event == nullptr) {
        return false;
    }
    return event->m_dispEntry || event->m_dispResult;
}

void GfQuestEvent::openEntry(unsigned int id) {
    GfQuestEvent* event = get();
    if (event != nullptr) {
        event->m_dispEntry = GfPlayFactory::createQuestUIOrder(id, true, false);
    }
}

void GfQuestEvent::openResult(unsigned int id) {
    GfQuestEvent* event = get();
    if (event != nullptr) {
        event->m_dispResult = GfPlayFactory::createQuestUIComplete(id);
    }
}

void GfQuestEvent::clearDispUI() {
    GfQuestEvent* event = get();
    if (event != nullptr) {
        event->m_dispEntry = false;
        event->m_dispResult = false;
    }
}

}  // namespace gf
