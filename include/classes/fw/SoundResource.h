#ifndef CLASSES_FW_SOUNDRESOURCE_H
#define CLASSES_FW_SOUNDRESOURCE_H

#include "classes/fw/ResourceObject.h"

namespace mm { namespace mtl { class IAllocator; } }
namespace fw { class AssetData; }
namespace fw { class AssetLoader; }
namespace fw { class SoundPack; }

namespace fw {
// table 0x7100B42B48 (0xE0 bytes): a sound pack file as a resource (type 5): its asset from the cache or read, then
// the SoundPack made from it
class SoundResource : public ::fw::ResourceObject {
public:
    // how a sound resource loads (12 bytes: request copies it into the resource at 0xD0); update hands its fields to
    // SoundPack::SetupInfo's category, priority and maxSound; their names are not known yet
    struct SetupInfo {
        unsigned int pad_0;
        unsigned int pad_4;
        unsigned int pad_8;
    };

    // inline: 3.0.1 has no out-of-line copy (request holds its stores)
    SoundResource(mm::mtl::IAllocator* allocator, LOAD_PRIO prio)
        : ResourceObject(5, allocator, prio, 0x1000), m_state(0), m_loader(nullptr), m_asset(nullptr),
          m_pack(nullptr) {
        m_info.pad_0 = 3;
        m_info.pad_4 = 0;
        m_info.pad_8 = 0x80;
    }
    virtual ~SoundResource();  // slot 0
    virtual void update();  // slot 2
    virtual bool valid() const;  // slot 3
    // the resource of a path, referenced: the loaded one ResourceManager finds, else a new one
    static SoundResource* request(mm::mtl::IAllocator* allocator, const char* path, const SetupInfo& info,
                                  LOAD_PRIO prio);
    SoundPack* getSoundPack();

    // the names are not the original's
    int m_state;  // 0: find or read the asset, 1: reading, 2: loaded (valid)
    AssetLoader* m_loader;  // the asset being read
    AssetData* m_asset;  // the asset (ResourceManager keeps it safe)
    SoundPack* m_pack;  // made from the asset
    SetupInfo m_info;  // request's
};
}  // namespace fw

#endif
