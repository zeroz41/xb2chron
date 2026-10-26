#include "classes/gf/GfGameSalvage.h"
#include "classes/ml/DevClock.h"
#include "ml/PadVibrationInfo.h"
#include "classes/fw/PadManager.h"
#include "gf/GfGameUtil.h"
#include "gf/GfItemUtil.h"
#include "classes/gf/GfGameSpeed.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/PlayerCamera.h"
#include "classes/gf/GfMenuFieldSkill.h"
#include "classes/gf/GfMenuObjButtonChallenge2.h"
#include "classes/gf/GfMenuObjSalvage.h"
#include "classes/gf/SCOM_ACHIEV_INC.h"
#include "classes/gf/SCOM_QUEST_GIMMICK.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/StateSalvageWait.h"
#include "classes/gf/StateSalvageTBoxCheck.h"
#include "classes/gf/StateSalvageErrorMessage.h"
#include "classes/gf/StateSalvageItemSelect.h"
#include "classes/gf/StateSalvageSetupFadeOut.h"
#include "classes/gf/StateSalvageLoad.h"
#include "classes/gf/StateSalvageSetupFadeIn.h"
#include "classes/gf/StateSalvageSkillCheck.h"
#include "classes/gf/StateSalvageStartVoice.h"
#include "classes/gf/StateSalvageDiveStart.h"
#include "classes/gf/StateSalvageDiveWait.h"
#include "classes/gf/StateSalvageDiveEnd.h"
#include "classes/gf/StateSalvageDiveFadeOut.h"
#include "classes/gf/StateSalvageDiveFadeWait.h"
#include "classes/gf/StateSalvageDiveFadeIn.h"
#include "classes/gf/StateSalvageClimbStart.h"
#include "classes/gf/StateSalvageResult.h"
#include "classes/gf/StateSalvageResultUi.h"
#include "classes/gf/StateSalvagePartyFormDelay.h"
#include "classes/gf/StateSalvageCamWait.h"
#include "classes/gf/StateSalvageFinish.h"
#include "gf/GfDataSalvage.h"
#include "classes/gf/GfComBehaviorSalvage.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObjCommonText.h"
#include "classes/gf/GfMenuObjCylinderSelect.h"
#include "classes/gf/SCOM_FADE.h"
#include "classes/gmk/AGmkBase.h"
#include "ml/MTRand.h"
#include "mm/Col4.h"
#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "plugin/Bdat.h"
#include "math.h"

namespace gf {

// the state the salvage game goes to when the game is being destroyed (the name is not the original's)
static const unsigned int SALVAGE_STATE_DESTROY = 20;

void StateSalvageWait::enter(GfGameSalvage* salvage, ai::State* prev) {}

void StateSalvageWait::leave(GfGameSalvage* salvage, ai::State* next) {}

void StateSalvageWait::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {}

void StateSalvageTBoxCheck::enter(GfGameSalvage* salvage, ai::State* prev) {}

void StateSalvageTBoxCheck::leave(GfGameSalvage* salvage, ai::State* next) {}

void StateSalvageTBoxCheck::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (salvage->isTboxExist()) {
        requestState(2);
    } else {
        requestState(3);
    }
}

void StateSalvageErrorMessage::enter(GfGameSalvage* salvage, ai::State* prev) {
    m_pContext = GfMenuCallContext::create();
    GfMenuObjCommonText::open(m_pContext, 14, 0);
}

void StateSalvageErrorMessage::leave(GfGameSalvage* salvage, ai::State* next) {
    if (m_pContext != nullptr) {
        m_pContext->release();
        m_pContext = nullptr;
    }
}

void StateSalvageErrorMessage::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (m_pContext->isTerm()) {
        requestState(0);
    }
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
}

void StateSalvageItemSelect::enter(GfGameSalvage* salvage, ai::State* prev) {
    unsigned int item = static_cast<unsigned short>(
        Bdat::getValCheck(salvage->getBindedBdatFp(), "SpecialItem", salvage->getBindedBdatId(), 2));
    m_pContext = GfMenuCallContext::create();
    GfMenuObjCylinderSelect::open(m_pContext, item);
    GfGameUtil::setDispByGmkType(static_cast<gmk::GmkType>(31), false);
    GfEvent::callSalvageStateChange(3);
}

void StateSalvageItemSelect::leave(GfGameSalvage* salvage, ai::State* next) {
    if (m_pContext != nullptr) {
        m_pContext->release();
        m_pContext = nullptr;
    }
}

