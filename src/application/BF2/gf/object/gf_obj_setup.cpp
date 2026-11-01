#include "gf/FileStaticVec3.h"
#include "classes/gf/GfObjSetup.h"
#include "mm/Mat44.h"
#include "fw/Transform.h"
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
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/DataObjEnemy.h"
#include "gf/SDataBlade.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "gf/GfDataDriver.h"
#include "classes/gf/GfBdatChrBl.h"
#include "classes/gf/GfBdatChrDr.h"
#include "classes/gf/GfAssetSetupUiObj.h"
#include "gf/GfObjUtil.h"

namespace gf {

namespace {
// name = the file name of path, without its folder and extension: the text after the last '/' (else '\\') with
// everything from the last '.' cut off (inline: no copy of its own in the original; the name is not the
// original's). The cut leaves the length as it was, so the slash search reads the old length. The slash searches
// sit under their own empty test: the original tests the length once for both (findLast's own tests fold into it)
inline void setArcName(mm::mtl::FixStr<128>& name, const char* path) {
    name = path;
    int dot = name.findLast('.');
    if (dot != -1) {
        name.m_str[dot] = '\0';
    }
    if (name.m_nLen != 0) {
        int slash = name.findLast('/');
        if (slash == -1) {
            slash = name.findLast('\\');
        }
        if (slash != -1) {
            name = &name.m_str[slash + 1];
        }
    }
}
}  // namespace

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

void GfObjSetup::setInitialTransform(const mm::Mat44& mtx) {
    m_initialPos = mtx.getTrans();
    // the rotation part with each row's scale divided out
    mm::Mat44 rot;
    float sx = ::sqrtf(mtx.m[0][0] * mtx.m[0][0] + mtx.m[0][1] * mtx.m[0][1] + mtx.m[0][2] * mtx.m[0][2]);
    rot.m[0][0] = mtx.m[0][0] / sx;
    rot.m[0][1] = mtx.m[0][1] / sx;
    rot.m[0][2] = mtx.m[0][2] / sx;
    float sy = ::sqrtf(mtx.m[1][0] * mtx.m[1][0] + mtx.m[1][1] * mtx.m[1][1] + mtx.m[1][2] * mtx.m[1][2]);
    rot.m[1][0] = mtx.m[1][0] / sy;
    rot.m[1][1] = mtx.m[1][1] / sy;
    rot.m[1][2] = mtx.m[1][2] / sy;
    float sz = ::sqrtf(mtx.m[2][0] * mtx.m[2][0] + mtx.m[2][1] * mtx.m[2][1] + mtx.m[2][2] * mtx.m[2][2]);
    rot.m[2][0] = mtx.m[2][0] / sz;
    rot.m[2][1] = mtx.m[2][1] / sz;
    rot.m[2][2] = mtx.m[2][2] / sz;
    rot.getRotXYZ(pad_30);
    pad_30.x = -pad_30.x;
    pad_30.y = -pad_30.y;
    pad_30.z = -pad_30.z;
}

void GfObjSetup::setInitialTransform(const fw::Transform& transform) {
    m_initialPos = transform.position;
    const mm::Quat& q = transform.rotation;
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
    pad_30.x = mm::asin(-m21);
    if (pad_30.x < 1.57079637f) {
        if (pad_30.x > -1.57079637f) {
            pad_30.z = ::atan2f(m01, m11);
            pad_30.y = ::atan2f(m20, m22);
        } else {
            pad_30.z = -::atan2f(m02, m00);
            pad_30.y = 0.0f;
        }
    } else {
        pad_30.z = ::atan2f(m02, m00);
        pad_30.y = 0.0f;
    }
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

#line 128
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamDriver& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupDriver* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupDriver(param);
    info->m_setup = setup;
    setup->pad_6c = param.pad_1a0;
    if (param.m_hasTransform) {
        setup->m_initialPos = param.m_initialPos;
        setup->pad_30 = param.pad_70;
    }
    return setup;
}

GfObjSetupDriver::GfObjSetupDriver(const GfInitParamDriver& param)
    : GfObjSetup(3, param), pad_6c(0), pad_6d(0), pad_6e(0), pad_70(-1) {
    m_param = param;
}

#line 150
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamBlade& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupBlade* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupBlade(param);
    info->m_setup = setup;
    setup->pad_6c = param.pad_98;
    return setup;
}

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

