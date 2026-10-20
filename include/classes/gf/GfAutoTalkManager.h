#ifndef CLASSES_GF_GFAUTOTALKMANAGER_H
#define CLASSES_GF_GFAUTOTALKMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfAutoTalkManager; }
namespace gf { enum RELOAD_BDAT : int; }

namespace gf {
// table 0x7100B53838
class GfAutoTalkManager : public ::mm::mtl::PtrSingleton< ::gf::GfAutoTalkManager>, public ::gf::IGfEvent {
public:
    virtual ~GfAutoTalkManager();  // slot 0
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int);  // slot 2
};
}  // namespace gf

#endif
