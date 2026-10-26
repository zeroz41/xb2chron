#ifndef CLASSES_SSD_DELEGATE_MULTICAST_H
#define CLASSES_SSD_DELEGATE_MULTICAST_H

#include "classes/ssd/List.h"
#include "ssd/Debug.h"

namespace ssd { namespace Delegate {
// one registered callback (Delegate::Object derives from it): MultiCast links it through its Node base.
// sizeof 0x18 (SoundHandle's delegates are given back 0x18 bytes apart)
class Handle : public List<Handle>::Node {
};

// the callbacks a SoundHandle notifies (VoiceHandle::FreeVoice calls ExecuteDelegateImpl), as a list of Handles
class MultiCast {
public:
    ~MultiCast() {
        Clear();
    }

    // unlinks every handle
    void Clear();
    Result AddDelegate(Handle* handle);
    Result RemoveDelegate(Handle* handle);

    List<Handle> handles_;  // the name is not the original's
};
}}  // namespace ssd::Delegate

#endif
