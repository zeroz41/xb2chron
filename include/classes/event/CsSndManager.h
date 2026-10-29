#ifndef CLASSES_EVENT_CSSNDMANAGER_H
#define CLASSES_EVENT_CSSNDMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3CD78; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::CsSndManager>
class CsSndManager : public IManager, public mm::mtl::Singleton<CsSndManager> {
public:
    virtual ~CsSndManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
