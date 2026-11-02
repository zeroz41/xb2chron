#ifndef GF_QUESTLISTACC_H
#define GF_QUESTLISTACC_H

#include "gf/QuestID.h"
#include "mm/mtl/FixedVector.h"

class CBdatWrapper;

namespace gf { class QuestTaskParam; }

namespace gf {
class QuestListAcc;

// which quest list QuestListAcc::begin and end walk
enum QTYPE {};

// one category of quest list or task rows: the rows in order and the (up to two) BDAT tables they come from
// (layout from addListCategory, addTaskCategory and getQuestListByIndex; the names are not the original's)
template <unsigned long N>
class QuestCategory {
public:
    void clear() {
        m_begin = 0;
        m_end = 0;
        m_bdat2 = nullptr;
        m_bdat = nullptr;
        m_split = 0xFFFF;
        m_ids.clear();
    }

    mm::mtl::FixedVector<unsigned short, N> m_ids;  // the rows' ids
    CBdatWrapper* m_bdat;    // the first table
    CBdatWrapper* m_bdat2;   // the table rows from m_split on come from
    unsigned short m_begin;  // the first and one past the last row (in the acc's numbering)
    unsigned short m_end;
    unsigned short m_split;  // the first row of m_bdat2 (0xFFFF none)
};

// a position in a quest list (0x18 bytes: 1.0.0's operator++ copies it out as three words)
class qlist_iterator {
public:
    // at the end of type's list (begin and end build one; a walk of the acc QuestListAcc::get returns)
    explicit qlist_iterator(QTYPE type);
    QuestID getQuestID() const;
    qlist_iterator operator++();
    // the walk compares positions only (GfMenuQuestList::setup reads the words at 0xC)
    bool operator!=(const qlist_iterator& other) const { return m_pos.m_index != other.m_pos.m_index; }

    // the list walked and the position in it, one 8-byte pair: operator++ loads it as one 64-bit value (an ldp
    // after its own load of m_index) and steps from that copy (the names are not the original's)
    struct Position {
        QTYPE m_type;  // the list walked (0 all of them, else category m_type)
        int m_index;   // the position (-1 past the end, 1.0.0's operator++)
    };

