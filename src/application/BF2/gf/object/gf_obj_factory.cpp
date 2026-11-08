#include "gf/GfObjFactory.h"
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
#include "classes/gf/GfMountManager.h"
#include "classes/gf/GfAppendHandles.h"
#include "gf/GFATTACH.h"
#include "gf/GfDataMob.h"
#include "classes/gf/GfInitParamEnemy.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "gf/GfDataDriver.h"
#include "classes/gf/GfObjSetupWeapon.h"
#include "classes/gf/GfObjSetupBlade.h"
#include "classes/gf/GfObjSetupDriver.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfInitParamWeapon.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfComSound.h"
#include "classes/gf/GfComProperty.h"
#include "gf/GfEnvProperty.h"
#include "fw/SoundResTrigger.h"
#include "classes/fw/SoundResSourceManager.h"
#include "classes/gf/GfExtendPacking.h"
#include "classes/gf/GfAssetResource.h"
#include "arc/CArcData.h"
#include "classes/gf/GfBdatChrBl.h"
#include "classes/gf/GfBdatChrDr.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "anm/SkeletonImporter.h"
#include "gf/GfUtil.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfAssetPack.h"
#include "classes/gf/GfComEffectCaster.h"
#include "classes/gf/GfComTransform.h"
#include "classes/gf/GfComDynamics.h"
#include "skd/DynamicsImporter.h"
#include <math.h>
#include <string.h>

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

// the create types 10 to 13 (the name is not the original's)
inline bool isEventActCreateType(int type) {
    return type >= 10 && type <= 13;
}
// the setup's pad_68 for an object's race (GfDataMob::getRace's): 1..10 to 0, 4, 1, 3, 5..10, else -1; createDriver,
// createBlade, createNpc, createMob and createEnemy share the switch's table (the name is not the original's)
inline int getRaceType(unsigned int race) {
    switch (race) {
    case 1:
        return 0;
    case 2:
        return 4;
    case 3:
        return 1;
    case 4:
        return 3;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;
    case 8:
        return 8;
    case 9:
        return 9;
    case 10:
        return 10;
    default:
        return -1;
    }
}
}  // namespace

bool checkSoundTriggerPlayer(GfComSound* sound, const fw::ResSoundTriggerInfo& info) {
    const char* name = info.m_stateName;
    if (strcmp(name, "S_jump_02") == 0 || strcmp(name, "S_jumpdmg") == 0) {
        GfComProperty* property = sound->m_owner->findComponent<GfComProperty>(5);
        const GfEnvProperty* env = property->m_env.get();
        const GfEnvProperty::Ground* ground = env->getGround(0);
        if ((env->m_flags & 1) != 0 && ground != nullptr) {
            return !(ground->m_position.y <= env->m_water.m_height);
        }
    }
    return true;
}

void fn_7100526BD8(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    unsigned int weapon = acc.getEquipWeapon(-1, false);
    if (acc.getBlade(-1, false) != 0) {
        GfObjSetup* setup = GfObjUtil::getObjSetup(handle);
        if (GfObjUtil::getMountHandle(handle, GFATTACH(0)) == reinterpret_cast<GF_MOUNT_HANDLE*>(-1)) {
            GfMountManager::addMountHandle(GfMountManager::createMount(handle, handle, GFATTACH(0), OPTMNT(1)), handle);
        }
        GfInitParamWeapon param;
        unsigned int value = setup->pad_18;
        param.m_createType = 7;
        param.m_objId = weapon;
        param.pad_120 = handle;
        param.pad_24 = value;
        param.pad_90 = false;
        param.pad_40 = 12;
        param.pad_81 = false;
        param.pad_30 = handle;
        param.pad_38 = handle;
        GfObjFactory::createDriverWeapon(param);
    }
}

