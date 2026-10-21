#ifndef CLASSES_GF_DATAOBJMOB_H
#define CLASSES_GF_DATAOBJMOB_H

#include "classes/gf/IDataObj.h"

namespace gf {
// table 0x7100B4FA18
class DataObjMob : public ::gf::IDataObj {
public:
    virtual ~DataObjMob();  // slot 0
    virtual bool isValid() const;  // slot 3
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual void getName() const;  // slot 8
    virtual void getName(unsigned char*&, unsigned int&) const;  // slot 10
    virtual void getBdatId() const;  // slot 11
    virtual void getObjType() const;  // slot 12
    virtual void getFootStep() const;  // slot 34
    virtual void getFootStepEffect() const;  // slot 35
    virtual bool isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual void vf42();  // slot 42
    virtual bool isScenarioMask() const;  // slot 43
    virtual void vf46();  // slot 46
    virtual void setVirtualEquipWpn(unsigned int, int);  // slot 47
    virtual void setVirtualEquipAcc(unsigned int, unsigned int);  // slot 48
    virtual void vf49();  // slot 49
    virtual void setVirtualEquipWpnChip(unsigned int);  // slot 50
    virtual void setVirtualEquipOrb(unsigned int, unsigned int);  // slot 51
    virtual void vf52();  // slot 52
    virtual void getMenuOffset() const;  // slot 55
};
}  // namespace gf

#endif
