#ifndef CLASSES_GF_GFMENUREFERENCEADAPTER_H
#define CLASSES_GF_GFMENUREFERENCEADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5D8F8
class GfMenuReferenceAdapter {
public:
    virtual ~GfMenuReferenceAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
