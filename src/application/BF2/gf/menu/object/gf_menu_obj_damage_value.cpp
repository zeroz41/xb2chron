#include "classes/gf/GfMenuObjDamageValue.h"
#include "classes/gf/GfMenuObjDamageValue/DamageInfo.h"
#include "classes/gf/GfMenuObjDamageValue/ListListener.h"
#include "classes/gf/GfMenuManyObjects.h"
#include "classes/gf/GfMenuCallManager.h"
#include "classes/gf/GfMenuFieldPosAdapter.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfMenuObjUtil.h"
#include "plugin/Bdat.h"
#include "ml/MTRand.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedQueue.h"
#include "mm/Vec2.h"
#include "mm/Vec3.h"
#include "mm/Math.h"
#include "ui/EventData.h"
#include "ui/UIStr.h"
#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIEventManager.h"
#include "classes/ui/UIObjectAcc.h"

namespace gf {

// Proposed name, not the original's: the symbols leave it unnamed (lbl_7100EAAA50)
mm::mtl::FixedQueue<GfMenuObjDamageValue::OpenParam, 32> GfMenuObjDamageValue::s_openRequests;

GfMenuObjDamageValue::GfMenuObjDamageValue(unsigned int handle) : GfMenuObject(handle) {}

GfMenuObjDamageValue::~GfMenuObjDamageValue() {
    GfMenuManyObjects::destroy<DamageInfo>(0);
}

void GfMenuObjDamageValue::initialize() {
    ui::UIObjectAcc acc(m_handle);
    unsigned int list = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(list).m_object != nullptr) {
        GfMenuObject::attachExternalCall(0x2c, list);
#line 91
        ListListener* listener = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) ListListener(this);
        // the original stores the count after the listener's own fields, not with its base
        listener->m_RefCount = 1;
        ui::UIEventManager::get()->registObjectListener(list, listener);
        if (listener != nullptr) {
            listener->release();
        }
    }
    ui::UIObjectAcc(m_handle).setTerm();
    GfMenuObject::initialize();
    GfMenuManyObjects::createQueue<DamageInfo>(0, 32);
    s_openRequests.clear();
}

void GfMenuObjDamageValue::finalize() {
    GfMenuObject::finalize();
}

void GfMenuObjDamageValue::update() {
    const mm::mtl::FixedQueue<OpenParam, 32>& requests = s_openRequests;
    for (mm::mtl::FixedQueue<OpenParam, 32>::const_iterator it = requests.begin(); it != requests.end(); ++it) {
        open(*it);
    }
    s_openRequests.clear();
    GfMenuObject::update();
}

// 0x71003E634C open(const OpenParam&) (fn_71003E634C): not identical yet, candidate in wip/

inline void GfMenuObjDamageValue::removeObject(ui::UIObjectAcc screen) {
    GfMenuManyObjects::remove<DamageInfo>(0, screen.m_handle);
    screen.setDisp(false);
    screen.setTerm();
}

// 0x71003E67C4 ListListener::reciveEvent: not identical yet, candidate in wip/

// 0x71003E6CF4 setupScreen: not identical yet, candidate in wip/

unsigned int GfMenuObjDamageValue::fn_71003E7394(const OpenParam& param) {
    if (s_openRequests.full()) {
        s_openRequests.pop();
    }
    s_openRequests.push_back(param);
    return 0;
}

void GfMenuObjDamageValue::close(unsigned int handle) {
    ui::UIObjectAcc root(GfMenuObject::getAttachedObject(0x2c));
    if (root.m_object != nullptr && !root.isTerm()) {
        ui::UIObjectAcc screen(handle);
        if (screen.m_object != nullptr && screen.isDuplicate()) {
            ui::EventData event;
            event.m_type = 0x22;
            event.m_param0Short = screen.getDuplicateIndex();
            GfMenuObject::sendEvent(root.m_handle, event, 0.0f);
        }
    }
}

void GfMenuObjDamageValue::closeAll() {
    unsigned int root = GfMenuObject::getAttachedObject(0x2c);
    if (ui::UIObjectAcc(root).m_object == nullptr) {
        return;
    }
    if (ui::UIObjectAcc(root).isTerm()) {
        return;
    }
    GfMenuManyObjects::closeAll<DamageInfo>(0, &close);
    s_openRequests.clear();
}

}  // namespace gf

// the info queue's operations (their callers, open and the list listener's, are not written yet)
template void mm::mtl::Queue<gf::GfMenuObjDamageValue::DamageInfo>::push_back(const gf::GfMenuObjDamageValue::DamageInfo&);
template void gf::GfMenuManyObjects::remove<gf::GfMenuObjDamageValue::DamageInfo>(unsigned int, unsigned int);
