#ifndef CLASSES_GF_DATAOBJGMK_H
#define CLASSES_GF_DATAOBJGMK_H

#include "classes/gf/IDataObj.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B50298: a gimmick's data (GfBdatRsc's treasure box or map object row, by its gimmick type)
class DataObjGmk : public ::gf::IDataObj {
public:
    DataObjGmk(GF_OBJ_HANDLE* handle);
    DataObjGmk(unsigned int id, GimmickType type);
    virtual bool isValid() const;  // slot 3
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual const char* getName() const;  // slot 8
    virtual bool getName(unsigned char*& bdat, unsigned int& id) const;  // slot 10
    virtual unsigned int getBdatId() const;  // slot 11
    virtual int getObjType() const { return 8; }  // slot 12
    virtual bool isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual GimmickType getGimmickType() const { return m_gimmickType; }  // slot 133

    GF_OBJ_HANDLE* m_handle;  // the object's, -1 for data read by row id alone (the name is not the original's)
    unsigned int m_bdatId;  // the row (getBdatId; the name is not the original's)
    GimmickType m_gimmickType;  // getGimmickType (1: a treasure box; the name is not the original's)
};
}  // namespace gf

#endif
