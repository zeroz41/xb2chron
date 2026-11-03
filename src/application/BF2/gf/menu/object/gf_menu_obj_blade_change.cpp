#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/gf/GfMenuObjBladeChange/BladeListener.h"
#include "classes/gf/TUnk_B5FEE8.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfWeapon.h"
#include "classes/ui/UIEventManager.h"
#include "classes/gf/TUnk_B60E28.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"
#include "mm/mtl/Vector.h"
#include "classes/gf/GfMenuBladeList.h"

// instantiated for gf::GfMenuObjBladeRelease::seqExecRelease, gf::GfMenuObjMercenaryForm::ListListener::reciveEvent, gf::GfMenuObjMercenaryForm::StartListener::reciveEvent, gf::GfMenuObjMercenaryForm::UnitListener::reciveEvent, gf::GfMenuObjMercenaryForm::updateBladeCount, gf::GfMenuObjMercenaryReport::seqCheckAchive (not written yet)
template mm::mtl::Vector<gf::MenuBladeInfo>::iterator mm::mtl::Vector<gf::MenuBladeInfo>::erase(gf::MenuBladeInfo*);

namespace gf {

bool GfMenuObjBladeChange::s_soloOpen;

GfMenuObjBladeChange::GfMenuObjBladeChange(unsigned int handle)
    : GfMenuObject(handle), m_ctrlSlot(-1), pad_28(-1), m_awakeMoved(false), pad_2D(false), pad_2E(false), m_seqActive(false), m_slots(),
      pad_48(-1), pad_4C(-1), m_seq(this) {
    for (int i = 0; i < 2; i++) {
        pad_50[i] = -1;
    }
}

GfMenuObjBladeChange::~GfMenuObjBladeChange() {}

void GfMenuObjBladeChange::initialize() {
    ui::UIObjectAcc acc(m_handle);
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc main(acc.m_handle, "LAY_main");
        GfMenuObject::attachExternalCall(0x3C, main.m_handle);
#line 100
        BladeListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) BladeListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        for (int i = 0; i < 3; i++) {
            mm::mtl::FixStr<32> name;
            name.format("IMG_face@%02d", i + 1);
            ui::UIObjectAcc face(acc.m_handle, name.m_str);
            if (GfMenuCharDataAdapter* adapter =
                    GfMenuCharDataAdapter::createFromPartyBlade(face.m_handle, 3, 0, i, true, false, true)) {
                adapter->setDispAlphaMode(true);
            }
            {
                name.format("TXT_info_name@%02d", i + 1);
                ui::UIObjectAcc info(acc.m_handle, name.m_str);
                if (GfMenuCharDataAdapter* adapter =
                        GfMenuCharDataAdapter::createFromPartyBlade(info.m_handle, 2, 0, i, true, false, true)) {
                    adapter->setDispAlphaMode(true);
                    name.format("LAY_info@%02d", i + 1);
                    GfMenuObjUtil::createSyncPlugin(acc.searchChild(name.m_str), info.m_handle, 0x10);
                    name.format("LAY_info_contents@%02d", i + 1);
                    ui::UIObjectAcc contents(acc.searchChild(name.m_str));
                    GfMenuObjUtil::FitOption option;
                    option.m_keepScaleY = true;
                    option.m_offsetWidth = 12;
                    name.format("IMG_info_bg@%02d", i + 1);
                    GfMenuObjUtil::createFitPlugin(acc.searchChild(name.m_str), contents.m_handle, 15, 0, option);
                }
                name.format("IMG_info_wpn@%02d", i + 1);
                GfMenuCharDataAdapter::createFromPartyBlade(acc.searchChild(name.m_str), 0x29, 0, i, true, false, true);
                GfMenuObjUtil::createDockPlugin(acc.searchChild(name.m_str), info.m_handle, 1, mm::Pnt<short>(4, 0), 0);
            }
            name.format("IMG_info_elem@%02d", i + 1);
            GfMenuCharDataAdapter::createFromPartyBlade(acc.searchChild(name.m_str), 0x2A, 0, i, true, false, true);
            name.format("IMG_face_mark@%02d", i + 1);
            GfMenuCharDataAdapter::createFromPartyBlade(acc.searchChild(name.m_str), 3, 0, i, true, false, true);
            name.format("LAY_face_mark@%02d", i + 1);
            GfMenuGfObjAdapter::createFromPartyBlade(acc.searchChild(name.m_str), 0x2A, 0, i, true, true);
            GfMenuObject::addDispEventCondition(main.m_handle, name.m_str, 2, i, false);
            name.format("IMG_face_bg@%02d", i + 1);
            GfMenuGfObjAdapter::createFromPartyBlade(acc.searchChild(name.m_str), 0x29, 0, i, true, true);
            GfMenuObject::addDispEventCondition(main.m_handle, name.m_str, 1, i, false);
            name.format("IMG_gauge@%02d", i + 1);
            if (GfMenuGfObjAdapter* adapter =
                    GfMenuGfObjAdapter::createFromPartyBlade(acc.searchChild(name.m_str), 0x27, 0, i, true, true)) {
                adapter->setNumberInterpolateMode(0.25f);
                ui::UIObjectAcc(acc.m_handle, name.m_str).startAnimation("start", true);
            }
            GfMenuObject::addNumberEventCondition(main.m_handle, name.m_str, 0, i, 1.0f);
            name.format("IMG_gauge_homuri@%02d", i + 1);
            if (GfMenuGfObjAdapter* adapter =
                    GfMenuGfObjAdapter::createFromPartyBlade(acc.searchChild(name.m_str), 0x28, 0, i, true, true)) {
                ui::UIObjectAcc gauge(acc.m_handle, name.m_str);
                gauge.setExtType(4);
                adapter->setNumberReverseMode(true);
            }
            name.format("LAY_blade@%02d", i + 1);
            ui::UIObjectAcc blade(acc.m_handle, name.m_str);
            name.format("LAY_blade_gauge@%02d", i + 1);
            GfMenuObjUtil::createSyncPlugin(acc.searchChild(name.m_str), blade.m_handle, 2);
        }
        {
            ui::UIObjectAcc solo(acc.m_handle, "LAY_dr_solo");
#line 224
            TUnk_B5FEE8* soloListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B5FEE8(this);
            soloListener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(solo.m_handle, soloListener);
            if (soloListener != nullptr) {
                soloListener->release();
            }
        }
        m_seqActive = GfMenuObjUtil::fn_710048FD30(1);
        GfMenuObject::initialize();
    }
}

