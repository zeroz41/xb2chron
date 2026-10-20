#ifndef CLASSES_GF_DATAOBJUIOBJ_H
#define CLASSES_GF_DATAOBJUIOBJ_H

#include "classes/gf/IDataObj.h"

namespace gf {
// table 0x7100B4FE58
class DataObjUiObj : public ::gf::IDataObj {
public:
    virtual ~DataObjUiObj();  // slot 0
    virtual void isValid() const;  // slot 3
    virtual void getModelResourceName() const;  // slot 4
    virtual void getMotionResourceName() const;  // slot 5
    virtual void getName() const;  // slot 8
    virtual void getName(unsigned char*&, unsigned int&) const;  // slot 10
    virtual void getBdatId() const;  // slot 11
    virtual void getObjType() const;  // slot 12
    virtual void isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual void vf42();  // slot 42
    virtual void setVirtualEquipWpn(unsigned int, int);  // slot 47
    virtual void setVirtualEquipWpnChip(unsigned int);  // slot 50
    virtual void setVirtualEquipOrb(unsigned int, unsigned int);  // slot 51
};
}  // namespace gf

#endif
