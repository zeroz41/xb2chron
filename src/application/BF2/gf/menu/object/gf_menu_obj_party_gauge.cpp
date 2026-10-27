#include "classes/gf/GfMenuObjPartyGauge.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObjPartyGauge/GaugeListener.h"
#include "classes/gf/GfMenuObjPartyGauge.h"
#include "classes/gf/GfMenuObjPartyGauge/GaugeListener.h"
#include "classes/gf/GfMenuBattleAdapter.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

bool GfMenuObjPartyGauge::s_locked;

GfMenuObjPartyGauge::GfMenuObjPartyGauge(unsigned int handle) : GfMenuObject(handle) {
    m_barCtrl = -1;
}

GfMenuObjPartyGauge::~GfMenuObjPartyGauge() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjPartyGauge::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x55, acc.m_handle);
        {
            ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
#line 79
            GaugeListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GaugeListener(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(gauge.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
            for (int i = 0; i < 3; i++) {
                mm::mtl::FixStr<32> name;
                name.format("IMG_gauge@%02d", i + 1);
                ui::UIObjectAcc image(gauge.m_handle, name.m_str);
                if (image.m_object != nullptr) {
                    GfMenuBattleAdapter* adapter = GfMenuBattleAdapter::create(gauge.searchChild(name.m_str), 0xC);
                    if (adapter != nullptr) {
                        image.setExtType(1);
                        adapter->m_index = i;
                    }
                    GfMenuObject::addNumberEventCondition(gauge.m_handle, name.m_str, 0, i, 1.0f);
                }
            }
            if (GfMenuObjUtil::fn_710048FD30(3)) {
                GfMenuBattleAdapter::create(gauge.searchChild("IMG_siren_pt_lv"), 0x23);
            }
        }
        if (GfMenuObjUtil::fn_710048FD30(3)) {
            ui::UIObjectAcc siren(acc.m_handle, "LAY_siren");
#line 114
            TUnk_B63FC8* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B63FC8(this);
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(siren.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
            ui::UIObjectAcc image(acc.m_handle, "IMG_siren_en_gauge");
            if (GfMenuBattleAdapter::create(image.m_handle, 0x22) != nullptr) {
                image.setExtType(2);
                GfMenuObject::addNumberEventCondition(siren.m_handle, "IMG_siren_en_gauge", 0, 0, 1.0f);
            }
            GfMenuBattleAdapter::create(siren.searchChild("IMG_siren_en_lv"), 0x24);
            GfMenuBattleAdapter::create(siren.searchChild("IMG_siren_en_pt"), 0x23);
        }
        GfMenuObject::initialize();
    }
}

void GfMenuObjPartyGauge::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjPartyGauge::update() {
    ui::UIObjectAcc(m_handle).setAlpha(1.0f);
    GfMenuObject::update();
}

void GfMenuObjPartyGauge::open() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
    if (acc.m_object != nullptr && !acc.isTerm() && !s_locked) {
        if (!GfMenuManager::isBattleState(3)) {
            acc.setDisp(true);
        }
        ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(gauge.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyGauge::close() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
    if (acc.m_object != nullptr && !acc.isTerm() && !s_locked) {
        ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(gauge.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyGauge::fn_71004569F8() {
    s_locked = false;
}

void GfMenuObjPartyGauge::fn_7100456A08() {
    s_locked = true;
}

void GfMenuObjPartyGauge::disp(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
    if (acc.m_object != nullptr && !acc.isTerm() && !s_locked) {
        acc.setDisp(disp);
        ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(gauge.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyGauge::fn_7100456AC8() {
    if (GfMenuObjUtil::fn_710048FD30(1) || GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
            ui::EventData event;
            event.m_type = 0x100;
            GfMenuObject::sendEvent(gauge.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjPartyGauge::fn_7100456B60(bool flag) {
    if (GfMenuObjUtil::fn_710048FD30(1) || GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
            ui::EventData event;
            event.m_type = 0x101;
            event.m_param0 = flag;
            GfMenuObject::sendEvent(gauge.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjPartyGauge::fn_7100456C0C(int value) {
    if (GfMenuObjUtil::fn_710048FD30(1) || GfMenuObjUtil::fn_710048FD30(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
            ui::EventData event;
            event.m_type = 0x102;
            event.m_param0 = value;
            GfMenuObject::sendEvent(gauge.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjPartyGauge::fn_7100456CB4(bool flag) {
    if (GfMenuObjUtil::fn_710048FD30(3) && GfMenuReference::fn_7100368418(4)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
            ui::EventData event;
            event.m_type = 0x103;
            event.m_param0 = flag;
            GfMenuObject::sendEvent(gauge.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjPartyGauge::fn_7100456D60() {
    if (GfMenuObjUtil::fn_710048FD30(3) && GfMenuReference::fn_7100368418(4)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::UIObjectAcc siren(acc.m_handle, "LAY_siren");
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = 1;
            GfMenuObject::sendEvent(siren.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjPartyGauge::fn_7100456E00() {
    if (GfMenuObjUtil::fn_710048FD30(3) && GfMenuReference::fn_7100368418(4)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::UIObjectAcc siren(acc.m_handle, "LAY_siren");
            ui::EventData event;
            event.m_type = 0x22;
            event.m_param0 = 1;
            GfMenuObject::sendEvent(siren.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjPartyGauge::fn_7100456EA0(bool flag) {
    if (GfMenuObjUtil::fn_710048FD30(3) && GfMenuReference::fn_7100368418(4)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::UIObjectAcc siren(acc.m_handle, "LAY_siren");
            ui::EventData event;
            event.m_type = 0x101;
            event.m_param0 = flag;
            GfMenuObject::sendEvent(siren.m_handle, event, 0.0f);
        }
    }
}

}  // namespace gf
