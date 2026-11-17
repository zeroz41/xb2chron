#ifndef CLASSES_GF_GFMENUOBJPOPUP_H
#define CLASSES_GF_GFMENUOBJPOPUP_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B64118
class GfMenuObjPopup : public ::gf::GfMenuObject {
public:
    class MainListener;
    class PopupInfo;
    // what SCOM_POPUP's requests carry (the names are not the original's): a popup kind (SCOM_POPUP::exec holds
    // kind 7 back while a blade-create event is busy) and up to three values the create functions pass
    struct OpenParam {
        // the three values are separate members, not an array: seqExecContinue's open event reads the first two as
        // one 8-byte load, which the compiler only merges for neighbours at the same depth
        unsigned int m_type;
        unsigned int m_value0;
        unsigned int m_value1;
        unsigned int m_value2;
        // the same request (remove looks a queued popup up so)
        friend bool operator==(const OpenParam& a, const OpenParam& b) {
            return a.m_type == b.m_type && a.m_value0 == b.m_value0 && a.m_value1 == b.m_value1 &&
                   a.m_value2 == b.m_value2;
        }
    };
    GfMenuObjPopup(unsigned int handle);
    // the popup layer's handle (0 when nothing opened)
    static unsigned int open(const OpenParam& param);
    static void close(unsigned int handle);
    virtual ~GfMenuObjPopup();  // slot 0
    static void closeAll();  // closes every popup (GfMenuManyObjects::closeAll with close)
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqExecContinue();
    static void pausePickup();
    static void continuePickup(unsigned int param);

    // 2.0.0's symbols name it. What it does: clears m_giftWait and answers true (the job is done).
    bool seqGiftEnd();
    // 2.0.0's symbols name it. What it does: plays IMG_gift_icon's "out" animation, then seqGiftEnd.
    bool seqGiftOut();
    // 2.0.0's symbols name it. What it does: waits (false) while GfMenuManager::isFading; then shows IMG_gift_icon,
    // plays sound 0x22 and queues its "in" and "out" animations and seqGiftEnd.
    bool seqGiftIn();
    // 2.0.0's symbols name it. What it does: drops the first queued popup whose request equals param
    // (GfMenuManyObjects::removeIndex) and answers true.
    static bool remove(const OpenParam& param);
    // 2.0.0's symbols name it. What it does: drops every queued popup of kind 4 or 5 whose first value is value;
    // answers whether it dropped one.
    static bool removeBlade(unsigned int value);

    // 1.0.0's sendOpen (out of line there, inlined in 3.0.1); defined inline in gf_menu_obj_popup.cpp: the open event (0x21) carrying a queued request
    static void sendOpen(unsigned int handle, const PopupInfo& info);
    // copies the request of the queued popup `index` places after the first into param; false without a queue or
    // popups (inlined in 3.0.1; the name is not the original's)
    static bool getParam(unsigned int index, OpenParam& param);

    // set once open has sent a popup's open event (open sends no other while set; reciveEvent sets and clears it)
    static bool s_disp;

    bool m_open;                  // 0x24: set while a popup shows (reciveEvent); the name is not the original's
    bool m_giftWait;              // 0x25: cleared by seqGiftEnd; the name is not the original's
    bool pad_26;
    int m_count;                  // 0x28: reciveEvent's; the name is not the original's
    // 0x30-0x58: the number plugins of TXT_text@05_1-4, @09 and @11 (initialize); the names are not the original's
    ui::UIObjectNumberPlugin* m_number05_1;
    ui::UIObjectNumberPlugin* m_number05_2;
    ui::UIObjectNumberPlugin* m_number05_3;
    ui::UIObjectNumberPlugin* m_number05_4;
    ui::UIObjectNumberPlugin* m_number09;
    ui::UIObjectNumberPlugin* m_number11;
    GfMenuSequence<GfMenuObjPopup, 8> m_seq;      // 0x60: the name is not the original's
    // 0x2F0: IMG_gift_icon's animations; the name is not the original's. The type is 2.0.0's (the symbols of the
    // addAnimJob, wait_anim and memberFuncInvoker this unit emits)
    GfMenuSequence<GfMenuObjPopup, 8> m_giftSeq;
};
}  // namespace gf

#endif
