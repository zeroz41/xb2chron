#ifndef CLASSES_GF_GFMAPMANAGER_H
#define CLASSES_GF_GFMAPMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfMapManager; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gf {
// a base of gf::GfMapManager no evidence names yet
class TUnk_B595B0 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// table 0x7100B59580; base at 0x8 unknown (TUnk_B595B0)
class GfMapManager : public ::mm::mtl::PtrSingleton< ::gf::GfMapManager>, public TUnk_B595B0, public ::gf::IGfEvent {
public:
    virtual ~GfMapManager();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 3
};
}  // namespace gf

#endif
