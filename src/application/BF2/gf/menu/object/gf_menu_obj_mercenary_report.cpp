#include "classes/gf/GfMenuObjMercenaryReport.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuObjBlKizunaRing.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjMercenaryReport/MainListener.h"
#include "classes/gf/GfMenuObjMercenaryReport/RewardListener.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfGameMercenaries.h"
#include "classes/gf/GfGameVoice.h"
#include "gf/GfDataMercenaries.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuMercenariesAdapter.h"
#include "classes/gf/GfMenuMissionAdapter.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuZoneAdapter.h"
#include "classes/ui/UIEventManager.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfMenuObjMercenaryRoot.h"
#include "classes/gf/GfMenuObjPopup.h"
#include "classes/gf/GfMenuObjQuestReward.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/Delegate.h"

namespace gf {

GfMenuObjMercenaryReport::GfMenuObjMercenaryReport(unsigned int handle)
    : GfMenuObject(handle), m_teamId(0), m_bladeList(nullptr), m_seq(this), m_rewardShown(false),
      m_rewardClosed(false), m_waitVoice(false), m_number(), m_rewardContext(nullptr), m_kizunaContext(nullptr),
      m_voice(-1) {
    m_number = GfMenuReferenceNumber::create();
    m_rewardContext = GfMenuCallContext::create();
    m_kizunaContext = GfMenuCallContext::create();
}

GfMenuObjMercenaryReport::~GfMenuObjMercenaryReport() {
    if (m_bladeList != nullptr) {
        m_bladeList->release();
        m_bladeList = nullptr;
    }
    if (m_kizunaContext != nullptr) {
        m_kizunaContext->release();
        m_kizunaContext = nullptr;
    }
    if (m_rewardContext != nullptr) {
        m_rewardContext->release();
        m_rewardContext = nullptr;
    }
    m_number = nullptr;
}

void GfMenuObjMercenaryReport::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    mm::mtl::FixStr<32> name;
    m_bladeList = GfMenuBladeList::create();
    GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("TXT_report_unit_zone"), 0, false);
    GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("IMG_reward_flag"), 2, false);
    GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_report_mission_name"), 0, 0, false);
    GfMenuMissionAdapter::createFromReferenceMission(acc.searchChild("TXT_reward_result"), 1, 0, false);
    GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("TXT_report_unit_idx_name"), 0, false);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild("IMG_bl_img"), 0x36, m_bladeList, 0, false);
    for (int i = 0; i < 6; i++) {
        name.format("IMG_report_unit_bl_face@%02d", i + 1);
        GfMenuCharDataAdapter* adapter =
            GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.m_str), 3, m_bladeList, i, false);
        if (adapter != nullptr) {
            name.format("LAY_report_unit_bl@%02d", i + 1);
            adapter->m_rowHandle = acc.searchChild(name.m_str);
        }
    }
    {
        ui::UIObjectAcc reward(acc.m_handle, "LAY_reward");
        GfMenuObjQuestReward::OpenParam param;
        param.pad_10 = m_number;
        param.m_handle = reward.searchChild("LAY_reward_info");
        param.pad_C = 1;
        GfMenuObjQuestReward::create(m_rewardContext, param, false);
#line 139
        RewardListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) RewardListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(reward.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
#line 143
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObjMainMenu2::setSystemKeyEnable(false);
    GfMenuObjMainMenu2::setCloseKeyEnable(false);
    GfMenuObject::initialize();
}

void GfMenuObjMercenaryReport::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMercenaryReport::update() {
    if (!m_seq.m_jobs.empty()) {
        if (m_waitVoice && GfMenuObjUtil::isVoiceSkip()) {
            m_rewardShown = false;
            m_seq.clear();
            m_seq.addJob(&GfMenuObjMercenaryReport::seqDispReward);
            m_waitVoice = false;
            if (m_voice != -1) {
                GfGameVoice::playStop(reinterpret_cast<GF_SCOM_HANDLE*>(m_voice));
                m_voice = -1;
            }
        }
        m_seq.update();
    }
    GfMenuObject::update();
}

bool GfMenuObjMercenaryReport::seqDispReward() {
    if (!m_rewardShown) {
        ui::UIObjectAcc acc(m_handle, "LAY_reward");
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        m_waitVoice = false;
        m_rewardShown = true;
        return false;
    }
    if (!m_rewardClosed) {
        return false;
    }
    m_rewardShown = false;
    m_seq.addJob(&GfMenuObjMercenaryReport::seqClose);
    return true;
}

