#ifndef CLASSES_WND_BROADPHAZEOCTREE_H
#define CLASSES_WND_BROADPHAZEOCTREE_H

#include "classes/wnd/BroadPhazeInterface.h"
#include "classes/wnd/BroadPhazeProxy.h"
#include "mm/mtl/IntrusiveList.h"
#include "wnd/AreaBlock.h"
#include "wnd/Octree.h"
#include "wnd/PoolObjectMemory.h"

namespace mm { namespace mtl { class IAllocator; }}
namespace wnd { class AABB; }
namespace wnd { class Dispatcher; }
namespace wnd { class OverlappingCache; }
namespace wnd { class Query; }
namespace wnd { class ResWind; }
namespace wnd { class WindObject; }
namespace wnd { class WindProbe; }

namespace wnd {
// table 0x7100B816D8; the broad phase over an octree of AreaBlocks: each area wind is kept in the cell its position
// falls in, and each probe collects the winds of the cells its box touches
class BroadPhazeOctree : public BroadPhazeInterface {
public:
    // a cell of the tree: the eighth at each level below the top (four bits a level, Octree::getBitFlag's) and
    // the level (1.0.0's getArea takes one)
    struct Key {
        unsigned long bits;
        unsigned int level;
    };
    // table 0x7100B81728; an octree proxy: the cell its object's position falls in (its destructor adds nothing,
    // so the table's first slot is the base's)
    class Proxy : public BroadPhazeProxy {
    public:
        Proxy() {
            m_key.bits = ~0UL;
            m_key.level = 0;
        }
        virtual ~Proxy() {}  // slot 0

        Key m_key;
    };
    // a fixed number of T in place, the unused ones in a list (the name and those of the members are not the
    // original's)
    template <typename T, int N>
    class FixedPool {
    public:
        FixedPool() {
            for (int i = 0; i < N; i++) {
                m_freeList.push_back(&m_objects[i]);
            }
        }

        T m_objects[N];
        mm::mtl::IntrusiveList<T> m_freeList;
    };

    BroadPhazeOctree(const ResWind& res, mm::mtl::IAllocator* allocator);
    virtual ~BroadPhazeOctree();  // slot 0
    void eraseProxyForce(AreaBlock& area);
    virtual void createProxy(WindObject& wind);  // slot 2
    virtual void destroyProxy(WindObject& wind);  // slot 3
    // the cell the object's proxy falls in, made when it is missing; none when its box is not inside the tree's
    AreaBlock* flushWindObject(WindObject& wind);
    virtual bool addWindObject(WindObject& wind);  // slot 4
    virtual void removeWindObject(WindObject& wind);  // slot 5
    // the cell of the key (1.0.0 has it out of line; 3.0.1 only inlines it)
    AreaBlock* getArea(const Key& key);
    // the empty cells from area up back to the pool (1.0.0 has it out of line; 3.0.1 only inlines it)
    void gcArea(AreaBlock* area);
    virtual void calculateOverlapping(Dispatcher& dispatcher, mm::mtl::IntrusiveList<WindProbe>& probes);  // slot 6
    // each dynamic probe's box recomputed when it moved, and its cell found (1.0.0 has it out of line; 3.0.1 only
    // inlines it into calculateOverlapping)
    void flushProbes(mm::mtl::IntrusiveList<WindProbe>& probes);
    void collectWindObj(Dispatcher& dispatcher, mm::mtl::IntrusiveList<WindProbe>& probes);
    virtual bool query(Query* pQuery);  // slot 7

    // the names below are not the original's
    Octree m_octree;
    AreaBlock m_root;
    mm::mtl::IAllocator* m_pAllocator;  // the constructor's
    FixedPool<Proxy, 512> m_proxyPool;
    PoolObjectMemory<AreaBlock> m_areaPool;
};

// the area winds of area whose boxes touch aabb within margin, into the cache
void detectAreaWind(AreaBlock* pArea, const AABB& aabb, float margin, OverlappingCache* pCache);
}  // namespace wnd

#endif
