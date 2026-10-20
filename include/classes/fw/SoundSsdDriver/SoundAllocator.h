#ifndef CLASSES_FW_SOUNDSSDDRIVER_SOUNDALLOCATOR_H
#define CLASSES_FW_SOUNDSSDDRIVER_SOUNDALLOCATOR_H

#include "classes/fw/SoundSsdDriver.h"

namespace fw {
// table 0x7100B430D8
class SoundSsdDriver::SoundAllocator {
public:
    virtual ~SoundAllocator();  // slot 0
    virtual void AllocInstance(unsigned long);  // slot 2
    virtual void FreeInstance(void*);  // slot 3
    virtual void AllocBuffer(unsigned long, unsigned long);  // slot 4
    virtual void FreeBuffer(void*);  // slot 5
    virtual void AllocStream(unsigned long, unsigned long);  // slot 6
    virtual void FreeStream(void*);  // slot 7
};
}  // namespace fw

#endif
