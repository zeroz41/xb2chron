#ifndef CLASSES_WND_BROADPHAZEINTERFACE_H
#define CLASSES_WND_BROADPHAZEINTERFACE_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace mm { namespace mtl { template <typename> class IntrusiveList; }}
namespace wnd { class Dispatcher; }
namespace wnd { class Query; }
namespace wnd { class WindObject; }
namespace wnd { class WindProbe; }

namespace wnd {
// table none (abstract and never constructed on its own: WindWorld's constructor takes one, 1.0.0's mangled name
// says so); counted (WindWorld adds a reference at 8). The slots are BroadPhazeOctree's, in its table's order; the
// parameter names are not the original's.
class BroadPhazeInterface : public mm::mtl::ReferenceObject {
public:
    virtual ~BroadPhazeInterface() {}  // slot 0
    virtual void createProxy(WindObject& object) = 0;  // slot 2: WindWorld::addProbe
    virtual void destroyProxy(WindObject& object) = 0;  // slot 3: WindWorld::removeProbe
    // slot 4: WindWorld::addAreaWind keeps the wind only when it is true
    virtual bool addWindObject(WindObject& object) = 0;
    virtual void removeWindObject(WindObject& object) = 0;  // slot 5: WindWorld::removeAreaWind
    virtual void calculateOverlapping(Dispatcher& dispatcher, mm::mtl::IntrusiveList<WindProbe>& probes) = 0;  // slot 6
    virtual void query(Query* pQuery) = 0;  // slot 7
};
}  // namespace wnd

#endif
