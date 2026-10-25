#ifndef CLASSES_EVENT_POSAXIS_H
#define CLASSES_EVENT_POSAXIS_H

#include "mm/Vec3.h"

namespace event {
// table 0x7100B3BF70
class PosAxis {
public:
    // out of line (the script commands' exec construct their member with it)
    PosAxis();
    PosAxis(unsigned int type, float x, float y, float z);
    virtual ~PosAxis() {}  // slot 0
    // how the position is given (1.0.0's getOrigName names the origin from it); the name is not the original's
    unsigned int m_type;  // 0x8
    mm::Vec3 m_value;     // 0x10; the name is not the original's
};
}  // namespace event

#endif