void GfMenuObjMercenaryReport::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjMercenaryReport::seqStart);
        GfMenuObjOperationInfo::setGuideDisp(false);
        break;
    case 2: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 6;
        param.m_startFlag1 = true;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 3:
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjMercenaryReport::seqStart() {
    for (unsigned int i = 0; i < GfDataMercenaries::getTeamNum(); i++) {
        GfDataMercenaries::Team* team = GfDataMercenaries::getTeamByIndex(i);
        if (team != nullptr && GfDataMercenaries::isTeamStateReward(team->m_teamId)) {
            m_teamId = team->m_teamId;
            break;
        }
    }
    if (m_teamId == 0) {
        m_seq.addJob(&GfMenuObjMercenaryReport::seqEnd);
        return true;
    }
    unsigned int mission = GfDataMercenaries::getTeamMission(m_teamId);
    unsigned int zone = GfDataMercenaries::getMissionZoneID(mission);
    GfMenuReference::setReferenceTeamID(m_teamId);
    GfMenuReference::setReferenceMissionID(mission);
    GfMenuReference::setReferenceZoneID(zone);
    GfMenuObjMercenaryRoot::openBg(zone);
    m_number->m_value = mission;
    {
        GfMenuBladeList::TeamSetup setup;
        setup.m_keepEmpty = true;
        setup.m_type = 0;
        setup.m_team = m_teamId;
        m_bladeList->clear();
        m_bladeList->setupFromTeam(setup);
    }
    m_rewardShown = false;
    m_seq.addWait(15);
    m_seq.addJob(&GfMenuObjMercenaryReport::seqDispBlade);
    {
        ui::UIObjectAcc acc(m_handle, "LAY_main");
        acc.setDisp(true);
        mm::Rect<short> rect;
        mm::Rect<short> next;
        acc.getLayoutRect("blade_l_1", rect);
        acc.getLayoutRect("blade_l_2", next);
        GfMenuObjUtil::placeObjectH(acc.m_handle, "LAY_report_unit_bl@%02d", m_bladeList->getSize(),
                                    mm::Pnt<short>(rect.x + rect.w / 2, rect.y + rect.h / 2), next.x - rect.x);
    }
    GfMenuObjQuestReward::open(m_rewardContext, false);
    GfMenuObjPopup::OpenParam param;
    param.m_type = 8;
    param.m_value[0] = GfDataMercenaries::getMissionMapID(mission);
    param.m_value[1] = m_teamId;
    param.m_value[2] = GfDataMercenaries::getTeamLeader(m_teamId);
    GfMenuObjPopup::remove(param);
    return true;
}

void GfMenuObjMercenaryReport::RewardListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 0x21: {
        acc.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_zoom_2";
        param.m_motion = "fade_in";
        param.m_startFlags = 8;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        m_owner->m_rewardClosed = false;
        GfMenuObjUtil::playJingle(7);
        break;
    }
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::registTimer(acc.m_handle, 0, 2.0f, false);
        } else if (event.m_param0 == 2) {
            GfMenuObject::enableInput(acc.m_handle);
            GfMenuObjOperationInfo::add(acc.m_handle, 0, 0, 0);
        } else if (event.m_param0 == 3) {
            acc.setDispChild(false, "TXT_reward_complete");
            m_owner->m_rewardClosed = true;
        }
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObject::disableInput(acc.m_handle);
            GfMenuObjOperationInfo::remove(acc.m_handle, 0, 0, 0);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_emotion";
            param.m_motion = "fade_out";
            param.m_startFlags = 10;
            param.m_eventId = 3;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            GfMenuObjUtil::playSECommonDecide();
        }
        break;
    case 0xB: {
        acc.setDispChild(true, "TXT_reward_complete");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "sample";
        param.m_motion = "fadein";
        param.m_startFlags = 8;
        param.m_eventId = 2;
        int ctrl = GfMenuObjUtil::startCtrl(acc.searchChild("TXT_reward_complete"), param, nullptr);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        GfMenuObject::releaseTimer(acc.m_handle);
        break;
    }
    case 1:
        GfMenuObject::disableInput(acc.m_handle);
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjMercenaryReport::seqEnd() {
    if (GfMenuManager::isSwitchingFullScreen()) {
        return false;
    }
    GfMenuObject::changeFSSubLayer(m_handle, 2, 0x34, false);
    return true;
}

