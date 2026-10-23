#ifndef GF_GFOBJACC_H
#define GF_GFOBJACC_H

namespace fw { class Transform; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GFOBJ_INFO; }
namespace gf { class GfObj; }

namespace gf {
// what GfObjAcc::isDisp asks about an object's display (GfMenuPosAdapter::update asks 0)
enum OBJDISP {};

// which of an object's user data pointers (GfObjAcc::getUserData reads the info's at 0x70 + 8 * it)
enum GfObjUserData {};

// access to one object through its handle or its GfObj: the manager's info for it and the object
class GfObjAcc {
public:
    GfObjAcc(GfObj* obj);
    GfObjAcc(GF_OBJ_HANDLE* handle);
    bool testFlag(unsigned int flag) const;
    GfObj* getObj() const;
    // the object's world transform (its frame's, synced first)
    const fw::Transform& getWorldTransform() const;
    // the same without syncing the frame first
    const fw::Transform& getWorldTransformNoSync() const;
    bool isDestroy() const;
    void* getUserData(GfObjUserData kind) const;
    int getType() const;  // the object's type (3: a driver)
    unsigned int getBdatId() const;
    bool isDisp(OBJDISP disp) const;
    bool isValidTransform() const;  // its world transform can be read
    // a bone's world transform; false when the object has no such bone
    bool getBoneTransform(fw::Transform& transform, const char* bone);
    float getModelScale() const;
    // the object's attribute bits (bit 1: TargetIKPlugin::update looks at it)
    unsigned int getAttribute() const;
    GF_OBJ_HANDLE* getHandle() const;
    unsigned int getPcWeaponId() const;  // the driver weapon object's weapon row (DataObjPcWpn)

    GFOBJ_INFO* m_info;  // GfObjManager::getObjInfo's for the handle
    GfObj* m_obj;  // the GfObj constructor's argument
};
}  // namespace gf

#endif
