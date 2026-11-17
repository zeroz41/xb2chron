#include "classes/gf/GfMenuObjMercenaryTop.h"
#include "classes/gf/GfMenuObjMercenaryTop/MainListener.h"
#include "classes/gf/GfMenuObjMercenaryTop/MissionListener.h"
#include "classes/gf/GfMenuObjMercenaryTop/ZoneListener.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjMercenaryRoot.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjQuestReward.h"
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
#include "classes/ui/UICtrlObject.h"
#include "gf/GfDataMercenaries.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuTypes.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
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

inline void GfMenuObjMercenaryTop::sendOpenOrMain(unsigned int handle, int param) {
    unsigned int target = handle != 0 ? handle : ui::UIObjectAcc(m_handle, "LAY_main").m_handle;
    ui::EventData open;
    open.m_type = 0x21;
    open.m_param0 = param;
    GfMenuObject::sendEvent(target, open, 0.0f);
}

void GfMenuObjMercenaryTop::ZoneListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        pad_0C = 0;
        acc.setDisp(false);
        break;
    case 2:
        if (pad_0C == 1) {
            GfMenuObjMercenaryRoot::openBg(m_owner->m_zoneList->getContents(m_owner->m_zoneList->getIndex(false)).m_id);
        }
        GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        acc.setTerm();
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObjMainMenu2::setSystemKeyEnable(true);
            GfMenuObjMainMenu2::setCloseKeyEnable(true);
            GfMenuObject::enableFSInput(0);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        }
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        bool hasPrev = prev != -1;
        if (index != -1) {
            mm::mtl::FixStr<32> name;
            if (hasPrev) {
                unsigned int zone = m_owner->m_zoneList->getContents(prev).m_id;
                name.format("IMG_zone_sel_flag@%02d", zone);
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x80000000;
                param.m_time = 0.25f;
                GfMenuObjUtil::startCtrl(m_owner->m_zoneSelect->getObject(prev), param, name.m_str);
                name.format("LAY_zone_sel_flag_notice@%02d", zone);
                GfMenuObjUtil::setChildDisp(m_owner->m_zoneSelect->getSelectObject(), name.m_str, true);
            }
            m_owner->m_zoneList->setIndex(index);
            m_owner->m_zoneSelect->setIndex(index);
            unsigned int zone = m_owner->m_zoneList->getContents(m_owner->m_zoneList->getIndex(false)).m_id;
            name.format("IMG_zone_sel_flag@%02d", zone);
            GfMenuObjUtil::CtrlParam param;
            param.m_scale = 1.0f;
            param.m_methods = 0x4080000;
            param.m_color = GfMenuObjUtil::getPresetColor("mer_flag_sel");
            param.m_startFlags = 4;
            param.m_time = 0.25f;
            GfMenuObjUtil::startCtrl(m_owner->m_zoneSelect->getSelectObject(), param, name.m_str);
            name.format("LAY_zone_sel_flag_notice@%02d", zone);
            GfMenuObjUtil::setChildDisp(m_owner->m_zoneSelect->getSelectObject(), name.m_str, false);
            m_owner->m_zoneNumber->setValue(m_owner->m_zoneList->getContents(m_owner->m_zoneList->getIndex(false)).m_id);
            m_owner->updateMissionList();
            if (index != prev && hasPrev) {
                GfMenuObjUtil::playSECommonTab();
            }
        }
        GfMenuObject::releaseTimer(acc.m_handle);
        GfMenuObject::registTimer(acc.m_handle, 1, 0.5f, false);
        pad_0C = 1;
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObjUtil::PresetCtrlParam preset;
            preset.m_preset = 6;
            preset.m_out = 1;
            preset.m_eventId = 2;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, preset);
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            m_owner->sendOpenOrMain(acc.searchSibiling("LAY_mis_sel"), 1);
            m_owner->updateMissionList();
            GfMenuReference::setReferenceZoneID(
                m_owner->m_zoneList->getContents(m_owner->m_zoneList->getIndex(false)).m_id);
            GfMenuObjMainMenu2::setSystemKeyEnable(false);
            GfMenuObjUtil::playSECommonDecide();
        }
        break;
    case 0xB:
        GfMenuObjMercenaryRoot::openBg(m_owner->m_zoneList->getContents(m_owner->m_zoneList->getIndex(false)).m_id);
        pad_0C = 0;
        break;
    case 0xD:
        if (event.m_param1 == 1) {
            unsigned int team = event.m_param2;
            if (event.m_param0 == 5) {
                GfMenuObjMercenaryTop::setDispUnitReturn(acc.m_handle, team);
            } else if (GfDataMercenaries::getTeamMission(team + 1) == 0) {
                GfMenuObjMercenaryTop::setDispUnitReady(acc.m_handle, team);
            } else {
                GfMenuObjMercenaryTop::setDispUnitProgress(acc.m_handle, team);
            }
            m_owner->refreshMissionList();
        }
        break;
    case 0xE:
        // the type of the control's event is read and nothing done with it
        if (ui::UICtrlObject::getEventCtrlObjID(event) == 1) {
            ui::UICtrlObject::getEventType(event);
        }
        break;
    case 0x21: {
        mm::mtl::FixStr<32> name;
        GfMenuObject::resetInputSelection(acc.m_handle);
        GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_zoneList);
        acc.setDispChild(m_owner->m_zoneList->getSize() > 1u, "LAY_zone_sel_arrow");
        GfMenuObjUtil::PresetCtrlParam preset;
        preset.m_preset = 6;
        preset.m_out = 0;
        preset.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, preset);
        for (unsigned int i = 0; i < m_owner->m_zoneList->getSize(); i++) {
            mm::mtl::FixedVector<unsigned short, 500> missions;
            GfGameMercenaries::getZoneMission(missions, m_owner->m_zoneList->getContents(i).m_id);
            bool notice = false;
            for (unsigned int j = 0; j < missions.size(); j++) {
                if (GfDataMercenaries::isNewMission(missions[j])) {
                    notice = true;
                    break;
                }
            }
            name.format("IMG_zone_sel_flag_notice@%02d", m_owner->m_zoneList->getContents(i).m_id);
            acc.setDispChild(notice, name.m_str);
        }
        if (GfDataMercenaries::getTeamMax() == 0) {
            acc.setDispChild(false, "LAY_zone_unit");
        } else {
            unsigned int count = acc.countChild("LAY_zone_unit@%02d", 1);
            acc.setDispChild(true, "LAY_zone_unit");
            m_owner->m_flagIcons->clear();
            for (unsigned int i = 0; i < count; i++) {
                bool active = i < GfDataMercenaries::getTeamMax();
                name.format("LAY_zone_unit@%02d", i + 1);
                acc.setDispChild(active, name.m_str);
                if (active) {
                    m_owner->m_flagIcons->addObject(acc.searchChild(name.m_str));
                    unsigned int mission = GfDataMercenaries::getTeamMission(i + 1);
                    if (mission == 0 || !GfDataMercenaries::isMissionOrderTeam(mission)) {
                        GfMenuObjMercenaryTop::setDispUnitReady(acc.searchChild(name.m_str), i);
                    } else if (GfDataMercenaries::isTeamStateReward(i + 1)) {
                        GfMenuObjMercenaryTop::setDispUnitReturn(acc.searchChild(name.m_str), i);
                    } else {
                        GfMenuObjMercenaryTop::setDispUnitProgress(acc.searchChild(name.m_str), i);
                    }
                }
            }
            mm::Rect<short> first;
            acc.getLayoutRect("mercenary_condition_2", first);
            mm::Rect<short> second;
            acc.getLayoutRect("mercenary_condition_3", second);
            GfMenuObjUtil::placeObjectH(m_owner->m_flagIcons,
                                        mm::Pnt<short>(first.x + first.w / 2, first.y + first.h / 2), second.x - first.x);
        }
        GfMenuObjOperationInfo::setGuideText(7, 0);
        GfMenuObjOperationInfo::setGuideDisp(true);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMercenaryTop::MissionListener::reciveEvent(ui::EventData const& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 2:
        if (acc.isDisp()) {
            GfDataMercenaries::clearNewMission(
                m_owner->m_missionList->getContents(m_owner->m_missionList->getIndex(false)).m_id);
        }
        acc.setTerm();
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObjMainMenu2::setCloseKeyEnable(true);
            GfMenuObject::enableFSInput(1);
        }
        break;
    case 6: {
        int index = event.m_param0;
        int prev = event.m_param1;
        if (index != -1) {
            mm::mtl::FixStr<32> name;
            unsigned int prevRow = m_owner->m_missionSelect->getIndex(false);
            m_owner->m_missionList->setIndex(index);
            m_owner->m_missionSelect->setIndex(m_owner->m_missionList->getIndex(true));
            unsigned int row = m_owner->m_missionSelect->getIndex(false);
            unsigned int mission = m_owner->m_missionList->getContents(m_owner->m_missionList->getIndex(false)).m_id;
            m_owner->m_rewardNumber->m_value = mission;
            m_owner->m_quest->m_quest = GfDataMercenaries::getMissionQuestID(mission);
            GfMenuObjQuestReward::open(m_owner->m_callContext, false);
            GfMenuReference::setReferenceMissionID(mission);
            if (prev != -1) {
                name.format("IMG_mis_sel_item_base@%02d", prevRow + 1);
                ui::UIObjectAcc base(acc.m_handle, name.m_str);
                base.loadDefColor();
                GfDataMercenaries::clearNewMission(m_owner->m_missionList->getContents(prev).m_id);
            }
            name.format("IMG_mis_sel_item_base@%02d", row + 1);
            ui::UIObjectAcc base(acc.m_handle, name.m_str);
            base.setMulColor("black");
            base.setAddColor("sys_select");
            m_owner->refreshMissionList();
            if (prev != -1 && index != prev) {
                GfMenuObjUtil::playSECommonCursor();
            }
        }
        break;
    }
    case 8:
        if (event.m_param1 == 1) {
            unsigned int mission =
                m_owner->m_missionList->getContents(m_owner->m_missionList->getIndex(false)).m_id;
            GfDataMercenaries::clearNewMission(mission);
            if (GfDataMercenaries::isMissionOrderTeam(mission)) {
                m_owner->m_exitHandle = acc.m_handle;
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjMercenaryTop::seqUnitBreak);
                GfMenuObject::disableFSInput();
            } else if (GfDataMercenaries::isOrderOnlyOne(mission) && GfDataMercenaries::isMissionCompleteFlag(mission)) {
                GfMenuManager::openCommonWindow(0xCE);
            } else if (GfMenuObjUtil::checkMissionCond(mission, m_owner->m_bladeList)) {
                if (GfDataMercenaries::isValidTeamID(GfMenuReference::getReferenceTeamID())) {
                    unsigned int reference = GfMenuReference::getReferenceMissionID();
                    GfMenuTypes::Param param;
                    param.m_menuId = reference;
                    GfMenuFullScreen::registLayerParam(0x34, param);
                    GfMenuObject::changeFSSubLayer(acc.m_handle, 2, 0x35, true);
                    GfMenuObjUtil::playSECommonDecide();
                } else {
                    GfMenuManager::openCommonWindow(0xAA);
                }
            } else {
                m_owner->m_exitHandle = acc.m_handle;
                m_owner->m_seq.clear();
                m_owner->m_seq.addJob(&GfMenuObjMercenaryTop::seqCanNotOrder);
                GfMenuObject::disableFSInput();
            }
        } else if (event.m_param1 == 2) {
            m_owner->sendOpenOrMain(acc.searchSibiling("LAY_zone"), 0);
            GfDataMercenaries::clearNewMission(
                m_owner->m_missionList->getContents(m_owner->m_missionList->getIndex(false)).m_id);
            GfMenuObjUtil::playSECommonCancel();
            mm::mtl::FixStr<32> name;
            name.format("IMG_mis_sel_item_base@%02d", m_owner->m_missionList->getIndex(true) + 1);
            {
                ui::UIObjectAcc base(acc.m_handle, name.m_str);
                base.loadDefColor();
            }
            int ctrl = GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_mis_sel_list"), 2, 1);
            GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
            GfMenuObjUtil::setCommonFadeOut(acc.searchChild("LAY_mis_sel_detail"), 1, 2);
            GfMenuObject::disableFSInput();
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
        }
        break;
    case 0x21:
        if (event.m_param0 == 1) {
            m_owner->m_missionList->setIndex(0);
        }
        if (m_owner->m_missionList->getSize() != 0) {
            GfMenuObject::resetInputSelection(acc.m_handle);
            GfMenuObject::setupInputSelectionFromList(acc.m_handle, *m_owner->m_missionList);
        }
    {
        int ctrl = GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_mis_sel_list"), 1, 1);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
    }
        GfMenuObjUtil::setCommonFadeIn(acc.searchChild("LAY_mis_sel_detail"), 1, 2);
        acc.setDisp(true);
        GfMenuObjOperationInfo::setGuideText(0x24, 0);
        GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        break;
    case 0x100: {
        GfMenuObjMercenaryTop* owner = m_owner;
        GfMenuBladeList::TeamSetup team;
        team.m_type = 3;
        team.m_team = 0;
        team.m_param.m_pageRowSize = 3;
        team.m_keepEmpty = false;
        owner->m_bladeList->clear();
        owner->m_bladeList->setupFromTeam(team);
        m_owner->refreshMissionList();
        GfMenuObject::enableFSInput(1);
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
