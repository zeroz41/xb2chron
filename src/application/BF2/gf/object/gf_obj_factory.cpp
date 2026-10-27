#include "classes/gf/GfInitParamNpc.h"
#include "gf/GfDataNpc.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfInitParam.h"
#include "classes/gf/GfInitParamGimmick.h"
#include "classes/gf/GfInitParamMapLodAnim.h"
#include "classes/gf/GfInitParamMob.h"
#include "gf/GfObjFactory.h"
#include "gf/GfAppendUtil.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfInitParamBelonging.h"
#include "classes/gf/GfInitParamExtra.h"
#include "classes/gf/GfInitParamEventObj.h"
#include "classes/gf/GfInitParamUiObj.h"
#include "classes/gf/GfObjSetupEventObj.h"
#include "gf/GfObjInfo.h"
#include "gf/GfObjUtil.h"
#include "gf/GfObjAcc.h"
#include "gf/GfAssetFactory.h"
#include "gf/AssetPackInfo.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfFobjDropitem.h"
#include "classes/gf/GfFobjManager.h"
#include "classes/gf/GfInitParamEnWeapon.h"
#include "classes/gf/GfInitParamFobj.h"
#include "classes/gf/GfInitParamGimmick.h"
#include "classes/gf/GfInitParamMapLodAnim.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfInitParamMob.h"
#include "classes/gf/GfGameManager.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "gf/SDataEnemy.h"
#include "classes/gf/GfInitParamMapSeamless.h"
#include "classes/gf/GfMapManager.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/gf/GfInitParamNpc.h"
#include "classes/gf/GfObjSetupNpc.h"
#include "classes/gf/GfObjSetupGimmick.h"
#include "gf/GfDataNpc.h"
#include "mm/mtl/FixStr.h"

#define GF_OBJ_FACTORY_PATH "D:/Monolithsoft/BF2/prog/application/BF2/gf/object/gf_obj_factory.cpp"

namespace gf {

namespace {
// what every create function does with a new object's info: its view, asset and the object it follows (the
// name is not the original's; the original's code is inline in each caller)
inline void setupObjInfo(GF_OBJ_HANDLE* handle, GF_ASSET_HANDLE* asset, const GfInitParam& param) {
    GFOBJ_INFO* info;
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && (info = GfObjManager::getObjInfo(handle)) != nullptr) {
        info->m_view = param.pad_24;
        info->m_assetHandle = asset;
        info->m_subHandle = param.pad_38;
        if (GfObjManager::sys() != nullptr && param.pad_38 != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            GfObjManager::sys()->addFollowObj(handle);
        }
        if (AssetPackInfo* pack = GfAssetManager::getAssetPackInfo(asset)) {
            pack->m_objHandle = handle;
        }
    }
}
// an object's setup as T when the setup and the object are of the given type, null otherwise (the name is not
// the original's; the original's code is inline in each caller)
template <class T>
inline T* getSetupOf(GFOBJ_INFO* info, int type) {
    if (info == nullptr || info->m_setup == nullptr) {
        return nullptr;
    }
    GfObjSetup* setup = info->m_setup;
    GfObj* obj = info->m_obj;
    if (setup->m_type == static_cast<int>(obj->m_type) && type == static_cast<int>(obj->m_type)) {
        return setup->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T*>(setup) : nullptr;
    }
    return nullptr;
}
// the create types GfAssetFactory makes event setups for (the name is not the original's)
inline bool isEventCreateType(int type) {
    switch (type) {
    case 2:
    case 3:
    case 11:
        return true;
    default:
        return false;
    }
}

// the create types 10 to 13 (the name is not the original's)
inline bool isEventActCreateType(int type) {
    return type >= 10 && type <= 13;
}
}  // namespace

