#ifndef CLASSES_GF_GFMENUITEMADAPTER_REFERENCEITEMCONVERTER_H
#define CLASSES_GF_GFMENUITEMADAPTER_REFERENCEITEMCONVERTER_H

#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuItemAdapter/IConverter.h"

namespace gf { class MenuItemInfo; }

namespace gf {
// table 0x7100B5CDC8
class GfMenuItemAdapter::ReferenceItemConverter : public ::gf::GfMenuItemAdapter::IConverter {
public:
    virtual ~ReferenceItemConverter();  // slot 0
    virtual void getItemInfo(gf::MenuItemInfo&);  // slot 2
};
}  // namespace gf

#endif
