#ifndef GF_QUESTLISTACC_H
#define GF_QUESTLISTACC_H

#include "gf/QuestID.h"

namespace gf { class QuestTaskParam; }

namespace gf {
class QuestListAcc;

// which quest list QuestListAcc::begin and end walk
enum QTYPE {};

// a position in a quest list (0x18 bytes: 1.0.0's operator++ copies it out as three words)
class qlist_iterator {
public:
    QuestID getQuestID() const;
    qlist_iterator operator++();
    // the walk compares positions only (GfMenuQuestList::setup reads the words at 0xC)
    bool operator!=(const qlist_iterator& other) const { return m_index != other.m_index; }

    QuestListAcc* m_acc;  // what 1.0.0's operator++ asks getQuestListByIndex; the name is not the original's
    unsigned char pad_08[4];
    int m_index;  // the position (-1 past the end, 1.0.0's operator++); the name is not the original's
    unsigned char pad_10[8];
};

// the quest lists
class QuestListAcc {
public:
    static QuestListAcc* get();
    qlist_iterator begin(QTYPE type) const;
    qlist_iterator end(QTYPE type) const;
    int getListQuestCategory(QuestID id) const;
    int getListVisible(QuestID id) const;
    int getListQuestIcon(QuestID id) const;  // 0 for none
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
    // Placeholder name: new in 3.0.1's place, nothing names it. A member because it fills QuestListAcc's unit and is
    // called with QuestListAcc::get()'s object. What it does: reads a row of GfBdatQuest's table at 0x50 (the collect
    // tasks') in the column lbl_7100C34680 keeps at 0xF8, as 16 bits; 0 out of the table's range. Callers pass a
    // collect task's id (GfQuestTask::getTaskMap, GfQuestInfo's task map lookup).
    unsigned int fn_710025B4A4(unsigned int id) const;
    // Placeholder name: new in 3.0.1's place, nothing names it. A member because it fills QuestListAcc's unit and is
    // called with QuestListAcc::get()'s object. What it does: reads a row of a GfBdatQuest table in the column
    // lbl_7100C34680 keeps at 0x1F0 (callers pass a gimmick task's id: GfQuestTarget::getIconTypeGimmick,
    // GfQuestTask::completeGimmickTask, GfQuestUtil::getGimmickTaskEndCheck).
    unsigned int fn_710025C23C(unsigned int id) const;
};
}  // namespace gf

#endif
