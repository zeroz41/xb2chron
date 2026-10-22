#ifndef CLASSES_WND_CONPOUNDWIND_H
#define CLASSES_WND_CONPOUNDWIND_H

#include "classes/wnd/WindNode.h"

namespace mm { class Vec3; }
namespace wnd { class ResConpoundWind; }
namespace wnd { class UpdateInfo; }

namespace wnd {
// table 0x7100B81868
class ConpoundWind : public WindNode {
public:
    ConpoundWind();
    virtual void update(wnd::UpdateInfo const&);  // slot 0
    void calcWind(float time, unsigned int index, mm::Vec3* pWind);

    const ResConpoundWind* m_pRes;  // calcWind's waves' parameters
    float m_powers[12][5];  // calcWind's: each wind's five waves' strengths
};
}  // namespace wnd

#endif
