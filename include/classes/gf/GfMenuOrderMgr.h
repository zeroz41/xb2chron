#ifndef CLASSES_GF_GFMENUORDERMGR_H
#define CLASSES_GF_GFMENUORDERMGR_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedQueue.h"
#include "ui/EventData.h"

namespace gf { class GfMenuOrderMgr; class GfSetupParam; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B5EE88; 0x370 bytes (build allocates so many)
class GfMenuOrderMgr : public ::mm::mtl::PtrSingleton< ::gf::GfMenuOrderMgr> {
public:
    // one queued order (the name is the original's: FixedQueue<GfMenuOrderMgr::sLog, 20>::insert; the field names are
    // not): setOrder copies its first 0x24 bytes
    struct sLog {
        sLog() : m_channel(0), m_handle(0), m_event(0), m_priority(0) {}
        int m_channel;  // 1 or 2 (GfMenuObjZoneTelop / GfMenuObjLocationTelop)
        unsigned int m_handle;  // the menu object postUpdate sends m_event to
        ui::EventData m_event;
        int m_priority;  // setOrder: from the channel's table entry (0x71009B7A1C); inserts before lower ones
    };

    GfMenuOrderMgr() : m_state(0) {
        m_initialized = true;
        m_logs.clear();
    }
    virtual ~GfMenuOrderMgr();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isInitialized();
    static void postUpdate(const fw::UpdateInfo& info);
    // queues the event for the handle on that order channel; finishOrder ends the channel's current one
    static void setOrder(int channel, unsigned int handle, const ui::EventData& event);
    static void finishOrder(int channel);
    static void cancelOrder(int channel);

    // takes the channel's queued orders off (cancelOrder passes the singleton)
    void cancelLogOrder(int channel);
    // 2.0.0's symbols name it. What it does: false (and the order zeroed) when the queue is empty; otherwise pops the
    // first order into it and returns true, unless that order is on channel 2 while GfMenuObjUtil::isValidExpansion(3)
    // and (GfMenuManager::hasNpcEntry() or GfMenuReference::isIraFlag(6)) hold.
    bool pickLogOrder(sLog& order);

    bool m_initialized;  // build sets it, destroy clears it
    mm::mtl::FixedQueue<sLog, 20> m_logs;  // 0x10 (the name is not the original's)
    sLog m_current;  // 0x340: the order being shown (the name is not the original's)
    int m_state;  // 0x368: 1 once postUpdate sent m_current's event, 0 again after finishOrder (the name is not the original's)
};
}  // namespace gf

#endif
