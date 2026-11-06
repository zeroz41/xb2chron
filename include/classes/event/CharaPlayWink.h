#ifndef CLASSES_EVENT_CHARAPLAYWINK_H
#define CLASSES_EVENT_CHARAPLAYWINK_H

#include "classes/event/ICmd.h"
#include "mm/Vec2.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace event { class CharaWinkPlayer; class CharaLensPlayer; class ObjectChara; }

namespace event {
// table 0x7100B3E680
class CharaPlayWink : public ::event::ICmd {
public:
    virtual ~CharaPlayWink() {}  // slot 0 (inline: its D0 is in the unit's inline tail)
    virtual void init();  // slot 2
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    void idle();  // out of line (0x71000ED230); term calls it
    // 3.0.1 symbols (0x71000ED124, 0x71000ECF74)
    void update();
    mm::Vec2 calcLensXYFromTarAxis(const mm::Vec3& tar);
    // the field names are not the original's
    // bit 0: following a target (m_target, the lens), bit 1: eyes driven (idle eases them open); init clears it
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10
    unsigned char pad_18[0x8];
    CharaWinkPlayer* m_wink;  // 0x20
    CharaLensPlayer* m_lens;  // 0x28
    unsigned char pad_30[0x30];
    float m_time;  // 0x60: idle sets -1
    unsigned char pad_64[0xc];
    mm::Vec2 m_lensXY;  // 0x70: idle sets zero (a Vec2 takes 16 bytes)
    ObjectChara* m_target;  // 0x80: update aims the lens at its character's head
    unsigned char pad_88[0x8];  // CharaObj holds one at 0xab0, the next table store (a CharaMount) at +0x90
};
}  // namespace event

#endif
