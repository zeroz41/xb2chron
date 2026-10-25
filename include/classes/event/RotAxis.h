#ifndef CLASSES_EVENT_ROTAXIS_H
#define CLASSES_EVENT_ROTAXIS_H

#include "mm/Vec3.h"

namespace event {
// table 0x7100B3BF90
class RotAxis {
public:
    RotAxis(unsigned int type, float x, float y, float z);
    virtual ~RotAxis() {}  // slot 0
    // how the rotation is given (1.0.0's getOrigName names the origin from it); the name is not the original's
    unsigned int m_type;  // 0x8
    mm::Vec3 m_value;     // 0x10; the name is not the original's
};
}  // namespace event

#endif
