#include "classes/ml/fixed_size_alloc_inside.h"
#include "classes/gf/GfObjManager.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfObjAcc.h"
#include "gf/GfObjUtil.h"
#include "classes/gf/GfAssetMultiBind.h"
#include "classes/gf/GfObjProperty.h"
#include "classes/gf/GfAssetManager.h"
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

void GfObjManager::applyModelLayerPauseSpeed() {
    bool request = false;
    for (unsigned int layer = 0; layer < 32; ++layer) {
        if (GfObjLayerSpeed::isRequest(layer)) {
            request = true;
            break;
        }
    }
    if (!request) {
        return;
    }
    for (HandleList2048::iterator it = m_updateObj.begin(); it != m_updateObj.end(); ++it) {
        GfObjAcc acc(*it);
        if (GfObjLayerSpeed::isRequest(acc.getLayer())) {
            acc.setFrameSpeed(GfObjLayerSpeed::getSpeed(acc.getLayer()));
        }
    }
}

void GfObjManager::postUpdate(const fw::UpdateInfo& info) {
    updateLayerPauseObjects(info);
    updateFirstObjects(info);
    updateChangeParamObjects(info);
    GfObjLayerSpeed::cleanup();
}

void GfObjManager::updateFirstObjects(const fw::UpdateInfo&) {
    for (HandleList::iterator it = m_firstObj.begin(); it != m_firstObj.end(); ++it) {
        GFOBJ_INFO* info = getObjInfo(*it);
        if (info != nullptr) {
            info->m_flags.set(19, true);
        }
    }
    m_firstObj.clear();
}

