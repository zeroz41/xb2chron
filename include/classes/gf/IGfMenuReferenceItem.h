#ifndef CLASSES_GF_IGFMENUREFERENCEITEM_H
#define CLASSES_GF_IGFMENUREFERENCEITEM_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace gf { class MenuItemInfo; }

namespace gf {
// table none (abstract); the counted item reference GfMenuItemAdapter::createFromReference takes (1.0.0's symbols name
// it as that parameter's type). GfMenuItemAdapter::ReferenceItemConverter reads the item through slot 2, the slot
// GfMenuReferenceItem::getItem fills.
class IGfMenuReferenceItem : public ::mm::mtl::ReferenceObject {
public:
    virtual void getItem(gf::MenuItemInfo& item) const = 0;  // slot 2
};
}  // namespace gf

#endif
