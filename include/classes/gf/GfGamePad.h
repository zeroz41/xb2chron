#ifndef CLASSES_GF_GFGAMEPAD_H
#define CLASSES_GF_GFGAMEPAD_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGamePad; }
namespace gf { enum EXEC_STATE : int; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B55158
class GfGamePad : public ::mm::mtl::PtrSingleton< ::gf::GfGamePad>, public ::gf::IGfEvent {
public:
    virtual ~GfGamePad();  // slot 0
    virtual void gevExecState(gf::EXEC_STATE);  // slot 2
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 3
};
}  // namespace gf

#endif
