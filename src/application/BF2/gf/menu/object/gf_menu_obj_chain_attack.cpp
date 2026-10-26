#include "classes/gf/GfMenuObjChainAttack.h"
#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/gf/GfMenuObjChainAttack/ExtendListener.h"
#include "classes/gf/GfMenuObjChainAttack.h"
#include "classes/gf/GfMenuObjChainAttack/ExtendListener.h"
#include "classes/gf/GfMenuObjChainAttack/StartListener.h"
#include "classes/gf/GfMenuObjChainAttack/StartListener.h"
#include "classes/gf/GfMenuObjArtsPalette.h"
#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

#include <string.h>

namespace gf {

GfMenuObjChainAttack::GfMenuObjChainAttack(unsigned int handle)
    : GfMenuObject(handle), pad_30(nullptr), pad_38(nullptr), pad_40(nullptr), pad_48(nullptr), pad_50(nullptr) {}

GfMenuObjChainAttack::~GfMenuObjChainAttack() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjChainAttack::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjChainAttack::update() {
    GfMenuObject::update();
}

bool GfMenuObjChainAttack::isEnableSelect(unsigned int id, int select) {
    ui::UIObjectAcc acc(id);
    bool enable;
    if (strcmp(acc.getName(), "LAY_turn_sel") != 0) {
        enable = true;
    } else {
        enable = GfMenuReference::getReferenceNumber(select) == 0;
    }
    return enable;
}

void GfMenuObjChainAttack::openStart(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc start(acc.searchChild("LAY_start"));
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(start.m_handle, event, 0.0f);
        GfMenuObject::startCallContext(context, 0x54, start.m_handle);
    }
}

void GfMenuObjChainAttack::openStatus(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc status(acc.searchChild("LAY_status"));
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(status.m_handle, event, 0.0f);
        GfMenuObjArtsPalette::startChainAttack();
        GfMenuObjBladeChange::startChainAttack(context);
    }
}

void GfMenuObjChainAttack::closeStatus() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc status(acc.searchChild("LAY_status"));
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(status.m_handle, event, 0.0f);
        GfMenuObjArtsPalette::exitChainAttack();
        GfMenuObjBladeChange::exitChainAttack();
    }
}

void GfMenuObjChainAttack::openResult(const ResultParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc result(acc.searchChild("LAY_result"));
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0Short = param.pad_0;
        event.m_param1 = param.pad_4;
        GfMenuObject::sendEvent(result.m_handle, event, 0.0f);
    }
}

void GfMenuObjChainAttack::closeResult() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc result(acc.searchChild("LAY_result"));
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(result.m_handle, event, 0.0f);
    }
}

void GfMenuObjChainAttack::openFullBurst(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        ui::UIObjectAcc burst(acc.searchChild("LAY_full_burst"));
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(burst.m_handle, event, 0.0f);
        GfMenuObject::startCallContext(context, 0x54, burst.m_handle);
    }
}

void GfMenuObjChainAttack::openRoundExtend() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc extend(acc.searchChild("LAY_extend"));
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(extend.m_handle, event, 0.0f);
    }
}

void GfMenuObjChainAttack::closeRoundExtend() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc extend(acc.searchChild("LAY_extend"));
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(extend.m_handle, event, 0.0f);
    }
}

void GfMenuObjChainAttack::changeCharacter(unsigned int character) {
    GfMenuObjUtil::playSE(0x34);
}

void GfMenuObjChainAttack::fn_71003BF974(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x54));
    ui::UIObjectAcc start(acc.searchChild("LAY_ovk_start"));
    ui::EventData event;
    event.m_type = 0x21;
    GfMenuObject::sendEvent(start.m_handle, event, 0.0f);
    if (context != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        GfMenuObject::startCallContext(context, 0x54, start.m_handle);
    }
}

void GfMenuObjChainAttack::StartListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 1) {
            GfMenuObject::termCallContext(acc.m_handle);
        }
        break;
    case 0x21: {
        ui::UIObjectAcc base(acc.m_handle, "IMG_start_base");
        base.startAnimationFromID(1, false);
        GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_in_r";
        param.m_setDefault = true;
        param.m_startFlags = 8;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, "TXT_start_caption");
        GfMenuObjUtil::playSE(0x33);
        acc.setDisp(true);
        break;
    }
    case 0xC: {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_setDefault = true;
        param.m_startFlags = 10;
        param.m_eventId = 1;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        break;
    }
    }
}

void GfMenuObjChainAttack::ExtendListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state = 0;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        break;
    case 0x21:
        if (m_state == 0) {
            acc.setDisp(true);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l_early";
            param.m_setDefault = true;
            param.m_eventId = 1;
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state = 1;
        }
        break;
    case 0x22:
        if (m_state == 1) {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_out_r_early";
            param.m_setDefault = true;
            param.m_eventId = 2;
            param.m_startFlags = 10;
            GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
            m_state = 0;
        }
        break;
    }
}

}  // namespace gf
