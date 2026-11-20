#ifndef CLASSES_EVENT_CHARAPLAYTALKAUTO_H
#define CLASSES_EVENT_CHARAPLAYTALKAUTO_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace event { class CharaPlayAction; }

namespace event {
// table 0x7100B3CCD8
class CharaPlayTalkAuto : public ::event::ICmd {
public:
    CharaPlayTalkAuto()
        : m_flags(0), m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_playAction(nullptr), m_time(-1.0f) {}
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
    // CharaObj::initModel points it at the CharaObj's CharaPlayAction (update skips the lip start while its
    // m_flags bit 7 is set); the name is not the original's
    CharaPlayAction* m_playAction;  // 0x18
    // the time left: update sets it from val(1) and counts it down by the CharaObj's FrameInfo::m_cmdStep (the name
    // is not the original's)
    float m_time;  // 0x20
    unsigned char pad_24[0x4];
};
}  // namespace event

#endif
