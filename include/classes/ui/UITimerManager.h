#ifndef CLASSES_UI_UITIMERMANAGER_H
#define CLASSES_UI_UITIMERMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/fw/PointerMap.h"
#include "mm/mtl/IntrusiveList.h"

namespace ui { class UITimerManager; }
namespace fw { class UpdateInfo; }

namespace ui {
// table 0x7100B755B8; the timers it runs for objects: each one's end sends its object an event (0xB)
class UITimerManager : public ::mm::mtl::PtrSingleton< ::ui::UITimerManager> {
public:
    // one timer in the list (the names are not the original's)
    struct TimerNode : public mm::mtl::IntrusiveListNodeBase {
        unsigned int m_handle;        // its timer's handle in m_timers
        unsigned int m_objHandle;     // the object it sends its event to
        unsigned short m_eventId;     // the event's first parameter
        unsigned short m_count;       // the times it ended; the event's second parameter
        bool m_suspend;               // 1.0.0's suspendTimer: update leaves it as it is
        bool m_repeat;                // it restarts at its end, instead of being released
    };
    UITimerManager();
    virtual ~UITimerManager();  // slot 0
    void update(const fw::UpdateInfo& info);
    // a timer of end time units for the object handle, its event's id the id; its handle, 0 when none is made
    unsigned int registTimer(unsigned int handle, unsigned short id, unsigned long end, bool repeat);
    void releaseTimer(unsigned int handle);
    void setTimerSpeedFactor(unsigned int handle, float factor);
    unsigned int getTimerHandle(unsigned int objHandle);  // the first timer of the object
    fw::PointerMap m_timers;  // the UITimers, by handle
    mm::mtl::IntrusiveList<TimerNode> m_list;
    bool m_suspend;  // 1.0.0's suspend: update runs no timer
};
}  // namespace ui

#endif
