#include "math.h"
#include "wnd/AABB.h"
#include "wnd/Query.h"
#include "wnd/PoolObjectMemory.h"
#include "classes/wnd/WindObject.h"
#include "classes/wnd/BroadPhazeProxy.h"
#include "classes/wnd/BroadPhazeInterface.h"
#include "classes/wnd/BroadPhazeOctree.h"
#include "classes/wnd/AreaWind.h"
#include "classes/wnd/Dispatcher.h"
#include "classes/wnd/Shape.h"
#include "classes/wnd/WindProbe.h"
#include "mm/MMStdBase.h"
#include "mm/mtl/FixedQueue.h"
#include "wnd/OverlappingCache.h"
#include "wnd/ResWind.h"
#include <new>

namespace wnd {

BroadPhazeOctree::BroadPhazeOctree(const ResWind& res, mm::mtl::IAllocator* allocator) : m_pAllocator(allocator) {
    const AABB& aabb = res.aabb;
    mm::Vec3 center = (aabb.max + aabb.min) * 0.5f;
    mm::Vec3 extent = aabb.max - aabb.min;
    float size = extent.x / 100.0f;
    float sizeY = extent.y / 100.0f;
    size = size > sizeY ? size : sizeY;
    float sizeZ = extent.z / 100.0f;
    size = size > sizeZ ? size : sizeZ;
    unsigned int depth = static_cast<unsigned int>(ceilf(log2f(size)));
    if (depth >= 15) {
        depth = 15;
    }
    float half = static_cast<float>(1 << depth) * 100.0f;
    AABB box;
    box.min = mm::Vec3(center.x - half, center.y - half, center.z - half);
    box.max = mm::Vec3(center.x + half, center.y + half, center.z + half);
    m_octree.setAABB(box, depth);
    m_root.m_aabb = box;
    m_areaPool.setAllocator(allocator);
}

BroadPhazeOctree::~BroadPhazeOctree() {
    eraseProxyForce(m_root);
}

void BroadPhazeOctree::eraseProxyForce(AreaBlock& area) {
    for (mm::mtl::IntrusiveList<AreaWind>::iterator it = area.m_winds.begin(); it != area.m_winds.end(); ++it) {
        destroyProxy(*it);
    }
    area.m_winds.clear();
    for (unsigned int i = 0; i < 8; i++) {
        if (AreaBlock* child = area.m_pChildren[i]) {
            eraseProxyForce(*child);
            gcArea(child);
        }
    }
}

void BroadPhazeOctree::createProxy(WindObject& wind) {
    Proxy* pProxy;
    if (m_proxyPool.m_freeList.empty()) {
        pProxy = nullptr;
    } else {
        pProxy = new (m_proxyPool.m_freeList.pop_front()) Proxy();
    }
    attachProxy(wind, *pProxy);
}

void BroadPhazeOctree::destroyProxy(WindObject& wind) {
    Proxy* pProxy = static_cast<Proxy*>(detachProxy(wind));
#line 77
    MM_ASSERT(pProxy);
    pProxy->~Proxy();
    m_proxyPool.m_freeList.push_back(pProxy);
}

bool BroadPhazeOctree::addWindObject(WindObject& wind) {
    createProxy(wind);
    AreaBlock* area = flushWindObject(wind);
    if (area == nullptr) {
        return false;
    }
    area->m_winds.push_back(static_cast<AreaWind*>(&wind));
    wind.addRef();
    return true;
}

void BroadPhazeOctree::removeWindObject(WindObject& wind) {
    Proxy* pProxy = static_cast<Proxy*>(wind.m_pProxy);
#line 161
    MM_ASSERT(pProxy);
    AreaBlock* area = getArea(pProxy->m_key);
    if (area == nullptr) {
        return;
    }
    area->m_winds.remove(static_cast<AreaWind*>(&wind));
    destroyProxy(wind);
    wind.release();
    gcArea(area);
}

AreaBlock* BroadPhazeOctree::getArea(const Key& key) {
    AreaBlock* area = &m_root;
    for (unsigned int level = 1; level < key.level; level++) {
        area = area->m_pChildren[(key.bits >> ((level - 1) * 4)) & 7];
    }
    return area;
}

void BroadPhazeOctree::gcArea(AreaBlock* area) {
    AreaBlock* block = area;
    while (AreaBlock* parent = block->m_pParent) {
        if (!block->m_winds.empty() || block->m_childFlags != 0) {
            return;
        }
        unsigned int index = 0;
        for (unsigned int i = 0; i < 8; i++) {
            if (block->m_pChildren[i] == area) {
                index = i;
                break;
            }
        }
        parent->destroyChild(index, m_areaPool);
        block = parent;
    }
}

void BroadPhazeOctree::calculateOverlapping(Dispatcher& dispatcher, mm::mtl::IntrusiveList<WindProbe>& probes) {
    flushProbes(probes);
    collectWindObj(dispatcher, probes);
}

void BroadPhazeOctree::flushProbes(mm::mtl::IntrusiveList<WindProbe>& probes) {
    for (mm::mtl::IntrusiveList<WindProbe>::iterator it = probes.begin(); it != probes.end(); ++it) {
        if (it->m_filter == FILTER_DYNAMIC) {
            if (it->m_pShape != nullptr && it->m_pProxy != nullptr && (it->m_flags & 1)) {
                it->m_pShape->calcAABB(it->m_transform, &it->m_pProxy->aabb);
                it->m_flags &= ~1;
            }
            flushWindObject(*it.m_node);
        }
    }
}

void BroadPhazeOctree::collectWindObj(Dispatcher& dispatcher, mm::mtl::IntrusiveList<WindProbe>& probes) {
    for (mm::mtl::IntrusiveList<WindProbe>::iterator it = probes.begin(); it != probes.end(); ++it) {
        BroadPhazeProxy* pProxy = it->m_pProxy;
        WindProbe& probe = *it;
        OverlappingCache* pCache = probe.m_pOverlappingCache;
        pCache->m_objects.clear();
        mm::mtl::FixedQueue<AreaBlock*, 1024> areas;
        if (isOverlap(m_root.m_aabb, pProxy->aabb, dispatcher.m_margin)) {
            areas.push_back(&m_root);
        }
        while (!areas.empty()) {
            AreaBlock* area = areas.front();
            areas.pop();
            detectAreaWind(area, pProxy->aabb, dispatcher.m_margin, pCache);
            for (unsigned int i = 0; i < 8; i++) {
                AreaBlock* child = area->m_pChildren[i];
                if (child != nullptr && isOverlap(child->m_aabb, pProxy->aabb, dispatcher.m_margin)) {
                    areas.push_back(child);
                }
            }
        }
    }
}

bool BroadPhazeOctree::query(Query* pQuery) {
    if (pQuery != nullptr) {
        if (AreaQuery* pAreaQuery = mm::mtl::rttiCast<AreaQuery>(pQuery)) {
            pAreaQuery->m_pArea = &m_root;
        }
    }
    return false;
}

void detectAreaWind(AreaBlock* pArea, const AABB& aabb, float margin, OverlappingCache* pCache) {
#line 235
    MM_ASSERT(pArea);
    MM_ASSERT(pCache);
    for (mm::mtl::IntrusiveList<AreaWind>::iterator it = pArea->m_winds.begin(); it != pArea->m_winds.end(); ++it) {
        BroadPhazeProxy* pProxy = it->m_pProxy;
#line 245
        MM_ASSERT(pProxy);
        if (isOverlap(pProxy->aabb, aabb, margin)) {
            WindObject* pWind = &*it;
            if (pCache->m_objects.full()) {
                mm::MMStdBase::mmPrint("warning:");
                mm::MMStdBase::mmPrint("ヒット候補が多すぎます");
            } else {
                pCache->m_objects.push_back(pWind);
            }
        }
    }
}

}  // namespace wnd
