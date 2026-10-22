#ifndef GF_GFOBJACC_H
#define GF_GFOBJACC_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GFOBJ_INFO; }
namespace gf { class GfObj; }

namespace gf {
// which of an object's user data pointers (GfObjAcc::getUserData reads the info's at 0x70 + 8 * it)
enum GfObjUserData {};

// access to one object through its handle or its GfObj: the manager's info for it and the object
class GfObjAcc {
public:
    GfObjAcc(GfObj* obj);
    GfObjAcc(GF_OBJ_HANDLE* handle);
    bool testFlag(unsigned int flag) const;
    GfObj* getObj() const;
    bool isDestroy() const;
    void* getUserData(GfObjUserData kind) const;
    int getType() const;  // the object's type (3: a driver)
    unsigned int getBdatId() const;

    GFOBJ_INFO* m_info;  // GfObjManager::getObjInfo's for the handle
    GfObj* m_obj;  // the GfObj constructor's argument
};
}  // namespace gf

#endif
