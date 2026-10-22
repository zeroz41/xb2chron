#include "ui/EventData.h"
#include "gf/GfMenuSequence.h"
#include "gf/GfMenuObjUtil.h"
#include "classes/gf/GfMenuOrderMgr.h"
#include "classes/gf/GfMenuObjZoneTelop.h"
#include "classes/gf/GfMenuObjZoneTelop/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/UIStr.h"

namespace gf {

GfMenuObjZoneTelop::GfMenuObjZoneTelop(unsigned int handle)
    : GfMenuObject(handle), m_seq(this), m_fadeStarted(false), m_fadeOutTime(0.0f) {}

GfMenuObjZoneTelop::~GfMenuObjZoneTelop() {}

void GfMenuObjZoneTelop::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int child = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(child).m_object != nullptr) {
#line 70
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(child, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::attachExternalCall(0x45, child);
    }
    GfMenuObject::initialize();
}

void GfMenuObjZoneTelop::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjZoneTelop::update() {
    m_seq.update();
    GfMenuObject::update();
}

void GfMenuObjZoneTelop::MainListener::reciveEvent(const ui::EventData& event, unsigned int handle) {
    ui::UIObjectAcc acc(handle);
    switch (event.m_type) {
    case 1:
        acc.setDisp(false);
        break;
    case 2:
        GfMenuObject::termCallContext(handle);
        acc.setTerm();
        break;
    default:
        UIObjectListener::reciveEvent(event, handle);
        break;
    case 0x21: {
        ui::UIObjectAcc title(acc.m_handle, "TXT_title");
        title.setText(ui::UIStr(GfDataBdat::getFP(0x12D), event.m_param0));
        m_owner->m_fadeOutTime = 0.5f;
        m_owner->m_fadeStarted = false;
        m_owner->m_seq.clear();
        m_owner->m_seq.addJob(&GfMenuObjZoneTelop::seqFadeIn);
        m_owner->m_seq.addWait(120);
        m_owner->m_seq.addJob(&GfMenuObjZoneTelop::seqFadeOut);
        break;
    }
    case 0x22:
        if (event.m_param0Float == 0.0f) {
            m_owner->m_fadeStarted = false;
            m_owner->m_seq.clear();
            acc.setDisp(false);
            GfMenuObject::termCallContext(acc.m_handle);
            GfMenuOrderMgr::finishOrder(1);
        } else {
            m_owner->m_fadeOutTime = event.m_param0Float;
            m_owner->m_fadeStarted = false;
            m_owner->m_seq.clear();
            m_owner->m_seq.addJob(&GfMenuObjZoneTelop::seqFadeOut);
        }
        break;
    }
}

bool GfMenuObjZoneTelop::seqFadeIn() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (!m_fadeStarted) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = 0.5f;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        m_fadeStarted = true;
        return false;
    }
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.m_handle))) {
        return false;
    }
    m_fadeStarted = false;
    return true;
}

bool GfMenuObjZoneTelop::seqFadeOut() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (!m_fadeStarted) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = m_fadeOutTime;
        GfMenuObjUtil::startCtrl(acc.m_handle, param, nullptr);
        m_fadeStarted = true;
        return false;
    }
    if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.m_handle))) {
        return false;
    }
    m_fadeStarted = false;
    GfMenuObject::termCallContext(acc.m_handle);
    GfMenuOrderMgr::finishOrder(1);
    return true;
}

void GfMenuObjZoneTelop::open(GfMenuCallContext* context, unsigned short name) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x45);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            if (context != nullptr) {
                GfMenuObject::startCallContext(context, 0x45, handle);
            }
            ui::EventData event;
            event.m_type = 0x21;
            event.m_param0 = name;
            GfMenuOrderMgr::setOrder(1, handle, event);
        }
    }
}

void GfMenuObjZoneTelop::close(float time) {
    unsigned int handle = GfMenuObject::getAttachedObject(0x45);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_param0Float = time;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

}  // namespace gf
