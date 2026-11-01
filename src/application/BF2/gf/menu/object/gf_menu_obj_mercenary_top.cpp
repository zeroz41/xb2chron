#include "classes/gf/GfMenuObjMercenaryTop.h"
#include "classes/gf/GfMenuObjMercenaryTop/MainListener.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuFullScreen.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuReferenceQuest.h"
#include "classes/ui/UICtrlRevolveSelect.h"
#include "classes/ui/UISelectObjList.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjMercenaryTop::GfMenuObjMercenaryTop(unsigned int handle)
    : GfMenuObject(handle), m_zoneList(nullptr), m_missionList(nullptr), m_zoneSelect(nullptr), m_zoneRevolve(nullptr),
      m_revolveStep(1.0f), m_flagIcons(nullptr), m_noticeIcons(nullptr), m_missionSelect(nullptr), m_zoneNumber(),
      m_rewardNumber(), m_quest(), m_callContext(nullptr), m_seq(this), m_jobStarted(false), m_exitHandle(0),
      m_callContext2(nullptr), m_canClose(true) {
    m_zoneNumber = GfMenuReferenceNumber::create();
    m_rewardNumber = GfMenuReferenceNumber::create();
    m_quest = GfMenuReferenceQuest::create();
    m_callContext = GfMenuCallContext::create();
    m_callContext2 = GfMenuCallContext::create();
}

GfMenuObjMercenaryTop::~GfMenuObjMercenaryTop() {
    if (m_callContext2 != nullptr) {
        m_callContext2->release();
        m_callContext2 = nullptr;
    }
    if (m_callContext != nullptr) {
        m_callContext->release();
        m_callContext = nullptr;
    }
    m_quest = nullptr;
    m_rewardNumber = nullptr;
    m_zoneNumber = nullptr;
    if (m_missionSelect != nullptr) {
        m_missionSelect->release();
        m_missionSelect = nullptr;
    }
    if (m_noticeIcons != nullptr) {
        m_noticeIcons->release();
        m_noticeIcons = nullptr;
    }
    if (m_flagIcons != nullptr) {
        m_flagIcons->release();
        m_flagIcons = nullptr;
    }
    if (m_zoneRevolve != nullptr) {
        m_zoneRevolve->release();
        m_zoneRevolve = nullptr;
    }
    if (m_zoneSelect != nullptr) {
        m_zoneSelect->release();
        m_zoneSelect = nullptr;
    }
    if (m_missionList != nullptr) {
        m_missionList->release();
        m_missionList = nullptr;
    }
    if (m_zoneList != nullptr) {
        m_zoneList->release();
        m_zoneList = nullptr;
    }
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
    if (m_bladeList2 != nullptr) {
        m_bladeList2->release();
        m_bladeList2 = nullptr;
    }
}

void GfMenuObjMercenaryTop::registOpenParam(OpenParam const& openParam) {
    GfMenuTypes::Param param;
    param.m_menuId = openParam.m_value;
    GfMenuFullScreen::registLayerParam(0x34, param);
}

