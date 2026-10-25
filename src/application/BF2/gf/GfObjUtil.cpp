#include "mm/mtl/Bitflag.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfGameParty.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfAssetManager.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjInfo.h"
#include "gf/GfObjAcc.h"
#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfExtendPacking.h"
#include "classes/gf/GfComProperty.h"
#include "classes/gf/GfStatusProperty.h"
#include "classes/gf/GfGameParty.h"
#include "classes/gf/DataParamAcc.h"
#include "gf/MsgUnk_1000047.h"
#include "gf/MsgUnk_1000048.h"
#include "gf/MsgUnk_1000046.h"
#include "classes/gf/GfComModel.h"

namespace gf {

int GfObjUtil::getObjType(GF_OBJ_HANDLE* handle) {
    if (GfObj* obj = getObj(handle)) {
        return obj->m_type;
    }
    return 0;
}

GfObj* GfObjUtil::getObj(GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return nullptr;
    }
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return nullptr;
    }
    return info->m_obj;
}

unsigned int GfObjUtil::getObjLayer(GF_OBJ_HANDLE* handle) {
    if (GfObj* obj = getObj(handle)) {
        return obj->m_updateBit;
    }
    return 4;
}

float GfObjUtil::getSetupScale(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_setup != nullptr) {
        return info->m_setup->m_initialScale.x;
    }
    return 1.0f;
}

GfObjSetup* GfObjUtil::getObjSetup(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return nullptr;
    }
    return info->m_setup;
}

GF_ASSET_HANDLE* GfObjUtil::getAssetHandle(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return reinterpret_cast<GF_ASSET_HANDLE*>(-1);
    }
    return info->m_assetHandle;
}

void GfObjUtil::applyExecUpdate(GfObj* obj) {
    bool exec = false;
    if (obj->m_updateFlags & 2) {
        GFOBJ_INFO* info = obj->m_info;
        if (info == nullptr || !testFlag(info, 0)) {
            GfObjManager* manager = GfObjManager::sys();
            if (manager == nullptr || !manager->isSuspendUpdate()) {
                if (info == nullptr || !testFlag(info, 18) || GfGameParty::isPartyMemberInGameObj()) {
                    exec = !isFollowObjNotReady(obj->m_handle);
                }
            }
        }
    }
    obj->m_execUpdate = exec;
}

GF_OBJ_HANDLE* GfObjUtil::getParentHandle(GF_OBJ_HANDLE* handle) {
    if (GfObj* obj = getObj(handle)) {
        if (GfObj* parent = getParentObj(obj)) {
            return parent->m_handle;
        }
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GfObj* GfObjUtil::getParentObj(GfObj* obj) {
    fw::UpdatableObject* parent = obj->m_parent.get();
    if (parent == nullptr) {
        return nullptr;
    }
    return mm::mtl::rttiCast<GfObj>(parent);
}

unsigned int GfObjUtil::getLayerSection(unsigned int layer) {
    switch (layer) {
    case 0:
        return 0;
    case 1:
    case 2:
    case 3:
        return 1;
    case 4:
    case 5:
    case 6:
        return 4;
    case 7:
    case 8:
    case 9:
        return 7;
    case 10:
    case 11:
    case 12:
        return 10;
    }
    return 4;
}

const char* GfObjUtil::getResourceName(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    return acc.getModelResourceName();
}

const char* GfObjUtil::getMotionResourceName(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    return acc.getMotionResourceName();
}

GF_MOUNT_HANDLE* GfObjUtil::getMountHandle(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return reinterpret_cast<GF_MOUNT_HANDLE*>(-1);
    }
    return info->m_mounts[attach].m_handle;
}

void GfObjUtil::setLimitHP(GF_OBJ_HANDLE* handle, unsigned int hp) {
    if (GfObj* obj = getObj(handle)) {
        MsgUnk_1000048 msg(hp);
        obj->sendMessage(obj, msg);
    }
}

void GfObjUtil::setInvincible(GF_OBJ_HANDLE* handle, bool on, bool value2) {
    if (GfObj* obj = getObj(handle)) {
        MsgUnk_1000047 msg(on, value2);
        obj->sendMessage(obj, msg);
    }
}

void GfObjUtil::setDisableAutoHeal(GF_OBJ_HANDLE* handle, bool on) {
    if (GfObj* obj = getObj(handle)) {
        MsgUnk_1000046 msg(on);
        obj->sendMessage(obj, msg);
    }
}

GfObjProperty* GfObjUtil::getProperty(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return nullptr;
    }
    return info->m_property;
}

unsigned int GfObjUtil::getHp(GF_OBJ_HANDLE* handle) {
    if (GfObj* obj = getObj(handle)) {
        if (GfComProperty* property = obj->getComponent<GfComProperty>(5)) {
            if (GfStatusProperty* status = property->m_status.get()) {
                return status->m_hp;
            }
        }
    }
    return 0;
}

