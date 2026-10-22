#ifndef CLASSES_GF_GFMENUSKILLADAPTER_H
#define CLASSES_GF_GFMENUSKILLADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5DA38; a driver's skill (GfDataDriverSkill): its name, caption, points, unlock state
class GfMenuSkillAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ReferenceDriverConverter;
    class ReferenceDriverLineLevelConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuSkillAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuSkillAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), pad_58(), m_driverId(0), m_kizunaLine(0),
          m_kizunaLevel(0), m_round(0) {}
    virtual ~GfMenuSkillAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuSkillAdapter* create(unsigned int handle, unsigned int type, unsigned int driverId,
                                      unsigned short kizunaLine, unsigned short kizunaLevel, unsigned short round,
                                      bool changed);
    bool update_SkillName();
    bool update_SkillCaption();
    bool update_SkillPoint();
    bool update_SkillReleaseFlagIcon();
    bool update_SkillReleaseFlagColor();
    bool update_SkillReleaseFlagColorIcon();
    bool update_SkillLearnDisp();
    bool update_SkillLevelLockIcon();
    bool update_SkillLearnNum();
    bool update_SkillLearnMax();
    bool update_SkillLevelUnlockNum();
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuSkillAdapter* createFromCoverter(unsigned int handle, unsigned int type,
                                                         IConverter* converter, bool changed);
    static GfMenuSkillAdapter* createFromReferenceDriver(unsigned int handle, unsigned int type, unsigned int reference,
                                                         unsigned short kizunaLine, unsigned short kizunaLevel,
                                                         unsigned short round, bool changed);
    static GfMenuSkillAdapter* createFromReferenceDriverLineLevel(unsigned int handle, unsigned int type,
                                                                  unsigned int reference, unsigned short kizunaLine,
                                                                  unsigned short kizunaLevel, unsigned short round,
                                                                  bool changed);
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the skill from it; owned
    unsigned char pad_58[4];
    // the skill, as GfDataDriverSkill finds it
    unsigned int m_driverId;
    unsigned int m_kizunaLine;  // 5 or more shows no skill (update_SkillLevelUnlockNum shows at 5)
    unsigned int m_kizunaLevel;
    unsigned int m_round;  // not 0: the new game plus round's
};
}  // namespace gf

#endif
