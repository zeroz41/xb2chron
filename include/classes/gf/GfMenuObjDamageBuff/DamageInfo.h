#ifndef CLASSES_GF_GFMENUOBJDAMAGEBUFF_DAMAGEINFO_H
#define CLASSES_GF_GFMENUOBJDAMAGEBUFF_DAMAGEINFO_H

#include "classes/gf/GfMenuManyObjects/InfoType.h"
#include "classes/gf/GfMenuObjDamageBuff.h"

namespace gf {
// table 0x7100B617D0: an open screen in GfMenuManyObjects' queue 1
class GfMenuObjDamageBuff::DamageInfo : public ::gf::GfMenuManyObjects::InfoType {
public:
    DamageInfo(unsigned int handle) : InfoType(handle) {}
};
}  // namespace gf

#endif
