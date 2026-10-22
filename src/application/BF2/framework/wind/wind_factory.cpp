#include "classes/fw/DynamicWindResource.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/fw/ReferenceFrame.h"
#include "classes/fw/WindProbe.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/WindFactory.h"
#include "mm/Vec3.h"

namespace fw {

WindProbe* WindFactory::createProbe(unsigned int capacity, float radius, mm::mtl::IntrusivePtr<ReferenceFrame> frame,
                                    bool isMain) {
#line 28
    WindProbe* probe = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__)
        WindProbe(capacity, radius, frame, isMain);
    probe->addRef();
    return probe;
}

mm::mtl::IntrusivePtr<DynamicWindResource> WindFactory::createWindResource(const mm::Vec3& min, const mm::Vec3& max) {
#line 60
    DynamicWindResource* resource = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) DynamicWindResource();
    resource->m_resWind.aabb.min = min;
    resource->m_resWind.aabb.max = max;
    return resource;
}

}  // namespace fw
