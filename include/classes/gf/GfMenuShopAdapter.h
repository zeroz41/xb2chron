#ifndef CLASSES_GF_GFMENUSHOPADAPTER_H
#define CLASSES_GF_GFMENUSHOPADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5D920
class GfMenuShopAdapter {
public:
    class ReferenceConverter;
    class ReferenceNumberConverter;
    virtual ~GfMenuShopAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_Name(unsigned int);  // slot 3
};
}  // namespace gf

#endif
