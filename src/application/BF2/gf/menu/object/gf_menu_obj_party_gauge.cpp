#include "gf/GfMenuObjUtil.h"
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

bool GfMenuObjPartyGauge::s_OpenDisable;

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
            if (GfMenuObjUtil::isValidExpansion(3)) {
                GfMenuBattleAdapter::create(gauge.searchChild("IMG_siren_pt_lv"), 0x23);
            }
        }
        if (GfMenuObjUtil::isValidExpansion(3)) {
            ui::UIObjectAcc siren(acc.m_handle, "LAY_siren");
#line 114
            SirenListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SirenListener(this);
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
    if (acc.m_object != nullptr && !acc.isTerm() && !s_OpenDisable) {
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
    if (acc.m_object != nullptr && !acc.isTerm() && !s_OpenDisable) {
        ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(gauge.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyGauge::enableOpen() {
    s_OpenDisable = false;
}

void GfMenuObjPartyGauge::disableOpen() {
    s_OpenDisable = true;
}

void GfMenuObjPartyGauge::disp(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
    if (acc.m_object != nullptr && !acc.isTerm() && !s_OpenDisable) {
        acc.setDisp(disp);
        ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
        ui::EventData event;
        event.m_type = 0x21;
        GfMenuObject::sendEvent(gauge.m_handle, event, 0.0f);
    }
}

void GfMenuObjPartyGauge::damage() {
    if (GfMenuObjUtil::isValidExpansion(1) || GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x55));
        if (acc.m_object != nullptr && !acc.isTerm()) {
            ui::UIObjectAcc gauge(acc.m_handle, "LAY_gauge");
            ui::EventData event;
            event.m_type = 0x100;
            GfMenuObject::sendEvent(gauge.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjPartyGauge::setLock(bool flag) {
    if (GfMenuObjUtil::isValidExpansion(1) || GfMenuObjUtil::isValidExpansion(3)) {
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

void GfMenuObjPartyGauge::setLimit(unsigned int value) {
    if (GfMenuObjUtil::isValidExpansion(1) || GfMenuObjUtil::isValidExpansion(3)) {
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

void GfMenuObjPartyGauge::dispSirenPT(bool flag) {
    if (GfMenuObjUtil::isValidExpansion(3) && GfMenuReference::isIraFlag(4)) {
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

void GfMenuObjPartyGauge::openSirenEN() {
    if (GfMenuObjUtil::isValidExpansion(3) && GfMenuReference::isIraFlag(4)) {
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

void GfMenuObjPartyGauge::closeSirenEN() {
    if (GfMenuObjUtil::isValidExpansion(3) && GfMenuReference::isIraFlag(4)) {
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

void GfMenuObjPartyGauge::setLockSirenEN(bool flag) {
    if (GfMenuObjUtil::isValidExpansion(3) && GfMenuReference::isIraFlag(4)) {
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


// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100B63F88). The lock animations for 0-2
// remaining chains.
static const char* s_chainAnims[] = {"chain_3", "chain_2", "chain_1"};

// a table's entry (the name is not the original's). The original's s_chainAnims is writable data (.data): clang 3.9
// makes a static table constant unless its address is passed on before inlining, so its user handed the table to an
// inline helper like this one (gf_bdat_rsc's _gfbrs::getSlot).
template <unsigned long N>
inline const char* getAnim(const char* (&table)[N], unsigned int index) {
    return table[index];
}

void GfMenuObjPartyGauge::GaugeListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state.m_ctrl = -1;
        break;
    case 0xD: {
        if (event.m_param1 != 0) {
            return;
        }
        int index = event.m_param2;
        int value = event.m_param0;
        mm::mtl::FixStr<32> name;
        name.format("IMG_gauge@%02d", index + 1);
        ui::UIObjectAcc image(acc.m_handle, name.m_str);
        name.format("IMG_gauge_icon@%02d", index + 1);
        ui::UIObjectAcc icon(acc.m_handle, name.m_str);
        if (value == 1) {
            icon.setDisp(true);
            if (index == 2 && m_owner->m_barCtrl == -1) {
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x40000000;
                param.m_time = 1.0f;
                param.m_reserve = true;
                param.m_curve = 4;
                param.m_startFlags = 8;
                param.m_bright = 0.25f;
                m_owner->m_barCtrl = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_gauge_bar"), param, nullptr);
                if (!GfMenuObjPartyGauge::s_OpenDisable) {
                    GfMenuObjUtil::playSE(0x26);
                }
            } else if (!GfMenuObjPartyGauge::s_OpenDisable) {
                GfMenuObjUtil::playSE(0x25);
            }
        } else {
            icon.setDisp(false);
            if (m_owner->m_barCtrl != -1) {
                GfMenuObjUtil::stopCtrl(m_owner->m_barCtrl);
                m_owner->m_barCtrl = -1;
            }
        }
        if (GfMenuObjUtil::isValidExpansion(3) && GfMenuReference::isIraFlag(4) &&
            acc.searchSibiling("LAY_siren") != 0) {
            ui::UIObjectAcc sirenIcon(acc.m_handle, "IMG_siren_pt_icon");
            if (index == 2) {
                sirenIcon.startAnimation(value == 1 ? "standbye" : "loop", false);
            }
        }
        return;
    }
    case 0x21:
        if (m_state.m_open == 0) {
            GfMenuObjUtil::PresetCtrlParam param;
            if (event.m_param0 == 0) {
                param.m_preset = 1;
            }
            param.m_out = 0;
            param.m_startFlag4 = true;
            param.m_slot = m_state.m_ctrl;
            m_state.m_ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            m_state.m_open = 1;
        }
        if (GfMenuObjUtil::isValidExpansion(3) && acc.searchSibiling("LAY_siren") != 0) {
            acc.setDispChild(false, "LAY_siren_pt");
            if (GfMenuReference::isIraFlag(4) && !GfMenuReference::getIraSirenInfo(1)->m_stateB) {
                GfMenuObject::sendEvent(acc.searchSibiling("LAY_siren"), event, 0.0f);
                acc.setDispChild(true, "LAY_siren_pt");
            }
        }
        break;
    case 0x22:
        if (m_state.m_open == 1) {
            GfMenuObjUtil::PresetCtrlParam param;
            if (event.m_param0 == 0) {
                param.m_preset = 1;
            }
            param.m_out = 1;
            param.m_startFlag4 = true;
            param.m_slot = m_state.m_ctrl;
            m_state.m_ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            m_state.m_open = 0;
        }
        if (GfMenuObjUtil::isValidExpansion(3) && GfMenuReference::isIraFlag(4) &&
            acc.searchSibiling("LAY_siren") != 0) {
            GfMenuObject::sendEvent(acc.searchSibiling("LAY_siren"), event, 0.0f);
        }
        break;
    case 0x100:
        if (GfMenuObjUtil::isValidExpansion(1) || GfMenuObjUtil::isValidExpansion(3)) {
            ui::UIObjectAcc limit(acc.m_handle, "IMG_gauge_limit");
            if (limit.m_object != nullptr) {
                limit.setAlpha(1.0f);
                limit.startAnimation("damage", false);
            }
        }
        return;
    case 0x101:
        if (GfMenuObjUtil::isValidExpansion(3)) {
            ui::UIObjectAcc lock(acc.m_handle, "IMG_gauge_lock");
            if (GfMenuReference::isIraFlag(4)) {
                bool disp = event.m_param0 == 1;
                lock.startAnimation("chain_3", false);
                lock.setDisp(disp);
            } else {
                lock.setDisp(false);
            }
        }
        return;
    case 0x102:
        if (GfMenuObjUtil::isValidExpansion(1) || GfMenuObjUtil::isValidExpansion(3)) {
            unsigned int count = event.m_param0;
            ui::UIObjectAcc lock(acc.m_handle, "IMG_gauge_lock");
            if (lock.m_object != nullptr) {
                if (count < 3) {
                    lock.setDisp(true);
                    lock.startAnimation(getAnim(s_chainAnims, count), false);
                } else {
                    lock.setDisp(false);
                }
            }
        }
        return;
    case 0x103:
        if (GfMenuObjUtil::isValidExpansion(3)) {
            int value = event.m_param0;
            acc.setDispChild(value == 1, "LAY_siren_pt");
            if (value != 1) {
                ui::UIObjectAcc icon(acc.m_handle, "IMG_siren_pt_icon");
                icon.startAnimation("loop", false);
            }
        }
        return;
    }
    UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjPartyGauge::SirenListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state.m_ctrl = -1;
        m_state.m_gaugeCtrl = -1;
        m_state.m_hold = 0;
        break;
    case 0xD: {
        if (event.m_param1 != 0) {
            return;
        }
        int value = event.m_param0;
        if (m_state.m_gaugeCtrl != -1) {
            GfMenuObjUtil::stopCtrl(m_state.m_gaugeCtrl);
            m_state.m_gaugeCtrl = -1;
        }
        if (value == 1) {
            ui::UIObjectAcc gauge(acc.m_handle, "IMG_siren_en_gauge");
            GfMenuObjUtil::CtrlParam param;
            param.m_methods = 0x04000000;
            param.m_color.r = 1.0f;
            param.m_color.g = 1.0f;
            param.m_color.b = 1.0f;
            param.m_time = 1.0f;
            param.m_reserve = true;
            param.m_curve = 3;
            param.m_startFlags = 8;
            m_state.m_gaugeCtrl = GfMenuObjUtil::startCtrl(gauge.m_handle, param, nullptr);
        }
        ui::UIObjectAcc icon(acc.m_handle, "IMG_siren_en_icon");
        icon.startAnimation(value == 1 ? "standbye" : "loop", false);
        return;
    }
    case 0x21:
        if (event.m_param0 == 1) {
            m_state.m_hold = 0;
        }
        if (m_state.m_open == 0 && m_state.m_hold == 0) {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_preset = 0;
            param.m_out = 0;
            param.m_startFlag4 = true;
            param.m_slot = m_state.m_ctrl;
            m_state.m_ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            m_state.m_open = 1;
            if (m_state.m_gaugeCtrl != -1) {
                GfMenuObjUtil::stopCtrl(m_state.m_gaugeCtrl);
                m_state.m_gaugeCtrl = -1;
            }
        }
        break;
    case 0x22: {
        int value = event.m_param0;
        if (m_state.m_open == 1) {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_out = 1;
            param.m_startFlag4 = true;
            param.m_slot = m_state.m_ctrl;
            m_state.m_ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            m_state.m_open = 0;
            if (m_state.m_gaugeCtrl != -1) {
                GfMenuObjUtil::stopCtrl(m_state.m_gaugeCtrl);
                m_state.m_gaugeCtrl = -1;
            }
        }
        if (value == 1) {
            m_state.m_hold = 1;
        }
        break;
    }
    case 0x101:
        if (GfMenuObjUtil::isValidExpansion(1) || GfMenuObjUtil::isValidExpansion(3)) {
            ui::UIObjectAcc lock(acc.m_handle, "IMG_siren_en_lock");
            bool disp = event.m_param0 == 1;
            lock.startAnimation("chain_3", false);
            lock.setDisp(disp);
        }
        return;
    }
    UIObjectListener::reciveEvent(event, handle);
}

}  // namespace gf
