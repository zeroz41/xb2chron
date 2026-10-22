#ifndef WND_AREABLOCK_H
#define WND_AREABLOCK_H

#include "mm/mtl/IntrusiveList.h"
#include "wnd/AABB.h"

namespace wnd { class AreaWind; }
namespace wnd { template <typename T> class PoolObjectMemory; }

namespace wnd {
// a cell of BroadPhazeOctree's tree: up to eight children, one per eighth of its box (wnd_area.cpp). Pooled: its
// node links it into a PoolObjectMemory's lists. The names other than m_winds are not the original's.
class AreaBlock : public mm::mtl::IntrusiveListNodeBase {
public:
    AreaBlock();
    ~AreaBlock();
    // a child from the pool at index, linked under this block and flagged in m_childFlags
    AreaBlock* createChild(unsigned int index, PoolObjectMemory<AreaBlock>& pool);
    // the child at index and all its descendants back to the pool, its flag cleared
    void destroyChild(unsigned int index, PoolObjectMemory<AreaBlock>& pool);

    AreaBlock* m_pParent;  // createChild's
    AreaBlock* m_pChildren[8];
    unsigned int m_childFlags;  // bit n: createChild set child n, destroyChild clears it
    // BroadPhazeOctree::flushWindObject sets a new child's to the tree level it is made at
    unsigned int m_level;
    AABB m_aabb;  // BroadPhazeOctree::flushWindObject sets a new child's to its eighth of the parent's box
    // the destructor asserts `m_winds.empty()`
    mm::mtl::IntrusiveList<AreaWind> m_winds;
};
}  // namespace wnd

#endif
