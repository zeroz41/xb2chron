#ifndef CLASSES_GF_GFMENUOBJPARTYSTATUS2_H
#define CLASSES_GF_GFMENUOBJPARTYSTATUS2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64088
class GfMenuObjPartyStatus2 : public ::gf::GfMenuObject {
public:
    static void open();   // 3.0.1 symbol (GfMenuObjPartyStatus::openPartyStatus calls it)
    static void close();  // 3.0.1 symbol (GfMenuObjPartyStatus::closePartyStatus calls it)
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
};
}  // namespace gf

#endif
