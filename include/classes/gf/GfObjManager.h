#ifndef CLASSES_GF_GFOBJMANAGER_H
#define CLASSES_GF_GFOBJMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/gf/IGfObjListener.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSetupParam; }
namespace fw { class UpdateInfo; }
namespace gf { class GfObjManager; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GFOBJ_INFO; }

namespace gf {
// table 0x7100B69FF8
class GfObjManager : public ::mm::mtl::PtrSingleton< ::gf::GfObjManager>, public ::gf::IGfEvent {
public:
    static void build(const GfSetupParam& param);
    static void destroy();
    void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    virtual ~GfObjManager();  // slot 0
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 2
    void addDestroyObj(GF_OBJ_HANDLE* handle, bool flag);
    static GFOBJ_INFO* getObjInfo(GF_OBJ_HANDLE* handle);
    // has the object's parameters (its alpha) applied again (GfObjAcc::setAlpha asks once one changed)
    void addApplyParam(GF_OBJ_HANDLE* handle);
    // while set, objects' components are not updated (GfObjUtil::applyExecUpdate)
    bool isSuspendUpdate() const;
    // whether a multi-bind id is still valid for the handle (GfObjAcc::isMultiBindWaiting)
    bool isValidMultiBind(GF_OBJ_HANDLE* handle, unsigned int id) const;
    // a listener called for the objects' events, and its removal
    static void addListener(IGfObjListener* listener, IGfObjListener::OBJEVT evt);
    static void removeListener(IGfObjListener* listener);
    bool hasReloadObjForDebug();
};
}  // namespace gf

#endif
