#include "classes/gf/GfMenuObjMercenaryForm.h"
#include "classes/gf/GfGameVoice.h"
#include "classes/gf/GfMenuBladeList.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuIDList.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/SCOM_FIELD_VOICE.h"
#include "classes/gf/GfMenuObjMercenaryForm/MainListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/ApplyListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/BlImgListener.h"
#include "classes/gf/GfMenuObjMercenaryForm/FormListener.h"
#include "classes/gf/GfMenuObjCmnStatus.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/ui/UICtrlCursorSelect.h"
#include "classes/ui/UISelectObjList.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjMercenaryForm::GfMenuObjMercenaryForm(unsigned int handle)
    : GfMenuObject(handle), m_teamId(0), m_unitBlades(nullptr), m_listBlades(nullptr), m_unitSelect(nullptr),
      m_unitCursor(nullptr), m_listSelect(nullptr), m_listCursor(nullptr), m_presetSelect(nullptr),
      m_presetCursor(nullptr), m_context(nullptr), m_numbers(), pad_100(0), m_waitFrames(0), m_seq(this),
      m_seqStep(false), m_subSeq(this), m_bladeIds(), pad_8F0(false), m_voice(nullptr), m_leaveVoice(-1),
      m_leaveRequest(false), m_voiceStopped(false) {
    for (int i = 0; i < 8; i++) {
        m_numbers[i] = GfMenuReferenceNumber::create();
    }
    m_context = GfMenuCallContext::create();
}

GfMenuObjMercenaryForm::~GfMenuObjMercenaryForm() {
    for (int i = 0; i < 8; i++) {
        m_numbers[i] = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        if (m_presetBlades[i] != nullptr) {
            m_presetBlades[i]->release();
            m_presetBlades[i] = nullptr;
        }
    }
    if (m_context != nullptr) {
        m_context->release();
        m_context = nullptr;
    }
    if (m_presetCursor != nullptr) {
        m_presetCursor->release();
        m_presetCursor = nullptr;
    }
    if (m_presetSelect != nullptr) {
        m_presetSelect->release();
        m_presetSelect = nullptr;
    }
    if (m_listCursor != nullptr) {
        m_listCursor->release();
        m_listCursor = nullptr;
    }
    if (m_listSelect != nullptr) {
        m_listSelect->release();
        m_listSelect = nullptr;
    }
    if (m_unitCursor != nullptr) {
        m_unitCursor->release();
        m_unitCursor = nullptr;
    }
    if (m_unitSelect != nullptr) {
        m_unitSelect->release();
        m_unitSelect = nullptr;
    }
    if (m_listBlades != nullptr) {
        m_listBlades->release();
        m_listBlades = nullptr;
    }
    if (m_unitBlades != nullptr) {
        m_unitBlades->release();
        m_unitBlades = nullptr;
    }
    if (m_formSelect != nullptr) {
        m_formSelect->release();
        m_formSelect = nullptr;
    }
    if (m_formCursor != nullptr) {
        m_formCursor->release();
        m_formCursor = nullptr;
    }
    if (m_idList != nullptr) {
        m_idList->release();
        m_idList = nullptr;
    }
    for (int i = 0; i < 3; i++) {
        if (m_refs[i] != nullptr) {
            m_refs[i]->release();
            m_refs[i] = nullptr;
        }
    }
}

void GfMenuObjMercenaryForm::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjMercenaryForm::update() {
    if (!m_seq.m_jobs.empty()) {
        if (m_leaveRequest && GfMenuObjUtil::fn_7100492C88()) {
            m_seqStep = false;
            m_seq.clear();
            m_seq.addJob(&GfMenuObjMercenaryForm::seqLeaveBlade);
            if (m_leaveVoice != -1) {
                GfGameVoice::fn_71002F1F64(m_leaveVoice);
                m_leaveVoice = -1;
            }
            m_leaveRequest = false;
        }
    }
    m_seq.update();
    m_subSeq.update();
    if (m_waitFrames != 0) {
        m_waitFrames--;
    }
    GfMenuObject::update();
}


// seqLeaveBlade is not here yet

void GfMenuObjMercenaryForm::setDetailBladePos(unsigned int handle) {
    ui::UIObjectAcc detail(m_handle, "LAY_form_bl_detail_bl");
    if (handle == 0) {
        detail.setDisp(false);
    } else {
        ui::UIObjectAcc blade(handle);
        mm::Rect<short> rect;
        blade.getRect(rect, 1);
        mm::Pnt<short> pos;
        pos.x = rect.x;
        pos.y = rect.y;
        detail.setPos(pos);
        detail.setDisp(true);
    }
}

void GfMenuObjMercenaryForm::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    case 2: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_out = 1;
        param.m_preset = 6;
        param.m_startFlag1 = true;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

