#ifndef CLASSES_EVENT_STATUSMANAGER_H
#define CLASSES_EVENT_STATUSMANAGER_H

#include "classes/ml/IWorkEvent.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::StatusManager no evidence names yet
class TUnk_B3D790 {
public:
    virtual ~TUnk_B3D790();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::StatusManager no evidence names yet
class TUnk_B3D808 {
public:
    virtual ~TUnk_B3D808();
};
// table 0x7100B3D790; base at 0x0 unknown (TUnk_B3D790), base at 0x10 unknown (TUnk_B3D808)
class StatusManager : public TUnk_B3D790, public ::ml::IWorkEvent, public TUnk_B3D808 {
public:
    virtual ~StatusManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
