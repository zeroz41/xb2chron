#ifndef CLASSES_GF_DATAOBJPCWPN_H
#define CLASSES_GF_DATAOBJPCWPN_H

#include "classes/gf/IDataObj.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B4E4D8: a driver weapon's data (GfBdatItem's PcWpn rows)
class DataObjPcWpn : public ::gf::IDataObj {
public:
    DataObjPcWpn(unsigned int id);
    DataObjPcWpn(GF_OBJ_HANDLE* handle);
    virtual ~DataObjPcWpn();  // slot 0
    virtual bool isValid() const;  // slot 3
    virtual const char* getName() const;  // slot 8
    virtual bool getName(unsigned char*& bdat, unsigned int& id) const;  // slot 10
    virtual unsigned int getBdatId() const;  // slot 11
    virtual int getObjType() const { return 10; }  // slot 12
    virtual unsigned int getWeaponDamage(bool) const;  // slot 29
    virtual unsigned int getWeaponStability(bool) const;  // slot 30
    virtual unsigned int getWeaponType(bool, int) const;  // slot 31
    virtual unsigned int getAttribute(bool, int) const;  // slot 40
    virtual bool isEnbaleTarget() const { return false; }  // slot 54
    virtual int getBladeSet(bool) const;  // slot 65
    virtual unsigned int getEquipWeapon(bool, int) const;  // slot 82

    GF_OBJ_HANDLE* m_handle;  // the object's, -1 for data read by row id alone (the name is not the original's)
    unsigned int m_bdatId;  // the weapon's row (getBdatId; the name is not the original's)
};
}  // namespace gf

#endif
