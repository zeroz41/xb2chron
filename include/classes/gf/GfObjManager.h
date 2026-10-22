#ifndef CLASSES_GF_GFOBJMANAGER_H
#define CLASSES_GF_GFOBJMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfObjManager; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }
namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GFOBJ_INFO; }

namespace gf {
// table 0x7100B69FF8
class GfObjManager : public ::mm::mtl::PtrSingleton< ::gf::GfObjManager>, public ::gf::IGfEvent {
public:
    virtual ~GfObjManager();  // slot 0
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 2
    void addDestroyObj(GF_OBJ_HANDLE* handle, bool flag);
    static GFOBJ_INFO* getObjInfo(GF_OBJ_HANDLE* handle);
};
}  // namespace gf

#endif
