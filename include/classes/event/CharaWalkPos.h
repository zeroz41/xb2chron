#ifndef CLASSES_EVENT_CHARAWALKPOS_H
#define CLASSES_EVENT_CHARAWALKPOS_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace event { class CharaIKUpdater; class CharaDysUpdater; }

namespace event {
// table 0x7100B3E418
class CharaWalkPos : public ::event::ICmd {
public:
    virtual ~CharaWalkPos();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // the character's gf object and its IK and dynamics updaters (term resets them); the names are not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8
    CharaIKUpdater* m_ik;  // 0x10
    CharaDysUpdater* m_dys;  // 0x18
    int m_gravity;  // 0x20 term turns the gravity back on when it is 0 (the name is not the original's)
    unsigned int pad_24;
    // the walk's state: term resets the walk when it is 2 or 4 (2: the turn too) and clears it; the name is not the
    // original's
    int m_state;  // 0x28
    unsigned int pad_2c;
};
}  // namespace event

#endif
