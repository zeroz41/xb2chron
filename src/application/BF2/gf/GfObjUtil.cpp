#include "gf/GfObjUtil.h"
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
#include "classes/gf/GfGamePlayerFormation.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjPropertyCharacter.h"
#include "gf/GfTargetProperty.h"
#include "classes/gf/GfManager.h"
#include "gf/GfDataDriver.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/fw/PadResEventManager.h"
#include "classes/gf/GfComponent.h"
#include "classes/gf/GfComIK.h"
#include "classes/fw/SphericalCoordinatesIkSolver.h"
#include "classes/fw/BlowRotateIkSolver.h"
#include "classes/fw/RotateIkSolver.h"
#include "classes/fw/SpineRotateIKSolver.h"
#include "classes/fw/LookIkSolver.h"
#include "classes/fw/SpineIkSolver.h"
#include "classes/fw/LookAtIkSolver.h"
#include "classes/fw/PlacementGroundSolver.h"
#include "classes/fw/SlopeGroundSolver.h"
#include "classes/fw/TwoCharaGroundSolver.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfComDynamics.h"
#include "gf/MsgUnk_1000007.h"
#include "classes/gf/GfComBehavior.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComEvtAnim.h"
#include "gf/GfObjUpdate.h"
#include "classes/gf/EyeBlinkPlugin.h"
#include "classes/gf/GfComPropertyPc.h"
#include "gf/GfAppend.h"
#include "classes/gf/GfObjSetupWeapon.h"
#include "classes/gf/GfComCollider.h"
#include "classes/fw/ColiObject.h"
#include "gf/GfDataUtil.h"
#include "classes/gf/GfGameMount.h"
#include "classes/gf/GfWeapon.h"
#include "gf/MsgObjectForceWeaponMount.h"
#include "classes/fw/TransLocalIkSolver.h"
#include "classes/fw/RotateLocalIkSolver.h"
#include "ml/MdlVtxParticle.h"
#include "ml/ScnObjAccMdlParticle.h"
#include "classes/fw/EffectManager.h"
#include <string.h>
#include "fw/PadRelay.h"
#include "gf/GfStaticRes.h"
#include "arc/CArcData.h"
#include "classes/fw/CommonResource.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfVolumeFade.h"
#include "classes/fw/ModelObject.h"
#include "ml/ScnObjAccEtcParams.h"
#include "gf/GfUtil.h"
#include "gf/GfDataFobj.h"
#include "gf/GfDataWeapon.h"
#include "classes/gf/GfObjSetupGimmick.h"
#include "fw/Transform.h"
#include "mm/Math.h"
#include "classes/gf/GfObjSetupDriver.h"
#include "classes/gf/GfObjSetupBlade.h"

namespace gf {

namespace {
// an object's info and its mount at one of its points (the name is not the original's)
struct MountAcc {
    MountAcc(GF_OBJ_HANDLE* handle, GFATTACH attach) {
        m_info = GfObjManager::getObjInfo(handle);
        m_mount = m_info != nullptr ? &m_info->m_mounts[attach] : nullptr;
    }

    GFOBJ_INFO* m_info;
    GFOBJ_MOUNT* m_mount;
};

// switches a SphericalCoordinatesIkSolver on whatever enable says: the original stores 1 on both paths, yet
// setEnableAllIK still passes its enable to setEnableSPCIK, so the source handed enable to a call inlined only
// after dead-argument elimination (the helper and its name are not the original's)
inline void enableSolver(fw::SphericalCoordinatesIkSolver* solver, bool) {
    solver->m_enable = true;
}
}  // namespace

void GfObjUpdate::updateComponent(GfObj* obj, const fw::UpdateInfo& info) {
    if (!obj->m_execUpdate) {
        return;
    }
    if (GfComAsm* com = obj->getComponent<GfComAsm>(2)) {
        com->executeCallback();
    } else if (GfComEvtAnim* anim = obj->getComponent<GfComEvtAnim>(2)) {
        anim->m_asm.executeCallback(anim);
    }
    if (GfComBehavior* behavior = obj->getComponent<GfComBehavior>(6)) {
        behavior->update(info);
    }
    if (GfComAsm* com = obj->getComponent<GfComAsm>(2)) {
        com->executeCallback();
    } else if (GfComEvtAnim* anim = obj->getComponent<GfComEvtAnim>(2)) {
        anim->m_asm.executeCallback(anim);
    }
}

void GfObjUtil::addDebugName(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return;
    }
    GfObjAcc acc(handle);
    unsigned int id = acc.getBdatId();
    switch (acc.getType()) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 15: {
        DataParamAcc data(handle);
        if (data.getModelResourceName() != nullptr) {
            info->m_modelBaseName = util::getFilePtrFromPath(data.getModelResourceName());
        }
        break;
    }
    case 8:
        if (GFOBJ_INFO* objInfo = GfObjManager::getObjInfo(handle)) {
            if (GfObjSetup* setup = objInfo->m_setup) {
                if (setup->m_type == objInfo->m_obj->m_type && objInfo->m_obj->m_type == 8 &&
                    setup->getRTTI()->isKindOf(&GfObjSetupGimmick::m_rtti)) {
                    if (static_cast<GfObjSetupGimmick*>(setup)->pad_98 != nullptr) {
                        info->m_modelBaseName = "";
                    }
                }
            }
        }
        break;
    case 9:
        if (const char* name = GfDataFobj::getFobjModelName(id)) {
            info->m_modelBaseName = util::getFilePtrFromPath(name);
        }
        break;
    case 10: {
        GfAppend* append = getAppend(handle, GFATTACH(0));
        if (append == nullptr) {
            append = getAppend(handle, GFATTACH(3));
        }
        if (append != nullptr) {
            if (const char* name = GfDataWeapon::getModelName(append->getRscID())) {
                info->m_modelBaseName = util::getFilePtrFromPath(name);
            }
        }
        break;
    }
    }
}

