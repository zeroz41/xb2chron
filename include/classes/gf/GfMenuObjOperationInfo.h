#ifndef CLASSES_GF_GFMENUOBJOPERATIONINFO_H
#define CLASSES_GF_GFMENUOBJOPERATIONINFO_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B63C38
class GfMenuObjOperationInfo : public ::gf::GfMenuObject {
public:
    class MainListener;
    virtual ~GfMenuObjOperationInfo();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void open(unsigned int handle, unsigned int, unsigned int, unsigned int);
    static void close();
    static void setGuideDisp(bool disp);
    static void setDisp(bool disp);
    // a handle's operation guide, kept until remove (GfMenuObjSkipTime's while it is open)
    static void add(unsigned int handle, unsigned int, unsigned int, unsigned int);
    static void remove(unsigned int handle, unsigned int, unsigned int, unsigned int);
    static void setGuideText(unsigned int text, unsigned int);
    // enables or disables an action of the operation guide for the object of that handle (the parameter names are
    // not the original's: GfMenuObjDrEquip2 passes action 10)
    static void setActionEnable(unsigned int handle, unsigned int action, bool enable);
};
}  // namespace gf

#endif
