#ifndef CLASSES_EVENT_CAMMOTION_H
#define CLASSES_EVENT_CAMMOTION_H

#include "classes/event/CamBase.h"

namespace event { class FrameInfo; }
namespace mm { class Vec3; }

namespace event {
// table 0x7100B3C938
class CamMotion : public ::event::CamBase {
public:
    virtual ~CamMotion();  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
    void play(const char* name, const mm::Vec3& pos);
};
}  // namespace event

#endif
