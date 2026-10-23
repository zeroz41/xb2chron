#ifndef CLASSES_GF_DATAOBJBELONGING_H
#define CLASSES_GF_DATAOBJBELONGING_H

#include "classes/gf/IDataObj.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B506D8: a belonging's data (it has no rows)
class DataObjBelonging : public ::gf::IDataObj {
public:
    DataObjBelonging(GF_OBJ_HANDLE* handle);
    virtual bool isValid() const;  // slot 3
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual const char* getName() const;  // slot 8
    virtual bool getName(unsigned char*& bdat, unsigned int& id) const;  // slot 10
    virtual unsigned int getBdatId() const;  // slot 11
    virtual int getObjType() const { return 13; }  // slot 12

    GF_OBJ_HANDLE* m_handle;  // the object's (isValid: not -1; the name is not the original's)
};
}  // namespace gf

#endif