GfAppend* GfObjUtil::getAppend(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    // a weapon set up for the second list takes its append from there
    bool second = false;
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr) {
        if (GfObjSetup* setup = info->m_setup) {
            if (setup->m_type == info->m_obj->m_type && info->m_obj->m_type == 10) {
                if (GfObjSetupWeapon* weapon = mm::mtl::rttiCast<GfObjSetupWeapon>(setup)) {
                    second = weapon->pad_78 != 0;
                }
            }
        }
    }
    MountAcc acc(handle, attach);
    if (acc.m_info == nullptr) {
        return nullptr;
    }
    int index = acc.m_mount->m_appendIndex;
    if (index < 0) {
        return nullptr;
    }
    mm::mtl::FixedVector<GfAppend*, 10>& appends = acc.m_mount->m_appendInfo.m_appends[second];
    if (appends.size() > static_cast<unsigned int>(index)) {
        return appends.begin()[static_cast<unsigned int>(index)];
    }
    return nullptr;
}

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

void GfObjUtil::destroy(GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfObjAcc acc(handle);
    if (acc.m_obj == nullptr) {
        return;
    }
    if (acc.setFlag(0, true)) {
        if (GfObjManager* manager = GfObjManager::sys()) {
            manager->addDestroyObj(handle, true);
        }
        applyExecUpdate(acc.getObj());
    }
    if (acc.m_obj == nullptr) {
        return;
    }
    GfObj* obj = acc.getObj();
    for (mm::mtl::IntrusiveList<fw::UpdatableObject>::iterator it = obj->m_children.begin();
         it != obj->m_children.end(); ++it) {
        destroy(mm::mtl::rttiCast<GfObj>(&*it)->m_handle);
    }
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

bool GfObjUtil::mountToBone(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* parent, const char* bone) {
    GfObj* parentObj = getObj(parent);
    if (parentObj == nullptr) {
        return false;
    }
    if (GfComModel* model = parentObj->getComponent<GfComModel>(1)) {
        GfComTransform* transform = GfObjManager::getObjInfo(handle)->m_obj->getComponent<GfComTransform>(0);
        if (!model->addBoneReferenceFrame(bone, transform->m_frame)) {
            return false;
        }
    }
    GfObj* mountObj = getObj(parent);
    GfObj* obj = getObj(handle);
    if (mountObj != nullptr && obj != nullptr) {
        mountObj->addChild(obj);
    }
    GfObjManager::getObjInfo(handle)->m_mountBoneName = bone;
    return true;
}

bool GfObjUtil::unmountFromBone(GF_OBJ_HANDLE* handle) {
    GfObj* obj = getObj(handle);
    if (obj == nullptr) {
        return false;
    }
    GfObj* parentObj = getParentObj(obj);
    if (parentObj == nullptr) {
        return false;
    }
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (GfComModel* model = parentObj->getComponent<GfComModel>(1)) {
        GfComTransform* transform = obj->getComponent<GfComTransform>(0);
        if (transform->m_frame->m_parent != nullptr) {
            model->removeBoneReferenceFrame(info->m_mountBoneName.m_str, transform->m_frame);
        }
    }
    GfObj* mountObj = getObj(getParentHandle(handle));
    GfObj* child = getObj(handle);
    if (mountObj != nullptr && child != nullptr) {
        mountObj->removeChild(child);
    }
    info->m_mountBoneName = "";
    return true;
}

bool GfObjUtil::attachGfObj(GF_OBJ_HANDLE* parent, GF_OBJ_HANDLE* child) {
    GfObj* parentObj = getObj(parent);
    GfObj* childObj = getObj(child);
    if (parentObj == nullptr || childObj == nullptr) {
        return false;
    }
    const mm::mtl::IntrusivePtr<fw::ReferenceFrame>& parentFrame =
        parentObj->getComponent<GfComTransform>(0)->getFrame();
    GfComTransform* childTransform = childObj->findComponent<GfComTransform>(0);
    if (childTransform->m_frame->m_parent != nullptr) {
        return false;
    }
    parentFrame->addChild(*childTransform->m_frame);
    childTransform->m_frame->setWorldTransformCurrent();
    childTransform->m_frame->syncLocalTransform();
    return true;
}

bool GfObjUtil::dettachGfObject(GF_OBJ_HANDLE* parent, GF_OBJ_HANDLE* child) {
    GfObj* parentObj = getObj(parent);
    GfObj* childObj = getObj(child);
    if (parentObj == nullptr || childObj == nullptr) {
        return false;
    }
    GfComTransform* parentTransform = parentObj->getComponent<GfComTransform>(0);
    if (parentTransform == nullptr) {
        return false;
    }
    const mm::mtl::IntrusivePtr<fw::ReferenceFrame>& parentFrame = parentTransform->getFrame();
    GfComTransform* childTransform = childObj->findComponent<GfComTransform>(0);
    if (childTransform->m_frame->m_parent != parentFrame.get()) {
        return false;
    }
    parentFrame->removeChild(*childTransform->m_frame);
    childTransform->m_frame->setWorldTransformCurrent();
    childTransform->m_frame->syncLocalTransform();
    return true;
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

void GfObjUtil::changeLayer(GfObj* obj, unsigned int layer) {
    unsigned int old = obj->m_updateBit;
    for (unsigned int i = 0; i < 12; i++) {
        if (GfComponent* component = obj->getComponent<GfComponent>(i)) {
            component->changeLayer(old, layer);
        }
    }
    obj->m_updateBit = layer;
}

void GfObjUtil::changeLayer(GF_OBJ_HANDLE* handle, unsigned int layer) {
    if (GfObj* obj = getObj(handle)) {
        changeLayer(obj, layer);
    }
}

const char* GfObjUtil::getResourceName(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    return acc.getModelResourceName();
}

const char* GfObjUtil::getMotionResourceName(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    return acc.getMotionResourceName();
}

void GfObjUtil::resetWeaponMotion(GF_OBJ_HANDLE* handle, OPTMNT option) {
    GfGameMount* mount = GfMountManager::getMount(getMountHandle(handle, GFATTACH()));
    if (mount == nullptr) {
        return;
    }
    if (option == -1) {
        option = mount->m_mountType;
    }
    GF_OBJ_HANDLE* owner = mount->getHandle(option);
    for (unsigned int i = 0; i < 10; ++i) {
        if (GfObj* obj = getObj(handle)) {
            if (GfObj* weapon = getObj(mount->m_weapon->getObjHandles()[i])) {
                MsgObjectForceWeaponMount msg(option, owner);
                obj->sendMessage(weapon, msg);
            }
        }
    }
}

GF_MOUNT_HANDLE* GfObjUtil::getMountHandle(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return reinterpret_cast<GF_MOUNT_HANDLE*>(-1);
    }
    return info->m_mounts[attach].m_handle;
}

unsigned int GfObjUtil::getGameObjectID(GF_OBJ_HANDLE* handle) {
    GfObjSetup* setup = getObjSetup(handle);
    if (setup == nullptr) {
        return -1;
    }
    if (getObjType(handle) == 5) {
        if (GfObjSetupEnemy* enemy = mm::mtl::rttiCast<GfObjSetupEnemy>(setup)) {
            return enemy->m_enArrangeId;
        }
        return -1;
    }
    return setup->m_bdatId;
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

bool GfObjUtil::testInvincible(GF_OBJ_HANDLE* handle) {
    bool found = false;
    bool invincible;
    if (GfObj* obj = getObj(handle)) {
        if (GfComProperty* property = obj->getComponent<GfComProperty>(5)) {
            if (GfStatusProperty* status = property->m_status.get()) {
                invincible = status->m_invincible;
                found = true;
            }
        }
    }
    return found && invincible;
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

GfAppendInfo* GfObjUtil::getAppendInfo(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    MountAcc acc(handle, attach);
    return acc.m_info == nullptr ? nullptr : &acc.m_mount->m_appendInfo;
}

GF_OBJ_HANDLE* GfObjUtil::getMaster(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    return info->m_subHandle;
}

unsigned int GfObjUtil::getPartyPos(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr || info->m_setup == nullptr || info->m_setup->m_partyId == static_cast<unsigned int>(-1)) {
        return 0;
    }
    GfObjAcc acc(handle);
    switch (acc.getType()) {
    case 3:
        return GfDataDriver::getPartyPos(acc.getDriverId());
    case 10:
        return getPartyPos(getMaster(handle));
    }
    return 0;
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

GfAssetResource* GfObjUtil::getResourceEab(GF_OBJ_HANDLE* handle) {
    switch (getObjType(handle)) {
    case 3:
    case 4:
        return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(62), static_cast<GfAssetType>(0));
    case 5:
    case 6:
    case 7:
        return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(10), static_cast<GfAssetType>(0));
    case 8:
        return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(4), static_cast<GfAssetType>(0));
    case 11:
    case 13:
    case 14:
    case 15:
        return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(3), static_cast<GfAssetType>(0));
    }
    return nullptr;
}