void GfMenuObjBladeChange::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBladeChange::update() {
    ui::UIObjectAcc(m_handle).setAlpha(1.0f);
    if (m_seqActive) {
        m_seq.update();
    }
    GfMenuObject::update();
}

void GfMenuObjBladeChange::fn_7100391CDC() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x105;
        if (s_soloOpen) {
            ui::UIObjectAcc solo(acc.searchSibiling("LAY_dr_solo"));
            if (solo.m_object != nullptr) {
                GfMenuObject::sendEvent(solo.m_handle, event, 0.0f);
            }
        } else {
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void TUnk_B5FEE8::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    default:
        ui::UIObjectListener::reciveEvent(event, handle);
        break;
    case 1:
        acc.setDisp(false);
        m_ctrlSlot = -1;
        break;
    case 0x21: {
        ui::UIObjectAcc solo(acc.m_handle, "LAY_btl_mode_solo");
        acc.setDisp(m_owner->m_seqActive ? fn_71002EE9EC() : false);
        if (m_owner->m_seqActive) {
            acc.setDispChild(false, "TXT_btl_mode@01");
            acc.setDispChild(false, "TXT_btl_mode@02");
            GfMenuObjBladeChange::fn_7100391CDC();
        }
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 1;
        param.m_out = 0;
        param.m_startFlag4 = true;
        param.m_slot = m_ctrlSlot;
        m_ctrlSlot = GfMenuObjUtil::startPresetCtrl(solo.m_handle, param);
        break;
    }
    case 0x22: {
        ui::UIObjectAcc solo(acc.m_handle, "LAY_btl_mode_solo");
        GfMenuObjUtil::PresetCtrlParam param;
        param.m_preset = 1;
        param.m_out = 1;
        param.m_startFlag4 = true;
        param.m_slot = m_ctrlSlot;
        m_ctrlSlot = GfMenuObjUtil::startPresetCtrl(solo.m_handle, param);
        break;
    }
    case 0x105: {
        unsigned int mode = GfMenuReference::fn_71003674A0();
        unsigned int on;
        unsigned int off;
        if (mode == 0) {
            on = acc.searchChild("TXT_btl_mode_solo@01");
            off = acc.searchChild("TXT_btl_mode_solo@02");
        } else {
            on = acc.searchChild("TXT_btl_mode_solo@02");
            off = acc.searchChild("TXT_btl_mode_solo@01");
        }
        {
            ui::UIObjectAcc(on).setDisp(true);
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x10000000;
            param.m_motionLib = "cmn_fade_motion_lr";
            param.m_motion = "fade_in_l";
            param.m_setDefault = true;
            param.m_startFlags = 8;
            GfMenuObjUtil::startCtrl(on, param, nullptr);
            if (ui::UIObjectAcc(on).isDisp()) {
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_out_r";
                param.m_methods = 0x10000000;
                param.m_setDefault = true;
                param.m_startFlags = 10;
                ui::UIObjectAcc(off).setDisp(true);
                GfMenuObjUtil::startCtrl(off, param, nullptr);
            }
        }
        ui::UIObjectAcc base(acc.m_handle, "IMG_btl_mode_base_solo");
        m_owner->m_seq.clear();
        switch (mode) {
        case 0:
            m_owner->m_seq.addAnimJob(base.m_handle, "push_manual");
            m_owner->m_seq.addAnimJob(base.m_handle, "manual");
            break;
        case 1:
            m_owner->m_seq.addAnimJob(base.m_handle, "push_auto");
            m_owner->m_seq.addAnimJob(base.m_handle, "auto_loop");
            break;
        }
        break;
    }
    }
}

