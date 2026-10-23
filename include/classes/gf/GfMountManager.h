#ifndef CLASSES_GF_GFMOUNTMANAGER_H
#define CLASSES_GF_GFMOUNTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedList.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_MOUNT_HANDLE; }
namespace gf { class GfAppendHandles; }
namespace gf { class GfGameMount; }
namespace gf { class GfSetupParam; }
namespace gf { class GfWeapon; }
namespace gf { enum OPTMNT : int; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
#include "gf/GFATTACH.h"
namespace gf { class GfMountManager; }
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfObjManager.h"

namespace gf {
// table 0x7100B54D28: the objects' mounts, each under a handle the objects' infos keep (build registers it as an
// object listener at 0x8: GfObjManager::addListener(this + 8))
class GfMountManager : public ::mm::mtl::PtrSingleton< ::gf::GfMountManager>, public ::gf::IGfObjListener {
public:
    // a mount and its handle: the list's element (1.0.0's FixedList<gf::GfMountManager::MINFO, 256>::erase names
    // the type; the field names are not the original's)
    struct MINFO {
        GfGameMount* m_mount;
        GF_MOUNT_HANDLE* m_handle;
    };
    typedef mm::mtl::FixedList<MINFO, 256> MountList;  // the typedef's name is not the original's

    // build's (out of line in 1.0.0, as are initialize, finalize and createHandle; 3.0.1 keeps no copy)
    GfMountManager(const GfSetupParam& param) : m_nextHandle(nullptr), m_active(false) {
        initialize(param);
    }
    void initialize(const GfSetupParam& param) {
        GfObjManager::addListener(this, static_cast<IGfObjListener::OBJEVT>(0));
        m_nextHandle = nullptr;
        m_active = true;
    }
    void finalize() {
        GfObjManager::removeListener(this);
        m_active = false;
    }
    // the next handle, counting from 0 and skipping -1
    GF_MOUNT_HANDLE* createHandle() {
        GF_MOUNT_HANDLE* handle = m_nextHandle;
        unsigned long next = reinterpret_cast<unsigned long>(handle) + 1;
        m_nextHandle = next == static_cast<unsigned long>(-1) ? nullptr : reinterpret_cast<GF_MOUNT_HANDLE*>(next);
        return handle;
    }
    virtual ~GfMountManager();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT evt, gf::GF_OBJ_HANDLE* handle, unsigned int);  // slot 2

    static void build(const GfSetupParam& param);
    static void destroy();
    // a mount of a weapon on owner's point (a blade's mount when the point is not 1), its new handle
    static GF_MOUNT_HANDLE* createMount(GF_OBJ_HANDLE* owner, GF_OBJ_HANDLE* blade, GFATTACH attach, OPTMNT option);
    static GF_MOUNT_HANDLE* createMount(GF_OBJ_HANDLE* owner, GFATTACH attach, OPTMNT option);
    // the mount under a handle out of the list (1.0.0's; 3.0.1 keeps no copy)
    static void destroyMount(GF_MOUNT_HANDLE* mount) {
        MountList& list = get()->m_mounts;
        for (MountList::iterator it = list.begin(); it != list.end(); ++it) {
            if (it->m_handle == mount) {
                list.erase(it);
                return;
            }
        }
    }
    // the mount under a handle, none without
    static GfGameMount* getMount(GF_MOUNT_HANDLE* mount);
    // msg handed to what an object has mounted at a point, from sender
    static void sendMessage(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach, fw::MessageObject* sender,
                            fw::Message& msg);
    // the mount of an object's point set to a mount option (GfComBehavior's "weaponAttach" passes 1,
    // "weaponDetach" 2)
    static void execMount(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach, gf::OPTMNT option);
    static GF_OBJ_HANDLE* getHandle(GF_OBJ_HANDLE* handle, GFATTACH attach, OPTMNT option);
    static OPTMNT getMountType(GF_OBJ_HANDLE* handle, GFATTACH attach);
    static void setMountType(GF_OBJ_HANDLE* handle, GFATTACH attach, OPTMNT option);
    static void resetMountType(GF_OBJ_HANDLE* handle, GFATTACH attach);
    static GfAppendHandles* getAppendHandles(GF_OBJ_HANDLE* handle, GFATTACH attach);
    // the weapon mounted on an object's point, none without
    static gf::GfWeapon* getGfWeapon(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    static void addMountHandle(gf::GF_MOUNT_HANDLE* mount, gf::GF_OBJ_HANDLE* handle);
    static void removeMountHandle(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    // the objects mounted at a point's right and left options, (GF_OBJ_HANDLE*)-1 without
    static gf::GF_OBJ_HANDLE* getOptionRight(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    static gf::GF_OBJ_HANDLE* getOptionLeft(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    void execDetachMount(GF_OBJ_HANDLE* handle, GFATTACH attach);
    static void gevGameObjEnter(GF_OBJ_HANDLE* handle);
    void execAttachMount(GF_OBJ_HANDLE* handle, GFATTACH attach);
    static void gevGameObjLeave(GF_OBJ_HANDLE* handle);
    static void setAlphaMount(GF_OBJ_HANDLE* handle, GFATTACH attach, float alpha);

    // (the field names are not the original's)
    MountList m_mounts;
    GF_MOUNT_HANDLE* m_nextHandle;  // createMount's next handle, counting from 0 and wrapping before -1
    bool m_active;                  // set while built, cleared by destroy
};
}  // namespace gf

#endif