unsigned int GfObjUtil::getPartyID(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_setup != nullptr) {
        return info->m_setup->m_partyId;
    }
    return -1;
}

void GfObjUtil::rebuild(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.m_obj == nullptr) {
        return;
    }
    if (acc.getUserData(static_cast<GfObjUserData>(0)) != nullptr) {
        destroy(handle);
    } else {
        acc.setFlag(6, true);
        if (GfObjManager* manager = GfObjManager::sys()) {
            manager->addDestroyObj(handle, false);
        }
    }
}

GfAppendHandles* GfObjUtil::getExtraMountObject(GF_OBJ_HANDLE* handle) {
    return GfMountManager::getAppendHandles(handle, static_cast<GFATTACH>(1));
}

bool GfObjUtil::isValid(GF_OBJ_HANDLE* handle) {
    return getObj(handle) != nullptr;
}

bool GfObjUtil::isLoading(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return false;
    }
    return info->m_state == 1;
}

bool GfObjUtil::isUpdate(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return false;
    }
    return info->m_state == 2;
}

void GfObjUtil::setOwner(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* owner) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr) {
        info->m_owner = owner;
    }
}

GF_OBJ_HANDLE* GfObjUtil::getOwner(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    return info->m_owner;
}

bool GfObjUtil::isExistAsm(GF_OBJ_HANDLE* handle) {
    GfExtendResource* resource = GfAssetManager::getExtentResource(getAssetHandle(handle), 0);
    if (resource == nullptr) {
        return false;
    }
    if (GfExtendPacking* packing = mm::mtl::rttiCast<GfExtendPacking>(resource)) {
        return packing->m_pResASM != nullptr;
    }
    return false;
}


void GfObjUtil::copyTransformToSetup(GF_OBJ_HANDLE* src, GF_OBJ_HANDLE* dst) {
    GfObjAcc acc(src);
    if (!acc.isValidTransform()) {
        return;
    }
    if (GfObjSetup* setup = getObjSetup(dst)) {
        setup->setInitialTransform(acc.getWorldTransform());
    }
}

bool GfObjUtil::isEnemyBlade(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    if (acc.getType() != 5) {
        return false;
    }
    GfObjSetup* setup = getObjSetup(handle);
    return setup != nullptr && setup->m_createType == 5;
}

bool GfObjUtil::setFlag(GF_OBJ_HANDLE* handle, unsigned int flag, bool on) {
    return setFlag(GfObjManager::getObjInfo(handle), flag, on);
}

bool GfObjUtil::setFlag(GFOBJ_INFO* info, unsigned int flag, bool on) {
    if (info == nullptr || info->m_flags[flag] == on) {
        return false;
    }
    info->m_flags.change(flag, on);
    if (GfObjManager* manager = GfObjManager::sys()) {
        manager->addApplyParam(info->m_handle);
    }
    return true;
}

bool GfObjUtil::testFlag(GF_OBJ_HANDLE* handle, unsigned int flag) {
    return testFlag(GfObjManager::getObjInfo(handle), flag);
}

bool GfObjUtil::testFlag(const GFOBJ_INFO* info, unsigned int flag) {
    if (info == nullptr) {
        return false;
    }
    return info->m_flags[flag];
}

const char* GfObjUtil::getModelBaseName(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return "";
    }
    return info->m_modelBaseName.m_str;
}

const char* GfObjUtil::getAssetMotionName(GF_OBJ_HANDLE* handle) {
    return GfAssetManager::getMotionInfo(getAssetHandle(handle));
}

GfComModel* GfObjUtil::getComModel(GF_OBJ_HANDLE* handle) {
    if (GfObj* obj = getObj(handle)) {
        return obj->getComponent<GfComModel>(1);
    }
    return nullptr;
}

GfVolumeFade* GfObjUtil::getVolumeFade(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return nullptr;
    }
    return info->m_volumeFade;
}

bool GfObjUtil::isVolumeFadeForUser(GF_OBJ_HANDLE* handle) {
    return testFlag(GfObjManager::getObjInfo(handle), 20);
}

void GfObjUtil::setVolumeFadeUserFlag(GF_OBJ_HANDLE* handle, bool on) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_flags[20] != on) {
        info->m_flags.change(20, on);
    }
}

void GfObjUtil::setTalking(GF_OBJ_HANDLE* handle, bool on) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr) {
        info->m_flags.change(21, on);
    }
}

bool GfObjUtil::isTalking(GF_OBJ_HANDLE* handle) {
    return testFlag(GfObjManager::getObjInfo(handle), 21);
}

bool GfObjUtil::isTrinityBlade(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return false;
    }
    if (info->m_setup == nullptr) {
        return false;
    }
    return info->m_setup->m_createType == 8;
}

}  // namespace gf
