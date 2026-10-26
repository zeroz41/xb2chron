#ifndef CLASSES_GF_GFMENUMSGLIST_H
#define CLASSES_GF_GFMENUMSGLIST_H

#include "classes/ui/UIListInfo.h"

namespace ui { class UIStr; }

namespace gf {
// a message list's content (8 bytes: UIListInfo<MsgID>'s buffer grows by 8)
class MsgID {
public:
    // the names are not the original's: getMsg shows m_id's text (through the data table's name column when
    // the list has one); the callers' sorts (fn_7100379F9C's comparators) order by m_sortKey first, which the
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits in this
    // unit's text right after getMsg and sorts this list (UIListInfo<MsgID>::sort). What it does: when the list
    // is not empty, sorts it with fn_710037A0E0 (flag set: m_sortKey descending) or fn_710037A10C (flag clear:
    // m_sortKey ascending), ties by m_id ascending. The event theater calls it after filling a list.
    void fn_7100379F9C(bool descending);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (its symbol was a byte match of 1.0.0's
    // GfMenuObjHanaCustom::searchIdList, which works on a GfMenuIDList). A member because it sits in this unit's
    // text and reads this list's contents. What it does: the index of the first content whose m_id is id, -1 when
    // none; the gift box menu (fn_710040E1E0) calls it on a GfMenuMsgList it fills.
    unsigned int fn_710037A244(unsigned int id);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because fn_7100379F9C (this
    // class) hands them to the sort and they sit right after it. What they do: fn_710037A0E0 orders by m_sortKey
    // descending, fn_710037A10C by m_sortKey ascending, both by m_id ascending on a tie.
    static bool fn_710037A0E0(const MsgID& a, const MsgID& b);
    static bool fn_710037A10C(const MsgID& a, const MsgID& b);

    unsigned char* m_dataBdat;  // a table whose name column gives m_id's message id (none: m_id is it); the name is not the original's
    unsigned char* m_msgBdat;   // the message table getMsg reads; the name is not the original's
};
}  // namespace gf

#endif
