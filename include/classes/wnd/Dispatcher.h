#ifndef CLASSES_WND_DISPATCHER_H
#define CLASSES_WND_DISPATCHER_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace wnd { class CollisionInfo; }
namespace wnd { class HitCache; }
namespace wnd { class WindObject; }

namespace wnd {
// a collision agent's test of two objects within a margin: true, with the cache filled, when they touch
typedef bool (*ProcessCollisionFunc)(const WindObject&, const WindObject&, float, HitCache*);

// table 0x7100B817E0; counted (its constructor clears the count at 8)
class Dispatcher : public mm::mtl::ReferenceObject {
public:
    Dispatcher(const CollisionInfo& info);
    virtual ~Dispatcher();  // slot 0

    // by the two objects' shape types: the constructor clears them and each agent's registerAgent sets its own
    ProcessCollisionFunc m_agents[2][2];
    unsigned char pad_30[0x8];  // fields: the constructor copies its info's first word to 0x30
};
}  // namespace wnd

#endif