inline void GfMenuObjMercenaryForm::sendOpenOrFormMain(unsigned int handle, int param) {
    unsigned int target = handle != 0 ? handle : ui::UIObjectAcc(m_handle, "LAY_form_main").m_handle;
    ui::EventData open;
    open.m_type = 0x21;
    open.m_param0 = param;
    GfMenuObject::sendEvent(target, open, 0.0f);
}

void GfMenuObjMercenaryForm::FormListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        pad_0C = 0;
        pad_10 = 0;
        GfMenuObjOperationInfo::setGuideText(0x25, 0);
        GfMenuObjCmnStatus::openBlStatus(0, -1);
        break;
    case 3:
        if (event.m_param0 == 0) {
            break;
        }
        if (event.m_param0 == 2) {
            m_owner->sendOpenOrFormMain(acc.searchSibiling("LAY_leader"), 0);
        }
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 0x102: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 1;
        param.m_eventId = 2;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        GfMenuObjCmnStatus::closeBlStatus();
        break;
    }
    case 0x103: {
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 6;
        param.m_out = 0;
        param.m_eventId = 1;
        GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
        m_owner->sendOpenOrFormMain(acc.searchChild("LAY_form_list_bl"), 1);
        GfMenuObjOperationInfo::setGuideText(0x25, 0);
        GfMenuObjCmnStatus::openBlStatus(0, -1);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

// seqReturnMissionSelect, the Apply/Preset listeners, seqPresetSave, seqPresetLoad and LeaderListener are not here
// yet

void GfMenuObjMercenaryForm::ApplyListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        acc.setDisp(true);
        ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
        base.startAnimation("non", false);
        acc.setDispChild(false, "LAY_form_apply_caption");
        m_open = 0;
        break;
    }
    case 0xC:
        if (m_open == 1) {
            ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
            base.startAnimation("loop", false);
        }
        break;
    case 0x21:
        if (m_open == 0) {
            ui::UIObjectAcc caption(acc.m_handle, "LAY_form_apply_caption");
            caption.setDisp(true);
            caption.setAlpha(1.0f);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_r";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(caption.m_handle, param, nullptr);
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
                base.startAnimation("start", false);
                GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
            }
            acc.setDisp(true);
            m_open = 1;
        }
        break;
    case 0x22: {
        ui::UIObjectAcc base(acc.m_handle, "IMG_form_apply_base");
        base.startAnimation("non", false);
        {
            ui::UIObjectAcc caption(acc.m_handle, "LAY_form_apply_caption");
            int slot = GfMenuObjUtil::getCtrlID(caption.m_handle);
            if (slot != -1) {
                GfMenuObjUtil::stopCtrl(slot);
            }
            caption.setDisp(false);
        }
        m_open = 0;
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjMercenaryForm::BlImgListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 3:
        break;
    case 0x21:
        if (GfMenuReference::getReferenceBladeID(0) != 0) {
            acc.setDisp(true);
            acc.setAlpha(1.0f);
            m_owner->m_subSeq.clear();
            m_owner->m_subSeq.addJob(&GfMenuObjMercenaryForm::seqOpenImage);
        }
        break;
    case 0x22: {
        ui::UIObjectAcc image(acc.m_handle, "IMG_leader_bl_img");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_r";
        param.m_startFlags = 2;
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(image.m_handle, param, nullptr);
        break;
    }
    case 0x100: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu090_anim_leader";
        param.m_motion = "start";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObjUtil::playSE(0xF);
        break;
    }
    case 0x101: {
        acc.setScale(mm::Vec2(1.0f, 1.0f));
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "mnu090_anim_leader";
        param.m_motion = "end";
        param.m_setDefault = true;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        GfMenuObjUtil::playSE("se_fld_allmap_503");
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

// seqConfirmStart (wip/seqConfirmStart.cpp, 4 words off) is not here yet

bool GfMenuObjMercenaryForm::seqDepartureStart() {
    m_seqStep = false;
    m_seq.addJob(&GfMenuObjMercenaryForm::seqApperBlade);
    m_voice = SCOM_FIELD_VOICE::createMercenariesLeader(GfMenuReference::getReferenceBladeID(0));
    m_voiceStopped = false;
    return true;
}

bool GfMenuObjMercenaryForm::seqRevertBladeSet() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    bool done;
    if (!m_seqStep) {
        GfMenuManager::openCommonWindow(200);
        done = false;
        m_seqStep = true;
    } else if (GfMenuManager::isOpenCommonWindow()) {
        done = false;
    } else {
        GfMenuObject::returnFSSubLayer(this);
        done = true;
        m_seqStep = false;
    }
    return done;
}

}  // namespace gf
