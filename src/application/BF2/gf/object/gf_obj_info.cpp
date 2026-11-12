#include "mm/Vec3.h"
#include "mm/mtl/FixedVector.h"
#include "gf/GfAppend.h"
#include "gf/GfObjInfo.h"
#include "classes/fw/ModelObject.h"
#include "classes/gf/GfComModel.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfObj.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfObjSetup.h"
#include "gf/GfVolumeFade.h"
#include "gf/GfObjFactory.h"
#include "gf/GfObjUtil.h"
#include "mm/mtl/IntrusivePtr.h"
#include "arc/CArcData.h"
#include "skd/DynamicsImporter.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfAssetManager.h"
#include "classes/gf/GfAssetResource.h"
#include "classes/gf/GfComDynamics.h"
#include "classes/gf/GfComIK.h"
#include "classes/gf/GfComTransform.h"
#include <math.h>

namespace gf {

void fn_7100544354(GfObj* obj, const mm::Vec3& pos, const mm::Vec3& rot) {
    GfComTransform* transform = obj->getComponent<GfComTransform>(0);
    GfComTransform::SetupInfo info;
    info.position = pos;
    mm::Vec3 half = mm::Vec3(rot) * 0.5f;
    float sx = ::sinf(half.x);
    float cx = ::cosf(half.x);
    float sy = ::sinf(half.y);
    float cy = ::cosf(half.y);
    float sz = ::sinf(half.z);
    float cz = ::cosf(half.z);
    info.rotation.x = sx * cy * cz - cx * sy * sz;
    info.rotation.y = cx * sy * cz + sx * cy * sz;
    info.rotation.z = cx * cy * sz - sx * sy * cz;
    info.rotation.w = cx * cy * cz + sx * sy * sz;
    info.frame_max = 2;
    info.childFrame = true;
    transform->setup(info);
}

void fn_71005444A0(GfObj* obj, const char* name, mm::mtl::IntrusivePtr<fw::ForceCalculator> force) {
    GF_ASSET_HANDLE* asset = GfObjUtil::getAssetHandle(obj->m_handle);
    GfComDynamics* dynamics = obj->getComponent<GfComDynamics>(8);
    GfComDynamics::SetupInfo info;
    info.colObj = nullptr;
    info.res = nullptr;
    info.level = 6;
    if (GfAssetResource* resource =
            GfAssetManager::getResource(asset, static_cast<GfFileIdx>(0x3B), static_cast<GfAssetType>(0))) {
        void* data = resource->getAssetData();
        if (name != nullptr) {
            arc::CArcData arc(data);
            data = arc.getFileAdr(name);
        }
        info.res = skd::DynamicsImporter::import(data);
        info.force = force;
    }
    dynamics->setup(info);
}

void fn_710054473C(GfObj* obj) {
    if (obj->findComponent<GfComModel>(1)->m_pose != nullptr) {
        GfComIK* ik = obj->getComponent<GfComIK>(3);
        DataParamAcc acc(obj->m_handle);
        ik->createBlowRotateIkSolver(acc.getRotateBone());
    }
}

GFOBJ_MOUNT::~GFOBJ_MOUNT() {
    m_appendInfo.clear();
}

GFOBJ_INFO::GFOBJ_INFO()
    : m_multiBindUniqId(0), m_view(0), m_layer(4), m_state(0), m_handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)),
      m_assetHandle(reinterpret_cast<GF_ASSET_HANDLE*>(-1)), m_obj(nullptr), m_updatableIndex(0), m_updatable(nullptr),
      m_setup(nullptr), m_flags(), m_reserved(0), m_dispOff(0), m_subHandle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)),
      m_owner(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), m_property(nullptr), m_modelScale(mm::Vec3::unit),
      m_attachIndex(-1), m_volumeFade(nullptr) {
    {
        GFOBJ_MOUNT mount;
        for (int i = 0; i < 4; i++) {
            m_mounts[i] = mount;
        }
    }
    for (int i = 0; i < 3; i++) {
        m_userData[i] = 0;
    }
    m_transform.position = mm::Vec3::zero;
    m_transform.rotation = mm::Quat::identity;
}

GFOBJ_INFO::~GFOBJ_INFO() {
    if (m_volumeFade != nullptr) {
        delete m_volumeFade;
        m_volumeFade = nullptr;
    }
    m_updatableIndex = 0;
    m_updatable = nullptr;
    if (m_setup != nullptr) {
        delete m_setup;
        m_setup = nullptr;
    }
    if (m_property != nullptr) {
        delete m_property;
        m_property = nullptr;
    }
    m_multiBindUniqId = 0;
    m_handle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    m_assetHandle = reinterpret_cast<GF_ASSET_HANDLE*>(-1);
    m_obj = nullptr;
    for (int i = 0; i < 3; i++) {
        m_userData[i] = 0;
    }
    m_subHandle = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
    m_owner = reinterpret_cast<GF_OBJ_HANDLE*>(-1);
}

void GFOBJ_INFO::createVolumeFade(GfComModel* model) {
    if (model == nullptr || model->m_model == nullptr || model->m_model->getInterface() == nullptr) {
        return;
    }
    if (m_volumeFade != nullptr) {
        delete m_volumeFade;
        m_volumeFade = nullptr;
    }
#line 91
    m_volumeFade = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8)
        GfVolumeFade(static_cast<GfObj*>(model->m_owner)->m_handle, model->m_model->getInterface());
}

}  // namespace gf
