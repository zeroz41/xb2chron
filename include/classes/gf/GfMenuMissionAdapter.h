#ifndef CLASSES_GF_GFMENUMISSIONADAPTER_H
#define CLASSES_GF_GFMENUMISSIONADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5D200
class GfMenuMissionAdapter {
public:
    class ListConverter;
    class MissionListConverter;
    class ReferenceConverter;
    class ReferenceMissionConverter;
    virtual ~GfMenuMissionAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
