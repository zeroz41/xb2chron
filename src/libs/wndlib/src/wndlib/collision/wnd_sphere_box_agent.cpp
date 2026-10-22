#include "wnd/SphereBoxAgent.h"
#include "classes/wnd/Dispatcher.h"
#include "classes/wnd/Shape.h"

namespace wnd {

void SphereBoxAgent::registerAgent(Dispatcher& dispatcher) {
    dispatcher.m_agents[SHAPE_TYPE_SPHERE][SHAPE_TYPE_BOX] = &processCollision;
}

// processCollision (0x7100895388) is not matched yet

}  // namespace wnd
