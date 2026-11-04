#ifndef CLASSES_GF_GFMENUMSGLIST_H
#define CLASSES_GF_GFMENUMSGLIST_H

#include "classes/ui/UIListInfo.h"

namespace ui { class UIStr; }

namespace gf {
// a message list's content (8 bytes: UIListInfo<MsgID>'s buffer grows by 8)
class MsgID {
public:
    // the names are not the original's: getMsg shows m_id's text (through the data table's name column when
    // the list has one); the callers' sorts (sort's comparators) order by m_sortKey first, which the
    // event theater fills from GfMenuBdat::getSortKeyName
    unsigned int m_id;
    unsigned int m_sortKey;
};

// table 0x7100B5F6A8
class GfMenuMsgList : public ::ui::UIListInfo< ::gf::MsgID> {
public:
    GfMenuMsgList() : m_dataBdat(nullptr), m_msgBdat(nullptr) {}
    virtual ~GfMenuMsgList();  // slot 0
    static GfMenuMsgList* create();
    void setBdat(unsigned int dataBdat, unsigned int msgBdat);
    bool getMsg(int index, ui::UIStr& str, bool page);
    // 2.0.0's symbols name it. What it does: when the list is not empty, sorts it with sortDescending (flag set:
    // m_sortKey descending) or sortAscending (flag clear: m_sortKey ascending), ties by m_id ascending. The event
    // theater calls it after filling a list.
    void sort(bool descending);
    // 2.0.0's symbols name it. What it does: the index of the first content whose m_id is id, -1 when none; the gift
    // box menu (fn_710040E1E0) calls it on a GfMenuMsgList it fills.
    unsigned int find(unsigned int id);
    // 2.0.0's symbols name them. What they do: sortDescending orders by m_sortKey descending, sortAscending by
    // m_sortKey ascending, both by m_id ascending on a tie.
    static bool sortDescending(const MsgID& a, const MsgID& b);
    static bool sortAscending(const MsgID& a, const MsgID& b);

    unsigned char* m_dataBdat;  // a table whose name column gives m_id's message id (none: m_id is it); the name is not the original's
    unsigned char* m_msgBdat;   // the message table getMsg reads; the name is not the original's
};
}  // namespace gf

#endif
