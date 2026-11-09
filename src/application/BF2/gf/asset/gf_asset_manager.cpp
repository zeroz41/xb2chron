#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetPack.h"
#include "classes/gf/GfAssetResource.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfFileSizePool.h"
#include "gf/AssetPackInfo.h"
#include "gf/GfSetupParam.h"
#include "gf/GfSlotMapping.h"
#include "mm/mtl/FixedVector.h"
#include "classes/ml/WinView.h"
#include "mtl/MemManager.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "classes/gf/GfInitParam.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfManager.h"

namespace gf {

GfAssetManager::GfAssetManager(const GfSetupParam& param) : m_serial(0), m_slotMapping(nullptr), m_initialized(false), pad_3CCC1(false) {
    initialize(param);
}

void GfAssetManager::initialize(const GfSetupParam& param) {
#line 101
    m_slotMapping = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfSlotMapping();
    param.m_view->attachWorkEvent(this, false);
    unsigned long size = mtl::MemManager::maxAllocSize(getAllocator(ALLOCATOR(3))->getMemHandle()) & ~0x1FFFUL;
    m_slotMapping->setup(param, getAllocator(ALLOCATOR(3)), size);
    GfFileSizePool::build(param);
    m_initialized = true;
}

void GfAssetManager::build(const GfSetupParam& param) {
#line 69
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfAssetManager(param);
}

void GfAssetManager::destroy() {
    GfAssetManager* self = get();
    self->finalize();
    delete self;
}

GfAssetManager::~GfAssetManager() {}

void GfAssetManager::finalize() {
    pad_3CCC1 = true;
    GfFileSizePool::destroy();
    while (m_loadingHandles.size() != 0) {
        GfSleep(1);
    }
    for (mm::mtl::FixedList<GF_ASSET_HANDLE*, 1024>::iterator it = m_loadedHandles.begin(); it != m_loadedHandles.end();
         ++it) {
        AssetPackInfo* info = getAssetPackInfo(*it);
        if (info != nullptr) {
            info->~AssetPackInfo();
            m_packInfos.deallocate(info);
        }
    }
    m_loadedHandles.clear();
    m_destroyHandles.clear();
    for (;;) {
        bool cached = true;
        for (mm::mtl::FixedList<GfAssetPack*, 2048>::iterator it = m_assetPacks.begin(); it != m_assetPacks.end();
             ++it) {
            if (!(*it)->isCached()) {
                cached = false;
                break;
            }
        }
        if (cached) {
            break;
        }
        GfSleep(1);
    }
    for (mm::mtl::FixedList<GfAssetPack*, 2048>::iterator it = m_assetPacks.begin(); it != m_assetPacks.end(); ++it) {
        (*it)->releaseResource();
    }
    GfSleep(5);
    for (mm::mtl::FixedList<GfAssetPack*, 2048>::iterator it = m_assetPacks.begin(); it != m_assetPacks.end(); ++it) {
        if (*it != nullptr) {
            (*it)->release();
            *it = nullptr;
        }
    }
    m_assetPacks.clear();
    m_slotMapping->destroy();
    GfManager::getSetupParam().m_view->detachWorkEvent(this);
    if (m_slotMapping != nullptr) {
        delete m_slotMapping;
        m_slotMapping = nullptr;
    }
    m_initialized = false;
}

AssetPackInfo* GfAssetManager::getAssetPackInfo(GF_ASSET_HANDLE* handle) {
    unsigned int index = static_cast<unsigned int>(reinterpret_cast<unsigned long>(handle));
    ml::fixed_size_alloc_inside<AssetPackInfo, 1024>& infos = get()->m_packInfos;
    unsigned int slot = index & 0x3FF;
    AssetPackInfo* info = &infos.m_pData[slot];
    unsigned int word = slot >> 5;
    unsigned int mask = 1u << (index & 0x1F);
    return (infos.m_pBits[word] & mask) != 0 ? info : nullptr;
}
}  // namespace gf

template ml::fixed_size_alloc_inside<gf::AssetPackInfo, 1024>::~fixed_size_alloc_inside();

namespace gf {

void GfAssetManager::destroy(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr && !info->m_destroy) {
        info->setDestroy();
        GfAssetManager* self = get();
        mm::mtl::FixedList<GF_ASSET_HANDLE*, 1024>::iterator it = self->m_loadedHandles.find(handle);
        if (it == self->m_loadedHandles.end()) {
            it = self->m_loadingHandles.find(handle);
            if (it == self->m_loadingHandles.end()) {
                return;
            }
        }
        self->m_destroyHandles.push_back(*it);
    }
}
}  // namespace gf

namespace gf {

void GfAssetManager::enableGameResource(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr && !info->m_usingGame) {
        info->setUsingGame(true);
    }
}

