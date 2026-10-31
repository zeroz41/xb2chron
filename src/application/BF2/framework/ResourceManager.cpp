#include "mm/mtl/FixStr.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/Framework.h"
#include "classes/fw/ResourceManager.h"
#include "classes/fw/ResourceObject.h"
#include "ml/PathUtil.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Hash.h"
#include "mtl/MemManager.h"
#include <string.h>

namespace fw {

mtl::ALLOC_HANDLE ResourceManager::m_hMemoryTemp;

mtl::ALLOC_HANDLE ResourceManager::getMemSYS() {
    return Framework::getMemHandle();
}

void ResourceManager::setMemTMP(mtl::ALLOC_HANDLE handle) {
    m_hMemoryTemp = handle;
}

unsigned int ResourceManager::getHash(const char* path) {
    return mm::mtl::hashStrCrc(path);
}

ResourceManager::ResourceManager(mm::mtl::IAllocator* allocator, unsigned int count)
    : m_allocator(allocator), m_loadCount(0), pad_524(), m_finalizeState(0), m_isFinalizeApplet(false) {
    for (int i = 0; i < 32; i++) {
        m_resources[i].setAllocator(allocator);
        m_resources[i].reserve(count);
    }
}

ResourceManager::~ResourceManager() {
    for (SafeObject *it = m_safeObjects.begin(), *last = m_safeObjects.end(); it != last; ++it) {
        if (it->m_object != nullptr) {
            it->m_object->release();
            it->m_object = nullptr;
        }
    }
    for (SafeObject *it = m_releaseList.begin(), *last = m_releaseList.end(); it != last; ++it) {
        if (it->m_object != nullptr) {
            it->m_object->release();
            it->m_object = nullptr;
        }
    }
    m_safeObjects.clear();
    m_releaseList.clear();
    for (int i = 0; i < 32; i++) {
        // a resource's release takes it out of the list (its destructor's removeResource)
        while (m_resources[i].size() != 0) {
            ResourceObject* resource = m_resources[i][m_resources[i].size() - 1];
            if (resource != nullptr) {
                resource->release();
            }
        }
        m_resources[i].clear();
    }
}

void ResourceManager::update(const UpdateInfo& info) {
    updateSafeReleaseList(false);
    m_loadCount = 0;
    for (int type = 0; type < 32; type++) {
        for (unsigned int i = 0; i < m_resources[type].size(); i++) {
            if (m_resources[type][i] != nullptr) {
                m_resources[type][i]->update();
            }
        }
    }
}

void ResourceManager::updateSafeReleaseList(bool force) {
    SafeObject* it = m_releaseList.begin();
    while (it != m_releaseList.end()) {
        --it->m_count;
        if (force || it->m_count <= 0) {
            if (it->m_object != nullptr) {
                it->m_object->release();
                it->m_object = nullptr;
            }
            it = m_releaseList.erase(it);
        } else {
            ++it;
        }
    }
}

void ResourceManager::addResource(ResourceObject* resource) {
    mm::mtl::Vector<ResourceObject*>& list = m_resources[resource->m_type];
    ResourceObject** it = list.begin();
    while (it != list.end() && resource->m_prio >= (*it)->m_prio) {
        ++it;
    }
    if (it == list.end()) {
        list.push_back(resource);
    } else {
        list.insert(it, resource);
    }
}

void ResourceManager::removeResource(ResourceObject* resource) {
    mm::mtl::Vector<ResourceObject*>& list = m_resources[resource->m_type];
    ResourceObject** it = list.begin();
    ResourceObject** last = list.end();
    while (it != last && *it != resource) {
        ++it;
    }
    if (it != list.end()) {
        list.erase(it);
    }
}

ResourceObject* ResourceManager::searchResource(unsigned int type, mtl::ALLOC_HANDLE handle, const char* path) {
    unsigned int hash = mm::mtl::hashStrCrc(path);
    for (unsigned int i = 0; i < m_resources[type].size(); i++) {
        if (m_resources[type][i] != nullptr && m_resources[type][i]->m_handle.m_handle == handle.m_handle &&
            m_resources[type][i]->m_hash == hash && strcmp(m_resources[type][i]->m_path.m_str, path) == 0) {
            return m_resources[type][i];
        }
    }
    return nullptr;
}

ResourceObject* ResourceManager::searchResource(unsigned int type, mm::mtl::IAllocator* allocator, const char* path) {
    unsigned int hash = mm::mtl::hashStrCrc(path);
    for (unsigned int i = 0; i < m_resources[type].size(); i++) {
        if (m_resources[type][i] != nullptr && m_resources[type][i]->m_allocator == allocator &&
            m_resources[type][i]->m_hash == hash && strcmp(m_resources[type][i]->m_path.m_str, path) == 0) {
            return m_resources[type][i];
        }
    }
    return nullptr;
}

bool ResourceManager::isDelayReleaseExtention(const char* path) {
    ResourceManager* manager = mm::mtl::PtrSingleton<ResourceManager>::get();
    if (manager != nullptr) {
        const char* ext = ml::PathUtil::getFileExtPtr(path);
        if (ext != nullptr) {
            mm::mtl::FixStr<16> extention(ext);
            for (const char **it = manager->m_delayReleaseExtentions.begin(),
                            **last = manager->m_delayReleaseExtentions.end();
                 it != last; ++it) {
                if (extention.find(*it) != -1) {
                    return true;
                }
            }
        }
    }
    return false;
}

void ResourceManager::addSafeObject(mm::mtl::ReferenceObject* object, eResourceType type) {
    SafeObject* it = m_safeObjects.begin();
    for (; it != m_safeObjects.end(); ++it) {
        if (it->m_object == object) {
            it->m_count++;
            break;
        }
    }
    if (it == m_safeObjects.end()) {
        object->addRef();
        SafeObject entry;
        entry.m_object = object;
        entry.m_count = 1;
        entry.m_type = type;
        m_safeObjects.push_back(entry);
    }
}

// removeSafeObject (0x710019C1AC) is not written yet: the closest attempt has the right steps, but the original's search keeps a
// byte offset tested at the loop's top (returning when the list runs out), then tests the entry against the old end
// again; neither a pointer walk with break, an inline find helper nor this index walk gives that loop.

bool ResourceManager::isLoaded() {
    for (int type = 0; type < 32; type++) {
        for (unsigned int i = 0; i < m_resources[type].size(); i++) {
            if (m_resources[type][i] != nullptr && !m_resources[type][i]->valid()) {
                return false;
            }
        }
    }
    return true;
}

void ResourceManager::enterFinalizeApplet() {
    m_isFinalizeApplet = true;
    m_finalizeState = 2;
}

}  // namespace fw
