#include "classes/gf/GfMenuObjActionWindow.h"
#include "classes/gf/GfMenuObjActionWindow/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuGameAdapter.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfGameUtil.h"
#include "gf/GfMenuBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjActionWindow::GfMenuObjActionWindow(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjActionWindow::~GfMenuObjActionWindow() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjActionWindow::initialize() {
    ui::UIObjectAcc acc(m_handle);
    if (acc.m_object != nullptr) {
        GfMenuObject::attachExternalCall(10, m_handle);
        unsigned int child = acc.searchChild("LAY_main");
        if (ui::UIObjectAcc(child).m_object != nullptr) {
            GfMenuObject::attachExternalCall(11, child);
#line 87
            MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
            // the original stores the count after the listener's own fields, not with its base
            listener->m_RefCount = 1;
            ui::UIEventManager::get()->registObjectListener(child, listener);
            if (listener != nullptr) {
                listener->release();
            }
        }
        GfMenuGameAdapter::create(acc.searchChild("LAY_contents"), 0x11, true);
        GfMenuObject::initialize();
    }
}

void GfMenuObjActionWindow::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjActionWindow::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
    case 0x101:
        acc.setDisp(false);
        break;
    case 0x100: {
        {
            ui::UIObjectAcc text(acc.searchChild("TXT_content"));
            if (text.m_object != nullptr) {
                GfMenuObject::setText(text.m_handle, event.m_param0);
            }
        }
        if (event.m_param1 != -1) {
            ui::UIObjectAcc icon(handle, "IMG_btn");
            if (icon.m_object != nullptr) {
                icon.setImageIndex(event.m_param1);
                icon.setDisp(true);
            } else {
                icon.setDisp(false);
            }
        }
        acc.setDisp(true);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void GfMenuObjActionWindow::update() {
    GfMenuObject::update();
}

void GfMenuObjActionWindow::eventHudSceneChange(unsigned int) {}

void GfMenuObjActionWindow::open(const OpenParam& param) {
    unsigned int handle = GfMenuObject::getAttachedObject(11);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            GF_OBJ_HANDLE* obj = param.m_obj;
            GfGameUtil::UiActionWindowInfo info;
            if (obj != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                info.create(obj);
            }
            unsigned short str = GfMenuObject::registString(ui::UIStr(info.m_bdat, info.m_id));
            ui::EventData event;
            event.m_type = 0x100;
            event.m_param0 = str;
            event.m_param1 = GfMenuBdat::getIconImageIndex(GfMenuObjUtil::getBtnIconNumber(param.m_button));
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjActionWindow::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(11);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x101;
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjActionWindow::disp(bool disp) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(10));
    if (acc.m_object != nullptr) {
        acc.setDisp(disp);
    }
}

void GfMenuObjActionWindow::openBattle(const OpenParam& param) {
    unsigned int handle = GfMenuObject::getAttachedObject(11);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            unsigned short str = GfMenuObject::registString(ui::UIStr(GfDataBdat::getFP(0x1AB), 5));
            ui::EventData event;
            event.m_type = 0x100;
            event.m_param0 = str;
            event.m_param1 = GfMenuBdat::getIconImageIndex(GfMenuObjUtil::getBtnIconNumber(param.m_button));
            ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjActionWindow::closeBattle() {
    close();
}

}  // namespace gf
