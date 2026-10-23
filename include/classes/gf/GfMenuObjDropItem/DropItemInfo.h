#ifndef CLASSES_GF_GFMENUOBJDROPITEM_DROPITEMINFO_H
#define CLASSES_GF_GFMENUOBJDROPITEM_DROPITEMINFO_H

#include "classes/gf/GfMenuManyObjects/InfoType.h"
#include "classes/gf/GfMenuObjDropItem.h"

namespace gf {
// table 0x7100B61960: an open drop item screen in GfMenuManyObjects' queue 3
class GfMenuObjDropItem::DropItemInfo : public ::gf::GfMenuManyObjects::InfoType {
public:
    DropItemInfo(unsigned int handle) : InfoType(handle) {}
};
}  // namespace gf

#endif
