#ifndef CLASSES_EVENT_SCRIPTCHARATALK_H
#define CLASSES_EVENT_SCRIPTCHARATALK_H

#include "classes/event/ITodo.h"

namespace event { class Param; }

namespace event {
// table 0x7100B3F438
class ScriptCharaTalk : public ::event::ITodo {
public:
    virtual ~ScriptCharaTalk();  // slot 0
    virtual void cmdName() const;  // slot 2
    virtual void doit(event::Param const&);  // slot 3
    virtual void redo(event::Param const&);  // slot 5
};
}  // namespace event

#endif
