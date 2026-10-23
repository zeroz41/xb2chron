#include "mm/mtl/FixedList.h"
#include "classes/gf/GfAppendHandles.h"
#include "classes/gf/GfWeapon.h"
#include "classes/gf/GfGameMount.h"
#include "classes/gf/GfGameMountBlade.h"
#include "classes/gf/GfMountManager.h"
#include "gf/GfAppend.h"
#include "gf/GfObjInfo.h"
#include "gf/GfObjAcc.h"
#include "gf/GfDataBlade.h"
#include "classes/fw/MessageObject.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjManager.h"
#include "gf/GfObjUtil.h"
#include "gf/GfGameUtil.h"
#include "classes/gf/GfComAsm.h"
#include "classes/gf/GfObjSetup.h"
#include "classes/gf/GfGameObj.h"

namespace gf {

GfMountManager::~GfMountManager() {}

void GfMountManager::build(const GfSetupParam& param) {
#line 55
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfMountManager(param);
}

void GfMountManager::destroy() {
    GfMountManager* self = get();
    self->finalize();
    delete self;
}

GF_MOUNT_HANDLE* GfMountManager::createMount(GF_OBJ_HANDLE* owner, GF_OBJ_HANDLE* blade, GFATTACH attach,
                                             OPTMNT option) {
    GfMountManager* self = get();
#line 107
    GfWeapon* weapon = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfWeapon;
    GfGameMount* mount;
    if (static_cast<int>(attach) == 1) {
#line 111
        mount = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfGameMount(owner, weapon, option, attach);
    } else {
#line 113
        mount = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
            GfGameMountBlade(owner, weapon, option, attach, blade);
    }
    GF_MOUNT_HANDLE* handle = self->createHandle();
    MINFO info;
    info.m_mount = mount;
    info.m_handle = handle;
    self->m_mounts.push_back(info);
    return handle;
}

GF_MOUNT_HANDLE* GfMountManager::createMount(GF_OBJ_HANDLE* owner, GFATTACH attach, OPTMNT option) {
    return createMount(owner, reinterpret_cast<GF_OBJ_HANDLE*>(-1), attach, option);
}

GfGameMount* GfMountManager::getMount(GF_MOUNT_HANDLE* mount) {
    MountList& list = get()->m_mounts;
    for (MountList::iterator it = list.begin(); it != list.end(); ++it) {
        if (it->m_handle == mount) {
            return it->m_mount;
        }
    }
    return nullptr;
}

void GfMountManager::sendMessage(GF_OBJ_HANDLE* handle, GFATTACH attach, fw::MessageObject* sender, fw::Message& msg) {
    GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount == nullptr) {
        return;
    }
    mount->m_weapon->sendMessage(sender, msg);
}

void GfMountManager::execMount(GF_OBJ_HANDLE* handle, GFATTACH attach, OPTMNT option) {
    if (GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach))) {
        mount->execMount(option);
    }
}

GF_OBJ_HANDLE* GfMountManager::getHandle(GF_OBJ_HANDLE* handle, GFATTACH attach, OPTMNT option) {
    if (GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach))) {
        return mount->getHandle(option);
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

OPTMNT GfMountManager::getMountType(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    if (GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach))) {
        return mount->m_mountType;
    }
    return static_cast<OPTMNT>(-1);
}

void GfMountManager::setMountType(GF_OBJ_HANDLE* handle, GFATTACH attach, OPTMNT option) {
    if (GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach))) {
        mount->m_mountType = option;
    }
}

void GfMountManager::resetMountType(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    if (GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach))) {
        mount->m_mountType = static_cast<OPTMNT>(-1);
        mount->m_pending = true;
    }
}

GfAppendHandles* GfMountManager::getAppendHandles(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    if (GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach))) {
        return mount->m_weapon;
    }
    return nullptr;
}

GfWeapon* GfMountManager::getGfWeapon(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    if (GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach))) {
        return mount->m_weapon;
    }
    return nullptr;
}

void GfMountManager::addMountHandle(GF_MOUNT_HANDLE* mount, GF_OBJ_HANDLE* handle) {
    if (mount == reinterpret_cast<GF_MOUNT_HANDLE*>(-1) || handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return;
    }
    MountList::iterator it = get()->m_mounts.begin();
    while (it->m_handle != mount) {
        ++it;
    }
    GfGameMount* found = it->m_mount;
    found->addRef();
    info->m_mounts[found->m_attach].m_handle = mount;
}

