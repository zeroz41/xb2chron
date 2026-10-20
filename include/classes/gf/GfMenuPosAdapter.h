#ifndef CLASSES_GF_GFMENUPOSADAPTER_H
#define CLASSES_GF_GFMENUPOSADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5D7E0
class GfMenuPosAdapter {
public:
    virtual ~GfMenuPosAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
