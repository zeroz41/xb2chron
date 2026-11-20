#include "mm/mtl/Algorithm.h"
#include "mm/mtl/FixStr.h"
#include "classes/gf/GfInitParam.h"
#include "classes/gf/GfAssetSetupWeapon.h"
// the asset setups: per kind of object, which files of its asset load and into which slots

#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetSetup.h"
#include "classes/gf/GfAssetSetupBelonging.h"
#include "classes/gf/GfAssetSetupBlade.h"
#include "classes/gf/GfAssetSetupDriver.h"
#include "classes/gf/GfAssetSetupEnWeapon.h"
#include "classes/gf/GfAssetSetupEnemy.h"
#include "classes/gf/GfAssetSetupEventObj.h"
#include "classes/gf/GfAssetSetupExtra.h"
#include "classes/gf/GfAssetSetupFobj.h"
#include "classes/gf/GfAssetSetupGimmick.h"
#include "classes/gf/GfAssetSetupMapSeamless.h"
#include "classes/gf/GfAssetSetupMob.h"
#include "classes/gf/GfAssetSetupNpc.h"
#include "classes/gf/GfAssetSetupUiObj.h"
#include "classes/gf/GfAssetSetupWeapon.h"
#include "classes/gf/GfAssetSetupBladeForUi.h"
#include "classes/gf/GfAssetSetupDriverForUi.h"
#include "classes/gf/GfAssetSetupEnemyBlade.h"
#include "classes/gf/GfAssetSetupEventBlade.h"
#include "classes/gf/GfAssetSetupEventDriver.h"
#include "classes/gf/GfAssetSetupEventEnemy.h"
#include "classes/gf/GfAssetSetupEventMob.h"
#include "classes/gf/GfAssetSetupEventNpc.h"
#include "classes/gf/GfAssetSetupSalvage.h"
#include "classes/gf/GfAssetSetupWeaponEventCS.h"
#include "gf/GfAssetPath.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfDataMob.h"
#include "gf/GfDataNpc.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfInitParam.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/GfAllocator.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfInitParamEnemy.h"
#include "classes/gf/GfInitParamNpc.h"
#include "classes/gf/GfBdatChrDr.h"
#include "classes/gf/GfBdatChrBl.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataMap.h"
#include "gf/GfUtil.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "gf/GfDataHana.h"
#include "classes/gf/GfInitParamDriver.h"
#include "classes/gf/GfInitParamEnWeapon.h"
#include "classes/gf/GfInitParamBelonging.h"
#include "classes/gf/GfInitParamExtra.h"
#include "classes/gf/GfInitParamFobj.h"
#include "classes/gf/GfInitParamWeapon.h"
#include "classes/gf/GfInitParamUiObj.h"
#include "classes/gf/GfInitParamEventObj.h"
#include "classes/gf/GfAssetPack.h"
#include "gf/GfDataWeapon.h"
#include <string.h>
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfAssetResource.h"
#include "gf/GfDataSound.h"
#include "gf/GfDataUtil.h"
#include "gf/FileStaticVec3.h"
#include "classes/gf/GfAssetSetupMapObj.h"
#include "classes/gf/GfAssetSetupMapMdl.h"
#include "classes/gf/GfInitParamMapSeamless.h"
#include "classes/gf/GfInitParamMob.h"
#include "classes/gf/GfInitParamGimmick.h"
#include "nn/diag.h"

