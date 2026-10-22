#ifndef CLASSES_GF_GFMENUFIELDSKILLADAPTER_H
#define CLASSES_GF_GFMENUFIELDSKILLADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuFieldSkillList.h"
#include "classes/gf/GfMenuReferenceFs.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5BD58; a field skill: its name or level
class GfMenuFieldSkillAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ListConverter;
    class ReferenceConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuFieldSkillAdapter::*func)(const MenuFieldSkill& skill);
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuFieldSkillAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), m_skill() {}
    virtual ~GfMenuFieldSkillAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuFieldSkillAdapter* create(unsigned int handle, unsigned int type, const MenuFieldSkill& skill);
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter"; 1.0.0 does not use changed)
    static inline GfMenuFieldSkillAdapter* createFromCoverter(unsigned int handle, unsigned int type,
                                                              IConverter* converter, bool changed);
    static GfMenuFieldSkillAdapter* createFromList(unsigned int handle, unsigned int type, GfMenuFieldSkillList* list,
                                                   int index);
    static GfMenuFieldSkillAdapter* createFromReference(unsigned int handle, unsigned int type,
                                                        mm::mtl::IntrusivePtr<GfMenuReferenceFs> reference);
    bool update_Name(const MenuFieldSkill& skill);
    bool update_Lv(const MenuFieldSkill& skill);
    mm::mtl::Delegate<bool(const MenuFieldSkill&)> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the skill from it; owned
    MenuFieldSkill m_skill;   // an id of 0 shows nothing
};
}  // namespace gf

#endif
