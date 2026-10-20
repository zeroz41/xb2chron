#ifndef CLASSES_GF_GFAUTOTALKMANAGER_H
#define CLASSES_GF_GFAUTOTALKMANAGER_H

#include "classes/gf/IGfEvent.h"

namespace gf { enum RELOAD_BDAT : int; }

namespace gf {
// a base of gf::GfAutoTalkManager no evidence names yet
class TUnk_B53838 {
public:
    virtual ~TUnk_B53838();
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int) = 0;
};
// table 0x7100B53838; base at 0x0 unknown (TUnk_B53838)
class GfAutoTalkManager : public TUnk_B53838, public ::gf::IGfEvent {
public:
    virtual ~GfAutoTalkManager();  // slot 0
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int);  // slot 2
};
}  // namespace gf

#endif
