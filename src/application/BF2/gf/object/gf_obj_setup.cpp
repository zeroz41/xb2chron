#include "gf/FileStaticVec3.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfObjSetupDriver.h"
#include "classes/gf/GfObjSetupBlade.h"
#include "classes/gf/GfObjSetupMap.h"
#include "classes/gf/GfObjSetupMapLodAnim.h"
#include "classes/gf/GfObjSetupEnemy.h"
#include "classes/gf/GfObjSetupNpc.h"
#include "classes/gf/GfObjSetupMob.h"
#include "classes/gf/GfObjSetupGimmick.h"
#include "classes/gf/GfObjSetupMapObj.h"
#include "classes/gf/GfObjSetupFieldObj.h"
#include "classes/gf/GfObjSetupWeapon.h"
#include "classes/gf/GfObjSetupEnWeapon.h"
#include "classes/gf/GfObjSetupBelonging.h"
#include "classes/gf/GfObjSetupExtra.h"
#include "classes/gf/GfObjSetupEventObj.h"
#include "classes/gf/GfObjSetupUiObj.h"
#include "classes/gf/DataObjDriver.h"
#include "classes/gf/DataObjBlade.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"
#include "gf/GfObjInfo.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfInitParamMapSeamless.h"
#include "classes/gf/GfInitParamWeapon.h"
#include "classes/gf/GfInitParamBlade.h"
#include "gf/GfDataBlade.h"
#include "classes/gf/GfInitParamEnemy.h"

