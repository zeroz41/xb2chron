#ifndef CLASSES_SSD_DELEGATE_MULTICAST_H
#define CLASSES_SSD_DELEGATE_MULTICAST_H

#include "classes/ssd/List.h"
#include "ssd/Debug.h"

namespace ssd { namespace Delegate {
// one registered callback (Delegate::Object derives from it): MultiCast links it through its Node base.
// sizeof 0x18 (SoundHandle's delegates are given back 0x18 bytes apart)
class Handle : public List<Handle>::Node {
public:
    // calls the callback with a notification's two arguments (MultiCast's ExecuteDelegateImpl)
    virtual Result ExecuteDelegate(unsigned long long, unsigned long long) = 0;  // slot 2
    // the same callback as other's (MultiCast::FindDelegate's test)
    virtual bool operator==(const Handle* other) const = 0;  // slot 3
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
    // the registered handle equal to handle (Handle::operator==), null for none
    Handle* FindDelegate(const Handle* handle);
    // calls every registered handle with the notification's two words, through SystemCore's delegates_ array
    // (a snapshot taken under the audio lock)
    void ExecuteDelegateImpl(unsigned long long, unsigned long long) const;

    List<Handle> handles_;  // the name is not the original's
};
}}  // namespace ssd::Delegate

#endif