void StateSalvageItemSelect::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (m_pContext->isTerm() && m_pContext->m_results.size() != 0) {
        GfMenuCallContext::GfMenuResult result;
        m_pContext->popResult(result);
        if (result.m_value != 0) {
            requestState(SALVAGE_STATE_DESTROY);
        } else {
            salvage->m_item = result.m_id;
            GfItemUtil::addItemBox(result.m_id, -1);
            requestState(m_stateID + 1);
        }
    }
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
}

void StateSalvageSetupFadeOut::enter(GfGameSalvage* salvage, ai::State* prev) {
    ml::DevClock::getClockNow(m_clock);
    SCOM_FADE::create(0, 10, mm::Col4::black);
    GfEvent::callSalvageStateChange(4);
}

void StateSalvageSetupFadeOut::leave(GfGameSalvage* salvage, ai::State* next) {
    salvage->applyPartyForm();
    salvage->setPartyDisp(false);
}

void StateSalvageSetupFadeOut::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    float time = 0.0f;
    ml::DevClock::getTimeNow(time, m_clock);
    if (time >= 0.4f) {
        requestState(m_stateID + 1);
    }
}

void StateSalvageLoad::enter(GfGameSalvage* salvage, ai::State* prev) {
    salvage->createModel();
}

void StateSalvageLoad::leave(GfGameSalvage* salvage, ai::State* next) {
    mm::Mat44 mtx;
    if (salvage->getEventOrigin(mtx) && salvage->isValidModel()) {
        mm::Vec3 pos(mtx.m[3][0], mtx.m[3][1], mtx.m[3][2]);
        float rotY = atan2f(mtx.m[2][0], mtx.m[2][2]);
        salvage->setModelTransform(pos, rotY * 57.295776f);
        salvage->createCameraDiveStart(pos, rotY);
    }
    GfGameParty::refreshPartyMemberPosition();
}

void StateSalvageLoad::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (salvage->isValidModel()) {
        requestState(m_stateID + 1);
    }
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
}

void StateSalvageSetupFadeIn::enter(GfGameSalvage* salvage, ai::State* prev) {
    ml::DevClock::getClockNow(m_clock);
    salvage->fn_7100315A84(false);
    SCOM_FADE::create(0, 10, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    GfEvent::callSalvageStateChange(6);
}

void StateSalvageSetupFadeIn::leave(GfGameSalvage* salvage, ai::State* next) {}

void StateSalvageSetupFadeIn::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    float time = 0.0f;
    ml::DevClock::getTimeNow(time, m_clock);
    if (time >= 0.9f) {
        requestState(m_stateID + 1);
    }
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
}

void StateSalvageSkillCheck::leave(GfGameSalvage* salvage, ai::State* next) {}

void StateSalvageSkillCheck::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
    if (!GfMenuFieldSkill::isRunning()) {
        requestState(m_stateID + 1);
    }
}

void StateSalvageStartVoice::enter(GfGameSalvage* salvage, ai::State* prev) {
    ml::DevClock::getClockNow(m_clock);
    if (salvage->m_skillLevel != 0) {
        salvage->playVoice(static_cast<GfGameSalvage::VoiceType>(1));
    } else {
        salvage->playVoice(static_cast<GfGameSalvage::VoiceType>(0));
    }
}

void StateSalvageStartVoice::leave(GfGameSalvage* salvage, ai::State* next) {}

void StateSalvageStartVoice::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
    if (salvage->isVoiceEnd()) {
        requestState(m_stateID + 1);
    }
}

void StateSalvageDiveStart::enter(GfGameSalvage* salvage, ai::State* prev) {
    salvage->clearLogButtonChallenge();
    salvage->playAnimation(static_cast<GfGameSalvage::AnimationType>(1));
    salvage->playCameraDiveStart();
    for (int i = 0; i < 3; i++) {
        m_pContexts[i] = nullptr;
    }
    m_count = 0;
    m_currentId = 0;
    m_successCount = 0;
    for (int i = 0; i < 3; i++) {
        m_ids[i] = salvage->getButtonChallengeId(i);
    }
    if (GfComBehaviorSalvage* behavior = salvage->getGfComBehaviorSalvage()) {
        behavior->m_stepCallback.set(this, &StateSalvageDiveStart::callback);
    }
}

