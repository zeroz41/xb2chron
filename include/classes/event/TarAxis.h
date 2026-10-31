#ifndef CLASSES_EVENT_TARAXIS_H
#define CLASSES_EVENT_TARAXIS_H

#include "mm/Vec3.h"

namespace event {
// table 0x7100B3BFB0
class TarAxis {
public:
    // out of line (the script commands' exec construct their member with it): type 1, value mm::Vec3::zero
    TarAxis();
    // 1.0.0's TarAxis(unsigned int, float, float, float); 3.0.1 keeps no copy (every user inlines it)
    TarAxis(unsigned int type, float x, float y, float z) : m_type(type), m_value(x, y, z) {}
    virtual ~TarAxis() {}  // slot 0
    // how the target is given, as PosAxis's; the name is not the original's
    unsigned int m_type;  // 0x8
    mm::Vec3 m_value;     // 0x10; the name is not the original's
};
}  // namespace event

#endif
