#ifndef CLASSES_EVENT_CAMFIELD_H
#define CLASSES_EVENT_CAMFIELD_H

#include "classes/event/CamBase.h"

namespace event { class FrameInfo; }

namespace event {
// table 0x7100B3C8C8
class CamField : public ::event::CamBase {
public:
    virtual ~CamField();  // slot 0
    virtual void update(event::FrameInfo const&);  // slot 2
};
}  // namespace event

#endif
