#ifndef CLASSES_EVENT_CHARAPLAYTALKAUTO_H
#define CLASSES_EVENT_CHARAPLAYTALKAUTO_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3CCD8
class CharaPlayTalkAuto : public ::event::ICmd {
public:
    virtual ~CharaPlayTalkAuto();  // slot 0
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // CharaObj holds one at 0xa10, the next command at +0x28
    // bits 0 and 2 both set: the destructor sends the object MsgGameLipAction 1 (lip animation off); the name is
    // not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10: the character the command plays on (the name is not the original's)
    unsigned char pad_18[0x10];
};
}  // namespace event

#endif
