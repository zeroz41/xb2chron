#ifndef CLASSES_GF_GFFOBJMANAGER_H
#define CLASSES_GF_GFFOBJMANAGER_H

#include "classes/gf/IGfEvent.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { enum GEV : int; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gf {
// a base of gf::GfFobjManager no evidence names yet
class TUnk_B52978 {
public:
    virtual ~TUnk_B52978();
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
    virtual void gevPlayEvent(gf::GEV, unsigned int) = 0;
    virtual void gevGameObjLeave(gf::GF_OBJ_HANDLE*) = 0;
};
// a base of gf::GfFobjManager no evidence names yet
class TUnk_B529B0 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// table 0x7100B52978; base at 0x0 unknown (TUnk_B52978), base at 0x8 unknown (TUnk_B529B0)
class GfFobjManager : public TUnk_B52978, public TUnk_B529B0, public ::gf::IGfEvent {
public:
    virtual ~GfFobjManager();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 3
    virtual void gevGameObjLeave(gf::GF_OBJ_HANDLE*);  // slot 4
};
}  // namespace gf

#endif
