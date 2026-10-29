#ifndef CLASSES_EVENT_MDLSTMMANAGER_H
#define CLASSES_EVENT_MDLSTMMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3C510; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::MdlstmManager>
class MdlstmManager : public IManager, public mm::mtl::Singleton<MdlstmManager> {
public:
    virtual ~MdlstmManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void update();
    void clear();
};
}  // namespace event

#endif
