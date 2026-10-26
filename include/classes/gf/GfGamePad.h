#ifndef CLASSES_GF_GFGAMEPAD_H
#define CLASSES_GF_GFGAMEPAD_H

#include "classes/gf/IGfEvent.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGamePad; }
namespace fw { struct PadData; }
namespace gf { enum EXEC_STATE : int; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B55158
class GfGamePad : public ::mm::mtl::PtrSingleton< ::gf::GfGamePad>, public ::gf::IGfEvent {
public:
    virtual ~GfGamePad();  // slot 0
    // the player's pad data: the manager's at 0x50, else &fw::PadManager::getControlPadData(0) (a pointer: GfMenuMnagerPadRead::uiGetControlPad returns a reference to it without a tail call)
    static const fw::PadData* getPadPlayer();
    virtual void gevExecState(gf::EXEC_STATE);  // slot 2
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 3
};
}  // namespace gf

#endif
