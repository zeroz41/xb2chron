#ifndef CLASSES_FW_COMMONRESOURCE_H
#define CLASSES_FW_COMMONRESOURCE_H

#include "classes/fw/ResourceObject.h"
#include "mtl/AllocHandle.h"

namespace mm { namespace mtl { class IAllocator; } }
namespace fw { class AssetData; }
namespace fw { class AssetLoader; }

namespace fw {
// table 0x7100B42980 (0xC8 bytes); its constructors construct a ResourceObject (counted: its destructor hands
// itself to ResourceManager::removeSafeObject as an mm::mtl::ReferenceObject, and GfAssetResource releases its one
// through the count at 8)
class CommonResource : public ::fw::ResourceObject {
public:
    // the parameter names are not the original's (type is ResourceObject's)
    CommonResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO prio, unsigned int type, int arg);
    CommonResource(mm::mtl::IAllocator* allocator, LOAD_PRIO prio, unsigned int type, int arg);
    virtual ~CommonResource();  // slot 0
    virtual void update();  // slot 2
    virtual bool valid() const;  // slot 3: whether it has loaded (GfAssetResource::isFinishLoad returns it)
    virtual const char* getAssetName() const;  // slot 4: the loaded asset's name, none before
    // the resource of a path, referenced: the loaded one ResourceManager finds, else a new one (type 0) that keeps
    // its asset safe when delayRelease is set or the path's extension asks for it, then loads (updateBlock: at
    // once, else update); the parameter names are not the original's
    static CommonResource* request_detail(mtl::ALLOC_HANDLE handle, const char* path, int prio, bool delayRelease,
                                          bool block);
    static CommonResource* request_detail(mm::mtl::IAllocator* allocator, const char* path, int prio,
                                          bool delayRelease, bool block);
    static CommonResource* request(mtl::ALLOC_HANDLE handle, const char* path, int prio, bool delayRelease);
    static CommonResource* request(mm::mtl::IAllocator* allocator, const char* path, int arg, bool flag);
    // request_detail at priority 10, loaded at once
    static CommonResource* blockRequest(mtl::ALLOC_HANDLE handle, const char* path, bool delayRelease);
    // reads the asset at once (the cached one, else the file)
    void updateBlock();
    // the loaded resource of a path, none (LocalizeResource::request adds a reference to it)
    static CommonResource* search(mtl::ALLOC_HANDLE handle, const char* path);
    static CommonResource* search(mm::mtl::IAllocator* allocator, const char* path);
    void* getAssetData();
    unsigned int getAssetSize() const;

    // the names are not the original's
    int m_state;  // 0: find or start reading the asset, 1: reading, 2: loaded (valid)
    // set by RenderResource's constructor, cleared by CommonResource's; while set ResourceManager keeps the asset
    // safe (addSafeObject; request_detail sets it from its flag or ResourceManager::isDelayReleaseExtention)
    bool m_isRender;
    unsigned char pad_b5[0x3];
    AssetLoader* m_loader;  // the asset being read
    AssetData* m_asset;  // the asset
};
}  // namespace fw

#endif