namespace gf {

mm::mtl::RTTI GfObjSetup::m_rtti("GfObjSetup", nullptr, nullptr);

unsigned int GfObjSetup::getFootStep() const {
    switch (m_type) {
    case 3: {
        DataObjDriver data(m_bdatId);
        return data.getFootStep();
    }
    case 4: {
        DataObjBlade data(m_bdatId);
        return data.getFootStep();
    }
    }
    return 0;
}

unsigned int GfObjSetup::getFootStepEffect() const {
    switch (m_type) {
    case 3: {
        DataObjDriver data(m_bdatId);
        return data.getFootStepEffect();
    }
    case 4: {
        DataObjBlade data(m_bdatId);
        return data.getFootStepEffect();
    }
    }
    return 1;
}

void GfObjSetup::setInitialScale(float scale) {
    m_initialScale.x = scale;
    m_initialScale.y = scale;
    m_initialScale.z = scale;
}

mm::mtl::RTTI GfObjSetupDriver::m_rtti("GfObjSetupDriver", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupBlade::m_rtti("GfObjSetupBlade", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupMap::m_rtti("GfObjSetupMap", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupMapLodAnim::m_rtti("GfObjSetupMapLodAnim", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupEnemy::m_rtti("GfObjSetupEnemy", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupNpc::m_rtti("GfObjSetupNpc", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupMob::m_rtti("GfObjSetupMob", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupGimmick::m_rtti("GfObjSetupGimmick", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupMapObj::m_rtti("GfObjSetupMapObj", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupFieldObj::m_rtti("GfObjSetupFieldObj", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupWeapon::m_rtti("GfObjSetupWeapon", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupEnWeapon::m_rtti("GfObjSetupEnWeapon", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupBelonging::m_rtti("GfObjSetupBelonging", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupExtra::m_rtti("GfObjSetupExtra", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupEventObj::m_rtti("GfObjSetupEventObj", &GfObjSetup::m_rtti, nullptr);
mm::mtl::RTTI GfObjSetupUiObj::m_rtti("GfObjSetupUiObj", &GfObjSetup::m_rtti, nullptr);

#line 164
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamMapSeamless& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupMap* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupMap(param);
    info->m_setup = setup;
    if (param.pad_90) {
        setup->pad_70 = param.m_objId;
    } else {
        setup->pad_6c = param.m_objId;
    }
    if (param.pad_98 != nullptr) {
        setup->pad_74 = true;
    }
    setup->pad_75 = true;
    return setup;
}

GfObjSetupMap::GfObjSetupMap(const GfInitParam& param)
    : GfObjSetup(1, param), pad_6c(0), pad_70(0), pad_74(false), pad_75(false) {}

#line 200
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamMapLodAnim& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupMapLodAnim* setup =
        new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupMapLodAnim(param);
    info->m_setup = setup;
    return setup;
}

GfObjSetupMapLodAnim::GfObjSetupMapLodAnim(const GfInitParamMapLodAnim& param)
    : GfObjSetup(2, param), pad_6c(false), pad_6d(false) {}

#line 245
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamNpc& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupNpc* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupNpc(param);
    info->m_setup = setup;
    setup->pad_90 = param.pad_98;
    return setup;
}

GfObjSetupNpc::GfObjSetupNpc(const GfInitParamNpc& param)
    : GfObjSetup(6, param), m_stateName("S_idle"), pad_90(nullptr) {}

#line 260
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamMob& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupMob* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupMob(param);
    info->m_setup = setup;
    if (setup->m_bdatId != 0) {
        switch (static_cast<unsigned char>(
            reinterpret_cast<unsigned long>(Bdat::getValCheck(GfDataBdat::getFP(0xAA), "Race", param.m_objId, 1)))) {
        case 1:
            setup->pad_68 = 0;
            break;
        case 3:
            setup->pad_68 = 1;
            break;
        default:
            setup->pad_68 = -1;
            break;
        }
    }
    return setup;
}

GfObjSetupMob::GfObjSetupMob(const GfInitParamMob& param) : GfObjSetup(7, param), m_stateName("S_idle"), pad_90(100) {}

#line 292
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamGimmick& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupGimmick* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupGimmick(param);
    info->m_setup = setup;
    setup->pad_98 = param.pad_90;
    return setup;
}

GfObjSetupGimmick::GfObjSetupGimmick(const GfInitParamGimmick& param)
    : GfObjSetup(8, param), pad_6c(0), m_stateName("S_idle"), pad_98(nullptr), pad_a0(true), pad_a1(true) {}

#line 320
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamFobj& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupFieldObj* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupFieldObj(param);
    info->m_setup = setup;
    mm::mtl::FixStr<16> column;
    column.format("paramid%d", param.pad_94);
    unsigned char** table = param.pad_18;
    unsigned int id = param.m_objId;
    setup->pad_6c =
        static_cast<unsigned short>(reinterpret_cast<unsigned long>(Bdat::getValCheck(*table, column.m_str, id, 2)));
    setup->m_bdatId = param.m_objId;
    return setup;
}

GfObjSetupFieldObj::GfObjSetupFieldObj(const GfInitParamFobj& param)
    : GfObjSetup(9, param), pad_6c(-1), pad_70(), pad_90(false) {}

#line 358
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamEnWeapon& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupEnWeapon* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupEnWeapon(param);
    info->m_setup = setup;
    setup->m_mountIndex = param.m_append.getMountIndex();
    return setup;
}

GfObjSetupEnWeapon::GfObjSetupEnWeapon(const GfInitParamEnWeapon& param) : GfObjSetup(12, param), m_mountIndex(-1) {}

#line 373
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamBelonging& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupBelonging* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupBelonging(param);
    info->m_setup = setup;
    setup->m_mountIndex = param.m_append.getMountIndex();
    setup->pad_50 = param.pad_130 ? 1.0f : 0.0f;
    return setup;
}

GfObjSetupBelonging::GfObjSetupBelonging(const GfInitParamBelonging& param)
    : GfObjSetup(13, param), m_mountIndex(-1) {}

#line 389
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamExtra& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupExtra* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupExtra(param);
    info->m_setup = setup;
    setup->m_mountIndex = param.m_append.getMountIndex();
    return setup;
}

GfObjSetupExtra::GfObjSetupExtra(const GfInitParamExtra& param) : GfObjSetup(14, param), m_mountIndex(-1) {}

GfObjSetupEventObj::GfObjSetupEventObj(const GfInitParamEventObj& param) : GfObjSetup(11, param) {}

GfObjSetupUiObj::GfObjSetupUiObj(const GfInitParamUiObj& param) : GfObjSetup(15, param), m_stateName("S_idle") {}

void GfInitParamWeapon::setupForEventBlade(unsigned int weaponId, GF_OBJ_HANDLE* handle) {
    m_createType = 2;
    m_objId = weaponId;
    pad_30 = handle;
    pad_38 = handle;
    pad_90 = false;
}

void GfInitParamWeapon::setupBladeForEventRightCS(unsigned int bladeId) {
    unsigned int driverId = GfDataBlade::getSetDriver(bladeId);
    if (driverId == 0) {
        driverId = GfDataBlade::getCreator(bladeId);
    }
    setupForEvent(driverId, bladeId);
    m_createType = 3;
    pad_1e0 = true;
}

void GfInitParamWeapon::setupBladeForEventLeftCS(unsigned int bladeId) {
    unsigned int driverId = GfDataBlade::getSetDriver(bladeId);
    if (driverId == 0) {
        driverId = GfDataBlade::getCreator(bladeId);
    }
    setupForEvent(driverId, bladeId);
    m_createType = 3;
    pad_1e1 = true;
}

GfObjSetupEnemy::~GfObjSetupEnemy() {
    if (m_sdata != nullptr) {
        delete m_sdata;
        m_sdata = nullptr;
    }
    if (pad_c0 != nullptr) {
        delete pad_c0;
        pad_c0 = nullptr;
    }
}

void GfInitParamBlade::setupForParty(unsigned int partyId, int pad98, unsigned int bladeId, GF_OBJ_HANDLE* handle,
                                     bool flag) {
    m_createType = 1;
    pad_90 = true;
    pad_20 = partyId;
    m_objId = bladeId;
    pad_98 = pad98;
    pad_38 = handle;
    pad_91 = flag;
    m_scale = GfDataBlade::getScale(bladeId);
}

void GfInitParamBlade::setupForEvent(unsigned int bladeId, bool flag) {
    m_createType = 2;
    m_objId = bladeId;
    pad_40 = 7;
    m_scale = GfDataBlade::getScale(bladeId);
    pad_a4 = (bladeId == 1001) & flag;
    pad_81 = false;
    pad_82 = 0;
}

void GfInitParamBlade::setupForUi(unsigned int bladeId, VIEWCAM camera) {
    m_createType = 6;
    m_objId = bladeId;
    pad_24 = camera;
    pad_40 = 10;
    m_scale = GfDataBlade::getScale(bladeId);
    pad_81 = false;
}

}  // namespace gf
