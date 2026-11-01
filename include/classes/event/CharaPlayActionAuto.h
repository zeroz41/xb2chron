#ifndef CLASSES_EVENT_CHARAPLAYACTIONAUTO_H
#define CLASSES_EVENT_CHARAPLAYACTIONAUTO_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3CC30
class CharaPlayActionAuto : public ::event::ICmd {
public:
    virtual ~CharaPlayActionAuto();  // slot 0
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // CharaObj holds one, the next command at +0x28
    // bit 2 set: the destructor puts the character back (bit 0 set: MsgGameTalkAction 2, else EVT_acttype row 1's
    // cmd2/stat2 on its event animation); the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10: the character the command plays on (the name is not the original's)
    unsigned char pad_18[0x10];
};
}  // namespace event

#endif
