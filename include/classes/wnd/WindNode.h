#ifndef CLASSES_WND_WINDNODE_H
#define CLASSES_WND_WINDNODE_H

#include "mm/Vec3.h"
#include "mm/mtl/FixedArray.h"

namespace wnd { class UpdateInfo; }

namespace wnd {
// table 0x7100B81818
class WindNode {
public:
    WindNode() { m_winds.assign(mm::Vec3::zero); }
    virtual void update(wnd::UpdateInfo const&) = 0;  // slot 0

    // twelve winds: ConpoundWind::update computes each, WindBlender::update blends two nodes' into its own
    mm::mtl::FixedArray<mm::Vec3, 12> m_winds;
};
}  // namespace wnd

#endif
