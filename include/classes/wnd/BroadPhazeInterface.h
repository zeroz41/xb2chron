#ifndef CLASSES_WND_BROADPHAZEINTERFACE_H
#define CLASSES_WND_BROADPHAZEINTERFACE_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/wnd/BroadPhazeProxy.h"
#include "classes/wnd/Shape.h"
#include "classes/wnd/WindObject.h"
#include "mm/MMStdBase.h"

// wndlib's wnd_broad_phaze_interface.h, as wndlib's own files' include path named it (the only spelling known)
#define WND_BROAD_PHAZE_INTERFACE_PATH "../../src\\wndlib/broadphaze/wnd_broad_phaze_interface.h"

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
    // the answer to a query; false from BroadPhazeOctree's (the return type is inferred from it)
    virtual bool query(Query* pQuery) = 0;  // slot 7

protected:
    // the object and the proxy tied to each other, the proxy's box its shape's (the names are not the original's)
    static void attachProxy(WindObject& wind, BroadPhazeProxy& proxy) {
#line 47 WND_BROAD_PHAZE_INTERFACE_PATH
        MM_ASSERT(wind.m_pProxy == nullptr);
#line 48 WND_BROAD_PHAZE_INTERFACE_PATH
        MM_ASSERT(proxy.pOnwer == nullptr);
        wind.m_pProxy = &proxy;
        proxy.pOnwer = &wind;
#line 54 WND_BROAD_PHAZE_INTERFACE_PATH
        MM_ASSERT(wind.m_pShape);
        wind.m_pShape->calcAABB(wind.m_transform, &proxy.aabb);
    }
    // the object's proxy, untied from it
    static BroadPhazeProxy* detachProxy(WindObject& wind) {
#line 60 WND_BROAD_PHAZE_INTERFACE_PATH
        MM_ASSERT(wind.m_pProxy != nullptr);
        BroadPhazeProxy* pProxy = wind.m_pProxy;
#line 63 WND_BROAD_PHAZE_INTERFACE_PATH
        MM_ASSERT(pProxy->pOnwer != nullptr);
        wind.m_pProxy = nullptr;
        pProxy->pOnwer = nullptr;
        return pProxy;
    }
};
}  // namespace wnd

#endif
