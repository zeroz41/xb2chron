#ifndef CLASSES_GF_GFMENUARTSADAPTER_H
#define CLASSES_GF_GFMENUARTSADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B59CE8
class GfMenuArtsAdapter {
public:
    class ListConverter;
    class ListReferenceDriverConverter;
    class ListReferenceDriverConverterReferenceIndex;
    virtual ~GfMenuArtsAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_ArtsName();  // slot 3
};
}  // namespace gf

#endif