namespace gf {

// every class's runtime type, stored by the static initializer in this order
mm::mtl::RTTI GfAssetSetup::m_rtti("GfAssetSetup", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupDriver::m_rtti("GfAssetSetupDriver", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupEventDriver::m_rtti("GfAssetSetupEventDriver", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupSalvage::m_rtti("GfAssetSetupSalvage", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupDriverForUi::m_rtti("GfAssetSetupDriverForUi", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupBlade::m_rtti("GfAssetSetupBlade", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupEventBlade::m_rtti("GfAssetSetupEventBlade", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupBladeForUi::m_rtti("GfAssetSetupBladeForUi", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupEnemy::m_rtti("GfAssetSetupEnemy", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupEnemyBlade::m_rtti("GfAssetSetupEnemyBlade", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupEventEnemy::m_rtti("GfAssetSetupEventEnemy", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupNpc::m_rtti("GfAssetSetupNpc", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupEventNpc::m_rtti("GfAssetSetupEventNpc", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupMob::m_rtti("GfAssetSetupMob", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupEventMob::m_rtti("GfAssetSetupEventMob", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupGimmick::m_rtti("GfAssetSetupGimmick", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupMapObj::m_rtti("GfAssetSetupMapObj", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupFobj::m_rtti("GfAssetSetupFobj", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupWeapon::m_rtti("GfAssetSetupWeapon", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupWeaponEventCS::m_rtti("GfAssetSetupWeaponEventCS", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupEnWeapon::m_rtti("GfAssetSetupEnWeapon", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupBelonging::m_rtti("GfAssetSetupBelonging", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupExtra::m_rtti("GfAssetSetupExtra", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupMapSeamless::m_rtti("GfAssetSetupMapSeamless", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupMapMdl::m_rtti("GfAssetSetupMapMdl", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupEventObj::m_rtti("GfAssetSetupEventObj", nullptr, nullptr);
mm::mtl::RTTI GfAssetSetupUiObj::m_rtti("GfAssetSetupUiObj", nullptr, nullptr);

GfAssetSetup::~GfAssetSetup() {
    for (RefResource*& resource : m_refResources) {
        if (resource != nullptr) {
            delete resource;
            resource = nullptr;
        }
    }
    GfAssetManager::lockEnterRersource(m_handle);
    if (m_paramCopy != nullptr) {
        delete m_paramCopy;
        m_paramCopy = nullptr;
    }
}

void GfAssetSetup::setupParam(GF_ASSET_HANDLE* handle, const GfInitParam& param) {
    m_handle = handle;
    m_objId = param.m_objId;
    m_param = &param;
    if (param.pad_18 != nullptr) {
#line 102
        m_paramCopy = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) unsigned char*(*param.pad_18);
    }
}

void GfAssetSetup::requestCoreResource(GfAssetPack* pack, GF_ASSET_HANDLE* handle, GfAssetType type) {
    if (pack == nullptr) {
        return;
    }
    GfAssetFiles& files = pack->m_files;
    const char* mdl = getMdlFile(type);
    if (mdl != nullptr) {
        if (!setupReference(pack, mdl, static_cast<GfFileIdx>(getMdlSlot()))) {
            GfAssetManager::setModelInfo(handle, mdl);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), mdl, ".wimdo");
            files.addResource(static_cast<GfFileIdx>(getMdlSlot()), path.m_str);
        }
    }
    const char* arc = getArcFile(type);
    if (arc != nullptr) {
        if (!setupReference(pack, arc, static_cast<GfFileIdx>(getArcSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), arc, ".arc");
            files.addResource(static_cast<GfFileIdx>(getArcSlot()), path.m_str);
        }
    }
    const char* mot = getMotFile(type);
    if (mot != nullptr) {
        if (!setupReference(pack, mot, static_cast<GfFileIdx>(getMotSlot()))) {
            GfAssetManager::setMotionInfo(handle, mot);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), mot, ".mot");
            files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
        }
    }
    const char* evtMot = getEvtMotFile(type);
    if (evtMot != nullptr) {
        if (!setupReference(pack, evtMot, static_cast<GfFileIdx>(getEvtMotSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEvtPath(), evtMot, ".mot");
            files.addResource(static_cast<GfFileIdx>(getEvtMotSlot()), path.m_str);
        }
    }
    const char* efp = getEfpFile(type);
    if (efp != nullptr) {
        if (!setupReference(pack, efp, static_cast<GfFileIdx>(getEfpSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), efp, ".wiefp");
            if (!files.addResource(static_cast<GfFileIdx>(getEfpSlot()), path.m_str)) {
                pack->dispAssetLogForDebug();
            }
        }
    }
    const char* eab = getEabFile(type);
    if (eab != nullptr) {
        if (!setupReference(pack, eab, static_cast<GfFileIdx>(getEabSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEffPath(), eab, ".wieab");
            files.addResource(static_cast<GfFileIdx>(getEabSlot()), path.m_str);
        }
    }
    const char* efb = getEfbFile(type);
    if (efb != nullptr) {
        if (!setupReference(pack, efb, static_cast<GfFileIdx>(getEfbSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEffPath(), efb, ".wiefb");
            files.addResource(static_cast<GfFileIdx>(getEfbSlot()), path.m_str);
        }
    }
    const char* stp = getStpFile(type);
    if (stp != nullptr) {
        mm::mtl::FixStr<128> name;
        GfAssetFilesInfo info;
        info.m_handle = handle;
        info.m_type = static_cast<GfAssetType>(12);
        info.m_name = name.m_str;
        makeAssetNamePrefix(name, info.m_type, stp, "Stp");
        GfAssetPack* stpPack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(stpPack, stp, static_cast<GfFileIdx>(getStpSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getStpPath(), stp, ".stp");
            stpPack->m_files.addResource(static_cast<GfFileIdx>(getStpSlot()), path.m_str);
        }
    }
    const char* evtStp = getEvtStpFile(type);
    if (evtStp != nullptr) {
        mm::mtl::FixStr<128> name;
        GfAssetFilesInfo info;
        info.m_handle = handle;
        info.m_type = static_cast<GfAssetType>(12);
        info.m_name = name.m_str;
        makeAssetNamePrefix(name, info.m_type, evtStp, "EvtStp");
        GfAssetPack* stpPack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(stpPack, evtStp, static_cast<GfFileIdx>(getEvtStpSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEvtPath(), evtStp, ".stp");
            stpPack->m_files.addResource(static_cast<GfFileIdx>(getEvtStpSlot()), path.m_str);
        }
    }
}

bool GfAssetSetup::setupReference(GfAssetPack* pack, const char* name, GfFileIdx idx) {
    RefResource* resource = findRefResource(idx);
    if (resource == nullptr || resource->m_data == nullptr) {
        return false;
    }
    if (pack->getResource(idx) == nullptr) {
        GfAssetResource* res =
            GfAssetResource::create(pack->getAssetName()->m_str, name, resource->m_data, resource->m_size);
        pack->m_files.addResource(idx, name);
        pack->setResource(idx, res);
    }
    return true;
}

void GfAssetSetup::makeAssetNamePrefix(mm::mtl::FixStr<128>& name, GfAssetType type, const char* file,
                                       const char* suffix) {
    name.format("%2d", type);
    if (file != nullptr) {
        name += util::getNoPathExtName(file).m_str;
    }
    if (suffix != nullptr) {
        name += util::getNoPathExtName(suffix).m_str;
    }
}

void GfAssetSetup::setRefResource(unsigned int index, const char* name, void* data, unsigned int size) {
    mm::mtl::FixStr<128> file;
    bool event = m_param != nullptr && m_param->m_createType == 3;
    const char* model = nullptr;
    if (strstr(name, ".wimdo") != nullptr) {
        GfBdatChrDr* chrDr = mm::mtl::PtrSingleton<GfBdatChrDr>::sys();
        for (unsigned int driver = 1; driver < 7; driver++) {
            if (GfDataDriver::isAttachedParty(driver) && strstr(name, chrDr->getChrDrModel(driver)) != nullptr) {
                model = GfGameUtil::getAcceDriverModel(driver, true, event);
                if (model != nullptr) {
                    break;
                }
            }
        }
        if (model == nullptr) {
            GfBdatChrBl* chrBl = mm::mtl::PtrSingleton<GfBdatChrBl>::sys();
            for (unsigned int blade = chrBl->getChrBlStart(); blade < chrBl->getChrBlEnd(); blade++) {
                if (GfDataBlade::isAttachedParty(blade) && strstr(name, chrBl->getChrBlModel(blade)) != nullptr) {
                    model = GfGameUtil::getAcceBladeModel(blade);
                    if (model != nullptr) {
                        break;
                    }
                }
            }
        }
    }
    if (model != nullptr) {
        file.format("model/%s%s", model, ".wimdo");
    } else {
        file = name;
    }
    RefResource* resource = findRefResource(index);
    if (resource == nullptr) {
#line 333
        resource = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) RefResource;
        m_refResources.push_back(resource);
        resource->m_fileIdx = static_cast<GfFileIdx>(index);
    }
    resource->m_name = file.m_str;
    resource->m_data = data;
    resource->m_size = size;
    pad_f0 = 1;
}

void GfAssetSetup::requestFootStepSePackFile(GfAssetFilesInfo& info, unsigned int footStep, GfFileIdx idx0,
                                             GfFileIdx idx1) {
    mm::mtl::FixedVector<const char*, 2> files;
    if (GfDataSound::getFootStepSePackFile(files, footStep)) {
        mm::mtl::FixStr<128> name;
        info.m_type = static_cast<GfAssetType>(19);
        info.m_backupTypes.clear();
        info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
        info.m_name = name.m_str;
        for (unsigned int i = 0; i < files.size(); i++) {
            makeAssetNamePrefix(name, info.m_type, *files.at(i), "");
            GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
            GfFileIdx idx = i == 0 ? idx0 : idx1;
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", GfAssetPath::getSePack(), files[i], ".xsp");
            pack->m_files.addResource(idx, path.m_str);
            pack->m_sePackId = idx;
        }
    }
}

void GfAssetSetup::requestWpnSePackFile(GfAssetFilesInfo& info, unsigned int weaponType, GfFileIdx idx) {
    const char* file = GfDataSound::getSeFileByWeaponType(weaponType);
    if (file == nullptr) {
        return;
    }
    mm::mtl::FixStr<128> name;
    info.m_type = static_cast<GfAssetType>(19);
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    info.m_name = name.m_str;
    makeAssetNamePrefix(name, info.m_type, file, "");
    GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
    GfFileIdx packIdx = static_cast<GfFileIdx>(weaponType + idx - 1);
    mm::mtl::FixStr<128> path;
    path.format("%s%s%s", GfAssetPath::getSePack(), file, ".xsp");
    pack->m_files.addResource(packIdx, path.m_str);
    pack->m_sePackId = packIdx;
}

GfAssetSetupDriver::GfAssetSetupDriver() : pad_1fc(-1) {}

bool GfAssetSetupDriver::makeAssetNameWpnType(mm::mtl::FixStr<128>& name, GfAssetType type, unsigned int driver,
                                              unsigned int weaponType, unsigned int blade) {
    name = "";
    mm::mtl::FixStr<128> anim;
    bool found = GfDataDriver::getDriverAddAnim(anim, driver, weaponType);
    if (anim.m_nLen == 0 || !found) {
        return false;
    }
    mm::mtl::FixStr<32> suffix;
    if (blade < 10) {
        suffix.format("_bl000%d", blade);
    } else if (blade < 100) {
        suffix.format("_bl00%d", blade);
    } else if (blade < 1000) {
        suffix.format("_bl0%d", blade);
    } else {
        suffix.format("_bl%2d", blade);
    }
    makeAssetNamePrefix(name, type, anim.m_str, suffix.m_str);
    return true;
}

void GfAssetSetupDriver::requestIraSePackFile(GfAssetFilesInfo& info) {
    if (!GfDataDriver::isIra(m_objId)) {
        return;
    }
    mm::mtl::FixStr<128> name;
    info.m_type = static_cast<GfAssetType>(19);
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    info.m_name = name.m_str;
    GfBdatChrDr* chrDr = GfBdatChrDr::sys();
    unsigned int ira = chrDr->getChrDrIraParam(m_objId);
    const char* model = GfAssetSetupDriver::getMdlFile(getAssetType());
    if (model == nullptr) {
        return;
    }
    makeAssetNamePrefix(name, info.m_type, model, "IraD");
    GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
    mm::mtl::FixStr<128> path;
    path.format("%s%s%s", GfAssetPath::getSePack(), chrDr->getChrIrSeDriver(ira), ".xsp");
    pack->m_files.addResource(static_cast<GfFileIdx>(54), path.m_str);
    pack->m_sePackId = static_cast<GfFileIdx>(54);
    makeAssetNamePrefix(name, info.m_type, model, "IraB");
    pack = GfAssetManager::createAssetFiles(info);
    path.format("%s%s%s", GfAssetPath::getSePack(), chrDr->getChrIrSeBlade(ira), ".xsp");
    pack->m_files.addResource(static_cast<GfFileIdx>(55), path.m_str);
    pack->m_sePackId = static_cast<GfFileIdx>(55);
}

const char* GfAssetSetupDriver::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = GfGameUtil::getDriverModel(m_objId, isEventCreateType(m_param->m_createType), m_param->m_createType == 3);
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupDriver::getArcFile(GfAssetType type) {
    RefResource* resource = findRefResource(getArcSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = GfGameUtil::getDriverModel(m_objId, isEventCreateType(m_param->m_createType), m_param->m_createType == 3);
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupDriver::getMotFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
            const char* name = acc.getMotionResourceName();
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupDriver::getEfpFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupDriver::getEabFile(GfAssetType type) {
    DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
    return acc.getEffectResourceName();
}

const char* GfAssetSetupDriver::getEfbFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        return getEabFile(type);
    }
    return nullptr;
}

const char* GfAssetSetupDriver::getEfTailFile(GfAssetType type) {
    if (type == 16) {
        return getEabFile(type);
    }
    return nullptr;
}

const char* GfAssetSetupDriver::getStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
        return validName(acc.getMotionResourceName());
    }
    return nullptr;
}

const char* GfAssetSetupDriver::getPath() const {
    return GfAssetPath::getMdoModel();
}

GfAssetType GfAssetSetupDriver::getAssetType() const {
    return static_cast<GfAssetType>(GfGameManager::isGameTypeIra() ? 5 : 4);
}

GfAssetType GfAssetSetupDriver::getAssetTypeMot() const {
    return static_cast<GfAssetType>(GfGameManager::isGameTypeIra() ? 7 : 5);
}

const char* GfAssetSetupEventDriver::getEvtMotFile(GfAssetType type) {
    if (getAssetTypeEvtMot() == type) {
        RefResource* resource = findRefResource(getEvtMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
            const char* name = acc.getMotionResourceName();
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupEventDriver::getEvtStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
        return validName(acc.getMotionResourceName());
    }
    return nullptr;
}

const char* GfAssetSetupEventDriver::getEvtPath() const {
    return GfAssetPath::getEvt();
}

void GfAssetSetupSalvage::setup(GF_ASSET_HANDLE* handle, const GfInitParamDriver& param) {
    setupParam(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;

    info.m_type = getAssetType();
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "");
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);

    info.m_type = getAssetTypeMot();
    const char* mot = getMotFile(info.m_type);
    if (mot != nullptr) {
        makeAssetNamePrefix(name, info.m_type, mot, "");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getMotSlot()))) {
            GfAssetManager::setMotionInfo(handle, mot);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), mot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
        }
    }

    info.m_type = getAssetTypeMot();
    const char* efb = getEfbFile(info.m_type);
    if (efb != nullptr) {
        makeAssetNamePrefix(name, info.m_type, efb, "");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, efb, static_cast<GfFileIdx>(getEfbSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEffPath(), efb, ".wiefb");
            pack->m_files.addResource(static_cast<GfFileIdx>(getEfbSlot()), path.m_str);
        }
    }

    info.m_type = static_cast<GfAssetType>(16);
    const char* salvageMot = getSalvageMotFile(info.m_type);
    if (salvageMot != nullptr) {
        makeAssetNamePrefix(name, info.m_type, salvageMot, getAssetCategoryName());
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, salvageMot, static_cast<GfFileIdx>(getSalvageMotSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), salvageMot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getSalvageMotSlot()), path.m_str);
        }
    }

    info.m_type = getAssetType();
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    const char* stp = getSalvageStpFile(info.m_type);
    if (stp != nullptr) {
        makeAssetNamePrefix(name, info.m_type, stp, getAssetCategoryName());
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, stp, static_cast<GfFileIdx>(getSalvageStpSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getStpPath(), stp, ".stp");
            pack->m_files.addResource(static_cast<GfFileIdx>(getSalvageStpSlot()), path.m_str);
        }
    }

    unsigned int footStep;
    {
        DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
        footStep = acc.getFootStep();
    }
    requestFootStepSePackFile(info, footStep, static_cast<GfFileIdx>(1), static_cast<GfFileIdx>(2));
}

const char* GfAssetSetupSalvage::getMdlFile(GfAssetType type) {
    return GfGameUtil::getSalvageDriverModel(m_objId);
}

const char* GfAssetSetupSalvage::getArcFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupSalvage::getSalvageMotFile(GfAssetType type) {
    if (type == 16) {
        DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
        const char* name = validName(acc.getMotionResourceName());
        // the file name with its number appended (the name is not the original's)
        static mm::mtl::FixStr<128> s_name;
        s_name.clear();
        s_name.format("%s_%d", name, 99);
        return s_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupSalvage::getSalvageStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
        const char* name = validName(acc.getMotionResourceName());
        // the file name with its number appended (the name is not the original's)
        static mm::mtl::FixStr<128> s_name;
        s_name.clear();
        s_name.format("%s_%d", name, 99);
        return s_name.m_str;
    }
    return nullptr;
}

namespace {
// the driver's UI event motion: its model's name with "_98" appended, kept in a static (only
// GfAssetSetupDriverForUi::setup uses it; an internal helper, as its static is created after the getters'; the
// name is not the original's)
const char* makeUiEventMotName(unsigned int driver) {
    DataParamAcc acc(3, driver, static_cast<GimmickType>(0));
    const char* name = GfAssetSetup::validName(GfGameUtil::getDriverModel(driver, false, false));
    static mm::mtl::FixStr<128> s_name;
    s_name.clear();
    s_name.format("%s_%d", name, 98);
    return s_name.m_str;
}
}  // namespace

void GfAssetSetupDriverForUi::setup(GF_ASSET_HANDLE* handle, const GfInitParamDriver& param) {
    setupParam(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;

    info.m_type = getAssetType();
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "");
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);

    info.m_type = getAssetTypeMot();
    const char* mot = getMotFile(info.m_type);
    if (mot != nullptr) {
        makeAssetNamePrefix(name, info.m_type, mot, "");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getMotSlot()))) {
            GfAssetManager::setMotionInfo(handle, mot);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), mot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
        }
    }

    info.m_type = static_cast<GfAssetType>(18);
    const char* uiMot = getUiMotFile(info.m_type);
    if (uiMot != nullptr) {
        makeAssetNamePrefix(name, info.m_type, uiMot, "");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, uiMot, static_cast<GfFileIdx>(getUiMotSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), uiMot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getUiMotSlot()), path.m_str);
        }
    }

    if (GfGameUtil::isNeedRetargetDriver(param.m_objId, false, false)) {
        const char* evtMot = makeUiEventMotName(param.m_objId);
        makeAssetNamePrefix(name, info.m_type, evtMot, "DR");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(0x45))) {
            GfAssetManager::setMotionInfo(handle, evtMot);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), evtMot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(0x45), path.m_str);
            path.format("%s%s%s", getPath(), GfDataDriver::getModelResourceName(param.m_objId), ".arc");
            pack->m_files.addResource(static_cast<GfFileIdx>(0x44), path.m_str);
        }
    }

    info.m_type = getAssetType();
    const char* stp = getUiStpFile(info.m_type);
    if (stp != nullptr) {
        makeAssetNamePrefix(name, info.m_type, stp, getAssetCategoryName());
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, stp, static_cast<GfFileIdx>(getUiStpSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getStpPath(), stp, ".stp");
            pack->m_files.addResource(static_cast<GfFileIdx>(getUiStpSlot()), path.m_str);
        }
    }

    info.m_type = getAssetTypeMot();
    const char* efb = getEfbFile(info.m_type);
    if (efb != nullptr) {
        makeAssetNamePrefix(name, info.m_type, efb, "");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, efb, static_cast<GfFileIdx>(getEfbSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEffPath(), efb, ".wiefb");
            pack->m_files.addResource(static_cast<GfFileIdx>(getEfbSlot()), path.m_str);
        }
    }

    info.m_type = static_cast<GfAssetType>(18);
    for (unsigned int i = 0; i < param.pad_98.size(); i++) {
        unsigned int weaponType = GfDataWeapon::getAsmWeaponType(param.pad_98.at(i)->m_weaponId);
        long slot = param.pad_98[i].m_slot;
        unsigned int weaponId = param.pad_98[i].m_weaponId;
        unsigned int blade = param.pad_98[i].m_bladeId;
        if (weaponType != 0) {
            int index = slot < 0 ? static_cast<int>(i) : slot;
            if (GfAssetSetupDriver::makeAssetNameWpnType(name, info.m_type, m_objId, weaponType, blade)) {
                info.m_name = name.m_str;
                GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
                mm::mtl::FixStr<128> anim;
                if (GfDataDriver::getDriverAddAnim(anim, m_objId, weaponType)) {
                    if (!setupReference(pack, anim.m_str,
                                        static_cast<GfFileIdx>(GfDataDriver::getWeaponAnmFileIdx(index)))) {
                        mm::mtl::FixStr<128> path;
                        path.format("%s%s%s", getPath(), anim.m_str, ".mot");
                        pack->m_files.addResource(static_cast<GfFileIdx>(GfDataDriver::getWeaponAnmFileIdx(index)),
                                                  path.m_str);
                        path.format("%s%s%s", getEffPath(), anim.m_str, ".wieab");
                        pack->m_files.addResource(static_cast<GfFileIdx>(GfDataDriver::getWeaponEabFileIdx(index)),
                                                  path.m_str);
                    }
                }
            }
        }
    }

    unsigned int footStep;
    {
        DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
        footStep = acc.getFootStep();
    }
    requestFootStepSePackFile(info, footStep, static_cast<GfFileIdx>(1), static_cast<GfFileIdx>(2));
}

