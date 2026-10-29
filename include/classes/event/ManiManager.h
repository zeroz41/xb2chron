#ifndef CLASSES_EVENT_MANIMANAGER_H
#define CLASSES_EVENT_MANIMANAGER_H

#include "classes/ml/IWorkEvent.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }
namespace ml { class EventView; }

namespace event {
// table 0x7100B3DB00; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::ManiManager>
class ManiManager : public IManager, public mm::mtl::Singleton<ManiManager>, public ::ml::IWorkEvent {
public:
    virtual ~ManiManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    virtual void OnMouseButtonDown(ml::EventView*);  // slot 3
    virtual void OnKeyDown(ml::EventView*);  // slot 4
};
}  // namespace event

#endif
