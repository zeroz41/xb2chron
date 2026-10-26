#include "classes/gf/GfMenuMissionAdapter.h"
#include "classes/gf/GfMenuMissionAdapter/ListConverter.h"
#include "classes/gf/GfMenuMissionAdapter/ReferenceConverter.h"
#include "classes/gf/GfMenuMissionAdapter/ReferenceMissionConverter.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "gf/GfDataMercenaries.h"
#include "classes/gf/GfGameMercenaries.h"
#include "ui/UIStr.h"
#include "gf/GfDataBladeArts.h"
#include "gf/GfDataFieldSkill.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfDataBdat.h"
#include "plugin/Bdat.h"
#include "gf/GfDataQuest.h"
#include "ui/uiDateTime.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"

namespace gf {

// Display callback and plugin settings for each adapter type, in create's index order.
// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B5D228).
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

GfMenuMissionAdapter::~GfMenuMissionAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
}

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

bool GfMenuMissionAdapter::fn_7100345570() {
    unsigned char* bdat;
    unsigned int id;
    if (getStat(m_missionId, false) == 2 || getStat(m_missionId, false) == 3) {
        GfDataQuest::getResult(bdat, id, GfDataMercenaries::getMissionQuestID(m_missionId));
    } else if (!GfDataMercenaries::getMsgSummaryName(bdat, id, m_missionId)) {
        return false;
    }
    if (id == 0 || bdat == nullptr) {
        return false;
    }
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuMissionAdapter::fn_7100345648() {
    unsigned char* bdat;
    unsigned int id;
    if (getStat(m_missionId, false) == 3) {
        GfDataQuest::getResult(bdat, id, GfDataMercenaries::getMissionQuestID(m_missionId));
    } else if (!GfDataMercenaries::getMsgSummaryName(bdat, id, m_missionId)) {
        return false;
    }
    if (id == 0 || bdat == nullptr) {
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

bool GfMenuMissionAdapter::update_MissionTime() {
    ui::uiDateTime time = {};
    int stat = getStat(m_missionId, false);
    if (stat == 0) {
        unsigned int minutes = GfDataMercenaries::getMissionTime(m_missionId);
        time.hour = minutes / 60;
        time.minute = minutes % 60;
    } else if (stat == 1) {
        ElapseTime remain = GfDataMercenaries::getTeamMissionTime(GfDataMercenaries::getTeamIDByMissionID(m_missionId));
        time.hour = remain.hour;
        time.minute = remain.min;
        time.sec = remain.sec;
    } else {
        return false;
    }
    setTime(time);
    return true;
}

bool GfMenuMissionAdapter::update_MissionTimeRemain() {
    ui::uiDateTime time = {};
    unsigned int team = GfDataMercenaries::getTeamIDByMissionID(m_missionId);
    if (getStat(m_missionId, false) == 1) {
        ElapseTime remain = GfDataMercenaries::getTeamMissionTime(team);
        time.hour = remain.hour;
        time.minute = remain.min;
        time.sec = remain.sec;
        if (time.hour != 0 || time.minute != 0 || time.sec != 0) {
            setTime(time);
            return true;
        }
    }
    return false;
}

bool GfMenuMissionAdapter::update_MissionStatusIcon() {
    static const int icons[] = {0, 1, 2, 2};
    setNumber(icons[getStat(m_missionId, true)]);
    return true;
}

bool GfMenuMissionAdapter::update_MissionStatus() {
    int row;
    switch (getStat(m_missionId, true)) {
    case 2:
    case 3:
        row = 0xD;
        break;
    case 0:
        if (!GfMenuObjUtil::checkMissionCond(m_missionId, m_bladeList)) {
            return false;
        }
        row = 0xB;
        break;
    default:
        row = 0xC;
        break;
    }
    unsigned char* status = GfDataBdat::getFP(0x13D);
    unsigned char* message = GfDataBdat::getFP(0xF5);
    ui::UIStr text(message, (unsigned short)Bdat::getVal(status, "name", row));
    setText(text);
    return true;
}

bool GfMenuMissionAdapter::update_MissionStatusColor() {
    // the colour of each getStat value. Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B5D7C0).
    static const char* const colors[] = {"mer_unit_ready", "mer_unit_active", "mer_unit_complete", "mer_unit_complete"};
    const char* color = colors[getStat(m_missionId, true)];
    switch (m_slot) {
    case 0:
        setAddColor(color);
        return true;
    case 1:
        setMulColor(color);
        return true;
    case 2:
        if (GfDataMercenaries::getTeamIDByMissionID(m_missionId) == 0) {
            return false;
        }
        setAddColor(color);
        return true;
    }
    return false;
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

bool GfMenuMissionAdapter::update_MissionCond() {
    if (m_slot >= 3) {
        return false;
    }
    GfRequestBladeData data = {};
    if (!GfDataMercenaries::getRequestCondition(data, m_missionId, m_slot)) {
        return false;
    }
    unsigned char* bdat = nullptr;
    unsigned int id = 0;
    switch (data.m_type) {
    case 1: {
        int index = data.m_param;  // read before getFP
        bdat = GfDataBdat::getFP(0x1CF);
        id = GfMenuObjUtil::getMsgIDFromList(0x141, index);
        break;
    }
    case 2:
        bdat = GfDataBdat::getFP(0xF5);
        id = GfMenuObjUtil::getMsgIDFromList(0x13D, 0x13);
        break;
    case 3: {
        int index = data.m_param;  // read before getFP
        bdat = GfDataBdat::getFP(0xF5);
        id = GfMenuObjUtil::getMsgIDFromList(0x143, index);
        break;
    }
    case 4: {
        int index = data.m_param;  // read before getFP
        bdat = GfDataBdat::getFP(0xF5);
        id = GfMenuObjUtil::getMsgIDFromList(0x142, index);
        break;
    }
    case 5:
        if (!GfDataBladeArts::getName(bdat, id, data.m_param)) {
            return false;
        }
        break;
    case 6:
        if (!GfDataFieldSkill::getName(bdat, id, data.m_param)) {
            return false;
        }
        break;
    case 7: {
        int index = data.m_param;  // read before getFP
        bdat = GfDataBdat::getFP(0x114);
        id = GfMenuObjUtil::getMsgIDFromList(0x13E, index + 1);
        break;
    }
    default:
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

bool GfMenuMissionAdapter::update_MissionCondLv() {
    if (m_slot < 3) {
        GfRequestBladeData data = {};
        if (GfDataMercenaries::getRequestCondition(data, m_missionId, m_slot)) {
            if (data.m_type == 5) {
                setNumber(data.m_level);
                return true;
            }
            if (data.m_type == 6) {
                setNumber(data.m_level);
                return true;
            }
            return false;
        }
    }
    return false;
}

bool GfMenuMissionAdapter::update_MissionCondParamIcon() {
    if (m_slot >= 3) {
        return false;
    }
    GfRequestBladeData data = {};
    if (GfDataMercenaries::getRequestCondition(data, m_missionId, m_slot) && data.m_type == m_condType) {
        int icon;
        if (data.m_type == 1) {
            icon = data.m_param;
        } else if (data.m_type == 3) {
            icon = data.m_param - 1;
        } else if (data.m_type == 4) {
            icon = static_cast<unsigned int>(data.m_param) >> 1;
        } else {
            return false;
        }
        setNumber(icon);
        return true;
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

bool GfMenuMissionAdapter::update_MissionCondBladeCount() {
    if (m_slot < 3) {
        if (m_bladeList == nullptr || m_bladeList->getSize() == 0) {
            return false;
        }
        GfRequestBladeData data = {};
        if (GfDataMercenaries::getRequestCondition(data, m_missionId, m_slot)) {
            setNumber(GfMenuObjUtil::getMissionCondBladeCount(data, m_bladeList));
            return true;
        }
    }
    return false;
}

bool GfMenuMissionAdapter::update_MissionCondCheckIcon() {
    if (m_slot < 3 && m_bladeList != nullptr && m_bladeList->getSize() != 0) {
        GfRequestBladeData data = {};
        if (GfDataMercenaries::getRequestCondition(data, m_missionId, m_slot)) {
            unsigned int count = GfMenuObjUtil::getMissionCondBladeCount(data, m_bladeList);
            unsigned int need = data.m_count == 0 ? 1 : data.m_count;
            setNumber(count >= need);
            return true;
        }
    }
    return false;
}

bool GfMenuMissionAdapter::update_MissionCondCheckDisp() {
    if (m_bladeList == nullptr || m_bladeList->getSize() == 0) {
        return false;
    }
    if (m_slot == -1) {
        return GfMenuObjUtil::checkMissionCond(m_missionId, m_bladeList);
    }
    if (m_slot < 3) {
        GfRequestBladeData data = {};
        if (GfDataMercenaries::getRequestCondition(data, m_missionId, m_slot)) {
            unsigned int count = GfMenuObjUtil::getMissionCondBladeCount(data, m_bladeList);
            unsigned int need = data.m_count == 0 ? 1 : data.m_count;
            return count >= need;
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

bool GfMenuMissionAdapter::update_MissionProgressDisp() {
    if (m_missionId == 0) {
        return false;
    }
    return getStat(m_missionId, false) != 0;
}

bool GfMenuMissionAdapter::update_MissionFieldSkillDisp() {
    return GfDataMercenaries::getFieldSkill(m_missionId, m_slot) != 0;
}

bool GfMenuMissionAdapter::update_MissionFieldSkillColor() {
    unsigned int skill = GfDataMercenaries::getFieldSkill(m_missionId, m_slot);
    if (skill == 0) {
        return false;
    }
    unsigned short* members = GfDataMercenaries::getTeamMember(GfMenuReference::getReferenceTeamID());
    if (members == nullptr) {
        return false;
    }
    for (unsigned short* member = members; member != members + 6; member++) {
        if (*member != 0) {
            DataParamAcc acc(4, *member, GimmickType(0));
            if (acc.getFieldSkill(0, false) == skill || acc.getFieldSkill(1, false) == skill ||
                acc.getFieldSkill(2, false) == skill) {
                setMulColor(nullptr);
                return true;
            }
        }
    }
    setMulColor("darkgray");
    return true;
}

bool GfMenuMissionAdapter::update_MemberFieldSkillLv() {
    unsigned int skill = GfDataMercenaries::getFieldSkill(m_missionId, m_slot);
    if (skill == 0) {
        return false;
    }
    unsigned short* members = GfDataMercenaries::getTeamMember(GfMenuReference::getReferenceTeamID());
    if (members == nullptr) {
        return false;
    }
    unsigned short blade = members[m_member];
    if (blade == 0) {
        return false;
    }
    DataParamAcc acc(4, blade, GimmickType(0));
    unsigned int index;
    if (acc.getFieldSkill(0, false) == skill) {
        index = 0;
    } else if (acc.getFieldSkill(1, false) == skill) {
        index = 1;
    } else if (acc.getFieldSkill(2, false) == skill) {
        index = 2;
    } else {
        return false;
    }
    setNumber(acc.getFieldSkillLevel(index, false));
    return true;
}

bool GfMenuMissionAdapter::update_MemberFieldSkillColor() {
    unsigned int skill = GfDataMercenaries::getFieldSkill(m_missionId, m_slot);
    if (skill == 0) {
        return false;
    }
    unsigned short* members = GfDataMercenaries::getTeamMember(GfMenuReference::getReferenceTeamID());
    if (members == nullptr) {
        return false;
    }
    unsigned short blade = members[m_member];
    if (blade == 0) {
        return false;
    }
    DataParamAcc acc(4, blade, GimmickType(0));
    if (acc.getFieldSkill(0, false) == skill || acc.getFieldSkill(1, false) == skill ||
        acc.getFieldSkill(2, false) == skill) {
        setMulColor(nullptr);
    } else {
        setMulColor("gray");
    }
    return true;
}

bool GfMenuMissionAdapter::update_MissionTimeOriginal() {
    unsigned int minutes = GfDataMercenaries::getMissionTime(m_missionId);
    ui::uiDateTime time = {};
    time.hour = minutes / 60;
    time.minute = minutes % 60;
    if (time.hour == 0 && time.minute == 0) {
        return false;
    }
    setTime(time);
    return true;
}

bool GfMenuMissionAdapter::update_MissionTimeAdjust() {
    unsigned int team = GfDataMercenaries::getTeamIDByMissionID(m_missionId);
    if (team == 0) {
        return false;
    }
    unsigned int minutes = GfDataMercenaries::getTeamMissionTime(team, m_missionId);
    ui::uiDateTime time = {};
    time.hour = minutes / 60;
    time.minute = minutes % 60;
    setTime(time);
    return true;
}

bool GfMenuMissionAdapter::update_MissionFieldSkillLevelCount() {
    if (m_bladeList == nullptr || m_bladeList->getSize() == 0) {
        return false;
    }
    unsigned int skill = GfDataMercenaries::getFieldSkill(m_missionId, m_slot);
    if (skill == 0) {
        return false;
    }
    int level = 0;
    for (unsigned int i = 0; i < m_bladeList->getSize(); i++) {
        DataParamAcc acc(4, m_bladeList->getContents(i).m_blade, GimmickType(0));
        unsigned int index;
        if (acc.getFieldSkill(0, false) == skill) {
            index = 0;
        } else if (acc.getFieldSkill(1, false) == skill) {
            index = 1;
        } else if (acc.getFieldSkill(2, false) == skill) {
            index = 2;
        } else {
            continue;
        }
        level += acc.getFieldSkillLevel(index, false);
    }
    setNumber(level);
    return true;
}

bool GfMenuMissionAdapter::update_MissionFieldSkillBladeCount() {
    if (m_bladeList == nullptr || m_bladeList->getSize() == 0) {
        return false;
    }
    unsigned int skill = GfDataMercenaries::getFieldSkill(m_missionId, m_slot);
    if (skill == 0) {
        return false;
    }
    int count = 0;
    for (unsigned int i = 0; i < m_bladeList->getSize(); i++) {
        DataParamAcc acc(4, m_bladeList->getContents(i).m_blade, GimmickType(0));
        if (acc.getFieldSkill(0, false) == skill || acc.getFieldSkill(1, false) == skill ||
            acc.getFieldSkill(2, false) == skill) {
            count++;
        }
    }
    setNumber(count);
    return true;
}

bool GfMenuMissionAdapter::update_MissionFieldSkillBladeMax() {
    if (GfDataMercenaries::getFieldSkill(m_missionId, m_slot) == 0) {
        return false;
    }
    setNumber(6);
    return true;
}

GfMenuMissionAdapter* GfMenuMissionAdapter::createFromList(unsigned int handle, unsigned int type, GfMenuIDList* list,
                                                           unsigned int index, GfMenuBladeList* bladeList,
                                                           bool changed) {
#line 262
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListConverter(list, index);
    GfMenuMissionAdapter* adapter = create(handle, type, converter->getMissionId(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
        if (bladeList != nullptr) {
            adapter->m_bladeList = bladeList;
            bladeList->addRef();
        }
    }
    return adapter;
}

GfMenuMissionAdapter* GfMenuMissionAdapter::createFromReference(unsigned int handle, unsigned int type,
                                                                mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference,
                                                                bool changed) {
#line 285
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceConverter(reference);
    GfMenuMissionAdapter* adapter = create(handle, type, converter->getMissionId(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuMissionAdapter* GfMenuMissionAdapter::createFromReferenceMission(unsigned int handle, unsigned int type,
                                                                       unsigned int slot, bool changed) {
#line 297
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceMissionConverter();
    GfMenuMissionAdapter* adapter = create(handle, type, converter->getMissionId(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
        adapter->m_slot = slot;
    }
    return adapter;
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

GfMenuMissionAdapter::ListConverter::~ListConverter() {
    if (m_list != nullptr) {
        m_list->release();
        m_list = nullptr;
    }
}

unsigned int GfMenuMissionAdapter::ListConverter::getMissionId() {
    if (m_index < m_list->getSize()) {
        GfMenuIDList* list = m_list;
        return list->getContents(list->getPageIndex(m_index)).m_id;
    }
    return 0;
}

GfMenuMissionAdapter::IConverter::~IConverter() {}

GfMenuMissionAdapter::ReferenceConverter::~ReferenceConverter() {
    m_reference = nullptr;
}

unsigned int GfMenuMissionAdapter::ReferenceConverter::getMissionId() {
    return m_reference->m_value;
}

unsigned int GfMenuMissionAdapter::ReferenceMissionConverter::getMissionId() {
    return GfMenuReference::getReferenceMissionID();
}

}  // namespace gf
