#ifndef CLASSES_SSD_SOUNDACTOR_H
#define CLASSES_SSD_SOUNDACTOR_H

#include "classes/ssd/List.h"
#include "classes/ssd/Object.h"
#include "ssd/Debug.h"

namespace ssd { class SoundEntry; }
namespace ssd { class SoundHandle; }

namespace ssd {
// table 0x7100B81960. What sounds play from: Init connects it to the SystemCore (which links it into its actor
// list through the Node base at 0x18), Play starts a handle's sound on it, Quit disconnects it.
// The field names are not the original's.
class SoundActor : public Object, public List<SoundActor>::Node {
public:
    SoundActor();
    // SoundActor3D's constructor passes its own type (9) here; SoundActor() passes 8
    SoundActor(ObjectType::Id type)
        : Object(type), connected_(false), linked_(false), is3D_(false), pad_33(0), pad_34(0), pad_38(1.0f),
          volume_(1.0f), pad_40(0.0f) {}
    virtual ~SoundActor();  // slot 0
    virtual Result Init();  // slot 2: -15 when already connected
    virtual Result Quit();  // slot 3: -15 when not connected
    virtual Result Play(SoundHandle* handle, const SoundEntry* entry, float volume, float pitch);  // slot 4
    virtual Result Stop(float fadeTime);  // slot 5
    virtual Result Pause(bool pause, float fadeTime);  // slot 6
    virtual void UpdateGameFrame(float frameTime);  // slot 7

    void SetVolume(float volume, float fadeTime);
    void SetCategoryId(int id);

    bool connected_;  // Init sets it, Quit clears it
    bool linked_;  // SystemCore::ConnectActor sets it
    bool is3D_;  // SoundActor3D's constructor sets it
    unsigned char pad_33;
    unsigned char pad_34;
    float pad_38;  // the constructor sets 1
    float volume_;  // SetVolume
    float pad_40;
};
}  // namespace ssd

#endif
