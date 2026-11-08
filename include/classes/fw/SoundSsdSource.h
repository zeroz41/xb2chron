#ifndef CLASSES_FW_SOUNDSSDSOURCE_H
#define CLASSES_FW_SOUNDSSDSOURCE_H

#include "classes/fw/SoundReferenceObject.h"
#include "mm/mtl/FixStr.h"
#include "classes/ssd/WaveSource.h"
#include "classes/ssd/SoundParam.h"

namespace ssd { class SoundEntry; }
namespace fw { class SoundSsdBank; }
namespace fw { enum SoundCategory : int; }

namespace fw {
// table 0x7100B42EA0
class SoundSsdSource : public ::fw::SoundReferenceObject {
public:
    // what fw::SoundSsdBank::addStream hands createStream (the type's name is from the constructor's symbol; the
    // member names are not the original's)
    struct SetupInfo {
        ssd::SoundParam param;  // 0x00: copied into the bank entry
        unsigned int pad_94;
        SoundCategory category;  // 0x98
        int bankId;  // 0x9C: the bank the source joins (SoundSsdBank::m_id)
        const char* name;  // 0xA0: the stream's file
    };
    // what fw::SoundSsdBank::addWave hands createWave (the type's name is from the constructor's symbol; the member
    // names are not the original's)
    struct SetupWaveInfo {
        ssd::SoundParam param;  // 0x00: copied into the bank entry
        unsigned int pad_94;
        SoundCategory category;  // 0x98
        int bankId;  // 0x9C
        const char* name;  // 0xA0: the source's name
        const char* label;  // 0xA8: the name SoundPack::findSource looks it up by
        void* data;  // 0xB0: the wave in memory
        unsigned int size;  // 0xB8
    };

    SoundSsdSource(const SetupInfo& info);
    SoundSsdSource(const SetupWaveInfo& info);
    virtual ~SoundSsdSource();  // slot 0
    static SoundSsdSource* createStream(const SetupInfo& info);
    static SoundSsdSource* createWave(const SetupWaveInfo& info);

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
    // 0x28: the setup's bank id, its name and the name's mm::mtl::hashStrCrc (the names are not the original's)
    int m_bankId;
    mm::mtl::FixStr<256> m_name;  // 0x2C
    unsigned int m_nameHash;  // 0x130
    // the name SoundPack::findSource looks sources up by: the wave constructor copies its setup's second name here
    // (the field's name is not the original's)
    mm::mtl::FixStr<256> m_label;
    unsigned int m_labelHash;  // 0x238
    // 0x23C: the entry's unique id (the SoundParam's word at 0x48; the name is not the original's)
    unsigned int m_uniqueId;
    unsigned int m_isStream : 1;  // 0x240 bit 0: createStream sets it (the name is not the original's)
    unsigned int m_is3D : 1;  // 0x240 bit 1: createWave sets it from the param's byte 0x69 (the name is not the original's)
    unsigned int pad_240_2 : 30;
    int pad_244;  // 6 at construction
};
}  // namespace fw

#endif
