#ifndef CLASSES_FW_RENDERRESOURCE_H
#define CLASSES_FW_RENDERRESOURCE_H

#include "classes/fw/CommonResource.h"
#include "classes/fw/ResourceManager.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw {
// table 0x7100B42A48
class RenderResource : public ::fw::CommonResource {
public:
    // inline: 3.0.1 has no out-of-line copy (the requests hold its stores); type 1, 0x1000
    RenderResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO prio) : CommonResource(handle, prio, 1, 0x1000) {
        m_isRender = true;
    }
    RenderResource(mm::mtl::IAllocator* allocator, LOAD_PRIO prio) : CommonResource(allocator, prio, 1, 0x1000) {
        m_isRender = true;
    }
    virtual ~RenderResource();  // slot 0
    // the loaded render resource of a path, none (1.0.0's; inline: 3.0.1 has no out-of-line copy)
    static RenderResource* search(mtl::ALLOC_HANDLE handle, const char* path) {
        return static_cast<RenderResource*>(mm::mtl::PtrSingleton<ResourceManager>::get()->searchResource(1, handle, path));
    }
    static RenderResource* search(mm::mtl::IAllocator* allocator, const char* path) {
        return static_cast<RenderResource*>(
            mm::mtl::PtrSingleton<ResourceManager>::get()->searchResource(1, allocator, path));
    }
    // the resource of a path, referenced: the loaded one ResourceManager finds, else a new one
    static RenderResource* request(mtl::ALLOC_HANDLE handle, const char* path, int prio);
    static RenderResource* request(mm::mtl::IAllocator* allocator, const char* path, int prio);
};
}  // namespace fw

#endif
