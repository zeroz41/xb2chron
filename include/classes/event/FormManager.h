#ifndef CLASSES_EVENT_FORMMANAGER_H
#define CLASSES_EVENT_FORMMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }
namespace mm { class Mat44; }

namespace event {
// table 0x7100B3CFA8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::FormManager>
class FormManager : public IManager, public mm::mtl::Singleton<FormManager> {
public:
    // user-provided: Singleton<FormManager>::getPtr stores the tables in its guard (not constant-initialized)
    FormManager() {}
    virtual ~FormManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // puts the form of that id at the matrix (SeqManager::start_form). Its body does not use this: the original's
    // start_form passes an undefined x0 (dead-argument elimination of a callee defined in the unit)
    void replace(unsigned int id, const mm::Mat44& mtx);
};
}  // namespace event

#endif