void GfMenuObjMercenaryTop::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMercenaryTop::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjMercenaryTop::refreshMissionList() {
    ui::UIObjectAcc list(m_handle, "LAY_mis_sel_list");
    if (list.m_object != nullptr) {
        mm::mtl::FixStr<32> name;
        for (unsigned int i = 0; i < m_missionSelect->getSize(); i++) {
            name.format("TXT_mis_sel_title@%02d", i + 1);
            ui::UIObjectAcc title(list.m_handle, name.m_str);
            name.format("TXT_mis_sel_time@%02d", i + 1);
            ui::UIObjectAcc time(list.m_handle, name.m_str);
            name.format("TXT_mis_sel_time_inf@%02d", i + 1);
            ui::UIObjectAcc timeInf(list.m_handle, name.m_str);
            unsigned int mission = m_missionList->getContents(m_missionList->getPageIndex(i)).m_id;
            if (GfDataMercenaries::isMissionOrderTeam(mission)) {
                GfMenuObjUtil::setColMulandAdd(title.m_handle, "txt_highlight");
                title.setBorderWeight(1.0f);
                time.setBorderWeight(1.0f);
                timeInf.setBorderWeight(1.0f);
            } else if (mission != 0 && GfMenuObjUtil::checkMissionCond(mission, m_bladeList)) {
                GfMenuObjUtil::setColDefault(title.m_handle);
                title.setBorderWeight(-0.5f);
                time.setBorderWeight(-0.5f);
                timeInf.setBorderWeight(-0.5f);
            } else {
                GfMenuObjUtil::setColMulandAdd(title.m_handle, "txt_disable");
                title.setBorderWeight(1.0f);
                time.setBorderWeight(1.0f);
                timeInf.setBorderWeight(1.0f);
            }
            if (m_missionList->getIndex(true) == i) {
                GfRequestBladeData data = {};
                for (unsigned int slot = 0; slot < 3; slot++) {
                    name.format("TXT_mis_sel_cond_txt@%02d", slot + 1);
                    ui::UIObjectAcc cond(list.m_handle, name.m_str);
                    name.format("IMG_mis_sel_cond_icon@%02d", slot + 1);
                    ui::UIObjectAcc icon(list.m_handle, name.m_str);
                    if (GfDataMercenaries::getRequestCondition(data, mission, slot) &&
                        static_cast<unsigned int>(data.m_count == 0 ? 1 : data.m_count) <=
                            GfMenuObjUtil::getMissionCondBladeCount(data, m_bladeList)) {
                        GfMenuObjUtil::setColDefault(cond.m_handle);
                        icon.setAddColor("mer_cond_ok");
                    } else {
                        GfMenuObjUtil::setColMulandAdd(cond.m_handle, "txt_warning");
                        icon.setAddColor("mer_cond_ng");
                    }
                }
            }
        }
    }
}

void GfMenuObjMercenaryTop::setDispUnitReady(unsigned int handle, unsigned int index) {
    ui::UIObjectAcc acc(handle);
    unsigned int no = index + 1;
    mm::mtl::FixStr<32> name;
    name.format("TXT_zone_unit_name@%02d", no);
    ui::UIObjectAcc(acc.searchChild(name.m_str)).setAlpha(0.0f);
    name.format("TXT_zone_unit_ready@%02d", no);
    acc.setDispChild(true, name.m_str);
    name.format("TXT_zone_unit_mission_name@%02d", no);
    ui::UIObjectAcc(acc.searchChild(name.m_str)).setAlpha(0.0f);
    name.format("TXT_zone_unit_mission_time@%02d", no);
    ui::UIObjectAcc(acc.searchChild(name.m_str)).setAlpha(0.0f);
    name.format("IMG_zone_unit_base@%02d", no);
    GfMenuObjUtil::setChildAddColor(acc.m_handle, name.m_str, "mer_unit_empty");
    name.format("TXT_zone_unit_mission_inf@%02d", no);
    ui::UIObjectAcc(acc.m_handle, name.m_str).setAlpha(0.0f);
}

void GfMenuObjMercenaryTop::setDispUnitProgress(unsigned int handle, unsigned int index) {
    ui::UIObjectAcc acc(handle);
    unsigned int no = index + 1;
    mm::mtl::FixStr<32> name;
    name.format("TXT_zone_unit_name@%02d", no);
    GfMenuObjUtil::setColDefault(acc.searchChild(name.m_str));
    ui::UIObjectAcc(acc.searchChild(name.m_str)).setAlpha(1.0f);
    name.format("TXT_zone_unit_ready@%02d", no);
    acc.setDispChild(false, name.m_str);
    name.format("TXT_zone_unit_mission_name@%02d", no);
    GfMenuObjUtil::setColDefault(acc.searchChild(name.m_str));
    ui::UIObjectAcc(acc.searchChild(name.m_str)).setAlpha(1.0f);
    name.format("TXT_zone_unit_mission_time@%02d", no);
    GfMenuObjUtil::setColDefault(acc.searchChild(name.m_str));
    name.format("IMG_zone_unit_base@%02d", no);
    GfMenuObjUtil::setColDefault(acc.searchChild(name.m_str));
    name.format("TXT_zone_unit_mission_inf@%02d", no);
    ui::UIObjectAcc(acc.m_handle, name.m_str).setAlpha(1.0f);
}

