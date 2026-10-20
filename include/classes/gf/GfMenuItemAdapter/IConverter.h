#ifndef CLASSES_GF_GFMENUITEMADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUITEMADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuItemAdapter.h"

namespace gf { class MenuItemInfo; }

namespace gf {
// table none (its derived classes')
class GfMenuItemAdapter::IConverter {
public:
    virtual ~IConverter();  // slot 0
    virtual void getItemInfo(gf::MenuItemInfo&) = 0;  // slot 2
    virtual void fromList();  // slot 3
    virtual void fromPouch();  // slot 4
    virtual void fromMission();  // slot 5
};
}  // namespace gf

#endif
