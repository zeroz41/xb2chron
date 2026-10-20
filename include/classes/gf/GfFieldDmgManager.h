#ifndef CLASSES_GF_GFFIELDDMGMANAGER_H
#define CLASSES_GF_GFFIELDDMGMANAGER_H

#include "classes/gf/IGfEvent.h"

namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace gf {
// a base of gf::GfFieldDmgManager no evidence names yet
class TUnk_B514E8 {
public:
    virtual ~TUnk_B514E8();
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&) = 0;
};
// table 0x7100B514E8; base at 0x0 unknown (TUnk_B514E8)
class GfFieldDmgManager : public TUnk_B514E8, public ::gf::IGfEvent {
public:
    virtual ~GfFieldDmgManager();  // slot 0
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 2
};
}  // namespace gf

#endif
