#ifndef CLASSES_SSD_SOUNDENTRY_H
#define CLASSES_SSD_SOUNDENTRY_H

#include "classes/ssd/List.h"
#include "classes/ssd/Object.h"
#include "classes/ssd/SoundParam.h"

namespace ssd { class SoundBank; }
namespace ssd { class SoundGroup; }
namespace ssd { class WaveSource; }

namespace ssd {
// table 0x7100B81A60: a sound a bank holds (fw::SoundSsdSource::createWave/createStream make one, copy the
// sound's SoundParam into it, give it the WaveSource and add it to the bank, which links it through the Node
// base at 0x18). sizeof 0xE0 (operator new(0xE0), DeleteInstance's stride). The field names are not the original's.
class SoundEntry : public Object, public List<SoundEntry>::Node {
public:
    SoundEntry();
    virtual ~SoundEntry();  // slot 0

    // the bank's group whose id is the entry's group id, or null
    SoundGroup* GetSoundGroup() const;

    SoundParam param_;  // 0x30
    WaveSource* source_;  // 0xC8: createWave/createStream store the source
    SoundBank* bank_;  // 0xD0: SoundBank::AddSoundEntry stores itself
    bool deleteOnRemove_;  // 0xD8: SoundBank::RemoveSoundEntry gives the entry back to SoundMemory::allocator_
};
}  // namespace ssd

#endif
