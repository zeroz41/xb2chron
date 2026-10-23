#include "classes/gf/GfMenuMissionAdapter.h"
#include "gf/GfDataMercenaries.h"
#include "classes/gf/GfGameMercenaries.h"
#include "ui/UIStr.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"

namespace gf {

// Display callback and plugin settings for each adapter type, in create's index order.
static GfMenuMissionAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuMissionAdapter::update_MissionName, {2, 0, 0}},
    {&GfMenuMissionAdapter::fn_7100345570, {2, 0, 0}},
    {&GfMenuMissionAdapter::fn_7100345648, {2, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionCategoryIcon, {1, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionTime, {7, 3, 0}},
    {&GfMenuMissionAdapter::update_MissionTimeRemain, {7, 3, 0}},
    {&GfMenuMissionAdapter::update_MissionStatusIcon, {1, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionStatus, {2, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionStatusColor, {8, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionRewardGold, {0, 0, 999999999}},
    {&GfMenuMissionAdapter::update_MissionRewardGoldBonus, {0, 0, 999999999}},
    {&GfMenuMissionAdapter::update_MissionRewardExp, {0, 0, 999999999}},
    {&GfMenuMissionAdapter::update_MissionRewardZone, {2, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionRewardZonePoint, {0, 0, 99999}},
    {&GfMenuMissionAdapter::update_MissionRewardZonePointBonus, {0, 0, 99999}},
    {&GfMenuMissionAdapter::update_MissionRewardIdeaPoint, {0, 0, 9999}},
    {&GfMenuMissionAdapter::update_MissionRewardMerPoint, {0, 0, 99999}},
    {&GfMenuMissionAdapter::update_MissionFieldSkill, {2, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionCond, {2, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionCondIcon, {1, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionCondParam, {0, 0, 99}},
    {&GfMenuMissionAdapter::update_MissionCondLv, {0, 0, 9}},
    {&GfMenuMissionAdapter::update_MissionCondParamIcon, {1, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionCondBladeMax, {0, 0, 6}},
    {&GfMenuMissionAdapter::update_MissionCondBladeCount, {0, 0, 144}},
    {&GfMenuMissionAdapter::update_MissionCondCheckIcon, {1, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionCondCheckDisp, {3, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionTeamIcon, {1, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionPartyIcon, {1, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionStateIcon, {1, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionNewDisp, {3, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionProgressDisp, {3, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionFieldSkillDisp, {3, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionFieldSkillColor, {8, 0, 0}},
    {&GfMenuMissionAdapter::update_MemberFieldSkillLv, {0, 0, 0}},
    {&GfMenuMissionAdapter::update_MemberFieldSkillColor, {8, 0, 0}},
    {&GfMenuMissionAdapter::update_MissionTimeOriginal, {7, 3, 0}},
    {&GfMenuMissionAdapter::update_MissionTimeAdjust, {7, 3, 0}},
    {&GfMenuMissionAdapter::update_MissionFieldSkillLevelCount, {0, 0, 594}},
    {&GfMenuMissionAdapter::update_MissionFieldSkillBladeCount, {0, 0, 6}},
    {&GfMenuMissionAdapter::update_MissionFieldSkillBladeMax, {0, 0, 6}},
};

GfMenuMissionAdapter* GfMenuMissionAdapter::create(unsigned int handle, unsigned int type, unsigned int mission,
                                                   bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 234
    GfMenuMissionAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuMissionAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_missionId = mission;
    plugin->release();
    return adapter;
}

bool GfMenuMissionAdapter::update_MissionName() {
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataMercenaries::getMsgTitleName(bdat, id, m_missionId)) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuMissionAdapter::update_MissionCategoryIcon() {
    setNumber(GfDataMercenaries::isOrderOnlyOne(m_missionId) ? 2 : 1);
    return true;
}

bool GfMenuMissionAdapter::update_MissionRewardGold() {
    bool team = GfDataMercenaries::isMissionOrderTeam(m_missionId);
    setNumber(GfGameMercenaries::getRewardGold(m_missionId, team));
    return true;
}

bool GfMenuMissionAdapter::update_MissionRewardGoldBonus() {
    bool team = GfDataMercenaries::isMissionOrderTeam(m_missionId);
    setNumber(GfGameMercenaries::getRewardGoldHosei(m_missionId, team));
    return true;
}

bool GfMenuMissionAdapter::update_MissionRewardExp() {
    bool team = GfDataMercenaries::isMissionOrderTeam(m_missionId);
    setNumber(GfGameMercenaries::getRewardExp(m_missionId, team));
    return true;
}

bool GfMenuMissionAdapter::update_MissionRewardZone() {
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataMercenaries::getMsgZoneName(bdat, id, m_missionId)) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuMissionAdapter::update_MissionRewardZonePoint() {
    bool team = GfDataMercenaries::isMissionOrderTeam(m_missionId);
    int develop = GfGameMercenaries::getRewardDevelop(m_missionId, team);
    setNumber(develop - GfGameMercenaries::getRewardDevelopHosei(m_missionId, team));
    return true;
}

bool GfMenuMissionAdapter::update_MissionRewardZonePointBonus() {
    bool team = GfDataMercenaries::isMissionOrderTeam(m_missionId);
    setNumber(GfGameMercenaries::getRewardDevelopHosei(m_missionId, team));
    return true;
}

bool GfMenuMissionAdapter::update_MissionRewardIdeaPoint() {
    setNumber(GfGameMercenaries::getRewardTrust(m_missionId));
    return true;
}

bool GfMenuMissionAdapter::update_MissionRewardMerPoint() {
    setNumber(GfGameMercenaries::getRewardMercenariesPoint(m_missionId));
    return true;
}

bool GfMenuMissionAdapter::update_MissionFieldSkill() {
    unsigned char* bdat;
    unsigned int id;
    if (!GfDataMercenaries::getFieldSkillInfo(bdat, id, m_missionId, m_slot)) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuMissionAdapter::update_MissionCondIcon() {
    if (m_slot < 3) {
        GfRequestBladeData data = {};
        if (GfDataMercenaries::getRequestCondition(data, m_missionId, m_slot)) {
            setNumber(data.m_type - 1);
            return true;
        }
    }
    return false;
}

bool GfMenuMissionAdapter::update_MissionCondParam() {
    if (m_slot < 3) {
        GfRequestBladeData data = {};
        if (GfDataMercenaries::getRequestCondition(data, m_missionId, m_slot) && data.m_type == 2) {
            setNumber(data.m_level);
            return true;
        }
    }
    return false;
}

bool GfMenuMissionAdapter::update_MissionCondBladeMax() {
    if (m_slot < 3) {
        GfRequestBladeData data = {};
        if (GfDataMercenaries::getRequestCondition(data, m_missionId, m_slot)) {
            setNumber(data.m_count == 0 ? 1 : data.m_count);
            return true;
        }
    }
    return false;
}

bool GfMenuMissionAdapter::update_MissionTeamIcon() {
    unsigned int team = GfDataMercenaries::getTeamIDByMissionID(m_missionId);
    if (team == 0) {
        return false;
    }
    setNumber(team - 1);
    return true;
}

bool GfMenuMissionAdapter::update_MissionPartyIcon() {
    if (!GfDataMercenaries::isMissionOrderParty(m_missionId)) {
        return false;
    }
    setNumber(0);
    return true;
}

bool GfMenuMissionAdapter::update_MissionStateIcon() {
    if (GfDataMercenaries::isMissionCompleteFlag(m_missionId)) {
        setNumber(2);
        return true;
    }
    if (GfDataMercenaries::isNewMission(m_missionId)) {
        setNumber(0);
        return true;
    }
    if (GfDataMercenaries::isMissionOrderTeam(m_missionId)) {
        setNumber(1);
        return true;
    }
    return false;
}

bool GfMenuMissionAdapter::update_MissionNewDisp() {
    if (m_missionId == 0) {
        return false;
    }
    return GfDataMercenaries::isNewMission(m_missionId);
}

bool GfMenuMissionAdapter::update_MissionFieldSkillDisp() {
    return GfDataMercenaries::getFieldSkill(m_missionId, m_slot) != 0;
}

void GfMenuMissionAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int mission = m_converter->getMissionId();
        if (mission != m_missionId) {
            m_missionId = mission;
            setChange();
        }
    }
    int stat = getStat(m_missionId, false);
    if (m_stat != stat) {
        m_stat = stat;
        setChange();
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_missionId == 0 ? false : m_update());
        m_flags &= ~1;
    }
}

}  // namespace gf
