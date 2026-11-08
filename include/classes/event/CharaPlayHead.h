#ifndef CLASSES_EVENT_CHARAPLAYHEAD_H
#define CLASSES_EVENT_CHARAPLAYHEAD_H

#include "classes/event/ICmd.h"

#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
class CharaWeightPlayer;
// table 0x7100B3E5A0
class CharaPlayHead : public ::event::ICmd {
public:
    virtual ~CharaPlayHead() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    void play(int id, float time, bool blendIn, bool blendOut, float weight, float speed);
    void idle();  // out of line (0x71000EB3D0); term calls it
    // debug box beside the character's head: CharaObj draws it at its position, height above it
    void render(const mm::Vec3& pos, float height);
    // set to 0 by init; bit 0: playing (render draws only then), bit 1: no time limit, bit 2: idle blends out; the
    // name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10: the character (the name is not the original's)
    CharaWeightPlayer* m_weightPlayer;  // 0x18: plays the head eases (the name is not the original's)
    // the head id the running command plays (ScriptCharaHead::doit saves it for undo); the name is not the original's
    int m_id;  // 0x20
    // the time left render prints as "life"; the name is not the original's
    float m_time;  // 0x24
    // the head motion's name render prints; the name is not the original's
    const char* m_name;  // 0x28
    // the two blend frames render prints around "LOOP"; the names are not the original's
    float m_blendIn;  // 0x30
    float m_blendOut;  // 0x34
    // CharaObj holds one at 0x950, the next command at +0x38
};
}  // namespace event

#endif
