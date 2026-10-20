#ifndef CLASSES_GF_GFMENUFIELDSKILLADAPTER_H
#define CLASSES_GF_GFMENUFIELDSKILLADAPTER_H

namespace fw { class UpdateInfo; }
namespace gf { class MenuFieldSkill; }

namespace gf {
// table 0x7100B5BD58
class GfMenuFieldSkillAdapter {
public:
    class ListConverter;
    class ReferenceConverter;
    virtual ~GfMenuFieldSkillAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    virtual void update_Name(gf::MenuFieldSkill const&);  // slot 3
};
}  // namespace gf

#endif
