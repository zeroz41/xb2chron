#ifndef CLASSES_EVENT_CAMOBJ_SETFOV_H
#define CLASSES_EVENT_CAMOBJ_SETFOV_H

#include "classes/event/CamObj.h"
#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3EFB0
class CamObj::SetFov : public ::event::ICmd {
public:
    virtual ~SetFov();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