#line 214
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamEnemy& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupEnemy* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupEnemy(param);
    info->m_setup = setup;
    setup->pad_6c = param.m_paramId;
    setup->m_enArrangeId = param.m_arrangeId != 0 ? param.m_arrangeId : 1;
    if (param.pad_a8 != 0) {
        setup->m_actMoveId = param.pad_a8;
    }
#line 227
    SDataEnemy* sdata = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SDataEnemy(setup->m_enArrangeId, param.pad_ac);
    setup->m_sdata = sdata;
    GFOBJ_INFO* owner = GfObjManager::getObjInfo(param.pad_38);
    if (owner != nullptr && owner->m_setup != nullptr && owner->m_setup->m_type == owner->m_obj->m_type &&
        owner->m_obj->m_type == 5) {
        GfObjSetupEnemy* ownerSetup = mm::mtl::rttiCast<GfObjSetupEnemy>(owner->m_setup);
        if (ownerSetup != nullptr && setup->m_sdata->pad_41 != 0) {
            ownerSetup->m_sdata->pad_41 = setup->m_sdata->pad_41;
        }
    }
    return setup;
}


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
            Bdat::getValCheck(GfDataBdat::getFP(0xAA), "Race", param.m_objId, 1))) {
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
        static_cast<unsigned short>(Bdat::getValCheck(*table, column.m_str, id, 2));
    setup->m_bdatId = param.m_objId;
    return setup;
}

GfObjSetupFieldObj::GfObjSetupFieldObj(const GfInitParamFobj& param)
    : GfObjSetup(9, param), pad_6c(-1), m_dropDistance(0.0f), m_appearDelay(0.0f), m_itemBdat(0), m_itemId(0), m_gold(0),
      m_amount(0), m_fobjId(0), pad_8c(), pad_90(false) {}

#line 341
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamWeapon& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupWeapon* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupWeapon(param);
    info->m_setup = setup;
    setup->pad_6c = param.pad_94;
    setup->m_mountIndex = param.pad_98.getMountIndex();
    setup->pad_78 = param.pad_98.m_secondList;
    return setup;
}

GfObjSetupWeapon::GfObjSetupWeapon(const GfInitParamWeapon& param)
    : GfObjSetup(10, param), pad_6c(-1), pad_70(0), m_mountIndex(-1), pad_78(0) {
    m_param = param;
}

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

#line 404
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamEventObj& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupEventObj* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupEventObj(param);
    info->m_setup = setup;
    GfAssetSetup* asset = param.m_assetSetup;
    if (asset != nullptr && asset->getArcFile(asset->getAssetType()) != nullptr) {
        setArcName(setup->m_arcName, param.m_assetSetup->getArcFile(param.m_assetSetup->getAssetType()));
    }
    return setup;
}

GfObjSetupEventObj::GfObjSetupEventObj(const GfInitParamEventObj& param) : GfObjSetup(11, param) {}

#line 447
GfObjSetup* GfObjSetup::createSetupParam(GF_OBJ_HANDLE* handle, const GfInitParamUiObj& param) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    GfObjSetupUiObj* setup = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfObjSetupUiObj(param);
    info->m_setup = setup;
    GF_ASSET_HANDLE* assetHandle = GfObjUtil::getAssetHandle(handle);
    GfAssetSetupUiObj assetSetup;
    assetSetup.setupParam(assetHandle, param);
    GfAssetSetup* asset = &assetSetup;
    if (param.m_assetSetup != nullptr) {
        asset = param.m_assetSetup;
    }
    setArcName(setup->m_arcName, asset->getArcFile(asset->getAssetType()));
    setup->m_stateName.format("S_idle");
    return setup;
}


GfObjSetupUiObj::GfObjSetupUiObj(const GfInitParamUiObj& param) : GfObjSetup(15, param), m_stateName("S_idle") {}

