#ifndef GF_SOUNDHANDLE_H
#define GF_SOUNDHANDLE_H

namespace gf {
// a playing sound, passed by value (8 bytes in a register; 4-aligned: GfMenuSoundManager keeps one in each 0xC-byte
// jingle)
class SoundHandle {
public:
    SoundHandle();  // no sound: 0, then 0xFFFF
    SoundHandle(unsigned int id);  // stores id, then 0xFFFF
    bool isValid() const;  // whether it holds a sound (a nonzero id)
    void clear();  // back to no sound
    unsigned int m_id;  // the constructor's; the name is not the original's
    // its GfSound::SeParam's index in the low 16 bits, 0xFFFF for none (GfSound::setCategory reads 16 bits; the
    // name is not the original's)
    unsigned int m_seIndex;
};
}  // namespace gf

#endif
