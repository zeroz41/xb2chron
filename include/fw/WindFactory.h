#ifndef FW_WINDFACTORY_H
#define FW_WINDFACTORY_H

#include "mm/mtl/IntrusivePtr.h"

namespace mm { class Vec3; }
namespace fw { class DynamicWindResource; }
namespace fw { class ReferenceFrame; }
namespace fw { class WindProbe; }

namespace fw {
// makes the wind framework's objects from the framework's wind memory
class WindFactory {
public:
    // a probe with one reference held for the caller
    static WindProbe* createProbe(unsigned int seed, float radius, mm::mtl::IntrusivePtr<ReferenceFrame> frame,
                                  bool flag);
    // a resource for a world spanning min to max, with no area winds
    static mm::mtl::IntrusivePtr<DynamicWindResource> createWindResource(const mm::Vec3& min, const mm::Vec3& max);
};
}  // namespace fw

#endif
