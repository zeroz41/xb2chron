#ifndef CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_H
#define CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5BAF0
class GfMenuElementComboAdapter {
public:
    class ReferenceRouteConverter;
    virtual ~GfMenuElementComboAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_ComboRouteColor();  // slot 3
};
}  // namespace gf

#endif
