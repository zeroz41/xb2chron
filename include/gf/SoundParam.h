#ifndef GF_SOUNDPARAM_H
#define GF_SOUNDPARAM_H

#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"

namespace gf {
class GF_OBJ_HANDLE;
// what GfSound::playSe plays: a sound by id or by name (WeatherSnd::create, GfFieldMapSe::createSeObj build one on
// the stack; clear() is gf_sound's)
class SoundParam {
public:
    SoundParam() : m_id(0) { clear(); }
    void clear();
    // a sound by its name (inline: the name is not the original's)
    void setName(const char* name) {
        m_id = 0;
        m_name = name;
    }

    unsigned int m_id;  // a sound by id (GfFieldMapSe's), 0 when by name
    mm::mtl::FixStr<32> m_name;  // a sound by name
    float m_volume;  // clear() makes it 1 (GfFieldMapSe passes its getVolume)
    unsigned char pad_2c[0x30 - 0x2c];
    // the object it follows (1.0.0's setupTransformObj/setupTransformBone; clear() makes it -1; the name is not the
    // original's)
    GF_OBJ_HANDLE* m_obj;
    // 8 for a weather's sound, 5 for a map sound (the name is not the original's)
    unsigned char m_kind;
    // 1 global, 2 object, 3 bone (1.0.0's setupTransformGlobal/Obj/Bone; the name is not the original's)
    unsigned char m_transform;
    unsigned char pad_3a;  // clear() zeroes it
    unsigned char pad_3b[0x40 - 0x3b];
    mm::Vec3 m_pos;  // where it plays (GfFieldMapSe's)
    const char* m_bone;  // 1.0.0's setupTransformBone's bone name (the name is not the original's)
    unsigned char pad_58[0x8];  // WeatherSnd::create's stack holds two in 0xC0 bytes
};
}  // namespace gf

#endif
