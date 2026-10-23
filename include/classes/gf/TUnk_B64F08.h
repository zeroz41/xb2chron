#ifndef CLASSES_GF_TUNK_B64F08_H
#define CLASSES_GF_TUNK_B64F08_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectListener.h"
#include "gf/GfMenuSequence.h"

namespace gf { class GfMenuCallContext; }
namespace gf { class GfMenuDriverList; }
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B64F08: the menu object of gf_menu_obj_vision.cpp (new in 3.0.1; nothing names the class yet). It
// works only while GfMenuObjUtil::fn_710048FD30(1) holds; its sequence shows LAY_en, LAY_arts, LAY_char and
// LAY_time one after another
class TUnk_B64F08 : public ::gf::GfMenuObject {
public:
    // what fn_7100494708 passes on as its open event's parameters (the names are not the original's)
    struct OpenParam {
        unsigned char pad_0[4];
        unsigned int m_driver;   // the event's first parameter: the listener shows that driver (0: the set one)
        unsigned short m_flag;   // its second: with m_target, the listener uses m_target
        unsigned char pad_A[6];
        unsigned long m_target;  // its last pair
    };
    TUnk_B64F08(unsigned int handle);
    virtual ~TUnk_B64F08();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they act on the object
    // attached under 0x8b (initialize attaches it) or are its sequence's jobs (m_seq calls them on this object).
    // fn_7100494708: with the context started, event 0x21 with param to the attached object (without
    // fn_710048FD30(1) it aborts the context as GfMenuCallContext::abort does).
    // fn_71004944B8 (GfMenuObjCharSelect::CharListener asks it): false for blade 0x412, else true once the game is
    // cleared or GfDataBlade::fn_7100231884() is past 2000
    static bool fn_71004944B8(int blade);
    static void fn_7100494708(GfMenuCallContext* context, const OpenParam& param);
    // fn_71004947C4: event 0x100 with value to the attached object, starting the context first when there is one
    // (without fn_710048FD30(1) it aborts the context)
    static void fn_71004947C4(unsigned int value, GfMenuCallContext* context);
    // The sequence's jobs: fn_7100494DEC shows LAY_main and hides its parts, then queues fn_7100494F1C;
    // fn_71004953CC ends the call context and waits for a result (fn_7100495470: 1 queues fn_710049553C, others
    // fn_7100495724); fn_7100495724 fades LAY_main out and queues fn_7100495960 (the fade's end) and fn_7100495918
    // (the close event); fn_7100495820 hides the parts and plays se_btl_bl_shulk19; fn_71004958B4 waits for
    // m_animHandle's animation.
    // fn_7100494F1C, fn_71004950AC and fn_710049523C fade LAY_en, LAY_arts and LAY_char in one after another (each
    // queues a 3-frame wait and the next); fn_710049553C shows IMG_eff's start animation and queues fn_7100495820,
    // fn_71004958B4 and fn_7100495918
    bool fn_7100494DEC();
    bool fn_7100494F1C();
    bool fn_71004950AC();
    bool fn_710049523C();
    bool fn_71004953CC();
    bool fn_710049553C();
    bool fn_7100495470();
    bool fn_7100495724();
    bool fn_7100495820();
    bool fn_71004958B4();
    bool fn_7100495918();
    bool fn_7100495960();
    unsigned char pad_24[4];
    GfMenuSequence<TUnk_B64F08, 16> m_seq;
    int m_ctrl;                   // the fade-out's control slot, -1 for none (the name is not the original's)
    unsigned int m_animHandle;    // the object whose animation fn_71004958B4 waits for (the name is not the original's)
    int m_result;                 // what fn_7100495470 waits for, 0 for none yet (the name is not the original's)
    GfMenuDriverList* m_drivers;  // the driver shown, as a list for the adapter (the name is not the original's)
};

// table 0x7100B64F50: TUnk_B64F08's listener (nothing names the class yet)
class TUnk_B64F50 : public ::ui::UIObjectListener {
public:
    // its code zeroes 0xC-0x1B after storing its table: its own fields, as other menus' listeners use theirs
    TUnk_B64F50(TUnk_B64F08* owner) : pad_0C(), m_owner(owner) {}
    virtual ~TUnk_B64F50() {}  // slot 0: its D1 slot is the base's destructor
    virtual void reciveEvent(ui::EventData const&, unsigned int);  // slot 2
    unsigned char pad_0C[0x10];
    TUnk_B64F08* m_owner;  // what initialize makes it for
};
}  // namespace gf

#endif
