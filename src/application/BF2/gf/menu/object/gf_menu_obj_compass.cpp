#include "gf/FileStaticVec3.h"
#include "classes/gf/GfMenuObjCompass.h"
#include "classes/gf/GfMenuObjCompass/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjCompass::GfMenuObjCompass(unsigned int handle) : GfMenuObject(handle) {
    m_IconObjList.clear();
}

GfMenuObjCompass::~GfMenuObjCompass() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjCompass::initialize() {
    ui::UIObjectAcc acc(m_handle, "LAY_main");
    GfMenuObject::attachExternalCall(0x42, acc.m_handle);
    GfMenuObject::attachExternalCall(0x43, acc.m_handle);
#line 83
    MainListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) MainListener(this);
    // the original stores the count after the listener's own fields, not with its base
    listener->m_RefCount = 1;
    ui::UIEventManager::get()->registObjectListener(acc.m_handle, listener);
    if (listener != nullptr) {
        listener->release();
    }
    GfMenuObject::initialize();
}

void GfMenuObjCompass::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjCompass::open() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x42);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x21;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

void GfMenuObjCompass::close() {
    unsigned int handle = GfMenuObject::getAttachedObject(0x42);
    if (ui::UIObjectAcc(handle).m_object != nullptr) {
        if (!ui::UIObjectAcc(handle).isTerm()) {
            ui::EventData event;
            event.m_type = 0x22;
            GfMenuObject::sendEvent(handle, event, 0.0f);
        }
    }
}

mm::mtl::FixedVector<GfMenuObjCompass::IconObj, 32> GfMenuObjCompass::m_IconObjList;

}  // namespace gf