void fn_7100527120(GfInitParamDriver& driver, GF_OBJ_HANDLE* handle) {
    unsigned int blade = driver.m_bladeId;
    if (blade == 0) {
        blade = GfDataDriver::getBlade(driver.m_objId, -1);
    }
    DataParamAcc acc(4, blade, GimmickType(0));
    if (GfObjUtil::getMountHandle(handle, GFATTACH(0)) == reinterpret_cast<GF_MOUNT_HANDLE*>(-1)) {
        GfMountManager::addMountHandle(GfMountManager::createMount(handle, handle, GFATTACH(0), OPTMNT(2)), handle);
    }
    if (acc.getEquipWeapon(-1, false) != 0) {
        GfInitParamWeapon param;
        int type = driver.m_createType == 3 ? 3 : 2;
        if (driver.m_createType - 10U < 4) {
            type = 11;
        }
        param.m_createType = type;
        param.m_objId = acc.getEquipWeapon(-1, false);
        param.pad_90 = false;
        param.pad_40 = 9;
        param.pad_120 = handle;
        param.pad_12c = blade;
        param.pad_30 = handle;
        param.pad_38 = handle;
        if (driver.pad_83) {
            param.pad_83 = true;
        }
        GfObjFactory::createDriverWeapon(param);
    }
}

GF_OBJ_HANDLE* GfObjFactory::createNpc(const GfInitParamNpc& param) {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr || GfGameManager::isAssetNumberInvalid()) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_OBJ_HANDLE* handle = manager->createGfObj(6, param);
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    const char* model = GfDataNpc::getModelName(param.m_objId);
    if (model != nullptr && *model != '\0') {
        GF_ASSET_HANDLE* asset = GfAssetFactory::createAssetPackNpc(param);
        setupObjInfo(handle, asset, param);
    }
    manager->addHandle(handle);
    GfObjSetup* setup = GfObjSetup::createSetupParam(handle, param);
    setup->setInitialScale(GfDataNpc::getScale(param.m_objId));
    if (setup->m_initialScale.x == 0.0f) {
        setup->setInitialScale(1.0f);
    }
    setup->pad_68 = getRaceType(GfDataNpc::getRace(param.m_objId));
    GfObjUtil::addDebugName(handle);
    fn_7100528684(handle, param.pad_a0[0], param.pad_a0[1], param.pad_a0[2], param.pad_a0[3]);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

GF_OBJ_HANDLE* GfObjFactory::createMob(const GfInitParamMob& param) {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr || GfGameManager::isAssetNumberInvalid()) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_OBJ_HANDLE* handle = manager->createGfObj(7, param);
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GF_ASSET_HANDLE* asset = GfAssetFactory::createAssetPackMob(param);
    setupObjInfo(handle, asset, param);
    manager->addHandle(handle);
    GfObjSetup* setup = GfObjSetup::createSetupParam(handle, param);
    setup->pad_68 = getRaceType(GfDataMob::getRace(param.m_objId));
    GfObjUtil::addDebugName(handle);
    fn_7100528684(handle, param.pad_90[0], param.pad_90[1], param.pad_90[2], param.pad_90[3]);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

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

