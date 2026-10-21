#ifndef CLASSES_GF_GFMENUHANAPARTSADAPTER_H
#define CLASSES_GF_GFMENUHANAPARTSADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5C948
class GfMenuHanaPartsAdapter {
public:
    class ListConverter;
    class ReferenceNumberConverter;
    virtual ~GfMenuHanaPartsAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
