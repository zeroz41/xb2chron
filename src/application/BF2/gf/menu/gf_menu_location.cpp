#include "classes/gf/GfMenuLocation.h"
#include "algorithm"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfMenuObjCompass.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/GfWeapon.h"
#include "fw/Transform.h"
#include "gf/GfDataQuest.h"
#include "gf/GfGameUtil.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfObjAcc.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfQuestTask.h"
#include "gf/QuestTaskParam.h"

namespace gf {

namespace {
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BCCCC). build reserves each list's
// locators so
const unsigned int s_reserveNum[5] = {4, 4, 1, 16, 0};
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009BCE44). updateLocator gives
// GfMenuObjCompass at most so many of each list's positions
const unsigned int s_addMax[5] = {5, 5, 1, 2, 1};
}  // namespace

GfMenuLocation::~GfMenuLocation() {}

void GfMenuLocation::build(const GfSetupParam& param) {
#line 76
    GfMenuLocation* self = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuLocation(param);
    for (long i = 0; i < 5; i++) {
        LocatorList& list = self->m_lists[i];
        list.m_dataNum = 0;
        list.m_locators.setAllocator(getAllocator(ALLOCATOR(0)));
        list.m_locators.reserve(s_reserveNum[i]);
        list.m_addedNum = 0;
    }
    self->m_initialized = true;
    self->pad_1560 = 0;
}

void GfMenuLocation::destroy() {
    GfMenuLocation* self = get();
    for (long i = 0; i < 5; i++) {
        if (self->m_lists[i].m_locators.capacity() != 0) {
            self->m_lists[i].m_locators.destroy();
        }
    }
    delete self;
}

bool GfMenuLocation::isInitialized() {
    if (get() != nullptr) {
        return get()->m_initialized;
    }
    return false;
}

void GfMenuLocation::updateLocator() {
    GfMenuLocation* self = get();
    if (self == nullptr) {
        return;
    }
    if (GfMenuObjUtil::fn_710048FD30(3)) {
        self->m_locator.fn_710027011C();
    }
    for (unsigned long kind = 0; kind < 5; kind++) {
        for (unsigned long i = 0; i < self->m_lists[kind].m_locators.size(); i++) {
            self->m_lists[kind].m_locators[i].update();
        }
        self->updateDataNum(kind);
        LocatorList& list = self->m_lists[kind];
        if (list.m_addedNum < list.m_dataNum) {
            int num = list.m_dataNum - list.m_addedNum;
            int i;
            for (i = 0; i < num && list.m_addedNum + i + 1 <= s_addMax[kind]; i++) {
                GfMenuObjCompass::LocatorParam param;
                param.m_id = kind;
                param.m_type = list.m_addedNum + i;
                param.m_count = kind == 3 ? 50 : 0;
                GfMenuObjCompass::addLocator(param);
            }
            list.m_addedNum += i;
        }
    }
}

void GfMenuLocation::refreshLocatorFromQuest(unsigned int kind, unsigned int type) {
    QuestID current = GfMenuObjUtil::getCurrentQuest(type);
    mm::mtl::FixedVector<QuestID, 16> quests;
    GfQuestManager::getLinkQuest(quests, current);
    for (QuestID* it = quests.begin(), *end = quests.end(); it != end; ++it) {
        if (GfMenuObjUtil::isQuestCompleted(*it)) {
            continue;
        }
        unsigned int purposeId = GfDataQuest::getListPurposeID(*it);
        for (unsigned int task = 0; task < 4; task++) {
            QuestTaskParam param(*it, task, purposeId, TASK_STATE(0));
            if (param.m_taskType == 0) {
                break;
            }
            if (!GfQuestInfo::isCompleteTask(param) && GfQuestTask::isEnableTaskCondition(param) &&
                !fn_71002EE5E0(*it, task)) {
                GfFieldLocator::CreateInfoByQuest createInfo;
                createInfo.m_questId = *it;
                createInfo.m_id = param.m_taskId;
                createInfo.m_type = param.m_taskType;
                GfFieldLocator locator(&createInfo);
                m_lists[kind].m_locators.push_back(locator);
            }
        }
    }
}

void GfMenuLocation::fn_7100356980(unsigned int value) {
    if (get() != nullptr) {
        get()->m_requestId = value;
    }
}

}  // namespace gf
