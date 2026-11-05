#include "classes/gf/GfMenuOrderMgr.h"
#include "classes/gf/GfAllocator.h"
#include "classes/ui/UIManager.h"

namespace gf {

GfMenuOrderMgr::~GfMenuOrderMgr() {}

void GfMenuOrderMgr::cancelOrder(int channel) {
    get()->cancelLogOrder(channel);
}

void GfMenuOrderMgr::setOrder(int channel, unsigned int handle, const ui::EventData& event) {
    // each channel's priority (lbl_71009B7A18; the name is not the original's)
    static const struct {
        int m_channel;
        int m_priority;
    } s_channelPriorities[] = {{1, 6}, {2, 5}};
    sLog log(channel, handle, event);
    int priority = 0;
    for (unsigned int i = 0; i < 2; ++i) {
        if (s_channelPriorities[i].m_channel == channel) {
            priority = s_channelPriorities[i].m_priority;
            break;
        }
    }
    log.m_priority = priority;
    GfMenuOrderMgr* mgr = get();
    if (mgr->m_logs.full()) {
        return;
    }
    mm::mtl::FixedQueue<sLog, 20>::iterator last = mgr->m_logs.end();
    for (mm::mtl::FixedQueue<sLog, 20>::iterator it = mgr->m_logs.begin(); it != last; ++it) {
        sLog& entry = *it;
        if (entry.m_channel == 2 && entry.m_channel == channel && entry.m_event.m_param3 == 0) {
            entry = log;
            return;
        }
        if (entry.m_priority < log.m_priority) {
            mgr->m_logs.insert(it, log);
            return;
        }
    }
    mgr->m_logs.push_back(log);
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
    if (mgr != nullptr && mgr->m_state == 0 && mgr->pickLogOrder(mgr->m_current)) {
        ui::UIManager::get()->requestObjectEvent(mgr->m_current.m_handle, mgr->m_current.m_event, 0.0f);
        mgr->m_state = 1;
    }
}

}  // namespace gf
