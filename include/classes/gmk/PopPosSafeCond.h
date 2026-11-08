#ifndef CLASSES_GMK_POPPOSSAFECOND_H
#define CLASSES_GMK_POPPOSSAFECOND_H

#include "mm/Vec3.h"

namespace gmk {
// no table: whether a pop position is safe for a summoned enemy (gf::GfRelSmnEnemy::getPopPos builds one on the
// stack and asks isMatch for each candidate). The field names are not the original's.
class PopPosSafeCond {
public:
    // what the constructor copies (getPopPos fills one on the stack); the defaults are the constructor's
    class CreateInfo {
    public:
        CreateInfo() : m_pos(mm::Vec3::zero), m_type(0), m_waterDepth(0.0f), m_snapLength(10.0f) {}
        mm::Vec3 m_pos;        // isMatch snaps it down to the ground
        unsigned char m_type;  // isMatch: 0 dry ground, 1 in water, 2 water shallower than m_waterDepth, 3 m_pos as
                               // it is; any other the zero vector
        float m_waterDepth;    // 0x14
        float m_snapLength;    // 0x18: how far isMatch tests down from m_pos
    };
    PopPosSafeCond(const CreateInfo* info);
    bool isMatch(mm::Vec3& pos) const;

    CreateInfo m_info;
    bool m_isValid;  // 0x20: set when the constructor was given a CreateInfo
};
}  // namespace gmk

#endif
