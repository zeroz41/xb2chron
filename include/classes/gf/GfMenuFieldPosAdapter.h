#ifndef CLASSES_GF_GFMENUFIELDPOSADAPTER_H
#define CLASSES_GF_GFMENUFIELDPOSADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5BD30
class GfMenuFieldPosAdapter {
public:
    virtual ~GfMenuFieldPosAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
