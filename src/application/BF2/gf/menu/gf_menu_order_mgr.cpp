#include "classes/gf/GfMenuOrderMgr.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIManager.h"

namespace gf {

GfMenuOrderMgr::~GfMenuOrderMgr() {}

void GfMenuOrderMgr::cancelOrder(int channel) {
    get()->cancelLogOrder(channel);
}

void GfMenuOrderMgr::finishOrder(int channel) {
    GfMenuOrderMgr* mgr = get();
    if (mgr->m_current.m_channel == channel) {
        mgr->m_state = 0;
    }
}

void GfMenuOrderMgr::build(const GfSetupParam& param) {
#line 67
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMenuOrderMgr;
}

void GfMenuOrderMgr::destroy() {
    GfMenuOrderMgr* mgr = get();
    mgr->m_initialized = false;
    delete mgr;
}

bool GfMenuOrderMgr::isInitialized() {
    GfMenuOrderMgr* mgr = get();
    if (mgr != nullptr) {
        return mgr->m_initialized;
    }
    return false;
}

void GfMenuOrderMgr::postUpdate(const fw::UpdateInfo& info) {
    GfMenuOrderMgr* mgr = get();
    if (mgr != nullptr && mgr->m_state == 0 && mgr->fn_7100363CD4(mgr->m_current)) {
        ui::UIManager::get()->requestObjectEvent(mgr->m_current.m_handle, mgr->m_current.m_event, 0.0f);
        mgr->m_state = 1;
    }
}

}  // namespace gf
