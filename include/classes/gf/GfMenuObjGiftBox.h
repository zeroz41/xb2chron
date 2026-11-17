#ifndef CLASSES_GF_TUNK_B625A0_H
#define CLASSES_GF_TUNK_B625A0_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Vector.h"

namespace gf { class GfMenuIDList; }
namespace gf { class GfMenuMsgList; }
namespace gf { class GfMenuReferenceItem; }
namespace gf { class GfMenuReferenceNumber; }

namespace gf {
// table 0x7100B625A0. The gift box menu object (its file is gf_menu_obj_gift_box.cpp, the assertion path of its
// listeners' news; its UI object is "mnu104_gift_box", GfMenuManager::reciveEvent news 0x3E0 bytes for it). 1.0.0
// has no such class and the symbols leave it unnamed, so it is named after its table. The field names are inferred.
class GfMenuObjGiftBox : public ::gf::GfMenuObject {
public:
    // its UI listeners (tables 0x7100B625E8, 0x7100B62610, 0x7100B62638, 0x7100B62660; nothing names them)
    class MainListener;
    class TopListener;
    class SubListener;
    class FilterListener;
    // an item seqGetItemAll got: 4 bytes (Vector<AddedItem>::expand's stride), its first word the item id it
    // handed execGetItem (the field name is not the original's)
    struct AddedItem {
        unsigned int m_id;
    };
    GfMenuObjGiftBox(unsigned int handle);
    virtual ~GfMenuObjGiftBox();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name them. fn_7100383310 calls them; each registers the gift box's full-screen layer (0x46) with
    // menu id 1 / 2, which initialize reads back into m_menuId. 2.0.0's symbols name it. A
    // static member: its address lies in this class's unit (before canGetItem, which it calls) and it takes no object.
    // What it does: off menu layer 3 and with GfMenuManager::hasGift, walks BDAT 0x10A's rows ("releasecount", add-on
    // 5, canGetItem) and answers whether a gift is waiting; the flag picks which rows count. Callers:
    // GfMenuObjMainMenu2's setupMainMenu and main listener (they show "LAY_gift_icon" with hasGetableGift(true)),
    // GfMenuObjPopup's main listener.
    static bool hasGetableGift(bool);
    // 2.0.0's symbols name them. hasGetableFreeGift: hasGetableGift over the rows with "releasecount" bit 7 only
    // (GfMenuObjAnnounce::initialize); hasGetableGiftFromFilter: over the rows the filter keeps.
    static bool hasGetableFreeGift(bool);
    bool hasGetableGiftFromFilter(bool);
    static void setCloseToAnnounce();
    static void setCloseToAnnounceEx();
    // 2.0.0's symbols name them. seqWaitCommonDialog waits for the common window to close; seqReturnTop / seqReturnSub
    // open "LAY_top_list" / "LAY_sub_list" (event 0x100); seqGetItem acts on the top list's selected id, refreshes and
    // opens common window 0xE8.
    bool seqWaitCommonDialog();
    bool seqReturnTop();
    bool seqGetItem();
    bool seqReturnSub();
    // 2.0.0's symbols name them. getAddedItemValue: what seqGetItemAll hands canGetItem as the row's second argument
    // (it reads m_ids, the rows already taken); seqGetItemAll takes every row of the top list's titles it can.
    unsigned int getAddedItemValue(unsigned int row);
    bool seqGetItemAll();
    // 2.0.0's symbols name them. canGetItem: the row's local flag (type 1) is clear, its game condition holds and
    // isGetItemFull(row, arg) is false. hasFreeGift: add-on 5 is present (gf::GfDataAoc::getContentVersion(5) >= 0) and some row's
    // "releasecount" has bit 7 set. isGetItemFull is called with the row and the caller's second
    // argument.
    static bool canGetItem(unsigned int row, unsigned int arg);
    static bool hasFreeGift();
    static bool isGetItemFull(unsigned int row, unsigned int arg);
    // 2.0.0's symbols name them.
    static void execGetItem(unsigned int id);
    void refreshTopList(bool);
    void refreshSubList();
    // the symbols name it (not written yet): FilterListener calls it after the selected filter changes
    void refreshFilter();
    // 2.0.0's symbols name it: fills m_topList from table 0x10A (initialize, TopListener)
    void updateTopList();
    // 2.0.0's symbols name them.
    void updateSubList();
    int ctrlTopItem(bool);
    int ctrlSubItem(bool);

    GfMenuMsgList* m_topList;  // 0x28: "LAY_top_list"'s list (initialize: setBdat(0, 0x139))
    GfMenuIDList* m_subList;   // 0x30: seqGetItem reads its selected id
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numbers[22];  // 0x38
    GfMenuSequence<GfMenuObjGiftBox, 8> m_seq;  // 0xE8: update runs it
    unsigned char pad_378;
    // 0x379-0x37B: the top list's filter (FilterListener sets them; hasGetableGiftFromFilter / updateTopList test
    // m_counts[m_filterIndex] against the rows' "releasecount" when m_filterIndex and m_filterCount are set). The names
    // are not the original's.
    // 0x379: a byte FilterListener shows the filter by (setDisp(count != 0), so not a bool) and hands
    // setupInputSelection as the selection count
    unsigned char m_filterCount;
    unsigned char m_filterIndex;   // 0x37A: the selected filter (FilterListener's event 6 sets it)
    // 0x37B: the first filter icon shown: FilterListener scrolls it by one when the selection leaves the icons
    // (m_iconCount of them) at either end and sets m_counts.size() - m_iconCount when the selection wraps to the end
    unsigned char m_filterCursor;
    mm::mtl::IntrusivePtr<GfMenuReferenceItem> m_refItem;  // 0x380
    mm::mtl::Vector<AddedItem> m_ids;  // 0x388: compared with the BDAT rows' ids (seqGetItemAll grows it through
                                       // Vector<AddedItem>::expand)
    mm::mtl::Vector<int> m_counts;     // 0x3B0: compared with the BDAT rows' "releasecount" (initialize grows it
                                       // through Vector<int>::expand)
    unsigned int m_menuId;  // 0x3D8: the layer parameter's menu id (setCloseToAnnounce / setCloseToAnnounceEx)
    bool m_hasMenuId;       // 0x3DC: initialize found a layer parameter
    bool m_noMenuId;        // 0x3DD: !m_hasMenuId
};
}  // namespace gf

#endif
