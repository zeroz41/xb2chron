#ifndef CLASSES_EVENT_CHARALINERROT_H
#define CLASSES_EVENT_CHARALINERROT_H

#include "classes/event/AnmVec.h"
#include "classes/event/ICmd.h"
namespace event { class CharaDysUpdater; class CharaIKUpdater; }

namespace event {
// table 0x7100B3E4C0
class CharaLinerRot : public ::event::ICmd {
public:
    // inline: D2 is emitted in CharaObj's destructor, D0 sits in CharaObj's tail; update is the key function
    virtual ~CharaLinerRot() {}  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    // CharaObj::initModel stores the CharaObj's dynamics updater (at 0xde0); the name is not the original's
    CharaDysUpdater* m_dys;  // 0x8
    AnmVec m_anm;  // 0x10 (CharaObj's destructor clears it); the name is not the original's
};
}  // namespace event

#endif
