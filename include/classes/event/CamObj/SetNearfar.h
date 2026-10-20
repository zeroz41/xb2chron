#ifndef CLASSES_EVENT_CAMOBJ_SETNEARFAR_H
#define CLASSES_EVENT_CAMOBJ_SETNEARFAR_H

#include "classes/event/CamObj.h"
#include "classes/event/ICmd.h"

namespace event {
// table 0x7100B3EFE8
class CamObj::SetNearfar : public ::event::ICmd {
public:
    virtual ~SetNearfar();  // slot 0
    virtual void update(event::ICmd::Param const&);  // slot 3
};
}  // namespace event

#endif
