#include "classes/gf/GfMenuObjBtlchTelop.h"
#include "classes/gf/GfMenuObjBtlchTutorial.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfMenuAdapterManager.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuReferenceAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UIEventManager.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

GfMenuObjBtlchTelop::GfMenuObjBtlchTelop(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_ctrl(-1), m_number(), m_result(0) {
    m_number = GfMenuReferenceNumber::create();
}

GfMenuObjBtlchTelop::~GfMenuObjBtlchTelop() {
    m_number = nullptr;
}

void GfMenuObjBtlchTelop::initialize() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x88, main.m_handle);
#line 71
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuAdapterManager::beginCategory(4);
    {
        ui::UIObjectAcc acc(m_handle);
        GfMenuReferenceAdapter::create(acc.searchChild("TXT_wave_title"), m_number, false);
        GfMenuReferenceAdapter::create(acc.searchChild("TXT_wave_title_shadow"), m_number, false);
    }
    GfMenuAdapterManager::endCategory();
    GfMenuObject::initialize();
}

void GfMenuObjBtlchTelop::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBtlchTelop::update() {
    if (m_ctrl != -1 && !GfMenuObjUtil::isBusyCtrl(m_ctrl)) {
        m_ctrl = -1;
    }
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjBtlchTelop::open(GfMenuCallContext* context, const OpenParam& param) {
    bool result = false;
    if (GfMenuObjUtil::isValidExpansion(1) && GfGameManager::isBattleArenaActive() && GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x88));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = param.m_type;
            // the wave number (types 1 and 2) and the result (type 3)
            if (param.m_type == 1 || param.m_type == 2) {
                event.m_param1 = param.m_value;
            } else if (param.m_type == 3) {
                event.m_param1 = param.m_value;
            }
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(context, 0x88, acc.m_handle);
            result = true;
        } else if (context != nullptr) {
            context->abort();
        }
    } else if (context != nullptr) {
        context->abort();
    }
    return result;
}

void GfMenuObjBtlchTelop::forceClose() {
    if (GfMenuObjUtil::isValidExpansion(1) && GfGameManager::isBattleArenaActive()) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x88));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjBtlchTelop::reset() {
    ui::UIObjectAcc acc(m_handle);
    m_seq.clear();
    if (m_ctrl != -1) {
        GfMenuObjUtil::stopCtrl(m_ctrl);
        m_ctrl = -1;
    }
    ui::UIObjectAcc(m_animHandle).stopAnimation();
    acc.setDispChild(false, "LAY_start");
    acc.setDispChild(false, "LAY_start_title");
    acc.setDispChild(false, "LAY_start_bch");
    acc.setDispChild(false, "LAY_wave");
    acc.setDispChild(false, "LAY_wave_title");
    acc.setDispChild(false, "LAY_result");
    acc.setDispChild(false, "LAY_success_title");
    acc.setDispChild(false, "LAY_failed_title");
    acc.setDispChild(false, "LAY_timeup_title");
    acc.setDispChild(false, "LAY_result_info");
}