const char* GfAssetSetupDriverForUi::getUiMotFile(GfAssetType type) {
    if (type == 18) {
        DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
        const char* name = validName(acc.getMotionResourceName());
        // the file name with its number appended (the name is not the original's)
        static mm::mtl::FixStr<128> s_name;
        s_name.clear();
        s_name.format("%s_%d", name, 98);
        return s_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupDriverForUi::getUiStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        DataParamAcc acc(3, m_objId, static_cast<GimmickType>(0));
        const char* name = validName(acc.getMotionResourceName());
        // the file name with its number appended (the name is not the original's)
        static mm::mtl::FixStr<128> s_name;
        s_name.clear();
        s_name.format("%s_%d", name, 98);
        return s_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupBladeForUi::getUiMotFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        DataParamAcc acc(4, m_objId, static_cast<GimmickType>(0));
        const char* name = validName(acc.getMotionResourceName());
        // the file name with its number appended (the name is not the original's)
        static mm::mtl::FixStr<128> s_name;
        s_name.clear();
        s_name.format("%s_%d", name, 98);
        return s_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupBladeForUi::getUiStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        DataParamAcc acc(4, m_objId, static_cast<GimmickType>(0));
        const char* name = validName(acc.getMotionResourceName());
        // the file name with its number appended (the name is not the original's)
        static mm::mtl::FixStr<128> s_name;
        s_name.clear();
        s_name.format("%s_%d", name, 98);
        return s_name.m_str;
    }
    return nullptr;
}

GfAssetSetupBlade::GfAssetSetupBlade() : pad_1fc(0) {}

const char* GfAssetSetupBlade::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = GfGameUtil::getBladeModel(m_objId, false);
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupBlade::getArcFile(GfAssetType type) {
    RefResource* resource = findRefResource(getArcSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = GfGameUtil::getBladeModel(m_objId, false);
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupBlade::getRetargetMotFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            const char* name = GfGameUtil::getBladeMotion(m_objId, false);
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupBlade::getEfpFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupBlade::getEabFile(GfAssetType type) {
    DataParamAcc acc(4, m_objId, static_cast<GimmickType>(0));
    return acc.getEffectResourceName();
}

const char* GfAssetSetupBlade::getEfbFile(GfAssetType type) {
    GfAssetType efbType = getAssetTypeEfb();
    if (type == 18 || efbType == type) {
        return getEabFile(type);
    }
    return nullptr;
}

const char* GfAssetSetupBlade::getStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        DataParamAcc acc(4, m_objId, static_cast<GimmickType>(0));
        return validName(acc.getMotionResourceName());
    }
    return nullptr;
}

const char* GfAssetSetupBlade::getPath() const {
    return GfAssetPath::getMdoModel();
}

const char* GfAssetSetupEventBlade::getEvtMotFile(GfAssetType type) {
    if (getAssetTypeEventMot() == type) {
        RefResource* resource = findRefResource(getEvtMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            const char* name = GfGameUtil::getBladeMotion(m_objId, pad_1fc == 0);
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupEventBlade::getEvtStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        DataParamAcc acc(4, m_objId, static_cast<GimmickType>(0));
        return validName(acc.getMotionResourceName());
    }
    return nullptr;
}

const char* GfAssetSetupEventBlade::getEvtPath() const {
    return GfAssetPath::getEvt();
}

const char* GfAssetSetupEventBlade::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = GfGameUtil::getBladeModel(m_objId, pad_1fc == 0);
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupEventBlade::getArcFile(GfAssetType type) {
    RefResource* resource = findRefResource(getArcSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = GfGameUtil::getBladeModel(m_objId, pad_1fc == 0);
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupEventBlade::getRetargetMotFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            const char* name = GfGameUtil::getBladeMotion(m_objId, pad_1fc == 0);
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

GfAssetSetupEnemy::GfAssetSetupEnemy() : m_enemyParam(nullptr) {}

void GfAssetSetupEnemy::makeEnemyEffectAssetName(mm::mtl::FixStr<128>& name, const GfInitParamEnemy& param,
                                                 unsigned int attribute) {
    makeAssetNamePrefix(name, static_cast<GfAssetType>(13), getEabFile(static_cast<GfAssetType>(13)), "");
    if (attribute == 0) {
        return;
    }
    mm::mtl::FixStr<16> weapon;
    if (GfDataBlade::getBladeWpnType(param.getBladeID()) != 0) {
        unsigned int type = GfDataWeapon::getAsmWeaponType(GfDataBlade::getBladeWpnType(param.getBladeID()));
        if (type >= 10) {
            weapon.format("%d", type);
        } else {
            weapon.format("0%d", type);
        }
        name += "_";
        name += weapon.m_str;
    }
    name += "_";
    name += GfDataUtil::getAttributeFileName(attribute);
}

unsigned int GfAssetSetupEnemy::getEnemyAttribute(const GfInitParamEnemy& param) {
    unsigned int attr = GfBdatChrEnArrange::sys()->getChrEnArrangeBladeAtr(param.getEnArrangeID());
    unsigned int blade = param.getBladeID();
    if (attr != 0) {
        return attr;
    }
    if (GfDataBlade::getCommonBladeName(getMdlFile(getAssetType())) ||
        GfBdatChrEnArrange::sys()->getChrEnArrangeDriverLev(param.getEnArrangeID()) != 0) {
        attr = GfDataBlade::getAttribute(blade);
        if (attr != 0) {
            return attr;
        }
    }
    if (!GfDataHana::isValid(param.getBladeID())) {
        return 0;
    }
    attr = GfDataBlade::getAttribute(blade);
    if (attr == 0) {
        if (blade == 1005) {
            attr = 5;
        } else if (blade == 1006) {
            attr = 1;
        } else if (blade == 1007) {
            attr = 5;
        }
    }
    return attr;
}

void GfAssetSetupEnemy::getEnemyEabFileName(mm::mtl::FixStr<128>& name, const GfInitParamEnemy& param,
                                            GfAssetType type) {
    const char* file = getEabFile(type);
    if (file != nullptr && (strstr(file, "en/") != nullptr || strstr(file, "np/") != nullptr)) {
        name.format("%s%s%s", getEffPath(), file, ".wieab");
        return;
    }
    unsigned int blade = param.getBladeID();
    if (!GfDataBlade::isRegularBlade(blade) || param.m_createType == 5 || GfDataHana::isValid(blade)) {
        name.format("%s%s%s%s", getEffPath(), file, GfDataBlade::getBaseEabWeaponName(blade), ".wieab");
    } else {
        name.format("%s%s%s%s", getEffPath(), file, GfDataBlade::getBaseEfbWeaponName(blade), ".wieab");
    }
}

void GfAssetSetupEnemy::getEnemyEfbFileName(mm::mtl::FixStr<128>& name, const GfInitParamEnemy& param,
                                            GfAssetType type, unsigned int attribute) {
    unsigned int blade = param.getBladeID();
    const char* file = getEfbFile(type);
    if ((file != nullptr && (strstr(file, "en/") != nullptr || strstr(file, "np/") != nullptr)) ||
        (GfDataBlade::isRegularBlade(blade) && param.m_createType == 5 && !GfDataHana::isValid(blade))) {
        name.format("%s%s%s", getEffPath(), file, ".wiefb");
        return;
    }
    if (blade == 1010) {
        attribute = 0;
    }
    name.format("%s%s%s%s%s", getEffPath(), file, GfDataBlade::getBaseEfbWeaponName(blade),
                GfDataBlade::getBaseEfbAttributeName(blade, attribute), ".wiefb");
}

void GfAssetSetupEnemy::setup(GF_ASSET_HANDLE* handle, const GfInitParamEnemy& param) {
    m_enemyParam = &param;
    setupParam(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    info.m_type = getAssetType();
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "");
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);

    info.m_type = getAssetTypeArc();
    const char* arc = getArcFile(info.m_type);
    if (arc != nullptr) {
        makeAssetNamePrefix(name, info.m_type, arc, "En");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getArcSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), arc, ".arc");
            pack->m_files.addResource(static_cast<GfFileIdx>(getArcSlot()), path.m_str);
        }
    }

    info.m_type = getAssetTypeMot();
    if (!GfGameUtil::isNeedRetargetDriverResource(getMdlFile(getAssetType()))) {
        const char* mot = getRetargetMotFile(info.m_type);
        if (mot != nullptr) {
            makeAssetNamePrefix(name, info.m_type, mot, "");
            GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
            if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getRetargetMotSlot()))) {
                GfAssetManager::setMotionInfo(handle, mot);
                mm::mtl::FixStr<128> path;
                path.format("%s%s%s", getPath(), mot, ".mot");
                pack->m_files.addResource(static_cast<GfFileIdx>(getRetargetMotSlot()), path.m_str);
                const char* add = GfDataEnemy::getAddMotionName(m_objId);
                if (add != nullptr) {
                    path.format("%s%s%s", getPath(), add, ".mot");
                    pack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
                }
            }
        }
    } else {
        const char* mdl = getMdlFile(getAssetType());
        mm::mtl::FixStr<128> path;
        makeAssetNamePrefix(name, info.m_type, mdl, "");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getRetargetMotSlot()))) {
            GfAssetManager::setMotionInfo(handle, mdl);
            path.format("%s%s%s", getPath(), mdl, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getRetargetMotSlot()), path.m_str);
        }
        unsigned int driver = GfGameUtil::getNeedRetargetDriverId(getMdlFile(getAssetType()));
        makeAssetNamePrefix(name, info.m_type, mdl, "DR");
        GfAssetPack* drPack = GfAssetManager::createAssetFiles(info);
        path.format("%s%s%s", getPath(), GfDataDriver::getModelResourceName(driver), ".mot");
        drPack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
    }

    info.m_type = static_cast<GfAssetType>(18);
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(11));
    const char* evt = getEvtMotFile(info.m_type);
    if (evt != nullptr) {
        makeAssetNamePrefix(name, info.m_type, evt, "Evt");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEvtMotSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEvtPath(), evt, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getEvtMotSlot()), path.m_str);
        }
    }

    info.m_type = static_cast<GfAssetType>(13);
    unsigned int blade = param.getBladeID();
    unsigned int attribute = getEnemyAttribute(param);
    makeEnemyEffectAssetName(name, param, attribute);
    GfAssetPack* effPack = GfAssetManager::createAssetFiles(info);
    if (!setupReference(effPack, name.m_str, static_cast<GfFileIdx>(getEabSlot()))) {
        mm::mtl::FixStr<128> path;
        getEnemyEabFileName(path, param, info.m_type);
        effPack->m_files.addResource(static_cast<GfFileIdx>(getEabSlot()), path.m_str);
    }
    const char* efb = getEfbFile(info.m_type);
    if (efb != nullptr) {
        if (!setupReference(effPack, name.m_str, static_cast<GfFileIdx>(getEfbSlot()))) {
            mm::mtl::FixStr<128> path;
            getEnemyEfbFileName(path, param, info.m_type, attribute);
            effPack->m_files.addResource(static_cast<GfFileIdx>(getEfbSlot()), path.m_str);
        }
        if (param.m_createType == 5) {
            if (attribute == 0) {
                mm::mtl::FixStr<16> weapon;
                if (GfDataBlade::getBladeWpnType(blade) != 0) {
                    unsigned int type = GfDataWeapon::getAsmWeaponType(GfDataBlade::getBladeWpnType(blade));
                    if (type >= 10) {
                        weapon.format("%d", type);
                    } else {
                        weapon.format("0%d", type);
                    }
                    name += "_";
                    name += weapon.m_str;
                }
            }
            name += "Db";
            GfAssetPack* dbPack = GfAssetManager::createAssetFiles(info);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s_deathblow_%s%s", getEffPath(), efb, GfDataBlade::getDeathBlowWeaponName(blade), "00",
                        ".wieab");
            dbPack->m_files.addResource(
                static_cast<GfFileIdx>(GfDataDriver::getDeathBlowEabFileIdx(static_cast<DBSLOT>(0), 0)), path.m_str);
            if (attribute == 0) {
                path.format("%s%s%s_deathblow_%s%s", getEffPath(), efb, GfDataBlade::getDeathBlowWeaponName(blade),
                            "00", ".wiefb");
            } else {
                path.format("%s%s%s_deathblow_%s%s%s", getEffPath(), efb, GfDataBlade::getDeathBlowWeaponName(blade),
                            "00", GfDataBlade::getBaseEfbAttributeName(blade, attribute), ".wiefb");
            }
            dbPack->m_files.addResource(
                static_cast<GfFileIdx>(GfDataDriver::getDeathBlowEfbFileIdx(static_cast<DBSLOT>(0), 0)), path.m_str);
        }
    }

    info.m_type = static_cast<GfAssetType>(13);
    {
        GfAssetType motType = getAssetTypeMot();
        const char* mot = getRetargetMotFile(motType);
        mm::mtl::FixStr<128> file;
        mm::mtl::FixStr<128> path;
        unsigned int arrange = param.m_arrangeId;
        if (mot == nullptr || (strstr(mot, "en/") == nullptr && strstr(mot, "np/") == nullptr)) {
            DataParamAcc acc(5, arrange, static_cast<GimmickType>(0));
            unsigned int type = GfDataWeapon::getAsmWeaponType(acc.getWeaponType(-1, false));
            if (type == 0) {
                file.format("%s", mot, type);
            } else if (type < 10) {
                file.format("%s_0%d", mot, type);
            } else {
                file.format("%s_%d", mot, type);
            }
        } else {
            file = mot;
        }
        mm::mtl::FixStr<16> weapon;
        if (param.m_createType == 5) {
            GfDataBlade::getBladeWpnType(blade);
            unsigned int type = GfDataWeapon::getAsmWeaponType(GfDataBlade::getBladeWpnType(blade));
            if (type >= 10) {
                weapon.format("%d", type);
            } else {
                weapon.format("0%d", type);
            }
        }
        makeAssetNamePrefix(name, info.m_type, file.m_str, "");
        if (weapon.m_nLen != 0) {
            name += "_";
            name += weapon.m_str;
        }
        name += "Swt";
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (param.m_createType == 5) {
            path.format("%s%s%s%s", getPath(), file.m_str, GfDataBlade::getDeathBlowWeaponName(blade), ".wiswt");
        } else {
            path.format("%s%s%s", getPath(), file.m_str, ".wiswt");
        }
        pack->m_files.addResource(static_cast<GfFileIdx>(17), path.m_str);
    }

    unsigned int weaponType = GfDataWeapon::getAsmWeaponType(GfDataEnemy::getWeaponType(param.m_arrangeId));
    if (weaponType != 0) {
        info.m_type = static_cast<GfAssetType>(16);
        // the driver's added animation's name (an inlined helper like GfAssetSetupDriver::makeAssetNameWpnType)
        bool named = [&](unsigned int arrange, unsigned int weapon) {
            name = "";
            mm::mtl::FixStr<128> anim;
            bool found = GfDataEnemy::getDriverAddAnim(anim, arrange, weapon);
            if (anim.m_nLen == 0 || !found) {
                return false;
            }
            makeAssetNamePrefix(name, static_cast<GfAssetType>(16), anim.m_str, "en");
            return true;
        }(param.m_arrangeId, weaponType);
        if (named) {
            GfAssetPack* animPack = GfAssetManager::createAssetFiles(info);
            mm::mtl::FixStr<128> path;
            mm::mtl::FixStr<128> file;
            if (GfDataEnemy::getDriverAddAnim(file, param.m_arrangeId, weaponType)) {
                if (!setupReference(animPack, file.m_str, static_cast<GfFileIdx>(16))) {
                    path.format("%s%s%s", getPath(), file.m_str, ".mot");
                    animPack->m_files.addResource(static_cast<GfFileIdx>(16), path.m_str);
                }
                mm::mtl::FixStr<128> model;
                mm::mtl::FixStr<128> deathBlow;
                GfDataEnemy::getDriverEffect(model, deathBlow, param.m_arrangeId, weaponType);
                info.m_type = static_cast<GfAssetType>(13);
                makeAssetNamePrefix(name, static_cast<GfAssetType>(13), file.m_str, "");
                GfAssetPack* drEffPack = GfAssetManager::createAssetFiles(info);
                const char* eff = blade == 1103 ? file.m_str : model.m_str;
                path.format("%s%s%s", getEffPath(), eff, ".wiefb");
                drEffPack->m_files.addResource(static_cast<GfFileIdx>(19), path.m_str);
                path.format("%s%s%s", getEffPath(), eff, ".wieab");
                drEffPack->m_files.addResource(static_cast<GfFileIdx>(18), path.m_str);
                path.format("%s%s_deathblow_%s%s", getEffPath(), deathBlow.m_str, "00", ".wieab");
                drEffPack->m_files.addResource(
                    static_cast<GfFileIdx>(GfDataDriver::getDeathBlowEabFileIdx(static_cast<DBSLOT>(0), 0)),
                    path.m_str);
                if (GfDataHana::isValid(blade)) {
                    path.format("%s%s_deathblow_%s%s%s", getEffPath(), deathBlow.m_str, "00",
                                GfDataBlade::getBaseEfbAttributeName(blade, attribute), ".wiefb");
                } else {
                    path.format("%s%s_deathblow_%s%s", getEffPath(), deathBlow.m_str, "00", ".wiefb");
                }
                drEffPack->m_files.addResource(
                    static_cast<GfFileIdx>(GfDataDriver::getDeathBlowEfbFileIdx(static_cast<DBSLOT>(0), 0)),
                    path.m_str);
            }
        }
    }

    requestIraDriverEffect();

    info.m_type = static_cast<GfAssetType>(19);
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    const char* se = GfDataEnemy::getSePack(m_objId);
    if (se != nullptr && *se != '\0') {
        makeAssetNamePrefix(name, info.m_type, se, "");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        pack->m_sePackId = 0;
        if (!setupReference(pack, se, static_cast<GfFileIdx>(0))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getSePackPath(), se, ".xsp");
            pack->m_files.addResource(static_cast<GfFileIdx>(0), path.m_str);
            if (strstr(se, "dlc_se_btl_bl_") != nullptr) {
                makeAssetNamePrefix(name, info.m_type, se, "WPN");
                GfAssetPack* wpnPack = GfAssetManager::createAssetFiles(info);
                wpnPack->m_sePackId = 0;
                mm::mtl::FixStr<128> file(se);
                mm::mtl::FixStr<128> prefix("dlc_se_btl_dr_w");
                // "dlc_se_btl_bl_" replaced by the driver's "dlc_se_btl_dr_w" (the new text's length is read
                // before the cut, as replace() reads it)
                int prefixLen = prefix.m_nLen;
                if (0 < file.m_nLen) {
                    file.cutFront(14);
                }
                file.insert(0, prefix.m_str, prefixLen);
                path.format("%s%s%s", getSePackPath(), file.m_str, ".xsp");
                wpnPack->m_files.addResource(static_cast<GfFileIdx>(0), path.m_str);
            }
        }
    }

    unsigned int footStep;
    {
        DataParamAcc acc(5, m_enemyParam->getEnArrangeID(), static_cast<GimmickType>(0));
        footStep = acc.getFootStep();
    }
    requestFootStepSePackFile(info, footStep, static_cast<GfFileIdx>(1), static_cast<GfFileIdx>(2));
}

