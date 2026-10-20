#ifndef CLASSES_GF_GFMENUITEMADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUITEMADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuItemAdapter/IConverter.h"

namespace gf { class MenuItemInfo; }

namespace gf {
// table 0x7100B5CD88
class GfMenuItemAdapter::ListConverter : public ::gf::GfMenuItemAdapter::IConverter {
public:
    virtual ~ListConverter();  // slot 0
    virtual void getItemInfo(gf::MenuItemInfo&);  // slot 2
    virtual void fromList();  // slot 3
};
}  // namespace gf

#endif
