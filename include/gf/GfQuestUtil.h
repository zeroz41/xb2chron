#ifndef GF_GFQUESTUTIL_H
#define GF_GFQUESTUTIL_H

#include "gf/QuestID.h"
namespace gf { class GF_OBJ_HANDLE; }
#include "gf/QuestListAcc.h"

namespace gf { class QuestTaskParam; }
namespace gf { struct GfQuestReward; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}
namespace mm { namespace mtl { template <typename T, unsigned long N> class FixedArray; }}

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
    // the last parent quest taken whose category (GfDataQuest::getQuestCategory) is not the type
    static QuestID getLastOrderInvalidCategoryQuest(QTYPE type);
    static void clearOrderParentQuest();
    static void addOrderParentQuest(QuestID id);
    static void removeOrderParentQuest(QuestID id);
    static QuestID getLastOrderParentQuest();
    // the quest a treasure box's object belongs to through an active task (GfPlayComFieldTbox's constructor keeps it)
    static QuestID getCurrentTBoxWithEvent(GF_OBJ_HANDLE* handle);
    // the quest an enemy's bdat id belongs to through an active task (CharacterManager::PreUpdateProc asks it for
    // every enemy in battle)
    static QuestID getCurrentEnemyWithEvent(unsigned int enemyID);
    // whether a battle task's enemy (or one of its group's) is on the field with HP left, not counting event-created
    // enemies
    static bool isExtstActivateEnemy(const QuestTaskParam& param);
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
    // whether the progressing quest has a task that reduces the object's HP (GfQuestTask::isReduceHpObj)
    static bool isReduceHpObj(GF_OBJ_HANDLE* handle);
    static unsigned short getBladeID(QuestID id);
    // takes the task's items from the party when its collect row deducts them
    static void removeQuestItem(const QuestTaskParam& param);
    // formats the task's enemy and its suppress counts (the log call itself is compiled out)
    static void sendSuppressLog(const QuestTaskParam& param, unsigned int enemy);
    // adds to a general-purpose (hanyou) task's flag count, up to its limit, and tells the quest manager
    static void addTaskHanyouCount(unsigned int purposeId, unsigned int task, unsigned int add);
    // how many of the enemy a battle task of the progressing or an ordered quest still needs; 0 when none more,
    // -1 when no task wants it
    static int getEnemyPopRemainNumber(unsigned int enemy);
    // resets the parent quests of categories 1, 3 and 2 for a new game (but a few kept ones)
    static void setupNewGameParam();
    // takes the items the quest's ItemLost row names (or the most held of its category) when it completes
    static void questCompleteItem(QuestID id);  // the affinity chart quest's blade, 0 for none
    // fills the reward with the rewards of that reward id (GfMenuObjShop's exchange tasks pass a QUEST_EXCHANGE row's
    // "Reward" and false); true when it has any
    static bool getReward(GfQuestReward& reward, unsigned int id, bool);
    // gives the party the reward (gf::fn_71002EE640 passes an affinity chart reward)
    static void execReward(const GfQuestReward& reward);
    // whether the enemy is one of the enemy group's 12 (GfBdatChrEnParam::getEnemyGroupEnemyID); false for no group
    static bool isEnemyGroup(unsigned int group, unsigned int enemy);
    // the dummy talk group (and its flag bit) of an NPC on a map for the quest; false when it has none (fn_710030B16C
    // passes them to GfQuestInfo::isDummuTalkGroupFlag)
    static bool getDummyTalkGroup(unsigned int& group, unsigned int& bit, unsigned int mapId, unsigned int npcId,
                                  QuestID questId);
    // counts a field skill use for the first ordered, unfinished affinity chart quest of the blade whose field skill
    // count task wants that skill (SCOM_FIELD_SKILL::exec)
    static void incFieldSkillTask(unsigned int blade, unsigned int skill);
    // each of the quest's 4 tasks' map (GfQuestTask::getTaskMap), from a linked quest's next quest when the quest's
    // own has none; false for no quest or a parent quest
    static bool getTaskMap(mm::mtl::FixedArray<unsigned short, 4>& maps, QuestID id);
    // Placeholder names (no symbol; these are new since 1.0.0, so no donor name):
    // counts the quest's collect tasks as used up while the party holds their limit (GfGameScene::gevItemAdd, update)
    static void applyNeedFollowQuestTask(QuestID id);
    // orders or resets a few fixed quests and flags whose conditions are met (GfGameScene::update)
    static void applyNeedFollowQuestState();
};

// a condition task's flag conditions: adds how many there are to total and how many hold to met; false when the task
// is no condition task or its condition has a premise (GfQuestUtil::getMsgQuestTaskLog)
bool fn_71003134FC(const QuestTaskParam& param, unsigned int& total, unsigned int& met);
// a condition task's first flag condition: its minimum and the flag's value capped at it; false when its first
// condition is no flag (GfQuestUtil::getMsgQuestTaskLog)
bool fn_71003135E4(const QuestTaskParam& param, unsigned int& min, unsigned int& value);
}  // namespace gf

#endif