void GfInitParamWeapon::setupForEvent(unsigned int driverId, unsigned int bladeId) {
    if (driverId == 0) {
        if (bladeId == 1042) {
            driverId = 8;
        }
        if (bladeId == 1043 || bladeId == 1044) {
            driverId = 7;
        }
        if (bladeId == 1045) {
            driverId = 7;
        }
    }
    DataParamAcc driver(3, driverId, GimmickType(0));
    m_createType = 2;
    if (bladeId == 0) {
        bladeId = driver.getBlade(-1, false);
    }
    if (bladeId != 0) {
        m_objId = GfDataBlade::getBladeWeapon(bladeId);
    }
    if (m_objId == 0) {
        m_objId = GfBdatChrBl::get()->getChrBlDefWeapon(GfBdatChrDr::get()->getChrDrDefBlade1(driverId));
    }
    if (bladeId != 0) {
        mm::mtl::FixedVector<unsigned int, 50> types;
        GfDataDriver::getEquipWpnType(types, driverId);
        GfDataBlade::getBladeWpnType(bladeId);
    }
    pad_90 = false;
    pad_40 = 9;
    pad_128 = driverId;
    pad_81 = false;
    pad_12c = bladeId;
}

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

GfObjSetupEnemy::GfObjSetupEnemy(const GfInitParamEnemy& param)
    : GfObjSetup(5, param), pad_6c(param.m_arrangeId), m_enArrangeId(param.m_paramId), m_stateName(), pad_98(false),
      m_sdata(nullptr), m_actMoveId(0), pad_ac(0), pad_b0(0), pad_b1(false), pad_b2(0), pad_b4(0), m_bladeId(param.m_bladeId), pad_c0(nullptr) {
    m_stateName = "S_idle";
    if (m_bladeId != 0) {
#line 662
        pad_c0 = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) SDataBlade;
        GfDataBlade::setupSDataBlade(*pad_c0, m_bladeId, false);
    }
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

void GfObjSetupEnemy::validateBy_pop_act_type(unsigned char type) {
    switch (type) {
    case 0:
        m_stateName = "S_idle";
        break;
    case 1:
        m_stateName = "S_specialA_01";
        break;
    case 2:
        m_stateName = "S_specialB_01";
        break;
    case 3:
    case 5:
        m_stateName = "S_specialC_00";
        break;
    case 4:
    case 6:
        m_stateName = "S_specialD_00";
        break;
    default:
        m_stateName = "S_idle";
        break;
    }
    pad_98 = !(type == 3 || type == 4 || type == 5 || type == 6);
}

void GfInitParamEnemy::setupForEvent(unsigned int arrangeId) {
    m_createType = 2;
    m_arrangeId = arrangeId;
    m_paramId = GfBdatChrEnArrange::get()->getChrEnArrangeParamID(arrangeId);
    m_objId = GfBdatChrEnParam::get()->getChrEnParamResourceID(m_paramId);
    pad_a4 = GfBdatChrEnParam::get()->getChrEnParamResourceID(m_paramId);
    pad_40 = 8;
    pad_81 = false;
    pad_82 = 0;
}

void GfInitParamEnemy::setupBlade(const GfInitParamEnemy& param) {
    GfBdatChrEnArrange* arrange = GfBdatChrEnArrange::get();
    m_createType = 5;
    m_arrangeId = arrange->getChrEnArrangeEnemyBladeID(param.m_arrangeId);
    m_paramId = arrange->getChrEnArrangeParamID(m_arrangeId);
    pad_a8 = 1;
    m_objId = GfBdatChrEnParam::get()->getChrEnParamResourceID(m_paramId);
    pad_40 = 5;
    m_bladeId = arrange->getChrEnArrangeBladeID(m_arrangeId);
}

void GfInitParamEnemy::setupForUi(unsigned int arrangeId, VIEWCAM camera) {
    m_createType = 6;
    m_arrangeId = arrangeId;
    m_paramId = GfBdatChrEnArrange::get()->getChrEnArrangeParamID(arrangeId);
    m_objId = GfBdatChrEnParam::get()->getChrEnParamResourceID(m_paramId);
    pad_40 = 11;
    pad_24 = camera;
    pad_81 = false;
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

GfObjSetupBlade::GfObjSetupBlade(const GfInitParamBlade& param)
    : GfObjSetup(4, param), pad_6c(-1), pad_70(0), pad_74(-1) {
    m_isCondBladeModel = GfGameUtil::isCondBladeModel(param.m_objId);
    m_param = param;
}

void GfInitParamDriver::fn_710054E050(unsigned int driverId, unsigned int bladeId) {
    pad_40 = 7;
    m_objId = driverId;
    pad_81 = false;
    m_createType = 3;
    m_bladeId = bladeId;
    pad_82 = 0;
    if (GfDataDriver::fn_710023F9A8(driverId)) {
        m_bladeId = GfDataBlade::fn_7100237B70(driverId, -1);
    }
}

}  // namespace gf
