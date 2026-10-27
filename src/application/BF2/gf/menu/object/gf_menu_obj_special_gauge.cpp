#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuBattleAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuObjSpecialGauge.h"
#include "classes/gf/GfMenuObjSpecialGauge/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjSpecialGauge::GfMenuObjSpecialGauge(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjSpecialGauge::~GfMenuObjSpecialGauge() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjSpecialGauge::push() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x29));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x10A;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjSpecialGauge::initialize() {
    ui::UIObjectAcc acc(m_handle);
    if (acc.m_object != nullptr) {
        ui::UIObjectAcc main(acc.m_handle, "LAY_main");
        if (main.m_object != nullptr) {
#line 83
            MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
            // the original stores the count after the listener's own fields, not with its base
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(main.m_handle, listener);
            if (listener != nullptr) {
                listener->release();
            }
            GfMenuObject::attachExternalCall(0x29, main.m_handle);
        }
        mm::mtl::FixStr<32> name;
        for (int i = 0; i < 5; i++) {
            name.format("IMG_gauge_lv@%d", i);
            ui::UIObjectAcc image(main.m_handle, name.m_str);
            if (image.m_object != nullptr) {
                GfMenuAdapter* adapter;
                if (GfMenuObjUtil::fn_710048FD30(3)) {
                    GfMenuBattleAdapter* battle = GfMenuBattleAdapter::create(image.m_handle, 0x1F);
                    battle->m_index = i;
                    adapter = battle;
                } else {
                    GfMenuGfObjAdapter* blade = GfMenuGfObjAdapter::createFromPartyBlade(image.m_handle, 0x25, 0, -1, true, false);
                    blade->m_index = i;
                    adapter = blade;
                }
                adapter->setNumberInterpolateMode(0.25f);
                image.startAnimation("start", true);
                GfMenuObject::addNumberEventCondition(main.m_handle, name.m_str, 0, i, 1.0f);
            }
        }
        bool layer = GfMenuObjUtil::fn_710048FD30(3);
        unsigned int arts = acc.searchChild("IMG_arts_lv");
        if (layer) {
            GfMenuBattleAdapter::create(arts, 0x20);
        } else {
            GfMenuGfObjAdapter::createFromPartyBlade(arts, 0x26, 0, -1, true, false);
        }
        GfMenuObject::addNumberEventCondition(main.m_handle, "IMG_arts_lv", 1, 0, 0.0f);
        GfMenuObject::initialize();
    }
}

void GfMenuObjSpecialGauge::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjSpecialGauge::update() {
    ui::UIObjectAcc(m_handle).setAlpha(1.0f);
    GfMenuObject::update();
}

void GfMenuObjSpecialGauge::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state.m_ctrl = -1;
        m_state.m_open = 0;
        m_state.m_shown = 0;
        m_state.m_enabled = 1;
        break;
    case 0xD: {
        int value = event.m_param0;
        if (event.m_param1 == 0) {
            int level = event.m_param2;
            mm::mtl::FixStr<32> name;
            name.format("LAY_gauge_lv@%d", level);
            if (value == 1) {
                GfMenuObjUtil::playSE(0x27);
                acc.setDispChild(false, name.m_str);
            } else {
                acc.setDispChild(true, name.m_str);
            }
        } else if (event.m_param1 == 1) {
            if (value == 1) {
                acc.setDispChild(false, "LAY_arts_lv");
            } else {
                acc.setDispChild(true, "LAY_arts_lv");
            }
        }
        break;
    }
    case 0x100:
        if (GfMenuManager::isBattleState(0)) {
            m_state.m_open = 1;
            if (m_state.m_shown == 0 && m_state.m_enabled == 1) {
                int slot = m_state.m_ctrl;
                GfMenuObjUtil::PresetCtrlParam param;
                param.m_preset = 0;
                param.m_out = 0;
                param.m_startFlag4 = true;
                param.m_slot = slot;
                int ctrl = GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
                if (ctrl != -1) {
                    m_state.m_ctrl = ctrl;
                }
                m_state.m_shown = 1;
            }
        }
        break;
    case 0x101:
        m_state.m_open = 0;
        if (m_state.m_shown != 0) {
            int slot = m_state.m_ctrl;
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_out = 1;
            param.m_startFlag4 = true;
            param.m_slot = slot;
            GfMenuObjUtil::startPresetCtrl(acc.m_handle, param);
            m_state.m_shown = 0;
        }
        break;
    case 0x10A:
        if (m_state.m_shown == 1) {
            GfMenuObjUtil::playSE(0x28);
        }
        break;
    case 0x10B: {
        int reverse = event.m_param0;
        ui::UIObjectAcc parent(acc.getParentHandle());
        parent.setDisp(reverse != 1);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjSpecialGauge::open() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x29));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x100;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjSpecialGauge::close() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x29));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x101;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjSpecialGauge::reverse(bool reverse) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x29));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x10B;
        event.m_param0 = reverse;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

}  // namespace gf
