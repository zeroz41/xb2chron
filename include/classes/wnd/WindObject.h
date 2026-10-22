#ifndef CLASSES_WND_WINDOBJECT_H
#define CLASSES_WND_WINDOBJECT_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/IntrusiveList.h"
#include "wnd/Transform.h"

// wndlib's wnd_object.h, as the game's files' include path named it (wndlib's own spelling is not known yet: none
// of its matched files inlines a citation from it)
#ifndef MM_LIB_FROM_LIBS
#define WND_OBJECT_PATH "D:/Monolithsoft/BF2/prog/application/BF2//../../libs/wndlib/src\\wndlib/object/wnd_object.h"
#endif

namespace wnd { class BroadPhazeProxy; }
namespace wnd { class Shape; }

namespace wnd {
// what an object is: wnd::WindProbe's constructor gives WindObject's 1, AreaWind's 2, LocalWind's 0
enum ObjectType {
    OBJECT_TYPE_LOCAL_WIND = 0,  // 1.0.0's LocalWind constructor's (the name is not the original's)
    OBJECT_TYPE_PROBE = 1,
    OBJECT_TYPE_AREA_WIND = 2,
};

// how an object moves: setTransform asserts `m_filter == FILTER_DYNAMIC`; fw::WindProbe's are dynamic,
// fw::WindManager::buildWorld's area winds 0
enum Filter {
    FILTER_DYNAMIC = 1,
};

// what WindObject's constructor takes (it asserts both pointers); constructed empty, so a derived create-info's
// first field takes the space after filter (ProbeCreateInfo's capacity)
class WindObjectCreateInfo {
public:
    WindObjectCreateInfo() : pTransform(nullptr), pShape(nullptr), filter() {}

    const Transform* pTransform;
    Shape* pShape;
    Filter filter;
};

// table 0x7100B818C0; counted (its constructor clears the count at 8). Its list node base is what WindWorld's
// object lists link (an element is found from its node by the base's offset, 0x10).
class WindObject : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNodeBase {
public:
    WindObject(ObjectType type, const WindObjectCreateInfo& info);
    virtual ~WindObject();  // slot 0

    // a dynamic object's move; BroadPhazeOctree::calculateOverlapping recomputes its proxy's box next
    void setTransform(const Transform& transform) {
#ifdef WND_OBJECT_PATH
#line 69 WND_OBJECT_PATH
#endif
        MM_ASSERT(m_filter == FILTER_DYNAMIC);
        m_transform = transform;
        m_flags |= 1;
    }

    ObjectType m_type;  // the constructor's
    Transform m_transform;  // the constructor copies its create-info's info.pTransform
    Shape* m_shape;  // the constructor's info.pShape, referenced; the destructor releases it
    // the create-info's; BroadPhazeOctree::calculateOverlapping recomputes the proxy's box of a dynamic object
    Filter m_filter;
    BroadPhazeProxy* m_pProxy;  // BroadPhazeOctree::createProxy's; the destructor asserts it is gone
    unsigned int m_flags;  // bit 0: setTransform sets it; calculateOverlapping recomputes the proxy's box, clears it
    // WindWorld links it into the list of objects it releases on its next update, which finds the object
    // through m_pReleaseOwner
    mm::mtl::IntrusiveListNodeBase m_releaseNode;
    WindObject* m_pReleaseOwner;  // the constructor's: this object
};
}  // namespace wnd

#endif
