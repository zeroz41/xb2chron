#ifndef GF_SOUNDHANDLE_H
#define GF_SOUNDHANDLE_H

namespace gf {
// a playing sound, passed by value (8 bytes in a register; 4-aligned: GfMenuSoundManager keeps one in each 0xC-byte
// jingle)
class SoundHandle {
public:
    SoundHandle(unsigned int id);  // stores id, then 0xFFFF
    unsigned int m_id;  // the constructor's; the name is not the original's
    unsigned int pad_4;
};
}  // namespace gf

#endif
