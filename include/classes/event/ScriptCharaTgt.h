#ifndef CLASSES_EVENT_SCRIPTCHARATGT_H
#define CLASSES_EVENT_SCRIPTCHARATGT_H

#include "classes/event/ITodo.h"
#include "classes/event/MemoryManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mtl/MemManager.h"
#include "classes/event/TarAxis.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F1F8
class ScriptCharaTgt : public ::event::ITodo {
public:
    // the factory TodoManager::add takes: a new command from the event memory manager's allocator
    static ITodo* exec() {
        return new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) ScriptCharaTgt;
    }
    virtual ~ScriptCharaTgt() {}  // slot 0
    virtual const char* cmdName() const { return "charatgt"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5

    // whether the character's setTar command was queued when doit ran; the name is not the original's
    bool m_wasQueued;  // 0x8
    // the active object's TarAxis before doit; the name is not the original's
    TarAxis m_prevTar;  // 0x10
};
}  // namespace event

#endif
