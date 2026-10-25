#include "classes/ml/fixed_size_alloc_inside.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include <string.h>

namespace gf {

// each object type's capacity (getGfObjCapacity); -1 for the types without one
// Proposed name, not the original's: the symbols leave it unnamed (lbl_71009C5F48)
static const int s_objCapacity[16] = {-1, -1, -1, -1, -1, 0x28, 0x20, 0x40, -1, -1, -1, -1, -1, -1, -1, -1};

GfObjManager* GfObjManager::s_pThis;
mm::mtl::FixedList<GfObjManager::ObjListener, 256> GfObjManager::m_aListenerObj;

GfObjManager::GfObjManager(const GfSetupParam& param) : m_initialized(false), pad_14(0) {
    initialize(param);
}

void GfObjManager::build(const GfSetupParam& param) {
#line 81
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfObjManager(param);
}

void GfObjManager::destroy() {
    GfObjManager* self = s_pThis;
    self->finalize();
    if (s_pThis != nullptr) {
        delete s_pThis;
        s_pThis = nullptr;
    }
    GfSleep(10);
}

void GfObjManager::update(const fw::UpdateInfo& info) {
    checkLoadingAndCreate(reinterpret_cast<GF_OBJ_HANDLE*>(-1));
    checkTerminate();
    applyModelLayerPauseSpeed();
}

int GfObjManager::getGfObjCapacity(unsigned int type) {
    unsigned long index = type;
    if (index > 15) {
        return -1;
    }
    if (index == 7 && get() != nullptr && !GfGameManager::isPlayEvent()) {
        return get()->m_capacityOutOfEvent;
    }
    return s_objCapacity[index];
}

int GfObjManager::getObjectNum(unsigned int type) {
    return s_pThis->m_objectNum[type];
}

void GfObjManager::addHandle(GF_OBJ_HANDLE* handle) {
    setStateLoading(handle);
}

const GfObjManager::HandleList& GfObjManager::getLoadingObj() const {
    return m_loadingObj;
}

const GfObjManager::HandleList& GfObjManager::getDestroyObj() const {
    return m_destroyObj;
}

bool GfObjManager::hasReloadObjForDebug() {
    return false;
}

void GfObjManager::addApplyParam(GF_OBJ_HANDLE* handle) {
    addApplyParamObj(GfObjUtil::getObj(handle));
}

bool GfObjManager::isSuspendUpdate() const {
    return m_suspendUpdate;
}

void GfObjManager::enterStayObject(GF_OBJ_HANDLE* handle) {
    if (handle == reinterpret_cast<GF_OBJ_HANDLE*>(-1)) {
        return;
    }
    GfObjAcc acc(handle);
    if (acc.testFlag(8)) {
        acc.setFlag(9, true);
        s_pThis->checkLoadingAndCreate(handle);
    }
}

}  // namespace gf