void GfMenuObjBtlchTelop::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        acc.setSuspend(true);
        m_open = 0;
        break;
    case 0x22:
        if (m_open == 1) {
            m_owner->reset();
            acc.setDisp(true);
            acc.setSuspend(false);
            GfMenuObject::termCallContext(acc.m_handle);
            m_open = 0;
        }
        break;
    case 0x21: {
        int type = event.m_param0;
        m_owner->reset();
        switch (type) {
        case 0:
            m_owner->m_seq.addJob(&GfMenuObjBtlchTelop::seqStartTitleOpen);
            break;
        case 1:
            m_owner->m_seq.addJob(&GfMenuObjBtlchTelop::seqWaveOpen);
            m_owner->m_number->setValue(event.m_param1);
            break;
        case 2:
            m_owner->m_seq.addJob(&GfMenuObjBtlchTelop::seqWaveOpen2);
            m_owner->m_number->setValue(event.m_param1);
            break;
        case 3:
            if (event.m_param1 == 1 || event.m_param1 == 2) {
                m_owner->m_seq.addJob(&GfMenuObjBtlchTelop::seqResultOpenFailed);
            } else if (event.m_param1 == 0) {
                m_owner->m_seq.addJob(&GfMenuObjBtlchTelop::seqResultOpenSuccess);
            }
            m_owner->m_result = event.m_param1;
            break;
        }
        if (m_owner->m_seq.m_jobs.empty()) {
            GfMenuObject::termCallContext(acc.m_handle);
        } else {
            acc.setDisp(true);
            acc.setSuspend(false);
            m_open = 1;
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjBtlchTelop::seqStartTitleOpen() {
    ui::UIObjectAcc start(m_handle, "LAY_start");
    start.setDisp(true);
    {
        ui::UIObjectAcc base(start.m_handle, "IMG_start_base");
        base.startAnimation("start_battlechallenge", false);
        m_animHandle = base.m_handle;
        if (!GfMenuObjBtlchTutorial::isOpen()) {
            GfMenuObjUtil::playSE("dlc_se_btl_chbtl001");
        }
    }
    {
        ui::UIObjectAcc title(start.m_handle, "LAY_start_title");
        title.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_zoom";
        param.m_motion = "fade_in";
        param.m_startFlags = 8;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
    }
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqStartOpen);
    return true;
}

bool GfMenuObjBtlchTelop::seqWaveOpen() {
    ui::UIObjectAcc wave(m_handle, "LAY_wave");
    wave.setDisp(true);
    {
        ui::UIObjectAcc base(wave.m_handle, "IMG_wave_base");
        base.startAnimation("start", false);
        m_animHandle = base.m_handle;
        if (!GfMenuObjBtlchTutorial::isOpen()) {
            GfMenuObjUtil::playSE("dlc_se_btl_chbtl002");
        }
    }
    {
        ui::UIObjectAcc title(wave.m_handle, "LAY_weve_title");
        title.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_startFlags = 8;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
    }
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqWaveFadeout);
    return true;
}

bool GfMenuObjBtlchTelop::seqWaveOpen2() {
    ui::UIObjectAcc wave(m_handle, "LAY_wave");
    wave.setDisp(true);
    {
        ui::UIObjectAcc base(wave.m_handle, "IMG_wave_base");
        base.startAnimation("start_time", false);
        m_animHandle = base.m_handle;
        if (!GfMenuObjBtlchTutorial::isOpen()) {
            GfMenuObjUtil::playSE("dlc_se_btl_chbtl002");
        }
    }
    {
        ui::UIObjectAcc title(wave.m_handle, "LAY_weve_title");
        title.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_startFlags = 8;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
    }
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqWaveFadeout2);
    return true;
}

bool GfMenuObjBtlchTelop::seqResultOpenSuccess() {
    ui::UIObjectAcc result(m_handle, "LAY_result");
    result.setDisp(true);
    {
        ui::UIObjectAcc base(result.m_handle, "IMG_result_base");
        base.startAnimation("start_success", false);
        m_animHandle = base.m_handle;
    }
    {
        ui::UIObjectAcc title(result.m_handle, "LAY_success_title");
        title.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_startFlags = 8;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
    }
    m_seq.addJob(&GfMenuObjBtlchTelop::seqCtrlWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqResultOpenSuccessSE);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqResultFadeoutSuccess);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqEnd);
    return true;
}

bool GfMenuObjBtlchTelop::seqResultOpenFailed() {
    ui::UIObjectAcc result(m_handle, "LAY_result");
    result.setDisp(true);
    {
        ui::UIObjectAcc base(result.m_handle, "IMG_result_base");
        base.startAnimation("start_failed", false);
        m_animHandle = base.m_handle;
    }
    {
        unsigned int handle = 0;
        if (m_result == 1) {
            handle = result.searchChild("LAY_failed_title");
        } else if (m_result == 2) {
            handle = result.searchChild("LAY_timeup_title");
        }
        ui::UIObjectAcc title(handle);
        title.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_l";
        param.m_startFlags = 8;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
    }
    m_seq.addJob(&GfMenuObjBtlchTelop::seqCtrlWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqResultOpenFailedSE);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqResultFadeoutFailed);
    return true;
}

bool GfMenuObjBtlchTelop::seqAnimWait() {
    bool done = true;
    if (m_animHandle != 0) {
        ui::UIObjectAcc anim(m_animHandle);
        if (anim.isPlayingAnimation()) {
            done = false;
        } else {
            m_animHandle = 0;
        }
    }
    return done;
}

