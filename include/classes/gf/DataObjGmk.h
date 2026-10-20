#ifndef CLASSES_GF_DATAOBJGMK_H
#define CLASSES_GF_DATAOBJGMK_H

#include "classes/gf/IDataObj.h"

namespace gf {
// table 0x7100B50298
class DataObjGmk : public ::gf::IDataObj {
public:
    virtual ~DataObjGmk();  // slot 0
    virtual void isValid() const;  // slot 3
    virtual void getModelResourceName() const;  // slot 4
    virtual void getMotionResourceName() const;  // slot 5
    virtual void getName() const;  // slot 8
    virtual void getName(unsigned char*&, unsigned int&) const;  // slot 10
    virtual void getBdatId() const;  // slot 11
    virtual void getObjType() const;  // slot 12
    virtual void isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual void vf42();  // slot 42
    virtual void isScenarioMask() const;  // slot 43
    virtual void vf46();  // slot 46
    virtual void setVirtualEquipWpn(unsigned int, int);  // slot 47
    virtual void setVirtualEquipAcc(unsigned int, unsigned int);  // slot 48
    virtual void vf49();  // slot 49
    virtual void setVirtualEquipWpnChip(unsigned int);  // slot 50
    virtual void setVirtualEquipOrb(unsigned int, unsigned int);  // slot 51
    virtual void vf52();  // slot 52
    virtual void getGimmickType() const;  // slot 133
};
}  // namespace gf

#endif
