#ifndef CLASSES_EVENT_CHARALINERPOS_H
#define CLASSES_EVENT_CHARALINERPOS_H

#include "classes/event/AnmVec.h"
#include "classes/event/ICmd.h"
namespace event { class CharaDysUpdater; class CharaIKUpdater; }

namespace event {
// table 0x7100B3E488
class CharaLinerPos : public ::event::ICmd {
public:
    // inline: D2 is emitted in CharaObj's destructor, D0 sits in CharaObj's tail; update is the key function
    CharaLinerPos() : m_ik(nullptr), m_dys(nullptr), m_gravity(0) {}
    virtual ~CharaLinerPos() {}  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    // CharaObj::initModel stores the CharaObj's IK and dynamics updaters (at 0xd60 and 0xde0) and its 0xd3c word;
    // the names are not the original's
    CharaIKUpdater* m_ik;  // 0x8
    CharaDysUpdater* m_dys;  // 0x10
    int m_gravity;  // 0x18 update turns the gravity off at the start when it is 0
    AnmVec m_anm;  // 0x20 (CharaObj's destructor clears it); the name is not the original's
};
}  // namespace event

#endif
