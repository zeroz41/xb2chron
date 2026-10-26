#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfAppendHandles.h"
#include "classes/gf/GfBdatChrDr.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfObj.h"
#include "gf/GfAppend.h"
#include "gf/GfAppendUtil.h"
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
// added to info's current list. Not written yet: candidate in the worker's wip/fn_71004A2C78.cpp.
void fn_71004A2C78(GfAppendInfo& info, unsigned int bone, unsigned int id);

// Placeholder name (1.0.0 leaves it unnamed too, fn_71004F463C). What it does: adds weaponId's models to info.
void fn_71004A1718(GfAppendInfo& info, unsigned int mountDriverId, unsigned int rscDriverId,
                   unsigned int weaponId, unsigned int bladeId, unsigned int weaponType, bool flag);

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