bool GfMenuObjBtlchTelop::seqStartOpen() {
    ui::UIObjectAcc start(m_handle, "LAY_start");
    start.setDisp(true);
    {
        ui::UIObjectAcc base(start.m_handle, "IMG_start_base");
        base.startAnimation("start_start", false);
        m_animHandle = base.m_handle;
    }
    {
        ui::UIObjectAcc title(start.m_handle, "LAY_start_title");
        title.setDisp(false);
    }
    {
        ui::UIObjectAcc bch(start.m_handle, "LAY_start_bch");
        bch.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_zoom_2";
        param.m_motion = "fade_in";
        param.m_startFlags = 8;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(bch.m_handle, param, nullptr);
    }
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqStartFadeout);
    return true;
}

bool GfMenuObjBtlchTelop::seqStartFadeout() {
    ui::UIObjectAcc start(m_handle, "LAY_start");
    start.setDisp(true);
    {
        ui::UIObjectAcc base(start.m_handle, "IMG_start_base");
        base.startAnimation("end", false);
        m_animHandle = base.m_handle;
    }
    {
        ui::UIObjectAcc bch(start.m_handle, "LAY_start_bch");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_zoom";
        param.m_motion = "fade_out";
        param.m_startFlags = 10;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(bch.m_handle, param, nullptr);
    }
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqEnd);
    return true;
}

bool GfMenuObjBtlchTelop::seqEnd() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x22;
    GfMenuObject::sendEvent(main.m_handle, event, 0.0f);
    return true;
}

bool GfMenuObjBtlchTelop::seqWaveFadeout() {
    ui::UIObjectAcc wave(m_handle, "LAY_wave");
    wave.setDisp(true);
    {
        ui::UIObjectAcc base(wave.m_handle, "IMG_wave_base");
        base.startAnimation("end", false);
        m_animHandle = base.m_handle;
    }
    {
        ui::UIObjectAcc title(wave.m_handle, "LAY_weve_title");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_lr", "fade_in_l");
        param.m_startFlags = 10;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
    }
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqEnd);
    return true;
}

bool GfMenuObjBtlchTelop::seqWaveFadeout2() {
    ui::UIObjectAcc wave(m_handle, "LAY_wave");
    wave.setDisp(true);
    {
        ui::UIObjectAcc base(wave.m_handle, "IMG_wave_base");
        base.startAnimation("end_time", false);
        m_animHandle = base.m_handle;
    }
    {
        ui::UIObjectAcc title(wave.m_handle, "LAY_weve_title");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_lr", "fade_in_l");
        param.m_startFlags = 10;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
    }
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqEnd);
    return true;
}

bool GfMenuObjBtlchTelop::seqCtrlWait() {
    if (m_ctrl != -1) {
        if (GfMenuObjUtil::isBusyCtrl(m_ctrl)) {
            return false;
        }
        m_ctrl = -1;
    }
    return true;
}

bool GfMenuObjBtlchTelop::seqResultOpenSuccessSE() {
    return true;
}

bool GfMenuObjBtlchTelop::seqResultFadeoutSuccess() {
    ui::UIObjectAcc result(m_handle, "LAY_result");
    result.setDisp(true);
    {
        ui::UIObjectAcc base(result.m_handle, "IMG_result_base");
        base.startAnimation("end_success", false);
        m_animHandle = base.m_handle;
    }
    {
        ui::UIObjectAcc title(result.m_handle, "LAY_success_title");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_lr", "fade_in_l");
        param.m_startFlags = 10;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
    }
    return true;
}

bool GfMenuObjBtlchTelop::seqResultOpenFailedSE() {
    return true;
}

bool GfMenuObjBtlchTelop::seqResultFadeoutFailed() {
    ui::UIObjectAcc result(m_handle, "LAY_result");
    result.setDisp(true);
    {
        ui::UIObjectAcc base(result.m_handle, "IMG_result_base");
        base.startAnimation("end_failed", false);
        m_animHandle = base.m_handle;
    }
    {
        unsigned int handle = 0;
        if (m_result == 1) {
            handle = result.searchChild("LAY_failed_title");
        } else if (m_result == 2) {
            handle = result.searchChild("LAY_timeup_title");
        }
        ui::UIObjectAcc title(handle);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_lr", "fade_in_l");
        param.m_startFlags = 10;
        param.m_setDefault = true;
        m_ctrl = GfMenuObjUtil::startCtrl(title.m_handle, param, nullptr);
    }
    m_seq.addJob(&GfMenuObjBtlchTelop::seqAnimWait);
    m_seq.addJob(&GfMenuObjBtlchTelop::seqEnd);
    return true;
}

}  // namespace gf
