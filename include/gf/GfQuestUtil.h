#ifndef GF_GFQUESTUTIL_H
#define GF_GFQUESTUTIL_H

#include "gf/QuestID.h"
namespace gf { class GF_OBJ_HANDLE; }
#include "gf/QuestListAcc.h"

namespace gf { class QuestTaskParam; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace gmk { enum GmkType : int; }

namespace gf {
// what GfQuestUtil::getMsgQuestTaskLog finds for a quest's task (the field names are not the original's)
struct GfQuestTaskLogResult {
    GfQuestTaskLogResult()
        : m_log(0), m_fp(nullptr), m_param(0), m_count(0), m_dispCount(0), m_count2(0), m_count3(0),
          m_complete(false), m_type(0), m_type2(0) {}
    unsigned int m_log;  // the task's log message (QuestListAcc::getTaskTaskLog), 0 for none
    unsigned char* m_fp;  // the quest's message BDAT (GfBdatMsg::getFpQuest)
    unsigned int m_param;  // the task's QuestTaskParam word at 0x10
    // GfQuestTask::getTaskCount's four counts; the second shown is its first, or its second once complete
    unsigned int m_count;
    unsigned int m_dispCount;
    unsigned int m_count2;
    unsigned int m_count3;
    bool m_complete;  // the task is complete or has a target NPC
    unsigned short m_type;  // the task's QuestTaskParam halfwords at 0xC and 0xE
    unsigned short m_type2;
};

// the quests' helpers (functions, by their symbols)
class GfQuestUtil {
public:
    // logs the task's item (fn_710030EB68 after a collect count changes, for a visible quest)
    static void sendItemLog(const QuestTaskParam& param);
    static QuestID getLastOrderCategoryQuest(QTYPE type);
    static void clearOrderParentQuest();
    static void addOrderParentQuest(QuestID id);
    static QuestID getLastOrderParentQuest();
    // the quest a treasure box's object belongs to through an active task (GfPlayComFieldTbox's constructor keeps it)
    static QuestID getCurrentTBoxWithEvent(GF_OBJ_HANDLE* handle);
    // whether the quest has a task for the NPC: its condition id into condId (GfPlayComTalk::start keeps both
    // for GfPlayComTalk::getQuestTargetNpc)
    static bool getTalkNpcInfo(unsigned int& condId, unsigned int npc, QuestID quest);
    // a talk with the NPC on the map ended (GfPlayComTalk::end: the quest ordered during the talk, or none)
    static void finishTalkNpc(unsigned int map, unsigned int npc, QuestID quest);
    static bool getDispCount(unsigned int& count, unsigned int& max, const struct AchievQuest& quest);
    static bool getResultIdea(unsigned int& idea, unsigned int& count, unsigned int blade, unsigned int line,
                              unsigned int level);
    // whether a quest task ends at a gimmick: 1 when its items drop, 2 when its UI closes (GfFieldTbox's checks)
    static int getGimmickTaskEndCheck(gmk::GmkType type, unsigned int gimmickId);
    // a quest's title, summary and result messages (GfDataQuest::getTaskLog's ids), 0 for none
    static unsigned int getMsgQuestTitle(QuestID id);
    static unsigned int getMsgQuestSummary(QuestID id);
    static unsigned int getMsgQuestResult(QuestID id);
    // the message of the field skill a quest needs (its first or second)
    static unsigned int getMsgQuestNeedFieldSkill(unsigned int index, QuestID id);
    static bool getMsgQuestTaskLog(GfQuestTaskLogResult& result, const QuestTaskParam& param);
    // the characters a quest's task needs
    static bool getNeedCharacterByQuestTask(mm::mtl::FixedVector<unsigned short, 32>& characters, QuestID id,
                                            unsigned int task);
    static int getClearChildQuest(QuestID id);  // the child quests cleared
};
}  // namespace gf

#endif
