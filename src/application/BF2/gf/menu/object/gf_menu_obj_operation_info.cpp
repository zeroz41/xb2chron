#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjOperationInfo/MainListener.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObjOperationInfo/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIObjectDockPlugin.h"
#include "plugin/Bdat.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjOperationInfo::GfMenuObjOperationInfo(unsigned int handle) : GfMenuObject(handle) {}

void GfMenuObjOperationInfo::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int main = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(main).m_object != nullptr) {
#line 108
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(main, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0x47, main);
    }
    GfMenuObject::initialize();
}

void GfMenuObjOperationInfo::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjOperationInfo::update() {
    GfMenuObject::update();
}

bool GfMenuObjOperationInfo::setupIconTable(mm::mtl::FixedVector<DupItem, 16>& items, unsigned int index,
                                            unsigned int key, unsigned int text, unsigned int order2) {
    if (index < items.size()) {
        for (unsigned int i = 0; i < index; i++) {
            if (items[i].m_key == key && items[i].m_used) {
                return false;
            }
        }
        items[index].m_key = key;
        items[index].m_text = text;
        const char* column = order2 == 0 ? "order" : "order2";
        unsigned char* fp = GfDataBdat::getFP(0x186);
        unsigned short order = 0;
        for (int id = Bdat::getIdTop(fp); id <= Bdat::getIdEnd(fp); id++) {
            if (static_cast<unsigned short>(Bdat::getVal(fp, "key", id)) == key) {
                order = Bdat::getVal(fp, column, id);
                break;
            }
        }
        items[index].m_order = order;
        items[index].m_used = true;
        return true;
    }
    return false;
}

void GfMenuObjOperationInfo::open(unsigned int a, unsigned int b, unsigned int c, unsigned int d) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x47);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = a;
            event.m_param1 = b;
            event.m_param2 = c;
            event.m_param3 = d;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjOperationInfo::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x47);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjOperationInfo::setDisp(bool disp) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x47);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::UIObjectAcc(handle).setDisp(disp);
        }
    }
}

void GfMenuObjOperationInfo::setGuideText(unsigned int text, unsigned int b) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x47);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x101;
            event.m_param0 = text;
            event.m_param1 = b;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjOperationInfo::setGuideDisp(bool disp) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x47);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x106;
            event.m_param0 = disp;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjOperationInfo::add(unsigned int handle_, unsigned int b, unsigned int c, unsigned int d) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x47);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x102;
            event.m_param0 = handle_;
            event.m_param1 = b;
            event.m_param2 = c;
            event.m_param3 = d;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjOperationInfo::remove(unsigned int handle_, unsigned int b, unsigned int c, unsigned int d) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x47);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x103;
            event.m_param0 = handle_;
            event.m_param1 = b;
            event.m_param2 = c;
            event.m_param3 = d;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjOperationInfo::changeText(unsigned int handle_, unsigned int action, bool alternate) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x47);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x104;
            event.m_param0 = handle_;
            event.m_param1 = action;
            event.m_param2 = alternate;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjOperationInfo::changeText(unsigned int handle_, unsigned int action, unsigned int text) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x47);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x104;
            event.m_param0 = handle_;
            event.m_param1 = action;
            event.m_param2 = text;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjOperationInfo::setActionEnable(unsigned int handle_, unsigned int action, bool enable) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x47);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x105;
            event.m_param0 = handle_;
            event.m_param1 = action;
            event.m_param2 = enable;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

}  // namespace gf
