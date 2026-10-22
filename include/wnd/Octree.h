#ifndef WND_OCTREE_H
#define WND_OCTREE_H

#include "wnd/AABB.h"

namespace mm { class Vec3; }

namespace wnd {
// a box cut into eighths, depth levels deep
class Octree {
public:
    Octree();
    void setAABB(const AABB& aabb, unsigned int depth);
    // the eighth holding a position at each level below the top, four bits a level (the first level's lowest);
    // all ones outside the box
    unsigned long getBitFlag(const mm::Vec3& pos) const;

    AABB m_aabb;
    unsigned int m_depth;
};
}  // namespace wnd

#endif
