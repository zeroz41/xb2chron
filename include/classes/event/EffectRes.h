#ifndef CLASSES_EVENT_EFFECTRES_H
#define CLASSES_EVENT_EFFECTRES_H

#include "classes/event/IResEvent.h"

namespace event {
// table 0x7100B3CEB0
class EffectRes {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~EffectRes();  // slot 1
};
}  // namespace event

#endif
