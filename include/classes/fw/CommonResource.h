#ifndef CLASSES_FW_COMMONRESOURCE_H
#define CLASSES_FW_COMMONRESOURCE_H

#include "classes/fw/ResourceObject.h"
#include "mtl/AllocHandle.h"

namespace mm { namespace mtl { class IAllocator; } }

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
    static CommonResource* request(mm::mtl::IAllocator* allocator, const char* path, int arg, bool flag);
    // the loaded resource of a path, none (LocalizeResource::request adds a reference to it)
    static CommonResource* search(mtl::ALLOC_HANDLE handle, const char* path);
    static CommonResource* search(mm::mtl::IAllocator* allocator, const char* path);
    void* getAssetData();
    unsigned int getAssetSize() const;

    unsigned char pad_b0[0x4];
    // set by RenderResource's constructor, cleared by CommonResource's (the name is not the original's)
    bool m_isRender;
    unsigned char pad_b5[0x13];
};
}  // namespace fw

#endif
