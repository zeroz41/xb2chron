#ifndef CLASSES_GF_GFMENUHANAADAPTER_H
#define CLASSES_GF_GFMENUHANAADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5C778
class GfMenuHanaAdapter {
public:
    class ReferenceIndexConverter;
    virtual ~GfMenuHanaAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
