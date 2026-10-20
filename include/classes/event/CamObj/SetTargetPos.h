#ifndef CLASSES_EVENT_CAMOBJ_SETTARGETPOS_H
#define CLASSES_EVENT_CAMOBJ_SETTARGETPOS_H

#include "classes/event/CamObj.h"
#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3EF78
class CamObj::SetTargetPos : public ::event::ICmd {
public:
    virtual ~SetTargetPos();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
