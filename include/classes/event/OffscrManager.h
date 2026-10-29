#ifndef CLASSES_EVENT_OFFSCRMANAGER_H
#define CLASSES_EVENT_OFFSCRMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3C168; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::OffscrManager>
class OffscrManager : public IManager, public mm::mtl::Singleton<OffscrManager> {
public:
    virtual ~OffscrManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
};
}  // namespace event

#endif
