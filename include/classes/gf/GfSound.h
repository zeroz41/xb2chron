#ifndef CLASSES_GF_GFSOUND_H
#define CLASSES_GF_GFSOUND_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfSound; }

namespace gf {
// table 0x7100B6B940
class GfSound : public ::mm::mtl::PtrSingleton< ::gf::GfSound>, public ::gf::IGfEvent {
public:
    class SeParam;
    virtual ~GfSound();  // slot 0
    virtual void gevPause(unsigned int, unsigned int);  // slot 2
    virtual void gevLayerPause(unsigned int, bool);  // slot 3
};
}  // namespace gf

#endif
