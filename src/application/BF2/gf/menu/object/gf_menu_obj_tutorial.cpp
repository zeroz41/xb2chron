#include "classes/gf/GfMenuObjTutorial.h"
#include "classes/gf/GfMenuObjTutorial/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfMenuCallContext.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "mm/mtl/Delegate.h"
#include "gf/GfMenuSequence.h"

namespace gf {

// the tutorial's call context: the constructor creates it, the destructor releases it (the name is not the
// original's; the symbol is unnamed)
static GfMenuCallContext* s_context;

GfMenuObjTutorial::GfMenuObjTutorial(unsigned int handle) : GfMenuObject(handle), m_seq(this), m_termWait(0) {
    s_context = GfMenuCallContext::create();
    s_context->reset();
}

GfMenuObjTutorial::~GfMenuObjTutorial() {
    if (s_context != nullptr) {
        s_context->release();
        s_context = nullptr;
    }
}

void GfMenuObjTutorial::openText(unsigned int index, const TextParam& param) {
    if (GfMenuObjUtil::checkCCStart(s_context)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
        if (acc.m_object != nullptr) {
            unsigned short text = GfMenuObject::registString(ui::UIStr(GfDataBdat::getFP(0x12A), param.m_text));
            ui::EventData event;
            event.m_type = 0x101;
            event.m_paramShort[0] = index;
            event.m_paramShort[1] = 1;
            event.m_paramShort[2] = text;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(s_context, 0x7A, acc.m_handle);
        }
    }
}

void GfMenuObjTutorial::closeText(unsigned int index) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x101;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = 0;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

bool GfMenuObjTutorial::isWaiting() {
    return s_context != nullptr && s_context->isActive();
}

void GfMenuObjTutorial::openFocus(unsigned int index, const FocusParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x102;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = 1;
        event.m_paramShort[2] = param.m_value[2];
        event.m_paramShort[3] = param.m_value[0];
        event.m_paramShort[4] = param.m_value[1];
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTutorial::closeFocus(unsigned int index) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x102;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = 0;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTutorial::openIcon(unsigned int index, const IconParam& param) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x103;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = 1;
        event.m_paramShort[3] = param.m_value[0];
        event.m_paramShort[4] = param.m_value[1];
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTutorial::closeIcon(unsigned int index) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x103;
        event.m_paramShort[0] = index;
        event.m_paramShort[1] = 0;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTutorial::start() {
    if (GfMenuObjUtil::checkCCStart(s_context)) {
        ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
        if (acc.m_object != nullptr) {
            ui::EventData event;
            event.m_type = 0x104;
            GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
            GfMenuObject::startCallContext(s_context, 0x7A, acc.m_handle);
        }
    }
}

void GfMenuObjTutorial::closeAll() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x7A));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x22;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjTutorial::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    if (acc.m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x7A, acc.m_handle);
#line 239
        MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
        if (listener != nullptr) {
            listener->release();
        }
        GfMenuObject::initialize();
    }
}

void GfMenuObjTutorial::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjTutorial::update() {
    m_seq.update();
    GfMenuObject::update();
}

bool GfMenuObjTutorial::seqEnd() {
    ui::UIObjectAcc main(m_handle, "LAY_main");
    ui::EventData event;
    event.m_type = 0x105;
    GfMenuObject::sendEvent(main.m_handle, event, 0.0f);
    return true;
}
}  // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTutorial>(const mm::mtl::Delegate<bool()>*);

template bool gf::GfMenuSequence<gf::GfMenuObjTutorial, 8>::wait();

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjTutorial, 8>>(const mm::mtl::Delegate<bool()>*);

namespace gf {

}  // namespace gf
