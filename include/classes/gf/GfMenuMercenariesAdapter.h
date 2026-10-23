#ifndef CLASSES_GF_GFMENUMERCENARIESADAPTER_H
#define CLASSES_GF_GFMENUMERCENARIESADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuFieldSkillList.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/Delegate.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }
namespace ui { class UIStr; }

namespace gf {
// table 0x7100B5CEC8; a mercenary team (GfDataMercenaries' team id): its name, state, mission, members
class GfMenuMercenariesAdapter : public ::gf::GfMenuAdapter {
public:
    class IConverter;
    class ReferenceBladeConverter;
    class ReferenceTeamConverter;
    // per type create is given: what update shows, and the plugin it makes
    struct TypeSetup {
        bool (GfMenuMercenariesAdapter::*func)();
        GfMenuAdapter::PluginSetup plugin;
    };
    // inline: 1.0.0 has it out of line, 3.0.1 none; m_index is left as it was (1.0.0's leaves it too)
    GfMenuMercenariesAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_converter(nullptr), m_teamId(0), m_missionId(0),
          m_bladeList(nullptr), m_fieldSkillList(nullptr) {}
    virtual ~GfMenuMercenariesAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuMercenariesAdapter* create(unsigned int handle, unsigned int type, unsigned int teamId, bool changed);
    bool update_TeamName();
    bool update_TeamBlFace();
    bool update_TeamIcon();
    bool update_TeamStat();
    bool update_TeamStatColor();
    bool update_TeamWait();
    bool update_TeamMisInfo();
    bool update_TeamMisZone();
    bool update_TeamMisZoneIcon();
    bool update_TeamMisName();
    bool update_TeamMisTime();
    bool update_TeamMisComplete();
    bool update_TeamStrength();
    bool update_TeamMale();
    bool update_TeamFemale();
    bool update_TeamAnimal();
    bool update_TeamStrengthDiffIcon();
    bool update_TeamFieldSkillDiffIcon();
    bool update_TeamNameRes();
    bool update_TeamIconRes();
    bool update_TeamIconResFace();
    bool update_TeamDispNum1();
    // inline: 1.0.0 has it out of line, 3.0.1 none (the original spells it "Coverter")
    static inline GfMenuMercenariesAdapter* createFromCoverter(unsigned int handle, unsigned int type,
                                                               IConverter* converter, bool changed);
    static GfMenuMercenariesAdapter* createFromReferenceTeam(unsigned int handle, unsigned int type, bool changed);
    static GfMenuMercenariesAdapter* createFromReferenceBlade(unsigned int handle, unsigned int type,
                                                              unsigned int index, bool changed);
    // inline: 1.0.0 has it out of line, 3.0.1 none. The name of the team's leader blade's team, false for a team
    // without a leader
    static bool getTeamName(unsigned int teamId, ui::UIStr& name) {
        unsigned int leader = GfDataMercenaries::getTeamLeader(teamId);
        if (leader == 0) {
            return false;
        }
        return GfMenuObjUtil::getBladeTeamName(leader, name);
    }
    // inline: 1.0.0 has it out of line, 3.0.1 none. Whether the team is out on a mission ordered for a team or a
    // party
    bool isOrder(unsigned int teamId) {
        unsigned int mission = GfDataMercenaries::getTeamMission(teamId);
        if (mission != 0) {
            if (GfDataMercenaries::isMissionOrderTeam(mission) || GfDataMercenaries::isMissionOrderParty(mission)) {
                return true;
            }
        }
        return false;
    }
    mm::mtl::Delegate<bool()> m_update;  // its type's update_*; update shows what it returns
    IConverter* m_converter;  // update takes the team from it; owned
    unsigned short m_teamId;  // 0 shows nothing
    unsigned short m_missionId;  // the team's mission, as update last saw it (a change redraws)
    // the blades update_TeamStrength, _Male, _Female, _Animal count instead of the team's own (1.0.0's
    // createFromReferenceTeamBladeList and createFromBladeList set it, referenced; 3.0.1's linker dropped them).
    // The destructor releases it.
    GfMenuBladeList* m_bladeList;
    // the field skills update_TeamFieldSkillDiffIcon compares the team's with (1.0.0's
    // createFromReferenceTeamFieldSkillList sets it, referenced; 3.0.1's linker dropped it). The destructor releases
    // it.
    GfMenuFieldSkillList* m_fieldSkillList;
    // the content of m_fieldSkillList, or the row in m_bladeList's page, it shows (1.0.0's
    // createFromReferenceTeamFieldSkillList and createFromBladeList set it); the name is not the original's
    unsigned int m_index;
};
}  // namespace gf

#endif
