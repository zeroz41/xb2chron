#ifndef CLASSES_GF_GFMENUOBJPOPUP_H
#define CLASSES_GF_GFMENUOBJPOPUP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64118
class GfMenuObjPopup : public ::gf::GfMenuObject {
public:
    class MainListener;
    class PopupInfo;
    virtual ~GfMenuObjPopup();  // slot 0
    static void closeAll();  // closes every popup (GfMenuManyObjects::closeAll with close)
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
