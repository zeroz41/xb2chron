#include "classes/gf/GfMenuObjBladeChange.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

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
            fn_71003C3648(disp);
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
