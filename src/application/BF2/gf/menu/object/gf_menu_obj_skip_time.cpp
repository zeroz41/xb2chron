#include "ui/EventData.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfFieldTime.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjMainMenu2.h"
#include "classes/gf/GfMenuObjSkipTime.h"
#include "classes/gf/GfMenuObjSkipTime/MainListener.h"
#include "classes/gf/GfMenuObjSkipTime/TimeChangeListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UIObjectTimePlugin.h"
#include "mm/mtl/FixStr.h"

namespace gf {

// how far the watch's hand turns for an hour: -15 degrees
static const float HOUR_ROT = -0.2617994f;

GfMenuObjSkipTime::GfMenuObjSkipTime(unsigned int handle)
    : GfMenuObject(handle), m_timePlugin(nullptr), m_time(), m_newTime() {}

GfMenuObjSkipTime::~GfMenuObjSkipTime() {
    if (m_timePlugin != nullptr) {
        m_timePlugin->release();
        m_timePlugin = nullptr;
    }
}

void GfMenuObjSkipTime::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 98
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x6D, main);
    unsigned int time = acc.searchChild("LAY_skiptime_main");
#line 104
    TimeChangeListener* timeListener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TimeChangeListener(this);
    timeListener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(time, timeListener);
    if (timeListener != nullptr) {
        timeListener->release();
    }
    GfMenuObject::initialize();
}

void GfMenuObjSkipTime::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjSkipTime::update() {
    GfMenuObject::update();
}

void GfMenuObjSkipTime::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        GfMenuObjOperationInfo::add(acc.searchChild("LAY_skiptime_main"), 0, 0, 0);
        GfMenuObjOperationInfo::setGuideText(0x38, 0);
        GfMenuObjMainMenu2::setSubIndexText(0x17);
        setFadeIn(handle);
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 3:
        if (event.m_param0 == 2) {
            GfMenuObjOperationInfo::remove(acc.searchChild("LAY_skiptime_main"), 0, 0, 0);
            acc.setDisp(false);
            acc.setTerm();
            GfMenuObject::returnFSSubLayer(m_owner);
        }
        break;
    case 0x21:
        acc.setDisp(true);
        break;
    case 0x22:
        setFadeOut(handle);
        break;
    }
}

void GfMenuObjSkipTime::TimeChangeListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc owner(m_owner->m_handle);
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        if (GfFieldTime::get() != nullptr) {
            m_owner->m_time = GfFieldTime::get()->getGameTime();
        }
        m_owner->m_newTime = m_owner->m_time;
        m_owner->m_newTime.min = 0;
        m_owner->m_newTime.sec = 0;
        m_owner->m_timePlugin = setupTimeChange(acc, m_owner->m_time, m_owner->m_newTime);
        GfMenuObject::setupInputSelection(handle, m_owner->m_newTime.hour, 24);
        GfMenuObject::enableInput(handle);
        break;
    }
    case 6: {
        int index = event.m_param0;
        int last = event.m_param1;
        m_owner->m_newTime.hour = index;
        ui::UIObjectAcc needle(acc.searchChild("IMG_watchneedle@02"));
        needle.setRot(static_cast<unsigned int>(m_owner->m_newTime.hour) * HOUR_ROT);
        setTime(m_owner->m_timePlugin, m_owner->m_newTime);
        if (last != -1) {
            GfMenuObjUtil::playSE(0x16);
        }
        if (GfFieldTime::get() != nullptr) {
            int range = GfFieldTime::get()->getTimeRange(m_owner->m_newTime.hour, m_owner->m_newTime.min);
            ui::UIObjectAcc icon(acc.searchChild("IMG_tmzoneicon"));
            icon.setImageIndex(range);
        }
        break;
    }
    case 8: {
        if (event.m_param1 == 1) {
            if (GfFieldTime::get() != nullptr) {
                GfFieldTime::get()->setGameTime(m_owner->m_newTime);
            }
            sendEvent(owner.searchChild("LAY_main"), 0x22, 0);
            GfMenuObject::disableInput(handle);
            GfMenuObjMainMenu2::setCloseKeyEnable(false);
            GfMenuObjUtil::playSECommonDecide();
        } else if (event.m_param1 == 2) {
            sendEvent(owner.searchChild("LAY_main"), 0x22, 0);
            GfMenuObject::disableInput(handle);
            GfMenuObjMainMenu2::setCloseKeyEnable(false);
            GfMenuObjUtil::playSECommonCancel();
        }
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

ui::UIObjectTimePlugin* GfMenuObjSkipTime::setupTimeChange(ui::UIObjectAcc& acc, GameTime& time, GameTime& newTime) {
    GfMenuObjUtil::setChildIcon(acc.m_handle, "IMG_buttonicon@01", 0x1D);
    GfMenuObjUtil::setChildIcon(acc.m_handle, "IMG_buttonicon@02", 0x1C);
    refreshSelect(acc, 0);
    ui::UIObjectAcc needle(acc.searchChild("IMG_watchneedle@01"));
    needle.setRot(static_cast<unsigned int>(time.hour) * HOUR_ROT);
    ui::UIObjectAcc text(acc.searchChild("TXT_bftimenum"));
    ui::UIObjectTimePlugin* plugin = ui::UIObjectTimePlugin::create(text.m_handle, 3);
    setTime(plugin, time);
    if (plugin != nullptr) {
        plugin->release();
    }
    ui::UIObjectAcc newNeedle(acc.searchChild("IMG_watchneedle@02"));
    newNeedle.setRot(static_cast<unsigned int>(newTime.hour) * HOUR_ROT);
    ui::UIObjectAcc newText(acc.searchChild("TXT_aftimenum"));
    ui::UIObjectTimePlugin* newPlugin = ui::UIObjectTimePlugin::create(newText.m_handle, 3);
    setTime(newPlugin, newTime);
    return newPlugin;
}

void GfMenuObjSkipTime::refreshSelect(ui::UIObjectAcc& acc, unsigned int select) {
    mm::mtl::FixStr<32> name;
    for (unsigned int i = 0; i < 2; i++) {
        name.format("IMG_tagbase@%02d", i + 1);
        ui::UIObjectAcc tag(acc.searchChild(name.m_str));
        const char* color = select == i ? "txt_bl_index" : "txt_dr_index";
        tag.setImageIndex(select == i);
        name.format("TXT_sellect@%02d", i + 1);
        ui::UIObjectAcc text(acc.searchChild(name.m_str));
        GfMenuObjUtil::setColMulandAdd(text.m_handle, color);
    }
}

}  // namespace gf
