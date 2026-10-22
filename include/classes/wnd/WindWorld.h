#ifndef CLASSES_WND_WINDWORLD_H
#define CLASSES_WND_WINDWORLD_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "classes/wnd/AreaWind.h"
#include "classes/wnd/BroadPhazeInterface.h"
#include "classes/wnd/Dispatcher.h"
#include "classes/wnd/GlobalWindManager.h"
#include "classes/wnd/LocalWind.h"
#include "classes/wnd/WindProbe.h"
#include "mm/mtl/IntrusiveList.h"
#include "wnd/Array.h"

namespace mm { namespace mtl { class IAllocator; }}
namespace wnd { class ResConpoundWind; }

namespace wnd {
// table 0x7100B818A0; counted (the constructor clears the count at 8). Its winds and probes, the broad phase that
// finds which touch, and the objects it lets go of. The field names other than m_pBroadPhaze (wnd_world.cpp asserts
// it) are not the original's.
class WindWorld : public mm::mtl::ReferenceObject {
public:
    WindWorld(Dispatcher* pDispatcher, BroadPhazeInterface* pBroadPhaze, const Array<const ResConpoundWind*>& resWind,
              mm::mtl::IAllocator* allocator);
    virtual ~WindWorld();  // slot 0
    // the area wind out of the broad phase and the world, released on the next update (1.0.0's; 3.0.1 has only the
    // destructor's inlined copy)
    void removeAreaWind(AreaWind& wind);
    void removeProbe(WindProbe& probe);
    // what removeProbe and removeAreaWind let go of, released (1.0.0's; 3.0.1 has only update's and the
    // destructor's inlined copies)
    void delayErace();
    void update(float deltaTime);
    bool addAreaWind(AreaWind& wind);
    bool addProbe(WindProbe& probe);

    float m_time;  // update adds each step to it
    GlobalWindManager m_globalWindManager;  // the constructor sets it up with its resources
    // the constructor's, referenced; the destructor releases them
    BroadPhazeInterface* m_pBroadPhaze;
    Dispatcher* m_pDispatcher;
    mm::mtl::IntrusiveList<WindProbe> m_probes;  // addProbe's
    mm::mtl::IntrusiveList<mm::mtl::IntrusiveListNode<AreaWind> > m_areaWinds;  // addAreaWind's
    mm::mtl::IntrusiveList<mm::mtl::IntrusiveListNode<LocalWind> > m_localWinds;  // the local winds'
    // what removeProbe and removeAreaWind let go of, through each object's m_releaseNode
    mm::mtl::IntrusiveList<mm::mtl::IntrusiveListNode<WindObject> > m_releaseList;
    bool m_debugMode;  // update hands it on in its UpdateInfo's debugMode
};
}  // namespace wnd

#endif
