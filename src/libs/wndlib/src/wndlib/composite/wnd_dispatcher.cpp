#include "classes/wnd/Dispatcher.h"
#include "wnd/SphereBoxAgent.h"
#include "wnd/SphereSphereAgent.h"

namespace wnd {

Dispatcher::Dispatcher(const CollisionInfo& info) : m_margin(info.margin) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            m_agents[i][j] = nullptr;
        }
    }
    SphereSphereAgent::registerAgent(*this);
    SphereBoxAgent::registerAgent(*this);
}

}  // namespace wnd
