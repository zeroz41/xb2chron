#include "classes/gf/GfMenuObjSpecialGauge.h"
#include "classes/gf/GfMenuObjSpecialGauge/MainListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuManager.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIManager.h"
#include "classes/ui/UIObjectAcc.h"
#include "gf/GfMenuObjUtil.h"
#include "mm/mtl/FixStr.h"
#include "ui/EventData.h"

namespace gf {

GfMenuObjSpecialGauge::GfMenuObjSpecialGauge(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjSpecialGauge::~GfMenuObjSpecialGauge() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

void GfMenuObjSpecialGauge::push() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x29));
    if (acc.m_object != nullptr) {
        ui::EventData event;
        event.m_type = 0x10A;
        GfMenuObject::sendEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjSpecialGauge::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjSpecialGauge::update() {
    ui::UIObjectAcc(m_handle).setAlpha(1.0f);
    GfMenuObject::update();
}

void GfMenuObjSpecialGauge::open() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x29));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x100;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

void GfMenuObjSpecialGauge::close() {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x29));
    if (acc.m_object != nullptr && !acc.isTerm()) {
        ui::EventData event;
        event.m_type = 0x101;
        ui::UIManager::get()->requestObjectEvent(acc.m_handle, event, 0.0f);
    }
}

}  // namespace gf
