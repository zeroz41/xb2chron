#ifndef CLASSES_GF_DATAOBJMOB_H
#define CLASSES_GF_DATAOBJMOB_H

#include "classes/gf/IDataObj.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B4FA18: a mob's data (GfDataMob's and GfBdatRsc's mob list row)
class DataObjMob : public ::gf::IDataObj {
public:
    DataObjMob(GF_OBJ_HANDLE* handle);
    DataObjMob(unsigned int id);
    virtual bool isValid() const;  // slot 3
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual const char* getName() const;  // slot 8
    virtual bool getName(unsigned char*& bdat, unsigned int& id) const;  // slot 10
    virtual unsigned int getBdatId() const;  // slot 11
    virtual int getObjType() const { return 7; }  // slot 12
    virtual unsigned int getFootStep() const;  // slot 34
    virtual unsigned int getFootStepEffect() const;  // slot 35
    virtual bool isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual int getMenuOffset() const;  // slot 55

    GF_OBJ_HANDLE* m_handle;  // the object's, -1 for data read by row id alone (the name is not the original's)
    unsigned int m_bdatId;  // the row (getBdatId; the name is not the original's)
};
}  // namespace gf

#endif
