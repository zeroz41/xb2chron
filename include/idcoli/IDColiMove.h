#ifndef IDCOLI_IDCOLIMOVE_H
#define IDCOLI_IDCOLIMOVE_H

#include "mm/Vec3.h"

namespace idcoli { class IDColiObj; }

namespace idcoli {
// one collision-checked move of an object, built on the stack (0x200 bytes)
class IDColiMove {
public:
    IDColiMove();
    void setShapeParms(float parm0, float parm1);
    void setFloor(float floor);
    void setAccuracy(bool accuracy);
    // moves `obj` by `move` as far as the collision allows; m_result holds how far it went
    bool moveColi(IDColiObj* obj, mm::Vec3 const& move);

    unsigned char pad_0[0x130];
    mm::Vec3 m_result;  // moveColi's: the move it allowed (the whole move for an object it skips)
    unsigned char pad_140[0x78];
    float m_shapeParms[2];  // 0x1B8, setShapeParms (the constructor's 1 and 2)
    unsigned char pad_1c0[4];
    float m_floor;  // 0x1C4, setFloor
    unsigned char pad_1c8[0x25];
    bool m_accuracy;  // 0x1ED, setAccuracy
    unsigned char pad_1ee[0x12];
};
}  // namespace idcoli

#endif
