#ifndef CLASSES_UI_TUNK_B74610_H
#define CLASSES_UI_TUNK_B74610_H

#include "classes/ui/UICtrlObject.h"
#include "mm/mtl/Vector.h"

namespace fw { class UpdateInfo; }
namespace mm { namespace mtl { class IAllocator; } }

namespace ui {
// table 0x7100B74610 (no RTTI; ui_ctrl_roll.cpp's control, so possibly "UICtrlRoll": the name is not the
// original's). Turns objects round the centre of the object it controls: each entry's object is placed on a circle
// of its radius, its angle advancing by its speed every update. The names of the fields are not the original's.
class UICtrlRoll : public ::ui::UICtrlObject {
public:
    // create's: where the entries' room comes from and how many entries it holds. A user constructor (the control's
    // constructor zeroes it as 8 + 4 bytes, and create's copy is 12 bytes, not 16: an assignment copies a non-POD
    // class's data size)
    struct Setting {
        Setting() : m_allocator(nullptr), m_count(0) {}
        ::mm::mtl::IAllocator* m_allocator;
        unsigned int m_count;
    };
    // one object's circle (fn_7100672168's)
    struct RollParam {
        bool m_reverse;            // true: the angle grows (wrapping past 360), false: it shrinks (wrapping below 0)
        unsigned int m_radius;     // the distance from the centre
        float m_startAngle;        // the angle the entry starts at (degrees)
        float m_speed;             // degrees per update
    };
    struct Entry {
        RollParam m_param;
        unsigned int m_handle;  // the object it turns
        float m_angle;          // its angle now (degrees)
    };

    UICtrlRoll(unsigned int handle) : UICtrlObject(handle), m_setting(), m_paused(false) {}
    virtual ~UICtrlRoll();  // slot 0
    virtual void update(const fw::UpdateInfo& info);  // slot 2

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. Static: the control's creator (its only
    // caller fn_710041D568 passes a handle and a {allocator, count} pair). What it does: allocates 0x70 bytes from
    // UIUtil::getProgAllocator() (ui_ctrl_roll.cpp line 46), constructs the control on handle, copies the setting,
    // gives the entry list the setting's allocator and room for count entries, empties it.
    static UICtrlRoll* fn_7100672020(unsigned int handle, const Setting& setting);
    // 2.0.0's symbols name it. What it does: empties the entry list (size 0).
    void reset();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member: works on this control's entry
    // list (caller gf::GfMenuObjHitonowa::refreshComplete). What it does: unless the list is full, gives the entry of
    // object handle the new parameters, or adds an entry for it starting at the parameters' start angle.
    void fn_7100672168(unsigned int handle, const RollParam& param);
    // 2.0.0's symbols name it. What it does: unless the list is full, erases the first entry of object handle.
    void delObject(unsigned int handle);
    // 2.0.0's symbols name it. What it does: stores the bool at 0x68; while it is set update moves nothing.
    void pause(bool paused);

    Setting m_setting;
    ::mm::mtl::Vector<Entry> m_entries;
    bool m_paused;
};
}  // namespace ui

#endif
