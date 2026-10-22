#ifndef CLASSES_GF_GFMENUOBJMAINMENU2_H
#define CLASSES_GF_GFMENUOBJMAINMENU2_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B62FB8
class GfMenuObjMainMenu2 : public ::gf::GfMenuObject {
public:
    class ChrChangeListener;
    class CloseListener;
    class ContentsListener;
    class IndexListener;
    virtual ~GfMenuObjMainMenu2();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void setCloseKeyEnable(bool enable);
    static void setSubIndexText(unsigned int text);
};
}  // namespace gf

#endif
