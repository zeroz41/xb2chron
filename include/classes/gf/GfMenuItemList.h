#ifndef CLASSES_GF_GFMENUITEMLIST_H
#define CLASSES_GF_GFMENUITEMLIST_H

#include "classes/ui/UIListInfo.h"

namespace gf { class MenuItemInfo; }

namespace gf {
// table 0x7100B5F488
class GfMenuItemList : public ::ui::UIListInfo< ::gf::MenuItemInfo> {
public:
    virtual ~GfMenuItemList();  // slot 0
};
}  // namespace gf

#endif
