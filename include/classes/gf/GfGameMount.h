#ifndef CLASSES_GF_GFGAMEMOUNT_H
#define CLASSES_GF_GFGAMEMOUNT_H

#include "classes/mm/mtl/ReferenceObject.h"
#include "gf/GFATTACH.h"

namespace gf { enum OPTMNT : int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfAppendInfo; }
namespace gf { class GfWeapon; }

namespace gf {
// table 0x7100B54D68: what an object has mounted at one of its points, counted by the objects that hold it
// (GfMountManager::addMountHandle adds a reference, removeMountHandle releases one: reference_object.h's assertion)
class GfGameMount : public ::mm::mtl::ReferenceObject {
public:
    // GfMountManager::createMount's (inline: 3.0.1 keeps no copy)
    GfGameMount(GF_OBJ_HANDLE* owner, GfWeapon* weapon, OPTMNT option, GFATTACH attach)
        : m_owner(owner), m_weapon(weapon), m_mountType(static_cast<OPTMNT>(-1)), m_option(option),
          m_pending(true), m_attach(attach) {}
    virtual ~GfGameMount();  // slot 0
    // the weapon put at the mount option's place: false when the option has none
    virtual bool execMount(gf::OPTMNT option);  // slot 2
    virtual bool setWeaponOwner(gf::OPTMNT option);  // slot 3
    // the object the weapon mounts on at an option, (GF_OBJ_HANDLE*)-1 for none
    virtual GF_OBJ_HANDLE* getHandle(gf::OPTMNT option);  // slot 4
    virtual GfAppendInfo* getAppendInfo();  // slot 5

    // the weapon's models scaled by scale times their appends' and setups' scales (1.0.0's, out of line; inline
    // in 3.0.1, which keeps no copy: detach passes 1, attach the blade's weapon scale)
    inline void setScaleMount(float scale);
    // whether every set object of the weapon is a valid game object, and one is (1.0.0's, out of line; inline in
    // 3.0.1, which keeps no copy: execMount mounts only then)
    inline bool isEnableOption() const;
    void detach();
    void attach(OPTMNT option, GF_OBJ_HANDLE* handle);
    unsigned int getAllWeapons() const;
    GF_OBJ_HANDLE* getAllWeapons(unsigned int index) const;
    void setWeaponOwner(GF_OBJ_HANDLE* owner);

    // (the field names are not the original's)
    GF_OBJ_HANDLE* m_owner;  // the object mounting (createMount's)
    GfWeapon* m_weapon;      // the objects mounted; the destructor deletes it
    OPTMNT m_mountType;      // the option execMount last put the weapon at, -1 before (getMountType / setMountType)
    OPTMNT m_option;         // the option asked for while the weapon's objects were not ready
    // set at first and by resetMountType: execAttachMount mounts again as an object enters; detach clears it
    bool m_pending;
    GFATTACH m_attach;       // the owner's point
};
}  // namespace gf

#endif
