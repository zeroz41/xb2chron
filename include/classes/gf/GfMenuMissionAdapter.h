#ifndef CLASSES_GF_GFMENUMISSIONADAPTER_H
#define CLASSES_GF_GFMENUMISSIONADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "mm/mtl/Delegate.h"
#include "gf/GfDataMercenaries.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace gf { class GfMenuBladeList; }

namespace gf {
// table 0x7100B5D200; create constructs it as a GfMenuAdapter, then installs this table. A mercenary mission's
// display.
class GfMenuMissionAdapter : public ::gf::GfMenuAdapter {
public:
    // where update takes the mission from (1.0.0's IConverter; its slot 2 gives the mission id)
    class IConverter {
    public:
        virtual ~IConverter();  // slot 0
        virtual unsigned int getMissionId() = 0;  // slot 2
    };
    class ListConverter;
    class MissionListConverter;
    class ReferenceConverter;
    class ReferenceMissionConverter;
    // a display callback and the plugin create makes for it (the table at 0x7100B5D228, in create's type order)
    struct TypeSetup {
        bool (GfMenuMissionAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    GfMenuMissionAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_update(), m_converter(nullptr), m_missionId(0), m_stat(0),
          pad_60(), m_condType(0), m_bladeList(nullptr), m_slot(0) {}
    virtual ~GfMenuMissionAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuMissionAdapter* create(unsigned int handle, unsigned int type, unsigned int mission, bool changed);
    // inline: 1.0.0 has it out of line (0x71003AE890, then complete was 2), 3.0.1 none. Where the mission stands:
    // 0 open, 1 a team (or with party, the party) is on it, 2 its team is back with the reward, 3 complete
    int getStat(unsigned int mission, bool party) {
        unsigned int team = GfDataMercenaries::getTeamIDByMissionID(mission);
        if (team == 0 && party && GfDataMercenaries::isMissionOrderParty(mission)) {
            return 1;
        }
        if (team != 0) {
            return GfDataMercenaries::isTeamStateReward(team) ? 2 : 1;
        }
        return GfDataMercenaries::isMissionComplete(mission) ? 3 : 0;
    }
    bool update_MissionName();
    // Placeholder names: one of them is 1.0.0's update_MissionSummary (the callback after update_MissionName), the
    // other is new in 3.0.1; nothing yet tells which. Members because they are entries 1 and 2 of this class's
    // TypeSetup table (text plugins). What they do: show the mission's summary (GfDataMercenaries::
    // getMsgSummaryName) or, for a complete mission or a team back with its reward, its quest's result
    // (GfDataQuest::getResult of GfDataMercenaries::getMissionQuestID); fn_7100345648 takes the result only for a
    // complete mission with no team.
    bool fn_7100345570();
    bool fn_7100345648();
    bool update_MissionCategoryIcon();
    bool update_MissionTime();
    bool update_MissionTimeRemain();
    bool update_MissionStatusIcon();
    bool update_MissionStatus();
    bool update_MissionStatusColor();
    bool update_MissionRewardGold();
    bool update_MissionRewardGoldBonus();
    bool update_MissionRewardExp();
    bool update_MissionRewardZone();
    bool update_MissionRewardZonePoint();
    bool update_MissionRewardZonePointBonus();
    bool update_MissionRewardIdeaPoint();
    bool update_MissionRewardMerPoint();
    bool update_MissionFieldSkill();
    bool update_MissionCond();
    bool update_MissionCondIcon();
    bool update_MissionCondParam();
    bool update_MissionCondLv();
    bool update_MissionCondParamIcon();
    bool update_MissionCondBladeMax();
    bool update_MissionCondBladeCount();
    bool update_MissionCondCheckIcon();
    bool update_MissionCondCheckDisp();
    bool update_MissionTeamIcon();
    bool update_MissionPartyIcon();
    bool update_MissionStateIcon();
    bool update_MissionNewDisp();
    bool update_MissionProgressDisp();
    bool update_MissionFieldSkillDisp();
    bool update_MissionFieldSkillColor();
    bool update_MemberFieldSkillLv();
    bool update_MemberFieldSkillColor();
    bool update_MissionTimeOriginal();
    bool update_MissionTimeAdjust();
    bool update_MissionFieldSkillLevelCount();
    bool update_MissionFieldSkillBladeCount();
    bool update_MissionFieldSkillBladeMax();

    // the field names are not the original's: create sets the callback and the mission, update takes the
    // mission from the converter and keeps getStat's answer
    mm::mtl::Delegate<bool()> m_update;
    IConverter* m_converter;  // owned
    unsigned int m_missionId;
    int m_stat;  // getStat(m_missionId, false) as update last saw it
    unsigned char pad_60[0x4];
    int m_condType;  // update_MissionCondParamIcon shows the condition only when it is of this type
    GfMenuBladeList* m_bladeList;  // referenced; the blades the condition callbacks count
    int m_slot;  // the condition or field skill slot the callbacks show (0..2)
};
}  // namespace gf

#endif
