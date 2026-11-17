#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfAppendHandles.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfBdatChrDr.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfObj.h"
#include "gf/GfAppend.h"
#include "gf/GfAppendUtil.h"
#include "gf/GfDataBlade.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataEnemy.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "gf/GfUtil.h"

namespace gf {

// Placeholder name: new in 3.0.1 (1.0.0's setupWeapon inlines the driver lookup). What it does: the CHR_Dr row a
// blade's weapon mounts by: 11 / 12 for driver 1 with blade 1001 / 1011 when onWeapon (attach 3), blade - 1110 for
// blades 1124..1132, else the first CHR_Dr row (getChrDrStart..getChrDrEnd) with driver's name (driver 0 read as 1).
static unsigned int fn_71004A1648(unsigned int driverId, unsigned int bladeId, bool onWeapon) {
    if (onWeapon) {
        if (driverId == 1 && bladeId == 1001) {
            return 11;
        }
        if (driverId == 1 && bladeId == 1011) {
            return 12;
        }
    }
    switch (bladeId) {
    case 1124:
        return 14;
    case 1125:
        return 15;
    case 1126:
        return 16;
    case 1127:
        return 17;
    case 1128:
        return 18;
    case 1129:
        return 19;
    case 1130:
        return 20;
    case 1131:
        return 21;
    case 1132:
        return 22;
    }
    unsigned int id = driverId == 0 ? 1 : driverId;
    GfBdatChrDr* chrDr = GfBdatChrDr::sys();
    unsigned int name = chrDr->getChrDrName(id);
    for (unsigned int i = chrDr->getChrDrStart(); i < chrDr->getChrDrEnd(); i++) {
        if (name == chrDr->getChrDrName(i)) {
            return i;
        }
    }
    return id;
}

// Placeholder name (1.0.0 leaves it unnamed too, fn_71004F5C90). What it does: a new append of RSC_NpcWpn row id
// (its model and motion, mounted on {"", "EX_wp_L", "EX_wp_R", "EX_back"}[bone] (.data 0x7100B654A8) with OPTMNT 2),
// added to info's current list. Not written yet.
void fn_71004A2C78(GfAppendInfo& info, unsigned int bone, unsigned int id);

// Placeholder name (1.0.0 leaves it unnamed too, fn_71004F463C). What it does: adds weaponId's models to info.
void fn_71004A1718(GfAppendInfo& info, unsigned int mountDriverId, unsigned int rscDriverId,
                   unsigned int weaponId, unsigned int bladeId, unsigned int weaponType, bool flag);

// Placeholder name (the symbols leave it unnamed). What it does: a new append of RSC_EnWpn row id (its model, motion
// and scale / 100, mounted on its MtpOutChara bone (OPTMNT 1), MtpInChara (2) and, when owner is not
// (GF_OBJ_HANDLE*)-1, MtpOutChara again (3)), added to info's current list.
static void fn_71004A2030(GfAppendInfo* info, unsigned int id, GF_OBJ_HANDLE* owner);

void GfAppendUtil::setupPartyBlade(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int weaponId,
                                   unsigned int driverId, unsigned int bladeId) {
    if (weaponId == 0) {
        return;
    }
    unsigned int weaponType = GfBdatItem::sys()->getPcWpnWpnType(weaponId);
    GfAppendInfo* info = GfObjUtil::getAppendInfo(handle, attach);
    if (info == nullptr) {
        return;
    }
    info->clear();
    if (GfObjUtil::getObjType(handle) == 4) {
        DataParamAcc acc(handle);
        bladeId = acc.isValid() ? acc.getBdatId() : 0;
    }
    bool onWeapon = attach == 3;
    unsigned int mountId = fn_71004A1648(driverId, bladeId, onWeapon);
    unsigned int rscId = fn_71004A1648(driverId, bladeId, onWeapon);
    if (bladeId == 1040) {
        rscId = 10;
    }
    fn_71004A1718(*info, mountId, rscId, weaponId, bladeId, weaponType, false);
}

void GfAppendUtil::setupWeapon(GFATTACH attach, GfAppendInfo& info, unsigned int weaponId, unsigned int driverId,
                               unsigned int bladeId, bool flag) {
    if (weaponId == 0) {
        return;
    }
    unsigned int weaponType = GfBdatItem::sys()->getPcWpnWpnType(weaponId);
    info.clear();
    unsigned int mountId = fn_71004A1648(driverId, bladeId, attach == 3);
    fn_71004A1718(info, mountId, mountId, weaponId, bladeId, weaponType, flag);
}

void GfAppendUtil::setupActViewer(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int weaponId,
                                  unsigned int driverId, unsigned int bladeId) {
    if (weaponId == 0) {
        return;
    }
    unsigned int weaponType = GfBdatItem::sys()->getPcWpnWpnType(weaponId);
    GfAppendInfo* info = GfObjUtil::getAppendInfo(handle, attach);
    info->clear();
    unsigned int mountId = fn_71004A1648(driverId, bladeId, attach == 3);
    fn_71004A1718(*info, mountId, mountId, weaponId, bladeId, weaponType, true);
}

void GfAppendUtil::setupEnemy(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int enArrangeId,
                              GF_OBJ_HANDLE* owner) {
    if (enArrangeId == 0) {
        return;
    }
    unsigned int rscId = GfDataEnemy::getRscIdByArrangeId(enArrangeId);
    GfAppendInfo* info = GfObjUtil::getAppendInfo(handle, attach);
    info->clear();
    GfBdatRsc* rsc = GfBdatRsc::sys();
    GfBdatBtl* btl = GfBdatBtl::sys();
    for (unsigned int i = 0; i < 5; i++) {
        unsigned int weapon = rsc->getRscEnWeaponNum(rscId, i);
        if (weapon != 0) {
            unsigned int idR = btl->getWpn_EnRscR(weapon);
            unsigned int idL = btl->getWpn_EnRscL(weapon);
            fn_71004A2030(info, idR, owner);
            fn_71004A2030(info, idL, owner);
        }
    }
}

static void fn_71004A2030(GfAppendInfo* info, unsigned int id, GF_OBJ_HANDLE* owner) {
    if (id == 0) {
        return;
    }
    GfBdatRsc* rsc = GfBdatRsc::sys();
#line 394
    GfAppend* append = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfAppend(rsc->getRscEnWpnModel(id), rsc->getRscEnWpnMotion(id), info->m_appends[info->m_list].size(), id,
                 rsc->getRscEnWpnScale(id) * 0.01f, info->m_list != 0);
    GfAppend::MOUNT_INFO mount;
    mount.m_mount = OPTMNT(1);
    mount.m_name = rsc->getRscEnWpnMtpOutChara(id);
    append->addMount(mount);
    mount.m_mount = OPTMNT(2);
    mount.m_name = rsc->getRscEnWpnMtpInChara(id);
    append->addMount(mount);
    if (owner != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        mount.m_mount = OPTMNT(3);
        mount.m_name = rsc->getRscEnWpnMtpOutChara(id);
        append->addMount(mount);
    }
    info->m_appends[info->m_list].push_back(append);
}

static unsigned int fn_71004A27A8(unsigned int weaponType, unsigned int bladeId);

void GfAppendUtil::setupEventActEnemy(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int enArrangeId) {
    if (enArrangeId == 0) {
        return;
    }
    unsigned int rscId = GfDataEnemy::getRscIdByArrangeId(enArrangeId);
    GfAppendInfo* info = GfObjUtil::getAppendInfo(handle, attach);
    info->clear();
    GfBdatRsc* rsc = GfBdatRsc::sys();
    GfBdatBtl* btl = GfBdatBtl::sys();
    for (unsigned int i = 0; i < 5; i++) {
        unsigned int weapon = rsc->getRscEnWeaponNum(rscId, i);
        if (weapon != 0) {
            unsigned int idR = btl->getWpn_EnRscR(weapon);
            unsigned int idL = btl->getWpn_EnRscL(weapon);
            fn_71004A2030(info, idR, reinterpret_cast<GF_OBJ_HANDLE*>(-1));
            fn_71004A2030(info, idL, reinterpret_cast<GF_OBJ_HANDLE*>(-1));
        }
    }
    if (!info->m_appends[info->m_list].empty()) {
        return;
    }
    unsigned int bladeId = GfDataEnemy::getEquipBlade(enArrangeId);
    if (bladeId == 0) {
        return;
    }
    unsigned int weaponId = GfDataBlade::getBladeWeapon(bladeId);
    if (weaponId == 0) {
        return;
    }
    DataParamAcc param(handle);
    unsigned int weaponType = GfBdatItem::sys()->getPcWpnWpnType(weaponId);
    unsigned int mountId = fn_71004A27A8(weaponType, bladeId);
    unsigned int rscDriverId = fn_71004A27A8(weaponType, bladeId);
    if (bladeId == 1040) {
        rscDriverId = 10;
    }
    fn_71004A1718(*info, mountId, rscDriverId, weaponId, bladeId, weaponType, false);
}

// Placeholder name. What it does: the CHR_Dr row an enemy blade's weapon mounts by: 13 for blades 1078 / 1079,
// blade - 1110 for blades 1124..1132, else fn_71004A1648 of the first CHR_Dr row with weaponType - 1's weapon flag.
static unsigned int fn_71004A27A8(unsigned int weaponType, unsigned int bladeId) {
    switch (bladeId) {
    case 1078:
    case 1079:
        return 13;
    case 1124:
        return 14;
    case 1125:
        return 15;
    case 1126:
        return 16;
    case 1127:
        return 17;
    case 1128:
        return 18;
    case 1129:
        return 19;
    case 1130:
        return 20;
    case 1131:
        return 21;
    case 1132:
        return 22;
    }
    GfBdatChrDr* chrDr = GfBdatChrDr::sys();
    for (unsigned int i = chrDr->getChrDrStart(); i < chrDr->getChrDrEnd(); i++) {
        if (chrDr->getChrDrWpnType(i, weaponType - 1) != 0) {
            return fn_71004A1648(i, 0, false);
        }
    }
    return 0;
}

void GfAppendUtil::setupEnemyBlade(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int, GF_OBJ_HANDLE*,
                                   GF_OBJ_HANDLE* blade) {
    GfAppendInfo* info = GfObjUtil::getAppendInfo(handle, attach);
    info->clear();
    GfObjAcc acc(blade);
    if (acc.m_obj == nullptr) {
        return;
    }
    unsigned int weaponId = GfDataBlade::getBladeWeapon(acc.getBladeId());
    if (weaponId == 0) {
        return;
    }
    DataParamAcc param(handle);
    unsigned int weaponType = GfBdatItem::sys()->getPcWpnWpnType(weaponId);
    unsigned int mountId = fn_71004A27A8(weaponType, acc.getBladeId());
    unsigned int bladeId = acc.getBladeId();
    unsigned int rscId = fn_71004A27A8(weaponType, bladeId);
    if (bladeId == 1040) {
        rscId = 10;
    }
    fn_71004A1718(*info, mountId, rscId, weaponId, acc.getBladeId(), weaponType, false);
}

void GfAppendUtil::setupEnemyBladeWithNoDriver(GFATTACH attach, GF_OBJ_HANDLE* handle, unsigned int bladeId,
                                               GF_OBJ_HANDLE*) {
    GfAppendInfo* info = GfObjUtil::getAppendInfo(handle, attach);
    info->clear();
    if (bladeId == 0) {
        return;
    }
    unsigned int weaponId = GfDataBlade::getBladeWeapon(bladeId);
    if (weaponId == 0) {
        return;
    }
    DataParamAcc param(handle);
    unsigned int weaponType = GfBdatItem::sys()->getPcWpnWpnType(weaponId);
    unsigned int mountId = fn_71004A27A8(weaponType, bladeId);
    unsigned int rscId = fn_71004A27A8(weaponType, bladeId);
    if (bladeId == 1040) {
        rscId = 10;
    }
    fn_71004A1718(*info, mountId, rscId, weaponId, bladeId, weaponType, false);
}

void GfAppendUtil::setupExtraModel(GF_OBJ_HANDLE* handle, GF_OBJ_HANDLE* owner) {
    GfObjAcc acc(owner);
    if (acc.getType() != 3) {
        return;
    }
    unsigned int rscId = GfDataDriver::getExtraMountNpcRsc(acc.getDriverId());
    if (rscId == 0) {
        return;
    }
    const char* bone = GfDataDriver::getExtraMountBone(acc.getDriverId());
    if (bone == nullptr || *bone == '\0') {
        return;
    }
    GfAppendInfo* info = GfObjUtil::getAppendInfo(handle, GFATTACH(1));
    if (info == nullptr) {
        return;
    }
    info->clear();
    // built in an inlined callee taking the list by reference (the original's push_back null check folds, and its
    // MOUNT_INFO takes the top stack slot); the callee's name is unknown
    [&](GfAppendInfo& list) {
        GfBdatRsc* rsc = GfBdatRsc::sys();
#line 630
        GfAppend* append = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
            GfAppend(rsc->getRscNpcListModel(rscId), rsc->getRscNpcListMotion(rscId),
                     list.m_appends[list.m_list].size(), rscId, 1.0f, list.m_list != 0);
        GfAppend::MOUNT_INFO mount;
        mount.m_mount = OPTMNT(2);
        mount.m_name = bone;
        append->addMount(mount);
        list.m_appends[list.m_list].push_back(append);
    }(*info);
}

void GfAppendUtil::setupBelongingForDriver(GF_OBJ_HANDLE* handle, const GfInitParamDriver& param) {
    GfObjAcc acc(handle);
    GfDataDriver::getBelongingMountBone();  // the original calls it here and drops the result
    GfAppendInfo* info = GfObjUtil::getAppendInfo(handle, GFATTACH(2));
    if (info == nullptr) {
        return;
    }
    info->clear();
    // built in an inlined callee taking the list by reference, as in setupExtraModel
    [&](GfAppendInfo& list) {
#line 678
        GfAppend* append = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
            GfAppend(GfDataDriver::getBelongingModelName(param), "", list.m_appends[list.m_list].size(), 0, 1.0f,
                     list.m_list != 0);
        GfAppend::MOUNT_INFO mount;
        mount.m_mount = OPTMNT(2);
        mount.m_name = GfDataDriver::getBelongingMountBone();
        append->addMount(mount);
        mount.m_mount = OPTMNT(1);
        mount.m_name = GfDataDriver::getBelongingMountBone();
        append->addMount(mount);
        list.m_appends[list.m_list].push_back(append);
    }(*info);
}

void GfAppendUtil::setupBelonging(GF_OBJ_HANDLE* handle, unsigned int boneR, unsigned int idR, unsigned int boneL,
                                  unsigned int idL) {
    GfAppendInfo* info = GfObjUtil::getAppendInfo(handle, GFATTACH(2));
    info->clear();
    if (idR != 0) {
        fn_71004A2C78(*info, boneR, idR);
    }
    if (idL != 0) {
        fn_71004A2C78(*info, boneL, idL);
    }
}

void GfAppendHandles::sendMessage(fw::MessageObject* sender, fw::Message& msg) const {
    for (int i = 0; i < 10; i++) {
        GfObj* obj = GfObjUtil::getObj(getObjHandles()[i]);
        if (obj != nullptr) {
            fw::MessageObject* receiver = obj;
            receiver->recieveMessage(sender, msg);
        }
    }
}

void GfAppendHandles::setAlpha(float alpha) {
    for (int i = 0; i < 10; i++) {
        GfObjAcc(getObjHandles()[i]).setAlphaNormal(alpha);
    }
}

void GfAppendHandles::destroy(mm::mtl::FixedArray<GF_OBJ_HANDLE*, 10>& handles) {
    for (int i = 0; i < 10; i++) {
        GF_OBJ_HANDLE* handle = handles[i];
        if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            handles[i] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
            GfObjUtil::destroy(handle);
        }
    }
}

