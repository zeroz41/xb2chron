#include "ui/EventData.h"
#include "gf/GfMenuSequence.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/gf/GfMenuObjElementEff.h"
#include "classes/gf/GfMenuObjElementEff/MainListener.h"
#include "classes/gf/GfMenuObjElementEff.h"
#include "classes/gf/GfMenuObjElementEff/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjElementEff::GfMenuObjElementEff(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_ctrl(-1), m_combo(0), m_wait(0) {}

GfMenuObjElementEff::~GfMenuObjElementEff() {}

void GfMenuObjElementEff::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
    GfMenuObject::attachExternalCall(0x17, main);
#line 62
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::initialize();
}

void GfMenuObjElementEff::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjElementEff::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjElementEff::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0x21:
        acc.setDisp(true);
        m_owner->m_combo = event.m_param0;
        m_owner->m_ctrl = -1;
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjElementEff::seqInit);
        m_owner->m_seq.addJob(&GfMenuObjElementEff::seqOpen);
        m_owner->m_seq.addJob(&GfMenuObjElementEff::seqComboName);
        m_owner->m_seq.addJob(&GfMenuObjElementEff::seqLoop);
        break;
    case 0x22:
        m_owner->m_ctrl = -1;
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjElementEff::seqClose);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

bool GfMenuObjElementEff::seqInit() {
    m_ctrl = -1;
    ui::UIObjectAcc top(m_handle, "IMG_top");
    if (top.isPlayingAnimation()) {
        top.stopAnimation();
    }
    ui::UIObjectAcc bottom(m_handle, "IMG_bottom");
    if (bottom.isPlayingAnimation()) {
        bottom.stopAnimation();
    }
    return true;
}

bool GfMenuObjElementEff::seqOpen() {
    ui::UIObjectAcc top(m_handle, "IMG_top");
    ui::UIObjectAcc bottom(m_handle, "IMG_bottom");
    mm::mtl::FixStr<32> color;
    color.format("elemental%02d", GfMenuObjUtil::getElementComboAtr(m_combo));
    top.setDisp(true);
    top.startAnimation("start", false);
    top.setMulColor(color.m_str);
    bottom.setDisp(true);
    bottom.startAnimation("start", false);
    bottom.setAddColor(color.m_str);
    ui::UIStr name = GfMenuObjUtil::getElementComboName(m_combo);
    {
        ui::UIObjectAcc lay(m_handle, "LAY_combo_name");
        ui::UIObjectAcc(lay.m_handle, "TXT_combo_name").setText(name);
        ui::UIObjectAcc(lay.m_handle, "TXT_combo_name_shadow").setText(name);
        lay.setDisp(true);
        {
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(lay.m_handle, param, nullptr);
        }
        ui::UIObjectAcc eff(m_handle, "LAY_combo_name_eff");
        ui::UIObjectAcc(eff.m_handle, "TXT_combo_name_eff").setText(name);
        ui::UIObjectAcc(eff.m_handle, "TXT_combo_name_eff_shadow").setText(name);
        eff.setDisp(false);
    }
    GfMenuObjUtil::playSE(0x2F);
    m_ctrl = -1;
    return true;
}

bool GfMenuObjElementEff::seqComboName() {
    if (m_ctrl == -1) {
        m_ctrl = 0;
        m_wait = 37;
        return false;
    }
    if (--m_wait != 0) {
        return false;
    }
    ui::UIObjectAcc eff(m_handle, "LAY_combo_name_eff");
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 0x10000000;
    param.m_motionLib = "cmn_fade_motion_zoom";
    param.m_motion = "fade_out";
    param.m_startFlags = 10;
    GfMenuObjUtil::startCtrl(eff.m_handle, param, nullptr);
    return true;
}

bool GfMenuObjElementEff::seqLoop() {
    ui::UIObjectAcc top(m_handle, "IMG_top");
    ui::UIObjectAcc bottom(m_handle, "IMG_bottom");
    if (top.isPlayingAnimation()) {
        return false;
    }
    if (bottom.isPlayingAnimation()) {
        return false;
    }
    top.startAnimation("loop", false);
    bottom.startAnimation("loop", false);
    m_ctrl = -1;
    return true;
}

bool GfMenuObjElementEff::seqClose() {
    ui::UIObjectAcc top(m_handle, "IMG_top");
    ui::UIObjectAcc bottom(m_handle, "IMG_bottom");
    if (m_ctrl == -1) {
        top.setDisp(true);
        top.startAnimation("end", false);
        bottom.setDisp(true);
        bottom.startAnimation("end", false);
        ui::UIObjectAcc lay(m_handle, "LAY_combo_name");
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 0x10000000;
        param.m_motionLib = "cmn_fade_motion_lr";
        param.m_motion = "fade_out_l";
        param.m_startFlags = 10;
        m_ctrl = GfMenuObjUtil::startCtrl(lay.m_handle, param, nullptr);
        return false;
    }
    if (top.isPlayingAnimation()) {
        return false;
    }
    if (bottom.isPlayingAnimation()) {
        return false;
    }
    if (GfMenuObjUtil::isBusyCtrl(m_ctrl)) {
        return false;
    }
    m_ctrl = -1;
    top.setDisp(false);
    bottom.setDisp(false);
    {
        ui::UIObjectAcc main(m_handle, "LAY_main");
        GfMenuObject::termCallContext(main.m_handle);
    }
    return true;
}

void GfMenuObjElementEff::start(GfMenuCallContext* context, const StartParam& param) {
    if (GfMenuObjUtil::checkCCStart(context)) {
        unsigned int handle = GfMenuObject::getAttachedObject(0x17);
        if (ui::UIObjectAcc(handle).m_object != nullptr) {
            if (!ui::UIObjectAcc(handle).isTerm()) {
                ui::EventData event;
                event.m_type = 0x21;
                event.m_param0 = param.m_combo;
                GfMenuObject::sendEvent(handle, event, 0.0f);
                GfMenuObject::startCallContext(context, 0x17, handle);
            }
        }
    }
}

void GfMenuObjElementEff::cancel(GfMenuCallContext* context) {
    if (GfMenuObjUtil::checkCCNext(context, 0x17)) {
        unsigned int handle = GfMenuObject::getAttachedObject(0x17);
        if (ui::UIObjectAcc(handle).m_object != nullptr) {
            if (!ui::UIObjectAcc(handle).isTerm()) {
                ui::EventData event;
                event.m_type = 0x22;
                GfMenuObject::sendEvent(handle, event, 0.0f);
            }
        }
    }
}

}  // namespace gf
