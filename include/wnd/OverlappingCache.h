#ifndef WND_OVERLAPPINGCACHE_H
#define WND_OVERLAPPINGCACHE_H

#include "mm/mtl/FixedQueue.h"

namespace wnd { class WindObject; }

namespace wnd {
// a probe's candidates for a collision: wnd::detectAreaWind queues the area winds whose boxes its box touches
// (it prints a warning, not an assertion, once 64 are queued); 1.0.0's Dispatcher::dispatchAll tests each against
// the probe
class OverlappingCache {
public:
    unsigned char pad_0[0x10];
    mm::mtl::FixedQueue<WindObject*, 64> m_objects;  // the name is not the original's
};
}  // namespace wnd

#endif
