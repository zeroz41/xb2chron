#ifndef WND_SPHEREBOXAGENT_H
#define WND_SPHEREBOXAGENT_H

namespace wnd { class Dispatcher; }
namespace wnd { class HitCache; }
namespace wnd { class WindObject; }

namespace wnd {
// the collision test of a sphere (first) and a box (second)
class SphereBoxAgent {
public:
    static void registerAgent(Dispatcher& dispatcher);
    static bool processCollision(const WindObject& obj0, const WindObject& obj1, float margin, HitCache* pCache);
};
}  // namespace wnd

#endif
