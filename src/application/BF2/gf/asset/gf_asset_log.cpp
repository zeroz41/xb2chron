#include "classes/gf/GfAssetSetup.h"
#include "classes/gf/GfInitParam.h"
#include "classes/gf/GfAssetManager.h"
#include "gf/GfAppend.h"
#include "gf/GfAssetFactory.h"
#include "classes/gf/GfAssetSetupDriver.h"
#include "classes/gf/GfAssetSetupEventDriver.h"
#include "classes/gf/GfAssetSetupSalvage.h"
#include "classes/gf/GfAssetSetupDriverForUi.h"
#include "classes/gf/GfAssetSetupBlade.h"
#include "classes/gf/GfAssetSetupEventBlade.h"
#include "classes/gf/GfAssetSetupBladeForUi.h"
#include "classes/gf/GfAssetSetupMapSeamless.h"
#include "classes/gf/GfAssetSetupEnemy.h"
#include "classes/gf/GfAssetSetupEnemyBlade.h"
#include "classes/gf/GfAssetSetupEventEnemy.h"
#include "classes/gf/GfAssetSetupNpc.h"
#include "classes/gf/GfAssetSetupEventNpc.h"
#include "classes/gf/GfAssetSetupMob.h"
#include "classes/gf/GfAssetSetupEventMob.h"
#include "classes/gf/GfAssetSetupGimmick.h"
#include "classes/gf/GfAssetSetupFobj.h"
#include "classes/gf/GfAssetSetupWeapon.h"
#include "classes/gf/GfAssetSetupWeaponEventCS.h"
#include "classes/gf/GfAssetSetupEnWeapon.h"
#include "classes/gf/GfAssetSetupBelonging.h"
#include "classes/gf/GfAssetSetupExtra.h"
#include "classes/gf/GfAssetSetupEventObj.h"
#include "classes/gf/GfAssetSetupUiObj.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfInitParamBlade.h"
#include "classes/gf/GfInitParamMapSeamless.h"
#include "classes/gf/GfInitParamEnemy.h"
#include "classes/gf/GfInitParamNpc.h"
#include "classes/gf/GfInitParamMob.h"
#include "classes/gf/GfInitParamGimmick.h"
#include "classes/gf/GfInitParamFobj.h"
#include "classes/gf/GfInitParamWeapon.h"
#include "classes/gf/GfInitParamEnWeapon.h"
#include "classes/gf/GfInitParamBelonging.h"
#include "classes/gf/GfInitParamExtra.h"
#include "classes/gf/GfInitParamEventObj.h"
#include "classes/gf/GfInitParamUiObj.h"

