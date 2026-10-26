#include "classes/gf/GfMenuObjPopup.h"
#include "classes/gf/GfMenuObjPopup/PopupInfo.h"
#include "classes/gf/GfMenuObjPopup/MainListener.h"
#include "classes/gf/GfMenuManyObjects.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfGameManager.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "plugin/Bdat.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjPopup::GfMenuObjPopup(unsigned int handle)
    : GfMenuObject(handle), m_open(false), m_giftWait(false), pad_26(false), m_count(0), m_number05_1(nullptr),
      m_number05_2(nullptr), m_number05_3(nullptr), m_number05_4(nullptr), m_number09(nullptr), m_number11(nullptr),
      m_seq(this), m_giftSeq(this) {}

GfMenuObjPopup::~GfMenuObjPopup() {
    if (m_number05_1 != nullptr) {
        m_number05_1->release();
        m_number05_1 = nullptr;
    }
    if (m_number05_2 != nullptr) {
        m_number05_2->release();
        m_number05_2 = nullptr;
    }
    if (m_number05_3 != nullptr) {
        m_number05_3->release();
        m_number05_3 = nullptr;
    }
    if (m_number05_4 != nullptr) {
        m_number05_4->release();
        m_number05_4 = nullptr;
    }
    if (m_number09 != nullptr) {
        m_number09->release();
        m_number09 = nullptr;
    }
    if (m_number11 != nullptr) {
        m_number11->release();
        m_number11 = nullptr;
    }
    GfMenuManyObjects::destroyQueue<PopupInfo>(7);
}

void GfMenuObjPopup::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjPopup::update() {
    m_seq.update();
    m_giftSeq.update();
    GfMenuObject::update();
}

bool GfMenuObjPopup::fn_710045C9E4() {
    ui::UIObjectAcc icon(m_handle, "IMG_gift_icon");
    m_giftSeq.addAnimJob(icon.m_handle, "out");
    m_giftSeq.addJob(&GfMenuObjPopup::fn_710045DA2C);
    return true;
}

bool GfMenuObjPopup::fn_710045CB7C() {
    if (GfMenuManager::isFading()) {
        return false;
    }
    ui::UIObjectAcc icon(m_handle, "IMG_gift_icon");
    GfMenuObjUtil::playSE(0x22);
    m_giftSeq.addAnimJob(icon.m_handle, "in");
    m_giftSeq.addAnimJob(icon.m_handle, "out");
    m_giftSeq.addJob(&GfMenuObjPopup::fn_710045DA2C);
    icon.setDisp(true);
    return true;
}

void GfMenuObjPopup::close(unsigned int handle) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x76));
    if (root.m_object != nullptr && !root.isTerm()) {
        ui::UIObjectAcc popup(handle);
        if (popup.m_object != nullptr && popup.isDuplicate()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_param0Short = ui::UIObjectAcc(handle).getDuplicateIndex();
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjPopup::closeAll() {
    GfMenuManyObjects::closeAll<PopupInfo>(7, &close);
}

void GfMenuObjPopup::pausePickup() {
    unsigned int root = GfMenuObject::getAttachedObject(0x76);
    if (ui::UIObjectAcc(root).m_object == nullptr) {
        return;
    }
    if (!ui::UIObjectAcc(root).isTerm()) {
        ui::EventData event;
        event.m_type = 0x101;
        ui::UIManager::get()->requestObjectEvent(root, event, 0.0f);
    }
}

void GfMenuObjPopup::continuePickup(unsigned int param) {
    unsigned int root = GfMenuObject::getAttachedObject(0x76);
    if (ui::UIObjectAcc(root).m_object == nullptr) {
        return;
    }
    if (ui::UIObjectAcc(root).isTerm()) {
        return;
    }
    if (!GfGameManager::isEvent(false) && !GfGameManager::isEventWait()) {
        ui::EventData event;
        event.m_type = 0x102;
        event.m_param0 = param;
        ui::UIManager::get()->requestObjectEvent(root, event, 0.0f);
    }
}

bool GfMenuObjPopup::fn_710045DA2C() {
    m_giftWait = false;
    return true;
}

}  // namespace gf
