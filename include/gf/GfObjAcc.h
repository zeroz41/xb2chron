#ifndef GF_GFOBJACC_H
#define GF_GFOBJACC_H

#include "gf/GfAlphaProperty.h"

namespace fw { class Transform; }
namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GFOBJ_INFO; }
namespace gf { class GfObj; }
namespace ml { class ScnObjModel; }
namespace mm { class Vec3; }

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
    // the object's world transform (its frame's, synced first)
    const fw::Transform& getWorldTransform() const;
    // the same without syncing the frame first
    const fw::Transform& getWorldTransformNoSync() const;
    // its position and its turn about the vertical; false without a transform component
    bool getObjPosRot(mm::Vec3& pos, float& rotY);
    bool isValidTransform() const;  // its world transform can be read
    float getAlpha(OBJ_ALPHA kind) const;
    void setAlpha(OBJ_ALPHA kind, float alpha);
    bool isAlphaChanged() const;
    void setAlphaEvent(float alpha);
    float getAlphaEvent() const;
    void setAlphaEvtDisp(float alpha);
    void setAlphaCamera(float alpha);
    float getAlphaCamera() const;
    void setAlphaLife(float alpha);
    float getAlphaLife() const;
    void setAlphaNormal(float alpha);
    float getAlphaNormal() const;
    float getAlpha() const;
    void applyAlpha();
    ml::ScnObjModel* getScnModel() const;
    void setFrameSpeed(float speed);
    void setCameraFade(bool on);
    void setFlag(unsigned int flag, bool on);
    bool testFlag(unsigned int flag) const;
    bool isCameraFadeDisableForEvent() const;
    void setCameraFadeDisableForEvent(bool on);
    bool isCameraFadeDisableForBattle() const;
    void setCameraFadeDisableForBattle(bool on);
    bool isCameraFadeAllOK() const;
    bool hasParent() const;
    // shows or hides it for disp (GfEvtModelDriver::setDispWeapon asks 2 for its weapons)
    void setDisp(OBJDISP disp, bool on);
    GfObj* getObj() const;
    GF_OBJ_HANDLE* getHandle() const;
    bool isDisp(OBJDISP disp) const;
    bool isDispChanged() const;
    void applyDisp();
    void setGpuClip(bool on);
    void setModelScaleForMenu(const mm::Vec3& scale);
    void setModelScale(float scale);
    const mm::Vec3& getModelScaleXYZ() const;
    float getModelScale() const;
    void setRenderCameraFade(bool on);
    void setGravity(bool on);
    bool isReload() const;
    bool isRebuild() const;  // the layer the object updates in (fw::Framework::isLayerPause takes it)
    void setAttribute(unsigned int attribute);
    // the object's attribute bits (bit 1: TargetIKPlugin::update looks at it)
    unsigned int getAttribute() const;
    float getModelRadius() const;
    float getModelAlpha() const;
    void applyClip();
    void applyClipGpu();
    bool isValidProperty() const;
    bool isValidModel() const;
    bool isDestroy() const;
    int getType() const;  // the object's type (3: a driver)
    void setCalcCameraAlpha();
    unsigned int getMultiBindUniqId() const;
    bool isMultiBindWaiting() const;
    GF_ASSET_HANDLE* getAssetHandle() const;
    GF_OBJ_HANDLE* getTarget() const;
    void setUserData(GfObjUserData kind, unsigned long data);
    void* getUserData(GfObjUserData kind) const;
    int getBoneIdx(const char* bone);
    // a bone's world transform; false when the object has no such bone
    bool getBoneTransform(fw::Transform& transform, const char* bone);
    bool getBoneTransform(fw::Transform& transform, int bone);
    unsigned int getBdatId() const;
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies in GfObjAcc's unit
    // and its callers pass a GfObjAcc as this. What it does: returns getBdatId() (a tail call). Callers:
    // GfMenuGfObjAdapter::fn_7100340094 (hands it to GfDataBlade::fn_710024DD94), fn_71003601DC,
    // GfMenuObjTargetInfo::openOther.
    unsigned int fn_7100523B74() const;
    unsigned int getDriverId() const;  // the driver object's row (DataObjDriver)
    unsigned int getBladeId() const;  // the blade object's row (DataObjBlade)
    bool isEnemyBlade() const;
    unsigned int getEnArrangeId() const;  // SCOM_CHAR_DEAD::exec hands it to the quest tasks
    unsigned int getEnRscId() const;
    unsigned int getPcWeaponId() const;  // the driver weapon object's weapon row (DataObjPcWpn)
    bool isLoadedWaitOK() const;
    unsigned int getView() const;
    unsigned int getLayer() const;
    bool isLayerPause() const;
    void setCollisionChar(bool on);
    void setCollisionGround(bool on);
    void setExtMeshAlpha(unsigned int mesh, float alpha);
    int getExtMeshMax() const;
    int getExtMeshIdx(const char* name) const;
    const char* getExtMeshName(int mesh) const;
    const char* getDebugName() const;
    bool isBattle() const;
    void setEtcParam(int index, float value);
    int getEtcParamIndex(const char* name) const;
    bool isPartyObj() const;
    unsigned int getPartyID() const;
    bool isCollideModelClip() const;
    void setEnableCollideModelClip(bool on);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it lies at the end of
    // GfObjAcc's unit and reads this's object and bdat id. What it does: the extra access distance of the object: 4
    // for the type-6 object of row 0xE4D, the kind-0x3E gimmick's float at 0x58 for a gimmick object (type 8), else 0.
    // Callers: GfGameSearchObj::updateObj, gf::pc::isActiveRange (adds it to the access range).
    float fn_710052478C() const;

    GFOBJ_INFO* m_info;  // GfObjManager::getObjInfo's for the handle
    GfObj* m_obj;  // the GfObj constructor's argument
};
}  // namespace gf

#endif
