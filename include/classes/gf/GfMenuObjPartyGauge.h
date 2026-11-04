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
    // 2.0.0's symbols name it. What it does: clears s_OpenDisable (GfMenuManager::unloadBchUI calls it after
    // terminating ui layer 102; reciveEvent calls it too).
    static void enableOpen();
    // 2.0.0's symbols name it. What it does: sets s_OpenDisable (caller
    // GfMenuObjBtlchOrder::ListListener::reciveEvent).
    static void disableOpen();
    // 1.0.0 symbol; 3.0.1's copy still carries a placeholder name (fn_7100456A1C), see the menu manager's renames
    static void disp(bool disp);
    // 2.0.0's symbols name them. What they do: while GfMenuObjUtil::isValidExpansion(1) or (3) holds, each sends an
    // event to "LAY_gauge" of the attached party gauge object (0x55): damage event 0x100, setLock event 0x101 with the
    // flag, setLimit event 0x102 with the value (btl::UIManager::UpdatePartyGauge calls all three).
    static void damage();
    static void setLock(bool flag);
    static void setLimit(unsigned int value);
    // 2.0.0's symbols name them. What they do: while GfMenuObjUtil::isValidExpansion(3) and
    // GfMenuReference::isIraFlag(4) hold, each sends an event to a child of the attached party gauge object:
    // dispSirenPT event 0x103 with the flag to "LAY_gauge"; setLockSirenEN event 0x101 with the flag to "LAY_siren";
    // closeSirenEN / openSirenEN event 0x22 / 0x21 (parameter 1) to "LAY_siren" (GfMenuReference::setIraSirenInfoDown /
    // setIraSirenInfoCompete call them).
    static void dispSirenPT(bool flag);
    static void setLockSirenEN(bool flag);
    static void closeSirenEN();
    static void openSirenEN();
    class GaugeListener;
    class SirenListener;
    virtual ~GfMenuObjPartyGauge();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // 2.0.0's symbols name it. While set, open, close and disp leave the gauge alone.
    static bool s_OpenDisable;
    // the slot of the control GaugeListener starts on "LAY_gauge_bar" when the third gauge fills (-1 for none;
    // the name is not the original's)
    int m_barCtrl;
};
}  // namespace gf

#endif
