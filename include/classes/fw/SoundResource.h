#ifndef CLASSES_FW_SOUNDRESOURCE_H
#define CLASSES_FW_SOUNDRESOURCE_H

#include "classes/fw/ResourceObject.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B42B48
class SoundResource : public ::fw::ResourceObject {
public:
    // how a sound resource loads (12 bytes: request copies it into the resource at 0xD0); its fields' meanings are
    // not known yet
    struct SetupInfo {
        unsigned int pad_0;
        unsigned int pad_4;
        unsigned int pad_8;
    };

    virtual ~SoundResource();  // slot 0
    virtual void update();  // slot 2
    virtual bool valid() const;  // slot 3
    // the resource of a path, referenced: the loaded one ResourceManager finds, else a new one
    static SoundResource* request(mm::mtl::IAllocator* allocator, const char* path, const SetupInfo& info,
                                  LOAD_PRIO prio);
};
}  // namespace fw

#endif
