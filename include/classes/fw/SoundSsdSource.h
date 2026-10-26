#ifndef CLASSES_FW_SOUNDSSDSOURCE_H
#define CLASSES_FW_SOUNDSSDSOURCE_H

#include "classes/fw/SoundReferenceObject.h"
#include "mm/mtl/FixStr.h"
#include "classes/ssd/WaveSource.h"

namespace ssd { class SoundEntry; }
namespace fw { class SoundSsdBank; }

namespace fw {
// table 0x7100B42EA0
class SoundSsdSource : public ::fw::SoundReferenceObject {
public:
    virtual ~SoundSsdSource();  // slot 0

    // whether the wave loops (1.0.0's, out of line there)
    bool isLoop() const { return m_wave != nullptr && m_wave->format_.loop.loop; }
    // a 3D source (bit 1 of the flags; the name is not the original's)
    bool is3D() const { return m_is3D; }

    unsigned char pad_c[0x4];
    ssd::WaveSource* m_wave;  // 0x10: createWave and createStream make it
    // 0x18: the bank entry the source plays through and 0x20 the bank it belongs to (the destructor removes the
    // entry from the bank and the source from the bank's list; the names are not the original's)
    ssd::SoundEntry* m_entry;
    SoundSsdBank* m_bank;
    unsigned char pad_28[0x10c];
    // the name SoundPack::findSource looks sources up by: the wave constructor copies its setup's second name here
    // (the field's name is not the original's)
    mm::mtl::FixStr<256> m_label;
    unsigned char pad_238[0x8];
    unsigned char pad_240_0 : 1;
    unsigned char m_is3D : 1;  // 0x240 bit 1 (the name is not the original's)
};
}  // namespace fw

#endif