GF_OBJ_HANDLE* GfObjFactory::createMap(const GfInitParamMapSeamless& param) {
    GfObjManager* manager = GfObjManager::sys();
    GF_ASSET_HANDLE* asset;
    if (manager == nullptr || GfMapManager::getGfObjHandle() != reinterpret_cast<GF_OBJ_HANDLE*>(-1) ||
        (asset = GfAssetFactory::createAssetPackMap(param)) == reinterpret_cast<GF_ASSET_HANDLE*>(-1)) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_OBJ_HANDLE* handle = manager->createGfObj(1, param);
    setupObjInfo(handle, asset, param);
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    GfObjUtil::addDebugName(handle);
    if (GfObj* obj = GfObjUtil::getObj(handle)) {
        obj->setUpdateComponent(true);
    }
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createMapLodAnim() {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GfInitParamMapLodAnim param;
    param.pad_40 = 0;
    GF_OBJ_HANDLE* handle = manager->createGfObj(2, param);
    GfObjSetup::createSetupParam(handle, param);
    manager->addHandle(handle);
    GfObjAcc acc(handle);
    acc.setCameraFade(false);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createGmkMapObj(const CBdatWrapper& bdat, int row) {
    unsigned char* fp = GfDataBdat::getFP(0xAB);
    unsigned short rscId = Bdat::getValCheck(bdat.m_fp, "RSC_ID", row, 2);
    GfInitParamGimmick param;
    param.m_objId = rscId;
    param.m_gimmickType = GimmickType(0);
    param.pad_18 = &fp;
    param.pad_44 = static_cast<unsigned char>(Bdat::getValCheck(bdat.m_fp, "Priority", row, 1));
    param.pad_90 = reinterpret_cast<void*>(Bdat::getValCheck(bdat.m_fp, "name", row, 7));
    param.pad_98 = Bdat::getFlagVal(fp, "flag", rscId, "BigObj") != 0;
    GF_OBJ_HANDLE* handle = createMapObj(param);
    GfObjSetupGimmick* setup = getSetupOf<GfObjSetupGimmick>(GfObjManager::getObjInfo(handle), 8);
    const char* state = reinterpret_cast<const char*>(Bdat::getValCheck(bdat.m_fp, "StateName", row, 7));
    if (state != nullptr && state[0] != '\0') {
        setup->m_stateName = state;
    }
    if (Bdat::getMember(bdat.m_fp, "mapobjcol") != nullptr) {
        setup->pad_a0 = Bdat::getFlagVal(bdat.m_fp, "flag", row, "mapobjcol") == 0;
    }
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createMapObj(const GfInitParamGimmick& param) {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_ASSET_HANDLE* asset = GfAssetFactory::createAssetPackGimmick(param);
    GF_OBJ_HANDLE* handle = manager->createGfObj(8, param);
    setupObjInfo(handle, asset, param);
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    GfObjUtil::addDebugName(handle);
    GfObjAcc acc(handle);
    acc.setCameraFade(false);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createGmkTbox(const CBdatWrapper& bdat, int row) {
    unsigned char* fp = GfDataBdat::getFP(0xAC);
    unsigned short rscId = Bdat::getValCheck(bdat.m_fp, "RSC_ID", row, 2);
    GfInitParamGimmick param;
    param.m_objId = rscId;
    param.pad_18 = &fp;
    param.m_gimmickType = GimmickType(1);
    return createMapObj(param);
}

GF_OBJ_HANDLE* GfObjFactory::createGmkNpc(const CBdatWrapper& bdat, int row) {
    if (GfObjManager::sys() == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    unsigned short npcId = Bdat::getValCheck(bdat.m_fp, "NpcID", row, 2);
    unsigned char* fp = GfDataNpc::getRscBdatFp(npcId);
    GfInitParamNpc param;
    param.m_objId = npcId;
    param.pad_18 = &fp;
    param.pad_a0[0] = Bdat::getValCheck(bdat.m_fp, "MountPoint", row, 2);
    param.pad_a0[1] = Bdat::getValCheck(bdat.m_fp, "MountObject", row, 2);
    if (GfGameManager::fn_71002A9E68()) {
        param.pad_a0[2] = Bdat::getValCheck(bdat.m_fp, "MountPoint2", row, 2);
        param.pad_a0[3] = Bdat::getValCheck(bdat.m_fp, "MountObject2", row, 2);
    }
    param.pad_90 = true;
    param.pad_98 = reinterpret_cast<void*>(Bdat::getValCheck(bdat.m_fp, "name", row, 7));
    GF_OBJ_HANDLE* handle = createNpc(param);
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GfObjSetupNpc* setup = getSetupOf<GfObjSetupNpc>(GfObjManager::getObjInfo(handle), 6);
    unsigned short mot = Bdat::getValCheck(bdat.m_fp, "Mot", row, 2);
    if (mot) {
        int id = mot;
        const char* name = reinterpret_cast<const char*>(
            Bdat::getValCheck(Bdat::getFP("FLD_NpcMobMotionId"), "cmdName", id, 7));
        setup->m_stateName = name;
        if (setup->m_stateName.length() != 0) {
            setup->m_stateName[0] = 'S';
        }
    }
    unsigned short group = Bdat::getValCheck(bdat.m_fp, "Group", row, 2);
    if (group != 0) {
        unsigned char num = Bdat::getValCheck(Bdat::getFP("FLD_NpcGroupId"), "memberNum", group, 1);
        if (num) {
            unsigned int count = num;
            GfObjManager::sys()->setMultiBind(handle, group, count, false);
        }
    }
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createGmkMob(int id, unsigned short a, unsigned short b, unsigned short c,
                                          unsigned short d) {
    unsigned char* fp = GfDataBdat::getFP(0xAA);
    GfInitParamMob param;
    param.m_objId = id;
    param.pad_18 = &fp;
    param.pad_90[0] = a;
    param.pad_90[1] = b;
    param.pad_90[2] = c;
    param.pad_90[3] = d;
    return createMob(param);
}

GF_OBJ_HANDLE* GfObjFactory::createMobNull() {
    GfInitParamMob param;
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr || GfGameManager::isAssetNumberInvalid()) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_OBJ_HANDLE* handle = manager->createGfObj(7, param);
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createSmnEnemy(int id, const mm::Vec3& pos, const mm::Vec3& rot, bool flag) {
    GF_OBJ_HANDLE* handle = createGmkEnemy(id, 0, 0, pos, rot, flag);
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    {
        DataParamAcc acc(handle);
        if (acc.getSDataEnemy()->m_named) {
            GfObjUtil::destroy(handle);
            return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
        }
    }
    GfObjSetupEnemy* setup = mm::mtl::rttiCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(handle)->m_setup);
    setup->pad_b2 = 1;
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createGmkEvent(const CBdatWrapper& bdat, int row) {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GfInitParamGimmick param;
    param.m_objId = row;
    param.pad_90 = reinterpret_cast<void*>(Bdat::getValCheck(bdat.m_fp, "name", row, 7));
    GF_OBJ_HANDLE* handle = manager->createGfObj(8, param);
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    GfObjUtil::addDebugName(handle);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createGmkCollection(const CBdatWrapper& bdat, int row) {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GfInitParamGimmick param;
    param.m_objId = row;
    param.pad_90 = reinterpret_cast<void*>(Bdat::getValCheck(bdat.m_fp, "name", row, 7));
    GF_OBJ_HANDLE* handle = manager->createGfObj(8, param);
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    GfObjUtil::addDebugName(handle);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createGmkMapGimmick(const CBdatWrapper& bdat, int row) {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GfInitParamGimmick param;
    param.m_objId = row;
    param.pad_90 = reinterpret_cast<void*>(Bdat::getValCheck(bdat.m_fp, "name", row, 7));
    param.pad_40 = 0;
    GF_OBJ_HANDLE* handle = manager->createGfObj(8, param);
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    GfObjUtil::addDebugName(handle);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createFieldObj(const GfInitParamFobj& param) {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_ASSET_HANDLE* asset = GfAssetFactory::createAssetPackFobj(param);
    GF_OBJ_HANDLE* handle = manager->createGfObj(9, param);
    setupObjInfo(handle, asset, param);
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    GfObjUtil::addDebugName(handle);
    if (param.m_isDropItem) {
        GfFobjDropitem* item = new (getAllocator(ALLOCATOR(0)), GF_OBJ_FACTORY_PATH, 2705, 8) GfFobjDropitem(handle);
        GfFobjManager::registFiledObj(item);
    }
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createEnWeapon(GfInitParamEnWeapon& param) {
    GfObjManager* manager = GfObjManager::sys();
    GF_ASSET_HANDLE* asset;
    if (manager == nullptr ||
        (asset = GfAssetFactory::createAssetPackEnWeapon(param)) == reinterpret_cast<GF_ASSET_HANDLE*>(-1)) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_OBJ_HANDLE* handle = manager->createGfObj(12, param);
    setupObjInfo(handle, asset, param);
    unsigned short mountIndex = param.m_append.getMountIndex();
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        if (GFOBJ_INFO* info = GfObjManager::getObjInfo(handle)) {
            info->m_mounts[0].m_appendIndex = mountIndex;
        }
    }
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    if (isEventCreateType(param.m_createType) || isEventActCreateType(param.m_createType)) {
        GfAppendUtil::setupEventActEnemy(param.m_attach, handle, param.getEnArrangeID());
    } else {
        GfAppendUtil::setupEnemy(param.m_attach, handle, param.getEnArrangeID(), param.m_ownerHandle);
    }
    GfObjUtil::addDebugName(handle);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createBelonging(GfInitParamBelonging& param) {
    GfObjManager* manager = GfObjManager::sys();
    GF_ASSET_HANDLE* asset;
    if (manager == nullptr ||
        (asset = GfAssetFactory::createAssetPackBelonging(param)) == reinterpret_cast<GF_ASSET_HANDLE*>(-1)) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_OBJ_HANDLE* handle = manager->createGfObj(13, param);
    setupObjInfo(handle, asset, param);
    unsigned short mountIndex = param.m_append.getMountIndex();
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        if (GFOBJ_INFO* info = GfObjManager::getObjInfo(handle)) {
            info->m_mounts[2].m_appendIndex = mountIndex;
        }
    }
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    if (param.m_isForDriver) {
        GfAppendUtil::setupBelongingForDriver(handle, *param.m_driverParam);
    } else {
        GfAppendUtil::setupBelonging(handle, param.m_belongingValues[0], param.m_belongingValues[1],
                                     param.m_belongingValues[2], param.m_belongingValues[3]);
    }
    GfObjUtil::addDebugName(handle);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createExtraModel(GfInitParamExtra& param) {
    GfObjManager* manager = GfObjManager::sys();
    GF_ASSET_HANDLE* asset;
    if (manager == nullptr ||
        (asset = GfAssetFactory::createAssetPackExtra(param)) == reinterpret_cast<GF_ASSET_HANDLE*>(-1)) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_OBJ_HANDLE* handle = manager->createGfObj(14, param);
    setupObjInfo(handle, asset, param);
    unsigned short mountIndex = param.m_append.getMountIndex();
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        if (GFOBJ_INFO* info = GfObjManager::getObjInfo(handle)) {
            info->m_mounts[1].m_appendIndex = mountIndex;
        }
    }
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    GfAppendUtil::setupExtraModel(handle, param.pad_38);
    GfObjUtil::addDebugName(handle);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createEventObj(const GfInitParamEventObj& param) {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_ASSET_HANDLE* asset = GfAssetFactory::createAssetPackEventObj(param);
    GF_OBJ_HANDLE* handle = manager->createGfObj(11, param);
    setupObjInfo(handle, asset, param);
    manager->addHandle(handle);
    GfObjSetupEventObj* setup = static_cast<GfObjSetupEventObj*>(GfObjSetup::createSetupParam(handle, param));
    GfAssetManager::setModelInfo(asset, setup->m_arcName.m_str);
    GfObjUtil::addDebugName(handle);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createUiObj(const GfInitParamUiObj& param) {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_ASSET_HANDLE* asset = GfAssetFactory::createAssetPackUiObj(param);
    GF_OBJ_HANDLE* handle = manager->createGfObj(15, param);
    setupObjInfo(handle, asset, param);
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    GfObjUtil::addDebugName(handle);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

bool GfObjFactory::destroyObjHandle(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfAssetManager::destroy(info->m_assetHandle);
    info->m_assetHandle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
    if (GfObjManager* manager = GfObjManager::sys()) {
        manager->callGfObjListener(IGfObjListener::OBJEVT(4), handle);
    }
    if (info->m_obj != nullptr) {
        info->m_obj->setTerminate();
        info->m_obj = nullptr;
    }
    return true;
}

void GfObjFactory::destroyObj(GF_OBJ_HANDLE* handle) {
    GfObjUtil::destroy(handle);
}

unsigned int GfInitParamEnWeapon::getEnArrangeID() const {
    return m_enArrangeId;
}

}  // namespace gf
