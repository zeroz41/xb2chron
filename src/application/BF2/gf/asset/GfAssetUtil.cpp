#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfObjManager.h"
#include "gf/AssetPackInfo.h"
#include "gf/GfAssetUtil.h"
#include "gf/GfObjAcc.h"

namespace gf {

// the object of a handle's pack; no handle (-1) for a handle with no pack
static GF_OBJ_HANDLE* getObjHandle(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = GfAssetManager::getAssetPackInfo(handle);
    return info != nullptr ? info->m_objHandle : reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

void GfAssetUtil::addDestroyObject(GF_ASSET_HANDLE* handle, bool flag) {
    GfObjAcc acc(getObjHandle(handle));
    if (acc.m_obj != nullptr && !acc.isDestroy()) {
        GfObjManager* manager = GfObjManager::get();
        if (manager != nullptr) {
            manager->addDestroyObj(getObjHandle(handle), flag);
        }
    }
}

bool GfAssetUtil::isObjectDestroy(GF_ASSET_HANDLE* handle) {
    GfObjAcc acc(getObjHandle(handle));
    if (acc.m_obj == nullptr) {
        return true;
    }
    return acc.isDestroy();
}

bool GfAssetUtil::isRetargetLoad(GF_ASSET_HANDLE* handle) {
    AssetPackInfo* info = GfAssetManager::getAssetPackInfo(handle);
    if (info == nullptr) {
        return false;
    }
    return info->m_retargetLoad;
}

void GfAssetUtil::setRetargetLoad(GF_ASSET_HANDLE* handle, bool retargetLoad) {
    AssetPackInfo* info = GfAssetManager::getAssetPackInfo(handle);
    if (info != nullptr) {
        info->m_retargetLoad = retargetLoad;
    }
}

}  // namespace gf
