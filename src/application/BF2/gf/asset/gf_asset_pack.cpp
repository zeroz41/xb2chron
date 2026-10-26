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

GfAssetType GfAssetPack::getAssetType() const {
    return m_files.m_type;
}

void GfAssetPack::dispAssetLogForDebug() {}

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

}  // namespace gf
