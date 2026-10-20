#ifndef CLASSES_GF_GFMENUPOUCHADAPTER_H
#define CLASSES_GF_GFMENUPOUCHADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5D808
class GfMenuPouchAdapter {
public:
    class ReferenceDriverConverter;
    virtual ~GfMenuPouchAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_PouchRemainTime();  // slot 3
};
}  // namespace gf

#endif