bool GfMenuObjMercenaryReport::seqDispBlade() {
    GfMenuObjUtil::ImageParam imageParam;
    ui::UIObjectAcc image(m_handle, "IMG_bl_img");
    if (!m_rewardShown) {
        ui::UIObjectAcc acc(m_handle, "LAY_bl_img");
        acc.setDisp(true);
        unsigned int blade = m_bladeList->getContents(0).m_blade;
        acc.setLayout(image.m_handle, "character");
        if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
            mm::Vec2 scale;
            image.getScale(scale);
            scale.x = imageParam.m_scale * scale.x;
            scale.y = imageParam.m_scale * scale.y;
            image.setScale(scale);
            GfMenuObjUtil::addPos(image.m_handle, imageParam.m_x, imageParam.m_y);
        }
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x200;
        param.m_curve = 1;
        param.m_time = 0.2f;
        GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
        GfMenuObjUtil::playSE("se_fld_allmap_503");
        m_voice = SCOM_FIELD_VOICE::createMercenariesResult(m_bladeList->getContents(0).m_blade);
        m_rewardShown = true;
        return false;
    }
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(image.m_handle))) {
        return false;
    }
    m_rewardShown = false;
    m_seq.addJob(&GfMenuObjMercenaryReport::seqDispInfo);
    return true;
}

bool GfMenuObjMercenaryReport::seqDispInfo() {
    ui::UIObjectAcc acc(m_handle, "LAY_report");
    ui::UIObjectAcc effect(acc.m_handle, "IMG_report_eff");
    if (!m_rewardShown) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        effect.startAnimation("start", false);
        effect.setDisp(true);
        GfMenuObjUtil::playSE(0x10);
        m_rewardShown = true;
        m_waitVoice = true;
        return false;
    }
    if (effect.isPlayingAnimation()) {
        return false;
    }
    m_rewardShown = false;
    m_seq.addWait(60);
    m_seq.addJob(&GfMenuObjMercenaryReport::seqDispReward);
    return true;
}

bool GfMenuObjMercenaryReport::seqClose() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (!m_rewardShown) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_startFlags = 10;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_report");
        GfMenuObjUtil::startCtrl(acc.m_handle, param, "LAY_bl_img");
        m_rewardShown = true;
        return false;
    }
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.searchChild("LAY_report")))) {
        return false;
    }
    acc.setDispChild(false, "LAY_bl_img");
    unsigned int mission = GfDataMercenaries::getTeamMission(m_teamId);
    GfGameMercenaries::execMissionRewardByTeamID(m_teamId);
    GfGameMercenaries::clearTeamMember(m_teamId);
    if (GfDataMercenaries::isEnableOrder(mission)) {
        GfGameMercenaries::setMissionFlag(mission, 1);
    }
    m_teamId = 0;
    m_seq.addWait(15);
    m_seq.addJob(&GfMenuObjMercenaryReport::seqCheckAchive);
    return true;
}

bool GfMenuObjMercenaryReport::seqCheckAchive() {
    if (m_bladeList->getSize() != 0) {
        while (m_bladeList->getSize() != 0) {
            if (GfMenuObjUtil::isBladeAchivementReleased(m_bladeList->getContents(0).m_blade)) {
                m_bladeList->getSize();  // the original calls it and drops the result
                ui::UIObjectAcc acc(m_handle, "LAY_main");
                unsigned int blade = m_bladeList->getContents(0).m_blade;
                GfMenuObjBlKizunaRing::openForMercenary(acc.m_handle, blade, 3);
                m_seq.addJob(&GfMenuObjMercenaryReport::seqWaitLoadKizuna);
                return true;
            }
            GfMenuBladeList* list = m_bladeList;
            list->m_list.erase(list->m_list.begin());
            list->subSize(1);
            list->m_changed = true;
        }
    }
    m_seq.addJob(&GfMenuObjMercenaryReport::seqStart);
    return true;
}

bool GfMenuObjMercenaryReport::seqWaitLoadKizuna() {
    if (GfMenuManager::isSwitchingFullScreen()) {
        return false;
    }
    m_kizunaContext->reset();
    if (!GfMenuObjBlKizunaRing::attach(m_kizunaContext)) {
        return false;
    }
    m_seq.addJob(&GfMenuObjMercenaryReport::seqWaitEndKizuna);
    return true;
}

bool GfMenuObjMercenaryReport::seqWaitEndKizuna() {
    if (!m_kizunaContext->isTerm() || GfMenuManager::isSwitchingFullScreen()) {
        return false;
    }
    m_seq.addJob(&GfMenuObjMercenaryReport::seqCheckAchive);
    return true;
}
}  // namespace gf

