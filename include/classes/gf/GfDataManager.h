#ifndef CLASSES_GF_GFDATAMANAGER_H
#define CLASSES_GF_GFDATAMANAGER_H

#include "classes/gf/IGfEvent.h"

namespace gf {
// a base of gf::GfDataManager no evidence names yet
class TUnk_B4DA08 {
public:
    virtual ~TUnk_B4DA08();
    virtual void vf2();
};
// table 0x7100B4DA08; base at 0x0 unknown (TUnk_B4DA08)
class GfDataManager : public TUnk_B4DA08, public ::gf::IGfEvent {
public:
    virtual ~GfDataManager();  // slot 0
    virtual void vf2();  // slot 2
};
}  // namespace gf

#endif
