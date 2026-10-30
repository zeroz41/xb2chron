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
class TUnk_B5F9E8 : public ::gf::GfMenuObject {
public:
    TUnk_B5F9E8(unsigned int handle);
    virtual ~TUnk_B5F9E8();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies in this
    // class's unit and it takes no object. What it does: registers full-screen layer 0x47 with a GfMenuTypes::Param
    // whose m_menuId is 1 (GfMenuFullScreen::registLayerParam).
    static void fn_710038289C();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because their addresses lie in
    // this class's unit and they read its fields. fn_7100383844, fn_7100383EE8, fn_7100385460 and fn_7100385508 are
    // m_seq jobs over LAY_contents_img (fades it out, swaps IMG_contents_img to m_imageIndex, fades it back in).
    bool fn_7100383844();
    bool fn_7100383EE8();
    bool fn_7100385460();
    bool fn_7100385508();
    // Placeholder name: new in 3.0.1. What it does: stops the control running on each LAY_schedule@%02d row of a page
    // of m_idList; the LAY_schedule listener calls it.
    void fn_710038521C();
    // Placeholder names: new in 3.0.1. What they do (the LAY_schedule listener calls them): fn_710038471C lays out
    // the LAY_schedule@%02d rows of a page of m_idList (its argument is 0 or 1); fn_7100384C20 and fn_7100384E1C
    // move the shown rows one place (towards schedule_group_<n>'s layout rect, fading each to its row's alpha),
    // count pad_308 down, clear m_mainSeq and return the middle row's control slot (-1 for none); fn_7100385024
    // starts each row's IMG_schedule_base@%02d animation, index_green when table 0x10D's "available" is 1, else
    // index_orange.
    void fn_710038471C(unsigned int);
    int fn_7100384C20();
    int fn_7100384E1C();
    void fn_7100385024();

    unsigned int pad_24;
    unsigned int pad_28;  // initialize: Bdat::getIdCount of table 0x10B
    unsigned int m_imageIndex;  // the IMG_contents_img image the jobs show (the name is not the original's)
    GfMenuSequence<TUnk_B5F9E8, 4> m_seq;      // 0x30 (the name is not the original's)
    GfMenuSequence<TUnk_B5F9E8, 4> m_mainSeq;  // 0x190 (the name is not the original's)
    // 0x2F0-0x300: what initialize creates, the destructor releases (the names are not the original's)
    ui::UISelectObjList* m_selectList;
    ui::UICtrlCursorSelect* m_cursor;  // over m_selectList
    GfMenuIDList* m_idList;            // the constructor's create
    unsigned int pad_308;  // a count fn_7100384C20 and fn_7100384E1C take down; the LAY_schedule listener clears it
    bool pad_30C;
    unsigned int pad_310;
    unsigned int pad_314;
};

// The listeners initialize registers on the object's layouts, each made for the object (m_owner). No RTTI, no 1.0.0
// symbol; each table's destructor slot is the base's, its deleting destructor a bare operator delete.
// table 0x7100B5FA30: LAY_main's listener
class TUnk_B5FA30 : public ::ui::UIObjectListener {
public:
    TUnk_B5FA30(TUnk_B5F9E8* owner) : pad_C(), m_owner(owner) {}
    virtual ~TUnk_B5FA30() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    TUnk_B5F9E8* m_owner;
};
// table 0x7100B5FA58: LAY_top's listener
class TUnk_B5FA58 : public ::ui::UIObjectListener {
public:
    TUnk_B5FA58(TUnk_B5F9E8* owner) : pad_C(), m_owner(owner) {}
    virtual ~TUnk_B5FA58() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    TUnk_B5F9E8* m_owner;
};
// table 0x7100B5FA80: LAY_page's listener
class TUnk_B5FA80 : public ::ui::UIObjectListener {
public:
    TUnk_B5FA80(TUnk_B5F9E8* owner) : pad_C(), m_owner(owner) {}
    virtual ~TUnk_B5FA80() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    TUnk_B5F9E8* m_owner;
};
// table 0x7100B5FAA8: LAY_schedule's listener
class TUnk_B5FAA8 : public ::ui::UIObjectListener {
public:
    TUnk_B5FAA8(TUnk_B5F9E8* owner) : pad_C(), m_owner(owner) {}
    virtual ~TUnk_B5FAA8() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    TUnk_B5F9E8* m_owner;
};
// table 0x7100B5FAD0: LAY_alert's listener
class TUnk_B5FAD0 : public ::ui::UIObjectListener {
public:
    TUnk_B5FAD0(TUnk_B5F9E8* owner) : pad_C(), m_owner(owner) {}
    virtual ~TUnk_B5FAD0() {}  // slot 0
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_C[0x10];
    TUnk_B5F9E8* m_owner;
};
}  // namespace gf

#endif
