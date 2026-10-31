#ifndef CLASSES_GF_GFMENUOBJPOPUP_POPUPINFO_H
#define CLASSES_GF_GFMENUOBJPOPUP_POPUPINFO_H

#include "classes/gf/GfMenuManyObjects/InfoType.h"
#include "classes/gf/GfMenuObjPopup.h"

namespace gf {
// table 0x7100B64188: a queued popup (kind 7 of GfMenuManyObjects): the popup layer's handle and its open request
class GfMenuObjPopup::PopupInfo : public ::gf::GfMenuManyObjects::InfoType {
public:
    PopupInfo() : m_param() {}
    PopupInfo(unsigned int handle, const OpenParam& param) : InfoType(handle), m_param(param) {}
    OpenParam m_param;  // 0xC; the name is not the original's
};
}  // namespace gf

#endif