void GfAssetManager::disableGameResource(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr && info->m_usingGame) {
        info->setUsingGame(false);
    }
}

GF_ASSET_HANDLE* GfAssetManager::createAssetHandle(const GfInitParam& param) {
    GfAssetManager* self = get();
    unsigned int index;
    AssetPackInfo* info = self->m_packInfos.allocate(index);
    new (info) AssetPackInfo(param.pad_c);
    unsigned int serial = self->m_serial++;
    if (serial >= 0xFFFFF) {
        serial = self->m_serial++;
    }
    GF_ASSET_HANDLE* handle = reinterpret_cast<GF_ASSET_HANDLE*>(static_cast<unsigned long>((index & 0x3FF) | serial << 10));
    info->m_handle = handle;
    self->m_loadingHandles.push_back(handle);
    return handle;
}

void GfAssetManager::loadStart(GfAssetPack* pack, mm::mtl::IAllocator* allocator) {
    pack->loadStart(allocator);
}

void GfAssetManager::releaseSlotHandle(GF_SLOT_HANDLE* handle) {
    get()->m_slotMapping->releaseSlot(handle);
}

GfAssetPack* GfAssetManager::getAssetPack(GF_ASSET_HANDLE* handle, GfFileIdx file) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->getAssetPack(file);
    }
    return nullptr;
}

GfSlotMapping* GfAssetManager::getSlotMapping() {
    GfAssetManager* self = get();
    if (self != nullptr) {
        return self->m_slotMapping;
    }
    return nullptr;
}

bool GfAssetManager::getFileNameByExt(mm::mtl::FixedVector<const char*, 128>& names, GF_ASSET_HANDLE* handle,
                                   const char* name) {
    if (handle != reinterpret_cast<GF_ASSET_HANDLE*>(-1) && name != nullptr) {
        AssetPackInfo* info = getAssetPackInfo(handle);
        if (info != nullptr) {
            return info->getFileNameByExt(names, name);
        }
    }
    return !names.empty();
}

GfAssetResource* GfAssetManager::getResource(GF_ASSET_HANDLE* handle, GfFileIdx file, GfAssetType type) {
    GfAssetResource* resource = nullptr;
    if (handle != reinterpret_cast<GF_ASSET_HANDLE*>(-1) && file != static_cast<GfFileIdx>(-1)) {
        AssetPackInfo* info = getAssetPackInfo(handle);
        if (info != nullptr) {
            GfAssetResource* loaded = info->getResource(file);
            if (loaded != nullptr) {
                resource = loaded->isValidData() ? loaded : nullptr;
            }
        }
    }
    return resource;
}

GfAssetResource* GfAssetManager::getResource(GF_ASSET_HANDLE* handle, const char* name) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->getResource(name);
    }
    return nullptr;
}

bool GfAssetManager::isLoaded(GF_ASSET_HANDLE* handle, mm::mtl::FixStr<128>* name) {
    if (handle != reinterpret_cast<GF_ASSET_HANDLE*>(-1)) {
        AssetPackInfo* info = getAssetPackInfo(handle);
        if (info != nullptr) {
            return info->isLoaded(name) && !info->m_reload;
        }
    }
    return true;
}

void GfAssetManager::setupStreamObject(GF_ASSET_HANDLE* handle) {
    if (handle != reinterpret_cast<GF_ASSET_HANDLE*>(-1)) {
        AssetPackInfo* info = getAssetPackInfo(handle);
        if (info != nullptr) {
            info->setupStreamObject();
        }
    }
}

bool GfAssetManager::isDestroy(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->m_destroy;
    }
    return false;
}

bool GfAssetManager::isReload(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->m_reload;
    }
    return false;
}

GF_OBJ_HANDLE* GfAssetManager::getObj(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->m_objHandle;
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

bool GfAssetManager::isExist(GF_ASSET_HANDLE* handle, GfFileIdx file) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->isExist(file);
    }
    return false;
}

void GfAssetManager::setExtendResource(GF_ASSET_HANDLE* handle, unsigned int index, GfExtendResource* resource) {
    getAssetPackInfo(handle)->setExtendResource(index, resource);
}

void GfAssetManager::destroySlotCache(GfAssetType type) {
    mm::mtl::FixedList<GfAssetType, 32>& types = get()->m_list3C940;
    if (types.find(type) == types.end()) {
        types.push_back(type);
    }
}

GfExtendResource* GfAssetManager::getExtentResource(GF_ASSET_HANDLE* handle, unsigned int index) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->m_extendResources[index];
    }
    return nullptr;
}

void GfAssetManager::destroyExtResource(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        info->releaseExtResource();
    }
}

