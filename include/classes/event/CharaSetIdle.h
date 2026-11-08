#ifndef CLASSES_EVENT_CHARASETIDLE_H
#define CLASSES_EVENT_CHARASETIDLE_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace event { class CharaDysUpdater; }

namespace event {
// table 0x7100B3E760
class CharaSetIdle : public ::event::ICmd {
public:
    virtual ~CharaSetIdle() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    // set to 0 by init (the command's step; the name is not the original's)
    int m_step;  // 0x8
    unsigned int pad_c;
    // the character's gf object (update sets its idle state); the name is not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10
    // the character's dynamics updater (update resets its dynamics); the name is not the original's
    CharaDysUpdater* m_dys;  // 0x18
    // the idle id update stores; ScriptCharaSetIdle::doit reads it back while the command is queued (the name is
    // not the original's)
    int m_id;  // 0x20
    unsigned char pad_24[0x4];  // CharaObj holds one at 0x5e0, the next command at 0x608
};
}  // namespace event

#endif
