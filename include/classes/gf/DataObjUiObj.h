#ifndef CLASSES_GF_DATAOBJUIOBJ_H
#define CLASSES_GF_DATAOBJUIOBJ_H

#include "classes/gf/IDataObj.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B4FE58: a UI object's data (read as a mob's rows)
class DataObjUiObj : public ::gf::IDataObj {
public:
    DataObjUiObj(unsigned int id);
    virtual bool isValid() const;  // slot 3
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual const char* getName() const;  // slot 8
    virtual bool getName(unsigned char*& bdat, unsigned int& id) const;  // slot 10
    virtual unsigned int getBdatId() const;  // slot 11
    virtual int getObjType() const { return 7; }  // slot 12
    virtual bool isDispInitExtraParts(unsigned int) const;  // slot 41

    GF_OBJ_HANDLE* m_handle;  // -1: data read by row id alone (the name is not the original's)
    unsigned int m_bdatId;  // the row (getBdatId; the name is not the original's)
};
}  // namespace gf

#endif
