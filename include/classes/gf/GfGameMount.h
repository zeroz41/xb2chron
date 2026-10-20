#ifndef CLASSES_GF_GFGAMEMOUNT_H
#define CLASSES_GF_GFGAMEMOUNT_H

namespace gf { enum OPTMNT : int; }

namespace gf {
// table 0x7100B54D68
class GfGameMount {
public:
    virtual ~GfGameMount();  // slot 0
    virtual void execMount(gf::OPTMNT);  // slot 2
    virtual void setWeaponOwner(gf::OPTMNT);  // slot 3
    virtual void getHandle(gf::OPTMNT);  // slot 4
    virtual void getAppendInfo();  // slot 5
};
}  // namespace gf

#endif
