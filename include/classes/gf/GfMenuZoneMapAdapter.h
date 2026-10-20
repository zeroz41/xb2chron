#ifndef CLASSES_GF_GFMENUZONEMAPADAPTER_H
#define CLASSES_GF_GFMENUZONEMAPADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5E350
class GfMenuZoneMapAdapter {
public:
    class ListConverter;
    virtual ~GfMenuZoneMapAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_ZoneMapName();  // slot 3
};
}  // namespace gf

#endif