void GfMenuObjBladeChange::open() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjBladeChange::close() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjBladeChange::fn_710039232C() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::UIObjectAcc solo(acc.searchSibiling("LAY_dr_solo"));
        if (solo.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x21;
            GfMenuObject::sendEvent(solo.m_handle, event, 0.0f);
            s_soloOpen = true;
        }
    }
}

void GfMenuObjBladeChange::fn_71003923CC() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::UIObjectAcc solo(acc.searchSibiling("LAY_dr_solo"));
        if (solo.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(solo.m_handle, event, 0.0f);
            s_soloOpen = false;
        }
    }
}

void GfMenuObjBladeChange::dispInfo(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        if (GfMenuObjUtil::fn_710048FD30(3)) {
            TUnk_B60E28::fn_71003C3648(disp);
        } else {
            acc.setDispChild(disp, "LAY_info");
        }
    }
}

void GfMenuObjBladeChange::enableAwakening(bool enable) {}

void GfMenuObjBladeChange::pushGroupUp() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x102;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjBladeChange::pushBladeChange(unsigned int index) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x103;
        event.m_param0 = index;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjBladeChange::startChainAttack(GfMenuCallContext* context) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x104;
        event.m_param0 = 1;
        GfMenuObject::sendEvent(acc.m_handle, event, GfMenuObjUtil::getParamMenu()->m_chainAttackWait);
        if (context != nullptr && GfMenuObjUtil::checkCCStart(context)) {
            GfMenuObject::startCallContext(context, 0x3C, acc.m_handle);
        }
    }
}

void GfMenuObjBladeChange::exitChainAttack() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x3C));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x104;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

}  // namespace gf
