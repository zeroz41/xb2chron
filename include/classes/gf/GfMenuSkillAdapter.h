#ifndef CLASSES_GF_GFMENUSKILLADAPTER_H
#define CLASSES_GF_GFMENUSKILLADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5DA38
class GfMenuSkillAdapter {
public:
    class ReferenceDriverConverter;
    class ReferenceDriverLineLevelConverter;
    virtual ~GfMenuSkillAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_SkillName();  // slot 3
};
}  // namespace gf

#endif
