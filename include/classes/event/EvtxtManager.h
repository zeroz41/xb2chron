#ifndef CLASSES_EVENT_EVTXTMANAGER_H
#define CLASSES_EVENT_EVTXTMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D9D8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::EvtxtManager>
class EvtxtManager : public IManager, public mm::mtl::Singleton<EvtxtManager> {
public:
    virtual ~EvtxtManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void render();
};
}  // namespace event

#endif
