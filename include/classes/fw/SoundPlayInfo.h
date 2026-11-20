#ifndef CLASSES_FW_SOUNDPLAYINFO_H
#define CLASSES_FW_SOUNDPLAYINFO_H

#include "mm/Vec3.h"

namespace fw { class SoundPack; enum SoundCategory : int; }

namespace fw {
// a class with no table: what ISoundDriver::playSeEx plays (SoundSsdDriver::playSeEx reads every field; the field
// names are not the original's)
class SoundPlayInfo {
public:
    SoundPack* pack;  // 0x00 (no sound without one)
    unsigned int id;  // 0x08 (the source's id in the pack)
    float volume;  // 0x0C
    SoundCategory category;  // 0x10
    bool hasPos;  // 0x14 (pos is set on the played handle when true)
    mm::Vec3 pos;  // 0x20
};
}  // namespace fw

#endif
