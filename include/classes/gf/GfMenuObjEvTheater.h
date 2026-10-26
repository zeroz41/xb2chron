#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf {
class GfMenuCallContext;
class GfMenuReferenceNumber;

// table 0x7100B62040
class GfMenuObjEvTheater : public ::gf::GfMenuObject {
public:
    class HeaderListener;
    class TUnk_B62178;  // the listener of table 0x7100B62178 (unnamed)
    // TitleMenu::setupEventTheater / openEventTheater / fadeoutEventTheater pass their call context
    static bool attach(GfMenuCallContext* context);
    static void fadein(GfMenuCallContext* context);
    static void fadeout(GfMenuCallContext* context);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code (a bare ret) is in
    // gf_menu_obj_ev_theater's unit. What it does: nothing in 3.0.1. TitleStatePlayEvent::enter and onLeave call it
    // with w0 = 0 (the bool parameter type is not proven).
    static void fn_71003FEE10(bool flag);
    virtual ~GfMenuObjEvTheater();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // Placeholder names: new in 3.0.1 (1.0.0's unit has no such functions). Members: fn_7100400C10 (a member: it reads
    // this object's fields) queues each one as a delegate on this object, with a parameter, in the 3-entry
    // delegate list at 0x88; they return true.
    // What it does: sets "IMG_select_set_ev_timezone"'s image from the 3-entry table s_timezoneImages: entry
    // m_timezone - 1 when m_timezone is set, else entry `value` (and clears m_timezoneFromList); returns false
    // without touching it while m_timezoneLocked is set.
    bool fn_7100401298(unsigned int value);
    // What it does: sets "IMG_select_set_ev_face"'s image to GfMenuBdat::getIconImageIndex(value != 0 ? 0xD0 : 0xCF).
    bool fn_7100401538(unsigned int value);
    // What it does: sets "IMG_select_set_bl_elem"'s image to GfMenuBdat::getIconImageIndex(s_elementIcons[value])
    // (7 icon ids 0x9F..0xA4, 0xA6).
    bool fn_7100401598(unsigned int value);
    // What it does: sets "IMG_select_set_bl_face"'s image to GfMenuBdat::getIconImageIndex(offset + m_faceIcon): the
    // offset is `value`, or for m_faceIcon 0x10E value + 1 wrapped to 0 past 3.
    bool fn_71004015F8(unsigned int value);
    // What it does: stores `value` into m_number's value.
    bool fn_710040166C(unsigned int value);
    // Placeholder name: new in 3.0.1. A member: the unnamed listener's reciveEvent fn_7100404E14 queues it as a job
    // of its owner's m_seq. What it does: sends event 0x105 to "LAY_preview"; returns true.
    bool fn_7100405294();
    // Placeholder name: new in 3.0.1. A member: the unnamed listener's reciveEvent fn_7100404E14 queues it as a job
    // of its owner's m_seq. What it does: adds GfMenuManager::getUpdateDT() to m_previewTime; while that is under 5
    // and "IMG_preview" is still streaming returns false, else fades "LAY_preview" in (setCommonFadeIn(handle, 1, 0)),
    // clears m_previewTime and returns true.
    bool fn_71004051EC();
    // Placeholder name: new in 3.0.1. A member: the unnamed listener's reciveEvent fn_7100403DE4 calls it (its x0
    // holds this object's fields 0x2C0/0x2C8, which the constructor clears). What it does: when the UI object
    // m_capHandle exists, sets its text to bdat 0x136's message whose id is m_capBdat's "cap_id" at row
    // s_capRows[index] (3 rows: 1, 2, 9).
    void fn_7100404720(unsigned int index);

    unsigned char pad_24[0x16C - 0x24];
    // fn_7100401298 shows timezone image m_timezone - 1 when it is set (the name is not the original's)
    unsigned int m_timezone;  // 0x16C
    unsigned char pad_170[0x178 - 0x170];
    // fn_71004015F8's base icon id for "IMG_select_set_bl_face"; fn_7100400C10 sets it from a 4-entry table by
    // the entry at 0x174 (the name is not the original's)
    unsigned int m_faceIcon;  // 0x178
    unsigned char pad_17C[0x180 - 0x17C];
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // 0x180: the constructor creates it (the name is not the original's)
    // fn_7100401298 does nothing while it is set; fn_7100400C10 clears it (the name is not the original's)
    bool m_timezoneLocked;  // 0x188
    // fn_7100401298 clears it when it shows the list's timezone (the name is not the original's)
    bool m_timezoneFromList;  // 0x189
    unsigned char pad_18A[0x2C0 - 0x18A];
    unsigned char* m_capBdat;  // 0x2C0: the table fn_7100404720 reads "cap_id" from (the name is not the original's)
    unsigned int m_capHandle;  // 0x2C8: the UI object fn_7100404720 sets the text of (the name is not the original's)
    unsigned char pad_2CC[0x320 - 0x2CC];
    GfMenuSequence<GfMenuObjEvTheater, 4> m_seq;  // 0x320: update runs it (the name is not the original's)
    // fn_71004051EC's seconds since the preview started loading (the name is not the original's)
    float m_previewTime;  // 0x480
};
}  // namespace gf

#endif
