#ifndef CLASSES_GF_GFMENUOBJEXPGET_EXPGETINFO_H
#define CLASSES_GF_GFMENUOBJEXPGET_EXPGETINFO_H

#include "classes/gf/GfMenuManyObjects/InfoType.h"
#include "classes/gf/GfMenuObjExpGet.h"

namespace gf {
// table 0x7100B62280: an open screen in GfMenuManyObjects' queue 4 or 5, with what opened it
class GfMenuObjExpGet::ExpGetInfo : public ::gf::GfMenuManyObjects::InfoType {
public:
    ExpGetInfo(unsigned int handle, const OpenParam& param) : InfoType(handle), m_param(param) {}
    OpenParam m_param;  // open's (the name is not the original's)
};
}  // namespace gf

#endif