GfAssetResource* GfObjUtil::getResourceEfb(GF_OBJ_HANDLE* handle) {
    switch (getObjType(handle)) {
    case 3:
    case 4:
        return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(63), static_cast<GfAssetType>(0));
    case 5:
    case 6:
    case 7:
        return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(11), static_cast<GfAssetType>(0));
    case 8:
        return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(5), static_cast<GfAssetType>(0));
    case 11:
    case 13:
    case 14:
    case 15:
        return GfAssetManager::getResource(getAssetHandle(handle), static_cast<GfFileIdx>(4), static_cast<GfAssetType>(0));
    }
    return nullptr;
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

void GfObjUtil::copyTransformToSetup(GF_OBJ_HANDLE* handle, const mm::Vec3& pos, const mm::Vec3& rot) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_setup != nullptr) {
        GfObjSetup* setup = info->m_setup;
        setup->m_initialPos.x = pos.x;
        setup->m_initialPos.y = pos.y;
        setup->m_initialPos.z = pos.z;
        setup->pad_30.x = rot.x;
        setup->pad_30.y = rot.y;
        setup->pad_30.z = rot.z;
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

void GfObjUtil::saveRebuildInfo(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    GfObjSetup* setup = getObjSetup(handle);
    // the world rotation as angles (GfObjSetup::setInitialTransform's reading); only the yaw is kept
    const mm::Quat& q = acc.getWorldTransform().rotation;
    float x2 = q.x + q.x;
    float y2 = q.y + q.y;
    float z2 = q.z + q.z;
    float xx = q.x * x2;
    float xy = q.x * y2;
    float xz = q.x * z2;
    float yy = q.y * y2;
    float yz = q.y * z2;
    float zz = q.z * z2;
    float wx = q.w * x2;
    float wy = q.w * y2;
    float wz = q.w * z2;
    float m00 = 1.0f - (yy + zz);
    float m01 = xy + wz;
    float m02 = xz - wy;
    float m11 = 1.0f - (xx + zz);
    float m20 = xz + wy;
    float m21 = yz - wx;
    float m22 = 1.0f - (xx + yy);
    mm::Vec3 rot;
    rot.x = mm::asin(-m21);
    if (rot.x < 1.57079637f) {
        if (rot.x > -1.57079637f) {
            rot.z = ::atan2f(m01, m11);
            rot.y = ::atan2f(m20, m22);
        } else {
            rot.z = -::atan2f(m02, m00);
            rot.y = 0.0f;
        }
    } else {
        rot.z = ::atan2f(m02, m00);
        rot.y = 0.0f;
    }
    setup->m_initialPos = acc.getWorldTransform().position;
    setup->pad_30 = mm::Vec3(0.0f, rot.y, 0.0f);
    if (acc.getType() == 3) {
        GfObjSetupDriver* driver = nullptr;
        if (GFOBJ_INFO* info = GfObjManager::getObjInfo(handle)) {
            if (GfObjSetup* objSetup = info->m_setup) {
                if (objSetup->m_type == info->m_obj->m_type && info->m_obj->m_type == 3 &&
                    objSetup->getRTTI()->isKindOf(&GfObjSetupDriver::m_rtti)) {
                    driver = static_cast<GfObjSetupDriver*>(objSetup);
                }
            }
        }
        if (GfComPropertyPc* property = acc.getObj()->getComponent<GfComPropertyPc>(5)) {
            driver->pad_70 = property->m_setupKind;
        }
    } else if (acc.getType() == 4) {
        GfObjSetupBlade* blade = nullptr;
        if (GFOBJ_INFO* info = GfObjManager::getObjInfo(handle)) {
            if (GfObjSetup* objSetup = info->m_setup) {
                if (objSetup->m_type == info->m_obj->m_type && info->m_obj->m_type == 4 &&
                    objSetup->getRTTI()->isKindOf(&GfObjSetupBlade::m_rtti)) {
                    blade = static_cast<GfObjSetupBlade*>(objSetup);
                }
            }
        }
        if (GfComPropertyPc* property = acc.getObj()->getComponent<GfComPropertyPc>(5)) {
            blade->pad_74 = property->m_setupKind;
        }
    }
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

void GfObjUtil::setEnableAllIK(GF_OBJ_HANDLE* handle, bool enable, float time) {
    setEnableBodyIK(handle, enable, time);
    setEnableBlowRotateIK(handle, enable, time);
    setEnableLookIK(handle, enable, time);
    setEnableFootIK(handle, enable);
    setEnableSPCIK(handle, enable);
    setEnableEyeIK(handle, enable, time);
}

void GfObjUtil::setEnableBodyIK(GF_OBJ_HANDLE* handle, bool enable, float time) {
    if (GfObj* obj = getObj(handle)) {
        if (GfComIK* ik = obj->getComponent<GfComIK>(3)) {
            if (fw::RotateIkSolver* rotate = ik->getSolver<fw::RotateIkSolver>(0)) {
                if (enable) {
                    rotate->fadeIn(time);
                } else {
                    rotate->fadeOut(time);
                }
            }
            if (fw::SpineRotateIKSolver* spine = ik->getSolver<fw::SpineRotateIKSolver>(4)) {
                if (enable) {
                    spine->fadeIn(time);
                } else {
                    spine->fadeOut(time);
                }
            }
        }
    }
}

void GfObjUtil::setEnableBlowRotateIK(GF_OBJ_HANDLE* handle, bool enable, float time) {
    if (GfObj* obj = getObj(handle)) {
        if (GfComIK* ik = obj->getComponent<GfComIK>(3)) {
            if (fw::BlowRotateIkSolver* blow = ik->getSolver<fw::BlowRotateIkSolver>(1)) {
                if (enable) {
                    blow->fadeIn(time);
                } else {
                    blow->fadeOut(time);
                }
            }
        }
    }
}

void GfObjUtil::setEnableLookIK(GF_OBJ_HANDLE* handle, bool enable, float time) {
    if (GfObj* obj = getObj(handle)) {
        if (GfComIK* ik = obj->getComponent<GfComIK>(3)) {
            if (fw::LookIkSolver* look = ik->getSolver<fw::LookIkSolver>(3)) {
                if (enable) {
                    look->fadeIn(time);
                } else {
                    look->fadeOut(time);
                }
            }
            if (fw::SpineIkSolver* spine = ik->getSolver<fw::SpineIkSolver>(3)) {
                if (enable) {
                    spine->fadeIn(time);
                } else {
                    spine->fadeOut(time);
                }
            }
            if (fw::LookAtIkSolver* lookAt = ik->getSolver<fw::LookAtIkSolver>(5)) {
                if (enable) {
                    lookAt->fadeIn(time);
                } else {
                    lookAt->fadeOut(time);
                }
            }
        }
    }
}

void GfObjUtil::setEnableFootIK(GF_OBJ_HANDLE* handle, bool enable) {
    if (GfObj* obj = getObj(handle)) {
        if (GfComIK* ik = obj->getComponent<GfComIK>(3)) {
            if (fw::PlacementGroundSolver* placement = ik->getSolver<fw::PlacementGroundSolver>(2)) {
                placement->m_enableDown = enable;
                placement->setEnablePlacement(enable);
            }
            if (fw::SlopeGroundSolver* slope = ik->getSolver<fw::SlopeGroundSolver>(0)) {
                slope->setEnablePlacement(enable);
                slope->m_enableSlope = enable;
            }
            if (fw::TwoCharaGroundSolver* twoChara = ik->getSolver<fw::TwoCharaGroundSolver>(2)) {
                twoChara->m_enableDown = enable;
                twoChara->setEnablePlacement(enable);
            }
        }
    }
}

void GfObjUtil::setEnableSPCIK(GF_OBJ_HANDLE* handle, bool enable) {
    if (GfObj* obj = getObj(handle)) {
        if (GfComIK* ik = obj->getComponent<GfComIK>(3)) {
            if (fw::SphericalCoordinatesIkSolver* solver = ik->getSolver<fw::SphericalCoordinatesIkSolver>(8)) {
                enableSolver(solver, enable);
            }
        }
    }
}

void GfObjUtil::setEnableEyeIK(GF_OBJ_HANDLE* handle, bool enable, float time) {
    if (GfObj* obj = getObj(handle)) {
        if (GfComIK* ik = obj->getComponent<GfComIK>(3)) {
            int type = getEyeIKType(handle);
            if (enable) {
                if (type == 1) {
                    if (fw::TransLocalIkSolver* left = ik->getSolver<fw::TransLocalIkSolver>(6)) {
                        left->fadeIn(time);
                    }
                    if (fw::TransLocalIkSolver* right = ik->getSolver<fw::TransLocalIkSolver>(7)) {
                        right->fadeIn(time);
                    }
                } else if (type == 2) {
                    if (fw::RotateLocalIkSolver* left = ik->getSolver<fw::RotateLocalIkSolver>(6)) {
                        left->fadeIn(time);
                    }
                    if (fw::RotateLocalIkSolver* right = ik->getSolver<fw::RotateLocalIkSolver>(7)) {
                        right->fadeIn(time);
                    }
                }
            } else {
                if (type == 1) {
                    if (fw::TransLocalIkSolver* left = ik->getSolver<fw::TransLocalIkSolver>(6)) {
                        left->fadeOut(time);
                    }
                    if (fw::TransLocalIkSolver* right = ik->getSolver<fw::TransLocalIkSolver>(7)) {
                        right->fadeOut(time);
                    }
                } else if (type == 2) {
                    if (fw::RotateLocalIkSolver* left = ik->getSolver<fw::RotateLocalIkSolver>(6)) {
                        left->fadeOut(time);
                    }
                    if (fw::RotateLocalIkSolver* right = ik->getSolver<fw::RotateLocalIkSolver>(7)) {
                        right->fadeOut(time);
                    }
                }
            }
        }
    }
}

int GfObjUtil::getEyeIKType(GF_OBJ_HANDLE* handle) {
    if (GfObj* obj = getObj(handle)) {
        if (const GfComIK* ik = obj->getComponent<GfComIK>(3)) {
            size_t index = ik->m_solvers[6].get() != nullptr ? 6 : 7;
            if (ik->getSolver<fw::TransLocalIkSolver>(index) != nullptr) {
                return 1;
            }
            if (ik->getSolver<fw::RotateLocalIkSolver>(index) != nullptr) {
                return 2;
            }
        }
    }
    return 0;
}

unsigned int GfObjUtil::getEyeRotControl(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    return acc.getEyeRotControl();
}

void GfObjUtil::setBlowRotate(GF_OBJ_HANDLE* handle, const mm::Quat& rotation) {
    if (GfObj* obj = getObj(handle)) {
        if (GfComIK* ik = obj->getComponent<GfComIK>(3)) {
            if (fw::BlowRotateIkSolver* solver = ik->getSolver<fw::BlowRotateIkSolver>(1)) {
                solver->m_rotation = rotation;
            }
        }
    }
}

void GfObjUtil::setEnableEyeBlink(GF_OBJ_HANDLE* handle, bool enable) {
    if (GfObj* obj = getObj(handle)) {
        if (GfComBehavior* behavior = obj->getComponent<GfComBehavior>(6)) {
            if (EyeBlinkPlugin* plugin = behavior->getPlugin<EyeBlinkPlugin>(1)) {
                plugin->setActivate(enable);
            }
        }
    }
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

bool GfObjUtil::isBattle(GF_OBJ_HANDLE* handle) {
    bool found = false;
    bool battle;
    if (GfObjProperty* property = getProperty(handle)) {
        if (GfObjPropertyCharacter* character = property->m_character) {
            battle = character->pad_30;
            found = true;
        }
    }
    return found && battle;
}

bool GfObjUtil::isVolumeFadeForUser(GF_OBJ_HANDLE* handle) {
    return testFlag(GfObjManager::getObjInfo(handle), 20);
}

void GfObjUtil::createVolumeFade(GF_OBJ_HANDLE* handle) {
    GfObj* obj = GfObjManager::getObjInfo(handle)->m_obj;
    if (GfComModel* model = obj->getComponent<GfComModel>(1)) {
        GfObjSetup* setup = getObjSetup(handle);
        GFOBJ_INFO* info = GfObjManager::getObjInfo(obj->m_handle);
        info->createVolumeFade(model);
        if (info->m_volumeFade == nullptr) {
            return;
        }
        if (setup->pad_64 != -1) {
            setVolumeFadeUserFlag(handle, true);
            DataParamAcc acc(handle);
            info->m_volumeFade->setEffectType(VFEFF(acc.getAttribute(-1, false)));
            info->m_volumeFade->setFadeRatio(VFACC(setup->pad_64), VFPARTS(-1), 0.0f);
            setup->pad_64 = -1;
            ml::ScnObjAccEtcParams params(model->m_model->getInterface());
            if (params.getMax() != 0) {
                for (unsigned int i = 0; i < 6; i++) {
                    params.setInitParams(i, 1.0f);
                }
            }
        } else if (isEventCreateType(setup->m_createType)) {
            DataParamAcc acc(handle);
            if (acc.getObjType() == 4) {
                VFEFF type = VFEFF(acc.getAttribute(-1, false));
                if (type != 0) {
                    info->m_volumeFade->setEffectType(type);
                    info->m_volumeFade->applyFadeRatio();
                }
            }
        } else {
            DataParamAcc acc(handle);
            if (acc.getObjType() == 4 ||
                (acc.getObjType() == 3 &&
                 GfDataDriver::isIra(acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0)) ||
                (acc.getObjType() == 10 && GfDataUtil::isIra())) {
                VFEFF type = VFEFF(acc.getAttribute(-1, false));
                if (type != 0) {
                    info->m_volumeFade->setEffectType(type);
                    info->m_volumeFade->applyFadeRatio();
                }
            }
        }
    }
}

void GfObjUtil::setVolumeFadeUserFlag(GF_OBJ_HANDLE* handle, bool on) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info != nullptr && info->m_flags[20] != on) {
        info->m_flags.change(20, on);
    }
}

bool GfObjUtil::isSearchEmptyResource(GF_OBJ_HANDLE* handle) {
    GF_ASSET_HANDLE* asset = getAssetHandle(handle);
    if (GfAssetManager* manager = GfAssetManager::sys()) {
        return manager->isFullResource(asset);
    }
    return false;
}

bool GfObjUtil::isStanbyTalkingPlayer(GF_OBJ_HANDLE* handle) {
    GfGamePlayerFormation* formation = GfGamePlayerFormation::sys();
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return false;
    }
    GfObjProperty* property = info->m_property;
    if (formation == nullptr || property == nullptr) {
        return false;
    }
    GfObjProperty::TargetInfo* target = property->m_target;
    if (target == nullptr) {
        return false;
    }
    if (target->m_isMoving) {
        return false;
    }
    return !formation->isFarRandomTalk(handle);
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

namespace {
// whether a create type takes the sound category 3 (types 6, 7 and 12; the name is not the original's)
inline bool isCategory3CreateType(int type) {
    switch (type) {
    case 6:
    case 7:
    case 12:
        return true;
    default:
        return false;
    }
}
}  // namespace

unsigned int GfObjUtil::getSoundCategoryNormal(GF_OBJ_HANDLE* handle) {
    GfObjSetup* setup = getObjSetup(handle);
    if (setup != nullptr && isCategory3CreateType(setup->m_createType)) {
        return 3;
    }
    return 13;
}

unsigned int GfObjUtil::getSoundCategoryWithoutSlow(GF_OBJ_HANDLE* handle) {
    GfObjSetup* setup = getObjSetup(handle);
    if (setup != nullptr && isCategory3CreateType(setup->m_createType)) {
        return 3;
    }
    return 14;
}

bool GfObjUtil::getMobSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE*, 88>& slots, GF_OBJ_HANDLE* handle) {
    slots.clear();
    if (getObjType(handle) == 7) {
        GfAssetManager::getSlotHandle(slots, getAssetHandle(handle));
    }
    return !slots.empty();
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

bool GfObjUtil::isFollowObjNotReady(GF_OBJ_HANDLE* handle) {
    GfObjSetup* setup = getObjSetup(handle);
    if (setup == nullptr || setup->m_createType != 1) {
        return false;
    }
    int type = getObjType(handle);
    if (type != 3 && type != 4) {
        return false;
    }
    GfComPropertyPc* property = GfObjManager::getObjInfo(handle)->m_obj->findComponent<GfComPropertyPc>(5);
    if (property->m_setupKind == static_cast<unsigned int>(-1)) {
        return false;
    }
    GfGamePlayerFormation* formation = GfGamePlayerFormation::sys();
    unsigned int follow = formation->m_players[property->m_setupKind].m_followIndex;
    if (follow == static_cast<unsigned int>(-1)) {
        return false;
    }
    GfObjAcc acc(formation->m_players[follow].m_handle);
    return acc.m_obj == nullptr || acc.isRebuild() || acc.isReload();
}

void GfObjUtil::setWarpTransform(GF_OBJ_HANDLE* handle, const fw::Transform& transform, bool notify) {
    if (GfObj* obj = getObj(handle)) {
        if (notify) {
            MsgUnk_1000007 msg;
            obj->sendMessage(obj, msg);
        }
        if (GfComTransform* com = obj->getComponent<GfComTransform>(0)) {
            com->setPosition(transform.position);
            com->setRotation(transform.rotation);
        }
        if (GfComDynamics* dynamics = obj->getComponent<GfComDynamics>(8)) {
            dynamics->resetMovement();
        }
    }
}

void GfObjUtil::setDeadParticle(GF_OBJ_HANDLE* handle, bool on, unsigned int particle, float alpha) {
    GfObjAcc acc(handle);
    ml::ScnObjModel* model = acc.getScnModel();
    if (particle != 0 && model != nullptr) {
        ml::MdlVtxParticle params;
        memcpy(&params, fw::EffectManager::sys()->m_particleParams[particle], 0x30);
        params.m_alpha = alpha;
        ml::ScnObjAccMdlParticle access(acc.getScnModel());
        access.setParams(params);
        access.setActive(on, 0x1000);
    }
}

void GfObjUtil::applyExecUpdate(GF_OBJ_HANDLE* handle) {
    applyExecUpdate(getObj(handle));
}

int GfObjUtil::getSetupObjNumberByEnArrangeId(unsigned int arrangeId) {
    if (GfObjManager* manager = GfObjManager::sys()) {
        int loading = fn_7100552C18(manager->getLoadingObj(), arrangeId);
        return fn_7100552C18(manager->getDestroyObj(), arrangeId) + loading;
    }
    return 0;
}

int GfObjUtil::fn_7100552C18(const GfObjManager::HandleList& list, unsigned int arrangeId) {
    int count = 0;
    for (GfObjManager::HandleList::const_iterator it = list.begin(); it != list.end(); ++it) {
        DataParamAcc acc(*it);
        if (acc.getObjType() == 5) {
            unsigned int bdatId = acc.isValid() ? acc.getBdatId() : 0;
            if (bdatId == arrangeId) {
                count++;
            }
        }
    }
    return count;
}

void GfObjUtil::replaceColisionPrio(GF_OBJ_HANDLE* handle) {
    GfGamePlayerFormation* formation = GfGamePlayerFormation::sys();
    if (formation == nullptr) {
        return;
    }
    unsigned int index = formation->findPlayer(handle);
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1) || index == static_cast<unsigned int>(-1)) {
        return;
    }
    if (GfObj* obj = getObj(handle)) {
        if (GfComCollider* collider = obj->getComponent<GfComCollider>(4)) {
            if (fw::ColiObject* coli = collider->getColiObject(0)) {
                obj->m_info->m_attachIndex = GfDataUtil::getPlayerColiPriority(index);
                coli->setPriority(obj->m_info->m_attachIndex);
            }
        }
    }
}

