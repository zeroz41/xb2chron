#ifndef CLASSES_GF_TUNK_B5F9E8_H
#define CLASSES_GF_TUNK_B5F9E8_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "classes/ui/UIObjectListener.h"

namespace gf { class GfMenuIDList; }
namespace ui { class UICtrlCursorSelect; }
namespace ui { class UISelectObjList; }
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5F9E8 (no RTTI, no 1.0.0 symbol): the menu object of gf_menu_obj_announce.cpp (the file name suggests
// an announce menu)
class GfMenuObjAnnounce : public ::gf::GfMenuObject {
public:
    class MainListener;
    class TopListener;
    class PageListener;
    class ScheduleListener;
    class AlertListener;
    GfMenuObjAnnounce(unsigned int handle);
    virtual ~GfMenuObjAnnounce();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name it. What it does: registers full-screen layer 0x47 with a GfMenuTypes::Param whose m_menuId
    // is 1 (GfMenuFullScreen::registLayerParam).
    static void setCloseToDlcGift();
    // 2.0.0's symbols name it. What it does: false on menu layer 3 (GfMenuObjUtil::isValidExpansion(3)) or while
    // lbl_7100C294C0 is 0; else true when gf::GfDataAoc::getContentVersion answers >= 0 for any of 0..4. Callers: this class's
    // initialize and its listener, GfMenuObjMainMenu2::initialize (which then drops contents id 8 when it is false, id
    // 9 when it is true).
    static bool hasAnyDLC();
    // 2.0.0's symbols name them. seqCloseImage2, seqCloseImage, seqOpenImage and seqWaitImage are m_seq jobs over
    // LAY_contents_img (fades it out, swaps IMG_contents_img to m_imageIndex, fades it back in).
    bool seqCloseImage2();
    bool seqCloseImage();
    bool seqOpenImage();
    bool seqWaitImage();
    // 2.0.0's symbols name it. What it does: stops the control running on each LAY_schedule@%02d row of a page of
    // m_idList; the LAY_schedule listener calls it.
    void stopScheduleMove();
    // 2.0.0's symbols name them. What they do (the LAY_schedule listener calls them): refreshSchedule lays out the
    // LAY_schedule@%02d rows of a page of m_idList (its argument is false or true); ctrlScheduleUp and ctrlScheduleDown move the shown rows one place (towards
    // schedule_group_<n>'s layout rect, fading each to its row's alpha), count pad_308 down, clear m_mainSeq and return
    // the middle row's control slot (-1 for none); closeScheduleBody starts each row's IMG_schedule_base@%02d
    // animation, index_green when table 0x10D's "available" is 1, else index_orange.
    void refreshSchedule(bool);
    int ctrlScheduleUp();
    int ctrlScheduleDown();
    void closeScheduleBody();

    unsigned int pad_24;
    unsigned int pad_28;  // initialize: Bdat::getIdCount of table 0x10B
    unsigned int m_imageIndex;  // the IMG_contents_img image the jobs show (the name is not the original's)
    GfMenuSequence<GfMenuObjAnnounce, 4> m_seq;      // 0x30 (the name is not the original's)
    GfMenuSequence<GfMenuObjAnnounce, 4> m_mainSeq;  // 0x190 (the name is not the original's)
    // 0x2F0-0x300: what initialize creates, the destructor releases (the names are not the original's)
    ui::UISelectObjList* m_selectList;
    ui::UICtrlCursorSelect* m_cursor;  // over m_selectList
    GfMenuIDList* m_idList;            // the constructor's create
    unsigned int pad_308;  // a count ctrlScheduleUp and ctrlScheduleDown take down; the LAY_schedule listener clears it
    bool pad_30C;
    unsigned int pad_310;
    unsigned int pad_314;
};

// The listeners initialize registers on the object's layouts, each made for the object (m_owner); 2.0.0's symbols
// name them, nested classes. Each table's destructor slot is the base's, its deleting destructor a bare operator delete.
// table 0x7100B5FA30: LAY_main's listener
class GfMenuObjAnnounce::MainListener : public ::ui::UIObjectListener {
public:
    MainListener(GfMenuObjAnnounce* owner) : pad_C(), m_owner(owner) {}
    virtual ~MainListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    GfMenuObjAnnounce* m_owner;
};
// table 0x7100B5FA58: LAY_top's listener
class GfMenuObjAnnounce::TopListener : public ::ui::UIObjectListener {
public:
    TopListener(GfMenuObjAnnounce* owner) : pad_C(), m_owner(owner) {}
    virtual ~TopListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    GfMenuObjAnnounce* m_owner;
};
// table 0x7100B5FA80: LAY_page's listener
class GfMenuObjAnnounce::PageListener : public ::ui::UIObjectListener {
public:
    PageListener(GfMenuObjAnnounce* owner) : pad_C(), m_owner(owner) {}
    virtual ~PageListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    GfMenuObjAnnounce* m_owner;
};
// table 0x7100B5FAA8: LAY_schedule's listener
class GfMenuObjAnnounce::ScheduleListener : public ::ui::UIObjectListener {
public:
    ScheduleListener(GfMenuObjAnnounce* owner) : pad_C(), m_owner(owner) {}
    virtual ~ScheduleListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    GfMenuObjAnnounce* m_owner;
};
// table 0x7100B5FAD0: LAY_alert's listener
class GfMenuObjAnnounce::AlertListener : public ::ui::UIObjectListener {
public:
    AlertListener(GfMenuObjAnnounce* owner) : pad_C(), m_owner(owner) {}
    virtual ~AlertListener() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    GfMenuObjAnnounce* m_owner;
};
}  // namespace gf

#endif
