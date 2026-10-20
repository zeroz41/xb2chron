#ifndef CLASSES_GF_GFGAMEMOUNTBLADE_H
#define CLASSES_GF_GFGAMEMOUNTBLADE_H

#include "classes/gf/GfGameMount.h"

namespace gf { enum OPTMNT : int; }

namespace gf {
// table 0x7100B54DA8
class GfGameMountBlade : public ::gf::GfGameMount {
public:
    virtual ~GfGameMountBlade();  // slot 0
    virtual void execMount(gf::OPTMNT);  // slot 2
    virtual void setWeaponOwner(gf::OPTMNT);  // slot 3
    virtual void getHandle(gf::OPTMNT);  // slot 4
    virtual void getAppendInfo();  // slot 5
};
}  // namespace gf

#endif