void GfMountManager::removeMountHandle(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    GFOBJ_INFO* info = GfObjManager::getObjInfo(handle);
    if (info == nullptr) {
        return;
    }
    GF_MOUNT_HANDLE* mountHandle = info->m_mounts[attach].m_handle;
    if (mountHandle == reinterpret_cast<GF_MOUNT_HANDLE*>(-1)) {
        return;
    }
    info->m_mounts[attach].m_handle = reinterpret_cast<GF_MOUNT_HANDLE*>(-1);
    MountList::iterator it = get()->m_mounts.begin();
    while (it->m_handle != mountHandle) {
        ++it;
    }
    GfGameMount* mount = it->m_mount;
    mount->m_weapon->eraseHandle(handle);
    if (mount->m_RefCount <= 1) {
        if (mount != nullptr) {
            mount->release();
        }
        destroyMount(mountHandle);
    } else if (mount != nullptr) {
        mount->release();
    }
}

GF_OBJ_HANDLE* GfMountManager::getOptionRight(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    if (GfObjUtil::getMountHandle(handle, attach) != reinterpret_cast<GF_MOUNT_HANDLE*>(-1)) {
        GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach));
        if (mount != nullptr && mount->m_weapon != nullptr) {
            return mount->m_weapon->getObjHandles()[0];
        }
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

GF_OBJ_HANDLE* GfMountManager::getOptionLeft(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    if (GfObjUtil::getMountHandle(handle, attach) != reinterpret_cast<GF_MOUNT_HANDLE*>(-1)) {
        GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach));
        if (mount != nullptr && mount->m_weapon != nullptr) {
            return mount->m_weapon->getObjHandles()[1];
        }
    }
    return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

void GfMountManager::listenerGfObj(IGfObjListener::OBJEVT evt, GF_OBJ_HANDLE* handle, unsigned int) {
    if (evt == 3) {
        execDetachMount(handle, GFATTACH(0));
        execDetachMount(handle, GFATTACH(1));
        execDetachMount(handle, GFATTACH(2));
        execDetachMount(handle, GFATTACH(3));
    } else if (evt == 4) {
        removeMountHandle(handle, GFATTACH(0));
        removeMountHandle(handle, GFATTACH(1));
        removeMountHandle(handle, GFATTACH(2));
        removeMountHandle(handle, GFATTACH(3));
    }
}

void GfMountManager::execDetachMount(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount == nullptr) {
        return;
    }
    OPTMNT type = mount->m_mountType;
    execMount(handle, attach, static_cast<OPTMNT>(0));
    mount->m_pending = true;
    mount->m_mountType = type;
}

void GfMountManager::gevGameObjEnter(GF_OBJ_HANDLE* handle) {
    get()->execAttachMount(handle, GFATTACH(0));
    get()->execAttachMount(handle, GFATTACH(1));
    get()->execAttachMount(handle, GFATTACH(2));
    get()->execAttachMount(handle, GFATTACH(3));
}

void GfMountManager::execAttachMount(GF_OBJ_HANDLE* handle, GFATTACH attach) {
    GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount == nullptr || !mount->m_pending) {
        return;
    }
    OPTMNT option = mount->m_mountType != -1 ? mount->m_mountType : mount->m_option;
    switch (GfObjUtil::getObjType(handle)) {
    case 3:
    case 4:
    case 5:
    case 10:
    case 12:
    case 13:
    case 14:
        execMount(handle, attach, option);
        break;
    }
}

void GfMountManager::gevGameObjLeave(GF_OBJ_HANDLE* handle) {}

void GfMountManager::setAlphaMount(GF_OBJ_HANDLE* handle, GFATTACH attach, float alpha) {
    GfGameMount* mount = getMount(GfObjUtil::getMountHandle(handle, attach));
    if (mount == nullptr) {
        return;
    }
    for (int i = 0; i < 10; i++) {
        GF_OBJ_HANDLE* object = mount->m_weapon->getObjHandles()[i];
        if (object != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            GfObjAcc acc(object);
            acc.setAlphaNormal(alpha);
        }
    }
}

GfGameMount::~GfGameMount() {
    if (m_weapon != nullptr) {
        delete m_weapon;
        m_weapon = nullptr;
    }
}

GfAppendInfo* GfGameMount::getAppendInfo() {
    return GfObjUtil::getAppendInfo(m_owner, m_attach);
}

GF_OBJ_HANDLE* GfGameMount::getHandle(OPTMNT option) {
    switch (option) {
    case 1:
    case 2:
    case 4:
        return m_owner;
    default:
        return reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    }
}

inline void GfGameMount::setScaleMount(float scale) {
    for (int i = 0; i < 10; i++) {
        GF_OBJ_HANDLE* object = m_weapon->getObjHandles()[i];
        if (object != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            GfObjSetup* setup = GfObjUtil::getObjSetup(object);
            GfAppend* append = GfObjUtil::getAppend(object, m_attach);
            float base = 1.0f;
            if (append != nullptr) {
                base = append->m_scale * setup->m_initialScale.x;
            }
            GfObjAcc acc(m_weapon->getObjHandles()[i]);
            acc.setModelScale(base * scale);
        }
    }
}

