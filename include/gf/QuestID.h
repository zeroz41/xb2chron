#ifndef GF_QUESTID_H
#define GF_QUESTID_H

namespace gf {
// a quest: passed by value in a register (4 bytes); 1.0.0's empty() tests the halfword at 0 against 1-29999
class QuestID {
public:
    // zeroes both halves: 1.0.0's qlist_iterator::getQuestID starts from one, and UIListInfo<QuestID>'s constructor
    // stores them separately (its zero stores merge into one memset of 0x58-0x64)
    QuestID() : m_id(0), pad_2(0) {}
    bool empty() const;
    unsigned short m_id;  // what empty() tests; the name is not the original's
    unsigned short pad_2;
};
}  // namespace gf

#endif
