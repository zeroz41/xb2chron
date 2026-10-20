#ifndef CLASSES_GF_GFMENUWEAPONADAPTER_H
#define CLASSES_GF_GFMENUWEAPONADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5DC40
class GfMenuWeaponAdapter {
public:
    class ReferenceBladeConverter;
    class ReferenceChipConverter;
    virtual ~GfMenuWeaponAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_Name(unsigned int);  // slot 3
};
}  // namespace gf

#endif
