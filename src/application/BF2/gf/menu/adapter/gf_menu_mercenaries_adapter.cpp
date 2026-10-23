#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataParty.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuMercenariesAdapter.h"
#include "classes/gf/GfMenuMercenariesAdapter/IConverter.h"
#include "classes/gf/GfMenuMercenariesAdapter/ReferenceBladeConverter.h"
#include "classes/gf/GfMenuMercenariesAdapter/ReferenceTeamConverter.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuFieldSkillList.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectPlugin.h"
#include "gf/GfMenuBdat.h"
#include "plugin/Bdat.h"
#include "ui/UIStr.h"
#include "ui/uiDateTime.h"

namespace gf {

// per type: the update_* update shows and the plugin create makes (text, image index, disp, colour, time,
// numbers up to 9999 or 18)
static GfMenuMercenariesAdapter::TypeSetup s_typeSetups[] = {
    {&GfMenuMercenariesAdapter::update_TeamName, {2, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamBlFace, {1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamIcon, {1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamStat, {2, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamStatColor, {8, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamWait, {3, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisInfo, {3, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisZone, {2, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisZoneIcon, {1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisName, {2, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisTime, {7, 3, 0}},
    {&GfMenuMercenariesAdapter::update_TeamMisComplete, {3, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamStrength, {0, 0, 9999}},
    {&GfMenuMercenariesAdapter::update_TeamMale, {0, 0, 18}},
    {&GfMenuMercenariesAdapter::update_TeamFemale, {0, 0, 18}},
    {&GfMenuMercenariesAdapter::update_TeamAnimal, {0, 0, 18}},
    {&GfMenuMercenariesAdapter::update_TeamStrengthDiffIcon, {1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamFieldSkillDiffIcon, {1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamNameRes, {2, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamIconRes, {1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamIconResFace, {1, 0, 0}},
    {&GfMenuMercenariesAdapter::update_TeamDispNum1, {3, 0, 0}},
};

GfMenuMercenariesAdapter::~GfMenuMercenariesAdapter() {
    if (m_converter != nullptr) {
        delete m_converter;
        m_converter = nullptr;
    }
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
    if (m_fieldSkillList != nullptr) {
        m_fieldSkillList->release();
        m_fieldSkillList = nullptr;
    }
}

GfMenuMercenariesAdapter* GfMenuMercenariesAdapter::create(unsigned int handle, unsigned int type,
                                                           unsigned int teamId, bool changed) {
    ui::UIObjectAcc acc(handle);
    if (acc.m_object == nullptr) {
        return nullptr;
    }
    const TypeSetup& setup = s_typeSetups[type];
    ui::UIObjectPlugin* plugin = createPlugin(handle, setup.plugin);
    if (plugin == nullptr) {
        return nullptr;
    }
#line 150
    GfMenuMercenariesAdapter* adapter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfMenuMercenariesAdapter(plugin, changed);
    adapter->m_update.set(adapter, setup.func);
    adapter->m_teamId = teamId;
    plugin->release();
    return adapter;
}

bool GfMenuMercenariesAdapter::update_TeamName() {
    if (m_teamId == 0 || !GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    ui::UIStr name;
    if (!getTeamName(m_teamId, name) || !name.isValid()) {
        return false;
    }
    setText(name);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamBlFace() {
    if (m_teamId == 0 || !GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    ui::UIStr name;  // unused: the original constructs (and destroys) it too
    unsigned int leader = GfDataMercenaries::getTeamLeader(m_teamId);
    if (leader == 0) {
        return false;
    }
    DataParamAcc acc(4, leader, GimmickType(0));
    if (!acc.isValid()) {
        return false;
    }
    int face = GfMenuObjUtil::getFaceIconID(acc);
    if (face == 0) {
        return false;
    }
    setNumber(GfMenuBdat::getIconImageIndex(face));
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamIcon() {
    setNumber(m_teamId - 1);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamStat() {
    unsigned char* stat = GfDataBdat::getFP(0x13D);
    unsigned char* message = GfDataBdat::getFP(0xF5);
    if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    int row;
    if (isOrder(m_teamId)) {
        row = GfDataMercenaries::isTeamStateReward(m_teamId) ? 0xD : 0xC;
    } else {
        row = 0xB;
    }
    ui::UIStr text(message, (unsigned short)(unsigned long)Bdat::getVal(stat, "name", row));
    setText(text);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamStatColor() {
    if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    setAddColor(isOrder(m_teamId) ? "mer_unit_active" : "mer_unit_ready");
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamWait() {
    if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    return !isOrder(m_teamId);
}

bool GfMenuMercenariesAdapter::update_TeamMisInfo() {
    if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    return isOrder(m_teamId);
}

bool GfMenuMercenariesAdapter::update_TeamMisZone() {
    if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    unsigned int mission = GfDataMercenaries::getTeamMission(m_teamId);
    if (mission == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    GfDataMercenaries::getMsgZoneName(bdat, id, mission);
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamMisZoneIcon() {
    if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    unsigned int mission = GfDataMercenaries::getTeamMission(m_teamId);
    if (mission == 0) {
        return false;
    }
    unsigned int zone = GfDataMercenaries::getMissionZoneID(mission);
    if (zone == 0) {
        return false;
    }
    setNumber(zone - 1);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamMisName() {
    if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    unsigned int mission = GfDataMercenaries::getTeamMission(m_teamId);
    if (mission == 0) {
        return false;
    }
    unsigned char* bdat;
    unsigned int id;
    GfDataMercenaries::getMsgTitleName(bdat, id, mission);
    ui::UIStr text(bdat, id);
    setText(text);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamMisTime() {
    if (!GfDataMercenaries::isValidTeamID(m_teamId) || !isOrder(m_teamId)) {
        return false;
    }
    ElapseTime remain = GfDataMercenaries::getTeamMissionTime(m_teamId);
    ui::uiDateTime time = {};
    time.hour = remain.hour;
    time.minute = remain.min;
    time.sec = remain.sec;
    if (time.hour == 0 && time.minute == 0 && time.sec == 0) {
        return false;
    }
    setTime(time);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamMisComplete() {
    if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    return GfDataMercenaries::isTeamStateReward(m_teamId);
}

// the counting loops compare unsigned (b.lo): getSize is declared int, the original compares it as unsigned
bool GfMenuMercenariesAdapter::update_TeamStrength() {
    int power;
    if (m_bladeList == nullptr) {
        if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
            return false;
        }
        power = GfDataMercenaries::getTeamPower(m_teamId);
    } else {
        power = 0;
        for (unsigned short i = 0; i < (unsigned int)m_bladeList->getSize(); i++) {
            power += GfDataBlade::getBladePower(m_bladeList->getContents(i).m_blade);
        }
    }
    setNumber(power);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamMale() {
    int count;
    if (m_bladeList == nullptr) {
        if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
            return false;
        }
        count = GfDataMercenaries::getTeamMaleNum(m_teamId);
    } else {
        count = 0;
        for (unsigned short i = 0; i < (unsigned int)m_bladeList->getSize(); i++) {
            count += GfDataBlade::isMale(m_bladeList->getContents(i).m_blade);
        }
    }
    setNumber(count);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamFemale() {
    int count;
    if (m_bladeList == nullptr) {
        if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
            return false;
        }
        count = GfDataMercenaries::getTeamFemaleNum(m_teamId);
    } else {
        count = 0;
        for (unsigned short i = 0; i < (unsigned int)m_bladeList->getSize(); i++) {
            count += GfDataBlade::isFemale(m_bladeList->getContents(i).m_blade);
        }
    }
    setNumber(count);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamAnimal() {
    int count;
    if (m_bladeList == nullptr) {
        if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
            return false;
        }
        count = GfDataMercenaries::getTeamAnimalNum(m_teamId);
    } else {
        count = 0;
        for (unsigned short i = 0; i < (unsigned int)m_bladeList->getSize(); i++) {
            count += GfDataBlade::isAnimal(m_bladeList->getContents(i).m_blade);
        }
    }
    setNumber(count);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamStrengthDiffIcon() {
    if (m_bladeList == nullptr) {
        return false;
    }
    unsigned int power = 0;
    for (unsigned short i = 0; i < (unsigned int)m_bladeList->getSize(); i++) {
        power += GfDataBlade::getBladePower(m_bladeList->getContents(i).m_blade);
    }
    if (!GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    unsigned int teamPower = GfDataMercenaries::getTeamPower(m_teamId);
    if (power == teamPower) {
        return false;
    }
    setNumber(power <= teamPower);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamFieldSkillDiffIcon() {
    if (m_fieldSkillList == nullptr || !GfDataMercenaries::isValidTeamID(m_teamId)) {
        return false;
    }
    unsigned short* members = GfDataMercenaries::getTeamMember(m_teamId);
    if (members == nullptr) {
        return false;
    }
    GfMenuFieldSkillList* list = GfMenuFieldSkillList::create();
    if (list == nullptr) {
        return false;
    }
    ui::UIListInfoBase::SetupParam param;
    list->setup(getAllocator(ALLOCATOR(0)), param);
    list->addFieldSkillFromBlade(members[0]);
    list->addFieldSkillFromBlade(members[1]);
    list->addFieldSkillFromBlade(members[2]);
    list->addFieldSkillFromBlade(members[3]);
    list->addFieldSkillFromBlade(members[4]);
    list->addFieldSkillFromBlade(members[5]);
    bool lower = false;
    for (unsigned short i = 0; i < (unsigned int)list->getSize(); i++) {
        if (m_fieldSkillList->getContents(m_index).m_id == list->getContents(i).m_id) {
            if (m_fieldSkillList->getContents(m_index).m_lv == list->getContents(i).m_lv) {
                list->release();
                return false;
            }
            lower = m_fieldSkillList->getContents(m_index).m_lv <= list->getContents(i).m_lv;
            break;
        }
    }
    list->release();
    setNumber(lower);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamNameRes() {
    if (m_bladeList == nullptr) {
        return false;
    }
    unsigned int index = m_bladeList->getRowOffset() + m_index;
    int reference = GfMenuReference::getReferenceNumber(0);
    if (reference == 0) {
        DataParamAcc acc(3, GfDataParty::getPartyMember(index, 0)->m_driver, GimmickType(0));
        if (!acc.isValid()) {
            return false;
        }
        setText(GfMenuObjUtil::getName(acc));
    } else if (reference == 1) {
        unsigned int id = (unsigned short)(unsigned long)Bdat::getVal(GfDataBdat::getFP(0x13D), "name", index + 1);
        ui::UIStr text(GfDataBdat::getFP(0xF5), id);
        setText(text);
    } else {
        return false;
    }
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamIconRes() {
    if (m_bladeList == nullptr) {
        return false;
    }
    unsigned int index = m_bladeList->getRowOffset() + m_index;
    int number;
    int reference = GfMenuReference::getReferenceNumber(0);
    if (reference == 2) {
        number = 10;
    } else if (reference == 1) {
        number = index;
    } else {
        return false;
    }
    setNumber(number);
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamIconResFace() {
    if (m_bladeList == nullptr) {
        return false;
    }
    unsigned int index = m_bladeList->getRowOffset() + m_index;
    int reference = GfMenuReference::getReferenceNumber(0);
    if (reference == 0) {
        DataParamAcc acc(3, GfDataParty::getPartyMember(index, 0)->m_driver, GimmickType(0));
        if (!acc.isValid()) {
            return false;
        }
        setNumber(GfMenuBdat::getIconImageIndex(acc.getIconData()));
    } else {
        return false;
    }
    return true;
}

bool GfMenuMercenariesAdapter::update_TeamDispNum1() {
    return GfDataMercenaries::getTeamNum() > 1;
}

GfMenuMercenariesAdapter* GfMenuMercenariesAdapter::createFromCoverter(unsigned int handle, unsigned int type,
                                                                       IConverter* converter, bool changed) {
    GfMenuMercenariesAdapter* adapter = create(handle, type, converter->getTeamId(), changed);
    if (adapter != nullptr) {
        adapter->m_converter = converter;
    }
    return adapter;
}

GfMenuMercenariesAdapter* GfMenuMercenariesAdapter::createFromReferenceTeam(unsigned int handle, unsigned int type,
                                                                            bool changed) {
#line 178
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceTeamConverter();
    return createFromCoverter(handle, type, converter, changed);
}

GfMenuMercenariesAdapter* GfMenuMercenariesAdapter::createFromReferenceBlade(unsigned int handle, unsigned int type,
                                                                             unsigned int index, bool changed) {
#line 232
    IConverter* converter = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ReferenceBladeConverter(index);
    return createFromCoverter(handle, type, converter, changed);
}

void GfMenuMercenariesAdapter::update(const fw::UpdateInfo& info) {
    if (m_converter != nullptr) {
        unsigned int teamId = m_converter->getTeamId();
        if (m_teamId != teamId) {
            m_teamId = teamId;
            setChange();
        }
    }
    unsigned int mission = GfDataMercenaries::getTeamMission(m_teamId);
    if (m_missionId != mission) {
        m_missionId = mission;
        setChange();
    }
    if (m_bladeList != nullptr &&
        (m_bladeList->UIListInfo<MenuBladeInfo>::m_changed || m_bladeList->UIListInfoBase::m_changed)) {
        setChange();
    }
    if (m_fieldSkillList != nullptr &&
        (m_fieldSkillList->UIListInfo<MenuFieldSkill>::m_changed || m_fieldSkillList->UIListInfoBase::m_changed)) {
        setChange();
    }
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_teamId != 0 ? m_update() : false);
        m_flags &= ~1;
    }
}

}  // namespace gf
