#ifndef CLASSES_GF_GFMENUREFERENCEITEM_H
#define CLASSES_GF_GFMENUREFERENCEITEM_H

namespace gf { class MenuItemInfo; }

namespace gf {
// table 0x7100B5FCE8
class GfMenuReferenceItem {
public:
    virtual ~GfMenuReferenceItem();  // slot 0
    virtual void getItem(gf::MenuItemInfo&) const;  // slot 2
};
}  // namespace gf

#endif