    QuestListAcc* m_acc;  // what 1.0.0's operator++ asks getQuestListByIndex; the name is not the original's
    Position m_pos;
    const QuestCategory<8096>* m_category;  // m_type's category (begin, end); the name is not the original's
};

// the quest lists
class QuestListAcc {
public:
    QuestListAcc();
    ~QuestListAcc();
    void clear();
    void rebuild();
    void addListCategory(unsigned short id, unsigned int category, CBdatWrapper* bdat);
    void addTaskCategory(unsigned short id, unsigned int category, CBdatWrapper* bdat);
    // 3.0.1 passes GfBdatQuest::m_useIra (bdatRefresh loads it into w1 for the tail call; the body never reads it:
    // its first call overwrites w1). The symbols spell 1.0.0's parameterless name; the parameter name is not the
    // original's.
    void makeQuestTaskInfo(bool useIra);
    bool getQuestListByIndex(CBdatWrapper*& bdat, unsigned short& id, unsigned int index) const;
    // the game flag a task of a purpose counts in (getTaskFlag's per-category bases)
    unsigned int getTaskFlag(unsigned int purposeId, unsigned int task) const;
    static QuestListAcc* get();
    qlist_iterator begin(QTYPE type) const;
    qlist_iterator end(QTYPE type) const;
    int getListQuestCategory(QuestID id) const;
    int getListVisible(QuestID id) const;
    int getListQuestIcon(QuestID id) const;  // 0 for none
    unsigned int getListTalker(QuestID id) const;
    unsigned int getListRewardSetA(QuestID id) const;
    unsigned int getListRewardSetB(QuestID id) const;
    unsigned int getListResultA(QuestID id) const;
    unsigned int getListResultB(QuestID id) const;
    unsigned int getListSummary(QuestID id) const;
    unsigned int getListFlagPRT(QuestID id) const;
    unsigned int getListFlagCLD(QuestID id) const;
    unsigned int getListCallEventA(QuestID id) const;
    unsigned int getListCallEventB(QuestID id) const;
    unsigned int getListHintsID(QuestID id) const;
    unsigned int getListPurposeID(QuestID id) const;
    unsigned int getListQuestTitle(QuestID id) const;
    unsigned int getListPRTQuestID(QuestID id) const;
    unsigned int getListCountCancel(QuestID id) const;
    unsigned int getListNextQuestA(QuestID id) const;
    unsigned int getListNextQuestB(QuestID id) const;
    unsigned int getListAutoStart(QuestID id) const;
    unsigned int getListItemLost(QuestID id) const;
    unsigned int getListCancelCondition(QuestID id) const;
    unsigned int getListLinkedQuestID(QuestID id) const;
    unsigned int getTaskTaskID(unsigned int purposeId, unsigned int task) const;
    unsigned int getTaskTaskType(unsigned int purposeId, unsigned int task) const;
    unsigned int getTaskTaskBranch(unsigned int purposeId, unsigned int task) const;
    // the first condition of the tasks of a purpose (GfKizunaringBlade::isNetabareOK asks GfGameCond about it)
    unsigned int getTaskTaskCondition1(unsigned int purposeId) const;
    unsigned int getTaskTaskUI(unsigned int purposeId, unsigned int task) const;
    unsigned int getTaskTaskLog(unsigned int purposeId, unsigned int task) const;
    unsigned int getTaskTaskCondition(unsigned int purposeId, unsigned int task) const;
    unsigned int getTaskPreCondition(unsigned int id) const;
    unsigned int getBattleEnemyID(unsigned int id) const;
    unsigned int getBattleEnemyGroupID(unsigned int id) const;
    unsigned int getBattleEnemySpeciesID(unsigned int id) const;
    unsigned int getBattleCount(unsigned int id) const;
    unsigned int getBattleCountFlag(unsigned int id) const;
    unsigned int getCollectItemID(unsigned int id) const;
    unsigned int getCollectCategory(unsigned int id) const;
    unsigned int getCollectCount(unsigned int id) const;
    unsigned int getUseItemID(unsigned int id) const;
    unsigned int getUseCategory(unsigned int id) const;
    unsigned int getUseItemNumber(unsigned int id) const;
    unsigned int getReachMapID(unsigned int id) const;
    unsigned int getTalkMapID(unsigned int id) const;
    unsigned int getConditionMapID(unsigned int id) const;
    unsigned int getConditionConditionID(unsigned int id) const;
    // the game flag (8 bits wide, after 0x5EF) counting a collect or use task's items
    int getCollectUseFlagIndex(const QuestTaskParam& param) const;
    // generated column accessors
    // Placeholder name: nothing in 1.0.0's place names it (new in 3.0.1, or 1.0.0 has no QuestListAcc
    // accessor for this column). A member because it fills QuestListAcc's unit between proven getters and
    // has their shape. What it does: reads a row of GfBdatQuest's column BattleEnemyRaceID (1.0.0 accessor prefix +
    // BDAT column name from rebuild's getMember string), 0 out of the table's range.
    unsigned int fn_710025ABB8(unsigned int id) const;
    unsigned int getBattleDeadAll(unsigned int id) const;
    unsigned int getBattleTimeCount(unsigned int id) const;
    unsigned int getBattleReduceEnemyHP(unsigned int id) const;
    unsigned int getBattleReducePCHP(unsigned int id) const;
    // Placeholder name: nothing in 1.0.0's place names it (new in 3.0.1, or 1.0.0 has no QuestListAcc
    // accessor for this column). A member because it fills QuestListAcc's unit between proven getters and
    // has their shape. What it does: reads a row of GfBdatQuest's column BattleTargetOff (1.0.0 accessor prefix +
    // BDAT column name from rebuild's getMember string), 0 out of the table's range.
    unsigned int fn_710025AFC4(unsigned int id) const;
    unsigned int getRequestItemSetNpcID(unsigned int id) const;
    unsigned int getRequestItemSetItemID(unsigned int id, unsigned int index) const;
    unsigned int getRequestItemSetCount(unsigned int id, unsigned int index) const;
    unsigned int getCollectDeduct(unsigned int id) const;
    // 1.0.0's name: QuestListAcc::getCollectTresureID reads the same table and BDAT column
    unsigned int getCollectTresureID(unsigned int id) const;
    // 1.0.0's name: QuestListAcc::getCollectEnemyID reads the same table and BDAT column
    unsigned int getCollectEnemyID(unsigned int id) const;
    // 1.0.0's name: QuestListAcc::getCollectMapID reads the same table and BDAT column
    unsigned int getCollectMapID(unsigned int id) const;
    // 1.0.0's name: QuestListAcc::getCollectNpcID reads the same table and BDAT column
    unsigned int getCollectNpcID(unsigned int id) const;
    // Placeholder name: nothing in 1.0.0's place names it (new in 3.0.1, or 1.0.0 has no QuestListAcc
    // accessor for this column). A member because it fills QuestListAcc's unit between proven getters and
    // has their shape. What it does: reads a row of GfBdatQuest's column CollectCollectionID (1.0.0 accessor prefix +
    // BDAT column name from rebuild's getMember string), 0 out of the table's range.
    unsigned int fn_710025B5CC(unsigned int id) const;
    // 1.0.0's name: QuestListAcc::getUsebladeID reads the same table and BDAT column
    unsigned int getUsebladeID(unsigned int id) const;
    unsigned int getReachCategory(unsigned int id) const;
    unsigned int getReachPlaceID(unsigned int id) const;
    unsigned int getTalkStart() const;
    unsigned int getTalkEnd() const;
    unsigned int getTalkNpcID(unsigned int id) const;
    unsigned int getTalkDummyGroup(unsigned int id) const;
    unsigned int getDummyGroupNpcID(unsigned int id, unsigned int index) const;
    unsigned int getGimmickStart() const;
    unsigned int getGimmickEnd() const;
    unsigned int getGimmickMapID(unsigned int id) const;
    unsigned int getGimmickDoorGimmickID(unsigned int id) const;
    unsigned int getGimmickElevatorGimmickID(unsigned int id) const;
    unsigned int getGimmickJumpGimmickID(unsigned int id) const;
    unsigned int getGimmickMapGimmickID(unsigned int id) const;
    unsigned int getGimmickMapGmkIconOff(unsigned int id) const;
    unsigned int getGimmickWarpGimmickID(unsigned int id) const;
    unsigned int getGimmickSalvagePointID(unsigned int id) const;
    unsigned int getGimmickTboxPopID(unsigned int id) const;
    // Placeholder name: nothing in 1.0.0's place names it (new in 3.0.1, or 1.0.0 has no QuestListAcc
    // accessor for this column). A member because it fills QuestListAcc's unit between proven getters and
    // has their shape. What it does: reads a row of GfBdatQuest's column GimmickEnemyWaveID (1.0.0 accessor prefix +
    // BDAT column name from rebuild's getMember string), 0 out of the table's range.
    unsigned int fn_710025C23C(unsigned int id) const;
    // Placeholder name: nothing in 1.0.0's place names it (new in 3.0.1, or 1.0.0 has no QuestListAcc
    // accessor for this column). A member because it fills QuestListAcc's unit between proven getters and
    // has their shape. What it does: reads a row of GfBdatQuest's column GimmickCampPopID (1.0.0 accessor prefix +
    // BDAT column name from rebuild's getMember string), 0 out of the table's range.
    unsigned int fn_710025C2D0(unsigned int id) const;
    // Placeholder name: nothing in 1.0.0's place names it (new in 3.0.1, or 1.0.0 has no QuestListAcc
    // accessor for this column). A member because it fills QuestListAcc's unit between proven getters and
    // has their shape. What it does: reads a row of GfBdatQuest's column GimmickCollectionPopID (1.0.0 accessor prefix +
    // BDAT column name from rebuild's getMember string), 0 out of the table's range.
    unsigned int fn_710025C364(unsigned int id) const;
    // 1.0.0's name: QuestListAcc::getGimmickEndCheck reads the same table and BDAT column
    unsigned int getGimmickEndCheck(unsigned int id) const;
    unsigned int getFieldSkillCountFieldSkillID(unsigned int id) const;
    unsigned int getFieldSkillCountCount(unsigned int id) const;
    unsigned int getRequestBladeRequestCategory(unsigned int id) const;
    unsigned int getRequestBladeRequestAtr(unsigned int id) const;
    unsigned int getRequestBladeRequestPerformance(unsigned int id) const;
    unsigned int getRequestBladeRequestRace(unsigned int id) const;
    unsigned int getRequestBladeRequestGender(unsigned int id) const;
    unsigned int getRequestBladeRequestArts(unsigned int id) const;
    unsigned int getRequestBladeRequestArtsLevel(unsigned int id) const;
    unsigned int getRequestBladeRequestFSkill(unsigned int id) const;
    unsigned int getRequestBladeRequestFSLevel(unsigned int id) const;
    unsigned int getRequestBladeRequestNumber(unsigned int id) const;
    unsigned int getConditionNpcID(unsigned int id) const;
    unsigned int getAchievementStatsID(unsigned int id) const;
    unsigned int getAchievementCount(unsigned int id) const;
    unsigned int getHintsFSkillID1(unsigned int id) const;
    unsigned int getHintsFSkillID2(unsigned int id) const;
    unsigned int getHintsFSkillID3(unsigned int id) const;
    unsigned int getHintsZoneID(unsigned int id) const;
    unsigned int getHintsFSkillID(unsigned int id, unsigned int index) const;
    unsigned int getEventEventID(unsigned int id) const;
    unsigned int getRewardGold(unsigned int id) const;
    unsigned int getRewardEXP(unsigned int id) const;
    unsigned int getRewardSp(unsigned int id) const;
    unsigned int getRewardCoin(unsigned int id) const;
    unsigned int getRewardDevelopZone(unsigned int id) const;
    unsigned int getRewardDevelopPoint(unsigned int id) const;
    unsigned int getRewardTrustPoint(unsigned int id) const;
    unsigned int getRewardMercenariesPoint(unsigned int id) const;
    unsigned int getRewardIdeaCategory(unsigned int id) const;
    unsigned int getRewardIdeaValue(unsigned int id) const;
    unsigned int getRewardItemID(unsigned int id, unsigned int index) const;
    unsigned int getRewardItemNumber(unsigned int id, unsigned int index) const;
    unsigned int getFLD_AchievementSetStart() const;
    unsigned int getFLD_AchievementSetEnd() const;
    unsigned int getFLD_AchievementSetCategory(unsigned int id) const;
    unsigned int getFLD_AchievementSetAbilityLevel(unsigned int id) const;
    unsigned int getFLD_AchievementSetAchievementID1(unsigned int id) const;
    unsigned int getFLD_AchievementSetAchievementID2(unsigned int id) const;
    unsigned int getFLD_AchievementSetAchievementID3(unsigned int id) const;
    unsigned int getFLD_AchievementSetAchievementID4(unsigned int id) const;
    unsigned int getFLD_AchievementSetAchievementID5(unsigned int id) const;
    unsigned int getFLD_AchievementSetAchievementID(unsigned int id, unsigned int index) const;
    unsigned int getFLD_AchievementListCategory(unsigned int id) const;
    unsigned int getFLD_AchievementListIcon(unsigned int id) const;
    unsigned int getFLD_AchievementListTask(unsigned int id) const;
    unsigned int getFLD_AchievementListVoiceCategory(unsigned int id) const;
    unsigned int getFLD_AchievementListAfterVoice(unsigned int id) const;
    unsigned int getFLD_AchievementListDifficulty(unsigned int id) const;
    unsigned int getFLD_AchievementListIdeaCategory(unsigned int id) const;
    unsigned int getFLD_MercenariesConfigValue(unsigned int id) const;
    unsigned int getFLD_MercenariesMissionStart() const;
    unsigned int getFLD_MercenariesMissionEnd() const;
    unsigned int getFLD_MercenariesMissionQuestID(unsigned int id) const;
    unsigned int getFLD_MercenariesMissionCategory(unsigned int id) const;
    unsigned int getFLD_MercenariesMissionRequestPerformance(unsigned int id) const;
    unsigned int getFLD_MercenariesMissionRepeatable(unsigned int id) const;
    unsigned int getFLD_MercenariesMissionAutoStart(unsigned int id) const;
    unsigned int getFLD_FieldSkillListStart() const;
    unsigned int getFLD_FieldSkillListEnd() const;
    unsigned int getFLD_FieldSkillListName(unsigned int id) const;
    unsigned int getFLD_FieldSkillListCaption(unsigned int id) const;
    // named by 1.0.0: column-text (its slot is looked up by its column name; 1.0.0's accessor reads that column)
    unsigned int getFLD_FieldSkillListMinLevel(unsigned int id) const;
    unsigned int getFLD_FieldSkillListMaxLevel(unsigned int id) const;
    // named by 1.0.0: column-text (its slot is looked up by its column name; 1.0.0's accessor reads that column)
    unsigned int getFLD_FieldSkillListCategory(unsigned int id) const;
    unsigned int getFLD_FieldSkillListVoiceCategory(unsigned int id) const;
    unsigned int getFLD_FieldSkillListAttirbute(unsigned int id) const;
    unsigned int getFLD_FieldSkillSettingStart() const;
    // named by 1.0.0: column-text (its slot is looked up by its column name; 1.0.0's accessor reads that column)
    unsigned int getFLD_FieldSkillSettingSuccessVoiceCategory(unsigned int id) const;
    // named by 1.0.0: column-text (its slot is looked up by its column name; 1.0.0's accessor reads that column)
    unsigned int getFLD_FieldSkillSettingMissVoiceCategory(unsigned int id) const;
    unsigned int getFLD_DevelopmentLevelValue(unsigned int id) const;
    // (layout from the constructor, clear, the getters and makeQuestTaskInfo; the names are not the original's)
    QuestCategory<8096> m_list[6];         // the quest list categories (category k is m_list[k - 1])
    unsigned int m_listIndex[16000];       // per quest id: category << 24 | row
    unsigned int m_listCount;              // the rows added
    QuestCategory<4096> m_task[6];         // the task categories
    unsigned int m_taskIndex[16000];       // per purpose id: category << 24 | row
    unsigned int m_taskCount;
    unsigned short m_taskInfoIndex[64000]; // per quest id * 4 + task: 1 + the task's m_taskInfo entry (0 none)
    mm::mtl::FixedVector<unsigned short, 1024> m_taskInfo;  // per collect/use task: its count flag
};

inline qlist_iterator::qlist_iterator(QTYPE type)
    : m_pos{type, -1} {
    m_acc = QuestListAcc::get();
    m_category = type != 0 ? &m_acc->m_list[type - 1] : nullptr;
}
}  // namespace gf

#endif
