#ifndef CLASSES_FW_ASSETDATA_H
#define CLASSES_FW_ASSETDATA_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"
#include "mtl/AllocHandle.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B40DC8; counted (fw::SoundResource hands it to ResourceManager::addSafeObject as an
// mm::mtl::ReferenceObject and releases it with reference_object.h's assertion)
class AssetData : public ::mm::mtl::ReferenceObject {
public:
    virtual ~AssetData();  // slot 0
    // the cached asset of a path, none
    static AssetData* CreateFromCache(mtl::ALLOC_HANDLE handle, const char* path);
    static AssetData* CreateFromCache(mm::mtl::IAllocator* allocator, const char* path);
    // an asset over data already read (fw::SoundResource::update hands it an AssetLoader's data and name)
    static AssetData* AssignFromMemory(mtl::ALLOC_HANDLE handle, const void* data, unsigned int size, const char* name,
                                       unsigned long arg);
    static AssetData* AssignFromMemory(mm::mtl::IAllocator* allocator, const void* data, unsigned int size,
                                       const char* name, unsigned long arg);

    // the names are not the original's
    unsigned char pad_c[0x4];
    mm::mtl::IAllocator* m_allocator;  // AssignFromMemory's
    unsigned int m_hash;  // AssetManager::getHash of the name
    unsigned int m_size;  // the data's size (AssignFromMemory's; a SoundPack's)
    void* m_data;  // the data (AssignFromMemory's; a SoundPack's)
    unsigned char pad_28[0x8];
    mm::mtl::FixStr<128> m_name;  // the asset's name (AssignFromMemory's; a SoundPack's)
};
}  // namespace fw

#endif
