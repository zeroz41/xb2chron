#include "mm/mtl/Vector.h"
#include "wnd/Array.h"
#include "classes/wnd/GlobalWind.h"
#include "classes/wnd/GlobalWindManager.h"
#include "classes/wnd/ConpoundWind.h"
#include "wnd/ResConpoundWind.h"
#include "wnd/UpdateInfo.h"
#include "mm/MMStdBase.h"

namespace wnd {

GlobalWindManager::GlobalWindManager() : m_currentIndex(-1), m_debugIndex(-1) {}

void GlobalWindManager::setup(const Array<const ResConpoundWind*>& resWind, mm::mtl::IAllocator* allocator) {
    m_resWindNum = resWind.m_size;
    m_ppResWinds = resWind.m_pElements;
    m_winds.setAllocator(allocator);
    unsigned int num = resWind.m_size;
    m_winds.resize(num);
    for (unsigned int i = 0; i < num; i++) {
#line 42
        MM_ASSERT(resWind[i]);
        ConpoundWind& wind = m_winds[i];
        wind.m_pRes = resWind[i];
    }
}

bool GlobalWindManager::setCurrentWind(int index) {
    if (index > static_cast<int>(m_winds.size())) {
        return false;
    }
    if (m_currentIndex != index) {
        if (m_debugIndex == -1) {
            ConpoundWind* pWind = index == -1 ? nullptr : &m_winds[index];
            m_globalWind.changeNode(pWind, 1.0f);
            m_globalWind.setWind(pWind);
        }
        m_currentIndex = index;
    }
    return true;
}

void GlobalWind::update(const UpdateInfo& info) {
    if (m_pPrevWind != nullptr) {
        m_pPrevWind->update(info);
    }
    if (m_pWind != nullptr) {
        m_pWind->update(info);
    }
    WindBlender::update(info);
    if (m_pPrevWind == nullptr) {
        m_pPrevWind = nullptr;
    }
}

}  // namespace wnd
