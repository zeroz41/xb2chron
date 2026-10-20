#ifndef CLASSES_GF_GFMENUWORLDMAPADAPTER_H
#define CLASSES_GF_GFMENUWORLDMAPADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5E0D8
class GfMenuWorldMapAdapter {
public:
    class ListConverter;
    class ReferenceConverter;
    virtual ~GfMenuWorldMapAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_WorldMapName();  // slot 3
};
}  // namespace gf

#endif
