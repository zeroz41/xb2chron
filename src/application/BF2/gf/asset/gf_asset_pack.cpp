#include "gf/AssetPackInfo.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetPack.h"
#include "gf/GfSlotMapping.h"
#include "gf/AssetPackInfo.h"
#include "classes/gf/GfAssetPack.h"
#include "classes/gf/GfAssetPack.h"
#include "gf/AssetPackInfo.h"
#include "gf/GfSlotMapping.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfFileSizePool.h"
#include "gf/GfAssetUtil.h"
#include "gf/GfUtil.h"
#include "mm/mtl/Hash.h"

namespace gf {

GfAssetName::GfAssetName(const char* path) {
    set(path);
}

void GfAssetName::set(const char* path) {
    m_name.clear();
    m_dir.clear();
    if (path != nullptr) {
        const char* name = util::getFilePtrFromPath(path);
        int dirLen = name - path;
        m_name = name;
        if (dirLen > 0) {
            mm::mtl::FixStr<128> full(path);
            m_dir = full.substr(0, dirLen).m_str;
        }
    }
}

GfAssetResource* GfAssetPack::getResource(GfFileIdx file) const {
    for (const Resource& resource : m_resources) {
        if (resource.m_fileIdx == file) {
            return resource.m_resource;
        }
    }
    for (unsigned int map : m_files.m_fileMap) {
        if ((map & 0xFFFF) == static_cast<unsigned int>(file)) {
            for (const Resource& resource : m_resources) {
                if (resource.m_fileIdx == (map >> 16)) {
                    return resource.m_resource;
                }
            }
            return nullptr;
        }
    }
    return nullptr;
}

GfAssetType GfAssetPack::getAssetType() const {
    return m_files.m_type;
}

void GfAssetPack::dispAssetLogForDebug() {}

AssetPackInfo::~AssetPackInfo() {
    for (GfAssetPack*& slot : m_packs) {
        GfAssetPack* pack = slot;
        --pack->m_useCount;
        slot = nullptr;
        GfAssetManager::callEventAssetPack(pack);
        if (pack != nullptr) {
            pack->release();
        }
    }
}

bool AssetPackInfo::getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE*, 88>& handles) const {
    for (GfAssetPack* pack : m_packs) {
        GF_SLOT_HANDLE* handle = pack->m_slotHandle;
        if (handle != reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
            handles.push_back(handle);
        }
    }
    return !handles.empty();
}

void AssetPackInfo::releaseEmptySlot() {
    for (GfAssetPack** it = m_packs.begin(); it != m_packs.end(); ++it) {
        (*it)->releaseEmptySlot();
    }
}

void AssetPackInfo::fn_71001B2418() {
    m_reload = false;
    for (GfAssetPack* pack : m_packs) {
        (void)pack;
    }
}

void AssetPackInfo::fn_71001B2904() {
    for (GfAssetPack** it = m_packs.begin(); it != m_packs.end(); ++it) {
        GfAssetPack* pack = *it;
        int users = pack->m_useCount;
        if (pack->m_RefCount - users == 1) {
            if (pack->m_refCacheCount < 99) {
                pack->m_refCacheCount++;
            }
        } else if (pack->m_refCacheCount != 0) {
            pack->m_refCacheCount = 0;
        }
    }
}

bool AssetPackInfo::fn_71001B29DC(const GfAssetPack* pack) const {
    if (pack == nullptr) {
        return false;
    }
    for (GfAssetPack* const* it = m_packs.begin(); it != m_packs.end(); ++it) {
        if (*it == pack) {
            return true;
        }
    }
    return false;
}

bool AssetPackInfo::fn_71001B3040() const {
    for (GfAssetPack* pack : m_packs) {
        if (!pack->isPreSizeSizeValid()) {
            return false;
        }
    }
    return true;
}

bool AssetPackInfo::isFullResource() const {
    for (GfAssetPack* pack : m_packs) {
        if (pack->m_full) {
            return true;
        }
    }
    return false;
}

void AssetPackInfo::lockEnterRersource() {
    for (GfAssetPack* pack : m_packs) {
        pack->m_resourceLocked = true;
        pack->m_enterLocked = true;
    }
}

bool GfAssetPack::isCached() const {
    if (GfAssetManager::getSlotMapping()->isRequest(this)) {
        return false;
    }
    if (m_useCount != 0) {
        return false;
    }
    return m_cacheCount > 3;
}

void AssetPackInfo::setExtendResource(unsigned int index, GfExtendResource* resource) {
    m_extendResources[index] = resource;
}

void AssetPackInfo::setDestroy() {
    if (m_destroy) {
        return;
    }
    m_destroy = true;
    GfAssetUtil::addDestroyObject(m_handle, true);
}

const mm::mtl::FixStr<64>* GfAssetPack::getAssetName() const {
    return &m_files.m_name;
}

void GfAssetPack::applyPreFileSize() {
    GfFileSizePool* pool = GfFileSizePool::sys();
    if (pool == nullptr) {
        return;
    }
    for (GfAssetFiles::AssetFile* file : m_files.m_files) {
        if (file->m_fileSize == -2) {
            pool->getFileSize(file->m_fileSize, file->m_sizeHandle);
        }
    }
}

bool GfAssetPack::isPreSizeSizeValid() const {
    for (GfAssetFiles::AssetFile* const* it = m_files.m_files.begin(); it != m_files.m_files.end(); ++it) {
        if ((*it)->m_fileSize == -2) {
            return false;
        }
    }
    return !m_files.m_files.empty();
}

void AssetPackInfo::setModelName(const char* name) {
    m_modelName = util::getFilePtrFromPath(name);
}

void AssetPackInfo::setMotionName(const char* name) {
    m_motionName = util::getFilePtrFromPath(name);
}

void AssetPackInfo::setupLoadStart() {
    m_loadState = 0;
}

GfAssetPack* GfAssetPack::create(const GfAssetFilesInfo& info) {
#line 1170
    return new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfAssetPack(info);
}

void GfAssetPack::updateCacheCount() {
    if (m_useCount == 0) {
        if (m_cacheCount < 99) {
            m_cacheCount++;
        }
        return;
    }
    if (m_cacheCount != 0) {
        m_cacheCount = 0;
    }
}

void GfAssetPack::setTimeout() {
    m_timeout = true;
}

AssetPackValue GfAssetPack::calcAssetPackValue(const char* name, GfAssetType type) {
    AssetPackValue value;
    value.m_type = type;
    value.m_hash = mm::mtl::hashStrCrc(name);
    return value;
}

GfAssetPack::~GfAssetPack() {
    destroySoundPack();
    releaseResource();
    releaseSlotHandle();
}

bool GfAssetPack::isExistSameAsset(const GfAssetPack& other) const {
    return m_files.isExistSameAsset(other.m_files);
}

void GfAssetFiles::setInitializeParam(const GfAssetFilesInfo& info) {
    m_type = info.m_type;
    if (info.m_name != nullptr) {
        m_name = info.m_name;
        m_nameHash = mm::mtl::hashStrCrc(info.m_name);
    } else {
        m_name = "";
        m_nameHash = 0;
    }
    for (AssetFile*& file : m_files) {
        if (file != nullptr) {
            delete file;
            file = nullptr;
        }
    }
    m_fileMap.clear();
    m_files.clear();
}

}  // namespace gf
