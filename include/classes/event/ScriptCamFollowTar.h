#ifndef CLASSES_EVENT_SCRIPTCAMFOLLOWTAR_H
#define CLASSES_EVENT_SCRIPTCAMFOLLOWTAR_H

#include "classes/event/ITodo.h"
#include "classes/event/MemoryManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mtl/MemManager.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F838
class ScriptCamFollowTar : public ::event::ITodo {
public:
    // the factory TodoManager::add takes: a new command from the event memory manager's allocator
    static ITodo* exec() {
        return new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) ScriptCamFollowTar;
    }
    virtual ~ScriptCamFollowTar() {}  // slot 0
    virtual const char* cmdName() const { return "camflwtar"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const& param) { doit(param); }  // slot 5

    // the camera's follow flag before doit, which undo restores; the name is not the original's
    bool m_prevFollow;  // 0x8
};
}  // namespace event

#endif
