#include "math.h"
#include "classes/wnd/ConpoundWind.h"
#include "classes/wnd/WindBlender.h"
#include "mm/MMStdBase.h"
#include "mm/Vec3.h"
#include "wnd/UpdateInfo.h"

namespace wnd {

WindBlender::WindBlender() : m_pNode(nullptr), m_pPrevNode(nullptr), m_rate(1.0f), m_time(0.0f) {}

void WindBlender::update(const UpdateInfo& info) {
    if (m_pPrevNode != nullptr) {
        m_rate += info.deltaTime / m_time;
        if (m_rate >= 1.0f) {
            m_pPrevNode = nullptr;
            m_rate = 1.0f;
        }
    }
    // each wind from the previous node's to the current one's (to zero without one) by the rate, or the current
    // node's (zero without one) once there is no previous node
    const mm::Vec3 zero = mm::Vec3::zero;
    for (int i = 0; i < 12; i++) {
        const WindNode* pNode = m_pNode;
        if (m_pPrevNode != nullptr) {
            mm::Vec3 from = m_pPrevNode->m_winds[i] * (1.0f - m_rate);
            if (pNode != nullptr) {
                mm::Vec3 to = pNode->m_winds[i] * m_rate;
                m_winds[i] = mm::Vec3(from.x + to.x, from.y + to.y, from.z + to.z);
            } else {
                mm::Vec3 to = zero * m_rate;
                m_winds[i] = mm::Vec3(from.x + to.x, from.y + to.y, from.z + to.z);
            }
        } else if (pNode != nullptr) {
            m_winds[i] = pNode->m_winds[i];
        } else {
            m_winds[i] = zero;
        }
    }
}

void WindBlender::changeNode(const WindNode* pNode, float time) {
    // its text has FLT_EPSILON as the SDK's float.h spells it
#line 80
    MM_ASSERT(abs(time) > 1.1920928955078125e-07F);
    if (m_pPrevNode != nullptr) {
        if (m_rate >= 0.5f) {
            m_pPrevNode = m_pNode;
        }
    } else {
        m_pPrevNode = m_pNode;
    }
    m_pNode = pNode;
    m_time = time;
    m_rate = 0.0f;
}

void WindBlender::setNode(const WindNode* pNode) {
    m_pNode = pNode;
    m_pPrevNode = nullptr;
    m_time = 0.0f;
}

ConpoundWind::ConpoundWind() : m_pRes(nullptr), m_powers() {}

}  // namespace wnd
