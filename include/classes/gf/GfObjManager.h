#ifndef CLASSES_GF_GFOBJMANAGER_H
#define CLASSES_GF_GFOBJMANAGER_H

#include "classes/gf/IGfEvent.h"

namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace gf {
// a base of gf::GfObjManager no evidence names yet
class TUnk_B69FF8 {
public:
    virtual ~TUnk_B69FF8();
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) = 0;
};
// table 0x7100B69FF8; base at 0x0 unknown (TUnk_B69FF8)
class GfObjManager : public TUnk_B69FF8, public ::gf::IGfEvent {
public:
    virtual ~GfObjManager();  // slot 0
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 2
};
}  // namespace gf

#endif
