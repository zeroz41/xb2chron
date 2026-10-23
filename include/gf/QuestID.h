#ifndef GF_QUESTID_H
#define GF_QUESTID_H

namespace gf {
// a quest: passed by value in a register (4 bytes); 1.0.0's empty() tests the halfword at 0 against 1-29999
class QuestID {
public:
    // zeroes both halves: 1.0.0's qlist_iterator::getQuestID starts from one, and UIListInfo<QuestID>'s constructor
    // stores them separately (its zero stores merge into one memset of 0x58-0x64)
    QuestID() : m_id(0), m_achieveId(0) {}
    // from an int holding both halves: GfQuestEvent's functions take unsigned ints and pass their 32 bits on as the
    // QuestID unchanged
    QuestID(unsigned int id) : m_id(id), m_achieveId(id >> 16) {}
    bool empty() const;
    bool operator==(const QuestID& o) const { return m_id == o.m_id && m_achieveId == o.m_achieveId; }
    unsigned short m_id;  // what empty() tests; the name is not the original's
    // the achievement an affinity chart quest belongs to (GfDataQuest::getAchievementBlade maps it to its blade;
    // GfKizunaringBlade::qevCompleteQuest looks only at quests with one). The name is not the original's.
    unsigned short m_achieveId;
};
}  // namespace gf

#endif
