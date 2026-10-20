#ifndef CLASSES_GF_GFMANAGER_H
#define CLASSES_GF_GFMANAGER_H

#include "classes/fw/IPauseTrigger.h"
#include "classes/gf/IGfEvent.h"

namespace gf { enum GF_STATE : int; }

namespace gf {
// a base of gf::GfManager no evidence names yet
class TUnk_B59268 {
public:
    virtual ~TUnk_B59268();
    virtual void updatePauseCallback() = 0;
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE) = 0;
    virtual void activate() = 0;
};
// table 0x7100B59268; base at 0x0 unknown (TUnk_B59268)
class GfManager : public TUnk_B59268, public ::fw::IPauseTrigger, public ::gf::IGfEvent {
public:
    virtual ~GfManager();  // slot 0
    virtual void updatePauseCallback();  // slot 2
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 3
    virtual void activate();  // slot 4
};
}  // namespace gf

#endif
