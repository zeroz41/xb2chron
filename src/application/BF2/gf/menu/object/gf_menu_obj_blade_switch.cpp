#include "gf/GfDataDriver.h"
#include "classes/gf/GfMenuObjBladeSwitch.h"
#include "classes/gf/GfMenuObjBladeSwitch/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/GfGameScene.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfObjAcc.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjBladeSwitch::GfMenuObjBladeSwitch(unsigned int handle)
    : GfMenuObject(handle), m_shown(false), m_opened(false), m_active(false), m_seq(this) {}

GfMenuObjBladeSwitch::~GfMenuObjBladeSwitch() {}

void GfMenuObjBladeSwitch::setActive(bool active) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x22));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x100;
        event.m_param0 = active;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjBladeSwitch::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
#line 107
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x22, acc.m_handle);
    GfMenuObject::initialize();
}

void GfMenuObjBladeSwitch::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjBladeSwitch::update() {
    if (!m_active) {
        return;
    }
    if (GfGameManager::isEvent(false)) {
        return;
    }
    bool enable = GfGameScene::get()->isEnableFieldBladeChange();
    GF_OBJ_HANDLE* leader = GfGameParty::getLeader();
    if (leader == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfObjAcc acc(leader);
    bool show;
    if (acc.getType() == 3) {
        // a driver with one blade engaged has none to change to
        int count = 0;
        for (int i = 0; i < 3; i++) {
            count += GfMenuObjUtil::isValidBlade(GfDataDriver::getBlade(acc.getBdatId(), i));
        }
        show = enable && count != 1;
    } else {
        show = false;
    }
    if (show != m_shown) {
        if (show) {
            open();
        } else {
            close();
        }
        m_shown = show;
    }
    GfMenuObject::update();
}

void GfMenuObjBladeSwitch::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        break;
    case 8:
        if (event.m_param1 == 9 && GfGameScene::get()->isEnableFieldBladeChange()) {
            GfGameScene::get()->requestFieldBladeChange();
        }
        break;
    case 0xC:
        if (!m_owner->m_opened) {
            acc.setDisp(false);
        }
        break;
    case 0x21:
        if (!m_owner->m_opened) {
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_base");
                base.startAnimation("fade_in", false);
                GfMenuObject::hookAnimationEvent(0, base.m_handle, 0);
            }
            {
                ui::UIObjectAcc input(acc.m_handle, "LAY_input");
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_in_l";
                param.m_setDefault = true;
                GfMenuObjUtil::startCtrl(input.m_handle, param, nullptr);
            }
            m_owner->m_opened = true;
            GfMenuObject::enableInput(acc.m_handle);
            acc.setDisp(true);
        }
        break;
    case 0x22:
        if (m_owner->m_opened) {
            {
                ui::UIObjectAcc base(acc.m_handle, "IMG_base");
                base.startAnimation("fade_out", false);
                GfMenuObject::hookAnimationEvent(acc.m_handle, base.m_handle, 0);
            }
            {
                ui::UIObjectAcc input(acc.m_handle, "LAY_input");
                GfMenuObjUtil::CtrlParam param;
                param.m_methods = 0x10000000;
                param.m_motionLib = "cmn_fade_motion_lr";
                param.m_motion = "fade_out_l";
                param.m_setDefault = true;
                param.m_startFlags = 10;
                GfMenuObjUtil::startCtrl(input.m_handle, param, nullptr);
            }
            m_owner->m_opened = false;
            GfMenuObject::disableInput(acc.m_handle);
        }
        break;
    case 0x100:
        m_owner->m_active = event.m_param0 == 1;
        if (!m_owner->m_active) {
            if (m_owner->m_opened) {
                close();
            }
            m_owner->m_shown = false;
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

}  // namespace gf
