#ifndef CLASSES_GF_GFMENUFIELDSKILLADAPTER_H
#define CLASSES_GF_GFMENUFIELDSKILLADAPTER_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5BD58
class GfMenuFieldSkillAdapter {
public:
    class ListConverter;
    class ReferenceConverter;
    virtual ~GfMenuFieldSkillAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
};
}  // namespace gf

#endif