bool GfObjUtil::isIra(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    if (acc.getObjType() == 3) {
        unsigned int id = acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0;
        return GfDataDriver::isIra(id);
    }
    return false;
}

bool GfObjUtil::isGhost(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    return !acc.isDisp(OBJDISP(0x40)) || !acc.isDisp(OBJDISP(2));
}

bool GfObjUtil::isDummyMover(GF_OBJ_HANDLE* handle) {
    GfObj* obj = getObj(handle);
    if (obj != nullptr && obj->m_type == 11) {
        return getAssetHandle(handle) == reinterpret_cast<GF_ASSET_HANDLE*>(-1);
    }
    return false;
}

void bindPadResources() {
    if (fw::PadResEventManager* manager = fw::PadResEventManager::sys()) {
        manager->setup(5, getAllocator(ALLOCATOR(0)));
        if (fw::CommonResource* resource = GfStaticRes::search("/param/pad.pdp")) {
            arc::CArcData arc(resource->getAssetData());
            fw::PadResEventManager::setResource(0, fw::PadEventImporter::create(arc.getFileAdr("field.pad"),
                                                                               "T:/BF2/param/pad/data/field.pdml"));
            fw::PadResEventManager::setResource(1, fw::PadEventImporter::create(arc.getFileAdr("battle.pad"),
                                                                               "T:/BF2/param/pad/data/battle.pdml"));
            fw::PadResEventManager::setResource(2, fw::PadEventImporter::create(arc.getFileAdr("camera.pad"),
                                                                               "T:/BF2/param/pad/data/camera.pdml"));
            fw::PadResEventManager::setResource(3, fw::PadEventImporter::create(arc.getFileAdr("target.pad"),
                                                                               "T:/BF2/param/pad/data/target.pdml"));
            fw::PadResEventManager::setResource(4, fw::PadEventImporter::create(arc.getFileAdr("system.pad"),
                                                                               "T:/BF2/param/pad/data/system.pdml"));
        }
    }
}

void unbindPadResource() {
    if (fw::PadResEventManager* manager = fw::PadResEventManager::sys()) {
        for (unsigned int i = 0; i < 5; i++) {
            fw::PadResEventManager::setResource(i, nullptr);
        }
        manager->cleanup();
    }
}

}  // namespace gf
