#ifndef CLASSES_GF_GFMENUACHIEVEMENTADAPTER_H
#define CLASSES_GF_GFMENUACHIEVEMENTADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B598A8
class GfMenuAchievementAdapter {
public:
    class ReferenceBladeConverter;
    class ReferenceBladeLineLevelConverter;
    virtual ~GfMenuAchievementAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