void StateSalvageDiveStart::callback() {
    if (m_count < 3) {
        int index = m_count++;
        m_currentId = m_ids[index];
        GfMenuCallContext*& context = m_pContexts[index];
        if (context != nullptr) {
            if (!context->isTerm()) {
                GfMenuObjButtonChallenge2::close(context);
            }
            context->reset();
        } else {
            context = GfMenuCallContext::create();
        }
        GfMenuObjButtonChallenge2::OptionParam param;
        GfMenuObjButtonChallenge2::open(context, m_currentId, param);
        GfGameSpeed::setSalvageSpeed((3 - m_count) * 0.05f + 0.1f);
    }
}

void StateSalvageDiveStart::leave(GfGameSalvage* salvage, ai::State* next) {
    if (GfComBehaviorSalvage* behavior = salvage->getGfComBehaviorSalvage()) {
        behavior->m_stepCallback.m_invoker = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        if (m_pContexts[i] != nullptr) {
            m_pContexts[i]->release();
            m_pContexts[i] = nullptr;
        }
    }
}

void StateSalvageDiveWait::enter(GfGameSalvage* salvage, ai::State* prev) {}

void StateSalvageDiveWait::leave(GfGameSalvage* salvage, ai::State* next) {}

void StateSalvageDiveWait::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
    if (salvage->isCameraDive()) {
        salvage->playCameraDive();
        requestState(m_stateID + 1);
    }
}

void StateSalvageDiveEnd::enter(GfGameSalvage* salvage, ai::State* prev) {}

void StateSalvageDiveEnd::leave(GfGameSalvage* salvage, ai::State* next) {}

void StateSalvageDiveEnd::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
    if (salvage->isAnimationEnd()) {
        requestState(m_stateID + 1);
    }
}

void StateSalvageDiveFadeOut::enter(GfGameSalvage* salvage, ai::State* prev) {
    ml::DevClock::getClockNow(m_clock);
    SCOM_FADE::create(0, 10, mm::Col4::black);
}

void StateSalvageDiveFadeOut::leave(GfGameSalvage* salvage, ai::State* next) {}

void StateSalvageDiveFadeOut::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    float time = 0.0f;
    ml::DevClock::getTimeNow(time, m_clock);
    if (time >= 0.9f) {
        requestState(m_stateID + 1);
    }
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
}

void StateSalvageDiveFadeWait::leave(GfGameSalvage* salvage, ai::State* next) {
    salvage->destroyCameraDive();
    mm::Mat44 mtx;
    if (salvage->getEventOrigin(mtx)) {
        mm::Vec3 pos(mtx.m[3][0], mtx.m[3][1], mtx.m[3][2]);
        float rotY = atan2f(mtx.m[2][0], mtx.m[2][2]);
        salvage->createCameraClimb(salvage->getClimbAnimationType(), pos, rotY);
    }
}

void StateSalvageDiveFadeWait::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    float time = 0.0f;
    ml::DevClock::getTimeNow(time, m_clock);
    if (time >= 2.0f) {
        requestState(m_stateID + 1);
    }
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
}

void StateSalvageDiveFadeIn::enter(GfGameSalvage* salvage, ai::State* prev) {
    ml::DevClock::getClockNow(m_clock);
    SCOM_FADE::create(0, 10, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    salvage->playClimbReady();
    salvage->playWireStart(0.0f, 2.0f, 0.3f);
}

void StateSalvageDiveFadeIn::leave(GfGameSalvage* salvage, ai::State* next) {}

void StateSalvageDiveFadeIn::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    float time = 0.0f;
    ml::DevClock::getTimeNow(time, m_clock);
    if (time >= 0.9f) {
        requestState(m_stateID + 1);
    }
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
}

void StateSalvageClimbStart::enter(GfGameSalvage* salvage, ai::State* prev) {
    m_animType = salvage->getClimbAnimationType();
    m_step = 0;
    salvage->playClimb();
    salvage->playCameraClimb();
    mm::Mat44 mtx;
    if (salvage->getEventTbox(mtx)) {
        mm::Vec3 pos(mtx.m[3][0], mtx.m[3][1], mtx.m[3][2]);
        salvage->createCameraCut01(pos, atan2f(mtx.m[2][0], mtx.m[2][2]));
    }
    if (GfComBehaviorSalvage* behavior = salvage->getGfComBehaviorSalvage()) {
        behavior->m_stepCallback.set(this, &StateSalvageClimbStart::callback);
    }
}

void StateSalvageClimbStart::leave(GfGameSalvage* salvage, ai::State* next) {
    if (GfComBehaviorSalvage* behavior = salvage->getGfComBehaviorSalvage()) {
        behavior->m_stepCallback.m_invoker = nullptr;
    }
}

