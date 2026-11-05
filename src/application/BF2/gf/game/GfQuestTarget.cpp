#include "classes/gf/GfQuestTarget.h"
#include "classes/gf/GfQuestManager.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfDataQuest.h"
#include "gf/QuestChangeParam.h"
#include "gf/QuestCompleteChildParam.h"
#include "gf/QuestOrderParam.h"
#include "gf/QuestStateParam.h"
#include "gf/QuestTaskParam.h"
#include "gf/QuestListAcc.h"
#include "gf/GfQuestTask.h"
#include "gf/GfQuestInfo.h"
#include "classes/gf/GfWeapon.h"
#include "mm/mtl/FixedVector.h"
#include "gf/GfQuestUtil.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjInfo.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetupNpc.h"

namespace gf {

// Placeholder name: 1.0.0's copy (0x7100371C58) is unnamed as well, a file-local function. What it does: the icon
// type of a talk target: walks the quest's task list (fn_710030A840), and for talk tasks (6) compares
// QuestListAcc's getTalkMapID/getTalkNpcID with the info's map and id, for condition tasks (10) getConditionMapID/
// getConditionNpcID, collect tasks (3) go to fn_710030AB00; it reads GfQuestInfo::getState/isParent and
// GfQuestUtil::getDummyTalkGroup.
static unsigned int fn_710030B16C(TargetInfo* info);

// Placeholder name: 1.0.0's copy (0x71003714B0) is unnamed as well. What it does: collects the quest's open tasks
// (enabled, not complete) of the kinds the info's type looks for; true when it found any.
static bool fn_710030A840(::mm::mtl::FixedVector<QuestTaskParam, 4>& tasks, const TargetInfo* info);
// Placeholder name: 1.0.0's copy (0x7100371714) is unnamed as well. The icon type of a collect task.
static unsigned int fn_710030AB00(unsigned int taskId, const TargetInfo* info);
// Placeholder name: 1.0.0's copy (0x710037299C) is unnamed as well. The icon type of a matching target: 1 for a
// main-story quest, 3 for the current quest (or one linked to it), else 0.
static unsigned int fn_710030C150(const TargetInfo* info);

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

// the icon type of a reach task (task id) for the info's reach target: its map, category and place must match
// (inline: the analog of the collect tasks' fn_710030AB00; the name is not the original's)
static inline unsigned int getIconTypeReachTask(unsigned int taskId, const TargetInfo* info) {
    if (info->m_reachCategory != 0) {
        QuestListAcc* acc = QuestListAcc::get();
        if (acc->getReachMapID(taskId) == info->m_mapId) {
            unsigned int reachCategory = acc->getReachCategory(taskId);
            unsigned int reachPlace = acc->getReachPlaceID(taskId);
            if (reachCategory == 1) {
                if (info->m_reachCategory == 1 && reachPlace == info->m_id) {
                    return fn_710030C150(info);
                }
            } else if (reachCategory == 2) {
                if (info->m_reachCategory == 2 && reachPlace == info->m_id) {
                    return fn_710030C150(info);
                }
            } else if (reachCategory == 3) {
                if (info->m_reachCategory == 3 && reachPlace == info->m_id) {
                    return fn_710030C150(info);
                }
            }
        }
    }
    return 0;
}

unsigned int GfQuestTarget::getIconTypeReachPlace(unsigned int category, unsigned int placeId, QuestID questId,
                                                  unsigned int mapId, bool flag) {
    TargetInfo info;
    if (mapId == 0) {
        mapId = GfGameManager::getMapID();
    }
    info.setupForReach(questId, category, placeId, mapId, flag);
    ::mm::mtl::FixedVector<QuestTaskParam, 4> tasks;
    if (fn_710030A840(tasks, &info)) {
        typedef ::mm::mtl::FixedVector<QuestTaskParam, 4>::iterator iterator;
        for (iterator it = tasks.begin(), end = tasks.end(); it != end; ++it) {
            unsigned int type = getIconTypeReachTask(it->m_taskId, &info);
            if (type != 0) {
                return type;
            }
        }
    }
    return 0;
}

static bool fn_710030A840(::mm::mtl::FixedVector<QuestTaskParam, 4>& tasks, const TargetInfo* info) {
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int i = 0; i < 4; ++i) {
        QuestTaskParam param(info->m_questId, i, TASK_STATE(0));
        if (param.m_taskType == 1) {
            if (acc->getBattleTargetOff(param.m_taskId)) {
                continue;
            }
        } else if (param.m_taskType == 0) {
            break;
        }
        if (!GfQuestTask::isEnableTaskCondition(param) || GfQuestInfo::isCompleteTask(param)) {
            continue;
        }
        if (fn_71002EE5E0(info->m_questId, i)) {
            continue;
        }
        switch (info->m_type) {
        case 1:
            if (param.m_taskType == 3) {
                tasks.push_back(param);
            }
            break;
        case 2:
            if (param.m_taskType == 5) {
                tasks.push_back(param);
            }
            break;
        case 3:
            if (param.m_taskType == 1 || param.m_taskType == 3 ||
                (GfGameManager::isGameTypeIra() && param.m_taskType == 8)) {
                tasks.push_back(param);
            }
            break;
        case 4:
            if (param.m_taskType == 2 || param.m_taskType == 3 || param.m_taskType == 6 || param.m_taskType == 10) {
                tasks.push_back(param);
            }
            break;
        case 5:
            if (param.m_taskType == 8 || param.m_taskType == 3) {
                tasks.push_back(param);
            }
            break;
        }
    }
    return tasks.size() != 0;
}

