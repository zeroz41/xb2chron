#ifndef CLASSES_EVENT_BOUMANAGER_H
#define CLASSES_EVENT_BOUMANAGER_H

#include "classes/ml/IWorkEvent.h"

namespace event { enum MSG_TYPE : int; }
namespace ml { class EventView; }

namespace event {
// a base of event::BouManager no evidence names yet
class TUnk_B3DA40 {
public:
    virtual ~TUnk_B3DA40();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
    virtual void OnMouseButtonDown(ml::EventView*) = 0;
    virtual void OnMouseMove(ml::EventView*) = 0;
    virtual void OnMouseButtonUp(ml::EventView*) = 0;
    virtual void OnKeyDown(ml::EventView*) = 0;
    virtual void OnKeyUp(ml::EventView*) = 0;
};
// a base of event::BouManager no evidence names yet
class TUnk_B3DA90 {
public:
    virtual ~TUnk_B3DA90();
};
// table 0x7100B3DA40; base at 0x0 unknown (TUnk_B3DA40), base at 0x8 unknown (TUnk_B3DA90)
class BouManager : public TUnk_B3DA40, public TUnk_B3DA90, public ::ml::IWorkEvent {
public:
    virtual ~BouManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    virtual void OnMouseButtonDown(ml::EventView*);  // slot 3
    virtual void OnMouseMove(ml::EventView*);  // slot 4
    virtual void OnMouseButtonUp(ml::EventView*);  // slot 5
    virtual void OnKeyDown(ml::EventView*);  // slot 6
    virtual void OnKeyUp(ml::EventView*);  // slot 7
};
}  // namespace event

#endif
