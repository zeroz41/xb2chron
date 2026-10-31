#include "classes/gf/GfMenuObjMercenaryReport.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuObjBlKizunaRing.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjMercenaryReport/MainListener.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

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

// seqStart and RewardListener::reciveEvent are not here yet: see the report

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