void StateSalvageClimbStart::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
    if (salvage->isClimbEnd() && salvage->isCameraClimbEnd()) {
        requestState(m_stateID + 1);
    }
}

void StateSalvageResult::enter(GfGameSalvage* salvage, ai::State* prev) {
    ml::DevClock::getClockNow(m_clock);
    m_vibrated = false;
    salvage->destroyCameraClimb();
    salvage->playCameraCut01();
    salvage->execPop();
}

void StateSalvageResult::leave(GfGameSalvage* salvage, ai::State* next) {
    salvage->fn_7100315A84(true);
}

void StateSalvageResult::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
    float time = 0.0f;
    ml::DevClock::getTimeNow(time, m_clock);
    if (time >= 1.0f && !m_vibrated) {
        m_vibrated = true;
        int vibration;
        switch (salvage->getTBoxNum()) {
        case 1:
            vibration = 2;
            break;
        case 2:
            vibration = 8;
            break;
        case 3:
            vibration = 9;
            break;
        default:
            vibration = -1;
            break;
        }
        if (vibration >= 0) {
            fw::PadManager::playVibration(ml::PadVibrationInfo(vibration));
        }
    }
    if (salvage->isCameraCut01End()) {
        requestState(m_stateID + 1);
    }
}

void StateSalvageResultUi::enter(GfGameSalvage* salvage, ai::State* prev) {
    salvage->applyPartyForm();
    GfGameSalvage::RaffleRet ret;
    salvage->getRaffleResult(ret);
    m_pContext = GfMenuCallContext::create();
    GfMenuObjSalvage::ResultParam param;
    unsigned int point;
    if (ret.m_rank == 4) {
        param.m_rank = 1;
        point = 1;
    } else if (ret.m_rank == 5) {
        param.m_rank = 2;
        point = 3;
    } else if (ret.m_rank == 6) {
        param.m_rank = 3;
        point = 6;
    } else {
        point = 0;
    }
    salvage->addSalvagerPoint(point);
    GfMenuObjSalvage::openResult(m_pContext, param);
    SCOM_ACHIEV_INC::addTotalCount(4, 1);
    SCOM_ACHIEV_INC::create(4, 1, 0);
}

void StateSalvageResultUi::leave(GfGameSalvage* salvage, ai::State* next) {
    if (m_pContext != nullptr) {
        m_pContext->release();
        m_pContext = nullptr;
    }
    salvage->setPartyDisp(true);
    SCOM_QUEST_GIMMICK::createSalvage(gmk::getBindedGmkInst(GfGameSalvage::get()->m_pHandle)->m_bdatId, 0.0f);
}

void StateSalvageResultUi::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    if (GfManager::isDestroyNow()) {
        requestState(SALVAGE_STATE_DESTROY);
    }
    if (m_pContext->isTerm()) {
        requestState(m_stateID + 1);
    }
}

void StateSalvagePartyFormDelay::enter(GfGameSalvage* salvage, ai::State* prev) {
    ml::DevClock::getClockNow(m_clock);
}

void StateSalvagePartyFormDelay::leave(GfGameSalvage* salvage, ai::State* next) {
    PlayerCamera::setOnceOff();
    salvage->destroyCameraCut01();
    salvage->destroyModel();
    salvage->createLog();
}

void StateSalvagePartyFormDelay::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    float time = 0.0f;
    ml::DevClock::getTimeNow(time, m_clock);
    if (time >= 0.2f) {
        requestState(m_stateID + 1);
    }
}

void StateSalvageCamWait::enter(GfGameSalvage* salvage, ai::State* prev) {
    ml::DevClock::getClockNow(m_clock);
}

void StateSalvageCamWait::leave(GfGameSalvage* salvage, ai::State* next) {}

void StateSalvageCamWait::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    float time = 0.0f;
    ml::DevClock::getTimeNow(time, m_clock);
    if (time >= 1.0f) {
        requestState(m_stateID + 1);
    }
}

void StateSalvageFinish::enter(GfGameSalvage* salvage, ai::State* prev) {
    ml::DevClock::getClockNow(m_clock);
}

void StateSalvageFinish::leave(GfGameSalvage* salvage, ai::State* next) {
    GfGameUtil::setDispByGmkType(static_cast<gmk::GmkType>(31), true);
    GfEvent::callSalvageStateChange(SALVAGE_STATE_DESTROY);
}

void StateSalvageFinish::update(GfGameSalvage* salvage, const fw::UpdateInfo& info) {
    requestState(0);
}

}  // namespace gf