GF_OBJ_HANDLE* GfObjFactory::createGmkTboxBattleChallenge(const CBdatWrapper&, int, int id) {
    unsigned char* fp = GfDataBdat::getFP(0xAC);
    GfInitParamGimmick param;
    param.m_objId = id;
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
    if (GfGameManager::isGameTypeIra()) {
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

GF_OBJ_HANDLE* GfObjFactory::createGmkEnemy(int id, signed char a, unsigned short b, const mm::Vec3& pos,
                                            const mm::Vec3& rot, bool flag) {
    GfBdatChrEnArrange* arrange = GfBdatChrEnArrange::sys();
    unsigned char* paramFp = GfDataBdat::getFP(0x8C);
    unsigned char* fp = GfDataBdat::getFP(0xA5);
    unsigned short paramId = arrange->getChrEnArrangeParamID(id);
    unsigned short rscId = Bdat::getValCheck(paramFp, "ResourceID", paramId, 2);
    unsigned int level = static_cast<unsigned short>(arrange->getChrEnArrangeLv(id)) + a;
    GfInitParamEnemy param;
    param.m_paramId = paramId;
    param.m_arrangeId = id;
    param.pad_81 = flag;
    param.m_objId = rscId;
    param.pad_44 = b;
    param.pad_ae = a;
    param.pad_18 = &fp;
    param.pad_ac = static_cast<int>(level) < 1 ? 1 : (level > 999 ? 999 : level);
    param.m_initialPos = pos;
    param.pad_70 = rot;
    param.m_hasTransform = true;
    if (GfGameManager::isGameTypeIra() && GfGameManager::isScenarioGame() && GfGameManager::isClearGame() &&
        param.m_arrangeId == 0x5A8) {
        unsigned int lv = GfDataDriver::getLevel(0x11);
        unsigned int lv2 = GfDataDriver::getLevel(0x12);
        lv = lv < lv2 ? lv : lv2;
        unsigned int lv3 = GfDataDriver::getLevel(0x13);
        param.pad_ac = lv < lv3 ? lv : lv3;
    }
    GF_OBJ_HANDLE* handle = createEnemy(param);
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GfObjSetupEnemy* setup = mm::mtl::rttiCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(handle)->m_setup);
    setup->m_enArrangeId = id;
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

GF_OBJ_HANDLE* GfObjFactory::createGmkBlade(const CBdatWrapper& bdat, int row, int index) {
    if (GfDataBlade::isCommonBlade(index)) {
        GfInitParamNpc param;
        param.m_objId = index;
        param.pad_90 = true;
        param.pad_98 = const_cast<char*>(GfDataBlade::getDebugName(index));
        return createNpc(param);
    }
    unsigned char* fp = GfDataNpc::getRscBdatFp(index);
    GfInitParamNpc param;
    param.m_objId = index;
    param.pad_18 = &fp;
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

GfAppendHandles* GfObjFactory::createDriverWeapon(GfInitParamWeapon& param) {
    GfAppendInfo info;
    DataParamAcc acc(param.pad_120);
    GfAppendInfo* appendInfo;
    if (GfDataDriver::isIra(acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0)) {
        appendInfo = GfObjUtil::getAppendInfo(param.pad_38, GFATTACH(param.pad_1e4));
    } else if (param.pad_120 != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        unsigned int driver = acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0;
        unsigned int blade = param.pad_12c;
        if (blade == 0) {
            blade = acc.getBlade(param.pad_94, false);
        }
        param.pad_128 = acc.isValid() && acc.getObjType() == 3 ? acc.getBdatId() : 0;
        GfAppendUtil::setupPartyBlade(GFATTACH(param.pad_1e4), param.pad_38, param.m_objId, driver, blade);
        appendInfo = GfObjUtil::getAppendInfo(param.pad_38, GFATTACH(param.pad_1e4));
    } else if (param.pad_30 == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        DataParamAcc driverAcc(3, param.pad_128, GimmickType(0));
        unsigned int blade = param.pad_12c;
        if (blade == 0) {
            blade = driverAcc.getBlade(param.pad_94, false);
        }
        GfAppendUtil::setupWeapon(GFATTACH(param.pad_1e4), info, param.m_objId, param.pad_128, blade,
                                  isEventActCreateType(param.m_createType));
        appendInfo = &info;
    } else {
        DataParamAcc driverAcc(param.pad_30);
        unsigned int blade = param.pad_12c;
        if (blade == 0) {
            blade = driverAcc.getBlade(param.pad_94, false);
        }
        if (driverAcc.getObjType() == 3) {
            param.pad_128 = driverAcc.isValid() && driverAcc.getObjType() == 3 ? driverAcc.getBdatId() : 0;
        }
        GfAppendUtil::setupWeapon(GFATTACH(param.pad_1e4), info, param.m_objId, param.pad_128, blade,
                                  isEventActCreateType(param.m_createType));
        appendInfo = &info;
    }
    GfAppendHandles* handles = GfMountManager::getAppendHandles(param.pad_38, GFATTACH(param.pad_1e4));
    if (handles == nullptr) {
        handles = &param.pad_130;
    } else {
        GF_OBJ_HANDLE* const* objs = handles->getObjHandles();
        for (int i = 0; i < 10; i++) {
            if (objs[i] != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                return handles;
            }
        }
    }
    bool second = appendInfo->m_list != 0;
    appendInfo->m_list = 1;
    handles->m_useSecond = true;
    fn_710052A760(*handles, param, *appendInfo);
    appendInfo->m_list = 0;
    handles->m_useSecond = false;
    fn_710052A760(*handles, param, *appendInfo);
    appendInfo->m_list = second;
    handles->m_useSecond = second;
    return handles;
}

GfAppendHandles* GfObjFactory::createEnemyBladeWeapon(GfInitParamWeapon& param, unsigned int id, GF_OBJ_HANDLE* owner,
                                                      GF_OBJ_HANDLE* blade) {
    if (param.pad_1e8) {
        GfAppendUtil::setupEnemyBladeWithNoDriver(GFATTACH(param.pad_1e4), param.pad_38, param.pad_12c, blade);
    } else {
        GfAppendUtil::setupEnemyBlade(GFATTACH(param.pad_1e4), param.pad_38, id, owner, blade);
    }
    GfAppendInfo* found = GfObjUtil::getAppendInfo(param.pad_38, GFATTACH(param.pad_1e4));
    GfAppendInfo info;
    GfAppendInfo* appendInfo = found == nullptr ? &info : found;
    GfAppendHandles* handles = GfMountManager::getAppendHandles(param.pad_38, GFATTACH(param.pad_1e4));
    if (handles == nullptr) {
        handles = &param.pad_130;
    } else {
        GF_OBJ_HANDLE* const* objs = handles->getObjHandles();
        for (int i = 0; i < 10; i++) {
            if (objs[i] != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                return handles;
            }
        }
    }
    for (unsigned int i = 0; i < static_cast<unsigned int>(appendInfo->m_appends[appendInfo->m_list].size()); i++) {
        param.pad_98 = *appendInfo->m_appends[appendInfo->m_list][i];
        GF_OBJ_HANDLE* handle = fn_710052AD9C(param, owner, blade);
        if (handles != nullptr) {
            (handles->m_useSecond ? handles->m_secondHandles : handles->m_handles)[i] = handle;
        }
    }
    return handles;
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

GF_OBJ_HANDLE* GfObjFactory::createDummyMover() {
    GfObjManager* manager = GfObjManager::sys();
    if (manager == nullptr) {
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
    GfInitParamEventObj param;
    param.m_createType = 11;
    param.pad_81 = false;
    GF_OBJ_HANDLE* handle = manager->createGfObj(11, param);
    setupObjInfo(handle, reinterpret_cast<GF_ASSET_HANDLE*>(-1), param);
    manager->addHandle(handle);
    GfObjSetup::createSetupParam(handle, param);
    GfObjUtil::addDebugName(handle);
    manager->callGfObjListener(IGfObjListener::OBJEVT(1), handle);
    return handle;
}

void addExtendPackingSoundTrigger(GF_ASSET_HANDLE* asset, GfFileIdx file, GfExtendPacking* packing) {
    if (packing == nullptr) {
        return;
    }
    GfAssetResource* resource = GfAssetManager::getResource(asset, file, static_cast<GfAssetType>(0));
    if (resource == nullptr) {
        return;
    }
    arc::CArcData arc(resource->getAssetData());
    unsigned int files = arc.getFiles();
    for (unsigned int i = 0; i != files; i++) {
        const fw::ResSoundTrigger* trigger = fw::SoundResTriggerImporter::importBinary(arc.getFileAdr(i));
        if (trigger != nullptr) {
            packing->m_soundTriggers.push_back(trigger);
        }
    }
}

bool getSlopeIKLimit(GfObj* obj, float* pitch, float* roll) {
    switch (GfObjUtil::getObjType(obj->m_handle)) {
    case 3: {
        GfObjSetup* setup = GfObjUtil::getObjSetup(obj->m_handle);
        GfBdatChrDr* bdat = mm::mtl::PtrSingleton<GfBdatChrDr>::sys();
        unsigned int id = setup->m_bdatId;
        unsigned char limitPitch = bdat->getChrDrRotateLimitPitch(id);
        unsigned char limitRoll = bdat->getChrDrRotateLimitRoll(id);
        *pitch = limitPitch * 0.0174532924f;
        *roll = limitRoll * 0.0174532924f;
        return true;
    }
    case 4: {
        GfObjSetup* setup = GfObjUtil::getObjSetup(obj->m_handle);
        GfBdatChrBl* bdat = mm::mtl::PtrSingleton<GfBdatChrBl>::sys();
        unsigned int id = setup->m_bdatId;
        unsigned char limitPitch = bdat->getChrBlRotateLimitPitch(id);
        unsigned char limitRoll = bdat->getChrBlRotateLimitRoll(id);
        *pitch = limitPitch * 0.0174532924f;
        *roll = limitRoll * 0.0174532924f;
        return true;
    }
    }
    return false;
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

void GfObjFactory::rebuildAssetHandle(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info->m_assetHandle == reinterpret_cast<GF_ASSET_HANDLE*>(-1)) {
        return;
    }
    GfAssetManager::destroy(info->m_assetHandle);
    info->m_assetHandle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
    switch (GfObjUtil::getObjType(handle)) {
    case 3: {
        GfObjSetupDriver* setup = getSetupOf<GfObjSetupDriver>(GfObjManager::getObjInfo(handle), 3);
        fn_7100525A2C(setup->m_param);
        GF_ASSET_HANDLE* asset = GfAssetFactory::createAssetPackDriver(setup->m_param);
        setupObjInfo(handle, asset, setup->m_param);
        break;
    }
    case 4: {
        GfObjSetupBlade* setup = getSetupOf<GfObjSetupBlade>(GfObjManager::getObjInfo(handle), 4);
        GF_ASSET_HANDLE* asset = GfAssetFactory::createAssetPackBlade(setup->m_param);
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            setupObjInfo(handle, asset, setup->m_param);
            int index = info->m_mounts[0].m_appendIndex;
            if (GFOBJ_INFO* newInfo = GfObjManager::getObjInfo(handle)) {
                newInfo->m_mounts[0].m_appendIndex = index;
            }
        }
        break;
    }
    case 10: {
        GfObjSetupWeapon* setup = getSetupOf<GfObjSetupWeapon>(GfObjManager::getObjInfo(handle), 10);
        GF_ASSET_HANDLE* asset = GfAssetFactory::createAssetPackWeapon(setup->m_param);
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            setupObjInfo(handle, asset, setup->m_param);
            int index = info->m_mounts[0].m_appendIndex;
            if (GFOBJ_INFO* newInfo = GfObjManager::getObjInfo(handle)) {
                newInfo->m_mounts[0].m_appendIndex = index;
            }
        }
        break;
    }
    default:
        break;
    }
}

void GfObjFactory::destroyObj(GF_OBJ_HANDLE* handle) {
    GfObjUtil::destroy(handle);
}

unsigned int GfInitParamEnWeapon::getEnArrangeID() const {
    return m_enArrangeId;
}

anm::Skeleton* fn_7100540BB4(GF_ASSET_HANDLE* asset) {
    GfAssetResource* resource = GfAssetManager::getResource(asset, static_cast<GfFileIdx>(0x44), static_cast<GfAssetType>(0));
    if (resource == nullptr) {
        return nullptr;
    }
    if (GfAssetManager::getAssetPack(asset, static_cast<GfFileIdx>(0x44)) == nullptr) {
        return nullptr;
    }
    mm::mtl::FixStr<64> name = util::getNoPathExtName(resource->getAssetName());
    arc::CArcData arc(resource->getAssetData());
    return anm::SkeletonImporter::import(arc.getFileAdr((name + ".skl").m_str));
}

anm::Skeleton* fn_710054113C(GF_ASSET_HANDLE* asset, GfFileIdx file, const char* name) {
    GfAssetResource* resource = GfAssetManager::getResource(asset, file, static_cast<GfAssetType>(0));
    if (resource == nullptr) {
        return nullptr;
    }
    arc::CArcData arc(resource->getAssetData());
    void* data;
    if (name != nullptr && arc.m_data != nullptr) {
        data = arc.getFileAdr(name);
        if (data == nullptr) {
            return nullptr;
        }
    } else {
        data = resource->getAssetData();
    }
    return anm::SkeletonImporter::import(data);
}

anm::Skeleton* fn_7100541780(GF_ASSET_HANDLE* asset, GfFileIdx file) {
    GfAssetResource* resource = GfAssetManager::getResource(asset, file, static_cast<GfAssetType>(0));
    if (resource == nullptr) {
        return nullptr;
    }
    GfAssetPack* pack = GfAssetManager::getAssetPack(asset, file);
    arc::CArcData arc(resource->getAssetData());
    mm::mtl::FixStr<32> name = pack->pad_258;
    return anm::SkeletonImporter::import(arc.getFileAdr((name + ".skl").m_str));
}

void fn_7100541A00(GfObj* obj, const mm::Vec3& pos, const mm::Vec3& rot) {
    GfComTransform* transform = obj->getComponent<GfComTransform>(0);
    GfComTransform::SetupInfo info;
    info.frame_max = 1;
    info.childFrame = false;
    info.position = pos;
    mm::Vec3 half = mm::Vec3(rot) * 0.5f;
    float sx = ::sinf(half.x);
    float cx = ::cosf(half.x);
    float sy = ::sinf(half.y);
    float cy = ::cosf(half.y);
    float sz = ::sinf(half.z);
    float cz = ::cosf(half.z);
    info.rotation.x = sx * cy * cz - cx * sy * sz;
    info.rotation.y = cx * sy * cz + sx * cy * sz;
    info.rotation.z = cx * cy * sz - sx * sy * cz;
    info.rotation.w = cx * cy * cz + sx * sy * sz;
    transform->setup(info);
}

void fn_7100543DC8(GfObj* obj, unsigned int kind, float value) {
    GfObjAcc acc(obj->m_handle);
    if (GfComEffectCaster* caster = obj->getComponent<GfComEffectCaster>(7)) {
        GfComEffectCaster::SetupInfo info;
        info.m_asset = acc.getAssetHandle();
        info.pad_10 = caster->getLayer();
        info.m_viewnum = acc.getView();
        info.m_kind = kind;
        info.pad_18 = value;
        caster->setup(info);
    }
}

void fn_7100543E68(GfObj* obj, GfFileIdx file, const char* name, bool high) {
    GF_ASSET_HANDLE* asset = GfObjUtil::getAssetHandle(obj->m_handle);
    GfComDynamics* dynamics = obj->getComponent<GfComDynamics>(8);
    GfComDynamics::SetupInfo info;
    info.colObj = nullptr;
    info.res = nullptr;
    info.level = 6;
    if (GfAssetResource* resource = GfAssetManager::getResource(asset, file, static_cast<GfAssetType>(0))) {
        void* data = resource->getAssetData();
        if (name != nullptr) {
            arc::CArcData arc(data);
            data = arc.getFileAdr(name);
        }
        info.res = skd::DynamicsImporter::import(data);
        if (high) {
            info.level = 30;
        }
    }
    dynamics->setup(info);
}

void fn_7100543F98(GF_OBJ_HANDLE* handle) {
    DataParamAcc acc(handle);
    if (acc.isValid() && acc.getObjType() == 3) {
        switch (acc.getBdatId()) {
        case 1:
            GfGameUtil::dispRexCrystal(handle, GfGameUtil::isDispRexCrystal());
            break;
        case 8:
            GfGameUtil::dispMetsuCrystal(handle, GfGameUtil::isDispMetsuCrystal());
            break;
        case 0x11:
            GfGameUtil::dispLauraMedal(handle, GfGameUtil::isDispLauraMedal());
            break;
        case 0x14:
            fn_71005442A4(handle);
            break;
        }
    }
}

void fn_71005442A4(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    acc.setupExtraParts();
    if (strstr(GfObjUtil::getModelBaseName(handle), "np100201") != nullptr) {
        GfGameUtil::dispMetsuCrystal(handle, GfGameUtil::isDispMetsuCrystal());
    }
    if (strstr(GfObjUtil::getModelBaseName(handle), "np100101") != nullptr) {
        GfGameUtil::dispSinMask(handle, GfGameUtil::isDispSinMask());
    }
    if (strstr(GfObjUtil::getModelBaseName(handle), "pc700401") != nullptr) {
        GfGameUtil::dispSinMask(handle, GfGameUtil::isDispSinMask());
    }
}

}  // namespace gf
