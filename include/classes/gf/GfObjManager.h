#ifndef CLASSES_GF_GFOBJMANAGER_H
#define CLASSES_GF_GFOBJMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/gf/IGfObjListener.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ml/fixed_size_alloc_inside.h"
#include "gf/GfObjInfo.h"
#include "mm/mtl/FixedList.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfInfo.h"
#include "classes/gf/GfObj.h"
#include <string.h>

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace gf { class GfObjManager; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfAssetMultiBind; }
namespace gf { class GfInitParam; }
namespace gf { class GfObj; }
namespace gf { class GfObjAcc; }

namespace gf {
// table 0x7100B69FF8; 0x484A30 bytes (build's allocation). The lists' and fields' names are not the original's
// unless a comment says otherwise: they are named by the functions that fill or read them.
class GfObjManager : public ::mm::mtl::PtrSingleton< ::gf::GfObjManager>, public ::gf::IGfEvent {
public:
    typedef mm::mtl::FixedList<GF_OBJ_HANDLE*, 4096> HandleList;
    typedef mm::mtl::FixedList<GF_OBJ_HANDLE*, 2048> HandleList2048;
    typedef mm::mtl::FixedList<GF_OBJ_HANDLE*, 768> ResultList;
    // a listener addListener registers, and the event it hears (the field names are not the original's)
    struct ObjListener {
        IGfObjListener* m_listener;
        IGfObjListener::OBJEVT m_evt;
    };

    GfObjManager(const GfSetupParam& param);
    virtual ~GfObjManager();  // slot 0
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 2

