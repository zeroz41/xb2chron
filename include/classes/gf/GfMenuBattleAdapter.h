#ifndef CLASSES_GF_GFMENUBATTLEADAPTER_H
#define CLASSES_GF_GFMENUBATTLEADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5A0A0
class GfMenuBattleAdapter {
public:
    class ReferenceIndexConverter;
    virtual ~GfMenuBattleAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_ArtsSlotRecast();  // slot 3
};
}  // namespace gf

#endif