void GfMenuObjMercenaryTop::setDispUnitReturn(unsigned int handle, unsigned int index) {
    ui::UIObjectAcc acc(handle);
    unsigned int no = index + 1;
    mm::mtl::FixStr<32> name;
    name.format("TXT_zone_unit_name@%02d", no);
    GfMenuObjUtil::setColMulandAdd(acc.searchChild(name.m_str), "txt_disable");
    ui::UIObjectAcc(acc.searchChild(name.m_str)).setAlpha(0.5f);
    name.format("TXT_zone_unit_ready@%02d", no);
    acc.setDispChild(false, name.m_str);
    name.format("TXT_zone_unit_mission_name@%02d", no);
    GfMenuObjUtil::setColMulandAdd(acc.searchChild(name.m_str), "txt_disable");
    ui::UIObjectAcc(acc.searchChild(name.m_str)).setAlpha(0.5f);
    name.format("TXT_zone_unit_mission_time@%02d", no);
    GfMenuObjUtil::setColMulandAdd(acc.searchChild(name.m_str), "txt_disable");
    name.format("IMG_zone_unit_base@%02d", no);
    GfMenuObjUtil::setChildAddColor(acc.m_handle, name.m_str, "black");
    name.format("TXT_zone_unit_mission_inf@%02d", no);
    ui::UIObjectAcc(acc.m_handle, name.m_str).setAlpha(0.0f);
}

void GfMenuObjMercenaryTop::MainListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 2:
    case 0x22: {
        if (!m_owner->m_canClose) {
            acc.setTerm();
            break;
        }
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 6;
        param.m_startFlag1 = true;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 0x24: {
        GfMenuObject::disableInput(acc.searchChild("LAY_zone"));
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        m_owner->m_canClose = false;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjMercenaryTop::seqUnitBreak() {
    if (!m_jobStarted) {
        unsigned int team =
            GfDataMercenaries::getTeamIDByMissionID(m_missionList->getContents(m_missionList->getIndex(false)).m_id);
        unsigned int leader = GfDataMercenaries::getTeamLeader(team);
        m_callContext2->reset();
        GfMenuObjCommonText::openMissionStop(m_callContext2, 0x22, leader);
        m_jobStarted = true;
        return false;
    }
    if (m_callContext2->isActive()) {
        return false;
    }
    GfMenuCallContext::GfMenuResult result;
    if (m_callContext2->popResult(result) && result.m_value == 0 && result.m_id == 0) {
        unsigned int mission = GfMenuReference::getReferenceMissionID();
        unsigned int team = GfDataMercenaries::getTeamIDByMissionID(mission);
        GfGameMercenaries::cancelMission(mission);
        GfGameMercenaries::clearTeamMember(team);
        GfMenuReference::setReferenceTeamID(0);
        for (unsigned int i = 0; i < GfDataMercenaries::getTeamNum(); i++) {
            GfDataMercenaries::Team* t = GfDataMercenaries::getTeamByIndex(i);
            if (t != nullptr && GfDataMercenaries::isTeamStateEmpty(t->m_teamId)) {
                GfMenuReference::setReferenceTeamID(t->m_teamId);
                break;
            }
        }
    }
    m_seq.addJob(&GfMenuObjMercenaryTop::seqExit);
    m_jobStarted = false;
    return true;
}

bool GfMenuObjMercenaryTop::seqCanNotOrder() {
    if (!m_jobStarted) {
        GfMenuManager::openCommonWindow(0x9E);
        m_jobStarted = true;
        return false;
    }
    if (GfMenuManager::isOpenCommonWindow()) {
        return false;
    }
    GfMenuManager::getCommonWindowResult();
    m_seq.addJob(&GfMenuObjMercenaryTop::seqExit);
    m_jobStarted = false;
    return true;
}

bool GfMenuObjMercenaryTop::seqExit() {
    if (m_exitHandle != 0) {
        ui::EventData event;
        event.m_type = 0x100;
        GfMenuObject::sendEvent(m_exitHandle, event, 0.0f);
        m_exitHandle = 0;
    }
    return true;
}

}  // namespace gf