GFOBJ_INFO* GfObjManager::getObjInfo(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = nullptr;
    if (handle != reinterpret_cast<GF_OBJ_HANDLE*>(-1) && s_pThis != nullptr) {
        unsigned int slot = static_cast<unsigned int>(reinterpret_cast<unsigned long>(handle)) & 0xFFF;
        GFOBJ_INFO* slotInfo = &s_pThis->m_objInfo[slot];
        if (s_pThis->m_objInfo.isUsed(slot)) {
            info = slotInfo->m_handle == handle ? slotInfo : nullptr;
        }
    }
    return info;
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

void GfObjManager::createGfObjProperty(GF_OBJ_HANDLE* handle) {
    GFOBJ_INFO* info = getObjInfo(handle);
    if (info != nullptr && info->m_property == nullptr) {
        info->m_property = GfObjProperty::create(handle);
    }
}

void GfObjManager::addHandle(GF_OBJ_HANDLE* handle) {
    setStateLoading(handle);
}

void GfObjManager::setStateLoading(GF_OBJ_HANDLE* handle) {
    setObjState(handle, 1);
    if (m_loadingObj.find(handle) != m_loadingObj.end()) {
        return;
    }
    m_loadingObj.push_back(handle);
    GfAssetManager::setupLoadStart(GfObjUtil::getAssetHandle(handle));
}

bool GfObjManager::isFinishLoadState(GfObjAcc& acc, bool flag) {
    GF_OBJ_HANDLE* handle = acc.getHandle();
    unsigned int id = acc.getMultiBindUniqId();
    if (id != 0) {
        for (mm::mtl::FixedList<GfAssetMultiBind*, 64>::iterator it = m_multiBind.begin(); it != m_multiBind.end(); ++it) {
            if ((*it)->m_id == id) {
                (*it)->loadedAsset(handle);
                break;
            }
        }
    }
    if (!isValidMultiBind(acc.getHandle(), acc.getMultiBindUniqId()) && !flag) {
        return false;
    }
    if (!acc.isLoadedWaitOK()) {
        return false;
    }
    if (acc.isLayerPause()) {
        acc.setDisp(OBJDISP(4), false);
        acc.applyDisp();
    }
    return true;
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

bool GfObjManager::getWaitingMultiBindObj(ResultList& list, unsigned int id) const {
    GfObjManager* self = const_cast<GfObjManager*>(this);
    for (mm::mtl::FixedList<GfAssetMultiBind*, 64>::iterator it = self->m_multiBind.begin(); it != self->m_multiBind.end(); ++it) {
        GfAssetMultiBind* bind = *it;
        if (bind->m_id == id) {
            for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 32>::iterator obj = bind->m_bindObj.begin(); obj != bind->m_bindObj.end(); ++obj) {
                list.push_back(*obj);
            }
            return !list.empty();
        }
    }
    return false;
}

void GfObjManager::addApplyParamObj(GfObj* obj) {
    if (obj == nullptr) {
        return;
    }
    if (m_applyParamObj.find(obj->m_info->m_handle) != m_applyParamObj.end()) {
        return;
    }
    m_applyParamObj.push_back(obj->m_info->m_handle);
    mm::mtl::IntrusiveList<fw::UpdatableObject>& children = obj->m_children;
    for (mm::mtl::IntrusiveList<fw::UpdatableObject>::iterator it = children.begin(); it != children.end(); ++it) {
        fw::UpdatableObject* child = (*it).m_handle.get();
        if (child != nullptr && child->getRTTI()->isKindOf(&GfObj::m_rtti)) {
            addApplyParamObj(static_cast<GfObj*>(child));
        }
    }
}

void GfObjManager::addApplyParam(GF_OBJ_HANDLE* handle) {
    addApplyParamObj(GfObjUtil::getObj(handle));
}

bool GfObjManager::isSuspendUpdate() const {
    return m_suspendUpdate;
}

void GfObjManager::gevMapjump(GEV gev, const MapjumpCallbackInfo&) {
    if (gev == 2) {
        m_suspendUpdate = true;
        for (HandleList::iterator it = m_loadingObj.begin(); it != m_loadingObj.end(); ++it) {
            GfObjUtil::applyExecUpdate(*it);
        }
        for (HandleList2048::iterator it = m_updateObj.begin(); it != m_updateObj.end(); ++it) {
            GfObjUtil::applyExecUpdate(*it);
        }
    } else if (gev == 6) {
        m_suspendUpdate = false;
        for (HandleList::iterator it = m_loadingObj.begin(); it != m_loadingObj.end(); ++it) {
            GfObjUtil::applyExecUpdate(*it);
        }
        for (HandleList2048::iterator it = m_updateObj.begin(); it != m_updateObj.end(); ++it) {
            GfObjUtil::applyExecUpdate(*it);
        }
    }
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

GfObjManager::~GfObjManager() {
    s_pThis = nullptr;
}

void GfObjManager::requestDestroyAll() {
    for (HandleList::iterator it = m_loadingObj.begin(); it != m_loadingObj.end(); ++it) {
        GfObjUtil::destroy(*it);
    }
    for (HandleList2048::iterator it = m_updateObj.begin(); it != m_updateObj.end(); ++it) {
        GfObjUtil::destroy(*it);
    }
}

bool GfObjManager::isValidMultiBind(GF_OBJ_HANDLE*, unsigned int id) const {
    if (id == 0) {
        return true;
    }
    GfObjManager* self = const_cast<GfObjManager*>(this);
    for (mm::mtl::FixedList<GfAssetMultiBind*, 64>::iterator it = self->m_multiBind.begin(); it != self->m_multiBind.end(); ++it) {
        if ((*it)->m_id == id) {
            return (*it)->isValid();
        }
    }
    return false;
}

void GfObjManager::setStateDestroy(GF_OBJ_HANDLE* handle) {
    setObjState(handle, 3);
    m_destroyObj.push_back(handle);
}

void GfObjManager::addListener(IGfObjListener* listener, IGfObjListener::OBJEVT evt) {
    ObjListener entry;
    entry.m_listener = listener;
    entry.m_evt = evt;
    m_aListenerObj.push_back(entry);
}

void GfObjManager::destroyLayerObj(unsigned int layer) {
    for (HandleList::iterator it = m_loadingObj.begin(); it != m_loadingObj.end(); ++it) {
        if (GfObjUtil::getObjLayer(*it) == layer) {
            GfObjUtil::destroy(*it);
        }
    }
    for (HandleList2048::iterator it = m_updateObj.begin(); it != m_updateObj.end(); ++it) {
        if (GfObjUtil::getObjLayer(*it) == layer) {
            GfObjUtil::destroy(*it);
        }
    }
}

GfAssetMultiBind* GfObjManager::getAssetMultiBind(unsigned int id) const {
    GfObjManager* self = const_cast<GfObjManager*>(this);
    for (mm::mtl::FixedList<GfAssetMultiBind*, 64>::iterator it = self->m_multiBind.begin(); it != self->m_multiBind.end(); ++it) {
        if ((*it)->m_id == id) {
            return *it;
        }
    }
    return nullptr;
}

void GfObjManager::setMultiBind(GF_OBJ_HANDLE* handle, unsigned int id, unsigned int objNum, bool flag) {
    GFOBJ_INFO* info = getObjInfo(handle);
    GfAssetMultiBind* bind = getAssetMultiBind(id);
    if (bind == nullptr) {
#line 1235
        bind = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfAssetMultiBind(id, flag);
        m_multiBind.push_back(bind);
    }
    bind->m_objNum = objNum;
    bind->bind(handle);
    info->m_multiBindUniqId = id;
}

const mm::mtl::FixedList<GF_OBJ_HANDLE*, 32>* GfObjManager::getMultiBindList(GF_OBJ_HANDLE* handle) const {
    GFOBJ_INFO* info = getObjInfo(handle);
    if (info->m_multiBindUniqId != 0) {
        GfObjManager* self = const_cast<GfObjManager*>(this);
        for (mm::mtl::FixedList<GfAssetMultiBind*, 64>::iterator it = self->m_multiBind.begin(); it != self->m_multiBind.end(); ++it) {
            GfAssetMultiBind* bind = *it;
            if (bind->m_id == info->m_multiBindUniqId) {
                return bind->m_flag ? nullptr : &bind->m_bindObj;
            }
        }
    }
    return nullptr;
}

void GfObjManager::addFollowObj(GF_OBJ_HANDLE* handle) {
    if (m_followObj.find(handle) == m_followObj.end()) {
        m_followObj.push_back(handle);
    }
}

void GfObjManager::addDestroyObj(GF_OBJ_HANDLE* handle, bool flag) {
    GfObjAcc acc(handle);
    if (acc.m_obj == nullptr) {
        return;
    }
    if (m_destroyRequestObj.find(handle) != m_destroyRequestObj.end()) {
        return;
    }
    if (m_destroyObj.find(handle) != m_destroyObj.end()) {
        return;
    }
    m_destroyRequestObj.push_back(handle);
    GfAssetManager::isReload(acc.getAssetHandle());
    if (!acc.isRebuild()) {
        checkDeleteFollowObj(handle);
    }
    if (flag) {
        GfObjAcc bound(handle);
        if (bound.m_obj != nullptr) {
            for (mm::mtl::FixedList<GfAssetMultiBind*, 64>::iterator it = m_multiBind.begin(); it != m_multiBind.end(); ++it) {
                GfAssetMultiBind* bind = *it;
                if (bind->m_id == bound.getMultiBindUniqId()) {
                    if (bind != nullptr && !bind->m_flag) {
                        for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 32>::iterator obj = bind->m_bindObj.begin(); obj != bind->m_bindObj.end(); ++obj) {
                            GfObjUtil::destroy(*obj);
                        }
                    }
                    return;
                }
            }
        }
    }
}

void GfObjManager::checkDeleteFollowObj(GF_OBJ_HANDLE* handle) {
    GfObjAcc acc(handle);
    GFOBJ_INFO* info = getObjInfo(handle);
    bool reload = GfAssetManager::isReload(acc.getAssetHandle());
    for (mm::mtl::FixedList<GF_OBJ_HANDLE*, 256>::iterator it = m_followObj.begin(); it != m_followObj.end(); ++it) {
        GFOBJ_INFO* follow = getObjInfo(*it);
        if (follow->m_subHandle == handle && info->m_obj != GfObjUtil::getParentObj(follow->m_obj) && !reload) {
            GfObjUtil::destroy(*it);
        }
    }
}

void GfObjManager::setStateUpdate(GF_OBJ_HANDLE* handle) {
    setObjState(handle, 2);
    m_updateObj.push_back(handle);
    m_firstObj.push_back(handle);
}

bool GfObjManager::isExistLayerObj(unsigned int layer) const {
    GfObjManager* self = const_cast<GfObjManager*>(this);
    for (HandleList::iterator it = self->m_loadingObj.begin(); it != self->m_loadingObj.end(); ++it) {
        if (GfObjUtil::getObjLayer(*it) == layer) {
            return true;
        }
    }
    for (HandleList2048::iterator it = self->m_updateObj.begin(); it != self->m_updateObj.end(); ++it) {
        if (GfObjUtil::getObjLayer(*it) == layer) {
            return true;
        }
    }
    for (HandleList::iterator it = self->m_destroyObj.begin(); it != self->m_destroyObj.end(); ++it) {
        if (GfObjUtil::getObjLayer(*it) == layer) {
            return true;
        }
    }
    return false;
}

bool GfObjManager::isExistGfObj(bool flag) const {
    if (!flag) {
        return !m_destroyObj.empty() || !m_loadingObj.empty() || !m_updateObj.empty();
    }
    GfObjManager* self = const_cast<GfObjManager*>(this);
    for (HandleList::iterator it = self->m_loadingObj.begin(); it != self->m_loadingObj.end(); ++it) {
        GfObjAcc acc(*it);
        if (acc.getType() != 1) {
            return true;
        }
    }
    for (HandleList2048::iterator it = self->m_updateObj.begin(); it != self->m_updateObj.end(); ++it) {
        GfObjAcc acc(*it);
        if (acc.getType() != 1) {
            return true;
        }
    }
    for (HandleList::iterator it = self->m_destroyObj.begin(); it != self->m_destroyObj.end(); ++it) {
        GfObjAcc acc(*it);
        if (acc.getType() != 1) {
            return true;
        }
    }
    return false;
}

}  // namespace gf
