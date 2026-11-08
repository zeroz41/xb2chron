#ifndef CLASSES_EVENT_CHARAPLAYACTION_H
#define CLASSES_EVENT_CHARAPLAYACTION_H

#include "classes/event/ICmd.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3E530
class CharaPlayAction : public ::event::ICmd {
public:
    virtual ~CharaPlayAction() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    void idle();  // out of line (0x71000E7D04); term calls it unless bit 1 is set
    // debug box over the character: CharaObj draws it at its position, height above it
    void render(const mm::Vec3& pos, float height);
    // bit 1: term clears it instead of calling idle; the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10: the character the command plays on (the name is not the original's)
    unsigned char pad_18[0x18];
    // the action id ScriptCharaAction::doit saves for undo while the command is queued; the name is not the original's
    int m_id;  // 0x30
    // the time left render prints as "life" (bit 5 of m_flags: no limit); the name is not the original's
    float m_time;  // 0x34
    // the text render prints under the label; the name is not the original's
    const char* m_name;  // 0x38
    // CharaObj holds one, the next command at +0x40
};
}  // namespace event

#endif
