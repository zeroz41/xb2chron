#ifndef CLASSES_GF_GFMENUQUESTADAPTER_H
#define CLASSES_GF_GFMENUQUESTADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5D880
class GfMenuQuestAdapter {
public:
    class ListConverter;
    class ReferenceConverter;
    virtual ~GfMenuQuestAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