const char* GfAssetSetupEnemy::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        unsigned char* fp = GfDataBdat::getFP(165);
        unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
        unsigned int id = m_objId;
        const char* name = validName(reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Model", id, 7)));
        return fn_71001BD044(name, m_enemyParam->m_createType == 3);
    }
    return resource->m_name.m_str;
}

const char* fn_71001BD044(const char* name, bool createType3) {
    GfBdatChrDr* chrDr = GfBdatChrDr::sys();
    for (unsigned int driver = 1; driver <= 6; driver++) {
        if (GfDataDriver::isAttachedParty(driver) && strcmp(name, chrDr->getChrDrModel(driver)) == 0) {
            return GfGameUtil::getDriverModel(driver, false, createType3);
        }
    }
    GfBdatChrBl* chrBl = GfBdatChrBl::sys();
    for (unsigned int blade = chrBl->getChrBlStart(); blade < chrBl->getChrBlEnd(); blade++) {
        if (GfDataBlade::isAttachedParty(blade) && strcmp(name, chrBl->getChrBlModel(blade)) == 0) {
            return GfGameUtil::getBladeModel(blade, false);
        }
    }
    return name;
}

const char* GfAssetSetupEnemy::getArcFile(GfAssetType type) {
    if (getAssetTypeArc() == type) {
        return getMdlFile(type);
    }
    return nullptr;
}

const char* GfAssetSetupEnemy::getMotFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            unsigned char* fp = GfDataBdat::getFP(165);
            unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
            unsigned int id = m_objId;
            const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Model", id, 7));
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupEnemy::getRetargetMotFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            unsigned char* fp = GfDataBdat::getFP(165);
            unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
            unsigned int id = m_objId;
            const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Motion", id, 7));
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupEnemy::getEfpFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupEnemy::getEabFile(GfAssetType type) {
    if (type == 13) {
        const char* name = GfBdatRsc::sys()->getRscEnComp_Eff(m_objId);
        if (name != nullptr && *name != '\0') {
            return name;
        }
        name = GfBdatRsc::sys()->getRscEnEffectPack(m_objId);
        if (name != nullptr && *name != '\0') {
            return name;
        }
        return getEfpFile(static_cast<GfAssetType>(13));
    }
    return nullptr;
}

const char* GfAssetSetupEnemy::getEfbFile(GfAssetType type) {
    if (type == 13) {
        return getEabFile(type);
    }
    return nullptr;
}

const char* GfAssetSetupEnemy::getStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        unsigned char* fp = GfDataBdat::getFP(165);
        unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
        unsigned int id = m_objId;
        const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Motion", id, 7));
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return nullptr;
}

const char* GfAssetSetupEnemy::getPath() const {
    return "/model/";
}

GfAssetSetupEnemyBlade::GfAssetSetupEnemyBlade() {}

const char* GfAssetSetupEnemyBlade::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        return fn_71001BD044(GfDataBlade::getResourceNameModel(m_enemyParam->m_bladeId),
                             m_enemyParam->m_createType == 3);
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupEnemyBlade::getMotFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            return GfDataBlade::getResourceNameMotion(m_enemyParam->m_bladeId);
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupEnemyBlade::getRetargetMotFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            return GfDataBlade::getResourceNameMotion(m_enemyParam->m_bladeId);
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupEnemyBlade::getPath() const {
    return GfAssetPath::getMdoModel();
}

