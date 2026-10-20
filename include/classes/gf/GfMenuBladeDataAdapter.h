#ifndef CLASSES_GF_GFMENUBLADEDATAADAPTER_H
#define CLASSES_GF_GFMENUBLADEDATAADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5A648
class GfMenuBladeDataAdapter {
public:
    virtual void vf0();  // slot 0
    virtual void vf1();  // slot 1
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void vf3();  // slot 3
};
}  // namespace gf

#endif
