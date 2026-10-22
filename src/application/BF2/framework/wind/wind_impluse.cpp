#include "classes/fw/WindImpluse.h"
#include "classes/wnd/LocalWind.h"
#include "fw/UpdateInfo.h"

namespace fw {

bool WindImpluse::update(const UpdateInfo& info) {
    m_elapsed += info.m_deltaTime;
    if (m_pWind) {
        float rate = m_elapsed / m_time;
        float clamped = rate < 0.0f ? 0.0f : (rate > 1.0f ? 1.0f : rate);
        m_pWind->m_power = m_power * (1.0f - clamped);
    }
    return m_elapsed < m_time;
}

}  // namespace fw
