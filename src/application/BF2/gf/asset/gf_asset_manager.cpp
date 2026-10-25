#include "gf/AssetPackInfo.h"
#include "gf/GfSlotMapping.h"
#include "classes/gf/GfAssetPack.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetPack.h"
#include "classes/gf/GfAssetResource.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfFileSizePool.h"
#include "gf/AssetPackInfo.h"
#include "gf/GfSetupParam.h"
#include "gf/GfSlotMapping.h"

namespace gf {

void GfAssetManager::build(const GfSetupParam& param) {
#line 69
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfAssetManager(param);
}

void GfAssetManager::destroy() {
    GfAssetManager* self = get();
    self->finalize();
    delete self;
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
        return info->m_modelName;
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
        return info->m_motionName;
    }
    return "";
}

void GfAssetManager::setupLoadStart(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = getAssetPackInfo(handle);
    if (info != nullptr) {
        info->setupLoadStart();
    }
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
