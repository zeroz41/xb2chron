#ifndef IDCOLI_IDCOLIMOVE_H
#define IDCOLI_IDCOLIMOVE_H

#include "mm/Vec3.h"

namespace idcoli { class IDColiObj; }

namespace idcoli {
// one collision-checked move of an object, built on the stack (0x200 bytes)
class IDColiMove {
public:
    IDColiMove();
    void setAccuracy(bool accuracy);
    // moves `obj` by `move` as far as the collision allows; m_result holds how far it went
    bool moveColi(IDColiObj* obj, mm::Vec3 const& move);

    unsigned char pad_0[0x130];
    mm::Vec3 m_result;  // moveColi's: the move it allowed (the whole move for an object it skips)
    unsigned char pad_140[0xC0];
};
}  // namespace idcoli

#endif
