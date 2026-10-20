#ifndef CLASSES_GF_GFMENUWEAPONTYPEADAPTER_H
#define CLASSES_GF_GFMENUWEAPONTYPEADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5DDB8
class GfMenuWeaponTypeAdapter {
public:
    class ReferenceDriverConverter;
    virtual ~GfMenuWeaponTypeAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_WpnTypeName();  // slot 3
};
}  // namespace gf

#endif
