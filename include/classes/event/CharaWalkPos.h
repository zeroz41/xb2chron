#ifndef CLASSES_EVENT_CHARAWALKPOS_H
#define CLASSES_EVENT_CHARAWALKPOS_H

#include "classes/event/ICmd.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace event { class CharaIKUpdater; class CharaDysUpdater; }

namespace event {
// table 0x7100B3E418
class CharaWalkPos : public ::event::ICmd {
public:
    CharaWalkPos()
        : m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_ik(nullptr), m_dys(nullptr), m_gravity(0), pad_24(0),
          m_state(0), pad_30(0), pad_40(0), pad_48(0), pad_50(0), pad_58(0), pad_60(0), pad_70(0), pad_78(0), pad_80(0),
          pad_84(), pad_90(30.0f), pad_94(0), pad_b4(0) {}
    virtual ~CharaWalkPos();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // the character's gf object and its IK and dynamics updaters (term resets them); the names are not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x8
    CharaIKUpdater* m_ik;  // 0x10
    CharaDysUpdater* m_dys;  // 0x18
    int m_gravity;  // 0x20 term turns the gravity back on when it is 0 (the name is not the original's)
    unsigned int pad_24;
    // the walk's state: term resets the walk when it is 2 or 4 (2: the turn too) and clears it; the name is not the
    // original's
    int m_state;  // 0x28
    unsigned int pad_2c;
    // 0x30..0xd0: the walk's work (update reads and writes it up to 0xcc; CharaObj's constructor stores these through
    // the inline constructor)
    int pad_30;
    unsigned char pad_34[0xc];
    unsigned long pad_40;
    int pad_48;
    unsigned char pad_4c[0x4];
    unsigned long pad_50;
    int pad_58;
    unsigned char pad_5c[0x4];
    int pad_60;
    unsigned char pad_64[0xc];
    unsigned long pad_70;
    int pad_78;
    unsigned char pad_7c[0x4];
    int pad_80;
    unsigned char pad_84[0x8];
    unsigned char pad_8c[0x4];
    float pad_90;  // the constructor stores 30
    int pad_94;
    unsigned char pad_98[0x1c];
    int pad_b4;
    unsigned char pad_b8[0x18];
};
}  // namespace event

#endif