bool GfAssetManager::isExistSameAsset(GfAssetPack* pack) {
    mm::mtl::FixedList<GfAssetPack*, 2048>& packs = get()->m_assetPacks;
    for (mm::mtl::FixedList<GfAssetPack*, 2048>::iterator it = packs.begin(); it != packs.end(); ++it) {
        GfAssetPack* other = *it;
        if (other != pack && other->m_value == pack->m_value && other->isExistSameAsset(*pack)) {
            return true;
        }
    }
    return false;
}

void GfAssetManager::clear() {
    destroySlotCache(GfAssetType(0));
}

bool GfAssetManager::getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE*, 88>& handles, GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->getSlotHandle(handles);
    }
    return false;
}

void GfAssetManager::setModelInfo(GF_ASSET_HANDLE* handle, const char* name) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        info->setModelName(name);
    }
}

bool GfAssetManager::isFullResource(GF_ASSET_HANDLE* handle) const {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->isFullResource();
    }
    return false;
}

fw::SoundPack* GfAssetManager::getSePackByFileIdx(GF_ASSET_HANDLE* handle, GfFileIdx file) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->getSePackByFileIdx(file);
    }
    return nullptr;
}

unsigned int GfAssetManager::getUsedAssetPackInfo() {
    GfAssetManager* self = get();
    if (self != nullptr) {
        return self->m_packInfos.m_count;
    }
    return 0;
}

const char* GfAssetManager::getModelInfo(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->m_modelName.m_str;
    }
    return "";
}

void GfAssetManager::setMotionInfo(GF_ASSET_HANDLE* handle, const char* name) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        info->setMotionName(name);
    }
}

const char* GfAssetManager::getMotionInfo(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->m_motionName.m_str;
    }
    return "";
}
}  // namespace gf

// instantiated for gf::GfAssetManager::updateCheckCacheReload, gf::GfAssetManager::updateCheckDestroy (not written yet), gf::GfAssetManager::updateCheckLoading
template mm::mtl::FixedList<gf::GF_ASSET_HANDLE*, 1024>::iterator mm::mtl::FixedList<gf::GF_ASSET_HANDLE*, 1024>::erase(mm::mtl::FixedList<gf::GF_ASSET_HANDLE*, 1024>::iterator);

namespace gf {

void GfAssetManager::updateCheckLoading() {
    for (mm::mtl::FixedList<GfAssetPack*, 2048>::iterator it = m_assetPacks.begin(); it != m_assetPacks.end(); ++it) {
        if (!(*it)->isPreSizeSizeValid()) {
            (*it)->applyPreFileSize();
        }
    }
    for (mm::mtl::FixedList<GF_ASSET_HANDLE*, 1024>::iterator it = m_loadingHandles.begin();
         it != m_loadingHandles.end();) {
        GF_ASSET_HANDLE*& handle = *it;
        AssetPackInfo* info = getAssetPackInfo(handle);
        if (info == nullptr) {
            it = m_loadingHandles.erase(it);
        } else if (info->m_destroy) {
            m_loadedHandles.push_back(handle);
            it = m_loadingHandles.erase(it);
        } else if (info->isLoaded(nullptr) && info->isPreSizeSizeValid()) {
            info->releaseEmptySlot();
            info->setLoadComplete();
            m_loadedHandles.push_back(handle);
            it = m_loadingHandles.erase(it);
        } else {
            ++it;
        }
    }
}

void GfAssetManager::releaseRefResource(void* resource) {
    for (mm::mtl::FixedList<GfAssetPack*, 2048>::iterator it = m_assetPacks.begin(); it != m_assetPacks.end(); ++it) {
        if ((*it)->releaseRefResource(resource)) {
            break;
        }
    }
}

void GfAssetManager::setupLoadStart(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        info->setupLoadStart();
    }
}

bool GfAssetManager::isExistResourceName(GF_ASSET_HANDLE* handle, const char* name) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->isExistResourceName(name);
    }
    return false;
}

void GfAssetManager::lockEnterRersource(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        info->lockEnterRersource();
    }
}

void GfAssetManager::update(const fw::UpdateInfo& info) {
    if (GfFileSizePool::get() != nullptr) {
        GfFileSizePool::get()->update();
    }
    getSlotMapping()->update(info);
    updateCheckLoading();
    updateCheckDestroy();
    updateCheckCacheReload();
}

}  // namespace gf

// instantiated for gf::GfAssetManager::updateCheckCacheReload, gf::GfAssetManager::updateCheckDestroy (not written yet)
template mm::mtl::FixedList<gf::GfAssetPack*, 2048>::iterator mm::mtl::FixedList<gf::GfAssetPack*, 2048>::erase(mm::mtl::FixedList<gf::GfAssetPack*, 2048>::iterator);
