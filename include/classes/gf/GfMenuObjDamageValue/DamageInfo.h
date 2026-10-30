#ifndef CLASSES_GF_GFMENUOBJDAMAGEVALUE_DAMAGEINFO_H
#define CLASSES_GF_GFMENUOBJDAMAGEVALUE_DAMAGEINFO_H

#include "classes/gf/GfMenuManyObjects/InfoType.h"
#include "classes/gf/GfMenuObjDamageValue.h"
#include "mm/Vec3.h"

namespace gf {
// table 0x7100B61878: an open damage value screen in GfMenuManyObjects' queue 0, with its position
class GfMenuObjDamageValue::DamageInfo : public ::gf::GfMenuManyObjects::InfoType {
public:
    DamageInfo(unsigned int handle, const mm::Vec3& pos) : InfoType(handle), m_pos(pos) {}
    mm::Vec3 m_pos;  // open's (it moves a new one that would show on an open one); the name is not the original's
};
}  // namespace gf

#endif
