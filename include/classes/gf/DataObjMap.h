#ifndef CLASSES_GF_DATAOBJMAP_H
#define CLASSES_GF_DATAOBJMAP_H

#include "classes/gf/IDataObj.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B4F5D8: a map object's data (GfBdatMaplist's row)
class DataObjMap : public ::gf::IDataObj {
public:
    DataObjMap(GF_OBJ_HANDLE* handle);
    DataObjMap(unsigned int id);
    virtual bool isValid() const;  // slot 3
    virtual const char* getName() const;  // slot 8
    virtual unsigned int getBdatId() const;  // slot 11
    virtual int getObjType() const { return 1; }  // slot 12

    GF_OBJ_HANDLE* m_handle;  // the object's, -1 for data read by row id alone (the name is not the original's)
    unsigned int m_bdatId;  // the row (getBdatId; the name is not the original's)
};
}  // namespace gf

#endif
