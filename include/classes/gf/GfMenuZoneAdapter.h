#ifndef CLASSES_GF_GFMENUZONEADAPTER_H
#define CLASSES_GF_GFMENUZONEADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5E1F8
class GfMenuZoneAdapter {
public:
    class ReferenceNumberConverter;
    class ReferenceZoneConverter;
    virtual ~GfMenuZoneAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_ZoneName();  // slot 3
};
}  // namespace gf

#endif
