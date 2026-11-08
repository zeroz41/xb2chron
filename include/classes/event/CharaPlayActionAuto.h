#ifndef CLASSES_EVENT_CHARAPLAYACTIONAUTO_H
#define CLASSES_EVENT_CHARAPLAYACTIONAUTO_H

#include "classes/event/ICmd.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; class GfObj; }

namespace event {
// table 0x7100B3CC30
class CharaPlayActionAuto : public ::event::ICmd {
public:
    virtual ~CharaPlayActionAuto();  // slot 0
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // out of line (0x71000E7198 / 0x71000E742C, not written yet): update starts the character's EVT_acttype
    // action once nothing keeps it busy, and puts it back when the time runs out
    void play(gf::GfObj* obj) const;
    void idle();
    // debug box over the character: CharaObj draws it at its position, height above it
    void render(const mm::Vec3& pos, float height);
    // CharaObj holds one, the next command at +0x28
    // bit 2 set: the destructor puts the character back (bit 0 set: MsgGameTalkAction 2, else EVT_acttype row 1's
    // cmd2/stat2 on its event animation); the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10: the character the command plays on (the name is not the original's)
    unsigned char pad_18[0x8];
    // the time left: update sets it from val(1) and counts it down by the CharaObj's FrameInfo::m_cmdStep (the name
    // is not the original's)
    float m_time;  // 0x20
    unsigned char pad_24[0x4];
};
}  // namespace event

#endif
