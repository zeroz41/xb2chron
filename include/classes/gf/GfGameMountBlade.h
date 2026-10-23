#ifndef CLASSES_GF_GFGAMEMOUNTBLADE_H
#define CLASSES_GF_GFGAMEMOUNTBLADE_H

#include "classes/gf/GfGameMount.h"

namespace gf { enum OPTMNT : int; }

namespace gf {
// table 0x7100B54DA8: a mount whose weapon a blade holds at option 3 (its destructor slot is GfGameMount's: inline)
class GfGameMountBlade : public ::gf::GfGameMount {
public:
    // GfMountManager::createMount's (inline: 3.0.1 keeps no copy)
    GfGameMountBlade(GF_OBJ_HANDLE* owner, GfWeapon* weapon, OPTMNT option, GFATTACH attach, GF_OBJ_HANDLE* blade)
        : GfGameMount(owner, weapon, option, attach), m_blade(blade) {}
    virtual bool execMount(gf::OPTMNT option);  // slot 2
    virtual bool setWeaponOwner(gf::OPTMNT option);  // slot 3
    virtual GF_OBJ_HANDLE* getHandle(gf::OPTMNT option);  // slot 4
    virtual GfAppendInfo* getAppendInfo();  // slot 5

    GF_OBJ_HANDLE* m_blade;  // the blade holding the weapon (the name is not the original's)
};
}  // namespace gf

#endif
