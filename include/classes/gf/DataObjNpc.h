#ifndef CLASSES_GF_DATAOBJNPC_H
#define CLASSES_GF_DATAOBJNPC_H

#include "classes/gf/IDataObj.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B4F198: an NPC's data (GfDataNpc's, by its row)
class DataObjNpc : public ::gf::IDataObj {
public:
    DataObjNpc(GF_OBJ_HANDLE* handle);
    DataObjNpc(unsigned int id);
    virtual bool isValid() const;  // slot 3
    virtual const char* getModelResourceName() const;  // slot 4
    virtual const char* getMotionResourceName() const;  // slot 5
    virtual const char* getName() const;  // slot 8
    virtual bool getName(unsigned char*& bdat, unsigned int& id) const;  // slot 10
    virtual unsigned int getBdatId() const;  // slot 11
    virtual int getObjType() const { return 6; }  // slot 12
    virtual unsigned int getFootStep() const;  // slot 34
    virtual unsigned int getFootStepEffect() const;  // slot 35
    virtual bool isDispInitExtraParts(unsigned int) const;  // slot 41
    virtual int getMenuOffset() const;  // slot 55
    virtual unsigned int getEyeRotControl() const;  // slot 59

    GF_OBJ_HANDLE* m_handle;  // the object's, -1 for data read by row id alone (the name is not the original's)
    unsigned int m_bdatId;  // the row (getBdatId; the name is not the original's)
};
}  // namespace gf

#endif
