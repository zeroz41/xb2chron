#ifndef CLASSES_EVENT_SCRIPTCHARAMOTIONABC_H
#define CLASSES_EVENT_SCRIPTCHARAMOTIONABC_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F378
class ScriptCharaMotionABC : public ::event::ITodo {
public:
    virtual ~ScriptCharaMotionABC();  // slot 0
    virtual void cmdName() const;  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
};
}  // namespace event

#endif