void GfAssetSetupEventEnemy::setup(GF_ASSET_HANDLE* handle, const GfInitParamEnemy& param) {
    m_enemyParam = &param;
    setupParam(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    info.m_type = getAssetType();
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "Mdl");
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);

    info.m_type = getAssetTypeArc();
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    const char* arc = getArcFile(info.m_type);
    if (arc != nullptr) {
        makeAssetNamePrefix(name, info.m_type, arc, "EV");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getArcSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), arc, ".arc");
            pack->m_files.addResource(static_cast<GfFileIdx>(getArcSlot()), path.m_str);
        }
    }

    info.m_type = getAssetTypeMot();
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    const char* mot = getRetargetMotFile(info.m_type);
    if (mot != nullptr) {
        makeAssetNamePrefix(name, info.m_type, mot, "Mot");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getRetargetMotSlot()))) {
            GfAssetManager::setMotionInfo(handle, mot);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), mot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getRetargetMotSlot()), path.m_str);
        }
    }

    const char* retarget = getRetargetMotFile(info.m_type);
    const char* add = GfDataEnemy::getAddMotionName(m_objId);
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    if (retarget != nullptr && add != nullptr && strcmp(retarget, add) != 0) {
        makeAssetNamePrefix(name, info.m_type, add, "Mot");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        mm::mtl::FixStr<128> path;
        path.format("%s%s%s", getPath(), add, ".mot");
        pack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
    }

    info.m_type = static_cast<GfAssetType>(18);
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(11));
    const char* evt = getEvtMotFile(static_cast<GfAssetType>(0));
    if (evt != nullptr) {
        makeAssetNamePrefix(name, info.m_type, evt, "Evt");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEvtMotSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEvtPath(), evt, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getEvtMotSlot()), path.m_str);
            const char* evtAdd = GfDataEnemy::getAddMotionName(m_objId);
            if (evtAdd != nullptr) {
                makeAssetNamePrefix(name, info.m_type, evtAdd, "Evt");
                GfAssetPack* addPack = GfAssetManager::createAssetFiles(info);
                path.format("%s%s%s", getEvtPath(), evtAdd, ".mot");
                addPack->m_files.addResource(static_cast<GfFileIdx>(getAddMotSlot()), path.m_str);
            }
        }
    }

    info.m_type = static_cast<GfAssetType>(13);
    info.m_backupTypes.clear();
    const char* eab = getEabFile(info.m_type);
    if (eab != nullptr) {
        makeAssetNamePrefix(name, info.m_type, eab, "Eff");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEabSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEffPath(), eab, ".wieab");
            pack->m_files.addResource(static_cast<GfFileIdx>(getEabSlot()), path.m_str);
        }
        const char* efb = getEfbFile(info.m_type);
        if (efb != nullptr) {
            if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEfbSlot()))) {
                mm::mtl::FixStr<128> path;
                path.format("%s%s%s", getEffPath(), efb, ".wiefb");
                pack->m_files.addResource(static_cast<GfFileIdx>(getEfbSlot()), path.m_str);
            }
        }
    }

    unsigned int footStep;
    {
        DataParamAcc acc(5, m_enemyParam->getEnArrangeID(), static_cast<GimmickType>(0));
        footStep = acc.getFootStep();
    }
    requestFootStepSePackFile(info, footStep, static_cast<GfFileIdx>(1), static_cast<GfFileIdx>(2));
}

const char* GfAssetSetupEventEnemy::getEvtMotFile(GfAssetType type) {
    if (type == 0) {
        RefResource* resource = findRefResource(getEvtMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            unsigned char* fp = GfDataBdat::getFP(165);
            unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
            unsigned int id = m_objId;
            const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Motion", id, 7));
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupEventEnemy::getEvtStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        unsigned char* fp = GfDataBdat::getFP(165);
        unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
        unsigned int id = m_objId;
        const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Model", id, 7));
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return nullptr;
}

const char* GfAssetSetupEventEnemy::getEvtPath() const {
    return GfAssetPath::getEvt();
}

GfAssetSetupNpc::GfAssetSetupNpc() {}

void GfAssetSetupNpc::setup(GF_ASSET_HANDLE* handle, const GfInitParamNpc& param) {
    setupParam(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    info.m_type = getAssetType();
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "");
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);

    info.m_type = getAssetTypeArc();
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    const char* arc = getArcFile(info.m_type);
    if (arc != nullptr) {
        makeAssetNamePrefix(name, info.m_type, arc, "NP");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getArcSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), arc, ".arc");
            pack->m_files.addResource(static_cast<GfFileIdx>(getArcSlot()), path.m_str);
        }
    }

    // the motion's name: the np423000 motions take asset type 18; types 15 and 18 add "Mot"
    auto makeMotName = [&](const char* file) {
        NN_ABORT_UNLESS(*file != '\0');
        GfAssetType type = info.m_type;
        if (strstr(file, "np423000") != nullptr) {
            type = static_cast<GfAssetType>(18);
        }
        const char* prefix = "";
        switch (type) {
        case 15:
        case 18:
            prefix = "Mot";
            break;
        default:
            break;
        }
        makeAssetNamePrefix(name, type, file, prefix);
        info.m_type = type;
    };

    info.m_type = getAssetTypeMot();
    if (!GfGameUtil::isNeedRetargetDriverResource(getMdlFile(getAssetType()))) {
        const char* mot = getRetargetMotFile(info.m_type);
        if (mot != nullptr) {
            makeMotName(mot);
            info.m_backupTypes.clear();
            info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
            GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
            if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getRetargetMotSlot()))) {
                GfAssetManager::setMotionInfo(handle, mot);
                mm::mtl::FixStr<128> path;
                path.format("%s%s%s", getPath(), mot, ".mot");
                pack->m_files.addResource(static_cast<GfFileIdx>(getRetargetMotSlot()), path.m_str);
            }
        }
        info.m_type = getAssetTypeMot();
        const char* retarget = getRetargetMotFile(info.m_type);
        const char* add = GfDataNpc::getAddMotionName(m_objId);
        if (retarget != nullptr && add != nullptr && strcmp(retarget, add) != 0) {
            makeMotName(add);
            makeMotName(add);
            info.m_backupTypes.clear();
            info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
            GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), add, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
        }
    } else {
        const char* mdl = getMdlFile(getAssetType());
        mm::mtl::FixStr<128> path;
        makeAssetNamePrefix(name, info.m_type, mdl, "");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getRetargetMotSlot()))) {
            GfAssetManager::setMotionInfo(handle, mdl);
            path.format("%s%s%s", getPath(), mdl, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getRetargetMotSlot()), path.m_str);
        }
        int driver = GfGameUtil::getNeedRetargetDriverId(getMdlFile(getAssetType()));
        makeAssetNamePrefix(name, info.m_type, mdl, "DR");
        GfAssetPack* drPack = GfAssetManager::createAssetFiles(info);
        path.format("%s%s%s", getPath(), GfDataDriver::getModelResourceName(driver), ".mot");
        drPack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
    }

    if (strstr(getMdlFile(info.m_type), "np/np002001") != nullptr) {
        info.m_type = static_cast<GfAssetType>(18);
        info.m_backupTypes.clear();
        const char* evt = getEvtMotFile(static_cast<GfAssetType>(0));
        if (evt != nullptr) {
            makeAssetNamePrefix(name, info.m_type, evt, "Evt");
            GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
            if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEvtMotSlot()))) {
                mm::mtl::FixStr<128> path;
                path.format("%s%s%s", getEvtPath(), evt, ".mot");
                pack->m_files.addResource(static_cast<GfFileIdx>(getEvtMotSlot()), path.m_str);
                const char* add = GfDataNpc::getAddMotionName(m_objId);
                if (add != nullptr) {
                    path.format("%s%s%s", getEvtPath(), add, ".mot");
                    pack->m_files.addResource(static_cast<GfFileIdx>(15), path.m_str);
                }
            }
        }
    }

    info.m_type = static_cast<GfAssetType>(13);
    info.m_backupTypes.clear();
    const char* eab = getEabFile(info.m_type);
    if (eab != nullptr) {
        makeAssetNamePrefix(name, info.m_type, eab, "");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEabSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEffPath(), eab, ".wieab");
            pack->m_files.addResource(static_cast<GfFileIdx>(getEabSlot()), path.m_str);
        }
        const char* efb = getEfbFile(info.m_type);
        if (efb != nullptr) {
            if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEfbSlot()))) {
                mm::mtl::FixStr<128> path;
                path.format("%s%s%s", getEffPath(), efb, ".wiefb");
                pack->m_files.addResource(static_cast<GfFileIdx>(getEfbSlot()), path.m_str);
            }
        }
    }

    unsigned int footStep;
    {
        DataParamAcc acc(6, m_objId, static_cast<GimmickType>(0));
        footStep = acc.getFootStep();
    }
    requestFootStepSePackFile(info, footStep, static_cast<GfFileIdx>(1), static_cast<GfFileIdx>(2));
}

const char* GfAssetSetupNpc::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        unsigned int id = m_objId;
        const char* name;
        if (id < 26) {
            name = GfGameUtil::getDriverModel(id, false, m_param->m_createType == 3);
        } else if (id <= 2000) {
            name = GfGameUtil::getBladeModel(id, false);
        } else {
            name = GfDataNpc::getModelName(id);
        }
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupNpc::getArcFile(GfAssetType type) {
    if (getAssetTypeArc() == type) {
        return getMdlFile(type);
    }
    return nullptr;
}

const char* GfAssetSetupNpc::getMotFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            const char* name = GfDataNpc::getMotionName(m_objId);
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupNpc::getEfpFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupNpc::getRetargetMotFile(GfAssetType type) {
    if (getAssetTypeMot() == type) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            const char* name = GfDataNpc::getMotionName(m_objId);
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupNpc::getStpFile(GfAssetType type) {
    if (getAssetType() != type) {
        return nullptr;
    }
    const char* name = GfDataNpc::getMotionName(m_objId);
    if (name == nullptr || *name == '\0') {
        return nullptr;
    }
    return name;
}

const char* GfAssetSetupNpc::getPath() const {
    return "/model/";
}

const char* GfAssetSetupNpc::getEvtMotFile(GfAssetType type) {
    if (type == 0 && GfDataNpc::isNeedResourceEvent(m_objId)) {
        RefResource* resource = findRefResource(getEvtMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            const char* name = GfDataNpc::getMotionName(m_objId);
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupNpc::getEabFile(GfAssetType type) {
    if (type == 13) {
        return GfDataNpc::getEffectName(m_objId);
    }
    return nullptr;
}

const char* GfAssetSetupNpc::getEfbFile(GfAssetType type) {
    return getEabFile(type);
}

const char* GfAssetSetupNpc::getEvtPath() const {
    return GfAssetPath::getEvt();
}

void GfAssetSetupEventNpc::setup(GF_ASSET_HANDLE* handle, const GfInitParamNpc& param) {
    setupParam(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    info.m_type = getAssetType();
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    info.m_backupTypes.push_back(static_cast<GfAssetType>(11));
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "Mdl");
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);

    info.m_type = getAssetTypeArc();
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(18));
    info.m_backupTypes.push_back(static_cast<GfAssetType>(11));
    const char* arc = getArcFile(info.m_type);
    if (arc != nullptr) {
        makeAssetNamePrefix(name, info.m_type, arc, "EV");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getArcSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), arc, ".arc");
            pack->m_files.addResource(static_cast<GfFileIdx>(getArcSlot()), path.m_str);
        }
    }

    info.m_type = getAssetTypeMot();
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(11));
    const char* mot = getRetargetMotFile(info.m_type);
    if (mot != nullptr) {
        makeAssetNamePrefix(name, info.m_type, mot, "Mot");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getRetargetMotSlot()))) {
            GfAssetManager::setMotionInfo(handle, mot);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", GfDataNpc::isEventRetarget(m_objId) ? getEvtPath() : getPath(), mot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getRetargetMotSlot()), path.m_str);
        }
    }

    const char* retarget = getRetargetMotFile(info.m_type);
    const char* add = GfDataNpc::getAddMotionName(m_objId);
    if (retarget != nullptr && add != nullptr && strcmp(retarget, add) != 0) {
        makeAssetNamePrefix(name, info.m_type, add, "Mot");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        mm::mtl::FixStr<128> path;
        path.format("%s%s%s", getPath(), add, ".mot");
        pack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
    }

    info.m_type = static_cast<GfAssetType>(18);
    info.m_backupTypes.clear();
    info.m_backupTypes.push_back(static_cast<GfAssetType>(11));
    const char* evt = getEvtMotFile(static_cast<GfAssetType>(0));
    if (evt != nullptr) {
        makeAssetNamePrefix(name, info.m_type, evt, "Evt");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEvtMotSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEvtPath(), evt, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getEvtMotSlot()), path.m_str);
            const char* evtAdd = GfDataNpc::getAddMotionName(m_objId);
            if (evtAdd != nullptr) {
                makeAssetNamePrefix(name, info.m_type, evtAdd, "Evt");
                GfAssetPack* addPack = GfAssetManager::createAssetFiles(info);
                path.format("%s%s%s", getEvtPath(), evtAdd, ".mot");
                addPack->m_files.addResource(static_cast<GfFileIdx>(15), path.m_str);
            }
        }
    }

    info.m_type = static_cast<GfAssetType>(13);
    info.m_backupTypes.clear();
    const char* eab = getEabFile(info.m_type);
    if (eab != nullptr) {
        makeAssetNamePrefix(name, info.m_type, eab, "Eff");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEabSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEffPath(), eab, ".wieab");
            pack->m_files.addResource(static_cast<GfFileIdx>(getEabSlot()), path.m_str);
        }
        const char* efb = getEfbFile(info.m_type);
        if (efb != nullptr) {
            if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEfbSlot()))) {
                mm::mtl::FixStr<128> path;
                path.format("%s%s%s", getEffPath(), efb, ".wiefb");
                pack->m_files.addResource(static_cast<GfFileIdx>(getEfbSlot()), path.m_str);
            }
        }
    }

    unsigned int footStep;
    {
        DataParamAcc acc(6, m_objId, static_cast<GimmickType>(0));
        footStep = acc.getFootStep();
    }
    requestFootStepSePackFile(info, footStep, static_cast<GfFileIdx>(1), static_cast<GfFileIdx>(2));
}

