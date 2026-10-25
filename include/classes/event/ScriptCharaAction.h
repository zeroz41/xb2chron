#ifndef CLASSES_EVENT_SCRIPTCHARAACTION_H
#define CLASSES_EVENT_SCRIPTCHARAACTION_H

#include "classes/event/ITodo.h"
#include "classes/event/MemoryManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mtl/MemManager.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F2F8
class ScriptCharaAction : public ::event::ITodo {
public:
    ScriptCharaAction() : pad_8(0) {}
    // the factory TodoManager::add takes: a new command from the event memory manager's allocator
    static ITodo* exec() {
        return new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) ScriptCharaAction;
    }
    virtual ~ScriptCharaAction() {}  // slot 0
    virtual const char* cmdName() const { return "charaact"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5
    int pad_8;  // zero until doit
    unsigned char pad_c[0x4];
};
}  // namespace event

#endif
