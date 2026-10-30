#ifndef CLASSES_EVENT_CAMOBJ_H
#define CLASSES_EVENT_CAMOBJ_H

#include "classes/event/CamBase.h"
#include "classes/event/CamHands.h"
#include "classes/event/CmdQueue.h"
#include "classes/event/CamMotion.h"

namespace event { class FrameInfo; }
namespace mm { class Col4; }

namespace event {
// table 0x7100B3C970
class CamObj {
public:
    class SetEnable;
    class SetFov;
    class SetNearfar;
    class SetTargetPos;
    virtual ~CamObj();  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
    virtual void render(mm::Col4 const&);  // slot 3
    virtual void tail();  // slot 4
    void changeActive(CamBase* cam);

    unsigned char pad_8[0x28];
    float m_fov;   // 0x30; the camcommands save it before changing it; the name is not the original's
    float m_rotZ;  // 0x34; the name is not the original's
    unsigned char pad_38[0x78];
    CamHands m_hands;  // 0xb0; the name is not the original's
    // CamHands is bigger than declared (setFov writes m_hands+0x480): part of this space is its
    unsigned char pad_f8[0xab8];
    CamMotion m_motion;  // 0xbb0; ScriptCamMotion plays it; the name is not the original's
    // 1.0.0's CamObj::end (0x71000B5748; 3.0.1 inlines it into ObjectCamera::end): the queued commands erased
    // first to last, then the motion stopped
    void end() {
        m_cmdQueue.eraseAll();
        m_motion.stop();
    }
    unsigned char pad_bf0[0x80];
    // the camera update runs and copies its fields from (0x70 holds one of them); render/tail work only while one is
    // set; the name is not the original's
    CamBase* m_activeCam;  // 0xc70
    CmdQueue<8, 0> m_cmdQueue;  // 0xc78; erased by end (CmdQueue<8,0>::erase); the name is not the original's

};
}  // namespace event

#endif
