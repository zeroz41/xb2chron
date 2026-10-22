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

namespace gf {

GFOBJ_MOUNT::~GFOBJ_MOUNT() {
    m_appendInfo.clear();
}

// GFOBJ_INFO::GFOBJ_INFO() (0x710054490C) is identical but emits GfAppendInfo's implicit copy assignment
// (0x7100544C08), which is not yet: both wait (see the worker's pending copy)

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
