#ifndef CLASSES_SSD_SOUNDACTOR3D_H
#define CLASSES_SSD_SOUNDACTOR3D_H

#include "classes/ssd/SoundActor.h"

namespace ssd { class SoundEntry; }
namespace ssd { class SoundHandle; }

namespace ssd {
// table 0x7100B819D0
class SoundActor3D : public ::ssd::SoundActor {
public:
    virtual ~SoundActor3D();  // slot 0
    virtual void Init();  // slot 2
    virtual void Quit();  // slot 3
    virtual void Play(ssd::SoundHandle*, ssd::SoundEntry const*, float, float);  // slot 4
    virtual void UpdateGameFrame(float);  // slot 7

    unsigned char pad_20[0x58];  // SoundActor's and SoundActor3D's fields, not recovered (fw::SoundSsdPlayer's start at 0x78)
};
}  // namespace ssd

#endif
