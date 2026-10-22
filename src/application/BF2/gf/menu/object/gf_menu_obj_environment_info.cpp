#include "classes/gf/GfMenuObjEnvironmentInfo.h"
#include "classes/gf/GfMenuObjEnvironmentInfo/ListListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuGameAdapter.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuFlag.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjEnvironmentInfo::GfMenuObjEnvironmentInfo(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjEnvironmentInfo::~GfMenuObjEnvironmentInfo() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjEnvironmentInfo::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int child = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(child).m_object != nullptr) {
#line 86
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(child, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0x2A, child);
        setupScreen(child);
    }
    GfMenuObject::initialize();
}

void GfMenuObjEnvironmentInfo::setupScreen(unsigned int handle) {
    {
        ui::UIObjectAcc icon(handle, "IMG_weather_icon");
        if (icon.m_object != nullptr) {
            icon.setDisp(GfMenuGameAdapter::create(icon.m_handle, 3, true) != nullptr);
        }
    }
    {
        ui::UIObjectAcc cloud(handle, "IMG_cloud");
        if (cloud.m_object != nullptr) {
            cloud.setDisp(GfMenuGameAdapter::create(cloud.m_handle, 4, true) != nullptr);
        }
    }
    {
        ui::UIObjectAcc time(handle, "TXT_time");
        if (time.m_object != nullptr) {
            time.setDisp(GfMenuGameAdapter::create(time.m_handle, 2, true) != nullptr);
        }
    }
    {
        ui::UIObjectAcc location(handle, "TXT_location");
        if (location.m_object != nullptr) {
            location.setDisp(GfMenuGameAdapter::create(location.m_handle, 6, true) != nullptr);
        }
    }
    {
        ui::UIObjectAcc timezone(handle, "IMG_timezone");
        if (timezone.m_object != nullptr) {
            timezone.setDisp(GfMenuGameAdapter::create(timezone.m_handle, 8, true) != nullptr);
        }
    }
}

void GfMenuObjEnvironmentInfo::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjEnvironmentInfo::update() {
    GfMenuObject::update();
}

void GfMenuObjEnvironmentInfo::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        m_state.m_open = 0;
        m_state.m_enabled = 1;
        m_state.m_ctrl = -1;
        break;
    case 2:
        acc.setTerm();
        break;
    case 0x21: {
        unsigned int disabled = GfMenuFlag::get1(30);
        m_state.m_enabled = disabled == 0;
        if (disabled == 0 && m_state.m_open == 0) {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_startFlag4 = true;
            param.m_slot = m_state.m_ctrl;
            int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
            m_state.m_open = 1;
            m_state.m_ctrl = ctrl;
        }
        break;
    }
    case 0x22:
        if (m_state.m_open == 1) {
            GfMenuObjUtil::PresetCtrlParam param;
            param.m_out = 1;
            param.m_startFlag4 = true;
            param.m_slot = m_state.m_ctrl;
            int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
            m_state.m_open = 0;
            m_state.m_ctrl = ctrl;
        }
        break;
    case 0x100:
        if (m_state.m_enabled == 0) {
            m_state.m_enabled = 1;
        }
        break;
    case 0x101:
        if (m_state.m_enabled == 1) {
            m_state.m_enabled = 0;
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjEnvironmentInfo::open() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x2A);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x21;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjEnvironmentInfo::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x2A);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjEnvironmentInfo::enable() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x2A);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x100;
            GfMenuObject::sendEvent(handle, event, 0.0f);
            GfMenuFlag::set1(30, 0);
        }
    }
}

void GfMenuObjEnvironmentInfo::disable() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x2A);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x101;
            GfMenuObject::sendEvent(handle, event, 0.0f);
            GfMenuFlag::set1(30, 1);
        }
    }
}

}  // namespace gf
