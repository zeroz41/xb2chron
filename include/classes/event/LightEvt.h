#ifndef CLASSES_EVENT_LIGHTEVT_H
#define CLASSES_EVENT_LIGHTEVT_H

#include "mm/mtl/FixStr.h"
namespace ml { class ScnObj; }

namespace event {
// table 0x7100B3D1C0
class LightEvt {
public:
    virtual ~LightEvt();  // slot 0
    // play (0x71000F75E4) releases the previous light to the scene, keeps the name, then the light the scene creates
    // and the int it was created with (the names are not the original's)
    ml::ScnObj* m_lgt;  // 0x8
    mm::mtl::FixStr<128> m_name;  // 0x10
    unsigned int m_lgtParam;  // 0x94
};
}  // namespace event

#endif
