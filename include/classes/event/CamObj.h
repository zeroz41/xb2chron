#ifndef CLASSES_EVENT_CAMOBJ_H
#define CLASSES_EVENT_CAMOBJ_H

#include "classes/event/CamHands.h"

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

};
}  // namespace event

#endif
