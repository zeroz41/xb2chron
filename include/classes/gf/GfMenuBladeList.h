#ifndef CLASSES_GF_GFMENUBLADELIST_H
#define CLASSES_GF_GFMENUBLADELIST_H

#include "classes/ui/UIListInfo.h"

namespace gf {
// a GfMenuBladeList's content (0xC bytes): a blade and how the list shows it
class MenuBladeInfo {
public:
    unsigned int m_blade;  // GfDataBlade's blade id (GfMenuMercenariesAdapter::update_TeamStrength)
    unsigned char pad_4[0x8];
};
}  // namespace gf

namespace gf {
// table 0x7100B5F180
class GfMenuBladeList : public ::ui::UIListInfo< ::gf::MenuBladeInfo> {
public:
    virtual ~GfMenuBladeList();  // slot 0
};
}  // namespace gf

#endif
