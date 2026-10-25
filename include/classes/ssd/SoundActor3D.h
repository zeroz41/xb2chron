#ifndef CLASSES_SSD_SOUNDACTOR3D_H
#define CLASSES_SSD_SOUNDACTOR3D_H

#include "classes/ssd/SoundActor.h"
#include "ssd/Math.h"

namespace ssd { class SoundEntry; }
namespace ssd { class SoundHandle; }
namespace ssd { class SoundListener; }

namespace ssd {
// table 0x7100B819D0. A SoundActor with a position, a velocity and a listener. The field names are not the
// original's.
class SoundActor3D : public ::ssd::SoundActor {
public:
    SoundActor3D();
    virtual ~SoundActor3D();  // slot 0
    virtual Result Init();  // slot 2
    virtual Result Quit() { return SoundActor::Quit(); }  // slot 3
    virtual Result Play(SoundHandle* handle, const SoundEntry* entry, float volume, float pitch);  // slot 4
    virtual void UpdateGameFrame(float frameTime);  // slot 7
    void SetListener(const SoundListener* listener);
    void SetPosition(const Vec3& position);
    void SetVelocity(const Vec3& velocity);

    Vec3 position_;  // 0x44: SetPosition
    Vec3 velocity_;  // 0x50: SetVelocity, or UpdateGameFrame from the position's change
    Vec3 lastPosition_;  // 0x5C: the position UpdateGameFrame last saw
    bool pad_68;  // the constructor sets it
    bool positionSet_;  // SetPosition sets it, UpdateGameFrame clears it
    unsigned char pad_6a;
    bool velocitySet_;  // SetVelocity sets it, UpdateGameFrame clears it
    const SoundListener* listener_;  // 0x70: SetListener
};
}  // namespace ssd

#endif
