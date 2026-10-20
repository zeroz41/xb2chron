#ifndef CLASSES_WND_BROADPHAZEOCTREE_H
#define CLASSES_WND_BROADPHAZEOCTREE_H

namespace mm { namespace mtl { template <typename> class IntrusiveList; }}
namespace wnd { class Dispatcher; }
namespace wnd { class Query; }
namespace wnd { class WindObject; }
namespace wnd { class WindProbe; }

namespace wnd {
// table 0x7100B816D8
class BroadPhazeOctree {
public:
    class Proxy;
    virtual ~BroadPhazeOctree();  // slot 0
    virtual void createProxy(wnd::WindObject&);  // slot 2
    virtual void destroyProxy(wnd::WindObject&);  // slot 3
    virtual void addWindObject(wnd::WindObject&);  // slot 4
    virtual void removeWindObject(wnd::WindObject&);  // slot 5
    virtual void calculateOverlapping(wnd::Dispatcher&, mm::mtl::IntrusiveList<wnd::WindProbe>&);  // slot 6
    virtual void query(wnd::Query*);  // slot 7
};
}  // namespace wnd

#endif
