#include "classes/wnd/WindObject.h"
#include "classes/wnd/LocalWind.h"
#include "classes/wnd/Shape.h"
#include "mm/MMStdBase.h"
#include "mm/Vec3.h"

namespace wnd {

void LocalWind::calcEffectiveWind(const mm::Vec3& pos, mm::Vec3* pWind) const {
    mm::Vec3 dir = mm::Vec3::zero;
    if (m_pShape != nullptr) {
        switch (m_pShape->m_type) {
        case SHAPE_TYPE_SPHERE:
            dir = pos - m_transform.position;
            break;
        default:
            mm::MMStdBase::mmPrint("warning:");
            mm::MMStdBase::mmPrint("未対応な形状です");
#line 49
            MM_ASSERT(0);
            break;
        }
    }
    float distance = dir.length();
    dir.normalize();
    float damping = calcDampingDistance(distance);
    *pWind = dir * m_power * damping;
}

}  // namespace wnd
