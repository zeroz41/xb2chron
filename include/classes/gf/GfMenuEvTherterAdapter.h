#ifndef CLASSES_GF_GFMENUEVTHERTERADAPTER_H
#define CLASSES_GF_GFMENUEVTHERTERADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5BC28
class GfMenuEvTherterAdapter {
public:
    class ListConverter;
    virtual ~GfMenuEvTherterAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_Title(unsigned int);  // slot 3
};
}  // namespace gf

#endif
