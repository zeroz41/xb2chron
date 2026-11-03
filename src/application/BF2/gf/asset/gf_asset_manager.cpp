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

namespace gf {

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

bool GfAssetManager::fn_71001AE8A8(mm::mtl::FixedVector<const char*, 128>& names, GF_ASSET_HANDLE* handle,
                                   const char* name) {
    if (handle != reinterpret_cast<GF_ASSET_HANDLE*>(-1) && name != nullptr) {
        AssetPackInfo* info = getAssetPackInfo(handle);
        if (info != nullptr) {
            return info->fn_71001B1840(names, name);
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

GfAssetResource* GfAssetManager::fn_71001AE9D0(GF_ASSET_HANDLE* handle, const char* name) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->fn_71001B1B30(name);
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

// instantiated for gf::GfAssetManager::updateCheckCacheReload, gf::GfAssetManager::updateCheckDestroy, gf::GfAssetManager::updateCheckLoading (not written yet)
template mm::mtl::FixedList<gf::GF_ASSET_HANDLE*, 1024>::iterator mm::mtl::FixedList<gf::GF_ASSET_HANDLE*, 1024>::erase(mm::mtl::FixedList<gf::GF_ASSET_HANDLE*, 1024>::iterator);

namespace gf {

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

bool GfAssetManager::fn_71001AF824(GF_ASSET_HANDLE* handle, const char* name) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        return info->fn_71001B3624(name);
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
