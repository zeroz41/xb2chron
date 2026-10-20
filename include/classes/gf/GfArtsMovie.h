// not proven yet: its table differs from the original's (word 4: _ZN2gf11GfArtsMovie3vf0Ev where the original has _ZN2gf11GfArtsMovie8gevPauseEjj)
#ifndef CLASSES_GF_GFARTSMOVIE_H
#define CLASSES_GF_GFARTSMOVIE_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfArtsMovie; }

namespace gf {
// table 0x7100B54488
class GfArtsMovie : public ::mm::mtl::PtrSingleton< ::gf::GfArtsMovie>, public ::gf::IGfEvent {
public:
    virtual void vf0();  // slot 0
    virtual void vf1();  // slot 1
    virtual void gevPause(unsigned int, unsigned int);  // slot 2
};
}  // namespace gf

#endif
