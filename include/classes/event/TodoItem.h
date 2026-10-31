#ifndef CLASSES_EVENT_TODOITEM_H
#define CLASSES_EVENT_TODOITEM_H

#include "mm/mtl/FixStr.h"
#include "classes/event/Param.h"

namespace event {
class ITodo;
// table 0x7100B3FC28; TodoManager's queue element (TodoManager::add builds one: the frame count, the command's
// creator, a copy of the parameters, the command it made)
class TodoItem {
public:
    virtual ~TodoItem() {}  // slot 0
    // the parameters' text (TodoManager::update dumps each item's into its string list)
    void createString(mm::mtl::FixStr<256>& str);
    unsigned int pad_8;  // FrameManager's frame count when added
    ITodo* (*pad_10)();  // the creator add was given
    Param m_param;  // 0x18; the name is not the original's
    ITodo* m_todo;  // 0x110; what the creator made (deleted by clear); the name is not the original's
};
}  // namespace event

#endif
