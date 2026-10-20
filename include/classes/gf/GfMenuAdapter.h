#ifndef CLASSES_GF_GFMENUADAPTER_H
#define CLASSES_GF_GFMENUADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B59C80
class GfMenuAdapter {
public:
    virtual ~GfMenuAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
