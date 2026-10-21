#ifndef CLASSES_GF_GFMENUITEMADAPTER_H
#define CLASSES_GF_GFMENUITEMADAPTER_H

namespace fw { class UpdateInfo; }
namespace gf { class MenuItemInfo; }

namespace gf {
// a base of gf::GfMenuItemAdapter no evidence names yet
class TUnk_B5CA20 {
public:
    virtual ~TUnk_B5CA20();
    virtual void update(fw::UpdateInfo const&) = 0;
    virtual void changeItem(gf::MenuItemInfo const&) = 0;
    unsigned char pad_8[0x28];  // fields: size from where the next base starts
};
// a base of gf::GfMenuItemAdapter no evidence names yet
class TUnk_B5CA50 {
public:
    virtual void changeItem(gf::MenuItemInfo const&) = 0;
};
// table 0x7100B5CA20; base at 0x0 unknown (TUnk_B5CA20), base at 0x30 unknown (TUnk_B5CA50)
class GfMenuItemAdapter : public TUnk_B5CA20, public TUnk_B5CA50 {
public:
    class IConverter;
    class ListConverter;
    class PouchReferenceDriverConverter;
    class ReferenceBladeEquipConverter;
    class ReferenceItemConverter;
    virtual ~GfMenuItemAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void changeItem(gf::MenuItemInfo const&);  // slot 3
};
}  // namespace gf

#endif
