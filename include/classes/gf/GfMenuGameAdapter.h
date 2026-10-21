#ifndef CLASSES_GF_GFMENUGAMEADAPTER_H
#define CLASSES_GF_GFMENUGAMEADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5BE10
class GfMenuGameAdapter {
public:
    virtual ~GfMenuGameAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
