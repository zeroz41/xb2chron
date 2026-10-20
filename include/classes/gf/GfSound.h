#ifndef CLASSES_GF_GFSOUND_H
#define CLASSES_GF_GFSOUND_H

#include "classes/gf/IGfEvent.h"

namespace gf {
// a base of gf::GfSound no evidence names yet
class TUnk_B6B940 {
public:
    virtual ~TUnk_B6B940();
    virtual void gevPause(unsigned int, unsigned int) = 0;
    virtual void gevLayerPause(unsigned int, bool) = 0;
};
// table 0x7100B6B940; base at 0x0 unknown (TUnk_B6B940)
class GfSound : public TUnk_B6B940, public ::gf::IGfEvent {
public:
    class SeParam;
    virtual ~GfSound();  // slot 0
    virtual void gevPause(unsigned int, unsigned int);  // slot 2
    virtual void gevLayerPause(unsigned int, bool);  // slot 3
};
}  // namespace gf

#endif