void GfAppendHandles::destroy() {
    destroy(m_handles);
    destroy(m_secondHandles);
}

void GfAppendHandles::eraseHandle(mm::mtl::FixedArray<GF_OBJ_HANDLE*, 10>& handles, GF_OBJ_HANDLE* handle) {
    for (int i = 0; i < 10; i++) {
        if (handles[i] == handle) {
            handles[i] = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
            return;
        }
    }
}

void GfAppendHandles::eraseHandle(GF_OBJ_HANDLE* handle) {
    eraseHandle(m_handles, handle);
    eraseHandle(m_secondHandles, handle);
}

GfAppend::GfAppend()
    : m_modelName(nullptr), m_motionName(nullptr), m_mountIndex(0xffff), m_rscID(0), m_scale(1.0f),
      m_secondList(false) {}


const char* GfAppend::getBone(OPTMNT mount) const {
    for (const MOUNT_INFO* it = m_mounts.begin(); it != m_mounts.end(); ++it) {
        if (it->m_mount == mount) {
            return it->m_name.m_str;
        }
    }
    return "";
}

const char* GfAppend::getModelName() const { return m_modelName; }

const char* GfAppend::getMotionName() const { return m_motionName; }

const char* GfAppend::getResourceName() const { return util::getFilePtrFromPath(m_modelName); }

const char* GfAppend::getAsmFileName() const { return util::getFilePtrFromPath(m_motionName); }

unsigned short GfAppend::getMountIndex() const { return m_mountIndex; }

unsigned short GfAppend::getRscID() const { return m_rscID; }

}  // namespace gf
