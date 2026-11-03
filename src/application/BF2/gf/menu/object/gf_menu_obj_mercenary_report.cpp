#include "classes/gf/GfMenuObjMercenaryReport.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuObjBlKizunaRing.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjMercenaryReport/MainListener.h"
#include "classes/gf/GfMenuObjMercenaryReport/RewardListener.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
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

// initialize (0x710043D45C) is not here yet: see the report

void GfMenuObjMercenaryReport::finalize() {
    GfMenuObject::finalize();
}

// update and seqDispReward are not here yet: see the report

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

// seqStart is not here yet: see the report

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

// seqDispBlade, seqDispInfo, seqClose and seqCheckAchive are not here yet: see the report

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

template bool gf::GfMenuSequence<gf::GfMenuObjMercenaryReport, 10>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjMercenaryReport, 10>>(const mm::mtl::Delegate<bool()>*);

namespace gf {

}  // namespace gf
