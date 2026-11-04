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
class GfMenuObjOCG : public ::gf::GfMenuObject {
public:
    // its two UI listeners (LAY_special's and LAY_result's)
    class MainListener;
    class ResultListener;
    GfMenuObjOCG(unsigned int handle);
    virtual ~GfMenuObjOCG();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // 2.0.0's symbols name them. seqCtrlWait waits for m_ctrl's control to end; seqAnimWait for m_animHandle's
    // animation; seqEndResult sends event 0x101 to LAY_result. Placeholder name: new in 3.0.1, nothing in 1.0.0's place
    // names it. A member because it is a job of its sequence (ResultListener::reciveEvent queues it on this object
    // after a one-frame wait when LAY_result opens).
    bool seqStartResult();
    bool seqCtrlWait();
    bool seqAnimWait();
    // 2.0.0's symbols name it.
    bool seqCloseResult();
    bool seqEndResult();
    // 2.0.0's symbols name them. Static members: they lie among this class's functions and act on its object (attached
    // object 0x90); GfMenuReference's openOCG / A48 / BAC / A4C tail-call them. openGear shows LAY_special and sends it
    // the open event; closeGear sends it the close event; openResult (when checkCCStart(context)) sends event 0x21 with
    // the two words to LAY_result and starts the call context on object 0x90; noticeExtend sends event 0x102 to
    // LAY_special. Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member as the four below
    // (it lies among this class's functions and acts on its object). What it does: shows or hides attached object 0x90
    // when it exists (setDisp of its argument). Caller: GfMenuManager's fn_7100359144.
    static void disp(bool disp);
    static void openGear();
    static void closeGear();
    static void openResult(GfMenuCallContext* context, unsigned int first, unsigned int second);
    static void noticeExtend();
    unsigned int m_count;  // cleared by the constructor (the name is not the original's)
    GfMenuSequence<GfMenuObjOCG, 16> m_seq;
    int m_ctrl;  // a control slot seqCtrlWait waits for, -1 for none (the name is not the original's)
    unsigned int m_animHandle;  // the object whose animation seqAnimWait waits for (the name is not the original's)
    // the reference adapters' numbers (the names are not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_numbers[2];
    unsigned int m_result;  // cleared by the constructor (the name is not the original's)
};
}  // namespace gf

#endif
