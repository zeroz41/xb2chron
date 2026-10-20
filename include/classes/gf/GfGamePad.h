#ifndef CLASSES_GF_GFGAMEPAD_H
#define CLASSES_GF_GFGAMEPAD_H

#include "classes/gf/IGfEvent.h"

namespace gf { enum EXEC_STATE : int; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// a base of gf::GfGamePad no evidence names yet
class TUnk_B55158 {
public:
    virtual ~TUnk_B55158();
    virtual void gevExecState(gf::EXEC_STATE) = 0;
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE) = 0;
};
// table 0x7100B55158; base at 0x0 unknown (TUnk_B55158)
class GfGamePad : public TUnk_B55158, public ::gf::IGfEvent {
public:
    virtual ~GfGamePad();  // slot 0
    virtual void gevExecState(gf::EXEC_STATE);  // slot 2
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 3
};
}  // namespace gf

#endif
