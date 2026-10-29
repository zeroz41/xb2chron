#ifndef CLASSES_EVENT_TODOMANAGER_H
#define CLASSES_EVENT_TODOMANAGER_H

#include "classes/event/Param.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; class ITodo; }

namespace event {
// table 0x7100B3DBA8; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::TodoManager>
class TodoManager : public IManager, public mm::mtl::Singleton<TodoManager> {
public:
    // out of line (mm::mtl::Singleton<event::TodoManager>::getPtr's static calls it)
    TodoManager();
    virtual ~TodoManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // the script plugins' commands: exec makes the command, which then runs with a copy of the parameters
    void add(ITodo* (*exec)(), const Param& param);
    static Param s_zero;
    // fields the constructor initializes; what they hold is not known yet
    long pad_10;
    unsigned char pad_18[0x8c00];
    long pad_8c18;
    long pad_8c20;
    unsigned char pad_8c28[0x8200];
    long pad_10e28;
};
}  // namespace event

#endif
