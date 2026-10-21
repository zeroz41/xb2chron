#ifndef CLASSES_GF_GFMENUDIFFADAPTER_H
#define CLASSES_GF_GFMENUDIFFADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5BA28
class GfMenuDiffAdapter {
public:
    virtual ~GfMenuDiffAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
