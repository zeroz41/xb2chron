#ifndef CLASSES_FW_ASSETDATA_H
#define CLASSES_FW_ASSETDATA_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"
#include "mtl/AllocHandle.h"
#include "classes/fw/AssetManager.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B40DC8; counted (fw::SoundResource hands it to ResourceManager::addSafeObject as an
// mm::mtl::ReferenceObject and releases it with reference_object.h's assertion)
class AssetData : public ::mm::mtl::ReferenceObject {
public:
    // inline (no symbol): AssignFromMemory and Clone build it in place and register it with the AssetManager, as the
    // destructor removes it
    AssetData() : m_allocator(nullptr), m_hash(0), m_size(0), m_data(nullptr), m_timeStamp(0) {
        AssetManager::sys()->addAsset(this);
    }
    virtual ~AssetData();  // slot 0
    // the cached asset of a path, none
    static AssetData* CreateFromCache(mtl::ALLOC_HANDLE handle, const char* path);
    static AssetData* CreateFromCache(mm::mtl::IAllocator* allocator, const char* path);
    // an asset over data already read (fw::SoundResource::update hands it an AssetLoader's data and name)
    static AssetData* AssignFromMemory(mtl::ALLOC_HANDLE handle, const void* data, unsigned int size, const char* name,
                                       unsigned long arg);
    static AssetData* AssignFromMemory(mm::mtl::IAllocator* allocator, const void* data, unsigned int size,
                                       const char* name, unsigned long arg);
    // a counted copy of the asset (its data copied into the handle's or allocator's memory)
    AssetData* Clone(mtl::ALLOC_HANDLE handle) const;
    AssetData* Clone(mm::mtl::IAllocator* allocator) const;

    // the names are not the original's
    mtl::ALLOC_HANDLE m_allocHandle;  // the memory its data is in (AssignFromMemory's handle; CreateFromCache compares it)
    mm::mtl::IAllocator* m_allocator;  // AssignFromMemory's
    unsigned int m_hash;  // AssetManager::getHash of the name
    unsigned int m_size;  // the data's size (AssignFromMemory's; a SoundPack's)
    void* m_data;  // the data (AssignFromMemory's; a SoundPack's)
    unsigned long m_timeStamp;  // AssignFromMemory's last parameter (a FileResTh's m_timeStamp)
    mm::mtl::FixStr<128> m_name;  // the asset's name (AssignFromMemory's; a SoundPack's)
};

// 1.0.0's table 0x71011777F0 (in AssetData.cpp's .data: two slots, its destructors); 3.0.1's linker dropped it.
// counted: fw::AssetManager keeps them beside its AssetData and releases them as reference_object.h does
class AssetCsvb : public ::mm::mtl::ReferenceObject {
public:
    virtual ~AssetCsvb();  // slot 0
};
}  // namespace fw

#endif
