#ifndef CLASSES_GF_DATAOBJMAP_H
#define CLASSES_GF_DATAOBJMAP_H

#include "classes/gf/IDataObj.h"

namespace gf {
// table 0x7100B4F5D8
class DataObjMap : public ::gf::IDataObj {
public:
    virtual ~DataObjMap();  // slot 0
    virtual bool isValid() const;  // slot 3
    virtual void getName() const;  // slot 8
    virtual void getBdatId() const;  // slot 11
    virtual void getObjType() const;  // slot 12
    virtual void vf42();  // slot 42
    virtual bool isScenarioMask() const;  // slot 43
    virtual void vf46();  // slot 46
    virtual void setVirtualEquipWpn(unsigned int, int);  // slot 47
    virtual void setVirtualEquipAcc(unsigned int, unsigned int);  // slot 48
    virtual void vf49();  // slot 49
    virtual void setVirtualEquipWpnChip(unsigned int);  // slot 50
    virtual void setVirtualEquipOrb(unsigned int, unsigned int);  // slot 51
    virtual void vf52();  // slot 52
};
}  // namespace gf

#endif
