#include "classes/fw/DynamicWindResource.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/WindProbe.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/WindFactory.h"
#include "mm/Vec3.h"

namespace fw {

DynamicWindResource::DynamicWindResource() {}

DynamicWindResource::~DynamicWindResource() {}

WindProbe* WindFactory::createProbe(unsigned int capacity, float radius, mm::mtl::IntrusivePtr<ReferenceFrame> frame,
                                    bool isMain) {
#line 28
    WindProbe* probe = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__)
        WindProbe(capacity, radius, frame, isMain);
    probe->addRef();
    return probe;
}

// createWindResource (0x71001AAB24) is not matched yet: this file's constructor gets inlined into it, where the
// original calls it

}  // namespace fw
