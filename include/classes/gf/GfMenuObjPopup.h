#ifndef CLASSES_GF_GFMENUOBJPOPUP_H
#define CLASSES_GF_GFMENUOBJPOPUP_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectNumberPlugin.h"
#include "gf/GfMenuSequence.h"

namespace gf {
class GfMenuObjShop;
// table 0x7100B64118
class GfMenuObjPopup : public ::gf::GfMenuObject {
public:
    class MainListener;
    class PopupInfo;
    // what SCOM_POPUP's requests carry (the names are not the original's): a popup kind (SCOM_POPUP::exec holds
    // kind 7 back while a blade-create event is busy) and up to three values the create functions pass
    struct OpenParam {
        unsigned int m_type;
        unsigned int m_value[3];
    };
    GfMenuObjPopup(unsigned int handle);
    static bool open(const OpenParam& param);
    static void close(unsigned int handle);
    virtual ~GfMenuObjPopup();  // slot 0
    static void closeAll();  // closes every popup (GfMenuManyObjects::closeAll with close)
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqExecContinue();
    static void pausePickup();
    static void continuePickup(unsigned int param);

    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because the gift-icon jobs
    // (fn_710045C9E4, fn_710045CB7C) queue it on m_giftSeq with this object. What it does: clears m_giftWait and
    // answers true (the job is done).
    bool fn_710045DA2C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because reciveEvent queues it on
    // m_giftSeq with this object. What it does: plays IMG_gift_icon's "out" animation, then fn_710045DA2C.
    bool fn_710045C9E4();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because reciveEvent queues it on
    // m_giftSeq with this object. What it does: waits (false) while GfMenuManager::isFading; then shows
    // IMG_gift_icon, plays sound 0x22 and queues its "in" and "out" animations and fn_710045DA2C.
    bool fn_710045CB7C();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member because it takes an
    // OpenParam and works on the popup queue (kind 7) under the popup layer (attached object 0x76). Callers:
    // GfMenuObjBlKizunaRing::seqAchieve, GfMenuObjMercenaryReport::seqStart, fn_7100569D44. What it does: drops the
    // first queued popup whose request equals param (GfMenuManyObjects::fn_710045D604) and answers true.
    static bool fn_710045D48C(const OpenParam& param);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A static member because it works on the
    // popup queue (kind 7) under the popup layer. What it does: drops every queued popup of kind 4 or 5 whose first
    // value is value; answers whether it dropped one.
    static bool fn_710045D754(unsigned int value);

    // 1.0.0's sendOpen (out of line there, inlined in 3.0.1); defined inline in gf_menu_obj_popup.cpp: the open event (0x21) carrying a queued request
    static void sendOpen(unsigned int handle, const PopupInfo& info);
    // the queued popup `index` places after the first, or null without a queue or popups (inlined in 3.0.1; the
    // name is not the original's)
    static PopupInfo* getInfo(unsigned int index);

    bool m_open;                  // 0x24: set while a popup shows (reciveEvent); the name is not the original's
    bool m_giftWait;              // 0x25: cleared by fn_710045DA2C; the name is not the original's
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
    // 0x2F0: IMG_gift_icon's animations; the name is not the original's. A GfMenuSequence<GfMenuObjShop, 8> in the
    // original (the symbols of the addAnimJob, wait_anim and memberFuncInvoker this unit emits), on this object
    GfMenuSequence<GfMenuObjShop, 8> m_giftSeq;
};
}  // namespace gf

#endif