    // what the constructor does (the name is not the original's: 1.0.0 keeps finalize, which undoes it; the
    // constructor hands it the setup parameters, which build passes on although nothing reads them)
    void initialize(const GfSetupParam& param) {
        m_suspendUpdate = false;
        m_capacityOutOfEvent = 0x28;
        s_pThis = this;
        memset(pad_4849C0, 0xFF, sizeof(pad_4849C0));
        memset(m_objectNum, 0, sizeof(m_objectNum));
        GfEvent::addEventCallback(this);
        GfObjLayerSpeed::initialize();
        m_initialized = true;
    }
    static void build(const GfSetupParam& param);
    static void destroy();
    // 1.0.0's: what destroy does before deleting the manager (3.0.1 inlines it)
    void finalize() {
        requestDestroyAll();
        while (!isEmptyObj()) {
            GfSleep(1);
        }
        GfObjLayerSpeed::finalize();
        GfEvent::removeEventCallback(this);
        m_initialized = false;
    }
    // 1.0.0's: no object loading, updating, destroying or following
    bool isEmptyObj() const {
        return m_loadingObj.empty() && m_updateObj.empty() && m_destroyObj.empty() && m_followObj.empty();
    }
    void requestDestroyAll();
    void update(const fw::UpdateInfo& info);
    void checkLoadingAndCreate(GF_OBJ_HANDLE* handle);
    void checkTerminate();
    void applyModelLayerPauseSpeed();
    void postUpdate(const fw::UpdateInfo& info);
    void updateLayerPauseObjects(const fw::UpdateInfo& info);
    void updateFirstObjects(const fw::UpdateInfo& info);
    void updateChangeParamObjects(const fw::UpdateInfo& info);
    static GFOBJ_INFO* getObjInfo(GF_OBJ_HANDLE* handle);
    GF_OBJ_HANDLE* createGfObj(unsigned int type, const GfInitParam& param);
    static int getGfObjCapacity(unsigned int type);
    static int getObjectNum(unsigned int type);
    void createGfObjProperty(GF_OBJ_HANDLE* handle);
    void addHandle(GF_OBJ_HANDLE* handle);
    void setStateLoading(GF_OBJ_HANDLE* handle);
    bool isFinishLoadState(GfObjAcc& acc, bool flag);
    // whether a multi-bind id is still valid for the handle (GfObjAcc::isMultiBindWaiting)
    bool isValidMultiBind(GF_OBJ_HANDLE* handle, unsigned int id) const;
    void setStateDestroy(GF_OBJ_HANDLE* handle);
    // the handle's info (its pool slot, without the in-use test) set to state (setStateLoading 1, setStateUpdate
    // 2, setStateDestroy 3 inline it) (the name is not the original's)
    static void setObjState(GF_OBJ_HANDLE* handle, unsigned short state) {
        GFOBJ_INFO* info = &s_pThis->m_objInfo.m_pData[reinterpret_cast<unsigned long>(handle) & 0xFFF];
        info = info->m_handle == handle ? info : nullptr;
        info->m_state = state;
    }
    void setStateUpdate(GF_OBJ_HANDLE* handle);
    void callGfObjListener(IGfObjListener::OBJEVT evt, GF_OBJ_HANDLE* handle);
    // a listener called for the objects' events, and its removal
    static void addListener(IGfObjListener* listener, IGfObjListener::OBJEVT evt);
    static void removeListener(IGfObjListener* listener);
    bool isExistGfObj(bool flag) const;
    bool isExistLayerObj(unsigned int layer) const;
    const HandleList& getLoadingObj() const;
    const HandleList& getDestroyObj() const;
    GF_OBJ_HANDLE* getExistFixedObj(int index) const;
    void destroyAllObj(bool flag);
    void destroyLayerObj(unsigned int layer);
    bool hasReloadObjForDebug();
    // the bind id's bound objects added to list; false when no bind has the id or the list stays empty
    bool getWaitingMultiBindObj(ResultList& list, unsigned int id) const;
    GfAssetMultiBind* getAssetMultiBind(unsigned int id) const;
    void setMultiBind(GF_OBJ_HANDLE* handle, unsigned int a, unsigned int b, bool flag);
    // the objects bound with the handle's object (its multi-bind id's), nullptr when none or the bind's flag is set
    const mm::mtl::FixedList<GF_OBJ_HANDLE*, 32>* getMultiBindList(GF_OBJ_HANDLE* handle) const;
    void addFollowObj(GF_OBJ_HANDLE* handle);
    void addDestroyObj(GF_OBJ_HANDLE* handle, bool flag);
    void checkDeleteFollowObj(GF_OBJ_HANDLE* handle);
    // the followed objects whose GFOBJ_INFO::m_subHandle is handle, added to list; whether the list holds any
    bool getFollowObj(ResultList& list, GF_OBJ_HANDLE* handle);
    void addApplyParamObj(GfObj* obj);
    // has the object's parameters (its alpha) applied again (GfObjAcc::setAlpha asks once one changed)
    void addApplyParam(GF_OBJ_HANDLE* handle);
    // while set, objects' components are not updated (GfObjUtil::applyExecUpdate)
    bool isSuspendUpdate() const;
    static void enterStayObject(GF_OBJ_HANDLE* handle);

    static GfObjManager* s_pThis;
    static mm::mtl::FixedList<ObjListener, 256> m_aListenerObj;

    bool m_initialized;  // 1.0.0's isInitialized reads it
    int pad_14;
    ml::fixed_size_alloc_inside<GFOBJ_INFO, 4096> m_objInfo;  // getObjInfo
    HandleList m_loadingObj;            // getLoadingObj, setStateLoading
    HandleList2048 m_updateObj;         // setStateUpdate
    HandleList m_firstObj;              // updateFirstObjects
    HandleList m_destroyObj;            // getDestroyObj, setStateDestroy
    HandleList m_layerPauseObj;         // updateLayerPauseObjects
    HandleList2048 m_destroyRequestObj; // addDestroyObj
    HandleList2048 m_applyParamObj;     // addApplyParamObj, updateChangeParamObjects
    mm::mtl::FixedList<GF_OBJ_HANDLE*, 256> m_followObj;  // addFollowObj
    short m_objectNum[16];              // getObjectNum
    mm::mtl::FixedList<GfAssetMultiBind*, 64> m_multiBind;  // getAssetMultiBind
    unsigned char pad_4849C0[0x68];     // all 0xFF at first
    bool m_suspendUpdate;               // isSuspendUpdate
    int m_capacityOutOfEvent;           // getGfObjCapacity's capacity of type 7 out of events (0x28)
};
}  // namespace gf

#endif
