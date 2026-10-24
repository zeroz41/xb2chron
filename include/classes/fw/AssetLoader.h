#ifndef CLASSES_FW_ASSETLOADER_H
#define CLASSES_FW_ASSETLOADER_H

#include "classes/ml/FileResTh.h"
#include "mtl/AllocHandle.h"

namespace mm { namespace mtl { class IAllocator; } }

namespace fw {
// table 0x7100B40DE8
class AssetLoader : public ::ml::FileResTh {
public:
    virtual ~AssetLoader();  // slot 0
    // a loader reading path (fw::SoundResource::update passes its allocator, path, load priority and the int at 0x24
    // of its ResourceObject; the parameter names are not the original's)
    static AssetLoader* Create(mtl::ALLOC_HANDLE handle, const char* path, int prio, int arg);
    static AssetLoader* Create(mm::mtl::IAllocator* allocator, const char* path, int prio, int arg);

    // the names are not the original's (AssetManager::searchLoader compares them with what it is asked for)
    unsigned char pad_f1[0xF];
    mtl::ALLOC_HANDLE m_allocHandle;  // the memory it reads into (Create's handle)
    unsigned char pad_104[0x4];
    mm::mtl::IAllocator* m_allocator;  // the same, as an allocator
    unsigned int m_hash;  // AssetManager::getHash of the path
};
}  // namespace fw

#endif