const char* GfAssetSetupEventNpc::getMotFile(GfAssetType type) {
    if (type == 0) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            const char* name = GfDataNpc::getMotionName(m_objId);
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupEventNpc::getEvtMotFile(GfAssetType type) {
    if (type == 0) {
        RefResource* resource = findRefResource(getEvtMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            const char* name = GfDataNpc::getMotionName(m_objId);
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupEventNpc::getEvtStpFile(GfAssetType type) {
    if (getAssetType() != type) {
        return nullptr;
    }
    const char* name = GfDataNpc::getMotionName(m_objId);
    if (name == nullptr || *name == '\0') {
        return nullptr;
    }
    return name;
}

GfAssetSetupMob::GfAssetSetupMob() {}

void GfAssetSetupMob::setup(GF_ASSET_HANDLE* handle, const GfInitParamMob& param) {
    setupParam(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "Mdl");
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);

    info.m_type = static_cast<GfAssetType>(0);
    const char* mot = getRetargetMotFile(info.m_type);
    if (mot != nullptr) {
        NN_ABORT_UNLESS(*mot != '\0');
        GfAssetType type = static_cast<GfAssetType>(strstr(mot, "np423000") == nullptr ? 15 : 18);
        makeAssetNamePrefix(name, type, mot, "Mot");
        info.m_type = type;
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getRetargetMotSlot()))) {
            GfAssetManager::setMotionInfo(handle, mot);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), mot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getRetargetMotSlot()), path.m_str);
        }
    }

    const char* retarget = getRetargetMotFile(static_cast<GfAssetType>(0));
    const char* add = GfDataMob::getAddMotionName(m_objId);
    if (retarget != nullptr && add != nullptr && strcmp(retarget, add) != 0) {
        NN_ABORT_UNLESS(*add != '\0');
        GfAssetType type = static_cast<GfAssetType>(strstr(add, "np423000") == nullptr ? 15 : 18);
        makeAssetNamePrefix(name, type, add, "Mot");
        info.m_type = type;
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        mm::mtl::FixStr<128> path;
        path.format("%s%s%s", getPath(), add, ".mot");
        pack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
    }

    unsigned int footStep;
    {
        DataParamAcc acc(7, m_objId, static_cast<GimmickType>(0));
        footStep = acc.getFootStep();
    }
    requestFootStepSePackFile(info, footStep, static_cast<GfFileIdx>(1), static_cast<GfFileIdx>(2));
}

const char* GfAssetSetupMob::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        unsigned char* fp = GfDataBdat::getFP(170);
        unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
        unsigned int id = m_objId;
        const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Model", id, 7));
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupMob::getArcFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupMob::getMotFile(GfAssetType type) {
    if (type == 0) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            unsigned char* fp = GfDataBdat::getFP(170);
            unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
            unsigned int id = m_objId;
            const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Motion", id, 7));
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupMob::getRetargetMotFile(GfAssetType type) {
    if (type == 0) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            const char* name = GfDataMob::getMotionName(m_objId);
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupMob::getStpFile(GfAssetType type) {
    return nullptr;
}

const char* GfAssetSetupMob::getPath() const {
    return "/model/";
}

const char* GfAssetSetupMob::getEfpFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupMob::getEabFile(GfAssetType type) {
    if (getAssetType() == type) {
        return GfDataMob::getEffectName(m_objId);
    }
    return nullptr;
}

const char* GfAssetSetupMob::getEfbFile(GfAssetType type) {
    return getEabFile(type);
}

void GfAssetSetupEventMob::setup(GF_ASSET_HANDLE* handle, const GfInitParamMob& param) {
    setupParam(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "Mdl");
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);

    const char* evtMot = getMdlFile(static_cast<GfAssetType>(0));
    if (evtMot != nullptr) {
        info.m_type = static_cast<GfAssetType>(18);
        makeAssetNamePrefix(name, info.m_type, evtMot, "Mot");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getRetargetMotSlot()))) {
            GfAssetManager::setMotionInfo(handle, evtMot);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEvtPath(), evtMot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getRetargetMotSlot()), path.m_str);
        }
    }

    const char* mot = getMdlFile(static_cast<GfAssetType>(0));
    if (mot != nullptr) {
        info.m_type = static_cast<GfAssetType>(18);
        makeAssetNamePrefix(name, info.m_type, mot, "Mot");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getMotSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), mot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
        }
    }

    if (strcmp(getMdlFile(static_cast<GfAssetType>(0)), getMotFile(static_cast<GfAssetType>(0))) != 0) {
        const char* own = getMotFile(static_cast<GfAssetType>(0));
        info.m_type = static_cast<GfAssetType>(18);
        makeAssetNamePrefix(name, info.m_type, own, "Mot");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(15))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), own, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(15), path.m_str);
        }
    }

    unsigned int footStep;
    {
        DataParamAcc acc(7, m_objId, static_cast<GimmickType>(0));
        footStep = acc.getFootStep();
    }
    requestFootStepSePackFile(info, footStep, static_cast<GfFileIdx>(1), static_cast<GfFileIdx>(2));
}

const char* GfAssetSetupEventMob::getEvtStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        unsigned char* fp = GfDataBdat::getFP(170);
        unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
        unsigned int id = m_objId;
        const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Motion", id, 7));
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return nullptr;
}

const char* GfAssetSetupEventMob::getEvtPath() const {
    return "/event/";
}

GfAssetSetupGimmick::GfAssetSetupGimmick() : pad_1fc(0) {}

void GfAssetSetupGimmick::setup(GF_ASSET_HANDLE* handle, const GfInitParamGimmick& param) {
    setupParam(handle, param);
    pad_1fc = param.m_gimmickType;
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    makeAssetNamePrefix(name, getAssetType(), getMdlFile(getAssetType()), "");
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);

    info.m_name = name.m_str;
    info.m_type = static_cast<GfAssetType>(17);
    const char* mot = getMotFile(info.m_type);
    if (mot != nullptr) {
        const char* efbName = getEfbFile(info.m_type);
        makeAssetNamePrefix(name, info.m_type, mot, efbName);
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getMotSlot()))) {
            GfAssetManager::setMotionInfo(handle, mot);
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), mot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getMotSlot()), path.m_str);
        }
        const char* efb = getEfbFile(info.m_type);
        if (efb != nullptr) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEffPath(), efb, ".wiefb");
            pack->m_files.addResource(static_cast<GfFileIdx>(getEfbSlot()), path.m_str);
        }
    }

    info.m_type = static_cast<GfAssetType>(18);
    const char* evtMot = getEvtMotFile(info.m_type);
    if (evtMot != nullptr) {
        makeAssetNamePrefix(name, info.m_type, evtMot, "Evt");
        GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
        if (!setupReference(pack, name.m_str, static_cast<GfFileIdx>(getEvtMotSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getEvtPath(), evtMot, ".mot");
            pack->m_files.addResource(static_cast<GfFileIdx>(getEvtMotSlot()), path.m_str);
        }
    }
}

const char* GfAssetSetupGimmick::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        unsigned char** table = m_paramCopy;
        unsigned int id = m_objId;
        const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Model", id, 7));
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupGimmick::getArcFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupGimmick::getMotFile(GfAssetType type) {
    if (type == 17) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            unsigned char** table = m_paramCopy;
            unsigned int id = m_objId;
            const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Motion", id, 7));
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupGimmick::getEfpFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupGimmick::getEabFile(GfAssetType type) {
    RefResource* resource = findRefResource(getEabSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        unsigned char** table = m_paramCopy;
        const char* name;
        {
            unsigned int id = m_objId;
            name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Comp_Eff", id, 7));
        }
        if (name == nullptr || *name == '\0') {
            unsigned int id = m_objId;
            name = validName(reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Model", id, 7)));
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupGimmick::getEfbFile(GfAssetType type) {
    if (type == 17) {
        return getEabFile(type);
    }
    return nullptr;
}

const char* GfAssetSetupGimmick::getStpFile(GfAssetType type) {
    if (getAssetType() == type) {
        unsigned char** table = m_paramCopy;
        unsigned int id = m_objId;
        const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "Motion", id, 7));
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return nullptr;
}

const char* GfAssetSetupGimmick::getPath() const {
    return "/model/";
}

GfAssetSetupFobj::GfAssetSetupFobj() {}

void GfAssetSetupFobj::setup(GF_ASSET_HANDLE* handle, const GfInitParamFobj& param) {
    setupParam(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), getMotFile(info.m_type));
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);
}

const char* GfAssetSetupFobj::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        unsigned char** table = m_paramCopy;
        unsigned int id = m_objId;
        const char* name = reinterpret_cast<const char*>(Bdat::getValCheck(*table, "mdo", id, 7));
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupFobj::getEabFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupFobj::getPath() const {
    return "/model/oj/";
}

GfAssetSetupWeapon::GfAssetSetupWeapon() {}

void GfAssetSetupWeapon::setup(GF_ASSET_HANDLE* handle, const GfInitParamWeapon& param) {
    setupParam(handle, param);
    m_append = param.pad_98;
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "");
    if (param.pad_83) {
        name += "DBW";
    }
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);
}

const char* GfAssetSetupWeapon::getMdlFile(GfAssetType type) {
    static mm::mtl::FixStr<128> s_file;
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource != nullptr) {
        fn_71001C0EE0(s_file, resource->m_name, m_append.getModelName(), m_param->pad_83);
    } else {
        mm::mtl::FixStr<128> none;
        fn_71001C0EE0(s_file, none, m_append.getModelName(), m_param->pad_83);
    }
    return s_file.m_nLen == 0 ? nullptr : s_file.m_str;
}


void fn_71001C0EE0(mm::mtl::FixStr<128>& out, const mm::mtl::FixStr<128>& file, const char* name, bool dbPath) {
    out.clear();
    if (file.m_nLen != 0) {
        out = file;
    } else if (name != nullptr && *name != '\0') {
        out = name;
    }
    if (dbPath && out.find("wp/") != -1) {
        out.cutFront(3);
        out.insert(0, "db/", 3);
    }
}
const char* GfAssetSetupWeapon::getArcFile(GfAssetType type) {
    static mm::mtl::FixStr<128> s_file;
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource != nullptr) {
        fn_71001C0EE0(s_file, resource->m_name, m_append.getModelName(), m_param->pad_83);
    } else {
        mm::mtl::FixStr<128> none;
        fn_71001C0EE0(s_file, none, m_append.getModelName(), m_param->pad_83);
    }
    return s_file.m_nLen == 0 ? nullptr : s_file.m_str;
}
const char* GfAssetSetupWeapon::getMotFile(GfAssetType type) {
    static mm::mtl::FixStr<128> s_file;
    RefResource* resource = findRefResource(getMotSlot());
    if (resource != nullptr) {
        fn_71001C0EE0(s_file, resource->m_name, m_append.getMotionName(), m_param->pad_83);
    } else {
        mm::mtl::FixStr<128> none;
        fn_71001C0EE0(s_file, none, m_append.getMotionName(), m_param->pad_83);
    }
    return s_file.m_nLen == 0 ? nullptr : s_file.m_str;
}
const char* GfAssetSetupWeapon::getEfpFile(GfAssetType type) {
    static mm::mtl::FixStr<128> s_file;
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource != nullptr) {
        fn_71001C0EE0(s_file, resource->m_name, m_append.getModelName(), m_param->pad_83);
    } else {
        mm::mtl::FixStr<128> none;
        fn_71001C0EE0(s_file, none, m_append.getModelName(), m_param->pad_83);
    }
    return s_file.m_nLen == 0 ? nullptr : s_file.m_str;
}


const char* GfAssetSetupWeapon::getStpFile(GfAssetType type) {
    return validName(m_append.getModelName());
}

const char* GfAssetSetupWeapon::getPath() const {
    return GfAssetPath::getMdoModel();
}

GfAssetSetupWeaponEventCS::GfAssetSetupWeaponEventCS() {}

