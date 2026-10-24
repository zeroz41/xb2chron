#ifndef GF_GFOBJINFO_H
#define GF_GFOBJINFO_H

#include "mm/Quat.h"
#include "mm/Vec3.h"
#include "mm/mtl/Bitflag.h"
#include "mm/mtl/FixStr.h"
#include "fw/Transform.h"
#include "gf/GfAppend.h"

namespace fw { class UpdatableObject; }
namespace gf { class GF_ASSET_HANDLE; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GF_MOUNT_HANDLE; }
namespace gf { class GfComModel; }
namespace gf { class GfObj; }
namespace gf { class GfObjProperty; }
namespace gf { class GfObjSetup; }
namespace gf { class GfVolumeFade; }

namespace gf {
// no table: what an object has mounted at one of its GFATTACH points (GfObjUtil::getMountHandle,
// getAppendInfo and getAppend index GFOBJ_INFO's four by it)
class GFOBJ_MOUNT {
public:
    // out of line in 1.0.0; 3.0.1 keeps no copy
    GFOBJ_MOUNT() : m_handle(reinterpret_cast<GF_MOUNT_HANDLE*>(-1)), m_appendIndex(-1) {}
    ~GFOBJ_MOUNT();

    // GfObjUtil::getMountHandle's GF_MOUNT_HANDLE; GfMountManager::addMountHandle stores it
    GF_MOUNT_HANDLE* m_handle;
    // which of the current list's appends GfObjUtil::getAppend returns, -1 for none (the name is not the original's)
    int m_appendIndex;
    GfAppendInfo m_appendInfo;  // GfObjUtil::getAppendInfo
};

// no table: what GfObjManager keeps for one object (getObjInfo looks it up by the object's handle; its pool's
// elements are 0x420 long)
class GFOBJ_INFO {
public:
    GFOBJ_INFO();
    ~GFOBJ_INFO();
    void createVolumeFade(GfComModel* model);

    unsigned short m_multiBindUniqId;  // GfObjAcc::getMultiBindUniqId
    unsigned short m_view;             // GfObjAcc::getView
    // the layer GfObjManager::createGfObj gives the object, 4 at first as GfObjAcc::getLayer's default (the name is
    // not the original's)
    unsigned short m_layer;
    // GfObjManager::setStateLoading sets 1, setStateUpdate 2, setStateDestroy 3 (the name is not the original's)
    unsigned short m_state;
    GF_OBJ_HANDLE* m_handle;          // GfObjAcc::getHandle
    GF_ASSET_HANDLE* m_assetHandle;   // GfObjAcc::getAssetHandle
    GfObj* m_obj;                     // GfObjAcc's object
    // the object's own fw::HandlePtr<fw::UpdatableObject>, which createGfObj copies (the names are not the
    // original's)
    unsigned int m_updatableIndex;
    fw::UpdatableObject* m_updatable;
    // the object's setup; the destructor deletes it (the name is not the original's)
    GfObjSetup* m_setup;
    mm::mtl::Bitflag<64> m_flags;  // GfObjUtil::setFlag / testFlag
    unsigned long m_reserved;  // cleared with the flags; its use is unknown (the name is not the original's)
    // OBJDISP bits that hide the object: GfObjAcc::isDisp is true while none of the asked ones is set (the name is
    // not the original's)
    unsigned int m_dispOff;
    // the object's place without a transform component: GfObjAcc::getWorldTransform returns it (the name is not
    // the original's)
    fw::Transform m_transform;
    unsigned long m_userData[3];  // by GfObjUserData: GfObjAcc::setUserData / getUserData
    // a handle, -1 when none (the name is not the original's)
    GF_OBJ_HANDLE* m_subHandle;
    GF_OBJ_HANDLE* m_owner;          // GfObjUtil::setOwner / getOwner
    GfObjProperty* m_property;       // GfObjManager::createGfObjProperty
    mm::Vec3 m_modelScale;           // GfObjAcc::getModelScaleXYZ
    int m_attachIndex;  // -1 at first (the name is not the original's)
    GFOBJ_MOUNT m_mounts[4];         // by GFATTACH
    GfVolumeFade* m_volumeFade;      // createVolumeFade's (GfObjUtil::getVolumeFade)
    mm::mtl::FixStr<32> m_mountBoneName;  // GfObjUtil::mountToBone's bone (the name is not the original's)
    mm::mtl::FixStr<16> m_modelBaseName;  // GfObjUtil::getModelBaseName
};
}  // namespace gf

#endif
