#ifndef CLASSES_EVENT_CAMHANDS_H
#define CLASSES_EVENT_CAMHANDS_H

#include "classes/event/CamBase.h"

#include "event/CvType.h"

namespace event { class FrameInfo; }
namespace mm { class Col4; }

namespace event {
// table 0x7100B3C900
class CamHands : public ::event::CamBase {
public:
    virtual ~CamHands();  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
    virtual void render(mm::Col4 const&);  // slot 3
    void setFov(float fov, CV_TYPE type);
    void addAnmFov(float time, float fov, CV_TYPE type);
    void setRotZ(float rotZ, CV_TYPE type);
    void addAnmRotZ(float time, float rotZ, CV_TYPE type);

    // bit 0: the camera follows the target object's position, bit 1: its target (the camfollowpos / camfollowtar
    // commands set and save them; playFade-style set/clear of the whole word); the name is not the original's
    unsigned int m_flags;  // 0x40
};
}  // namespace event

#endif
