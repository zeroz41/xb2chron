#include "classes/gf/TUnk_B62D58.h"
#include "ui/EventData.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

TUnk_B62D58::TUnk_B62D58(unsigned int handle) : GfMenuObject(handle), m_dispCount(0) {}

TUnk_B62D58::~TUnk_B62D58() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void TUnk_B62D58::initialize() {
    {
        ui::UIObjectAcc acc(m_handle, "LAY_loading");
#line 53
        TUnk_B62DA0* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B62DA0(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    {
        ui::UIObjectAcc acc(m_handle, "LAY_saving");
#line 58
        TUnk_B62DA0* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) TUnk_B62DA0(this);
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    GfMenuObject::attachExternalCall(0x8f, m_handle);
    GfMenuObject::initialize();
}

void TUnk_B62D58::finalize() {
    GfMenuObject::finalize();
}

void TUnk_B62D58::update() {
    GfMenuObject::update();
}

void TUnk_B62DA0::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 0x21: {
        if (m_owner->m_dispCount++ > 0) {
            break;
        }
        float time = event.m_param0 * (1.0f / 30.0f);
        if (time == 0.0f) {
            acc.setDisp(true);
            break;
        }
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = time;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        break;
    }
    case 0x22: {
        if (--m_owner->m_dispCount > 0) {
            break;
        }
        m_owner->m_dispCount = 0;
        float time = event.m_param0 * (1.0f / 30.0f);
        if (time == 0.0f) {
            acc.setDisp(false);
            break;
        }
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = time;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        break;
    }
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    }
}

void TUnk_B62D58::fn_710042AE80(bool open, unsigned short frames) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8f));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = open ? 0x21 : 0x22;
        event.m_param0 = frames;
        GfMenuObject::sendEvent(acc.searchChild("LAY_loading"), event, 0.0f);
    }
}

void TUnk_B62D58::fn_710042AF14(bool open, unsigned short frames) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x8f));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = open ? 0x21 : 0x22;
        event.m_param0 = frames;
        GfMenuObject::sendEvent(acc.searchChild("LAY_saving"), event, 0.0f);
    }
}

}  // namespace gf
