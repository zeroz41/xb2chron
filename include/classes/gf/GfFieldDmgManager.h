#ifndef CLASSES_GF_GFFIELDDMGMANAGER_H
#define CLASSES_GF_GFFIELDDMGMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfFieldDmgManager; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace gf {
// table 0x7100B514E8
class GfFieldDmgManager : public ::mm::mtl::PtrSingleton< ::gf::GfFieldDmgManager>, public ::gf::IGfEvent {
public:
    virtual ~GfFieldDmgManager();  // slot 0
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 2
};
}  // namespace gf

#endif
