#include "gf/AssetPackInfo.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetPack.h"
#include "classes/gf/GfAssetResource.h"
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
#include "fw/Reflection.h"

#include <string.h>

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
    int common = m_files.getCommonResource(file);
    if (common == -1) {
        return nullptr;
    }
    for (const Resource& resource : m_resources) {
        if (resource.m_fileIdx == common) {
            return resource.m_resource;
        }
    }
    return nullptr;
}

bool GfAssetPack::isLoaded(mm::mtl::FixStr<128>*) const {
    if (m_files.m_files.empty()) {
        return false;
    }
    for (const GfAssetFiles::AssetFile* file : m_files.m_files) {
        GfAssetResource* resource = getResource(file->m_idx);
        if (resource != nullptr) {
            if (!resource->isFinishLoad()) {
                return false;
            }
            if (resource->getAssetSize() == 0) {
                continue;
            }
        } else {
            if (m_files.isNoFile(file->m_idx)) {
                continue;
            }
            return false;
        }
    }
    return true;
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

GfAssetPack* AssetPackInfo::getAssetPack(GfFileIdx file) const {
    for (GfAssetPack* pack : m_packs) {
        if (pack->m_files.isExistFile(file)) {
            return pack;
        }
    }
    return nullptr;
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

bool AssetPackInfo::getFileNameByExt(mm::mtl::FixedVector<const char*, 128>& names, const char* name) {
    for (GfAssetPack* pack : m_packs) {
        for (const GfAssetPack::Resource& resource : pack->m_resources) {
            if (resource.m_resource != nullptr && strstr(resource.m_resource->getAssetName(), name) != nullptr) {
                names.push_back(resource.m_resource->getAssetName());
            }
        }
    }
    return !names.empty();
}

GfAssetResource* AssetPackInfo::getResource(GfFileIdx file) {
    for (GfAssetPack** it = m_packs.begin(); it != m_packs.end(); ++it) {
        GfAssetPack* pack = *it;
        for (const GfAssetPack::Resource& resource : pack->m_resources) {
            if (resource.m_fileIdx == file) {
                if (resource.m_resource != nullptr) {
                    return resource.m_resource;
                }
                break;
            }
        }
    }
    for (GfAssetPack** it = m_packs.begin(); it != m_packs.end(); ++it) {
        GfAssetPack* pack = *it;
        int common = pack->m_files.getCommonResource(file);
        if (common != -1) {
            for (const GfAssetPack::Resource& resource : pack->m_resources) {
                if (resource.m_fileIdx == common) {
                    if (resource.m_resource != nullptr) {
                        return resource.m_resource;
                    }
                    break;
                }
            }
        }
    }
    return nullptr;
}

inline GfAssetResource* GfAssetPack::getResource(const char* name) const {
    for (const Resource& resource : m_resources) {
        if (resource.m_resource == nullptr) {
            continue;
        }
        if (strcmp(resource.m_resource->getAssetName(), name) == 0) {
            return resource.m_resource;
        }
    }
    return nullptr;
}

GfAssetResource* AssetPackInfo::getResource(const char* name) {
    for (GfAssetPack** it = m_packs.begin(); it != m_packs.end(); ++it) {
        if (GfAssetResource* resource = (*it)->getResource(name)) {
            return resource;
        }
    }
    return nullptr;
}

bool AssetPackInfo::isExist(GfFileIdx file) const {
    for (GfAssetPack* const* it = m_packs.begin(); it != m_packs.end(); ++it) {
        if (GfAssetResource* resource = (*it)->getResource(file)) {
            return resource->isValidData();
        }
    }
    return false;
}

inline void GfAssetPack::setupStreamObject() {
    for (const GfAssetFiles::AssetFile* file : m_files.m_files) {
        if (file->m_isWimdo) {
            if (GfAssetResource* resource = getResource(file->m_idx)) {
                resource->setupStreamObject();
            }
        }
    }
}

void AssetPackInfo::setupStreamObject() {
    for (GfAssetPack* pack : m_packs) {
        pack->setupStreamObject();
    }
}

void AssetPackInfo::releaseEmptySlot() {
    for (GfAssetPack** it = m_packs.begin(); it != m_packs.end(); ++it) {
        (*it)->releaseEmptySlot();
    }
}

void GfAssetPack::releaseEmptySlot() {
    if (!isLoaded(nullptr)) {
        return;
    }
    if (m_slotHandle == reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
        return;
    }
    for (const GfAssetFiles::AssetFile* file : m_files.m_files) {
        GfAssetResource* resource = getResource(file->m_idx);
        if (resource != nullptr && resource->getAssetSize() != 0) {
            return;
        }
    }
    releaseSlotHandle();
}

void AssetPackInfo::setLoadComplete() {
    m_reload = false;
    for (GfAssetPack* pack : m_packs) {
        (void)pack;
    }
}

void GfAssetPack::createSoundPack() {
    if (m_sePackId == -1) {
        return;
    }
    if (m_sePack != nullptr) {
        m_sePackRef++;
        return;
    }
    for (const GfAssetFiles::AssetFile* file : m_files.m_files) {
        if (GfAssetResource* resource = getResource(file->m_idx)) {
            if (GfSound* sound = GfSound::sys()) {
                m_sePack = sound->createObjSePack(resource);
                m_sePackRef++;
            }
            return;
        }
    }
}

bool AssetPackInfo::isCached() const {
    if (m_reload) {
        for (GfAssetPack* const* it = m_packs.begin(); it != m_packs.end(); ++it) {
            if (!((*it)->m_refCacheCount > 9)) {
                return false;
            }
        }
    } else {
        for (GfAssetPack* const* it = m_packs.begin(); it != m_packs.end(); ++it) {
            if (!(*it)->isCached()) {
                return false;
            }
        }
    }
    return true;
}

void AssetPackInfo::updateReloadCount() {
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

bool AssetPackInfo::isExistAssetPack(const GfAssetPack* pack) const {
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

bool AssetPackInfo::isPreSizeSizeValid() const {
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

void GfAssetPack::releaseResource() {
    destroySoundPack();
    for (Resource& resource : m_resources) {
        if (resource.m_resource != nullptr) {
            resource.m_resource->release();
            resource.m_resource = nullptr;
        }
    }
    m_resources.clear();
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

inline fw::SoundPack* GfAssetPack::getSePackByFileIdx(GfFileIdx file) {
    GfAssetResource* resource = getResource(file);
    if (resource != nullptr && resource->isValidData()) {
        return m_sePack;
    }
    return nullptr;
}

fw::SoundPack* AssetPackInfo::getSePackByFileIdx(GfFileIdx file) {
    for (GfAssetPack* pack : m_packs) {
        if (fw::SoundPack* sePack = pack->getSePackByFileIdx(file)) {
            return sePack;
        }
    }
    return nullptr;
}

bool AssetPackInfo::isSameResource(const AssetPackInfo* other) const {
    if (m_packs.size() != other->m_packs.size()) {
        return false;
    }
    for (unsigned long i = 0; i < m_packs.size(); i++) {
        if (m_packs[i]->m_value.m_key != other->m_packs[i]->m_value.m_key) {
            return false;
        }
    }
    return true;
}

bool AssetPackInfo::isExistResourceName(const char* name) const {
    for (const GfAssetPack* pack : m_packs) {
        for (const GfAssetFiles::AssetFile* file : pack->m_files.m_files) {
            GfAssetResource* resource = pack->getResource(file->m_idx);
            if (resource != nullptr && strstr(resource->getAssetName(), name) != nullptr) {
                return true;
            }
        }
    }
    return false;
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

bool GfAssetPack::isExistReferenceMemory() const {
    for (const GfAssetFiles::AssetFile* file : m_files.m_files) {
        GfAssetResource* resource = getResource(file->m_idx);
        if (resource != nullptr && resource->m_type == 3) {
            return true;
        }
    }
    return false;
}

void GfAssetPack::loadStart(mm::mtl::IAllocator* allocator) {
    m_allocator = allocator;
    for (const GfAssetFiles::AssetFile* file : m_files.m_files) {
        GfFileIdx idx = file->m_idx;
        const mm::mtl::FixStr<128>& name = m_files.getFileName(idx);
        if (!m_files.isNoFile(idx) && getResource(idx) == nullptr) {
            GfAssetResource* resource = GfAssetResource::create(m_files.m_name.m_str, name.m_str, allocator, 10);
            setResource(idx, resource);
        }
    }
}

bool GfAssetPack::isNeedLoad() const {
    if (m_slotHandle == reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
        return true;
    }
    for (const GfAssetFiles::AssetFile* file : m_files.m_files) {
        if (!m_files.isNoFile(file->m_idx) && getResource(file->m_idx) == nullptr) {
            return true;
        }
    }
    return false;
}

void GfAssetPack::setTimeout() {
    m_timeout = true;
}

bool GfAssetPack::changeBackupAssetType() {
    if (m_backupTypes.empty()) {
        return false;
    }
    for (const GfAssetFiles::AssetFile* file : m_files.m_files) {
        if (getResource(file->m_idx) != nullptr) {
            return false;
        }
    }
    GfAssetType type = m_backupTypes.front();
    if (type != 0) {
        m_files.m_type = type;
    }
    m_backupTypes.pop();
    m_backupChanged = true;
    return true;
}

AssetPackValue GfAssetPack::calcAssetPackValue(const char* name, GfAssetType type) {
    AssetPackValue value;
    value.m_type = type;
    value.m_hash = mm::mtl::hashStrCrc(name);
    return value;
}

bool GfAssetPack::releaseRefResource(void* resource) {
    if (resource == nullptr) {
        return false;
    }
    for (GfAssetFiles::AssetFile* file : m_files.m_files) {
        GfAssetResource* loaded = getResource(file->m_idx);
        if (loaded != nullptr && loaded->getAssetData() == resource) {
            if (!m_refReleased) {
                m_refReleased = true;
            }
            return true;
        }
    }
    return false;
}

GfAssetPack::~GfAssetPack() {
    destroySoundPack();
    releaseResource();
    releaseSlotHandle();
}

void GfAssetPack::setResource(GfFileIdx file, GfAssetResource* resource) {
    Resource entry;
    entry.m_resource = resource;
    entry.m_fileIdx = file;
    m_resources.push_back(entry);
    resource->addRef();
}

bool GfAssetPack::isExistSameAsset(const GfAssetPack& other) const {
    return m_files.isExistSameAsset(other.m_files);
}

const mm::mtl::FixStr<128>& GfAssetFiles::getFileName(GfFileIdx idx) const {
    // the name returned for a file the pack does not have (the name is not the original's)
    static mm::mtl::FixStr<128> s_noName;
    int common = getCommonResource(idx);
    if (common == -1) {
        common = idx;
    }
    for (const AssetFile* file : m_files) {
        if (file->m_idx == common) {
            return file->m_path;
        }
    }
    return s_noName;
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

// the pack vector's growth: 2.0.0's symbols name the instantiation (its users, AssetPackInfo's constructor and
// setAssetPack, are not written yet)
template void mm::mtl::Vector<gf::GfAssetPack*>::expand(size_t, size_t);
