#ifndef GF_PC_WALLAICONTEXTFIELD_H
#define GF_PC_WALLAICONTEXTFIELD_H

namespace gf { namespace pc { class BlackBoardField; } }

namespace gf { namespace pc {

// what the wall AI's states work on (their enter, update and leave take one): TaskFieldWallPrepare holds it and
// hands its Fsm its address as the states' owner (1.0.0's and 3.0.1's state functions name the class; the field
// name is not the original's)
struct WallAiContextField {
    BlackBoardField* m_blackBoard;  // the blackboard while the task steps the states or handles an event
};

}}  // namespace gf::pc

#endif
