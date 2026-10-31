#ifndef CLASSES_EVENT_CAMMOTION_H
#define CLASSES_EVENT_CAMMOTION_H

#include "classes/event/CamBase.h"
#include "classes/event/CamEvaPlayer.h"
#include "classes/event/CamEvaPlayerEff.h"

namespace event { class FrameInfo; }
namespace mm { class Vec3; }

namespace event {
// table 0x7100B3C938
class CamMotion : public ::event::CamBase {
public:
    virtual ~CamMotion();  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
    void play(const char* name, const mm::Vec3& pos);
    void stop();

    // the layout follows CamObj's constructor (it builds the motion in place) and the destructor; the names are not
    // the original's. Size 0xC0.
    unsigned int pad_40;
    unsigned long pad_48;
    unsigned long pad_50;
    unsigned long pad_58;
    CamEvaPlayer m_player;  // @0x60
    unsigned char pad_78[0x28];
    CamEvaPlayerEff m_playerEff;  // @0xA0
    unsigned long pad_b8;
};
}  // namespace event

#endif
