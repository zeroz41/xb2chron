#ifndef CLASSES_EVENT_LIPSYNCRES_H
#define CLASSES_EVENT_LIPSYNCRES_H

#include "classes/event/IResEvent.h"

namespace event {
// table 0x7100B3D298
class LipsyncRes {
public:
    virtual void OnResEvent(event::IResEvent::PARAM const&);  // slot 0
    virtual ~LipsyncRes() {}  // slot 1
};
}  // namespace event

#endif