unsigned int GfQuestTarget::getIconTypeCollect(unsigned int kind, unsigned int id, QuestID questId, unsigned int mapId,
                                               bool flag) {
    TargetInfo info;
    if (mapId == 0) {
        mapId = GfGameManager::getMapID();
    }
    info.setupForCollect(questId, TargetInfo::COLLECT_CATEGORY(kind), id, mapId, flag);
    ::mm::mtl::FixedVector<QuestTaskParam, 4> tasks;
    if (fn_710030A840(tasks, &info)) {
        typedef ::mm::mtl::FixedVector<QuestTaskParam, 4>::iterator iterator;
        for (iterator it = tasks.begin(), end = tasks.end(); it != end; ++it) {
            unsigned int type = fn_710030AB00(it->m_taskId, &info);
            if (type != 0) {
                return type;
            }
        }
    }
    return 0;
}

static unsigned int fn_710030AB00(unsigned int taskId, const TargetInfo* info) {
    QuestListAcc* acc = QuestListAcc::get();
    if (unsigned int boxId = acc->getCollectTresureID(taskId)) {
        if (info->m_category == 1 && info->m_id == boxId) {
            return fn_710030C150(info);
        }
    } else if (unsigned int enemyId = acc->getCollectEnemyID(taskId)) {
        if (info->m_category == 3 && info->m_id == enemyId) {
            return fn_710030C150(info);
        }
    } else if (unsigned int npcId = acc->getCollectNpcID(taskId)) {
        if (acc->getCollectMapID(taskId) == info->m_mapId && npcId == info->m_id) {
            return fn_710030C150(info);
        }
    } else if (unsigned int collectionId = acc->getCollectCollectionID(taskId)) {
        if (acc->getCollectMapID(taskId) == info->m_mapId && info->m_category == 4 && collectionId == info->m_id) {
            return fn_710030C150(info);
        }
    } else if (unsigned int itemId = acc->getCollectItemID(taskId)) {
        if (info->m_category != 3 && itemId == info->m_id) {
            return fn_710030C150(info);
        }
    }
    return 0;
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

static unsigned int fn_710030B16C(TargetInfo* info) {
    // the icon types of a talk task and of a condition task: inline helpers in the original (their QuestID
    // arguments carry no loop state, and the loop steps as after a call); unnamed here
    auto talkIconType = [info](unsigned int taskId) -> unsigned int {
        QuestListAcc* acc = QuestListAcc::get();
        if (acc->getTalkMapID(taskId) == info->m_mapId && acc->getTalkNpcID(taskId) == info->m_id) {
            int state = GfQuestInfo::getState(info->m_questId);
            if (state != 1) {
                if (state != 0) {
                    return 0;
                }
                if (GfQuestInfo::isParent(info->m_questId)) {
                    return 2;
                }
            }
        } else {
            unsigned int group;
            unsigned int bit;
            if (!GfQuestUtil::getDummyTalkGroup(group, bit, info->m_mapId, info->m_id, info->m_questId) ||
                GfQuestInfo::isDummuTalkGroupFlag(group, bit) || GfQuestInfo::getState(info->m_questId) != 1) {
                return 0;
            }
        }
        return fn_710030C150(info);
    };
    auto conditionIconType = [info](unsigned int taskId) -> unsigned int {
        QuestListAcc* acc = QuestListAcc::get();
        unsigned int mapId = acc->getConditionMapID(taskId);
        if (mapId != 0 && mapId != info->m_mapId) {
            return 0;
        }
        if (GfObjUtil::getObjType(info->m_handle) == 6 || info->m_type == 4) {
            unsigned int npcId = acc->getConditionNpcID(taskId);
            if (npcId == 0 || npcId != info->m_id) {
                return 0;
            }
        }
        if (info->m_handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            GFOBJ_INFO* obj = GfObjManager::getObjInfo(info->m_handle);
            if (obj != nullptr && obj->m_setup != nullptr) {
                GfObjSetup* setup = obj->m_setup;
                if (setup->m_type == static_cast<int>(obj->m_obj->m_type) &&
                    static_cast<int>(obj->m_obj->m_type) == 6 &&
                    setup->getRTTI()->isKindOf(&GfObjSetupNpc::m_rtti)) {
                    if (isEventCreateType(setup->m_createType)) {
                        return 0;
                    }
                }
            }
        }
        return fn_710030C150(info);
    };
    ::mm::mtl::FixedVector<QuestTaskParam, 4> tasks;
    if (fn_710030A840(tasks, info)) {
        typedef ::mm::mtl::FixedVector<QuestTaskParam, 4>::iterator iterator;
        for (iterator it = tasks.begin(), end = tasks.end(); it != end; ++it) {
            unsigned int taskType = it->m_taskType;
            if (taskType == 6) {
                unsigned int type = talkIconType(it->m_taskId);
                if (type != 0) {
                    return type;
                }
            } else if (taskType == 10) {
                unsigned int type = conditionIconType(it->m_taskId);
                if (type != 0) {
                    return type;
                }
            } else if (taskType == 3) {
                unsigned int type = fn_710030AB00(it->m_taskId, info);
                if (type != 0) {
                    return type;
                }
            }
        }
    }
    return 0;
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

bool GfQuestTarget::getNpcList(::mm::mtl::FixedVector<unsigned short, 64>& npcs, QuestID questId) {
    // (true for an empty list when the quest is not in progress)
    if (!GfQuestInfo::isQuestProgress(questId)) {
        return npcs.empty();
    }
    QuestListAcc* acc = QuestListAcc::get();
    for (unsigned int i = 0; i < 4; ++i) {
        QuestTaskParam param(questId, i, TASK_STATE(0));
        switch (param.m_taskType) {
        case 2:
            if (acc->getRequestItemSetNpcID(param.m_taskId) != 0) {
                npcs.push_back(acc->getRequestItemSetNpcID(param.m_taskId));
            }
            break;
        case 3:
            if (acc->getCollectNpcID(param.m_taskId) != 0) {
                npcs.push_back(acc->getCollectNpcID(param.m_taskId));
            }
            break;
        case 6: {
            QuestListAcc* talk = QuestListAcc::get();
            if (talk->getTalkNpcID(param.m_taskId) != 0) {
                npcs.push_back(talk->getTalkNpcID(param.m_taskId));
            }
            unsigned int group = talk->getTalkDummyGroup(param.m_taskId);
            if (group != 0) {
                for (unsigned int j = 0; j < 8; ++j) {
                    unsigned int npcId = talk->getDummyGroupNpcID(group, j);
                    if (npcId != 0) {
                        npcs.push_back(npcId);
                    }
                }
            }
            break;
        }
        case 10:
            if (acc->getConditionNpcID(param.m_taskId) != 0) {
                npcs.push_back(acc->getConditionNpcID(param.m_taskId));
            }
            break;
        }
    }
    return npcs.size() != 0;
}

static unsigned int fn_710030C150(const TargetInfo* info) {
    if (GfDataQuest::getQuestCategory(info->m_questId) == 1) {
        return 1;
    }
    if (!info->m_flag || GfQuestManager::getCurrentQuest(QTYPE(0)) == info->m_questId ||
        GfQuestManager::getProgressCurrentQuest(QTYPE(0)) == info->m_questId) {
        return 3;
    }
    QuestID linked = QuestListAcc::get()->getListLinkedQuestID(info->m_questId);
    if (GfQuestManager::getCurrentQuest(QTYPE(0)) == linked || GfQuestManager::getProgressCurrentQuest(QTYPE(0)) == linked) {
        return 3;
    }
    return 0;
}

}  // namespace gf
