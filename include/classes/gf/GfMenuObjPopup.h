#ifndef CLASSES_GF_GFMENUOBJPOPUP_H
#define CLASSES_GF_GFMENUOBJPOPUP_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
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
    static bool open(const OpenParam& param);
    virtual ~GfMenuObjPopup();  // slot 0
    static void closeAll();  // closes every popup (GfMenuManyObjects::closeAll with close)
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
