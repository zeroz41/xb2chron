#include "classes/gf/GfMenuObjEventSkip.h"
#include "classes/gf/GfMenuObjEventSkip/ListListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObjOperationInfo.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjEventSkip::GfMenuObjEventSkip(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjEventSkip::~GfMenuObjEventSkip() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjEventSkip::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int child = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(child).m_object != nullptr) {
#line 72
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(child, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0x2F, child);
    }
    GfMenuObject::initialize();
}

void GfMenuObjEventSkip::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjEventSkip::update() {
    GfMenuObject::update();
}

void GfMenuObjEventSkip::ListListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1: {
        ui::UIObjectAcc text(handle, "TXT_pause");
        GfMenuObjUtil::setDockPos(acc.searchChild("IMG_accent_l"), text.m_handle, 1, false);
        GfMenuObjUtil::addPos(acc.searchChild("IMG_accent_l"), -16, 0);
        GfMenuObjUtil::setDockPos(acc.searchChild("IMG_accent_r"), text.m_handle, 2, false);
        GfMenuObjUtil::addPos(acc.searchChild("IMG_accent_r"), 16, 0);
        acc.setDisp(false);
        GfMenuObject::disableInput(acc.m_handle);
        break;
    }
    case 2:
        GfMenuObject::termCallContext(handle);
        acc.setDisp(false);
        acc.setTerm();
        break;
    case 3:
        switch (m_pauseShown) {
        case 0: {
            ui::UIObjectAcc pause(handle, "LAY_pause");
            if (pause.m_object != nullptr) {
                pause.setAlpha(0.0f);
                GfMenuObjUtil::CtrlParam param;
                param.m_time = 1.0f;
                param.m_methods = 1;
                int ctrl = GfMenuObjUtil::startCtrl(pause.m_handle, param, nullptr);
                if (ctrl >= 0) {
                    GfMenuObject::hookCtrlEvent(handle, ctrl);
                }
                m_pauseShown = 1;
            }
            break;
        }
        case 1: {
            ui::UIObjectAcc pause(handle, "LAY_pause");
            if (pause.m_object != nullptr) {
                pause.setAlpha(1.0f);
                GfMenuObjUtil::CtrlParam param;
                param.m_time = 1.0f;
                param.m_methods = 2;
                int ctrl = GfMenuObjUtil::startCtrl(pause.m_handle, param, nullptr);
                if (ctrl >= 0) {
                    GfMenuObject::hookCtrlEvent(handle, ctrl);
                }
                m_pauseShown = 0;
            }
            break;
        }
        }
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 8:
        if (event.m_param1 == 1) {
            GfMenuObject::addResultCallContext(handle, 0, 0);
            close();
        } else if (event.m_param1 == 9 || event.m_param1 == 2) {
            GfMenuObject::addResultCallContext(handle, 1, 0);
            close();
        }
        GfMenuObjUtil::playSECommonFromInput(event.m_param1);
        break;
    case 0x21: {
        acc.setDisp(true);
        m_pauseShown = 1;
        ui::EventData start;
        start.m_type = 3;
        GfMenuObject::sendEvent(handle, start, 0.0f);
        GfMenuObject::enableInput(acc.m_handle);
        GfMenuObjOperationInfo::open(handle, 0, 0, 0);
        GfMenuObjOperationInfo::setGuideDisp(false);
        break;
    }
    case 0x22:
        GfMenuObject::termCallContext(handle);
        GfMenuObject::disableInput(acc.m_handle);
        GfMenuObjOperationInfo::close();
        acc.setDisp(false);
        break;
    }
}

void GfMenuObjEventSkip::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x2F);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjEventSkip::open(GfMenuCallContext* context) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x2F);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            GfMenuObject::startCallContext(context, 0x2F, handle);
            ui::EventData event;
            event.m_type = 0x21;
            GfMenuObject::sendEvent(handle, event, 0.0f);
            GfMenuObjUtil::playSE(3);
        }
    }
}

}  // namespace gf
