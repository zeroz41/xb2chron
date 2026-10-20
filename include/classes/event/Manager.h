#ifndef CLASSES_EVENT_MANAGER_H
#define CLASSES_EVENT_MANAGER_H

#include "classes/ml/IWorkBackground.h"
#include "classes/ml/IWorkEvent.h"

namespace ml { class EventView; }

namespace event {
// a base of event::Manager no evidence names yet
class TUnk_B3E2F8 {
public:
    virtual ~TUnk_B3E2F8();
    virtual void OnKeyDown(ml::EventView*) = 0;
    virtual void bkgHomeMenu(bool) = 0;
};
// table 0x7100B3E2F8; base at 0x0 unknown (TUnk_B3E2F8)
class Manager : public TUnk_B3E2F8, public ::ml::IWorkEvent, public ::ml::IWorkBackground {
public:
    virtual ~Manager();  // slot 0
    virtual void OnKeyDown(ml::EventView*);  // slot 2
    virtual void bkgHomeMenu(bool);  // slot 3
};
}  // namespace event

#endif