void GfGameMount::detach() {
    for (int i = 0; i < 10; i++) {
        if (m_weapon->getObjHandles()[i] != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            GfObjUtil::unmountFromBone(m_weapon->getObjHandles()[i]);
        }
    }
    if (m_pending) {
        m_pending = false;
    }
    setScaleMount(1.0f);
}

void GfGameMount::attach(OPTMNT option, GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfAppendInfo* info = getAppendInfo();
    if (info != nullptr && info->m_appends[1].size() != 0) {
        bool first = option == 1 || option == 2;
        info->m_list = !first;
        m_weapon->m_useSecond = !first;
        GfMountManager::setAlphaMount(handle, m_attach, 0.0f);
        m_weapon->fn_71002AE854();
        info->m_list = first;
        m_weapon->m_useSecond = first;
        GfMountManager::setAlphaMount(handle, m_attach, 1.0f);
        m_weapon->fn_71002AE854();
    }
    for (int i = 0; i < 10; i++) {
        GfObjAcc acc(m_weapon->getObjHandles()[i]);
        if (acc.isValidModel()) {
            GF_OBJ_HANDLE* parent = GfObjUtil::getParentHandle(acc.getHandle());
            if (GfObjUtil::isUpdate(handle) && acc.isValidModel() && parent == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
                if (GfAppend* append = GfObjUtil::getAppend(acc.getHandle(), m_attach)) {
                    GfObjUtil::mountToBone(acc.getHandle(), handle, append->getBone(option));
                }
            }
        }
    }
    if (option == 3) {
        GfObjAcc owner(handle);
        if (owner.getType() == 4) {
            setScaleMount(GfDataBlade::getWpnScale(owner.getBladeId()));
        }
    }
}

unsigned int GfGameMount::getAllWeapons() const {
    unsigned int count = 0;
    for (int i = 0; i < 10; i++) {
        if (m_weapon->m_handles[i] != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            count++;
        }
        if (m_weapon->m_secondHandles[i] != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            count++;
        }
    }
    return count;
}

bool GfGameMount::setWeaponOwner(OPTMNT option) {
    switch (option) {
    case 0:
    case 1:
    case 2:
    case 4:
        setWeaponOwner(getHandle(static_cast<OPTMNT>(2)));
        return true;
    default:
        return false;
    }
}

void GfGameMount::setWeaponOwner(GF_OBJ_HANDLE* owner) {
    for (int i = 0; i < 10; i++) {
        if (m_weapon->getObjHandles()[i] != reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
            GfObjUtil::setOwner(m_weapon->getObjHandles()[i], owner);
        }
    }
}

void GfWeapon::fn_71002AE854() {
    for (int i = 0; i < 10; i++) {
        GfObj* obj = GfObjUtil::getObj(getObjHandles()[i]);
        if (obj == nullptr) {
            continue;
        }
        if (GfComAsm* comAsm = obj->getComponent<GfComAsm>(2)) {
            GfObjAcc owner(GfGameUtil::getWeaponOwner(obj->m_handle));
            mm::mtl::FixStr<32> state;
            GfGameUtil::makeWeaponStateIdle(state, owner.getHandle(), owner.isBattle());
            comAsm->setState(state.m_str, AnimLayer(0));
        }
    }
}

bool GfGameMountBlade::execMount(OPTMNT option) {
    if (GfGameMount::execMount(option)) {
        return true;
    }
    if (option != 3) {
        return false;
    }
    if (GfObjUtil::getObj(m_blade) != nullptr) {
        detach();
        attach(static_cast<OPTMNT>(3), m_blade);
        m_mountType = static_cast<OPTMNT>(3);
    }
    return true;
}

GF_OBJ_HANDLE* GfGameMountBlade::getHandle(OPTMNT option) {
    GF_OBJ_HANDLE* handle = GfGameMount::getHandle(option);
    if (option == 3 && handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        handle = m_blade;
    }
    return handle;
}

bool GfGameMountBlade::setWeaponOwner(OPTMNT option) {
    GF_OBJ_HANDLE* owner;
    switch (option) {
    case 0:
    case 1:
    case 2:
    case 4:
        owner = getHandle(static_cast<OPTMNT>(2));
        break;
    case 3:
        owner = m_blade;
        break;
    default:
        return false;
    }
    GfGameMount::setWeaponOwner(owner);
    return true;
}

GfAppendInfo* GfGameMountBlade::getAppendInfo() {
    if (GfAppendInfo* info = GfObjUtil::getAppendInfo(m_blade, m_attach)) {
        return info;
    }
    return GfGameMount::getAppendInfo();
}

}  // namespace gf
