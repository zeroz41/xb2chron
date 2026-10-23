#ifndef CLASSES_GF_GFGAMESTATE_H
#define CLASSES_GF_GFGAMESTATE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "ai/Fsm.h"
#include "classes/gf/GfAllocator.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfGameState; }
namespace gf { class GfSetupParam; }
namespace gf { enum GF_STATE : int; }

namespace gf {
// table 0x7100B55FF0; the game's state machine (the states gf_game_state.cpp makes, by GF_STATE)
// (field names are not the original's except m_stateReserve, after get/setStateReserve)
class GfGameState : public ::mm::mtl::PtrSingleton< ::gf::GfGameState> {
public:
    GfGameState()
        : m_fsm(getAllocator(ALLOCATOR(0))), m_stateFlags(0), m_stateReserve(static_cast<GF_STATE>(3)),
          m_reserveFrame(0), m_stateTime(0.0f) {}
    virtual ~GfGameState();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    static void update(const fw::UpdateInfo& info);
    static void clear();  // restarts the time in the state
    static bool test(unsigned int flags);  // any of the current state's flags (its onEnter sets them)
    static GF_STATE getState();
    static GF_STATE getStateReserve();
    static void setStateReserve(GF_STATE state);
    static void setState(GF_STATE state, bool keepReserve);

    ai::Fsm m_fsm;
    unsigned int m_stateFlags;      // set by each state's onEnter
    GF_STATE m_stateReserve;
    unsigned int m_reserveFrame;    // GfInfo's frame count when m_stateReserve was set
    float m_stateTime;              // the time in the current state (update adds, setState and clear zero it)
};
}  // namespace gf

#endif
