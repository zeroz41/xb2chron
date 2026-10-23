#ifndef CLASSES_GF_GFMENUACHIEVEMENTADAPTER_H
#define CLASSES_GF_GFMENUACHIEVEMENTADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B598A8; the blade affinity chart's achievement display.
class GfMenuAchievementAdapter : public GfMenuAdapter {
public:
    class IConverter;
    class ReferenceBladeConverter;
    class ReferenceBladeLineLevelConverter;
    struct TypeSetup {
        bool (GfMenuAchievementAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    GfMenuAchievementAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), pad_58(), m_bladeId(0),
          m_kizunaLine(0), m_kizunaLevel(0) {}
    virtual ~GfMenuAchievementAdapter();
    virtual void update(const fw::UpdateInfo& info);
    static GfMenuAchievementAdapter* create(unsigned int handle, unsigned int type, unsigned int bladeId,
                                           unsigned short kizunaLine, unsigned short kizunaLevel, bool changed);
    bool update_AchievementReleaseFlagIcon();
    bool update_AchievementCategory();
    bool update_AchievementTitle();
    bool update_AchievementResult();
    bool update_AchievementIcon();
    bool update_AchievementVoiceCategory();
    bool update_AchievementVoiceAfter();
    bool update_AchievementDifficulty();
    bool update_AchievementQuest();
    bool update_AchievementSetCategory();
    bool update_AchievementSetAbilityLevel();
    bool update_AchievementTypeIcon();
    bool update_AchievementCategoryIcon();
    bool update_AchievementReleaseFlagColor();
    bool update_AchievementSkillName();
    bool update_LearnNum();
    bool update_LearnMax();
    bool update_QuestNum();
    bool update_QuestMax();
    bool update_IdeaText();
    bool update_IdeaIcon();
    bool update_QuestCaptionText();
    bool update_QuestResultText();
    bool update_KeyIcon();
    bool update_NetabareOkDisp();
    static GfMenuAchievementAdapter* createFromReferenceBlade(unsigned int handle, unsigned int type,
        unsigned int reference, unsigned short kizunaLine, unsigned short kizunaLevel, bool changed);
    static GfMenuAchievementAdapter* createFromReferenceBladeLineLevel(unsigned int handle, unsigned int type,
        unsigned int reference, unsigned short kizunaLine, unsigned short kizunaLevel, bool changed);

    // Inferred field names: update invokes the selected display callback and reads these chart coordinates
    // from the converter; create initializes them from its arguments.
    mm::mtl::Delegate<bool()> m_update;
    IConverter* m_converter;
    unsigned char pad_58[4];
    unsigned int m_bladeId;
    unsigned int m_kizunaLine;
    unsigned int m_kizunaLevel;
};
}  // namespace gf

#endif