void GfAssetSetupWeaponEventCS::setup(GF_ASSET_HANDLE* handle, const GfInitParamWeapon& param) {
    GfAssetSetupWeapon::setup(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    info.m_type = static_cast<GfAssetType>(18);
    const char* mot = getEvtMotFile(info.m_type);
    if (mot == nullptr) {
        return;
    }
    makeAssetNamePrefix(name, info.m_type, mot, "Evt");
    GfAssetPack* pack = GfAssetManager::createAssetFiles(info);
    if (setupReference(pack, mot, static_cast<GfFileIdx>(getEvtMotSlot()))) {
        return;
    }
    mm::mtl::FixStr<128> path;
    path.format("%s%s%s", getEvtPath(), mot, ".mot");
    pack->m_files.addResource(static_cast<GfFileIdx>(getEvtMotSlot()), path.m_str);
}

const char* GfAssetSetupWeaponEventCS::getEvtMotFile(GfAssetType type) {
    if (type == 18) {
        return getMotFile(type);
    }
    return nullptr;
}

const char* GfAssetSetupWeaponEventCS::getEvtPath() const {
    return "/event/mot/";
}

GfAssetSetupEnWeapon::GfAssetSetupEnWeapon() {}

void GfAssetSetupEnWeapon::setup(GF_ASSET_HANDLE* handle, const GfInitParamEnWeapon& param) {
    setupParam(handle, param);
    m_append = param.m_append;
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), getMotFile(info.m_type));
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);
}

const char* GfAssetSetupEnWeapon::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = m_append.getModelName();
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupEnWeapon::getArcFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupEnWeapon::getMotFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMotSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = m_append.getMotionName();
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupEnWeapon::getEfpFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupEnWeapon::getStpFile(GfAssetType type) {
    return validName(m_append.getModelName());
}

const char* GfAssetSetupEnWeapon::getPath() const {
    return GfAssetPath::getMdoModel();
}

GfAssetSetupBelonging::GfAssetSetupBelonging() {}

void GfAssetSetupBelonging::setup(GF_ASSET_HANDLE* handle, const GfInitParamBelonging& param) {
    setupParam(handle, param);
    m_append = param.m_append;
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), getMotFile(info.m_type));
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);
}

const char* GfAssetSetupBelonging::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = m_append.getModelName();
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupBelonging::getArcFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupBelonging::getMotFile(GfAssetType type) {
    if (getMotSlot() >= 0) {
        RefResource* resource = findRefResource(getMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            const char* name = m_append.getMotionName();
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupBelonging::getPath() const {
    return GfAssetPath::getMdoModel();
}

GfAssetSetupExtra::GfAssetSetupExtra() {}

void GfAssetSetupExtra::setup(GF_ASSET_HANDLE* handle, const GfInitParamExtra& param) {
    setupParam(handle, param);
    m_append = param.m_append;
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), getMotFile(info.m_type));
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);
}

const char* GfAssetSetupExtra::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = m_append.getModelName();
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupExtra::getArcFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupExtra::getMotFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMotSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = m_append.getMotionName();
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupExtra::getStpFile(GfAssetType type) {
    return validName(m_append.getModelName());
}

const char* GfAssetSetupExtra::getPath() const {
    return GfAssetPath::getMdoModel();
}

GfAssetSetupMapSeamless::GfAssetSetupMapSeamless() : pad_1fc(0) {}

void GfAssetSetupMapSeamless::setup(GF_ASSET_HANDLE* handle, const GfInitParamMapSeamless& param) {
    setupParam(handle, param);
    pad_1fc = param.pad_90;
    if (param.pad_98 != nullptr) {
        // the name without its extension
        mm::mtl::FixStr<128> noExt;
        [&] {
            noExt = param.pad_98;
            int dot = noExt.findLast('.');
            if (dot == -1 || dot == 0) {
                return false;
            }
            noExt = noExt.substr(0, dot);
            return true;
        }();
        pad_200 = noExt;
    }
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "");
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);
}

const char* GfAssetSetupMapSeamless::getMdlFile(GfAssetType type) {
    const char* name = getRefFile(getMdlSlot());
    if (name == nullptr) {
        name = validName(pad_1fc != 0 ? GfDataMap::getMapResourceNameByMapID(m_objId)
                                      : GfDataMap::getMapResourceName(m_objId));
        if (pad_200.m_nLen != 0) {
            name = pad_200.m_str;
        }
    }
    return name;
}

const char* GfAssetSetupMapSeamless::getColFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupMapSeamless::getNaviFile(GfAssetType type) {
    return getMdlFile(type);
}

// the model's file name with a final 'a' dropped and "_pack" added
const char* GfAssetSetupMapSeamless::getEfbFile(GfAssetType type) {
    pad_284 = util::getFilePtrFromPath(getMdlFile(type));
    if (pad_284.m_nLen != 0) {
        int last = pad_284.m_nLen - 1;
        if (pad_284.m_str[last] == 'a') {
            pad_284.m_str[last] = '\0';
            pad_284.m_nLen = last;
        }
        pad_284 += "_pack";
    }
    return pad_284.m_str;
}

const char* GfAssetSetupMapSeamless::getGIblFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupMapSeamless::getLIblFile(GfAssetType type) {
    return getMdlFile(type);
}

// the map's files: model, collision, navigation, effects and both lights, by the asset type it has (the type it is
// given is not used)
void GfAssetSetupMapSeamless::requestCoreResource(GfAssetPack* pack, GF_ASSET_HANDLE*, GfAssetType) {
    if (pack == nullptr) {
        return;
    }
    GfAssetFiles& files = pack->m_files;
    const char* mdl = getMdlFile(getAssetType());
    if (mdl != nullptr) {
        if (!setupReference(pack, mdl, static_cast<GfFileIdx>(getMdlSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), mdl, ".wismhd");
            files.addResource(static_cast<GfFileIdx>(getMdlSlot()), path.m_str);
        }
    }
    const char* col = getColFile(getAssetType());
    if (col != nullptr) {
        if (!setupReference(pack, col, static_cast<GfFileIdx>(getColSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), col, ".wiidcm");
            files.addResource(static_cast<GfFileIdx>(getColSlot()), path.m_str);
        }
    }
    const char* navi = getNaviFile(getAssetType());
    if (navi != nullptr) {
        if (!setupReference(pack, navi, static_cast<GfFileIdx>(getNaviSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), navi, ".winvhe");
            files.addResource(static_cast<GfFileIdx>(getNaviSlot()), path.m_str);
        }
    }
    const char* efb = getEfbFile(getAssetType());
    if (efb != nullptr) {
        if (!setupReference(pack, efb, static_cast<GfFileIdx>(getEpkSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("/effect/ma/%s%s", efb, ".wiefb");
            files.addResource(static_cast<GfFileIdx>(getEpkSlot()), path.m_str);
        }
    }
    const char* gIbl = getGIblFile(getAssetType());
    if (gIbl != nullptr) {
        if (!setupReference(pack, gIbl, static_cast<GfFileIdx>(getGIblSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s%s", getPath(), gIbl, ".wiibl");
            files.addResource(static_cast<GfFileIdx>(getGIblSlot()), path.m_str);
        }
    }
    const char* lIbl = getLIblFile(getAssetType());
    if (lIbl != nullptr) {
        if (!setupReference(pack, lIbl, static_cast<GfFileIdx>(getLIblSlot()))) {
            mm::mtl::FixStr<128> path;
            path.format("%s%s_libl%s", getPath(), lIbl, ".wilgt");
            files.addResource(static_cast<GfFileIdx>(getLIblSlot()), path.m_str);
        }
    }
}

const char* GfAssetSetupMapSeamless::getPath() const {
    return pad_200.m_nLen == 0 ? GfAssetPath::getMdoMap() : "";
}

GfAssetSetupEventObj::GfAssetSetupEventObj() {}

void GfAssetSetupEventObj::setup(GF_ASSET_HANDLE* handle, const GfInitParamEventObj& param) {
    setupParam(handle, param);
    if (param.pad_18 != nullptr) {
#line 5672
        m_paramCopy = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) unsigned char*(*param.pad_18);
    }
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_type = getAssetType();
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), getMotFile(info.m_type));
    name += "Evt";
    if (pad_f0) {
        name += "Out";
    }
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);
}

const char* GfAssetSetupEventObj::getMdlFile(GfAssetType type) {
    return getRefFile(getMdlSlot());
}

const char* GfAssetSetupEventObj::getArcFile(GfAssetType type) {
    return getRefFile(getArcSlot());
}

const char* GfAssetSetupEventObj::getEfpFile(GfAssetType type) {
    return getRefFile(getEfpSlot());
}

const char* GfAssetSetupEventObj::getEabFile(GfAssetType type) {
    return getRefFile(getEabSlot());
}

const char* GfAssetSetupEventObj::getEfbFile(GfAssetType type) {
    return getRefFile(getEfbSlot());
}

GfAssetSetupUiObj::GfAssetSetupUiObj() {}

void GfAssetSetupUiObj::setup(GF_ASSET_HANDLE* handle, const GfInitParamUiObj& param) {
    setupParam(handle, param);
    if (getMdlFile(getAssetType()) == nullptr || *getMdlFile(getAssetType()) == '\0') {
        GfAssetManager::destroy(m_handle);
        m_handle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
        return;
    }
    mm::mtl::FixStr<128> name;
    GfAssetFilesInfo info;
    info.m_handle = handle;
    info.m_name = name.m_str;
    info.pad_40 = param.pad_44;
    info.m_type = getAssetType();
    makeAssetNamePrefix(name, info.m_type, getMdlFile(info.m_type), "");
    GfAssetPack* core = GfAssetManager::createAssetFiles(info);
    requestCoreResource(core, handle, info.m_type);
}

const char* GfAssetSetupUiObj::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        const char* name = GfBdatRsc::sys()->getRSC_MapObjListModel(m_objId);
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }
        return name;
    }
    return resource->m_name.m_str;
}

const char* GfAssetSetupUiObj::getArcFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupUiObj::getPath() const {
    return "/model/";
}

const char* GfAssetSetup::getAssetCategoryName() const {
    return nullptr;
}

const char* GfAssetSetup::getRetargetMotFile(GfAssetType type) {
    return nullptr;
}

const char* GfAssetSetup::getEvtMotFile(GfAssetType type) {
    return nullptr;
}

const char* GfAssetSetup::getSalvageMotFile(GfAssetType type) {
    return nullptr;
}

const char* GfAssetSetup::getUiMotFile(GfAssetType type) {
    return nullptr;
}

const char* GfAssetSetup::getEvtStpFile(GfAssetType type) {
    return nullptr;
}

const char* GfAssetSetup::getUiStpFile(GfAssetType type) {
    return nullptr;
}

const char* GfAssetSetup::getSalvageStpFile(GfAssetType type) {
    return nullptr;
}

int GfAssetSetupDriver::getMdlSlot() const {
    return 56;
}

int GfAssetSetupDriver::getArcSlot() const {
    return 59;
}

int GfAssetSetupDriver::getMotSlot() const {
    return 60;
}

int GfAssetSetup::getRetargetMotSlot() const {
    return -1;
}

int GfAssetSetup::getEvtMotSlot() const {
    return -1;
}

int GfAssetSetup::getSalvageMotSlot() const {
    return -1;
}

int GfAssetSetup::getUiMotSlot() const {
    return -1;
}

int GfAssetSetupDriver::getEfpSlot() const {
    return 61;
}

int GfAssetSetupDriver::getEabSlot() const {
    return 62;
}

int GfAssetSetupDriver::getEfbSlot() const {
    return 63;
}

int GfAssetSetupDriver::getStpSlot() const {
    return 70;
}

int GfAssetSetup::getEvtStpSlot() const {
    return -1;
}

int GfAssetSetup::getUiStpSlot() const {
    return -1;
}

int GfAssetSetup::getSalvageStpSlot() const {
    return -1;
}

const char* GfAssetSetup::getEvtPath() const {
    return "";
}

const char* GfAssetSetup::getEffPath() const {
    return GfAssetPath::getEff();
}

const char* GfAssetSetup::getStpPath() const {
    return GfAssetPath::getStp();
}

const char* GfAssetSetup::getSePackPath() const {
    return GfAssetPath::getSePack();
}

GfAssetType GfAssetSetupDriver::getAssetTypeEvtMot() const {
    return static_cast<GfAssetType>(18);
}

const char* GfAssetSetup::getMotFile(GfAssetType type) {
    return nullptr;
}

const char* GfAssetSetup::getEfTailFile(GfAssetType type) {
    return nullptr;
}

