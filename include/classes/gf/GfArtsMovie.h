// not proven yet: its table differs from the original's (word 5: _ZN2gf11GfArtsMovie3vf0Ev where the original has =-8)
#ifndef CLASSES_GF_GFARTSMOVIE_H
#define CLASSES_GF_GFARTSMOVIE_H

#include "classes/gf/IGfEvent.h"

namespace gf {
// a base of gf::GfArtsMovie no evidence names yet
class TUnk_B54488 {
public:
    virtual ~TUnk_B54488();
    virtual void gevPause(unsigned int, unsigned int) = 0;
};
// table 0x7100B54488; base at 0x0 unknown (TUnk_B54488)
class GfArtsMovie : public TUnk_B54488, public ::gf::IGfEvent {
public:
    virtual void vf0();  // slot 0
    virtual void vf1();  // slot 1
    virtual void gevPause(unsigned int, unsigned int);  // slot 2
};
}  // namespace gf

#endif
