#include "mm/mtl/Vector.h"
#include "classes/wnd/LocalWind.h"
#include "classes/wnd/WindProbe.h"
#include "classes/wnd/GlobalWind.h"
#include "wnd/Query.h"
#include "classes/wnd/AreaWind.h"
#include "mm/MMStdBase.h"

namespace wnd {

mm::mtl::RTTI Query::m_rtti("Query", nullptr, nullptr);
mm::mtl::RTTI AreaWindQuery::m_rtti("AreaWindQuery", &Query::m_rtti, nullptr);
mm::mtl::RTTI LocalWindQuery::m_rtti("LocalWindQuery", &Query::m_rtti, nullptr);
mm::mtl::RTTI ProbeQuery::m_rtti("ProbeQuery", &Query::m_rtti, nullptr);
mm::mtl::RTTI AreaQuery::m_rtti("AreaQuery", &Query::m_rtti, nullptr);

WindProbe::WindProbe(const ProbeCreateInfo& info, unsigned int windIndex, mm::mtl::IAllocator* allocator)
    : WindObject(OBJECT_TYPE_PROBE, info),
      m_windIndex(windIndex),
      m_pGlobalWind(nullptr),
      m_pAreaWind(nullptr),
      m_hitCaches(allocator),
      m_pOverlappingCache(nullptr) {
    m_hitCaches.reserve(info.capacity);
}

WindProbe::~WindProbe() {
#line 38
    MM_ASSERT(m_pOverlappingCache == nullptr);
}

void WindProbe::bindGlobalWind(const GlobalWind& wind) {
    m_blender.setNode(&wind);
    m_pGlobalWind = &wind;
}

void WindProbe::unbindGlobalWind() {
    if (m_pGlobalWind == m_blender.m_pNode) {
        m_blender.setNode(nullptr);
    }
    m_pGlobalWind = nullptr;
}

void WindProbe::calcGlobalWindPower(const UpdateInfo& info) {
    m_blender.update(info);
}

void WindProbe::setAreaWind(const AreaWind* pAreaWind) {
    if (m_pAreaWind != pAreaWind) {
        if (pAreaWind != nullptr) {
            m_blender.changeNode(&pAreaWind->m_wind, pAreaWind->m_blendTime);
        } else {
            m_blender.changeNode(m_pGlobalWind, m_pAreaWind->m_blendTime);
        }
        m_pAreaWind = pAreaWind;
    }
}

}  // namespace wnd
