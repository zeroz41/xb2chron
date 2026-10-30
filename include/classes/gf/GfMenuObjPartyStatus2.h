#ifndef CLASSES_GF_GFMENUOBJPARTYSTATUS2_H
#define CLASSES_GF_GFMENUOBJPARTYSTATUS2_H

#include "classes/gf/GfMenuObject.h"

namespace ui { class UIObjectAcc; }

namespace gf {

class GfMenuRewriteNumber;

// table 0x7100B64088
class GfMenuObjPartyStatus2 : public ::gf::GfMenuObject {
public:
    GfMenuObjPartyStatus2(unsigned int handle);

    static void open();   // 3.0.1 symbol (GfMenuObjPartyStatus::openPartyStatus calls it)
    static void close();  // 3.0.1 symbol (GfMenuObjPartyStatus::closePartyStatus calls it)
    static void disp(bool disp);
    // 3.0.1 symbol: GfMenuObjExpGet::open passes a driver's party place (GfDataParty::getDriverPartyID) for its level up
    static void levelup(unsigned int party);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is in this class's
    // unit. What it does: sends the object attached as 0x5D (unless it is missing or terminating) an event 0xD with
    // parameters 3, 0, the value, 0 (GfMenuObjPartyStatus::MainListener's member change (0x109) passes the member
    // for members above 1).
    static void fn_710045A610(unsigned int value);
    class MainListener;
    virtual ~GfMenuObjPartyStatus2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4

    // the three drivers' name, level, HP and experience displays on "LAY_dr@%02d", their HP numbers rewritten
    // through the one given
    static void setupPartyStatus(ui::UIObjectAcc& acc, GfMenuRewriteNumber* rewrite);
    // a driver's frame ("LAY_dr@%02d") in and out: the control's slot goes to ctrl, its end event is 7 + index
    // (in) or 10 + index (out)
    static void movePartyFrameIn(ui::UIObjectAcc& acc, unsigned int index, int& ctrl);
    static void movePartyFrameOut(ui::UIObjectAcc& acc, unsigned int index, int& ctrl);
    // fades in the driver's name and HP number once its frame is in
    static void movePartyFrameInEnd(ui::UIObjectAcc& acc, unsigned int index);

    bool m_open;  // the listener's open (0x21) sets it, close (0x22) clears it (the name is not the original's)
    // the listener's open event makes it and the adapters rewrite through it; the destructor releases it (the name is
    // not the original's)
    GfMenuRewriteNumber* m_rewriteNumber;
    // per driver frame: movePartyFrameIn/Out's control slot (-1 for none) (the name is not the original's)
    int m_frameCtrl[3];
};
}  // namespace gf

#endif
