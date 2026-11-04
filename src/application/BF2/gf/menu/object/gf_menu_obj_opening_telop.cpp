#include "classes/gf/GfMenuObjOpeningTelop.h"
#include "classes/gf/GfMenuObjOpeningTelop/MainListener.h"
#include "classes/gf/GfMenuManager.h"
#include "ui/EventData.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "classes/ui/UISelectObjList.h"
#include "mm/mtl/FixStr.h"

namespace gf {

namespace {
// per position (center, left, right, right half, left half): its layout, and the format of its images' names (the
// names are not the original's)
const char* s_layers[] = {"LAY_center", "LAY_left", "LAY_right", "LAY_right_half", "LAY_left_half"};
const char* s_images[] = {"IMG_center@%02d", "IMG_left@%02d", "IMG_right@%02d", "IMG_right_half@%02d",
                          "IMG_left_half@%02d"};
}  // namespace

GfMenuObjOpeningTelop::GfMenuObjOpeningTelop(unsigned int handle)
    : GfMenuObject(handle), m_imageCounts(), m_streaming(nullptr) {
    ui::UISelectObjList::CreateParam create;
    create.m_allocator = getAllocator(ALLOCATOR(0));
    m_streaming = ui::UISelectObjList::create(create);
}

GfMenuObjOpeningTelop::~GfMenuObjOpeningTelop() {
    if (m_streaming != nullptr) {
        m_streaming->release();
        m_streaming = nullptr;
    }
}

void GfMenuObjOpeningTelop::openCenter(unsigned int image) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x82));
    if (acc.m_object != nullptr && !GfMenuManager::isTheaterNonTelop()) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = 0;
        event.m_param1 = image;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjOpeningTelop::closeCenter() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x82));
    if (acc.m_object != nullptr && !GfMenuManager::isTheaterNonTelop()) {
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjOpeningTelop::openLeft(unsigned int image) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x82));
    if (acc.m_object != nullptr && !GfMenuManager::isTheaterNonTelop()) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = 1;
        event.m_param1 = image;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjOpeningTelop::closeLeft() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x82));
    if (acc.m_object != nullptr && !GfMenuManager::isTheaterNonTelop()) {
        ui::EventData event;
        event.m_type = 0x22;
        event.m_param0 = 1;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjOpeningTelop::openRight(unsigned int image) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x82));
    if (acc.m_object != nullptr && !GfMenuManager::isTheaterNonTelop()) {
        ui::EventData event;
        event.m_type = 0x21;
        event.m_param0 = 2;
        event.m_param1 = image;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjOpeningTelop::closeRight() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x82));
    if (acc.m_object != nullptr && !GfMenuManager::isTheaterNonTelop()) {
        ui::EventData event;
        event.m_type = 0x22;
        event.m_param0 = 2;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjOpeningTelop::openRightHalf(unsigned int image) {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x82));
        if (acc.m_object != nullptr && !GfMenuManager::isTheaterNonTelop()) {
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = 3;
            event.m_param1 = image;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjOpeningTelop::closeRightHalf() {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x82));
        if (acc.m_object != nullptr && !GfMenuManager::isTheaterNonTelop()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_param0 = 3;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjOpeningTelop::openLeftHalf(unsigned int image) {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x82));
        if (acc.m_object != nullptr && !GfMenuManager::isTheaterNonTelop()) {
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = 4;
            event.m_param1 = image;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjOpeningTelop::closeLeftHalf() {
    if (GfMenuObjUtil::isValidExpansion(3)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x82));
        if (acc.m_object != nullptr && !GfMenuManager::isTheaterNonTelop()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_param0 = 4;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
        }
    }
}

inline int GfMenuObjOpeningTelop::ctrlFadeIn(unsigned int handle, unsigned int eventId) {
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 1;
    param.m_time = 0.5f;
    param.m_eventId = eventId;
    return GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

inline int GfMenuObjOpeningTelop::ctrlFadeOut(unsigned int handle, unsigned int eventId) {
    GfMenuObjUtil::CtrlParam param;
    param.m_methods = 2;
    param.m_time = 0.5f;
    param.m_eventId = eventId;
    return GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjOpeningTelop::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
#line 253
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x82, acc.m_handle);
    GfMenuObject::initialize();
}

void GfMenuObjOpeningTelop::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjOpeningTelop::update() {
    for (unsigned int i = 0; i < m_streaming->getSize(); i++) {
        ui::UIObjectAcc image(m_streaming->getObject(i));
        if (!image.isStreaming()) {
            ctrlFadeIn(image.m_handle, 0);
            m_streaming->delObject(image.m_handle);
        }
    }
    GfMenuObject::update();
}

void GfMenuObjOpeningTelop::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 2:
        acc.setDisp(false);
        acc.setTerm();
        break;
    case 3: {
        // the control's end event: the position + 1 its fade-out passed, 0 for the fade-ins
        unsigned int id = event.m_param0;
        if (id == 0) {
            return;
        }
        int pos = id - 1;
        int count = m_owner->m_imageCounts[pos];
        mm::mtl::FixStr<32> name;
        for (int i = 0; i != count;) {
            i++;
            name.format(s_images[pos], i);
            ui::UIObjectAcc image(acc.m_handle, name.m_str);
            if (image.m_object != nullptr) {
                image.setImageIndex(0);
                image.setDisp(false);
            }
        }
        m_owner->m_imageCounts[pos] = 0;
        break;
    }
    case 0x21: {
        int pos = event.m_param0;
        unsigned int index = event.m_param1;
        {
            ui::UIObjectAcc layer(acc.m_handle, s_layers[pos]);
            int ctrl = GfMenuObjUtil::getCtrlID(layer.m_handle);
            if (ctrl != -1) {
                GfMenuObjUtil::stopCtrl(ctrl);
            }
            layer.setDisp(true);
            layer.setAlpha(1.0f);
        }
        int count = m_owner->m_imageCounts[pos];
        mm::mtl::FixStr<32> name;
        name.format(s_images[pos], count + 1);
        ui::UIObjectAcc image(acc.m_handle, name.m_str);
        image.setImageIndex(index);
        if (image.isStreaming()) {
            m_owner->m_streaming->addObject(image.m_handle);
        }
        m_owner->m_imageCounts[pos]++;
        break;
    }
    case 0x22: {
        int pos = event.m_param0;
        ui::UIObjectAcc layer(acc.m_handle, s_layers[pos]);
        int ctrl = ctrlFadeOut(layer.m_handle, pos + 1);
        GfMenuObject::hookCtrlEvent(acc.m_handle, ctrl);
        break;
    }
    }
    UIObjectListener::reciveEvent(event, handle);
}

}  // namespace gf