int GfAssetSetupBlade::getMdlSlot() const {
    return 56;
}

int GfAssetSetupBlade::getArcSlot() const {
    return 59;
}

int GfAssetSetupBlade::getMotSlot() const {
    return 60;
}

int GfAssetSetupBlade::getRetargetMotSlot() const {
    return 69;
}

int GfAssetSetupBlade::getEfpSlot() const {
    return 61;
}

int GfAssetSetupBlade::getEabSlot() const {
    return 62;
}

int GfAssetSetupBlade::getEfbSlot() const {
    return 63;
}

int GfAssetSetupBlade::getStpSlot() const {
    return 70;
}

GfAssetType GfAssetSetupBlade::getAssetType() const {
    return static_cast<GfAssetType>(6);
}

GfAssetType GfAssetSetupBlade::getAssetTypeMot() const {
    return static_cast<GfAssetType>(7);
}

GfAssetType GfAssetSetupBlade::getAssetTypeEventMot() const {
    return static_cast<GfAssetType>(18);
}

GfAssetType GfAssetSetupBlade::getAssetTypeEfb() const {
    return static_cast<GfAssetType>(9);
}

int GfAssetSetupEnemy::getMdlSlot() const {
    return 6;
}

int GfAssetSetupEnemy::getArcSlot() const {
    return 7;
}

int GfAssetSetupEnemy::getMotSlot() const {
    return 8;
}

int GfAssetSetupEnemy::getRetargetMotSlot() const {
    return 14;
}

int GfAssetSetupEnemy::getEfpSlot() const {
    return 9;
}

int GfAssetSetupEnemy::getEabSlot() const {
    return 10;
}

int GfAssetSetupEnemy::getEfbSlot() const {
    return 11;
}

int GfAssetSetupEnemy::getStpSlot() const {
    return 4;
}

GfAssetType GfAssetSetupEnemy::getAssetType() const {
    return static_cast<GfAssetType>(10);
}

int GfAssetSetupEnemy::getAddMotSlot() const {
    return 15;
}

GfAssetType GfAssetSetupEnemy::getAssetTypeMot() const {
    return static_cast<GfAssetType>(11);
}

GfAssetType GfAssetSetupEnemy::getAssetTypeArc() const {
    return static_cast<GfAssetType>(12);
}

int GfAssetSetupNpc::getMdlSlot() const {
    return 6;
}

int GfAssetSetupNpc::getArcSlot() const {
    return 7;
}

int GfAssetSetupNpc::getMotSlot() const {
    return 8;
}

int GfAssetSetupNpc::getRetargetMotSlot() const {
    return 14;
}

int GfAssetSetupNpc::getEvtMotSlot() const {
    return 12;
}

int GfAssetSetupNpc::getEfpSlot() const {
    return 9;
}

int GfAssetSetupNpc::getEabSlot() const {
    return 10;
}

int GfAssetSetupNpc::getEfbSlot() const {
    return 11;
}

int GfAssetSetupNpc::getStpSlot() const {
    return 4;
}

GfAssetType GfAssetSetupNpc::getAssetType() const {
    return static_cast<GfAssetType>(10);
}

GfAssetType GfAssetSetupNpc::getAssetTypeMot() const {
    return static_cast<GfAssetType>(11);
}

GfAssetType GfAssetSetupNpc::getAssetTypeArc() const {
    return static_cast<GfAssetType>(12);
}

int GfAssetSetupMob::getMdlSlot() const {
    return 6;
}

int GfAssetSetupMob::getArcSlot() const {
    return 7;
}

int GfAssetSetupMob::getMotSlot() const {
    return 8;
}

int GfAssetSetupMob::getRetargetMotSlot() const {
    return 14;
}

int GfAssetSetupMob::getEfpSlot() const {
    return 9;
}

int GfAssetSetupMob::getEabSlot() const {
    return 10;
}

int GfAssetSetupMob::getEfbSlot() const {
    return 11;
}

int GfAssetSetupMob::getStpSlot() const {
    return 4;
}

GfAssetType GfAssetSetupMob::getAssetType() const {
    return static_cast<GfAssetType>(15);
}

int GfAssetSetupGimmick::getMdlSlot() const {
    return 0;
}

int GfAssetSetupGimmick::getArcSlot() const {
    return 1;
}

int GfAssetSetupGimmick::getMotSlot() const {
    return 2;
}

int GfAssetSetupGimmick::getEfpSlot() const {
    return 3;
}

int GfAssetSetupGimmick::getEabSlot() const {
    return 4;
}

int GfAssetSetupGimmick::getEfbSlot() const {
    return 5;
}

int GfAssetSetupGimmick::getStpSlot() const {
    return 6;
}

GfAssetType GfAssetSetupGimmick::getAssetType() const {
    return static_cast<GfAssetType>(15);
}

const char* GfAssetSetup::getEfpFile(GfAssetType type) {
    return nullptr;
}

const char* GfAssetSetup::getEfbFile(GfAssetType type) {
    return nullptr;
}

const char* GfAssetSetup::getStpFile(GfAssetType type) {
    return nullptr;
}

int GfAssetSetup::getEfpSlot() const {
    return -1;
}

int GfAssetSetup::getEfbSlot() const {
    return -1;
}

int GfAssetSetup::getStpSlot() const {
    return -1;
}

const char* GfAssetSetup::getArcFile(GfAssetType type) {
    return nullptr;
}

int GfAssetSetupFobj::getMdlSlot() const {
    return 0;
}

int GfAssetSetup::getArcSlot() const {
    return -1;
}

int GfAssetSetup::getMotSlot() const {
    return -1;
}

int GfAssetSetupFobj::getEabSlot() const {
    return 4;
}

GfAssetType GfAssetSetupFobj::getAssetType() const {
    return static_cast<GfAssetType>(14);
}

const char* GfAssetSetup::getEabFile(GfAssetType type) {
    return nullptr;
}

int GfAssetSetupWeapon::getMdlSlot() const {
    return 0;
}

int GfAssetSetupWeapon::getArcSlot() const {
    return 1;
}

int GfAssetSetupWeapon::getMotSlot() const {
    return 2;
}

int GfAssetSetupWeapon::getEfpSlot() const {
    return 3;
}

int GfAssetSetup::getEabSlot() const {
    return -1;
}

int GfAssetSetupWeapon::getStpSlot() const {
    return 5;
}

GfAssetType GfAssetSetupWeapon::getAssetType() const {
    return static_cast<GfAssetType>(8);
}

int GfAssetSetupWeaponEventCS::getEvtMotSlot() const {
    return 4;
}

int GfAssetSetupEnWeapon::getMdlSlot() const {
    return 0;
}

int GfAssetSetupEnWeapon::getArcSlot() const {
    return 1;
}

int GfAssetSetupEnWeapon::getMotSlot() const {
    return 6;
}

int GfAssetSetupEnWeapon::getEfpSlot() const {
    return 2;
}

int GfAssetSetupEnWeapon::getStpSlot() const {
    return 5;
}

GfAssetType GfAssetSetupEnWeapon::getAssetType() const {
    return static_cast<GfAssetType>(17);
}

int GfAssetSetupBelonging::getMdlSlot() const {
    return 0;
}

int GfAssetSetupBelonging::getArcSlot() const {
    return 1;
}

GfAssetType GfAssetSetupBelonging::getAssetType() const {
    return static_cast<GfAssetType>(17);
}

int GfAssetSetupExtra::getMdlSlot() const {
    return 0;
}

int GfAssetSetupExtra::getArcSlot() const {
    return 1;
}

int GfAssetSetupExtra::getMotSlot() const {
    return 6;
}

int GfAssetSetupExtra::getStpSlot() const {
    return 5;
}

GfAssetType GfAssetSetupExtra::getAssetType() const {
    return static_cast<GfAssetType>(17);
}

int GfAssetSetupMapSeamless::getMdlSlot() const {
    return 0;
}

GfAssetType GfAssetSetupMapSeamless::getAssetType() const {
    return static_cast<GfAssetType>(3);
}

int GfAssetSetupMapSeamless::getColSlot() const {
    return 1;
}

int GfAssetSetupMapSeamless::getNaviSlot() const {
    return 2;
}

int GfAssetSetupMapSeamless::getEpkSlot() const {
    return 6;
}

int GfAssetSetupMapSeamless::getGIblSlot() const {
    return 7;
}

int GfAssetSetupMapSeamless::getLIblSlot() const {
    return 8;
}

const char* GfAssetSetupEventObj::getAssetCategoryName() const {
    return "Evt";
}

int GfAssetSetupEventObj::getMdlSlot() const {
    return 0;
}

int GfAssetSetupEventObj::getArcSlot() const {
    return 1;
}

int GfAssetSetupEventObj::getEfpSlot() const {
    return 2;
}

int GfAssetSetupEventObj::getEabSlot() const {
    return 3;
}

int GfAssetSetupEventObj::getEfbSlot() const {
    return 4;
}

const char* GfAssetSetup::getPath() const {
    return "";
}

GfAssetType GfAssetSetupEventObj::getAssetType() const {
    return static_cast<GfAssetType>(18);
}

const char* GfAssetSetupUiObj::getAssetCategoryName() const {
    return "Sal";
}

int GfAssetSetupUiObj::getMdlSlot() const {
    return 0;
}

int GfAssetSetupUiObj::getArcSlot() const {
    return 1;
}

GfAssetType GfAssetSetupUiObj::getAssetType() const {
    return static_cast<GfAssetType>(18);
}

const char* GfAssetSetup::getMdlFile(GfAssetType type) {
    return nullptr;
}

int GfAssetSetup::getMdlSlot() const {
    return -1;
}

GfAssetType GfAssetSetup::getAssetType() const {
    return static_cast<GfAssetType>(0);
}

const char* GfAssetSetupEventDriver::getAssetCategoryName() const {
    return "Evt";
}

int GfAssetSetupEventDriver::getEvtMotSlot() const {
    return 64;
}

int GfAssetSetupEventDriver::getEvtStpSlot() const {
    return 71;
}

const char* GfAssetSetupSalvage::getAssetCategoryName() const {
    return "Sal";
}

int GfAssetSetupSalvage::getSalvageMotSlot() const {
    return 67;
}

int GfAssetSetupSalvage::getSalvageStpSlot() const {
    return 73;
}

int GfAssetSetupDriverForUi::getUiMotSlot() const {
    return 66;
}

int GfAssetSetupDriverForUi::getUiStpSlot() const {
    return 72;
}

GfAssetType GfAssetSetupDriverForUi::getAssetTypeEvtMot() const {
    return static_cast<GfAssetType>(18);
}

const char* GfAssetSetupEventBlade::getAssetCategoryName() const {
    return "Evt";
}

int GfAssetSetupEventBlade::getEvtMotSlot() const {
    return 64;
}

int GfAssetSetupEventBlade::getEvtStpSlot() const {
    return 71;
}

int GfAssetSetupBladeForUi::getUiMotSlot() const {
    return 66;
}

int GfAssetSetupBladeForUi::getUiStpSlot() const {
    return 72;
}

GfAssetType GfAssetSetupBladeForUi::getAssetType() const {
    return static_cast<GfAssetType>(18);
}

GfAssetType GfAssetSetupBladeForUi::getAssetTypeMot() const {
    return static_cast<GfAssetType>(18);
}

GfAssetType GfAssetSetupBladeForUi::getAssetTypeEventMot() const {
    return static_cast<GfAssetType>(18);
}

GfAssetType GfAssetSetupBladeForUi::getAssetTypeEfb() const {
    return static_cast<GfAssetType>(18);
}

const char* GfAssetSetupEventEnemy::getAssetCategoryName() const {
    return "Evt";
}

int GfAssetSetupEventEnemy::getEvtMotSlot() const {
    return 12;
}

int GfAssetSetupEventEnemy::getEvtStpSlot() const {
    return 5;
}

const char* GfAssetSetupEventNpc::getAssetCategoryName() const {
    return "Evt";
}

int GfAssetSetupEventNpc::getEvtStpSlot() const {
    return 5;
}

GfAssetType GfAssetSetupEventNpc::getAssetType() const {
    return static_cast<GfAssetType>(10);
}

GfAssetType GfAssetSetupEventNpc::getAssetTypeMot() const {
    return static_cast<GfAssetType>(18);
}

const char* GfAssetSetupEventMob::getAssetCategoryName() const {
    return "Evt";
}

int GfAssetSetupEventMob::getEvtStpSlot() const {
    return 5;
}

}  // namespace gf
