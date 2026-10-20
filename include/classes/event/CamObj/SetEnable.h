#ifndef CLASSES_EVENT_CAMOBJ_SETENABLE_H
#define CLASSES_EVENT_CAMOBJ_SETENABLE_H

#include "classes/event/CamObj.h"
#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3EF40
class CamObj::SetEnable : public ::event::ICmd {
public:
    virtual ~SetEnable();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
