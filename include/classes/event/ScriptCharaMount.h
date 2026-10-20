#ifndef CLASSES_EVENT_SCRIPTCHARAMOUNT_H
#define CLASSES_EVENT_SCRIPTCHARAMOUNT_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F4B8
class ScriptCharaMount : public ::event::ITodo {
public:
    virtual ~ScriptCharaMount();  // slot 0
    virtual void cmdName() const;  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void undo(event::Param const&);  // slot 4
};
}  // namespace event

#endif
