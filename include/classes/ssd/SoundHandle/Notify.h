#ifndef CLASSES_SSD_SOUNDHANDLE_NOTIFY_H
#define CLASSES_SSD_SOUNDHANDLE_NOTIFY_H

#include "classes/ssd/SoundHandle.h"

namespace ssd {
// a class with no table: what is declared inside it
class SoundHandle::Notify {
public:
    // what a handle's delegates are told (fw::SoundSsdDriver::SoundHandleDelegate acts on 1, the handle's voice
    // being freed); the enumerators' names are unknown
    enum Type : int;
};
}  // namespace ssd

#endif
