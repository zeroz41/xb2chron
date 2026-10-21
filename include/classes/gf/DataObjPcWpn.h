#ifndef CLASSES_GF_DATAOBJPCWPN_H
#define CLASSES_GF_DATAOBJPCWPN_H

#include "classes/gf/IDataObj.h"

namespace gf {
// table 0x7100B4E4D8
class DataObjPcWpn : public ::gf::IDataObj {
public:
    virtual ~DataObjPcWpn();  // slot 0
    virtual bool isValid() const;  // slot 3
    virtual void getName() const;  // slot 8
    virtual void getName(unsigned char*&, unsigned int&) const;  // slot 10
    virtual void getBdatId() const;  // slot 11
    virtual void getObjType() const;  // slot 12
    virtual void getWeaponDamage(bool) const;  // slot 29
    virtual void getWeaponStability(bool) const;  // slot 30
    virtual void getWeaponType(bool, int) const;  // slot 31
    virtual void getAttribute(bool, int) const;  // slot 40
    virtual void vf42();  // slot 42
    virtual bool isScenarioMask() const;  // slot 43
    virtual void vf46();  // slot 46
    virtual void setVirtualEquipWpn(unsigned int, int);  // slot 47
    virtual void setVirtualEquipAcc(unsigned int, unsigned int);  // slot 48
    virtual void vf49();  // slot 49
    virtual void setVirtualEquipWpnChip(unsigned int);  // slot 50
    virtual void setVirtualEquipOrb(unsigned int, unsigned int);  // slot 51
    virtual void vf52();  // slot 52
    virtual bool isEnbaleTarget() const { return false; }  // slot 54
    virtual void getBladeSet(bool) const;  // slot 65
    virtual void getEquipWeapon(bool, int) const;  // slot 82
};
}  // namespace gf

#endif
