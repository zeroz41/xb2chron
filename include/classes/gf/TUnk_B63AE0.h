#ifndef CLASSES_GF_TUNK_B63AE0_H
#define CLASSES_GF_TUNK_B63AE0_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GfMenuReferenceNumber; }
namespace gf { class GfMenuCallContext; }

namespace gf {
// table 0x7100B63AE0: the menu object of gf_menu_obj_ocg.cpp (new in 3.0.1; nothing names the class yet). It shows
// LAY_special's counts and LAY_result's totals (dlc240_result)
class TUnk_B63AE0 : public ::gf::GfMenuObject {
public:
    // its two UI listeners (LAY_special's and LAY_result's)
    class TUnk_B63B28;
    class TUnk_B63B50;
    TUnk_B63AE0(unsigned int handle);
    virtual ~TUnk_B63AE0();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they are its sequence's
    // jobs (m_seq calls them on this object). fn_710044A304 waits for m_ctrl's control to end; fn_710044A348 for
    // m_animHandle's animation; fn_710044A5DC sends event 0x101 to LAY_result.
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is a job of its sequence
    // (TUnk_B63B50::reciveEvent queues it on this object after a one-frame wait when LAY_result opens).
    bool fn_7100449E78();
    bool fn_710044A304();
    bool fn_710044A348();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is a job of its sequence
    // (fn_7100449E78 queues it): plays IMG_result_base's "end" and fades the totals out, then queues the waits and
    // fn_710044A5DC.
    bool fn_710044A3AC();
    bool fn_710044A5DC();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Static members: they lie among this
    // class's functions and act on its object (attached object 0x90); GfMenuReference's fn_7100368A44 / A48 / BAC /
    // A4C tail-call them. fn_7100448E58 shows LAY_special and sends it the open event; fn_7100448ED4 sends it the
    // close event; fn_7100448F44 (when checkCCStart(context)) sends event 0x21 with the two words to LAY_result and
    // starts the call context on object 0x90; fn_7100448FFC sends event 0x102 to LAY_special.
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member as the four below (it lies
    // among this class's functions and acts on its object). What it does: shows or hides attached object 0x90 when
    // it exists (setDisp of its argument). Caller: GfMenuManager's fn_7100359144.
    static void fn_7100448E04(bool disp);
    static void fn_7100448E58();
    static void fn_7100448ED4();
    static void fn_7100448F44(GfMenuCallContext* context, unsigned int first, unsigned int second);
    static void fn_7100448FFC();
    unsigned int m_count;  // cleared by the constructor (the name is not the original's)
    GfMenuSequence<TUnk_B63AE0, 16> m_seq;
    int m_ctrl;  // a control slot fn_710044A304 waits for, -1 for none (the name is not the original's)
    unsigned int m_animHandle;  // the object whose animation fn_710044A348 waits for (the name is not the original's)
    // the reference adapters' numbers (the names are not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numbers[2];
    unsigned int m_result;  // cleared by the constructor (the name is not the original's)
};
}  // namespace gf

#endif
