#ifndef GF_SOUNDPARAM_H
#define GF_SOUNDPARAM_H

#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"

namespace gf {
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
    unsigned char pad_2c[0x38 - 0x2c];
    // 8 for a weather's sound, 5 for a map sound (the name is not the original's)
    unsigned char m_kind;
    unsigned char pad_39[0x40 - 0x39];
    mm::Vec3 m_pos;  // where it plays (GfFieldMapSe's)
    unsigned char pad_50[0x10];  // WeatherSnd::create's stack holds two in 0xC0 bytes
};
}  // namespace gf

#endif
