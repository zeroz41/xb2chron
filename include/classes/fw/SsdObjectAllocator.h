#ifndef CLASSES_FW_SSDOBJECTALLOCATOR_H
#define CLASSES_FW_SSDOBJECTALLOCATOR_H

#include "mtl/MemManager.h"

namespace fw {
// destroys the sound driver's objects (1.0.0/3.0.1 deleteObject<SoundPoolMemory> and <SoundSsdPlayer>, out of line
// in sound_ssd_drv.cpp): the destructor, then MemManager::deallocate
class SsdObjectAllocator {
public:
    template <typename T>
    static void deleteObject(T* object) {
        object->~T();
        mtl::MemManager::deallocate(object, 0, false);
    }
};
}  // namespace fw

#endif
