#ifndef CLASSES_EVENT_SCRIPTCHARAMOUNT_H
#define CLASSES_EVENT_SCRIPTCHARAMOUNT_H

#include "classes/event/ITodo.h"
#include "classes/event/MemoryManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mtl/MemManager.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F4B8
class ScriptCharaMount : public ::event::ITodo {
public:
    // the factory TodoManager::add takes: a new command from the event memory manager's allocator
    static ITodo* exec() {
        return new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) ScriptCharaMount;
    }
    virtual ~ScriptCharaMount() {}  // slot 0
    virtual const char* cmdName() const { return "charamount"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
};
}  // namespace event

#endif
