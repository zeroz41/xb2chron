#ifndef CLASSES_GF_GFMOUNTMANAGER_H
#define CLASSES_GF_GFMOUNTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_MOUNT_HANDLE; }
namespace gf { class GfWeapon; }
namespace gf { enum OPTMNT : int; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
#include "gf/GFATTACH.h"
namespace gf { class GfMountManager; }
#include "classes/gf/IGfObjListener.h"

namespace gf {
// a base of gf::GfMountManager no evidence names yet
class TUnk_B54D50 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// table 0x7100B54D28; base at 0x8 unknown (TUnk_B54D50)
class GfMountManager : public ::mm::mtl::PtrSingleton< ::gf::GfMountManager>, public TUnk_B54D50 {
public:
    virtual ~GfMountManager();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    // the weapon mounted on an object's point, none without
    static gf::GfWeapon* getGfWeapon(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    static void addMountHandle(gf::GF_MOUNT_HANDLE* mount, gf::GF_OBJ_HANDLE* handle);
    static void removeMountHandle(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    // msg handed to what an object has mounted at a point, from sender
    static void sendMessage(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach, fw::MessageObject* sender,
                            fw::Message& msg);
    // the mount of an object's point set to a mount option (GfComBehavior's "weaponAttach" passes 1,
    // "weaponDetach" 2)
    static void execMount(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach, gf::OPTMNT option);
    // the objects mounted at a point's right and left options, (GF_OBJ_HANDLE*)-1 without
    static gf::GF_OBJ_HANDLE* getOptionRight(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
    static gf::GF_OBJ_HANDLE* getOptionLeft(gf::GF_OBJ_HANDLE* handle, gf::GFATTACH attach);
};
}  // namespace gf

#endif
