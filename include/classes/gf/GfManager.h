#ifndef CLASSES_GF_GFMANAGER_H
#define CLASSES_GF_GFMANAGER_H

#include "classes/fw/IPauseTrigger.h"
#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfManager; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B59268
class GfManager : public ::mm::mtl::PtrSingleton< ::gf::GfManager>, public ::fw::IPauseTrigger, public ::gf::IGfEvent {
public:
    virtual ~GfManager();  // slot 0
    virtual void updatePauseCallback();  // slot 2
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 3
    virtual void activate();  // slot 4
};
}  // namespace gf

#endif
