#include "classes/fw/AssetManager.h"
#include "classes/fw/AssetLoader.h"
#include "classes/fw/AssetData.h"
#include "classes/fw/AssetManager.h"
#include "classes/fw/AssetData.h"
#include "classes/fw/AssetLoader.h"
#include "classes/fw/Framework.h"
#include "classes/ml/DevFileTh.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Hash.h"
#include "string.h"

namespace fw {

mtl::ALLOC_HANDLE AssetManager::getMemSYS() {
    return Framework::getMemHandle();
}

unsigned int AssetManager::getHash(const char* name) {
    return mm::mtl::hashStrCrc(name);
}

AssetManager::AssetManager(mm::mtl::IAllocator* allocator, unsigned int count)
    : m_assets(allocator), m_csvbs(allocator), m_loaders(allocator) {
    m_assets.reserve(count, 8);
    m_csvbs.reserve(count, 8);
    m_loaders.reserve(count, 8);
}

AssetManager::~AssetManager() {
    while (m_assets.size() != 0) {
        if (m_assets[m_assets.size() - 1] != nullptr) {
            m_assets[m_assets.size() - 1]->release();
            m_assets[m_assets.size() - 1] = nullptr;
        }
    }
    m_assets.clear();
    while (m_csvbs.size() != 0) {
        if (m_csvbs[m_csvbs.size() - 1] != nullptr) {
            m_csvbs[m_csvbs.size() - 1]->release();
            m_csvbs[m_csvbs.size() - 1] = nullptr;
        }
    }
    m_csvbs.clear();
    while (m_loaders.size() != 0) {
        if (m_loaders[m_loaders.size() - 1] != nullptr) {
            m_loaders[m_loaders.size() - 1]->release();
            m_loaders[m_loaders.size() - 1] = nullptr;
        }
    }
    m_loaders.clear();
}

void AssetManager::addAsset(AssetData* asset) {
    m_assets.push_back(asset);
}

void AssetManager::removeAsset(AssetData* asset) {
    AssetData** it = m_assets.begin();
    AssetData** last = m_assets.end();
    while (it != last && *it != asset) {
        ++it;
    }
    if (it != m_assets.end()) {
        m_assets.erase(it);
    }
}

AssetData* AssetManager::searchAsset(const char* name, AssetData* after) {
    if (m_assets.size() == 0) {
        return nullptr;
    }
    mm::mtl::FixStr<256> path;
    ml::DevFileTh::normalizeDvdFileName(path, name);
    unsigned int hash = mm::mtl::hashStrCrc(path.m_str);
    AssetData** it = m_assets.begin();
    if (after != nullptr) {
        AssetData** first = m_assets.begin();
        AssetData** last = m_assets.end();
        while (first != last && *first != after) {
            ++first;
        }
        it = first;
        if (it != m_assets.end()) {
            ++it;
        }
    }
    for (; it != m_assets.end(); ++it) {
        AssetData* asset = *it;
        if (asset != nullptr && asset->m_hash == hash && strcmp(asset->m_name.m_str, path.m_str) == 0) {
            return asset;
        }
    }
    return nullptr;
}

void AssetManager::addLoader(AssetLoader* loader) {
    m_loaders.push_back(loader);
}

void AssetManager::removeLoader(AssetLoader* loader) {
    AssetLoader** it = m_loaders.begin();
    AssetLoader** last = m_loaders.end();
    while (it != last && *it != loader) {
        ++it;
    }
    if (it != m_loaders.end()) {
        m_loaders.erase(it);
    }
}

AssetLoader* AssetManager::searchLoader(mtl::ALLOC_HANDLE handle, const char* name) {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    for (unsigned int i = 0; i < m_loaders.size(); i++) {
        AssetLoader* loader = m_loaders[i];
        if (loader != nullptr && loader->m_allocHandle.m_handle == handle.m_handle && loader->m_hash == hash &&
            strcmp(loader->m_name.m_str, name) == 0) {
            return loader;
        }
    }
    return nullptr;
}

AssetLoader* AssetManager::searchLoader(mm::mtl::IAllocator* allocator, const char* name) {
    unsigned int hash = mm::mtl::hashStrCrc(name);
    for (unsigned int i = 0; i < m_loaders.size(); i++) {
        AssetLoader* loader = m_loaders[i];
        if (loader != nullptr && loader->m_allocator == allocator && loader->m_hash == hash &&
            strcmp(loader->m_name.m_str, name) == 0) {
            return loader;
        }
    }
    return nullptr;
}

const char* AssetManager::getName() const {
    return "AssetManager";
}

void AssetManager::update(fw::UpdateInfo const&) {}

}  // namespace fw
