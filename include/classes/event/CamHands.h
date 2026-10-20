#ifndef CLASSES_EVENT_CAMHANDS_H
#define CLASSES_EVENT_CAMHANDS_H

#include "classes/event/CamBase.h"

namespace event { class FrameInfo; }
namespace mm { class Col4; }

namespace event {
// table 0x7100B3C900
class CamHands : public ::event::CamBase {
public:
    virtual ~CamHands();  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
    virtual void render(mm::Col4 const&);  // slot 3
};
}  // namespace event

#endif
