#ifndef WND_HITCACHE_H
#define WND_HITCACHE_H

#include "mm/Vec3.h"

namespace wnd {
class WindObject;

// what a collision agent's processCollision reports for a pair that touches
class HitCache {
public:
    const WindObject* object;  // the pair's second object
    float distance;  // between the two objects' positions
    mm::Vec3 normal;  // from the second object's position to the first's, at length 1 (zero when they coincide)
};
}  // namespace wnd

#endif
