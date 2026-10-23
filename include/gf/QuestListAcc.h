#ifndef GF_QUESTLISTACC_H
#define GF_QUESTLISTACC_H

#include "gf/QuestID.h"

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
};
}  // namespace gf

#endif
