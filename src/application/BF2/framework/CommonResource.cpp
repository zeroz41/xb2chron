#include "classes/ml/FileResTh.h"
#include "classes/ml/DevFileTh.h"
#include "classes/fw/ResourceManager.h"
#include "classes/fw/ResourceObject.h"
#include "classes/fw/AssetData.h"
#include "classes/fw/AssetLoader.h"
#include "classes/fw/CommonResource.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/fw/Framework.h"
#include "classes/ml/Scn.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "ml/DevFileParamTh.h"
#include "mm/mtl/FixStr.h"
#include "mtl/MemManager.h"
#include "mm/mtl/Vector.h"

namespace fw {

void fn_71001996F0(bool flag) {
    ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<Framework>::get()->m_scn->m_renderDrSys, 0);
    acc.setRenderTexMode(flag);
}

CommonResource* CommonResource::search(mtl::ALLOC_HANDLE handle, const char* path) {
    return static_cast<CommonResource*>(mm::mtl::PtrSingleton<ResourceManager>::get()->searchResource(0, handle, path));
}

CommonResource* CommonResource::search(mm::mtl::IAllocator* allocator, const char* path) {
    return static_cast<CommonResource*>(
        mm::mtl::PtrSingleton<ResourceManager>::get()->searchResource(0, allocator, path));
}

CommonResource* CommonResource::request_detail(mtl::ALLOC_HANDLE handle, const char* path, int prio,
                                               bool delayRelease, bool block) {
    CommonResource* resource = search(handle, path);
    if (resource != nullptr) {
        resource->addRef();
        return resource;
    }
    resource = new (ResourceManager::getMemSYS(), nullptr, 0, 4, false)
        CommonResource(handle, static_cast<LOAD_PRIO>(prio), 0, 0);
    if (resource != nullptr) {
        resource->setPath(path);
        resource->addRef();
        if (delayRelease) {
            resource->m_isRender = true;
        } else {
            resource->m_isRender = ResourceManager::isDelayReleaseExtention(path);
        }
        if (resource->m_isRender) {
            resource->m_arg = 0x1000;
        }
        if (block) {
            resource->updateBlock();
        } else {
            resource->update();
        }
    }
    return resource;
}

// updateBlock (0x7100199A58) is not written yet: the closest attempt is ~99 words off. The control flow and calls are
// right; the original's frame is 0x20 bigger (one more callee-saved register: it keeps m_path's address in x20 and
// the FixStr's in x22) and its locals sit 0x18 higher (FixStr at sp+0x98, DevFileParamTh at sp+0x28, the VAL64 at
// sp+0x10), which no declaration order or VAL64 size tried here reproduces.

CommonResource* CommonResource::request_detail(mm::mtl::IAllocator* allocator, const char* path, int prio,
                                               bool delayRelease, bool block) {
    CommonResource* resource = search(allocator, path);
    if (resource != nullptr) {
        resource->addRef();
        return resource;
    }
    resource = new (ResourceManager::getMemSYS(), nullptr, 0, 4, false)
        CommonResource(allocator, static_cast<LOAD_PRIO>(prio), 0, 0);
    if (resource != nullptr) {
        resource->setPath(path);
        resource->addRef();
        if (delayRelease) {
            resource->m_isRender = true;
        } else {
            resource->m_isRender = ResourceManager::isDelayReleaseExtention(path);
        }
        if (resource->m_isRender) {
            resource->m_arg = 0x1000;
        }
        if (block) {
            resource->updateBlock();
        } else {
            resource->update();
        }
    }
    return resource;
}

CommonResource* CommonResource::request(mtl::ALLOC_HANDLE handle, const char* path, int prio, bool delayRelease) {
    return request_detail(handle, path, prio, delayRelease, false);
}

CommonResource* CommonResource::request(mm::mtl::IAllocator* allocator, const char* path, int prio,
                                        bool delayRelease) {
    return request_detail(allocator, path, prio, delayRelease, false);
}

CommonResource* CommonResource::blockRequest(mtl::ALLOC_HANDLE handle, const char* path, bool delayRelease) {
    return request_detail(handle, path, 10, delayRelease, true);
}

