#ifndef CLASSES_EVENT_TODOMANAGER_H
#define CLASSES_EVENT_TODOMANAGER_H

#include "classes/event/Param.h"
#include "classes/event/TodoItem.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
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
    void updateAdd();
    static Param s_zero;
    void update();
    void render();
    unsigned int pad_10;
    unsigned int pad_14;  // bit 0 (byte test): update dumps the items, render draws them
    mm::mtl::FixedVector<TodoItem, 128> m_items;  // 0x18 (count 0x8c18); the name is not the original's
    long pad_8c20;
    // each item's parameters as text (update; render draws them); the name is not the original's
    mm::mtl::FixedVector<mm::mtl::FixStr<256>, 128> m_texts;  // 0x8c28 (count 0x10e28)
};
}  // namespace event

#endif
