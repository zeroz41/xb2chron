#include "classes/fw/ResourceManager.h"
#include "classes/fw/ResourceObject.h"
#include "classes/fw/SoundResource.h"
#include "classes/fw/AssetData.h"
#include "classes/ml/BaseObjectM.h"
#include "classes/ml/FileResTh.h"
#include "classes/fw/AssetLoader.h"
#include "classes/fw/SoundPack.h"
#include "classes/fw/ScriptInfo.h"
#include "classes/fw/ScriptManager.h"
#include "classes/ml/DevFileTh.h"
#include "ml/DevFileParamTh.h"
#include "ml/EventFileTh.h"
#include "ml/PathUtil.h"
#include "vm/yvm2.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mtl/MemManager.h"
#include <string.h>

namespace fw {

SoundResource* SoundResource::request(mm::mtl::IAllocator* allocator, const char* path, const SetupInfo& info,
                                      LOAD_PRIO prio) {
    SoundResource* resource = static_cast<SoundResource*>(
        mm::mtl::PtrSingleton<ResourceManager>::get()->searchResource(5, allocator, path));
    if (resource != nullptr) {
        resource->addRef();
        return resource;
    }
    resource = new (ResourceManager::getMemSYS(), nullptr, 0, 4, false) SoundResource(allocator, prio);
    if (resource != nullptr) {
        resource->setPath(path);
        resource->m_info = info;
        resource->addRef();
        resource->update();
    }
    return resource;
}

SoundResource::~SoundResource() {
    if (m_loader != nullptr) {
        m_loader->Release();
        m_loader = nullptr;
    }
    if (m_pack != nullptr) {
        m_pack->release();
        m_pack = nullptr;
    }
    if (m_asset != nullptr) {
        mm::mtl::PtrSingleton<ResourceManager>::get()->removeSafeObject(m_asset);
        if (m_asset != nullptr) {
            m_asset->release();
            m_asset = nullptr;
        }
    }
}

void SoundResource::update() {
    for (;;) {
        switch (m_state) {
        case 0: {
            mm::mtl::FixStr<256> path;
            ml::DevFileTh::normalizeDvdFileName(path, m_path.m_str);
            m_asset = AssetData::CreateFromCache(m_allocator, path.m_str);
            if (m_asset != nullptr) {
                SoundPack::SetupInfo info;
                info.name = m_asset->m_name.m_str;
                info.category = static_cast<SoundCategory>(m_info.pad_0);
                info.priority = static_cast<SoundPriority>(m_info.pad_4);
                info.maxSound = m_info.pad_8;
                info.assetName = m_asset->m_name.m_str;
                info.data = m_asset->m_data;
                info.size = m_asset->m_size;
                m_pack = SoundPack::createFromStream(m_allocator, info);
                mm::mtl::PtrSingleton<ResourceManager>::get()->addSafeObject(m_asset, static_cast<eResourceType>(5));
                m_state = 2;
            } else {
                m_loader = AssetLoader::Create(m_allocator, path.m_str, m_prio, m_arg);
                m_state++;
            }
            break;
        }
        case 1:
            if (m_loader == nullptr) {
                m_state = 2;
                break;
            }
            if (m_loader->m_handle != nullptr) {
                return;
            }
            if (m_loader->m_size == -2) {
                // no file
                m_loader->Release();
                m_loader = nullptr;
                break;
            }
            if (m_loader->isExist()) {
                m_loader->m_ownsData = false;
                m_asset = AssetData::AssignFromMemory(m_allocator, m_loader->m_data, m_loader->m_size,
                                                      m_loader->m_name.m_str, 0);
                SoundPack::SetupInfo info;
                info.name = m_asset->m_name.m_str;
                info.category = static_cast<SoundCategory>(m_info.pad_0);
                info.priority = static_cast<SoundPriority>(m_info.pad_4);
                info.maxSound = m_info.pad_8;
                info.assetName = m_asset->m_name.m_str;
                info.data = m_asset->m_data;
                info.size = m_asset->m_size;
                m_pack = SoundPack::createFromStream(m_allocator, info);
                mm::mtl::PtrSingleton<ResourceManager>::get()->addSafeObject(m_asset, static_cast<eResourceType>(5));
            }
            if (m_loader != nullptr) {
                m_loader->Release();
                m_loader = nullptr;
            }
            break;
        case 2:
            return;
        }
    }
}

bool SoundResource::valid() const {
    return m_state == 2;
}

SoundPack* SoundResource::getSoundPack() {
    return m_pack;
}

ScriptInfo::ScriptInfo()
    : m_buffer(nullptr), m_size(0), m_id(-1), m_handle(nullptr), m_state(0), m_flags(0), m_allocator(nullptr),
      m_manager(nullptr) {}

ScriptInfo::~ScriptInfo() {
    if ((m_flags & FLAG_LINKED) && m_buffer != nullptr) {
        m_flags &= ~FLAG_LINKED;
        vmUnlink(m_buffer);
    } else if (m_handle != nullptr) {
        ml::DevFileTh::cancel(m_handle, false);
        m_handle = nullptr;
    }
    m_path.clear();
    m_fileName.clear();
    // the handle, state and flags zeroed as one 16-byte block (the original's destructor stores them with one stp
    // through the handle's address)
    memset(&m_handle, 0, 0x10);
}

// destroy (0x710019CCB0) is not written yet: the same steps as the destructor above, but the original zeroes the
// handle and the state/flags word with two stores where this text gives one 16-byte block (19 words apart)
// void ScriptInfo::destroy() {
//     if ((m_flags & FLAG_LINKED) && m_buffer != nullptr) {
//         m_flags &= ~FLAG_LINKED;
//         vmUnlink(m_buffer);
//     } else if (m_handle != nullptr) {
//         ml::DevFileTh::cancel(m_handle, false);
//         m_handle = nullptr;
//     }
//     m_path.clear();
//     m_fileName.clear();
//     // the handle, state and flags zeroed as one 16-byte block (the original's destructor stores them with one stp
//     // through the handle's address)
//     memset(&m_handle, 0, 0x10);
// }

void ScriptInfo::initialize(ScriptManager* manager, int id, void* buffer, unsigned int size) {
    m_path.clear();
    m_fileName.clear();
    m_handle = nullptr;
    m_state = 0;
    m_flags = 0;
    m_buffer = buffer;
    m_size = size;
    m_manager = manager;
    m_id = id;
}

// load (0x710019CDC4) is not written yet: as below it is 82 words off, all around the inlined DevFileParamTh
// (its constructor's stores merge differently: the original pairs 0x8/0x10 and keeps the four bools at 0x6C in one
// word store) and the zeroing after destroy; the read itself and the name copies are right.
// void ScriptInfo::load(const mm::mtl::FixStr<256>& path, ml::FILE_PRIO prio) {
//     if (strcmp(path.m_str, m_path.m_str) == 0) {
//         if ((m_flags & FLAG_LINKED) && m_buffer != nullptr) {
//             m_flags &= ~FLAG_LINKED;
//             vmUnlink(m_buffer);
//         }
//         m_flags = (m_flags & ~(FLAG_LOADING | FLAG_LOADED | FLAG_STARTED | FLAG_LINKED | FLAG_LOAD_ERR)) | FLAG_LOADED;
//         m_state = 1;
//         return;
//     }
//     destroy();
//     m_flags = 0;
//     ml::DevFileParamTh param;
//     param.m_path = path.m_str;
//     param.m_buffer = m_buffer;
//     param.m_size = m_size;
//     param.m_listener = this;
//     param.m_prio = prio;
//     m_handle = ml::DevFileTh::readFile(param);
//     if (m_handle != nullptr) {
//         m_path = path;
//         const char* name = ml::PathUtil::getFilePtrFromPath(path.m_str);
//         if (name != nullptr) {
//             m_fileName = name;
//         } else {
//             m_fileName = path.m_str;
//         }
//         m_flags |= FLAG_LOADING;
//         m_state = 1;
//     }// }


void ScriptInfo::start() {
    if (m_flags & FLAG_STARTED) {
        return;
    }
    unsigned int flags = m_flags;
    m_flags = flags | FLAG_STARTED;
    if (flags & FLAG_LOADED) {
        execute();
    }
}

void ScriptInfo::execute() {
    if (m_buffer == nullptr) {
        return;
    }
    if (m_state == 1) {
        if ((m_flags & (FLAG_LOADED | FLAG_STARTED)) == (FLAG_LOADED | FLAG_STARTED)) {
            if (!(m_flags & FLAG_LINKED) && vmLink(m_buffer)) {
                vmStart(m_buffer);
                m_flags |= FLAG_LINKED | FLAG_ACTIVE;
                if (m_manager != nullptr) {
                    m_manager->notifyEvent(m_id, static_cast<ScriptEventParam::State>(2));
                }
            }
            m_state = 2;
        }
    } else if (m_state == 2) {
        if (vmThreadIsFinish(m_buffer)) {
            m_flags &= ~FLAG_ACTIVE;
            m_state = 3;
            if (m_manager != nullptr) {
                m_manager->notifyEvent(m_id, static_cast<ScriptEventParam::State>(3));
            }
        }
    }
}

bool ScriptInfo::isLoaded() const {
    return (m_flags & FLAG_LOADED) != 0;
}

bool ScriptInfo::isLoadErr() const {
    return (m_flags & FLAG_LOAD_ERR) != 0;
}

bool ScriptInfo::isFinish() const {
    return m_state == 3;
}

bool ScriptInfo::isActive() const {
    return (m_flags & FLAG_ACTIVE) != 0;
}

// OnFileEvent (0x710019D0E0) is one word off as written below: the original ORs the flags with the selected bit
// (orr w9, w9, w8), this ORs the bit with the flags (orr w9, w8, w9); the ternary, if/else, `m_flags = m_flags | x`
// and a local for the bit all keep it (zkit sweep found no rewrite).
// bool ScriptInfo::OnFileEvent(ml::EventFileTh* event) {
//     if (m_handle != event->m_handle) {
//         return false;
//     }
//     int result = event->m_result;
//     m_flags &= ~FLAG_LOADING;
//     if (event->m_kind == 2 && result != 0) {
//         m_flags |= FLAG_LOADED;
//     } else {
//         m_flags |= FLAG_LOAD_ERR;
//     }
//     m_handle = nullptr;
//     if (m_manager != nullptr) {
//         m_manager->notifyEvent(m_id, static_cast<ScriptEventParam::State>(isLoaded()));
//     }
//     return true;
// }

}  // namespace fw
