#ifndef CLASSES_EVENT_CHARAPLAYMOTION_H
#define CLASSES_EVENT_CHARAPLAYMOTION_H

#include "classes/event/ICmd.h"
#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; class GfObj; }

namespace event {
class CharaIKUpdater;
class CharaDysUpdater;
// table 0x7100B3CC68
class CharaPlayMotion : public ::event::ICmd {
public:
    CharaPlayMotion()
        : m_flags(0), m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), m_ik(nullptr), m_dys(nullptr),
          m_data(nullptr), pad_30(), pad_3c(0), pad_40(0) {}
    virtual ~CharaPlayMotion();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // debug box over the character: CharaObj draws it at its position, height above it
    void render(const mm::Vec3& pos, float height);
    void play(gf::GfObj* obj, void* data, unsigned long size, float frame);
    void stop(gf::GfObj* obj);
    // bit 3: no time limit (render prints "life" without a number); the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10: the character the motion plays on (the name is not the original's)
    // the character's updaters (update sets the foot IK, play/stop reset the dynamics); the names are not the
    // original's
    CharaIKUpdater* m_ik;  // 0x18
    CharaDysUpdater* m_dys;  // 0x20
    // the motion data update loads (null when none, render draws nothing); the name is not the original's
    void* m_data;  // 0x28
    unsigned char pad_30[0x8];
    // the time left render prints as "life"; the name is not the original's
    float m_time;  // 0x38
    int pad_3c;
    int pad_40;
    unsigned char pad_44[0x4];
    // the motion's path (render prints its file name); the name is not the original's
    const char* m_name;  // 0x48
    // CharaObj holds one at 0x680, the next command at +0x50
};
}  // namespace event

#endif
