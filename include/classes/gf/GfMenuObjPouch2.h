#ifndef CLASSES_GF_GFMENUOBJPOUCH2_H
#define CLASSES_GF_GFMENUOBJPOUCH2_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/ui/UIManager.h"
#include "ui/EventData.h"

namespace ui {
class UICtrlCursorSelect;
class UIObjectAcc;
class UISelectObjList;
class UIStr;
}  // namespace ui

namespace gf {
class GAME_VOICE_HANDLE;
class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuItemList;

// table 0x7100B641A0; the pouch item menu (favourite items of the party). Field names are not the original's.
class GfMenuObjPouch2 : public ::gf::GfMenuObject {
public:
    class FilterListener2;
    class ItemListListener;
    class MainListener;
    class PartyInfoListener;
    class ResultListener;
    class SlotListener;
    // a driver's or blade's favourites (1.0.0's setFavFlag/procFavFlag name the type; 0x18 bytes, the field names
    // are not the original's): setFavFlag fills it, seqFavLoop compares the old and new stats
    struct FavoriteFlag {
        unsigned int m_id;        // the driver (first) or blade id, 0 for none
        unsigned int m_chr;       // the driver setFavFlag is given
        unsigned int m_stat[4];   // GfMenuObjUtil::getFavoriteStat of each FAVORITE
    };
    GfMenuObjPouch2(unsigned int handle);
    virtual ~GfMenuObjPouch2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void setupSlot(ui::UIObjectAcc& acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number);
    static void updateSlotList(GfMenuItemList* items);
    static void refreshSlot(ui::UIObjectAcc& acc, unsigned int index);
    static void updateItemList(GfMenuItemList* items, ui::UISelectObjList* select, unsigned int filter, unsigned int sort);
    static void setupItemList(ui::UIObjectAcc& acc, GfMenuItemList* items);
    static void refreshItemList(ui::UIObjectAcc& acc, GfMenuItemList* items, ui::UISelectObjList* select,
                         unsigned int index);
    static void setFavFlag(unsigned int driver, unsigned int chr, mm::mtl::FixedArray<FavoriteFlag, 4>& flags,
                           const GfMenuBladeList* blades);
    bool seqFavOpen();
    bool seqFavLoop();
    bool seqFavClose();
    bool seqFavPouchIn();
    static void setupResult(ui::UIObjectAcc& acc);
    static void refreshResult(ui::UIObjectAcc& acc, const GfMenuBladeList* blades);
    static void setupFilter(ui::UIObjectAcc& acc, unsigned int filter);
    static void getFilterText(unsigned int filter, ui::UIStr& text);
    static void setupPartyInfo(ui::UIObjectAcc& acc);
    // 1.0.0's GfMenuObjPouch2::sendEvent (0x71004B7394, out of line there; 3.0.1 inlines every call): an event of
    // that type and first parameter to the handle's object
    static void sendEvent(unsigned int handle, unsigned int type, unsigned int param) {
        ui::EventData event;
        event.m_type = type;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
    static GAME_VOICE_HANDLE* procFavFlag(ui::UIObjectAcc& acc, FavoriteFlag& flag, unsigned int index,
                                          unsigned int favorite);

    GfMenuItemList* m_slotItems;                      // the pouch slots (initialize creates it: 3 rows)
    ui::UICtrlCursorSelect* m_slotCursor;             // the slots' cursor (SlotListener creates it)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // initialize creates it
    GfMenuItemList* m_items;                          // the stock list (initialize creates it)
    ui::UISelectObjList* m_select;                    // the stock list's selection (initialize creates it)
    GfMenuCallContext* m_context;                     // initialize creates it
    int m_cursorMode;                                 // the listeners set 0x18 / 0x48
    unsigned int m_filter;                            // the stock list's filter
    unsigned int m_prevFilter;
    // nonzero: the stock (favourite) list is open: the result closes LAY_fvstock_fevitem, not LAY_eqp_fevitem
    // (the name is not the original's)
    unsigned int m_fvStock;
    GfMenuCallContext* m_subContext;                  // initialize creates it
    mm::mtl::FixedArray<FavoriteFlag, 4> m_favBefore;  // the party's favourite stats before
    mm::mtl::FixedArray<FavoriteFlag, 4> m_favAfter;   // and after
    GfMenuSequence<GfMenuObjPouch2, 8> m_seq;
    unsigned int m_favIndex;                          // seqFavLoop: the party member (0 driver, then blades)
    unsigned int m_favKind;                           // seqFavLoop: the FAVORITE
    bool m_favVoice;                                  // seqFavLoop: a voice is playing
    bool m_slotActive;
    GAME_VOICE_HANDLE* m_voice;
    unsigned int m_sort;                              // the stock list's sort
    GfMenuBladeList* m_blades;                        // initialize creates it
    bool pad_3E8;
};
}  // namespace gf

#endif
