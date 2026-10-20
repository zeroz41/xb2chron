#ifndef CLASSES_GF_GFMENUMERCENARIESADAPTER_H
#define CLASSES_GF_GFMENUMERCENARIESADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5CEC8
class GfMenuMercenariesAdapter {
public:
    class ReferenceBladeConverter;
    class ReferenceTeamConverter;
    virtual ~GfMenuMercenariesAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_TeamName();  // slot 3
};
}  // namespace gf

#endif
