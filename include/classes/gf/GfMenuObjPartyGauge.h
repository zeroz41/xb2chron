#ifndef CLASSES_GF_GFMENUOBJPARTYGAUGE_H
#define CLASSES_GF_GFMENUOBJPARTYGAUGE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63F40
class GfMenuObjPartyGauge : public ::gf::GfMenuObject {
public:
    GfMenuObjPartyGauge(unsigned int handle);
    static void open();   // 1.0.0 symbol
    static void close();  // 1.0.0 symbol
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies in this
    // class's unit. What it does: clears s_locked (GfMenuManager::fn_710035CE3C calls it after terminating ui layer
    // 102; reciveEvent calls it too).
    static void fn_71004569F8();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address lies in this
    // class's unit, next to fn_71004569F8. What it does: sets s_locked (caller fn_71003AF9CC).
    static void fn_7100456A08();
    // 1.0.0 symbol; 3.0.1's copy still carries a placeholder name (fn_7100456A1C), see the menu manager's renames
    static void disp(bool disp);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because their addresses lie in
    // this class's unit. What they do: while GfMenuObjUtil::fn_710048FD30(1) or (3) holds, each sends an event to
    // "LAY_gauge" of the attached party gauge object (0x55): fn_7100456AC8 event 0x100, fn_7100456B60 event 0x101
    // with the flag, fn_7100456C0C event 0x102 with the value (btl::UIManager::fn_71000B2238 calls all three).
    static void fn_7100456AC8();
    static void fn_7100456B60(bool flag);
    static void fn_7100456C0C(int value);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because their addresses lie in
    // this class's unit. What they do: while GfMenuObjUtil::fn_710048FD30(3) and GfMenuReference::fn_7100368418(4)
    // hold, each sends an event to a child of the attached party gauge object: fn_7100456CB4 event 0x103 with the
    // flag to "LAY_gauge"; fn_7100456EA0 event 0x101 with the flag to "LAY_siren"; fn_7100456E00 / fn_7100456D60
    // event 0x22 / 0x21 (parameter 1) to "LAY_siren" (GfMenuReference::fn_7100368570 / fn_7100368600 call them).
    static void fn_7100456CB4(bool flag);
    static void fn_7100456EA0(bool flag);
    static void fn_7100456E00();
    static void fn_7100456D60();
    class GaugeListener;
    class TUnk_B63FC8;
    virtual ~GfMenuObjPartyGauge();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAB929). While set, open, close and
    // disp leave the gauge alone.
    static bool s_locked;
    // the slot of the control GaugeListener starts on "LAY_gauge_bar" when the third gauge fills (-1 for none;
    // the name is not the original's)
    int m_barCtrl;
};
}  // namespace gf

#endif
