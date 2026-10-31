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

bool GfMenuObjPopup::s_disp;

GfMenuObjPopup::GfMenuObjPopup(unsigned int handle)
    : GfMenuObject(handle), m_open(false), m_giftWait(false), pad_26(false), m_count(0), m_number05_1(nullptr),
      m_number05_2(nullptr), m_number05_3(nullptr), m_number05_4(nullptr), m_number09(nullptr), m_number11(nullptr),
      m_seq(this), m_giftSeq((GfMenuObjShop*)this) {}

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
    GfMenuManyObjects::destroy<PopupInfo>(7);
}

void GfMenuObjPopup::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
#line 130
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::attachExternalCall(0x76, main);
    {
    unsigned char* names = GfDataBdat::getFP(0x15c);
    unsigned char* labels = GfDataBdat::getFP(0x15c);
    unsigned char* text = GfDataBdat::getFP(0x132);
    unsigned int id05_1 = static_cast<unsigned short>(Bdat::getVal(labels, "name", 7));
    ui::UIObjectAcc text05_1(acc.searchChild("TXT_text@05_1"));
    text05_1.setText(ui::UIStr(text, id05_1));
    unsigned int id05_2 = static_cast<unsigned short>(Bdat::getVal(labels, "name", 8));
    ui::UIObjectAcc text05_2(acc.searchChild("TXT_text@05_2"));
    text05_2.setText(ui::UIStr(text, id05_2));
    unsigned int id05_3 = static_cast<unsigned short>(Bdat::getVal(labels, "name", 9));
    ui::UIObjectAcc text05_3(acc.searchChild("TXT_text@05_3"));
    text05_3.setText(ui::UIStr(text, id05_3));
    unsigned int id05_4 = static_cast<unsigned short>(Bdat::getVal(labels, "name", 10));
    ui::UIObjectAcc text05_4(acc.searchChild("TXT_text@05_4"));
    text05_4.setText(ui::UIStr(text, id05_4));
    unsigned int id09 = static_cast<unsigned short>(Bdat::getVal(names, "name", 4));
    unsigned char* text09 = GfDataBdat::getFP(0x132);
    ui::UIObjectAcc acc09(acc.searchChild("TXT_text@09"));
    acc09.setText(ui::UIStr(text09, id09));
    unsigned int id11 = static_cast<unsigned short>(Bdat::getVal(names, "name", 3));
    unsigned char* text11 = GfDataBdat::getFP(0x132);
    ui::UIObjectAcc acc11(acc.searchChild("TXT_text@11"));
    acc11.setText(ui::UIStr(text11, id11));
    }
    m_number05_1 = ui::UIObjectNumberPlugin::create(acc.searchChild("TXT_text@05_1"));
    m_number05_2 = ui::UIObjectNumberPlugin::create(acc.searchChild("TXT_text@05_2"));
    m_number05_3 = ui::UIObjectNumberPlugin::create(acc.searchChild("TXT_text@05_3"));
    m_number05_4 = ui::UIObjectNumberPlugin::create(acc.searchChild("TXT_text@05_4"));
    m_number09 = ui::UIObjectNumberPlugin::create(acc.searchChild("TXT_text@09"));
    m_number11 = ui::UIObjectNumberPlugin::create(acc.searchChild("TXT_text@11"));
    GfMenuObject::initialize();
    GfMenuManyObjects::createQueue<PopupInfo>(7, 64);
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