namespace gf {

// event (2, 3, 11), UI (6, 7, 12) and salvage (9, 13) uses of GfInitParam::m_createType (the names are not the
// original's; the first two test a table of bits, the original's mark of a switch that yields a bool)
static inline bool isEventCreate(int type) {
    switch (type) {
    case 2:
    case 3:
    case 11:
        return true;
    default:
        return false;
    }
}
static inline bool isUiCreate(int type) {
    switch (type) {
    case 6:
    case 7:
    case 12:
        return true;
    default:
        return false;
    }
}
static inline bool isSalvageCreate(int type) {
    return type == 9 || type == 13;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackDriver(const GfInitParamDriver& param) {
    if (isEventCreate(param.m_createType)) {
        return createAssetPackDriverForEvent(param);
    }
    if (isSalvageCreate(param.m_createType)) {
        return createAssetPackDriverForSalvage(param);
    }
    if (isUiCreate(param.m_createType) && param.m_createType != 7) {
        return createAssetPackDriverForUi(param);
    }
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupDriver assetSetup;
    GfAssetSetupDriver* setup =
        param.m_assetSetup != nullptr ? static_cast<GfAssetSetupDriver*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

// out of line in 1.0.0; 3.0.1 keeps no copy
inline GF_ASSET_HANDLE* GfAssetFactory::createAssetPackDriverForEvent(const GfInitParamDriver& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupEventDriver assetSetup;
    GfAssetSetupEventDriver* setup = &assetSetup;
    if (param.m_assetSetup != nullptr) {
        setup = mm::mtl::rttiCast<GfAssetSetupEventDriver>(param.m_assetSetup);
    }
    setup->setup(handle, param);
    return setup->m_handle;
}

// out of line in 1.0.0; 3.0.1 keeps no copy
inline GF_ASSET_HANDLE* GfAssetFactory::createAssetPackDriverForSalvage(const GfInitParamDriver& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupSalvage assetSetup;
    GfAssetSetupSalvage* setup = &assetSetup;
    if (param.m_assetSetup != nullptr) {
        setup = mm::mtl::rttiCast<GfAssetSetupSalvage>(param.m_assetSetup);
    }
    setup->setup(handle, param);
    return setup->m_handle;
}

// out of line in 1.0.0; 3.0.1 keeps no copy
inline GF_ASSET_HANDLE* GfAssetFactory::createAssetPackDriverForUi(const GfInitParamDriver& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupDriverForUi assetSetup;
    GfAssetSetupDriverForUi* setup = &assetSetup;
    if (param.m_assetSetup != nullptr) {
        setup = mm::mtl::rttiCast<GfAssetSetupDriverForUi>(param.m_assetSetup);
    }
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackBlade(const GfInitParamBlade& param) {
    if (isEventCreate(param.m_createType)) {
        return createAssetPackBladeForEvent(param);
    }
    if (isUiCreate(param.m_createType)) {
        return createAssetPackBladeForUi(param);
    }
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupBlade assetSetup;
    GfAssetSetupBlade* setup =
        param.m_assetSetup != nullptr ? static_cast<GfAssetSetupBlade*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

// out of line in 1.0.0; 3.0.1 keeps no copy
inline GF_ASSET_HANDLE* GfAssetFactory::createAssetPackBladeForEvent(const GfInitParamBlade& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupEventBlade assetSetup;
    GfAssetSetupEventBlade* setup = &assetSetup;
    if (param.m_assetSetup != nullptr) {
        setup = mm::mtl::rttiCast<GfAssetSetupEventBlade>(param.m_assetSetup);
    }
    setup->setup(handle, param);
    return setup->m_handle;
}

// out of line in 1.0.0; 3.0.1 keeps no copy
inline GF_ASSET_HANDLE* GfAssetFactory::createAssetPackBladeForUi(const GfInitParamBlade& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupBladeForUi assetSetup;
    GfAssetSetupBladeForUi* setup = &assetSetup;
    if (param.m_assetSetup != nullptr) {
        setup = mm::mtl::rttiCast<GfAssetSetupBladeForUi>(param.m_assetSetup);
    }
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackMap(const GfInitParamMapSeamless& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupMapSeamless assetSetup;
    GfAssetSetupMapSeamless* setup = param.m_assetSetup != nullptr ? static_cast<GfAssetSetupMapSeamless*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackEnemy(const GfInitParamEnemy& param) {
    if (isEventCreate(param.m_createType)) {
        return createAssetPackEnemyForEvent(param);
    }
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    if (param.m_createType == 5) {
        GfAssetSetupEnemyBlade assetSetup;
        GfAssetSetupEnemy* setup =
            param.m_assetSetup != nullptr ? static_cast<GfAssetSetupEnemy*>(param.m_assetSetup) : &assetSetup;
        setup->setup(handle, param);
        return setup->m_handle;
    }
    GfAssetSetupEnemy assetSetup;
    GfAssetSetupEnemy* setup =
        param.m_assetSetup != nullptr ? static_cast<GfAssetSetupEnemy*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

// out of line in 1.0.0; 3.0.1 keeps no copy
inline GF_ASSET_HANDLE* GfAssetFactory::createAssetPackEnemyForEvent(const GfInitParamEnemy& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupEventEnemy assetSetup;
    GfAssetSetupEventEnemy* setup = &assetSetup;
    if (param.m_assetSetup != nullptr) {
        setup = mm::mtl::rttiCast<GfAssetSetupEventEnemy>(param.m_assetSetup);
    }
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackNpc(const GfInitParamNpc& param) {
    if (isEventCreate(param.m_createType)) {
        return createAssetPackNpcForEvent(param);
    }
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupNpc assetSetup;
    GfAssetSetupNpc* setup =
        param.m_assetSetup != nullptr ? static_cast<GfAssetSetupNpc*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

// out of line in 1.0.0; 3.0.1 keeps no copy
inline GF_ASSET_HANDLE* GfAssetFactory::createAssetPackNpcForEvent(const GfInitParamNpc& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupEventNpc assetSetup;
    GfAssetSetupEventNpc* setup = &assetSetup;
    if (param.m_assetSetup != nullptr) {
        setup = mm::mtl::rttiCast<GfAssetSetupEventNpc>(param.m_assetSetup);
    }
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackMob(const GfInitParamMob& param) {
    if (isEventCreate(param.m_createType)) {
        return createAssetPackMobForEvent(param);
    }
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupMob assetSetup;
    GfAssetSetupMob* setup =
        param.m_assetSetup != nullptr ? static_cast<GfAssetSetupMob*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

// out of line in 1.0.0; 3.0.1 keeps no copy
inline GF_ASSET_HANDLE* GfAssetFactory::createAssetPackMobForEvent(const GfInitParamMob& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupEventMob assetSetup;
    GfAssetSetupEventMob* setup = &assetSetup;
    if (param.m_assetSetup != nullptr) {
        setup = mm::mtl::rttiCast<GfAssetSetupEventMob>(param.m_assetSetup);
    }
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackGimmick(const GfInitParamGimmick& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupGimmick assetSetup;
    GfAssetSetupGimmick* setup = param.m_assetSetup != nullptr ? static_cast<GfAssetSetupGimmick*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackFobj(const GfInitParamFobj& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupFobj assetSetup;
    GfAssetSetupFobj* setup = param.m_assetSetup != nullptr ? static_cast<GfAssetSetupFobj*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackWeapon(const GfInitParamWeapon& param) {
    if (param.m_createType == 3) {
        return createAssetPackWeaponForEventCS(param);
    }
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupWeapon assetSetup;
    GfAssetSetupWeapon* setup =
        param.m_assetSetup != nullptr ? static_cast<GfAssetSetupWeapon*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

// out of line in 1.0.0; 3.0.1 keeps no copy
inline GF_ASSET_HANDLE* GfAssetFactory::createAssetPackWeaponForEventCS(const GfInitParamWeapon& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupWeaponEventCS assetSetup;
    GfAssetSetupWeaponEventCS* setup = &assetSetup;
    if (param.m_assetSetup != nullptr) {
        setup = mm::mtl::rttiCast<GfAssetSetupWeaponEventCS>(param.m_assetSetup);
    }
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackEnWeapon(const GfInitParamEnWeapon& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupEnWeapon assetSetup;
    GfAssetSetupEnWeapon* setup = param.m_assetSetup != nullptr ? static_cast<GfAssetSetupEnWeapon*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackBelonging(const GfInitParamBelonging& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupBelonging assetSetup;
    GfAssetSetupBelonging* setup = param.m_assetSetup != nullptr ? static_cast<GfAssetSetupBelonging*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackExtra(const GfInitParamExtra& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupExtra assetSetup;
    GfAssetSetupExtra* setup = param.m_assetSetup != nullptr ? static_cast<GfAssetSetupExtra*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackEventObj(const GfInitParamEventObj& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupEventObj assetSetup;
    GfAssetSetupEventObj* setup = param.m_assetSetup != nullptr ? static_cast<GfAssetSetupEventObj*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

GF_ASSET_HANDLE* GfAssetFactory::createAssetPackUiObj(const GfInitParamUiObj& param) {
    GF_ASSET_HANDLE* handle = GfAssetManager::createAssetHandle(param);
    GfAssetSetupUiObj assetSetup;
    GfAssetSetupUiObj* setup = param.m_assetSetup != nullptr ? static_cast<GfAssetSetupUiObj*>(param.m_assetSetup) : &assetSetup;
    setup->setup(handle, param);
    return setup->m_handle;
}

}  // namespace gf
