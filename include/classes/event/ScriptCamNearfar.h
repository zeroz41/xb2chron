#ifndef CLASSES_EVENT_SCRIPTCAMNEARFAR_H
#define CLASSES_EVENT_SCRIPTCAMNEARFAR_H

#include "classes/event/ITodo.h"
#include "classes/event/MemoryManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mtl/MemManager.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F778
class ScriptCamNearfar : public ::event::ITodo {
public:
    // the factory TodoManager::add takes: a new command from the event memory manager's allocator
    static ITodo* exec() {
        return new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) ScriptCamNearfar;
    }
    virtual ~ScriptCamNearfar() {}  // slot 0
    virtual const char* cmdName() const { return "camnearfar"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const& param) { doit(param); }  // slot 5
    // the camera's near and far clip before doit, which undo restores; the name is not the original's
    float m_prevNear;  // 0x8
    float m_prevFar;   // 0xc
};
}  // namespace event

#endif
