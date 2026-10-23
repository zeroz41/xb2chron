#include "classes/wnd/WindObject.h"
#include "mm/mtl/IntrusiveList.h"
#include "wnd/UpdateInfo.h"
#include "classes/wnd/WindObject.h"
#include "classes/wnd/Dispatcher.h"
#include "wnd/OverlappingCache.h"
#include <float.h>
#include "classes/wnd/AreaWind.h"
#include "classes/wnd/LocalWind.h"
#include "classes/wnd/Shape.h"
#include "classes/wnd/WindProbe.h"
#include "mm/mtl/Vector.h"
#include "wnd/HitCache.h"
#include "wnd/SphereBoxAgent.h"
#include "wnd/SphereSphereAgent.h"

namespace wnd {

Dispatcher::Dispatcher(const CollisionInfo& info) : m_margin(info.margin) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            m_agents[i][j] = nullptr;
        }
    }
    SphereSphereAgent::registerAgent(*this);
    SphereBoxAgent::registerAgent(*this);
}

// 1.0.0's (name from its symbols); 3.0.1's linker dropped it as unused, leaving its strings in this file's .rodata.
void Dispatcher::dispatchAll(mm::mtl::IntrusiveList<WindProbe>& probes, const UpdateInfo& info) {
    HitCache caches[64];
    for (mm::mtl::IntrusiveList<WindProbe>::iterator it = probes.begin(); it != probes.end(); ++it) {
        WindProbe& probe = *it;
        const Shape* pProbeShape = probe.m_pShape;
#line 73
        MM_ASSERT(pProbeShape);
        OverlappingCache* pCache = probe.m_pOverlappingCache;
#line 76
        MM_ASSERT(pCache);
        unsigned int count = 0;
        mm::mtl::FixedQueue<WindObject*, 64>::iterator end = pCache->m_objects.end();
        for (mm::mtl::FixedQueue<WindObject*, 64>::iterator wi = pCache->m_objects.begin(); wi != end; ++wi) {
            WindObject* pWind = *wi;
#line 85
            MM_ASSERT(pWind);
            const Shape* pShape = pWind->m_pShape;
#line 87
            MM_ASSERT(pShape);
            ProcessCollisionFunc func = m_agents[pProbeShape->m_type][pShape->m_type];
            if (func != nullptr) {
                count += func(probe, *pWind, m_margin, &caches[count]);
            }
        }
        probe.m_hitCaches.clear();
        const AreaWind* pArea = nullptr;
        float distance = FLT_MAX;
        for (unsigned int i = 0; i < count; i++) {
            const HitCache& cache = caches[i];
            const WindObject* object = cache.object;
            switch (object->m_type) {
            case OBJECT_TYPE_LOCAL_WIND:
                if (probe.m_hitCaches.size() != probe.m_hitCaches.capacity()) {
                    LocalWindHitCache hit;
                    hit.pWind = static_cast<const LocalWind*>(object);
                    hit.normal = cache.normal;
                    hit.distance = cache.distance;
                    probe.m_hitCaches.push_back(hit);
                }
                break;
            case OBJECT_TYPE_AREA_WIND:
                if (!info.debugMode && cache.distance < distance) {
                    distance = cache.distance;
                    pArea = static_cast<const AreaWind*>(object);
                }
                break;
            default:
                break;
            }
        }
        probe.setAreaWind(pArea);
    }
}

}  // namespace wnd
