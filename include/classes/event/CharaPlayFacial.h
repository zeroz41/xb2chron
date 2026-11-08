#ifndef CLASSES_EVENT_CHARAPLAYFACIAL_H
#define CLASSES_EVENT_CHARAPLAYFACIAL_H

#include "classes/event/ICmd.h"

#include "mm/Vec3.h"

namespace event {
// table 0x7100B3E610
class CharaPlayFacial : public ::event::ICmd {
public:
    virtual ~CharaPlayFacial() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    void idle();  // out of line (0x71000EBAB8); term calls it
    // debug box beside the character's head: CharaObj draws it at its position, height above it
    void render(const mm::Vec3& pos, float height);
    // set to 0 by init; bit 0: playing (render draws only then), bit 1: no time limit; the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x14];
    // the facial id the running command plays (ScriptCharaFacial::doit saves it for undo); the name is not the original's
    int m_id;  // 0x20
    // the time left render prints as "life"; the name is not the original's
    float m_time;  // 0x24
    // the names and values render prints in its "seat:", "priset:", "brow:", "eye:" and "lip:" rows and the two
    // blend frames of its "blend:" row; the names are not the original's
    const char* m_seat;  // 0x28
    const char* m_preset;  // 0x30
    const char* m_brow;  // 0x38
    float m_browValue;  // 0x40
    unsigned char pad_44[0x4];
    const char* m_eye;  // 0x48
    float m_eyeValue;  // 0x50
    unsigned char pad_54[0x4];
    const char* m_lip;  // 0x58
    float m_lipValue;  // 0x60
    float m_blendIn;  // 0x64
    float m_blendOut;  // 0x68
    unsigned char pad_6c[0x4];  // CharaObj holds one at 0x9a0, the next command at +0x70
};
}  // namespace event

#endif
