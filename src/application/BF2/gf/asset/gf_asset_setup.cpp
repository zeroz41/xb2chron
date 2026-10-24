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
#include "gf/GfGameUtil.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {

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

GfAssetSetupDriver::GfAssetSetupDriver() : pad_1fc(-1) {}

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

const char* GfAssetSetupEventDriver::getEvtPath() const {
    return GfAssetPath::getEvt();
}

const char* GfAssetSetupSalvage::getMdlFile(GfAssetType type) {
    return GfGameUtil::getSalvageDriverModel(m_objId);
}

const char* GfAssetSetupSalvage::getArcFile(GfAssetType type) {
    return getMdlFile(type);
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

GfAssetSetupEnemy::GfAssetSetupEnemy() : pad_200(0) {}

const char* GfAssetSetupEnemy::getEfpFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupEnemy::getEfbFile(GfAssetType type) {
    if (type == 13) {
        return getEabFile(type);
    }
    return nullptr;
}

const char* GfAssetSetupEnemy::getPath() const {
    return "/model/";
}

GfAssetSetupEnemyBlade::GfAssetSetupEnemyBlade() {}

const char* GfAssetSetupEnemyBlade::getPath() const {
    return GfAssetPath::getMdoModel();
}

const char* GfAssetSetupEventEnemy::getEvtMotFile(GfAssetType type) {
    if (type == 0) {
        RefResource* resource = findRefResource(getEvtMotSlot());
        if (resource == nullptr || resource->m_name.m_nLen == 0) {
            unsigned char* fp = GfDataBdat::getFP(165);
            unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
            unsigned int id = m_objId;
            const char* name = Bdat::getValCheck(*table, "Motion", id, 7);
            if (name == nullptr || *name == '\0') {
                return nullptr;
            }
            return name;
        }
        return resource->m_name.m_str;
    }
    return nullptr;
}

const char* GfAssetSetupEventEnemy::getEvtPath() const {
    return GfAssetPath::getEvt();
}

GfAssetSetupNpc::GfAssetSetupNpc() {}

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

GfAssetSetupMob::GfAssetSetupMob() {}

const char* GfAssetSetupMob::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        unsigned char* fp = GfDataBdat::getFP(170);
        unsigned char** table = m_paramCopy != nullptr ? m_paramCopy : &fp;
        unsigned int id = m_objId;
        const char* name = Bdat::getValCheck(*table, "Model", id, 7);
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
            const char* name = Bdat::getValCheck(*table, "Motion", id, 7);
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

const char* GfAssetSetupEventMob::getEvtPath() const {
    return "/event/";
}

GfAssetSetupGimmick::GfAssetSetupGimmick() : pad_1fc(0) {}

const char* GfAssetSetupGimmick::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        unsigned char** table = m_paramCopy;
        unsigned int id = m_objId;
        const char* name = Bdat::getValCheck(*table, "Model", id, 7);
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
            const char* name = Bdat::getValCheck(*table, "Motion", id, 7);
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

const char* GfAssetSetupGimmick::getEfbFile(GfAssetType type) {
    if (type == 17) {
        return getEabFile(type);
    }
    return nullptr;
}

const char* GfAssetSetupGimmick::getPath() const {
    return "/model/";
}

GfAssetSetupFobj::GfAssetSetupFobj() {}

const char* GfAssetSetupFobj::getMdlFile(GfAssetType type) {
    RefResource* resource = findRefResource(getMdlSlot());
    if (resource == nullptr || resource->m_name.m_nLen == 0) {
        unsigned char** table = m_paramCopy;
        unsigned int id = m_objId;
        const char* name = Bdat::getValCheck(*table, "mdo", id, 7);
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

const char* GfAssetSetupWeapon::getStpFile(GfAssetType type) {
    return validName(m_append.getModelName());
}

const char* GfAssetSetupWeapon::getPath() const {
    return GfAssetPath::getMdoModel();
}

GfAssetSetupWeaponEventCS::GfAssetSetupWeaponEventCS() {}

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

const char* GfAssetSetupBelonging::getPath() const {
    return GfAssetPath::getMdoModel();
}

GfAssetSetupExtra::GfAssetSetupExtra() {}

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

const char* GfAssetSetupMapSeamless::getColFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupMapSeamless::getNaviFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupMapSeamless::getGIblFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupMapSeamless::getLIblFile(GfAssetType type) {
    return getMdlFile(type);
}

const char* GfAssetSetupMapSeamless::getPath() const {
    return pad_200.m_nLen == 0 ? GfAssetPath::getMdoMap() : "";
}

GfAssetSetupEventObj::GfAssetSetupEventObj() {}

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
