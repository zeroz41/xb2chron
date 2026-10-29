#ifndef CLASSES_EVENT_SCRIPTEFFECTSCALE_H
#define CLASSES_EVENT_SCRIPTEFFECTSCALE_H

#include "classes/event/ITodo.h"
#include "classes/event/MemoryManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mtl/MemManager.h"
#include "mm/Vec3.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F9F8
class ScriptEffectScale : public ::event::ITodo {
public:
    // the factory TodoManager::add takes: a new command from the event memory manager's allocator
    static ITodo* exec() {
        return new (mm::mtl::Singleton<MemoryManager>::getPtr()->m_handle, nullptr, 0, 4, false) ScriptEffectScale;
    }
    virtual ~ScriptEffectScale() {}  // slot 0
    virtual const char* cmdName() const { return "effscale"; }  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
    virtual void redo(event::Param const&);  // slot 5
    unsigned char pad_8[0x8];
    // the effect's scale before doit, which undo restores; the name is not the original's
    mm::Vec3 m_prevScale;  // 0x10
};
}  // namespace event

#endif
