#ifndef CLASSES_WND_DISPATCHER_H
#define CLASSES_WND_DISPATCHER_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace wnd { class HitCache; }
namespace wnd { class WindObject; }

namespace wnd {
// a collision agent's test of two objects within a margin: true, with the cache filled, when they touch
typedef bool (*ProcessCollisionFunc)(const WindObject&, const WindObject&, float, HitCache*);

// what Dispatcher's constructor takes (fw::WindManager::buildWorld's margin is 0.001); the field name is not the
// original's
class CollisionInfo {
public:
    float margin;  // what 1.0.0's Dispatcher::dispatchAll passes each agent as its margin
};

// table 0x7100B817E0; counted (its constructor clears the count at 8)
class Dispatcher : public mm::mtl::ReferenceObject {
public:
    Dispatcher(const CollisionInfo& info);
    virtual ~Dispatcher() {}  // slot 0: inline, so its D1 slot is the base's destructor

    // by the two objects' shape types: the constructor clears them and each agent's registerAgent sets its own
    ProcessCollisionFunc m_agents[2][2];
    float m_margin;  // the constructor's info.margin (the name is not the original's)
};
}  // namespace wnd

#endif
