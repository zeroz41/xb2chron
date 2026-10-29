#ifndef CLASSES_EVENT_LODMANAGER_H
#define CLASSES_EVENT_LODMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D250; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::LodManager>
class LodManager : public IManager, public mm::mtl::Singleton<LodManager> {
public:
    virtual ~LodManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
