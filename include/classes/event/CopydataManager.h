#ifndef CLASSES_EVENT_COPYDATAMANAGER_H
#define CLASSES_EVENT_COPYDATAMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3E160; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::CopydataManager>
class CopydataManager : public IManager, public mm::mtl::Singleton<CopydataManager> {
public:
    virtual ~CopydataManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