CommonResource::CommonResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO prio, unsigned int type, int arg)
    : ResourceObject(type, handle, prio, arg), m_state(0), m_isRender(false), m_loader(nullptr), m_asset(nullptr) {}

CommonResource::CommonResource(mm::mtl::IAllocator* allocator, LOAD_PRIO prio, unsigned int type, int arg)
    : ResourceObject(type, allocator, prio, arg), m_state(0), m_isRender(false), m_loader(nullptr),
      m_asset(nullptr) {}

CommonResource::~CommonResource() {
    if (m_loader != nullptr) {
        m_loader->Release();
        m_loader = nullptr;
    }
    if (m_asset != nullptr) {
        if (m_isRender) {
            mm::mtl::PtrSingleton<ResourceManager>::get()->removeSafeObject(m_asset);
        }
        if (m_asset != nullptr) {
            m_asset->release();
            m_asset = nullptr;
        }
    }
}

void CommonResource::update() {
    for (;;) {
        switch (m_state) {
        case 0:
            if (m_handle.m_handle != 0) {
                m_asset = AssetData::CreateFromCache(m_handle, m_path.m_str);
            } else if (m_allocator != nullptr) {
                m_asset = AssetData::CreateFromCache(m_allocator, m_path.m_str);
            }
            if (m_asset != nullptr) {
                if (m_isRender) {
                    mm::mtl::PtrSingleton<ResourceManager>::get()->addSafeObject(m_asset,
                                                                                  static_cast<eResourceType>(0));
                }
                m_state = 2;
            } else {
                mm::mtl::FixStr<256> path;
                ml::DevFileTh::normalizeDvdFileName(path, m_path.m_str);
                if (m_handle.m_handle != 0) {
                    m_loader = AssetLoader::Create(m_handle, path.m_str, m_prio, m_arg);
                } else if (m_allocator != nullptr) {
                    m_loader = AssetLoader::Create(m_allocator, path.m_str, m_prio, m_arg);
                }
                m_state++;
            }
            break;
        case 1:
            if (m_loader == nullptr) {
                m_state = 2;
                break;
            }
            if (m_loader->m_handle != nullptr) {
                return;
            }
            if (m_loader->m_size != -2) {
                if (m_loader->isExist()) {
                    m_loader->m_ownsData = false;
                    if (m_handle.m_handle != 0) {
                        m_asset = AssetData::AssignFromMemory(m_handle, m_loader->m_data, m_loader->m_size,
                                                              m_loader->m_name.m_str, m_loader->m_timeStamp);
                    } else if (m_allocator != nullptr) {
                        m_asset = AssetData::AssignFromMemory(m_allocator, m_loader->m_data, m_loader->m_size,
                                                              m_loader->m_name.m_str, m_loader->m_timeStamp);
                    }
                    if (m_isRender) {
                        mm::mtl::PtrSingleton<ResourceManager>::get()->addSafeObject(m_asset,
                                                                                      static_cast<eResourceType>(0));
                    }
                }
                if (m_loader == nullptr) {
                    break;
                }
            }
            m_loader->Release();
            m_loader = nullptr;
            break;
        case 2:
            return;
        }
    }
}

bool CommonResource::valid() const {
    return m_state == 2;
}

void* CommonResource::getAssetData() {
    if (m_asset != nullptr) {
        return m_asset->m_data;
    }
    return nullptr;
}

unsigned int CommonResource::getAssetSize() const {
    if (m_asset != nullptr) {
        return m_asset->m_size;
    }
    return 0;
}

const char* CommonResource::getAssetName() const {
    return m_asset != nullptr ? m_asset->m_name.m_str : nullptr;
}

}  // namespace fw

// Vector<CommonResource*>'s growth (0x7100199740): 3.0.1 keeps this unit's copy (fn_71003606A0 calls it); nothing
// left in the unit uses the vector, so it is instantiated here
template void mm::mtl::Vector<fw::CommonResource*>::expand(size_t capacity, size_t alignment);
