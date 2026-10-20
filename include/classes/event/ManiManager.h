#ifndef CLASSES_EVENT_MANIMANAGER_H
#define CLASSES_EVENT_MANIMANAGER_H

#include "classes/ml/IWorkEvent.h"

namespace event { enum MSG_TYPE : int; }
namespace ml { class EventView; }

namespace event {
// a base of event::ManiManager no evidence names yet
class TUnk_B3DB00 {
public:
    virtual ~TUnk_B3DB00();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
    virtual void OnMouseButtonDown(ml::EventView*) = 0;
    virtual void OnKeyDown(ml::EventView*) = 0;
};
// a base of event::ManiManager no evidence names yet
class TUnk_B3DB38 {
public:
    virtual ~TUnk_B3DB38();
};
// table 0x7100B3DB00; base at 0x0 unknown (TUnk_B3DB00), base at 0x8 unknown (TUnk_B3DB38)
class ManiManager : public TUnk_B3DB00, public TUnk_B3DB38, public ::ml::IWorkEvent {
public:
    virtual ~ManiManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    virtual void OnMouseButtonDown(ml::EventView*);  // slot 3
    virtual void OnKeyDown(ml::EventView*);  // slot 4
};
}  // namespace event

#endif
