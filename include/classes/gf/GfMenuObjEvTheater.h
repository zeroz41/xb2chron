#ifndef CLASSES_GF_GFMENUOBJEVTHEATER_H
#define CLASSES_GF_GFMENUOBJEVTHEATER_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/FixedVector.h"

namespace gf {
class GfMenuCallContext;
class GfMenuMsgList;
class GfMenuReferenceNumber;
class GfMenuIDList;
class SDataOption;
}  // namespace gf
namespace ui { class UISelectObjList; }
namespace gf {

// table 0x7100B62040
class GfMenuObjEvTheater : public ::gf::GfMenuObject {
public:
    class HeaderListener;
    class TUnk_B62178;  // the listener of table 0x7100B62178 (unnamed)
    class SubListener;
    // TitleMenu::setupEventTheater / openEventTheater / fadeoutEventTheater pass their call context
    static bool attach(GfMenuCallContext* context);
    static void fadein(GfMenuCallContext* context);
    static void fadeout(GfMenuCallContext* context);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: its code (a bare ret) is in
    // gf_menu_obj_ev_theater's unit. What it does: nothing in 3.0.1. TitleStatePlayEvent::enter and onLeave call it
    // with w0 = 0 (the bool parameter type is not proven).
    static void fn_71003FEE10(bool flag);
    // one row of the event theater's sound settings (bdat 0x104's rows s_capRows), 2 bytes, as fn_7100404B58 pushes
    // them: the setting and its maximum (the struct and field names are not the original's; GfMenuObjOption's own
    // Level, from 1.0.0's symbols, is the same idea)
    struct Level {
        unsigned char m_level;
        unsigned char m_max;
    };
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them (they follow GfMenuObjOption's
    // convLevelListToOptionData / getDefaultLevel, with a 2-byte Level). Members: fn_7100404B58 and fn_710040457C
    // work on this object's m_levels / m_volumeLevel, fn_7100403DE4 (this object's listener) calls fn_7100404A08 and
    // fn_710040457C; the unsigned int each takes (a category, as in GfMenuObjOption's) is passed on, never read.
    // fn_7100404A08: stores levels into option: row 1 - top (Bdat::getIdTop of bdat 0x104) == 1 into the event
    // subtitle flag, row 2 - top's level / max (at most 1) * 255 into m_volume[1], and with
    // GfMenuManager::fn_71003596C0 row 3 - top == 2 into m_byte1E.
    static void fn_7100404A08(unsigned int category, const mm::mtl::FixedVector<Level, 32>& levels, SDataOption& option);
    // fn_7100404B58: clears levels and pushes bdat 0x104's "default_level" / "max_level" of rows s_capRows (the third
    // only with GfMenuManager::fn_71003596C0); with GfMenuObjUtil::fn_710048FD30(3) the third's default is 2 or 1 by
    // fw::LangUtil::getLangType and the second's is m_volumeLevel scaled to max_level (max_level when it is 0xFF).
    void fn_7100404B58(unsigned int category, mm::mtl::FixedVector<Level, 32>& levels);
    // fn_710040457C: refills m_levels with fn_7100404B58, then sets them from option (the inverse of fn_7100404A08).
    void fn_710040457C(unsigned int category, const SDataOption& option);
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
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: it reads this object's fields and
    // calls fn_7100401298 on it (inlined); fn_7100400C10 queues it with the other delegates. What it does: for a row
    // of m_weathers sets "IMG_select_set_ev_weather"'s weather icon; a row with a timezone shows it (fn_7100401298),
    // stores it in m_choices[0] and sets m_timezoneLocked, else clears it; "LAY_select_set_ev_input@01" is then gray
    // at half alpha while locked, else white; returns true.
    bool fn_710040132C(unsigned int index);
    // plays "select" on the selected row's IMG_select_frame@NN and "non" on the others (1.0.0's name)
    void refreshSelctList();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: SubListener's reciveEvent calls it
    // on its owner (x0 = this object) after it moves m_msgList's selection (event 6) and on open (0x21).
    void fn_71004016B8();
    // 0x71004047B8 (the symbols name it GfMenuObjOption::refreshLevel, but its this is this class and its only caller
    // is this class's listener) shows m_levels row by row; left out until the symbol is renamed

    // the names of the fields below are not the original's
    int m_title;  // 0x24: which TXT_header_title@%02d / TXT_header_input@%02d (from 1) HeaderListener shows
    unsigned char pad_28[0x50 - 0x28];
    GfMenuMsgList* m_msgList;  // 0x50: HeaderListener shows its selected entry's text
    // 0x58: initialize creates it for "LAY_sub" (UISelectObjList::create, rows LAY_sub_item@%02d); SubListener shows
    // LAY_sub_arrow while m_msgList holds more entries than it (the name is not the original's)
    ui::UISelectObjList* m_subObjList;
    GfMenuIDList* m_selectIdList;          // 0x60: the constructor creates it; its page index is the selected row
    ui::UISelectObjList* m_selectObjList;  // 0x68: the rows refreshSelctList animates
    unsigned char pad_70[0xA8 - 0x70];
    // 0xA8: 8-byte entries; fn_710040132C stores the selected event's timezone into entry 0's second word (what the
    // entries hold is not known; the names are not the original's)
    struct Choice {
        unsigned char pad_0[0x4];
        unsigned int m_value;
    };
    mm::mtl::FixedVector<Choice, 11> m_choices;
    // 0x108: the events' weather and timezone, by row (fn_710040132C; the names are not the original's)
    struct Weather {
        unsigned short m_weather;   // GfMenuBdat::getIconIDFromWeatherType's type
        unsigned short m_timezone;  // 0: none; else fn_7100401298's value
    };
    mm::mtl::FixedVector<Weather, 22> m_weathers;
    unsigned char pad_168[0x16C - 0x168];
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
    unsigned char pad_2CC[0x2D0 - 0x2CC];
    mm::mtl::FixedVector<Level, 32> m_levels;  // 0x2D0: the sound settings' rows (the name is not the original's)
    // 0x318: fn_7100404B58's 0..255 value for the second row (0xFF: max_level) (the name is not the original's)
    unsigned int m_volumeLevel;
    unsigned char pad_31C[0x320 - 0x31C];
    GfMenuSequence<GfMenuObjEvTheater, 4> m_seq;  // 0x320: update runs it (the name is not the original's)
    // fn_71004051EC's seconds since the preview started loading (the name is not the original's)
    float m_previewTime;  // 0x480
};
}  // namespace gf

#endif
