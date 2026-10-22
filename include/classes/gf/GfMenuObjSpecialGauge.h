#ifndef CLASSES_GF_GFMENUOBJSPECIALGAUGE_H
#define CLASSES_GF_GFMENUOBJSPECIALGAUGE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64A68
class GfMenuObjSpecialGauge : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjSpecialGauge(unsigned int handle);
    virtual ~GfMenuObjSpecialGauge();  // slot 0
    static void push();  // event 0x10A: the listener's sound (40) while shown
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void open();   // event 0x100: fades in during battle
    static void close();  // event 0x101
    static void reverse(bool reverse);  // event 0x10B: hides the parent object when it is set
};
}  // namespace gf

#endif
