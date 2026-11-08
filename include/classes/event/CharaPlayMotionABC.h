#ifndef CLASSES_EVENT_CHARAPLAYMOTIONABC_H
#define CLASSES_EVENT_CHARAPLAYMOTIONABC_H

#include "classes/event/ICmd.h"

#include "mm/Vec3.h"

namespace gf { class GF_OBJ_HANDLE; class GfObj; }

namespace event {
class CharaIKUpdater;
class CharaDysUpdater;
// table 0x7100B3CCA0
class CharaPlayMotionABC : public ::event::ICmd {
public:
    virtual ~CharaPlayMotionABC();  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    // debug box over the character: CharaObj draws it at its position, height above it
    void render(const mm::Vec3& pos, float height);
    void updateBlend(gf::GfObj* obj, float weight0, float weight1, float weight2);
    void stopMotion(gf::GfObj* obj);
    // bit 0: playing (render draws only then); the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10: the character the motions play on (the name is not the original's)
    // the character's updaters (term sets the foot IK, stopMotion resets the dynamics); the names are not the
    // original's
    CharaIKUpdater* m_ik;  // 0x18
    CharaDysUpdater* m_dys;  // 0x20
    // which of the three motions plays (1-3; render prints that one's file name); the name is not the original's
    int m_phase;  // 0x28
    // the time left render prints as "life"; the name is not the original's
    float m_time;  // 0x2c
    unsigned char pad_30[0x4];
    // each motion's weight slot updateBlend writes (negative: none); the name is not the original's
    int m_weightSlots[3];  // 0x34
    // the three motions' paths; the name is not the original's
    const char* m_names[3];  // 0x40
    unsigned char pad_58[0x8];
    // the motion updateBlend fades in (0-2); the name is not the original's
    int m_blendIndex;  // 0x60
    // how far the fade has gone (0-1); the name is not the original's
    float m_blendRate;  // 0x64
    // the weights updateBlend hands on, and the ones the fade starts from; the names are not the original's
    float m_weights[3];  // 0x68
    float m_fromWeights[3];  // 0x74
    // CharaObj holds one at 0x6d0, the next command at +0x80
};
}  // namespace event

#endif
