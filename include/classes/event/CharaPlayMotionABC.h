#ifndef CLASSES_EVENT_CHARAPLAYMOTIONABC_H
#define CLASSES_EVENT_CHARAPLAYMOTIONABC_H

#include "classes/event/ICmd.h"

#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3CCA0
class CharaPlayMotionABC : public ::event::ICmd {
public:
    virtual ~CharaPlayMotionABC();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // debug box over the character: CharaObj draws it at its position, height above it
    void render(const mm::Vec3& pos, float height);
    // bit 0: playing (render draws only then); the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10: the character the motions play on (the name is not the original's)
    unsigned char pad_18[0x10];
    // which of the three motions plays (1-3; render prints that one's file name); the name is not the original's
    int m_phase;  // 0x28
    // the time left render prints as "life"; the name is not the original's
    float m_time;  // 0x2c
    unsigned char pad_30[0x10];
    // the three motions' paths; the name is not the original's
    const char* m_names[3];  // 0x40
    unsigned char pad_58[0x28];  // CharaObj holds one at 0x6d0, the next command at +0x80
};
}  // namespace event

#endif
