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
};
}  // namespace gf

#endif
